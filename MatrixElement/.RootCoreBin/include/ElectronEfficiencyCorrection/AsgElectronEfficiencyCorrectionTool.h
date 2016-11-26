// Dear emacs, this is -*-c++-*-

#ifndef __ASGELECTRONEFFICIENCYCORRECTIONTOOL__
#define __ASGELECTRONEFFICIENCYCORRECTIONTOOL__

/**
   @class AthElectronEfficiencyCorrectionTool
   @brief Calculate the egamma scale factors in Athena

   @author Kristin Lohwasser (Rob Roy Fletcher, Karsten Koeneke)
   @date   May 2014
*/

// STL includes
#include <vector>
#include <string>

// Utility includes
#include "boost/unordered_map.hpp"

// Include the return object and the underlying ROOT tool
#include "PATCore/TResult.h"
#include "AthContainers/AuxElement.h"

//xAOD includes
#include "AsgTools/AsgTool.h"
#include "PATInterfaces/ISystematicsTool.h"
#include "PATInterfaces/SystematicRegistry.h"
#include "PATInterfaces/CorrectionCode.h"
#include "ElectronEfficiencyCorrection/TElectronEfficiencyCorrectionTool.h"
#include "ElectronEfficiencyCorrection/IAsgElectronEfficiencyCorrectionTool.h"
#include "xAODEgamma/ElectronFwd.h"

class AsgElectronEfficiencyCorrectionTool
  : virtual public IAsgElectronEfficiencyCorrectionTool,
    public asg::AsgTool
{
  ASG_TOOL_CLASS(AsgElectronEfficiencyCorrectionTool, IAsgElectronEfficiencyCorrectionTool)

  public:
  /// Standard constructor
  AsgElectronEfficiencyCorrectionTool ( const std::string myname );

  /// Standard destructor
  virtual ~AsgElectronEfficiencyCorrectionTool();


public:
  /// Gaudi Service Interface method implementations
  virtual StatusCode initialize();

  /// Gaudi Service Interface method implementations
  virtual StatusCode finalize();

  // Main methods from IUserDataCalcTool
public:

  int getNumberOfToys( ){return m_number_of_toys;} ;


  CP::CorrectionCode getEfficiencyScaleFactor(const xAOD::Electron& inputObject, double& efficiencyScaleFactor) const;
  CP::CorrectionCode applyEfficiencyScaleFactor(const xAOD::Electron& inputObject) const;

  /// print available/implemented correlation models
  void printCorrelationModels() {
    ATH_MSG_INFO(" Available Correlation Models for the ElectronEfficiencyCorrectionTool");
    ATH_MSG_INFO("FULL");
    ATH_MSG_INFO("SIMPLIFIED");
    ATH_MSG_INFO("MCTOYS");
    ATH_MSG_INFO("SYST");
    ATH_MSG_INFO("COMBMCTOYS");
    ATH_MSG_INFO("TOTAL");
  } ;

  /// returns: whether this tool is affected by the given systematis
  virtual bool isAffectedBySystematic( const CP::SystematicVariation& systematic ) const ;
  
  /// returns: the list of all systematics this tool can be affected by
  virtual CP::SystematicSet affectingSystematics() const ;
  
  /// returns: the list of all systematics this tool recommends to use
  virtual CP::SystematicSet recommendedSystematics() const ;

  /// returns: the currently applied systematics
  const CP::SystematicSet& appliedSystematics() const {
    return *m_appliedSystematics;
  }

  /// Configure this tool for the given systematics
  virtual CP::SystematicCode applySystematicVariation ( const CP::SystematicSet& systConfig ) ;

  CP::SystematicCode registerSystematics();

  // Private member variables
private:

  /// The main calculate method: the actual correction factors are determined here
  const Root::TResult& calculate( const xAOD::Electron& egam, const unsigned int runnumber, int &currentElectronSimplifiedUncorrSystRegion, int& currentElectronUncorrSystRegion ) const ;
  CP::SystematicCode InitSystematics();

  // struct for toys
  struct SystConf{
    float m_total;
    unsigned m_toy_index;
    float m_toy_scale;
  };

  /// Pointer to the underlying ROOT based tool
  Root::TElectronEfficiencyCorrectionTool* m_rootTool;

  /// A dummy return TResult object
  Root::TResult m_resultDummy;

  /// Systematics filter map
  boost::unordered_map<CP::SystematicSet, CP::SystematicSet> m_systFilter;

  ///Affected systematic, should be done only once
  CP::SystematicSet m_affectedSys;

  /// Currently applied systematics
  CP::SystematicSet* m_appliedSystematics;

  // Properties
  std::string m_correlation_model_name;

  /// The list of file names
  std::vector< std::string > m_corrFileNameList;

  /// The prefix string for the result
  std::string m_resultPrefix;

  /// The string for the result
  std::string m_resultName;

  // The prefix for the systematic name
  std::string m_sysSubstring;

  /// The Event info collection name
  std::string m_eventInfoCollectionName;

  //use RandomRun Number
  bool m_useRandomRunNumber;
  unsigned int m_defaultRandomRunNumber;

  //The data type
  PATCore::ParticleDataType::DataType m_dataType;

  /// Force the data type to a given value
  int m_dataTypeOverwrite;

  // Number of toys:
  int m_number_of_toys;

  // seed for toys:
  int m_seed_toys;
    
  // scale for toy uncertainty:
  double m_scale_toys;

  // number if systematics uncertainty    
  int m_nCorrSyst;
  int m_nUncorrSyst ;
  std::map<float, std::vector<float> > m_pteta_bins;
  
  // simplified uncorrelation regions
  TH2F * m_UncorrRegions;
  int m_nSimpleUncorrSyst;

}; // End: class definition



#endif
