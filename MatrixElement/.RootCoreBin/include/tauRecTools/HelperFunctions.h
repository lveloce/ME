#ifndef TAURECTOOLS_HELPERFUNCTIONS_H
#define TAURECTOOLS_HELPERFUNCTIONS_H

#include <vector>

// ROOT include(s)
#include "TLorentzVector.h"

// EDM include(s):
#include "xAODTau/TauJet.h"

namespace tauRecTools
{

void createPi0Vectors(const xAOD::TauJet* xTau, std::vector<TLorentzVector>& vPi0s);

}

#endif // not TAUANALYSISTOOLS_HELPERFUNCTIONS_H
