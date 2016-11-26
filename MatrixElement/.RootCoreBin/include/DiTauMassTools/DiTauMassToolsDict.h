#ifndef DITAUMASSTOOLS_DITAUMASSTOOLSDICT_H
#define DITAUMASSTOOLS_DITAUMASSTOOLSDICT_H


// Special handling for Eigen vectorization
#if defined(__GCCXML__) and not defined(EIGEN_DONT_VECTORIZE)
#define EIGEN_DONT_VECTORIZE
#endif

#include "DiTauMassTools/MissingMassTool.h"

#endif
