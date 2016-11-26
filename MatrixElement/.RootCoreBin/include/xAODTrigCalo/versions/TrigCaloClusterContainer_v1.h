// Dear emacs, this is -*- c++ -*-
// $Id: TrigCaloClusterContainer_v1.h 631117 2014-11-26 08:48:22Z gwatts $
#ifndef XAODTRIGCALO_VERSIONS_TRIGCALOCLUSTERCONTAINER_V1_H
#define XAODTRIGCALO_VERSIONS_TRIGCALOCLUSTERCONTAINER_V1_H

// EDM include(s):
#include "AthContainers/DataVector.h"

// Local include(s):
#include "xAODTrigCalo/versions/TrigCaloCluster_v1.h"

namespace xAOD {
   /// Define the trigger calorimeter cluster container as a simple DataVector
   typedef DataVector< TrigCaloCluster_v1 > TrigCaloClusterContainer_v1;
}

#endif // XAODTRIGCALO_VERSIONS_TRIGCALOCLUSTERCONTAINER_V1_H
