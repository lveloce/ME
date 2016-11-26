// Dear emacs, this is -*- c++ -*-
#ifndef XAODTRIGRINGER_VERSIONS_TRIGRINGERRINGSCONTAINER_V1_H
#define XAODTRIGRINGER_VERSIONS_TRIGRINGERRINGSCONTAINER_V1_H

// EDM include(s):
#include "AthContainers/DataVector.h"

// Local include(s):
#include "xAODTrigRinger/versions/TrigRingerRings_v1.h"

namespace xAOD {
   /// Define the TrigRingerRings container as a simple DataVector
   typedef DataVector< TrigRingerRings_v1 > TrigRingerRingsContainer_v1;
}
#endif
