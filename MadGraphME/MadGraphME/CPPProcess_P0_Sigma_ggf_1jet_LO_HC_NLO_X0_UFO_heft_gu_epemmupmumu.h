//==========================================================================
// This file has been automatically generated for C++ Standalone by
// MadGraph5_aMC@NLO v. 2.3.2.2, 2015-09-06
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#ifndef MG5_Sigma_HC_NLO_X0_UFO_heft_gu_epemmupmumu_H
#define MG5_Sigma_HC_NLO_X0_UFO_heft_gu_epemmupmumu_H

#include <complex> 
#include <vector> 

#include "Parameters_HC_NLO_X0_UFO_heft.h"

using namespace std; 

//==========================================================================
// A class for calculating the matrix elements for
// Process: g u > x0 u WEIGHTED=3 QNP=1 / t
// *   Decay: x0 > z > e+ e- mu+ mu- WEIGHTED=6 QNP=1
// Process: g c > x0 c WEIGHTED=3 QNP=1 / t
// *   Decay: x0 > z > e+ e- mu+ mu- WEIGHTED=6 QNP=1
// Process: g d > x0 d WEIGHTED=3 QNP=1 / t
// *   Decay: x0 > z > e+ e- mu+ mu- WEIGHTED=6 QNP=1
// Process: g s > x0 s WEIGHTED=3 QNP=1 / t
// *   Decay: x0 > z > e+ e- mu+ mu- WEIGHTED=6 QNP=1
// Process: g b > x0 b WEIGHTED=3 QNP=1 / t
// *   Decay: x0 > z > e+ e- mu+ mu- WEIGHTED=6 QNP=1
//--------------------------------------------------------------------------

class CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gu_epemmupmumu
{
  public:

    // Constructor.
    CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gu_epemmupmumu() {}

    // Initialize process.
    virtual void initProc(string param_card_name); 

    // Calculate flavour-independent parts of cross section.
    virtual void sigmaKin(); 

    // Evaluate sigmaHat(sHat).
    virtual double sigmaHat(); 

    // Info on the subprocess.
    virtual string name() const {return "g u > e+ e- mu+ mu- u (HC_NLO_X0_UFO_heft)";}

    virtual int code() const {return 0;}

    const vector<double> & getMasses() const {return mME;}

    // Get and set momenta for matrix element evaluation
    vector < double * > getMomenta(){return p;}
    void setMomenta(vector < double * > & momenta){p = momenta;}
    void setInitial(int inid1, int inid2){id1 = inid1; id2 = inid2;}

    // Get matrix element vector
    const double * getMatrixElements() const {return matrix_element;}

    // Constants for array limits
    static const int ninitial = 2; 
    static const int nexternal = 7; 
    static const int nprocesses = 2; 

  private:

    // Private functions to calculate the matrix element for all subprocesses
    // Calculate wavefunctions
    void calculate_wavefunctions(const int perm[], const int hel[]); 
    static const int nwavefuncs = 17; 
    std::complex<double> w[nwavefuncs][18]; 
    static const int namplitudes = 3; 
    std::complex<double> amp[namplitudes]; 
    double matrix_gu_x0u_no_t_xz_epemmupmum(); 

    // Store the matrix element value from sigmaKin
    double matrix_element[nprocesses]; 

    // Color flows, used when selecting color
    double * jamp2[nprocesses]; 

    // Pointer to the model parameters
    Parameters_HC_NLO_X0_UFO_heft * pars; 

    // vector with external particle masses
    vector<double> mME; 

    // vector with momenta (to be changed each event)
    vector < double * > p; 
    // Initial particle ids
    int id1, id2; 

}; 


#endif  // MG5_Sigma_HC_NLO_X0_UFO_heft_gu_epemmupmumu_H
