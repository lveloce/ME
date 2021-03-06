// Dear emacs, this is -*- c++ -*-
// $Id: CMXCPHitsAuxContainer_v1.h 687949 2015-08-06 15:48:49Z amazurov $
#ifndef XAODTRIGL1CALO_VERSIONS_CMXCPHITSAUXCONTAINER_V1_H
#define XAODTRIGL1CALO_VERSIONS_CMXCPHITSAUXCONTAINER_V1_H

// STL include(s):
#include <vector>
// System include(s):
#include <stdint.h>

// EDM include(s):
#include "xAODCore/AuxContainerBase.h"

namespace xAOD{

  /// Description of CMXCPHitsAuxContainer_v1
  ///
  /// @author John Morris <john.morris@cern.ch>
  ///
  /// $Revision: 687949 $
  /// $Date: 2015-08-06 17:48:49 +0200 (Thu, 06 Aug 2015) $

  class CMXCPHitsAuxContainer_v1 : public AuxContainerBase {
    public:
      /// Default constructor
      CMXCPHitsAuxContainer_v1();

    private:
      std::vector<uint8_t> crate;
      std::vector<uint8_t> cmx;
      std::vector<uint8_t> sourceComponent;
      std::vector<uint8_t> peak;
      std::vector<std::vector<uint32_t> > hitsVec0;
      std::vector<std::vector<uint32_t> > hitsVec1;
      std::vector<std::vector<uint32_t> > errorVec0;
      std::vector<std::vector<uint32_t> > errorVec1;

  }; // class CMXCPHitsAuxContainer_v2
} // namespace xAOD

SG_BASE( xAOD::CMXCPHitsAuxContainer_v1 , xAOD::AuxContainerBase );

#endif

