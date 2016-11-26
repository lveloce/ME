///////////////////////// -*- C++ -*- /////////////////////////////
// METHelpers.h
// Header file for METHelpers functions
// Author: T.J.Khoo<khoo@cern.ch>
///////////////////////////////////////////////////////////////////
#ifndef METUTILITIES_MET_METHELPERS_H
#define METUTILITIES_MET_METHELPERS_H 1

namespace met {

  void addGhostMuonsToJets(const xAOD::MuonContainer& muons, xAOD::JetContainer& jets);

}

#endif
