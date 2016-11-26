// Dear emacs, this is -*- c++ -*-
// $Id$
#ifndef XAODTAU_VERSIONS_TAUJETCALIBMAPPER_V1_H
#define XAODTAU_VERSIONS_TAUJETCALIBMAPPER_V1_H

// System include(s):
#include <iostream>
#include "xAODTau/TauDefs.h"
namespace xAOD {
struct TauJetCalibTypeMapper_v1 {
   bool getValue(TauJetParameters::TauCalibType type, std::string& stringName){
     switch (type){
     case TauJetParameters::JetSeed:
       stringName = "JetSeed";
       return true;
     case TauJetParameters::DetectorAxis:
       stringName = "DetectorAxis";
       return true;
     case TauJetParameters::IntermediateAxis:
       stringName = "IntermediateAxis";
       return true;
     case TauJetParameters::TauEnergyScale:
       stringName = "TauEnergyScale";
       return true;
     case TauJetParameters::TauEtaCalib:
       stringName = "TauEtaCalib";
       return true;
     case TauJetParameters::PanTauEFlowRecProto:
       stringName = "PanTauEFlowRecProto";
       return true;
     case TauJetParameters::PanTauEFlowRec:
       stringName = "PanTauEFlowRec";
       return true;
     case TauJetParameters::PanTauCellBasedProto:
       stringName = "PanTauCellBasedProto";
       return true;
     case TauJetParameters::PanTauCellBased:
       stringName = "PanTauCellBased";
       return true;              
     case TauJetParameters::TrigCaloOnly:
       stringName = "TrigCaloOnly";
       return true;
     }//switch
     return false;
   }//getValue

};

}

#endif
