// Dear emacs, this is -*- c++ -*-
#ifndef XAODTRIGRINGER_VERSIONS_TRIGRNNOUTPUTCONTAINER_V1_H
#define XAODTRIGRINGER_VERSIONS_TRIGRNNOUTPUTCONTAINER_V1_H

// EDM include(s):
#include "AthContainers/DataVector.h"

// Local include(s):
#include "xAODTrigRinger/versions/TrigRNNOutput_v1.h"

namespace xAOD {
   /// Define the RingerRings container as a simple DataVector
   typedef DataVector< TrigRNNOutput_v1 > TrigRNNOutputContainer_v1;
}


#endif // XAODTRIGRINGER_VERSIONS_TRIGRNNOUTPUTCONTAINER_V1_H
