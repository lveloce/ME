//==========================================================================
// This file has been automatically generated for C++ Standalone by
// MadGraph5_aMC@NLO v. 2.3.2.2, 2015-09-06
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#include "CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_uux_epemepemg.h"
#include "HelAmps_HC_NLO_X0_UFO_heft.h"

using namespace MG5_HC_NLO_X0_UFO_heft; 

//==========================================================================
// Class member functions for calculating the matrix elements for
// Process: u u~ > x0 g WEIGHTED=3 QNP=1 / t
// *   Decay: x0 > z > e+ e- e+ e- WEIGHTED=6 QNP=1
// Process: c c~ > x0 g WEIGHTED=3 QNP=1 / t
// *   Decay: x0 > z > e+ e- e+ e- WEIGHTED=6 QNP=1
// Process: d d~ > x0 g WEIGHTED=3 QNP=1 / t
// *   Decay: x0 > z > e+ e- e+ e- WEIGHTED=6 QNP=1
// Process: s s~ > x0 g WEIGHTED=3 QNP=1 / t
// *   Decay: x0 > z > e+ e- e+ e- WEIGHTED=6 QNP=1
// Process: b b~ > x0 g WEIGHTED=3 QNP=1 / t
// *   Decay: x0 > z > e+ e- e+ e- WEIGHTED=6 QNP=1
// Process: u u~ > x0 g WEIGHTED=3 QNP=1 / t
// *   Decay: x0 > z > mu+ mu- mu+ mu- WEIGHTED=6 QNP=1
// Process: c c~ > x0 g WEIGHTED=3 QNP=1 / t
// *   Decay: x0 > z > mu+ mu- mu+ mu- WEIGHTED=6 QNP=1
// Process: d d~ > x0 g WEIGHTED=3 QNP=1 / t
// *   Decay: x0 > z > mu+ mu- mu+ mu- WEIGHTED=6 QNP=1
// Process: s s~ > x0 g WEIGHTED=3 QNP=1 / t
// *   Decay: x0 > z > mu+ mu- mu+ mu- WEIGHTED=6 QNP=1
// Process: b b~ > x0 g WEIGHTED=3 QNP=1 / t
// *   Decay: x0 > z > mu+ mu- mu+ mu- WEIGHTED=6 QNP=1

//--------------------------------------------------------------------------
// Initialize process.

void CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_uux_epemepemg::initProc(string param_card_name) 
{
  // Instantiate the model class and set parameters that stay fixed during run
  //pars = Parameters_HC_NLO_X0_UFO_heft::getInstance(); 
  pars = new Parameters_HC_NLO_X0_UFO_heft();
  SLHAReader slha(param_card_name); 
  pars->setIndependentParameters(slha); 
  pars->setIndependentCouplings(); 
  pars->printIndependentParameters(); 
  pars->printIndependentCouplings(); 
  // Set external particle masses for this matrix element
  mME.push_back(pars->ZERO); 
  mME.push_back(pars->ZERO); 
  mME.push_back(pars->ZERO); 
  mME.push_back(pars->ZERO); 
  mME.push_back(pars->ZERO); 
  mME.push_back(pars->ZERO); 
  mME.push_back(pars->ZERO); 
  jamp2[0] = new double[1]; 
}

//--------------------------------------------------------------------------
// Evaluate |M|^2, part independent of incoming flavour.

void CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_uux_epemepemg::sigmaKin() 
{
  // Set the parameters which change event by event
  pars->setDependentParameters(); 
  pars->setDependentCouplings(); 
  static bool firsttime = true; 
  if (firsttime)
  {
    pars->printDependentParameters(); 
    pars->printDependentCouplings(); 
    firsttime = false; 
  }

  // Reset color flows
  for(int i = 0; i < 1; i++ )
    jamp2[0][i] = 0.; 

  // Local variables and constants
  const int ncomb = 128; 
  static bool goodhel[ncomb] = {ncomb * false}; 
  static int ntry = 0, sum_hel = 0, ngood = 0; 
  static int igood[ncomb]; 
  static int jhel; 
  std::complex<double> * * wfs; 
  double t[nprocesses]; 
  // Helicities for the process
  static const int helicities[ncomb][nexternal] = {{-1, -1, -1, -1, -1, -1,
      -1}, {-1, -1, -1, -1, -1, -1, 1}, {-1, -1, -1, -1, -1, 1, -1}, {-1, -1,
      -1, -1, -1, 1, 1}, {-1, -1, -1, -1, 1, -1, -1}, {-1, -1, -1, -1, 1, -1,
      1}, {-1, -1, -1, -1, 1, 1, -1}, {-1, -1, -1, -1, 1, 1, 1}, {-1, -1, -1,
      1, -1, -1, -1}, {-1, -1, -1, 1, -1, -1, 1}, {-1, -1, -1, 1, -1, 1, -1},
      {-1, -1, -1, 1, -1, 1, 1}, {-1, -1, -1, 1, 1, -1, -1}, {-1, -1, -1, 1, 1,
      -1, 1}, {-1, -1, -1, 1, 1, 1, -1}, {-1, -1, -1, 1, 1, 1, 1}, {-1, -1, 1,
      -1, -1, -1, -1}, {-1, -1, 1, -1, -1, -1, 1}, {-1, -1, 1, -1, -1, 1, -1},
      {-1, -1, 1, -1, -1, 1, 1}, {-1, -1, 1, -1, 1, -1, -1}, {-1, -1, 1, -1, 1,
      -1, 1}, {-1, -1, 1, -1, 1, 1, -1}, {-1, -1, 1, -1, 1, 1, 1}, {-1, -1, 1,
      1, -1, -1, -1}, {-1, -1, 1, 1, -1, -1, 1}, {-1, -1, 1, 1, -1, 1, -1},
      {-1, -1, 1, 1, -1, 1, 1}, {-1, -1, 1, 1, 1, -1, -1}, {-1, -1, 1, 1, 1,
      -1, 1}, {-1, -1, 1, 1, 1, 1, -1}, {-1, -1, 1, 1, 1, 1, 1}, {-1, 1, -1,
      -1, -1, -1, -1}, {-1, 1, -1, -1, -1, -1, 1}, {-1, 1, -1, -1, -1, 1, -1},
      {-1, 1, -1, -1, -1, 1, 1}, {-1, 1, -1, -1, 1, -1, -1}, {-1, 1, -1, -1, 1,
      -1, 1}, {-1, 1, -1, -1, 1, 1, -1}, {-1, 1, -1, -1, 1, 1, 1}, {-1, 1, -1,
      1, -1, -1, -1}, {-1, 1, -1, 1, -1, -1, 1}, {-1, 1, -1, 1, -1, 1, -1},
      {-1, 1, -1, 1, -1, 1, 1}, {-1, 1, -1, 1, 1, -1, -1}, {-1, 1, -1, 1, 1,
      -1, 1}, {-1, 1, -1, 1, 1, 1, -1}, {-1, 1, -1, 1, 1, 1, 1}, {-1, 1, 1, -1,
      -1, -1, -1}, {-1, 1, 1, -1, -1, -1, 1}, {-1, 1, 1, -1, -1, 1, -1}, {-1,
      1, 1, -1, -1, 1, 1}, {-1, 1, 1, -1, 1, -1, -1}, {-1, 1, 1, -1, 1, -1, 1},
      {-1, 1, 1, -1, 1, 1, -1}, {-1, 1, 1, -1, 1, 1, 1}, {-1, 1, 1, 1, -1, -1,
      -1}, {-1, 1, 1, 1, -1, -1, 1}, {-1, 1, 1, 1, -1, 1, -1}, {-1, 1, 1, 1,
      -1, 1, 1}, {-1, 1, 1, 1, 1, -1, -1}, {-1, 1, 1, 1, 1, -1, 1}, {-1, 1, 1,
      1, 1, 1, -1}, {-1, 1, 1, 1, 1, 1, 1}, {1, -1, -1, -1, -1, -1, -1}, {1,
      -1, -1, -1, -1, -1, 1}, {1, -1, -1, -1, -1, 1, -1}, {1, -1, -1, -1, -1,
      1, 1}, {1, -1, -1, -1, 1, -1, -1}, {1, -1, -1, -1, 1, -1, 1}, {1, -1, -1,
      -1, 1, 1, -1}, {1, -1, -1, -1, 1, 1, 1}, {1, -1, -1, 1, -1, -1, -1}, {1,
      -1, -1, 1, -1, -1, 1}, {1, -1, -1, 1, -1, 1, -1}, {1, -1, -1, 1, -1, 1,
      1}, {1, -1, -1, 1, 1, -1, -1}, {1, -1, -1, 1, 1, -1, 1}, {1, -1, -1, 1,
      1, 1, -1}, {1, -1, -1, 1, 1, 1, 1}, {1, -1, 1, -1, -1, -1, -1}, {1, -1,
      1, -1, -1, -1, 1}, {1, -1, 1, -1, -1, 1, -1}, {1, -1, 1, -1, -1, 1, 1},
      {1, -1, 1, -1, 1, -1, -1}, {1, -1, 1, -1, 1, -1, 1}, {1, -1, 1, -1, 1, 1,
      -1}, {1, -1, 1, -1, 1, 1, 1}, {1, -1, 1, 1, -1, -1, -1}, {1, -1, 1, 1,
      -1, -1, 1}, {1, -1, 1, 1, -1, 1, -1}, {1, -1, 1, 1, -1, 1, 1}, {1, -1, 1,
      1, 1, -1, -1}, {1, -1, 1, 1, 1, -1, 1}, {1, -1, 1, 1, 1, 1, -1}, {1, -1,
      1, 1, 1, 1, 1}, {1, 1, -1, -1, -1, -1, -1}, {1, 1, -1, -1, -1, -1, 1},
      {1, 1, -1, -1, -1, 1, -1}, {1, 1, -1, -1, -1, 1, 1}, {1, 1, -1, -1, 1,
      -1, -1}, {1, 1, -1, -1, 1, -1, 1}, {1, 1, -1, -1, 1, 1, -1}, {1, 1, -1,
      -1, 1, 1, 1}, {1, 1, -1, 1, -1, -1, -1}, {1, 1, -1, 1, -1, -1, 1}, {1, 1,
      -1, 1, -1, 1, -1}, {1, 1, -1, 1, -1, 1, 1}, {1, 1, -1, 1, 1, -1, -1}, {1,
      1, -1, 1, 1, -1, 1}, {1, 1, -1, 1, 1, 1, -1}, {1, 1, -1, 1, 1, 1, 1}, {1,
      1, 1, -1, -1, -1, -1}, {1, 1, 1, -1, -1, -1, 1}, {1, 1, 1, -1, -1, 1,
      -1}, {1, 1, 1, -1, -1, 1, 1}, {1, 1, 1, -1, 1, -1, -1}, {1, 1, 1, -1, 1,
      -1, 1}, {1, 1, 1, -1, 1, 1, -1}, {1, 1, 1, -1, 1, 1, 1}, {1, 1, 1, 1, -1,
      -1, -1}, {1, 1, 1, 1, -1, -1, 1}, {1, 1, 1, 1, -1, 1, -1}, {1, 1, 1, 1,
      -1, 1, 1}, {1, 1, 1, 1, 1, -1, -1}, {1, 1, 1, 1, 1, -1, 1}, {1, 1, 1, 1,
      1, 1, -1}, {1, 1, 1, 1, 1, 1, 1}};
  // Denominators: spins, colors and identical particles
  const int denominators[nprocesses] = {144, 144}; 

  ntry = ntry + 1; 

  // Reset the matrix elements
  for(int i = 0; i < nprocesses; i++ )
  {
    matrix_element[i] = 0.; 
  }
  // Define permutation
  int perm[nexternal]; 
  for(int i = 0; i < nexternal; i++ )
  {
    perm[i] = i; 
  }

  if (sum_hel == 0 || ntry < 10)
  {
    // Calculate the matrix element for all helicities
    for(int ihel = 0; ihel < ncomb; ihel++ )
    {
      if (goodhel[ihel] || ntry < 2)
      {
        calculate_wavefunctions(perm, helicities[ihel]); 
        t[0] = matrix_uux_x0g_no_t_xz_epemepem(); 
        // Mirror initial state momenta for mirror process
        perm[0] = 1; 
        perm[1] = 0; 
        // Calculate wavefunctions
        calculate_wavefunctions(perm, helicities[ihel]); 
        // Mirror back
        perm[0] = 0; 
        perm[1] = 1; 
        // Calculate matrix elements
        t[1] = matrix_uux_x0g_no_t_xz_epemepem(); 
        double tsum = 0; 
        for(int iproc = 0; iproc < nprocesses; iproc++ )
        {
          matrix_element[iproc] += t[iproc]; 
          tsum += t[iproc]; 
        }
        // Store which helicities give non-zero result
        if (tsum != 0. && !goodhel[ihel])
        {
          goodhel[ihel] = true; 
          ngood++; 
          igood[ngood] = ihel; 
        }
      }
    }
    jhel = 0; 
    sum_hel = min(sum_hel, ngood); 
  }
  else
  {
    // Only use the "good" helicities
    for(int j = 0; j < sum_hel; j++ )
    {
      jhel++; 
      if (jhel >= ngood)
        jhel = 0; 
      double hwgt = double(ngood)/double(sum_hel); 
      int ihel = igood[jhel]; 
      calculate_wavefunctions(perm, helicities[ihel]); 
      t[0] = matrix_uux_x0g_no_t_xz_epemepem(); 
      // Mirror initial state momenta for mirror process
      perm[0] = 1; 
      perm[1] = 0; 
      // Calculate wavefunctions
      calculate_wavefunctions(perm, helicities[ihel]); 
      // Mirror back
      perm[0] = 0; 
      perm[1] = 1; 
      // Calculate matrix elements
      t[1] = matrix_uux_x0g_no_t_xz_epemepem(); 
      for(int iproc = 0; iproc < nprocesses; iproc++ )
      {
        matrix_element[iproc] += t[iproc] * hwgt; 
      }
    }
  }

  for (int i = 0; i < nprocesses; i++ )
    matrix_element[i] /= denominators[i]; 



}

//--------------------------------------------------------------------------
// Evaluate |M|^2, including incoming flavour dependence.

double CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_uux_epemepemg::sigmaHat() 
{
  // Select between the different processes
  if(id1 == 3 && id2 == -3)
  {
    // Add matrix elements for processes with beams (3, -3)
    return matrix_element[0] * 2; 
  }
  else if(id1 == -1 && id2 == 1)
  {
    // Add matrix elements for processes with beams (-1, 1)
    return matrix_element[1] * 2; 
  }
  else if(id1 == 4 && id2 == -4)
  {
    // Add matrix elements for processes with beams (4, -4)
    return matrix_element[0] * 2; 
  }
  else if(id1 == -3 && id2 == 3)
  {
    // Add matrix elements for processes with beams (-3, 3)
    return matrix_element[1] * 2; 
  }
  else if(id1 == 2 && id2 == -2)
  {
    // Add matrix elements for processes with beams (2, -2)
    return matrix_element[0] * 2; 
  }
  else if(id1 == -5 && id2 == 5)
  {
    // Add matrix elements for processes with beams (-5, 5)
    return matrix_element[1] * 2; 
  }
  else if(id1 == -4 && id2 == 4)
  {
    // Add matrix elements for processes with beams (-4, 4)
    return matrix_element[1] * 2; 
  }
  else if(id1 == -2 && id2 == 2)
  {
    // Add matrix elements for processes with beams (-2, 2)
    return matrix_element[1] * 2; 
  }
  else if(id1 == 5 && id2 == -5)
  {
    // Add matrix elements for processes with beams (5, -5)
    return matrix_element[0] * 2; 
  }
  else if(id1 == 1 && id2 == -1)
  {
    // Add matrix elements for processes with beams (1, -1)
    return matrix_element[0] * 2; 
  }
  else
  {
    // Return 0 if not correct initial state assignment
    return 0.; 
  }
}

//==========================================================================
// Private class member functions

//--------------------------------------------------------------------------
// Evaluate |M|^2 for each subprocess

void CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_uux_epemepemg::calculate_wavefunctions(const int perm[], const int hel[])
{
  // Calculate wavefunctions for all processes
  int i, j; 

  // Calculate all wavefunctions
  ixxxxx(p[perm[0]], mME[0], hel[0], +1, w[0]); 
  oxxxxx(p[perm[1]], mME[1], hel[1], -1, w[1]); 
  ixxxxx(p[perm[2]], mME[2], hel[2], -1, w[2]); 
  oxxxxx(p[perm[3]], mME[3], hel[3], +1, w[3]); 
  ixxxxx(p[perm[4]], mME[4], hel[4], -1, w[4]); 
  oxxxxx(p[perm[5]], mME[5], hel[5], +1, w[5]); 
  FFV1P0_3(w[2], w[3], pars->GC_3, pars->ZERO, pars->ZERO, w[6]); 
  FFV2_4_3(w[4], w[5], pars->GC_21, pars->GC_24, pars->mdl_MZ, pars->mdl_WZ,
      w[7]);
  VVS10_11_2_3(w[6], w[7], pars->GC_3006a, pars->GC_3006h1, pars->GC_3006h2,
      pars->mdl_MX0, pars->mdl_WX0, w[8]);
  vxxxxx(p[perm[6]], mME[6], hel[6], +1, w[9]); 
  VVS2_10P0_1(w[9], w[8], pars->GC_3002h, pars->GC_3002a, pars->ZERO,
      pars->ZERO, w[10]);
  FFV2_4_3(w[2], w[3], pars->GC_21, pars->GC_24, pars->mdl_MZ, pars->mdl_WZ,
      w[11]);
  FFV1P0_3(w[4], w[5], pars->GC_3, pars->ZERO, pars->ZERO, w[12]); 
  VVS10_11_2_3(w[12], w[11], pars->GC_3006a, pars->GC_3006h1, pars->GC_3006h2,
      pars->mdl_MX0, pars->mdl_WX0, w[13]);
  VVS2_10P0_1(w[9], w[13], pars->GC_3002h, pars->GC_3002a, pars->ZERO,
      pars->ZERO, w[14]);
  VVS10_1_2_13_3(w[11], w[7], pars->GC_3007a, pars->GC_3007h1, pars->GC_3007h2,
      pars->GC_3007h3, pars->mdl_MX0, pars->mdl_WX0, w[15]);
  VVS2_10P0_1(w[9], w[15], pars->GC_3002h, pars->GC_3002a, pars->ZERO,
      pars->ZERO, w[16]);
  FFV1P0_3(w[2], w[5], pars->GC_3, pars->ZERO, pars->ZERO, w[17]); 
  FFV2_4_3(w[4], w[3], pars->GC_21, pars->GC_24, pars->mdl_MZ, pars->mdl_WZ,
      w[18]);
  VVS10_11_2_3(w[17], w[18], pars->GC_3006a, pars->GC_3006h1, pars->GC_3006h2,
      pars->mdl_MX0, pars->mdl_WX0, w[19]);
  VVS2_10P0_1(w[9], w[19], pars->GC_3002h, pars->GC_3002a, pars->ZERO,
      pars->ZERO, w[20]);
  FFV2_4_3(w[2], w[5], pars->GC_21, pars->GC_24, pars->mdl_MZ, pars->mdl_WZ,
      w[21]);
  FFV1P0_3(w[4], w[3], pars->GC_3, pars->ZERO, pars->ZERO, w[22]); 
  VVS10_11_2_3(w[22], w[21], pars->GC_3006a, pars->GC_3006h1, pars->GC_3006h2,
      pars->mdl_MX0, pars->mdl_WX0, w[23]);
  VVS2_10P0_1(w[9], w[23], pars->GC_3002h, pars->GC_3002a, pars->ZERO,
      pars->ZERO, w[24]);
  VVS10_1_2_13_3(w[21], w[18], pars->GC_3007a, pars->GC_3007h1,
      pars->GC_3007h2, pars->GC_3007h3, pars->mdl_MX0, pars->mdl_WX0, w[25]);
  VVS2_10P0_1(w[9], w[25], pars->GC_3002h, pars->GC_3002a, pars->ZERO,
      pars->ZERO, w[26]);

  // Calculate all amplitudes
  // Amplitude(s) for diagram number 0
  FFV1_0(w[0], w[1], w[10], pars->GC_5, amp[0]); 
  FFV1_0(w[0], w[1], w[14], pars->GC_5, amp[1]); 
  FFV1_0(w[0], w[1], w[16], pars->GC_5, amp[2]); 
  FFV1_0(w[0], w[1], w[20], pars->GC_5, amp[3]); 
  FFV1_0(w[0], w[1], w[24], pars->GC_5, amp[4]); 
  FFV1_0(w[0], w[1], w[26], pars->GC_5, amp[5]); 

}
double CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_uux_epemepemg::matrix_uux_x0g_no_t_xz_epemepem() 
{
  int i, j; 
  // Local variables
  const int ngraphs = 6; 
  const int ncolor = 1; 
  std::complex<double> ztemp; 
  std::complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1}; 
  static const double cf[ncolor][ncolor] = {{4}}; 

  // Calculate color flows
  jamp[0] = +amp[0] + amp[1] + amp[2] - amp[3] - amp[4] - amp[5]; 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[0][i] += real(jamp[i] * conj(jamp[i])); 

  return matrix; 
}



