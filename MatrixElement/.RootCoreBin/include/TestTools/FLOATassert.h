/**  functions & macros to test the difference between floats */
#ifndef TESTTOOLS_FLOATASSERT_H
#define TESTTOOLS_FLOATASSERT_H

#include <iostream>
#include <cassert>
#include <cfloat>
#include <cmath>

#undef NDEBUG

namespace Athena_test {
  inline
  bool floatEQ(float lhs, float rhs) {
    return fabs(lhs-rhs)<=FLT_EPSILON;
  }
  inline
  bool floatNEQ(float lhs, float rhs) {
    return fabs(lhs-rhs)>FLT_EPSILON;
  }

  inline
  bool isEqual (double x1, double x2, double thresh = 1e-6)
  {
    double den = std::abs(x1+x2);
    if (den < thresh) return true;
    if (std::abs (x1-x2) / den < thresh)
      return true;
    std::cout << "Match failure: " << x1 << " " << x2 << "\n";
    return false;
  }

}

#define FLOAT_NEQassert( LHS, RHS ) assert(Athena_test::floatNEQ(LHS, RHS));	
#define FLOAT_EQassert( LHS, RHS ) assert(Athena_test::floatEQ(LHS, RHS));	

#endif
