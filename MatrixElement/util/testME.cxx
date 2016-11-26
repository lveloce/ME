//macro for testing the matrix element codes, basically the same as the testMadgaphME.cxx code from the MadGraphME package

#include "MatrixElement/AddME.h"
#include "MadGraphME/ComputeMGME.h"

#include "TRandom2.h"

#include <iostream>
#include <memory>

class TestMEBase {
public:
  virtual void getME() = 0;

  template <typename T>
  static std::shared_ptr<TestMEBase> build(std::string pCard);
};

template <typename T>
class TestME: public TestMEBase {
public:
  TestME(T&& s, std::string pCard);
  void getME();
  void setMomenta();
private:
  T m_S; 
  std::string m_paramCard; 

  TLorentzVector m_cms, m_cms4l; //m of the total event, m of the 4 leptons
  std::vector<TLorentzVector> m_fermions; //the fermion vector
};

template <typename T>
TestME<T>::TestME(T&& s, std::string pCard):
  m_S(s), m_paramCard(pCard) {
    m_S.initProc(m_paramCard.c_str()); // This can throw an exception
    setMomenta(); //this builds the 4-momenta
}

//This template builds the 4-momenta to send to compute ME
template <typename T>
void TestME<T>::setMomenta() {

  if( (m_S.nexternal - m_S.ninitial) < 4 )
    std::cerr << "ERROR: the process is not compatible with our test!" << std::endl;
  m_fermions.clear();
  m_fermions.resize(m_S.nexternal - m_S.ninitial);
 // Input should be in GeV !!!!
 // Define MGME_USE_MEV if you need MeV!
 // ComputeMGME_cmsM4l is just a wrapper around the MadGraph ME. 
 // In particular, the ordering of m_fermions must correspond to the process:
 // e.g. in MadGraphME/inc/CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_ddx_epemepemuux.h
 // which is produced after building the MadGraph MEs.

#define USE_RANDOM_VALUES
#ifdef USE_RANDOM_VALUES
  TRandom2 rnd;
  for(int i = 0 ; i < 4 ; ++i)
    m_fermions[i].SetPtEtaPhiM( rnd.Uniform(10.,200.), rnd.Uniform(-2.5,2.5), rnd.Uniform(0, 6.2831853072), 106. );
  if( (m_S.nexternal - m_S.ninitial) == 6 ) {
    for(int i = 4 ; i < 6 ; ++i)
      m_fermions[i].SetPtEtaPhiM( rnd.Uniform(30.,200), rnd.Uniform(-2.5,2.5), rnd.Uniform(0, 6.2831853072), 2.3 );
  }
  else if( (m_S.nexternal - m_S.ninitial) == 5 ) {
    for(int i = 4 ; i < 5 ; ++i)
      m_fermions[i].SetPtEtaPhiM( rnd.Uniform(30.,200), rnd.Uniform(-2.5,2.5), rnd.Uniform(0, 6.2831853072), 2.3 );
  }
#else
  m_fermions[0].SetPtEtaPhiM( 35., 1.10, 1.234, 106. );
  m_fermions[1].SetPtEtaPhiM( 38., -1.0, 1.500, 106. );
  m_fermions[2].SetPtEtaPhiM( 10., 1.10, 1.234, 106. );
  m_fermions[3].SetPtEtaPhiM( 10., -1.8, 1.234, 106. );
  if( (m_S.nexternal - m_S.ninitial) == 6 ) {
    m_fermions[4].SetPtEtaPhiM( 20., 0.9, 1.104, 2.3 );
    m_fermions[5].SetPtEtaPhiM( 20., -1.18, 1.104, 2.3 );
  }
  if( (m_S.nexternal - m_S.ninitial) == 5 ) {
    m_fermions[4].SetPtEtaPhiM( 20., 0.9, 1.104, 2.3 );
  }
#endif
  for(unsigned i = 0 ; i < m_fermions.size() ; ++i) {
    m_cms += m_fermions[i];
    if( i < 4 ) m_cms4l += m_fermions[i];
  }
  for(unsigned i = 0 ; i < m_fermions.size() ; ++i)
    m_fermions[i].Boost( -( m_cms.BoostVector() ) );

  std::cout << std::string(80,'-') << endl;
  std::cout << " Momenta:\t" << "Pt\tEta\tPhi\tMass" << endl;

  double (TLorentzVector::*fPtr[])() const =  { &TLorentzVector::E, &TLorentzVector::Px, &TLorentzVector::Py, &TLorentzVector::Pz };
  for(unsigned i = 0 ; i < m_fermions.size() ; ++i) {
    for(int j = 0 ; j < 4 ; ++j)
      std::cout << "\t" << (m_fermions[i].*fPtr[j])();
    std::cout << std::endl;
  }

  std::cout << std::string(80,'-') << endl;

}

template <typename T> //this function is what actually calls the ME calculation
void TestME<T>::getME() {

  std::cout << "Param card: " << m_paramCard << std::endl;
  std::cout << std::string(80,'-') << endl;

  // Will use the event's CMS as MH value
  std::vector<float> mtxElem = ComputeMGME_cmsM4l(m_S, m_fermions, m_cms, m_cms4l); //here is where the ME is calculated

  // Display matrix elements
  for(int i=0; i<m_S.nprocesses;i++) {
    std::cout << " Matrix element = "
      << setiosflags(ios::fixed) << setprecision(17)
      << mtxElem[i]
      << " GeV^" << -(2*m_S.nexternal-8) << endl;
    std::cout << " Log = " << log( mtxElem[0] ) << std::endl;
  }

  std::cout << std::string(80,'-') << endl;

}

template <typename T> 
std::shared_ptr<TestMEBase> TestMEBase::build(std::string pCard) { 
    std::shared_ptr<TestMEBase> sharedPtr = std::make_shared<TestME<T>>(T(), pCard);
    return sharedPtr;
}

//here is where we load the parameter cards, collect the fermion vectors, and call the ME calculation
int main (int argc, const char** argv) {
  argc = argc;
  argv = argv;

  std::vector<std::shared_ptr<TestMEBase>> testMatrixElements;

  // Loading proper parameter card
  const char* param_card = "0"; 

  try {
    // 2jet VBF Processes
    param_card = "MadGraphME/Cards/param_card_VBF_SM.dat";
    testMatrixElements.push_back( TestMEBase::build<CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemepem>(param_card) );
    
    param_card = "MadGraphME/Cards/param_card_ggF1j_SM.dat";
    testMatrixElements.push_back( TestMEBase::build<CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg>(param_card) );

  } catch (const char* e) {
    std::cout << "Exception: " << e << ". Parameter card: " << param_card << std::endl; 
    return 1;
  }
  for(auto tH : testMatrixElements) {
    tH->getME();
  }
  
  return 0;
}







