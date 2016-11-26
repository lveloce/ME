//==========================================================================
// This file has been automatically generated for C++ Standalone by
// MadGraph5_aMC@NLO v. 2.3.3, 2015-10-25
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#ifndef MG5_Sigma_HC_NLO_X0_UFO_udx_udxepemmupmum_H
#define MG5_Sigma_HC_NLO_X0_UFO_udx_udxepemmupmum_H

#include <complex> 
#include <vector> 

#include "Parameters_HC_NLO_X0_UFO_VH.h"

using namespace std; 

//==========================================================================
// A class for calculating the matrix elements for
// Process: u d~ > w+ x0 WEIGHTED=4 QNP=1 @1
// *   Decay: w+ > u d~ WEIGHTED=2 QNP=1
// *   Decay: x0 > e+ e- mu+ mu- WEIGHTED=6 QNP=1
// Process: c s~ > w+ x0 WEIGHTED=4 QNP=1 @1
// *   Decay: w+ > u d~ WEIGHTED=2 QNP=1
// *   Decay: x0 > e+ e- mu+ mu- WEIGHTED=6 QNP=1
// Process: u d~ > w+ x0 WEIGHTED=4 QNP=1 @1
// *   Decay: w+ > c s~ WEIGHTED=2 QNP=1
// *   Decay: x0 > e+ e- mu+ mu- WEIGHTED=6 QNP=1
// Process: c s~ > w+ x0 WEIGHTED=4 QNP=1 @1
// *   Decay: w+ > c s~ WEIGHTED=2 QNP=1
// *   Decay: x0 > e+ e- mu+ mu- WEIGHTED=6 QNP=1
//--------------------------------------------------------------------------

class CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum
{
  public:

    // Constructor.
    CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum() {}

    // se the 4l mass
    void setM4l(double m_m4l);

    // Initialize process.
    virtual void initProc(string param_card_name); 

    // Calculate flavour-independent parts of cross section.
    virtual void sigmaKin(); 

    // Evaluate sigmaHat(sHat).
    virtual double sigmaHat(); 

    // Info on the subprocess.
    virtual string name() const {return "u d~ > u d~ e+ e- mu+ mu- (HC_NLO_X0_UFO)";}

    virtual int code() const {return 1;}

    const vector<double> & getMasses() const {return mME;}

    // Get and set momenta for matrix element evaluation
    vector < double * > getMomenta(){return p;}
    void setMomenta(vector < double * > & momenta){p = momenta;}
    void setInitial(int inid1, int inid2){id1 = inid1; id2 = inid2;}

    // Get matrix element vector
    const double * getMatrixElements() const {return matrix_element;}

    // Constants for array limits
    static const int ninitial = 2; 
    static const int nexternal = 8; 
    static const int nprocesses = 2; 

  private:

    // Private functions to calculate the matrix element for all subprocesses
    // Calculate wavefunctions
    void calculate_wavefunctions(const int perm[], const int hel[]); 
    static const int nwavefuncs = 18; 
    std::complex<double> w[nwavefuncs][18]; 
    static const int namplitudes = 4; 
    std::complex<double> amp[namplitudes]; 
    double matrix_1_udx_wpxwp_udx_xepemmupmum(); 

    // Store the matrix element value from sigmaKin
    double matrix_element[nprocesses]; 

    // Color flows, used when selecting color
    double * jamp2[nprocesses]; 

    // Pointer to the model parameters
    Parameters_HC_NLO_X0_UFO_VH * pars; 

    // vector with external particle masses
    vector<double> mME; 

    // vector with momenta (to be changed each event)
    vector < double * > p; 
    // Initial particle ids
    int id1, id2; 

}; 


#endif  // MG5_Sigma_HC_NLO_X0_UFO_udx_udxepemmupmum_H
