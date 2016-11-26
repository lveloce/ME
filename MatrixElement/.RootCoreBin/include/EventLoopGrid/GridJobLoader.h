#ifndef GRID_JOB_LOADER_H
#define GRID_JOB_LOADER_H

#include <TROOT.h>

namespace EL {

  class GridJobLoader {

  public:

    GridJobLoader(){}

    virtual ~GridJobLoader(){}

    void Run(const std::string& sampleName);

    ClassDef(EL::GridJobLoader, 1);

  };
}

#endif
