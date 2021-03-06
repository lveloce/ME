// Dear emacs, this is -*- c++ -*-
// $Id$
#ifndef XAODTRACKING_VERTEXCONTAINERFWD_H
#define XAODTRACKING_VERTEXCONTAINERFWD_H

// This is a forward declaration for the latest vertex container type.

// EDM include(s):
#include "AthContainers/DataVector.h"

// Local include(s):
#include "xAODTracking/VertexFwd.h"

namespace xAOD {
   /// Provide a forward declaration for VertexContainer
   typedef DataVector< Vertex > VertexContainer;
}

#endif // XAODTRACKING_VERTEXCONTAINERFWD_H
