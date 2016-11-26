// Dear emacs, this is -*-c++-*-

#ifndef __ASGELECTRONMULTILEPTONSELECTOR__
#define __ASGELECTRONMULTILEPTONSELECTOR__

/**
   @class AsgElectronMultiLeptonSelector
   @brief Tool to select electrons

   @author Karsten Koeneke
   @date   October 2012

   12-MAR-2014, convert to ASGTool (Jovan Mitrevski)

*/

// Atlas includes
#include "AsgTools/AsgTool.h"
#include "ElectronPhotonSelectorTools/IAsgElectronMultiLeptonSelector.h"

// Include the return object and ROOT tool
#include "PATCore/TAccept.h"
#include "ElectronPhotonSelectorTools/TElectronMultiLeptonSelector.h"


class AsgElectronMultiLeptonSelector : public asg::AsgTool,
	    virtual public IAsgElectronMultiLeptonSelector
{
  ASG_TOOL_CLASS2(AsgElectronMultiLeptonSelector, IAsgElectronMultiLeptonSelector,
		  IAsgSelectionTool)

public: 
  /** Standard constructor */
  AsgElectronMultiLeptonSelector(std::string myname);


  /** Standard destructor */
  virtual ~AsgElectronMultiLeptonSelector();


public:
  /** Gaudi Service Interface method implementations */
  virtual StatusCode initialize();

  /** Gaudi Service Interface method implementations */
  virtual StatusCode finalize();

  // Main methods for IAsgSelectionTool interface

  /** The main accept method: the actual cuts are applied here */
  const Root::TAccept& accept( const xAOD::IParticle* part ) const;

  /** The main accept method: the actual cuts are applied here */
  const Root::TAccept& accept( const xAOD::Electron* eg ) const;

  /** Accept using reference **/
  virtual const Root::TAccept& accept( const xAOD::Electron& part ) const {
    return accept (&part);
  }

  /** Accept using reference **/
  virtual const Root::TAccept& accept( const xAOD::IParticle& part ) const {
    return accept (&part);
  }

  /** Method to get the plain TAccept */
  inline virtual const Root::TAccept& getTAccept( ) const
  {
    return m_rootTool->getTAccept();
  }

  /** Method to get the operating point */
  virtual std::string getOperatingPointName( ) const;


  // Private member variables
private:
  /** Pointer to the underlying ROOT based tool */
  Root::TElectronMultiLeptonSelector* m_rootTool;
  
  /** A dummy return TAccept object */
  Root::TAccept m_acceptDummy;

}; // End: class definition






#endif

