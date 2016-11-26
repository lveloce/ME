// Dear emacs, this is -*- c++ -*-
// $Id: RingerRingsContainer_v1.h  $
#ifndef XAODTRIGRINGER_VERSIONS_TRIGRINGERRINGSCONTAINER_V2_H
#define XAODTRIGRINGER_VERSIONS_TRIGRINGERRINGSCONTAINER_V2_H

// EDM include(s):
#include "AthContainers/DataVector.h"

// Local include(s):
#include "xAODTrigRinger/versions/TrigRingerRings_v2.h"

namespace xAOD {
   /// Define the TrigRingerRings container as a simple DataVector
   typedef DataVector< TrigRingerRings_v2 > TrigRingerRingsContainer_v2;
}

#endif // XAODTRIGRINGER_VERSIONS_TRIGRINGERRINGSCONTAINER_V2_H
