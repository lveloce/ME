// -*- c++ -*-
#pragma once

#include "AsgTools/IAsgTool.h"
#include "PATInterfaces/ISystematicsTool.h"
#include "xAODTracking/TrackParticle.h"
#include <string>

namespace InDet {

  class InDetTrackTruthOriginTool;

  /// @class InDetTrackTruthFilterTool
  /// This class selects tracks based on their truth origin
  /// @author Remi Zaidan (remi.zaidan@cern.ch)
  /// @author Felix Clark (michael.ryan.clark@cern.ch)

  class IInDetTrackTruthFilterTool
    : public virtual asg::IAsgTool
    , public virtual CP::ISystematicsTool
  {
      
  public:
    ASG_TOOL_INTERFACE( InDet::IInDetTrackTruthFilterTool )
	
    virtual StatusCode initialize() = 0;
    virtual void prepare() = 0; // not sure if/why this function is necessary - felix
    virtual StatusCode finalize() = 0;

    virtual bool accept(const xAOD::TrackParticle* track) const = 0;
    virtual bool selectTrack(const xAOD::TrackParticle* track) const __attribute__ ((deprecated("use accept(track) instead"))) = 0; // an old name for the above

      
    // implement the CP::ISystematicTool interface
      
    /// returns: whether the tool is affected by the systematic
    virtual bool isAffectedBySystematic( const CP::SystematicVariation& ) const = 0;
    /// returns: list of systematics this tool can be affected by
    virtual CP::SystematicSet affectingSystematics() const = 0;
    /// returns: list of recommended systematics to use with this tool
    virtual CP::SystematicSet recommendedSystematics() const = 0;
    /// configure the tool to apply a given list of systematic variations
    virtual CP::SystematicCode applySystematicVariation( const CP::SystematicSet& ) = 0;
      
      
  }; // class IInDetTrackTruthFilterTool

} // namespace InDet
