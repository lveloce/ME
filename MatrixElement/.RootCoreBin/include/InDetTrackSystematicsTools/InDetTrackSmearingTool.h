// Dear emacs, this is -*- c++ -*-
// $Id: InDetTrackSmearingTool.h 300810 2014-06-06 12:28:18Z krasznaa $
#pragma once

// Framework include(s):
#include "AsgTools/AsgTool.h"
#include "PATInterfaces/CorrectionTool.h"
#include "PATInterfaces/SystematicVariation.h"

//EDM include(s):
#include "xAODTracking/TrackParticleContainer.h"

// Local include(s):
#include "InDetTrackSystematicsTools/IInDetTrackSmearingTool.h"
#include "InDetTrackSystematicsTools/InDetTrackSystematicsTool.h"

#include <TFile.h>
#include <TH2F.h>
#include <TF2.h>
#include <TRandom3.h>

namespace InDet {

  class InDetTrackSmearingTool
    : public virtual IInDetTrackSmearingTool
    , public virtual InDetTrackSystematicsTool
    , public virtual CP::CorrectionTool< xAOD::TrackParticleContainer >
  {

    /// Create a proper constructor for Athena
    ASG_TOOL_CLASS( InDetTrackSmearingTool, 
		    InDet::IInDetTrackSmearingTool )
    public:
    /// Create a constructor for standalone usage
    InDetTrackSmearingTool( const std::string& name );
    virtual ~InDetTrackSmearingTool() = default;

    /// Function initialising the tool
    virtual StatusCode initialize();
    /// Function finalising the tool
    virtual StatusCode finalize();
    /// Smearing method
    virtual CP::CorrectionCode applyCorrection( xAOD::TrackParticle& ID );

    // we need explicit forwarding calls because CP::CorrectionTool does not have a pure interface
    // this isn't really elegant (ideally these would come automatically) but we'd need IInDetTrackSmearingTool
    //  to inherit from CP::CorrectionTool, which would make it not pure-virtual.
    // at least, forwarding calls are easy enough to read and understand.
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

  private:
    /// Get smearing widths to add to IPs
    float GetSmearD0Sigma(const xAOD::TrackParticle&);
    float GetSmearZ0Sigma(const xAOD::TrackParticle&);

    int m_seed = 0;
    std::unique_ptr<TRandom3> m_rnd; //!

    // StatusCode initHistogram(TH1*& histogram, std::string rootFileName, std::string histogramName) const;
    // StatusCode initFunction(TF2*& function, std::string rootFileName, std::string functionName) const;
    float readHistogram( TH2*, float pt, float eta ) const;
      
    // float readHistogram(TH1* histogram, float pt, float eta) const;
    // float readHistograms(std::vector<TH1 *> histogram, float pt, float eta) const;    
    // histograms for dead module smearing as a function of p
    TH1* m_smearD0Dead = nullptr;
    TH1* m_smearZ0Dead = nullptr;

    // for 20.7, we'll use histograms directly, instead of fit functions
    TH2* m_smearD0Loose = nullptr;
    TH2* m_smearZ0Loose = nullptr;
    TH2* m_smearD0Tight = nullptr;
    TH2* m_smearZ0Tight = nullptr;
     
  }; /// class InDetTrackSmearingTool

} /// namespace InDet
