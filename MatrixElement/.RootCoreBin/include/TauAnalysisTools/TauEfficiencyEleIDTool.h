// Dear emacs, this is -*- c++ -*-
#ifndef TAUANALYSISTOOLS_TAUEFFICIENCYELEIDTOOL_H
#define TAUANALYSISTOOLS_TAUEFFICIENCYELEIDTOOL_H

/*
  author: Dirk Duschinger
  mail: dirk.duschinger@cern.ch
  documentation in: ../README.rst
                    or
                    https://svnweb.cern.ch/trac/atlasoff/browser/PhysicsAnalysis/TauID/TauAnalysisTools/tags/TauAnalysisTools-<tag>/README.rst
		    or
                    https://svnweb.cern.ch/trac/atlasoff/browser/PhysicsAnalysis/TauID/TauAnalysisTools/trunk/README.rst
*/

// Local include(s):
#include "CommonEfficiencyTool.h"

namespace TauAnalysisTools
{

class TauEfficiencyEleIDTool : public CommonEfficiencyTool
{

public:

  TauEfficiencyEleIDTool(std::string sName);

  virtual ~TauEfficiencyEleIDTool();

  CP::CorrectionCode getEfficiencyScaleFactor(const xAOD::TauJet& xTau,
      double& dEfficiencyScaleFactor);

  virtual StatusCode initialize();

private:
  void setupWorkingPointSubstrings();
  std::string convertIDToString(int iLevel) const;
  std::string convertEVetoToString(int iLevel) const;
  std::string convertOLRToString(int iLevel) const;

  // declaration of the working point
  std::string m_sWorkingPoint_1p;
  std::string m_sWorkingPoint_3p;

};
} // namespace TauAnalysisTools

#endif // TAUANALYSISTOOLS_TAUEFFICIENCYELEIDTOOL_H
