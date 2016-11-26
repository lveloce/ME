// Dear emacs, this is -*- c++ -*-
#ifndef XAODTRIGRINGER_VERSIONS_TRIGRNNOUTPUTCONTAINER_V2_H
#define XAODTRIGRINGER_VERSIONS_TRIGRNNOUTPUTCONTAINER_V2_H

// EDM include(s):
#include "AthContainers/DataVector.h"

// Local include(s):
#include "xAODTrigRinger/versions/TrigRNNOutput_v2.h"

namespace xAOD {
   /// Define the RingerRings container as a simple DataVector
   typedef DataVector< TrigRNNOutput_v2 > TrigRNNOutputContainer_v2;
}

#endif // XAODTRIGRINGER_VERSIONS_TRIGRNNOUTPUTCONTAINER_V2_H
