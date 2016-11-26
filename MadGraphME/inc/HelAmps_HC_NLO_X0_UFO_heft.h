//==========================================================================
// This file has been automatically generated for C++ Standalone
// MadGraph5_aMC@NLO v. 2.3.2.2, 2015-09-06
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#ifndef HelAmps_HC_NLO_X0_UFO_heft_H
#define HelAmps_HC_NLO_X0_UFO_heft_H

#include <cmath> 
#include <complex> 

using namespace std; 

namespace MG5_HC_NLO_X0_UFO_heft 
{
void ixxxxx(double p[4], double fmass, int nhel, int nsf, std::complex<double>
    fi[6]);

void sxxxxx(double p[4], int nss, std::complex<double> sc[3]); 

void vxxxxx(double p[4], double vmass, int nhel, int nsv, std::complex<double>
    v[6]);

void txxxxx(double p[4], double tmass, int nhel, int nst, std::complex<double>
    fi[18]);

void oxxxxx(double p[4], double fmass, int nhel, int nsf, std::complex<double>
    fo[6]);

double Sgn(double e, double f); 

void VVS2_0(complex<double> V1[], complex<double> V2[], complex<double> S3[],
    complex<double> COUP, complex<double> & vertex);
void VVS2_10_0(complex<double> V1[], complex<double> V2[], complex<double>
    S3[], complex<double> COUP1, complex<double> COUP2, complex<double> &
    vertex);

void VVS10_3(complex<double> V1[], complex<double> V2[], complex<double> COUP,
    double M3, double W3, complex<double> S3[]);
void VVS10_1_2_13_3(complex<double> V1[], complex<double> V2[], complex<double>
    COUP1, complex<double> COUP2, complex<double> COUP3, complex<double> COUP4,
    double M3, double W3, complex<double> S3[]);
void VVS10_11_2_3(complex<double> V1[], complex<double> V2[], complex<double>
    COUP1, complex<double> COUP2, complex<double> COUP3, double M3, double W3,
    complex<double> S3[]);

void VVS10_0(complex<double> V1[], complex<double> V2[], complex<double> S3[],
    complex<double> COUP, complex<double> & vertex);

void VVS10P0_1(complex<double> V2[], complex<double> S3[], complex<double>
    COUP, double M1, double W1, complex<double> V1[]);

void FFV1_0(complex<double> F1[], complex<double> F2[], complex<double> V3[],
    complex<double> COUP, complex<double> & vertex);

void FFV4_3(complex<double> F1[], complex<double> F2[], complex<double> COUP,
    double M3, double W3, complex<double> V3[]);

void VVS1_3(complex<double> V1[], complex<double> V2[], complex<double> COUP,
    double M3, double W3, complex<double> S3[]);

void FFV1P0_3(complex<double> F1[], complex<double> F2[], complex<double> COUP,
    double M3, double W3, complex<double> V3[]);

void VVS13_3(complex<double> V1[], complex<double> V2[], complex<double> COUP,
    double M3, double W3, complex<double> S3[]);

void VVS11_3(complex<double> V1[], complex<double> V2[], complex<double> COUP,
    double M3, double W3, complex<double> S3[]);

void VVS2_3(complex<double> V1[], complex<double> V2[], complex<double> COUP,
    double M3, double W3, complex<double> S3[]);

void VVV1_0(complex<double> V1[], complex<double> V2[], complex<double> V3[],
    complex<double> COUP, complex<double> & vertex);

void FFV2_3(complex<double> F1[], complex<double> F2[], complex<double> COUP,
    double M3, double W3, complex<double> V3[]);
void FFV2_4_3(complex<double> F1[], complex<double> F2[], complex<double>
    COUP1, complex<double> COUP2, double M3, double W3, complex<double> V3[]);

void VVS2P0_1(complex<double> V2[], complex<double> S3[], complex<double> COUP,
    double M1, double W1, complex<double> V1[]);
void VVS2_10P0_1(complex<double> V2[], complex<double> S3[], complex<double>
    COUP1, complex<double> COUP2, double M1, double W1, complex<double> V1[]);

void VVVS2_0(complex<double> V1[], complex<double> V2[], complex<double> V3[],
    complex<double> S4[], complex<double> COUP, complex<double> & vertex);

void VVVS1_0(complex<double> V1[], complex<double> V2[], complex<double> V3[],
    complex<double> S4[], complex<double> COUP, complex<double> & vertex);
void VVVS1_2_0(complex<double> V1[], complex<double> V2[], complex<double>
    V3[], complex<double> S4[], complex<double> COUP1, complex<double> COUP2,
    complex<double> & vertex);

void VVV1P0_1(complex<double> V2[], complex<double> V3[], complex<double> COUP,
    double M1, double W1, complex<double> V1[]);

}  // end namespace MG5_HC_NLO_X0_UFO_heft

#endif  // HelAmps_HC_NLO_X0_UFO_heft_H
