// Dear emacs, this is -*- c++ -*-
// $Id: ElectronxAODHelpers.h 673480 2015-06-08 18:14:25Z christos $
#ifndef XAOD_ELECTRONXAODHELPERS_H
#define XAOD_ELECTRONXAODHELPERS_H

#include "xAODEgamma/ElectronFwd.h"
#include "xAODTracking/TrackParticleFwd.h"
#include <cstddef>
#include <set>
#include <vector>

namespace xAOD {

  namespace EgammaHelpers{

    ///@brief Helper function for getting the "Original" Track Particle (i.e before GSF) via the electron
    const xAOD::TrackParticle* getOriginalTrackParticle(const xAOD::Electron* el);

    ///@brief Helper function for getting the "Original" Track Particle (i.e before GSF) via the GSF Track Particle
    const xAOD::TrackParticle* getOriginalTrackParticleFromGSF(const xAOD::TrackParticle* trkPar);

    ///@Brief return parameters for the last measurement for a GSF track particle
    float getLastMeasurementQoverP(const xAOD::TrackParticle *tp);

    ///@brief Return a list of all or only the best TrackParticle associated to the object. 
    ///If useBremAssoc is set, get the original TrackParticle 
    ///This is useful when a std::set of the original track Particles is required, which is mainly the case for the 
    //isolation interface,
    ///as it will re-order the elements in pointer order and not best match.
    const std::set<const xAOD::TrackParticle*> getTrackParticles(const xAOD::Electron* el,
								 bool useBremAssoc = true, bool allParticles = true);


    ///@brief Return a list of all or only the best TrackParticle associated to the object. 
    ///If useBremAssoc is set, get the original TrackParticle 
    ///This one returns a vector so as to be more "user friendly",as it retains the original
    ///best match ordering
    const std::vector<const xAOD::TrackParticle*> getTrackParticlesVec(const xAOD::Electron* el,
								       bool useBremAssoc = true, bool allParticles = true);

    
    ///@brief return the number of Si hits in the track particle
    std::size_t numberOfSiHits(const xAOD::TrackParticle *tp);
    
  } //namaspace EgammaHelpers

} // namespace xAOD

#endif // XAOD_ELECTRONXAODHELPERS_H
