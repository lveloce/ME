// Dear emacs, this is -*- c++ -*-
#ifndef TAUANALYSISTOOLS_TAUCONVERSIONTOOL_H
#define TAUANALYSISTOOLS_TAUCONVERSIONTOOL_H
#ifdef XAODTAU_VERSIONS_TAUJET_V3_H

/*
  author: Justin Griffiths
  mail: justin.griffiths@cern.ch
  documentation in: ../README.rst
  or
  https://svnweb.cern.ch/trac/atlasoff/browser/PhysicsAnalysis/TauID/TauAnalysisTools/tags/TauAnalysisTools-<tag>/README.rst
  or
  https://svnweb.cern.ch/trac/atlasoff/browser/PhysicsAnalysis/TauID/TauAnalysisTools/trunk/README.rst

  Perhaps documentation is not in above.  This simply converts TauJet_v2-->TauJet_v3.
  Produced Taus are stored in StoreGate/TStore

  use like this:
  //in event loop
  xAOD::TauJetContainer* tauCont=0;
  tool->retrieveTaus(tauCont);


*/

// Framework include(s):
#include "AsgTools/AsgTool.h"

//local include(s):
#include "TauAnalysisTools/ITauConversionTool.h"

//EDM include(s):
#include "xAODTau/versions/TauJet_v2.h"
#include "xAODTau/TauJet.h"
#include "xAODTau/TauTrackContainer.h"

//system
#include <string>

namespace TauAnalysisTools
{

class TauConversionTool
  : public asg::AsgTool
  , public virtual ITauConversionTool
{
  /// Create a proper constructor for Athena
  ASG_TOOL_CLASS( TauConversionTool, TauAnalysisTools::ITauConversionTool )

public:
  /// Create a constructor for standalone usage
  TauConversionTool( const std::string& sName );

  ~TauConversionTool();

  /// Function initialising the tool
  virtual StatusCode initialize();

  virtual StatusCode retrieveTaus(xAOD::TauJetContainer* &taus);
  virtual StatusCode copyTau(xAOD::TauJet*, const xAOD::TauJet_v2*, xAOD::TauTrackContainer*);

private:

  std::string m_inputTauContainerName;
  std::string m_outputTauContainerName;
  std::string m_outputTauTrackContainerName;
  bool m_storeInStoreGate;

}; // class TauConversionTool

} // namespace TauAnalysisTools

#endif // XAODTAU_VERSIONS_TAUJET_V3_H
#endif // TAUANALYSISTOOLS_TAUCONVERSIONTOOL_H
