// Dear emacs, this is -*- c++ -*-
#ifndef TAUANALYSISTOOLS_ITAUCONVERSIONTOOL_H
#define TAUANALYSISTOOLS_ITAUCONVERSIONTOOL_H
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
#include "AsgTools/IAsgTool.h"

// EDM include(s):
#include "xAODTau/TauJet.h"
#include "xAODTau/versions/TauJet_v2.h"
#include "xAODTau/TauTrackContainer.h"
#include "xAODTau/TauJetContainer.h"

namespace TauAnalysisTools
{

class ITauConversionTool
  : public virtual asg::IAsgTool
{

  /// Declare the interface that the class provides
  ASG_TOOL_INTERFACE( TauAnalysisTools::ITauConversionTool )

public:

  /// Apply the correction on a modifyable object
  virtual StatusCode retrieveTaus(xAOD::TauJetContainer* &taus)=0;
  virtual StatusCode copyTau(xAOD::TauJet*, const xAOD::TauJet_v2*, xAOD::TauTrackContainer*)=0;

}; // class ITauConversionTool

} // namespace TauAnalysisTools

#endif // XAODTAU_VERSIONS_TAUJET_V3_H
#endif // TAUANALYSISTOOLS_ITAUCONVERSIONTOOL_H
