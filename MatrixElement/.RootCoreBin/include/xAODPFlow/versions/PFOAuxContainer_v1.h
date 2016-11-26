// Dear emacs, this is -*- c++ -*-
// $Id: PFOAuxContainer_v1.h 630853 2014-11-25 11:15:03Z mhodgkin $
#ifndef XAODPFLOW_VERSIONS_PFOAUXCONTAINER_V1_H
#define XAODPFLOW_VERSIONS_PFOAUXCONTAINER_V1_H

// System include(s):
#include "xAODPFlow/PFODefs.h"

// EDM include(s):
#include "xAODCore/AuxContainerBase.h"
#include "AthLinks/ElementLink.h"
#include "xAODPFlow/PFO.h"

namespace xAOD {


  /// Temporary container used until we have I/O for AuxStoreInternal
  ///
  /// This class is meant to serve as a temporary way to provide an auxiliary
  /// store with Athena I/O capabilities for the pfo EDM. Will be exchanged for
  /// a generic auxiliary container type (AuxStoreInternal) later on.
  ///
  /// @author Michel Janus <janus@cern.ch> and Mark Hodgkinson
  ///
  ///


  // let's try using a root class directly. 
  // (Can switch to float[4] if preferred)

  class PFOAuxContainer_v1 : public AuxContainerBase {

  public:
    /// Default constructor
    PFOAuxContainer_v1();
    ~PFOAuxContainer_v1() {};

  private:
    /** BDT Score used to classify clusters as Pi0 like or not */
    std::vector<float> bdtPi0Score;
    /** CenterMag moment needed to do vertex correction */
    std::vector<float> centerMag;
    /** Charge of PFO */
    std::vector<float> charge;
    /** 4-vector of PFO */
    std::vector<float> pt;
    std::vector<float> eta;
    std::vector<float> phi;
    std::vector<float> m;
    /** 4-vector of PFO at EM scale */
    std::vector<float> ptEM;
    std::vector<float> mEM;
    /** Vectors of links to constiuents - see PFODetails::PFOParticleType for valid types */
    std::vector<std::vector<ElementLink<IParticleContainer> > > pfo_ClusterLinks;
    std::vector<std::vector<ElementLink<IParticleContainer> > >  pfo_TrackLinks;
    std::vector<std::vector<ElementLink<IParticleContainer> > > pfo_TauShotLinks;

  }; // class PFOAuxContainer_v1

} // namespace xAOD

#ifndef XAOD_STANDALONE
#include "SGTools/BaseInfo.h"
SG_BASE( xAOD::PFOAuxContainer_v1, xAOD::AuxContainerBase );
#endif // not XAOD_STANDALONE

#endif // XAODPFLOW_VERSIONS_PFOAUXCONTAINER_V1_H
