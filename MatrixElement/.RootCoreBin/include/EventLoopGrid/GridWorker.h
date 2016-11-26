#ifndef EVENT_LOOP_GRID_WORKER_H
#define EVENT_LOOP_GRID_WORKER_H

#include <string>

#include <TList.h>

#include "SampleHandler/MetaObject.h"
#include "EventLoop/Worker.h"
#include "EventLoop/Global.h"
#include "EventLoopGrid/PandaRootTools.h"

namespace EL
{
  class GridWorker : public Worker
  {

  public:

    void testInvariant() const;

    GridWorker(const SH::MetaObject *sample, 
	       TList *output,
	       const TList& bigOutputs,
	       const TList& algs, 
	       const std::string& location,
	       PandaRootTools& pandaTools);

    void run();


  private:

    const SH::MetaObject *m_meta;

    const std::string m_location;

    PandaRootTools m_pandaTools;

    ClassDef(EL::GridWorker, 1);
  };

}

#endif
