// Dear emacs, this is -*- c++ -*-
// $Id: MuonStationIndex.h 594238 2014-04-25 09:00:53Z krasznaa $
#ifndef MUONIDHELPERS_MUONSTATIONINDEXHELPERS_H
#define MUONIDHELPERS_MUONSTATIONINDEXHELPERS_H

#include <vector>
#include "MuonIdHelpers/MuonStationIndex.h"

namespace Muon {
  class MuonStationIndexHelpers {
  public:

    /** get techonolgies in */
    static std::vector<MuonStationIndex::TechnologyIndex> technologiesInStation( MuonStationIndex::StIndex stIndex );

    /** returns whether a sector is small */
    static bool isSmall( int sector );
  };
}

#endif
