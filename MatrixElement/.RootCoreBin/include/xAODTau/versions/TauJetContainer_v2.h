// Dear emacs, this is -*- c++ -*-
// $Id: TauJetContainer_v2.h 631748 2014-11-28 09:58:13Z janus $
#ifndef XAODTAU_VERSIONS_TAUCONTAINER_V2_H
#define XAODTAU_VERSIONS_TAUCONTAINER_V2_H

// Core include(s):
#include "AthContainers/DataVector.h"

// Local include(s):
#include "xAODTau/versions/TauJet_v2.h"

namespace xAOD {
   /// The container is a simple typedef for now
   typedef DataVector< xAOD::TauJet_v2 > TauJetContainer_v2;
}

#endif // XAODTAU_VERSIONS_TAUCONTAINER_V2_H
