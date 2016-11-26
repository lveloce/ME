//==========================================================================
// This file has been automatically generated for C++ Standalone by
// MadGraph5_aMC@NLO v. 2.3.2.2, 2015-09-06
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#include "CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg.h"
#include "HelAmps_HC_NLO_X0_UFO_heft.h"

using namespace MG5_HC_NLO_X0_UFO_heft; 

//==========================================================================
// Class member functions for calculating the matrix elements for
// Process: g g > x0 g WEIGHTED=3 QNP=1 / t
// *   Decay: x0 > z > e+ e- e+ e- WEIGHTED=6 QNP=1
// Process: g g > x0 g WEIGHTED=3 QNP=1 / t
// *   Decay: x0 > z > mu+ mu- mu+ mu- WEIGHTED=6 QNP=1

//--------------------------------------------------------------------------
// Initialize process.

void CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg::initProc(string param_card_name) 
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
  jamp2[0] = new double[2]; 
}

//--------------------------------------------------------------------------
// Set M4l Mass

void CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg::setM4l(double m_m4l){
   //Adujst Parameters_sm to include new function if you wish to use m4l as mH, following Parameters_heft
  pars->set4lepMass(m_m4l);
}

//--------------------------------------------------------------------------
// Evaluate |M|^2, part independent of incoming flavour.

void CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg::sigmaKin() 
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
  for(int i = 0; i < 2; i++ )
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
  const int denominators[nprocesses] = {1024}; 

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
        t[0] = matrix_gg_x0g_no_t_xz_epemepem(); 

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
      t[0] = matrix_gg_x0g_no_t_xz_epemepem(); 

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

double CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg::sigmaHat() 
{
  // Select between the different processes
  if(id1 == 21 && id2 == 21)
  {
    // Add matrix elements for processes with beams (21, 21)
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

void CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg::calculate_wavefunctions(const int perm[], const int hel[])
{
  // Calculate wavefunctions for all processes
  int i, j; 

  // Calculate all wavefunctions
  vxxxxx(p[perm[0]], mME[0], hel[0], -1, w[0]); 
  vxxxxx(p[perm[1]], mME[1], hel[1], -1, w[1]); 
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
  FFV2_4_3(w[2], w[3], pars->GC_21, pars->GC_24, pars->mdl_MZ, pars->mdl_WZ,
      w[10]);
  FFV1P0_3(w[4], w[5], pars->GC_3, pars->ZERO, pars->ZERO, w[11]); 
  VVS10_11_2_3(w[11], w[10], pars->GC_3006a, pars->GC_3006h1, pars->GC_3006h2,
      pars->mdl_MX0, pars->mdl_WX0, w[12]);
  VVS10_1_2_13_3(w[10], w[7], pars->GC_3007a, pars->GC_3007h1, pars->GC_3007h2,
      pars->GC_3007h3, pars->mdl_MX0, pars->mdl_WX0, w[13]);
  FFV1P0_3(w[2], w[5], pars->GC_3, pars->ZERO, pars->ZERO, w[14]); 
  FFV2_4_3(w[4], w[3], pars->GC_21, pars->GC_24, pars->mdl_MZ, pars->mdl_WZ,
      w[15]);
  VVS10_11_2_3(w[14], w[15], pars->GC_3006a, pars->GC_3006h1, pars->GC_3006h2,
      pars->mdl_MX0, pars->mdl_WX0, w[16]);
  FFV2_4_3(w[2], w[5], pars->GC_21, pars->GC_24, pars->mdl_MZ, pars->mdl_WZ,
      w[17]);
  FFV1P0_3(w[4], w[3], pars->GC_3, pars->ZERO, pars->ZERO, w[18]); 
  VVS10_11_2_3(w[18], w[17], pars->GC_3006a, pars->GC_3006h1, pars->GC_3006h2,
      pars->mdl_MX0, pars->mdl_WX0, w[19]);
  VVS10_1_2_13_3(w[17], w[15], pars->GC_3007a, pars->GC_3007h1,
      pars->GC_3007h2, pars->GC_3007h3, pars->mdl_MX0, pars->mdl_WX0, w[20]);
  VVV1P0_1(w[0], w[1], pars->GC_4, pars->ZERO, pars->ZERO, w[21]); 
  VVS2_10P0_1(w[0], w[8], pars->GC_3002h, pars->GC_3002a, pars->ZERO,
      pars->ZERO, w[22]);
  VVS2_10P0_1(w[0], w[12], pars->GC_3002h, pars->GC_3002a, pars->ZERO,
      pars->ZERO, w[23]);
  VVS2_10P0_1(w[0], w[13], pars->GC_3002h, pars->GC_3002a, pars->ZERO,
      pars->ZERO, w[24]);
  VVS2_10P0_1(w[0], w[16], pars->GC_3002h, pars->GC_3002a, pars->ZERO,
      pars->ZERO, w[25]);
  VVS2_10P0_1(w[0], w[19], pars->GC_3002h, pars->GC_3002a, pars->ZERO,
      pars->ZERO, w[26]);
  VVS2_10P0_1(w[0], w[20], pars->GC_3002h, pars->GC_3002a, pars->ZERO,
      pars->ZERO, w[27]);
  VVV1P0_1(w[0], w[9], pars->GC_4, pars->ZERO, pars->ZERO, w[28]); 

  // Calculate all amplitudes
  // Amplitude(s) for diagram number 0
  VVVS1_2_0(w[0], w[1], w[9], w[8], pars->GC_3003h, pars->GC_3003a, amp[0]); 
  VVVS1_2_0(w[0], w[1], w[9], w[12], pars->GC_3003h, pars->GC_3003a, amp[1]); 
  VVVS1_2_0(w[0], w[1], w[9], w[13], pars->GC_3003h, pars->GC_3003a, amp[2]); 
  VVVS1_2_0(w[0], w[1], w[9], w[16], pars->GC_3003h, pars->GC_3003a, amp[3]); 
  VVVS1_2_0(w[0], w[1], w[9], w[19], pars->GC_3003h, pars->GC_3003a, amp[4]); 
  VVVS1_2_0(w[0], w[1], w[9], w[20], pars->GC_3003h, pars->GC_3003a, amp[5]); 
  VVS2_10_0(w[9], w[21], w[8], pars->GC_3002h, pars->GC_3002a, amp[6]); 
  VVS2_10_0(w[9], w[21], w[12], pars->GC_3002h, pars->GC_3002a, amp[7]); 
  VVS2_10_0(w[9], w[21], w[13], pars->GC_3002h, pars->GC_3002a, amp[8]); 
  VVS2_10_0(w[9], w[21], w[16], pars->GC_3002h, pars->GC_3002a, amp[9]); 
  VVS2_10_0(w[9], w[21], w[19], pars->GC_3002h, pars->GC_3002a, amp[10]); 
  VVS2_10_0(w[9], w[21], w[20], pars->GC_3002h, pars->GC_3002a, amp[11]); 
  VVV1_0(w[1], w[9], w[22], pars->GC_4, amp[12]); 
  VVV1_0(w[1], w[9], w[23], pars->GC_4, amp[13]); 
  VVV1_0(w[1], w[9], w[24], pars->GC_4, amp[14]); 
  VVV1_0(w[1], w[9], w[25], pars->GC_4, amp[15]); 
  VVV1_0(w[1], w[9], w[26], pars->GC_4, amp[16]); 
  VVV1_0(w[1], w[9], w[27], pars->GC_4, amp[17]); 
  VVS2_10_0(w[1], w[28], w[8], pars->GC_3002h, pars->GC_3002a, amp[18]); 
  VVS2_10_0(w[1], w[28], w[12], pars->GC_3002h, pars->GC_3002a, amp[19]); 
  VVS2_10_0(w[1], w[28], w[13], pars->GC_3002h, pars->GC_3002a, amp[20]); 
  VVS2_10_0(w[1], w[28], w[16], pars->GC_3002h, pars->GC_3002a, amp[21]); 
  VVS2_10_0(w[1], w[28], w[19], pars->GC_3002h, pars->GC_3002a, amp[22]); 
  VVS2_10_0(w[1], w[28], w[20], pars->GC_3002h, pars->GC_3002a, amp[23]); 

}
double CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg::matrix_gg_x0g_no_t_xz_epemepem() 
{
  int i, j; 
  // Local variables
  const int ngraphs = 24; 
  const int ncolor = 2; 
  std::complex<double> ztemp; 
  std::complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {3, 3}; 
  static const double cf[ncolor][ncolor] = {{7, -2}, {-2, 7}}; 

  // Calculate color flows
  jamp[0] = +2. * (-std::complex<double> (0, 1) * amp[0] - std::complex<double>
      (0, 1) * amp[1] - std::complex<double> (0, 1) * amp[2] +
      std::complex<double> (0, 1) * amp[3] + std::complex<double> (0, 1) *
      amp[4] + std::complex<double> (0, 1) * amp[5] - std::complex<double> (0,
      1) * amp[6] - std::complex<double> (0, 1) * amp[7] - std::complex<double>
      (0, 1) * amp[8] + std::complex<double> (0, 1) * amp[9] +
      std::complex<double> (0, 1) * amp[10] + std::complex<double> (0, 1) *
      amp[11] - std::complex<double> (0, 1) * amp[12] - std::complex<double>
      (0, 1) * amp[13] - std::complex<double> (0, 1) * amp[14] +
      std::complex<double> (0, 1) * amp[15] + std::complex<double> (0, 1) *
      amp[16] + std::complex<double> (0, 1) * amp[17] + std::complex<double>
      (0, 1) * amp[18] + std::complex<double> (0, 1) * amp[19] +
      std::complex<double> (0, 1) * amp[20] - std::complex<double> (0, 1) *
      amp[21] - std::complex<double> (0, 1) * amp[22] - std::complex<double>
      (0, 1) * amp[23]);
  jamp[1] = +2. * (+std::complex<double> (0, 1) * amp[0] + std::complex<double>
      (0, 1) * amp[1] + std::complex<double> (0, 1) * amp[2] -
      std::complex<double> (0, 1) * amp[3] - std::complex<double> (0, 1) *
      amp[4] - std::complex<double> (0, 1) * amp[5] + std::complex<double> (0,
      1) * amp[6] + std::complex<double> (0, 1) * amp[7] + std::complex<double>
      (0, 1) * amp[8] - std::complex<double> (0, 1) * amp[9] -
      std::complex<double> (0, 1) * amp[10] - std::complex<double> (0, 1) *
      amp[11] + std::complex<double> (0, 1) * amp[12] + std::complex<double>
      (0, 1) * amp[13] + std::complex<double> (0, 1) * amp[14] -
      std::complex<double> (0, 1) * amp[15] - std::complex<double> (0, 1) *
      amp[16] - std::complex<double> (0, 1) * amp[17] - std::complex<double>
      (0, 1) * amp[18] - std::complex<double> (0, 1) * amp[19] -
      std::complex<double> (0, 1) * amp[20] + std::complex<double> (0, 1) *
      amp[21] + std::complex<double> (0, 1) * amp[22] + std::complex<double>
      (0, 1) * amp[23]);

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



