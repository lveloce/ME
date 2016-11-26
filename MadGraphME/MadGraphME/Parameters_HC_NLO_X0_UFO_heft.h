//==========================================================================
// This file has been automatically generated for C++
// MadGraph5_aMC@NLO v. 2.3.2.2, 2015-09-06
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#ifndef Parameters_HC_NLO_X0_UFO_heft_H
#define Parameters_HC_NLO_X0_UFO_heft_H

#include <complex> 

#include "read_slha.h"
using namespace std; 

class Parameters_HC_NLO_X0_UFO_heft
{
  public:

    static Parameters_HC_NLO_X0_UFO_heft * getInstance(); 

    // Define "zero"
    double zero, ZERO; 
    // Model parameters independent of aS
    double mdl_WX0, mdl_WW, mdl_WZ, mdl_WT, mdl_ymtau, aS, mdl_Gf, aEWM1,
        mdl_MX0, mdl_MZ, mdl_MTA, mdl_MT, MU_R, mdl_kHdwI, mdl_kHdwR, mdl_kHdz,
        mdl_kHda, mdl_kAww, mdl_kHww, mdl_kAzz, mdl_kHzz, mdl_kAgg, mdl_kHgg,
        mdl_kAza, mdl_kHza, mdl_kAaa, mdl_kHaa, mdl_kAll, mdl_kHll, mdl_kSM,
        mdl_cosa, mdl_Lambda, mdl_CKM22, mdl_Ncol, mdl_CA, mdl_TF, mdl_CF,
        mdl_MZ__exp__2, mdl_MZ__exp__4, mdl_sqrt__2, mdl_MX0__exp__2,
        mdl_cosa__exp__2, mdl_sina, mdl_nb__2__exp__0_75, mdl_aEW, mdl_MW,
        mdl_sqrt__aEW, mdl_ee, mdl_MW__exp__2, mdl_sw2, mdl_cw, mdl_sqrt__sw2,
        mdl_sw, mdl_g1, mdl_gw, mdl_vev, mdl_vev__exp__2, mdl_lam, mdl_ytau,
        mdl_muH, mdl_AxialZUp, mdl_AxialZDown, mdl_VectorZUp, mdl_VectorZDown,
        mdl_VectorAUp, mdl_VectorADown, mdl_VectorWmDxU, mdl_AxialWmDxU,
        mdl_VectorWpUxD, mdl_AxialWpUxD, mdl_ee__exp__2, mdl_gAaa,
        mdl_cw__exp__2, mdl_gAza, mdl_gHaa, mdl_gHza, mdl_gw__exp__2,
        mdl_sw__exp__2;
    std::complex<double> mdl_complexi, mdl_kHdw, mdl_conjg__kHdw; 
    // Model parameters dependent on aS
    double mdl_sqrt__aS, G, mdl_G__exp__2, mdl_gAgg, mdl_gHgg; 
    // Model couplings independent of aS
    std::complex<double> GC_3, GC_21, GC_24, GC_3006a, GC_3006h2, GC_3007h1,
        GC_3006h1, GC_3007a, GC_3007h2, GC_3007h3;
    // Model couplings dependent on aS
    std::complex<double> GC_5, GC_4, GC_3002a, GC_3003a, GC_3002h, GC_3003h; 

    // Set parameters that are unchanged during the run
    void setIndependentParameters(SLHAReader& slha); 
    // Set couplings that are unchanged during the run
    void setIndependentCouplings(); 
    // Set parameters that are changed event by event
    void setDependentParameters(); 
    // Set couplings that are changed event by event
    void setDependentCouplings(); 
    // Set Mass 
    void set4lepMass(double m_m4l);
    // Set Width
    long double setWidth(double m_m4l);
    // Print parameters that are unchanged during the run
    void printIndependentParameters(); 
    // Print couplings that are unchanged during the run
    void printIndependentCouplings(); 
    // Print parameters that are changed event by event
    void printDependentParameters(); 
    // Print couplings that are changed event by event
    void printDependentCouplings(); 


  private:
    static Parameters_HC_NLO_X0_UFO_heft * instance; 
}; 

#endif  // Parameters_HC_NLO_X0_UFO_heft_H

