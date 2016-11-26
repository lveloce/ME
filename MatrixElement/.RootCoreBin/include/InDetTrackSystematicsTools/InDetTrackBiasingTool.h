// -*- c++ -*-
#pragma once

#include "InDetTrackSystematicsTools/IInDetTrackBiasingTool.h"
#include "AsgTools/AsgTool.h"
#include "PATInterfaces/CorrectionTool.h"
#include "InDetTrackSystematicsTools/InDetTrackSystematicsTool.h"
#include "xAODTracking/TrackParticleContainer.h"
#include <string>
#include <vector>

#include <TH2.h>

#include "TRandom3.h"

class TFile;

namespace InDet {

  /// @class InDetTrackBiasingTool
  /// This class biases tracks to emulate systematic distortions of the tracking geometry
  /// @author Pawel Bruckman (pawel.bruckman.de.renstrom@cern.ch)
  /// @author Felix Clark (michael.ryan.clark@cern.ch)

  class InDetTrackBiasingTool
    : public virtual IInDetTrackBiasingTool
    , public virtual InDetTrackSystematicsTool
    , public virtual CP::CorrectionTool< xAOD::TrackParticleContainer >
  {

    ASG_TOOL_CLASS( InDetTrackBiasingTool,
		    InDet::IInDetTrackBiasingTool )

    public:

    InDetTrackBiasingTool (const std::string& name);
    virtual ~InDetTrackBiasingTool();

    virtual StatusCode initialize() override;
    virtual void prepare() override {};
    virtual StatusCode finalize() override;

    /// Computes the tracks origin
    virtual CP::CorrectionCode applyCorrection(xAOD::TrackParticle& track) override;
    virtual CP::CorrectionCode correctedCopy( const xAOD::TrackParticle& in,
					      xAOD::TrackParticle*& out );
    virtual CP::CorrectionCode applyContainerCorrection( xAOD::TrackParticleContainer& cont );


    /// returns: whether the tool is affected by the systematic
    virtual bool isAffectedBySystematic( const CP::SystematicVariation& ) const;
    /// returns: list of systematics this tool can be affected by
    virtual CP::SystematicSet affectingSystematics() const;
    /// returns: list of recommended systematics to use with this tool
    virtual CP::SystematicSet recommendedSystematics() const;
    /// configure the tool to apply a given list of systematic variations
    virtual CP::SystematicCode applySystematicVariation( const CP::SystematicSet& );


  protected:

    float readHistogram(float fDefault, TH2* histogram, float phi, float eta) const;
    float readEtaHistogram(float fDefault, TH1* histogram, float eta) const;

    float m_biasD0 = 0.f;
    float m_biasZ0 = 0.f;
    float m_biasQoverPsagitta = 0.f;    

    TH2* m_biasD0Histogram = nullptr;
    TH2* m_biasZ0Histogram = nullptr;
    TH2* m_biasQoverPsagittaHistogram = nullptr;

  }; // class InDetTrackBiasingTool

} // namespace InDet
