///////////////////////// -*- C++ -*- /////////////////////////////
// JetCalibrationTool.h 
// Header file for class JetCalibrationTool
// Author: Joe Taenzer <joseph.taenzer@cern.ch>
/////////////////////////////////////////////////////////////////// 
#ifndef JETCALIBTOOLS_APPLYJETCALIBRATION_H
#define JETCALIBTOOLS_APPLYJETCALIBRATION_H 1

#include <string.h>

#include <TString.h>
#include <TEnv.h>

#include "AsgTools/AsgTool.h"

#include "xAODEventInfo/EventInfo.h"
#include "xAODTracking/VertexContainer.h"
#include "xAODEventShape/EventShape.h"

// JetCalibTools includes
#include "JetCalibTools/IJetCalibrationTool.h"
#include "JetCalibTools/JetCalibrationToolBase.h"
#include "JetCalibTools/CalibrationMethods/JetPileupCorrection.h"
#include "JetCalibTools/CalibrationMethods/ResidualOffsetCorrection.h"
#include "JetCalibTools/CalibrationMethods/EtaJESCorrection.h"
#include "JetCalibTools/CalibrationMethods/GlobalSequentialCorrection.h"
#include "JetCalibTools/CalibrationMethods/InsituDataCorrection.h"
#include "JetCalibTools/CalibrationMethods/JMSCorrection.h"

class JetPileupCorrection;
class ResidualOffsetCorrection;
class EtaJESCorrection;
class GlobalSequentialCorrection;
class InsituDataCorrection;
class JMSCorrection;

class JetCalibrationTool
  : virtual public ::JetCalibrationToolBase {

  ASG_TOOL_CLASS2(JetCalibrationTool, IJetCalibrationTool, IJetModifier)

public: 

  // Default constructor: 
  JetCalibrationTool();

  /// Constructor with parameters: 
  JetCalibrationTool(const std::string& name);

  JetCalibrationTool(const std::string& name,
                     TString jetAlgo, 
                     TString config = "", 
                     TString calibSeq = "JetArea_Offset_AbsoluteEtaJES_Insitu",
                     bool isData = true,
		     bool mass = false,
                     TString rhoKey = "auto",
                     TString dir = "JetCalibTools/CalibrationConfigs/",
                     TString eInfoName = "EventInfo");


  /// Destructor: 
  virtual ~JetCalibrationTool(); 

  enum jetScale { EM, LC, PFLOW };

  // Initialize the tool (default, assumes private members were set in the constructor)
  virtual StatusCode initializeTool(const std::string& name);

  // PATInterfaces inherited method
  StatusCode initialize();
 
  //PATInterfaces inherited method
  StatusCode finalize();

  ///Implement IJetCalibrationTool interface :
  virtual StatusCode applyCalibration(xAOD::Jet& jet) const;
  //PATInterfaces version of applyCalibration
  virtual CP::CorrectionCode applyCorrection(xAOD::Jet& jet);

  virtual int modify(xAOD::JetContainer&) const;
  virtual int modifyJet(xAOD::Jet&) const;
  
protected:
  /// This is where the actual calibration code goes.
  virtual StatusCode calibrateImpl(xAOD::Jet& jet, JetEventInfo& jetEventInfo) const;

//Private methods
private:
  //Set event by event info like rho, mu, NPV
  virtual StatusCode initializeEvent(JetEventInfo& jetEventInfo) const;
  //Create the vector of calibration classes
  StatusCode getCalibClass(const std::string& name, TString calibration);

//Private members
private:
  //Variables for configuration
  std::string m_jetAlgo;
  std::string m_config;
  std::string m_calibSeq;
  std::string m_calibAreaTag;
  bool m_devMode;
  bool m_isData;
  bool m_mass;
  std::string m_rhoKey;
  std::string m_dir;
  std::string m_eInfoName;

  //TEnv to hold the global text config
  TEnv * m_globalConfig;

  //Bools/enums to avoid string comparisons at run time
  jetScale m_jetScale;
  bool m_doJetArea;
  bool m_doResidual;
  bool m_doOrigin;
  bool m_doGSC;

  //Class objects for each calibration step
  std::vector<JetCalibrationToolBase*> m_calibClasses;
  JetPileupCorrection * m_jetPileupCorr;
  EtaJESCorrection * m_etaJESCorr;
  GlobalSequentialCorrection * m_globalSequentialCorr;
  InsituDataCorrection * m_insituDataCorr;
  JMSCorrection * m_jetMassCorr;

}; 

#endif //> !JETCALIBTOOLS_APPLYJETCALIBRATION_H
