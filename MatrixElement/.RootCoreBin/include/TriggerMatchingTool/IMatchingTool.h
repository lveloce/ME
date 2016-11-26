// Dear emacs, this is -*- c++ -*-
#ifndef IMATCHINGTOOL_H
#define IMATCHINGTOOL_H


// Framework include(s):
#include "AsgTools/IAsgTool.h"

namespace xAOD{
  class IParticle;
}



namespace Trig {

class MatchingImplementation;

class IMatchingTool : virtual public asg::IAsgTool {
  ASG_TOOL_INTERFACE(IMatchingTool)
public:

  ///single object trigger matching. matchThreshold is typically the deltaR requirement to obtain positive matching
  virtual bool match(const xAOD::IParticle& recoObject, const std::string& chain, double matchThreshold=0.1) = 0;
  ///multi-object trigger matching
  virtual bool match(const std::vector<const xAOD::IParticle*>& recoObjects, const std::string& chain, double matchThreshold=0.1) = 0;

protected:
  virtual MatchingImplementation* impl() = 0;
};

}

#endif
