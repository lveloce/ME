#ifndef PILEUPREWEIGHTINGDICT_H
#define PILEUPREWEIGHTINGDICT_H

#include "PileupReweighting/PileupReweightingTool.h"
#include "PileupReweighting/IPileupReweightingTool.h"

#ifdef XAOD_ANALYSIS
#include "AsgTools/AnaToolHandle.h"
namespace {
   struct GCCXML_DUMMY_INSTATIATION {
      asg::AnaToolHandle<CP::IPileupReweightingTool> t;
   };
}
#endif


#endif 
