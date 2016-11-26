// Asg wrapper around the MissingMassCalculator
// author Quentin Buat <quentin.buat@no.spam.cern.ch>
#ifndef DITAUMASSTOOLS_MISSINGMASSTOOL_H
#define DITAUMASSTOOLS_MISSINGMASSTOOL_H

// Framework includes
#include "AsgTools/AsgTool.h"

//Local includes
#include "DiTauMassTools/IMissingMassTool.h"
#include "DiTauMassTools/MissingMassCalculator.h"


class MissingMassTool : virtual public IMissingMassTool, virtual public asg::AsgTool
{

  /// Proper constructor for Athena
  ASG_TOOL_CLASS(MissingMassTool, IMissingMassTool)

 public:
  
  /// Standard constructor for standalone usage
  MissingMassTool(const std::string& name);
  /// Copy constructor for reflex in Athena
  MissingMassTool(const MissingMassTool& other);

  /// virtual destructor
  virtual ~MissingMassTool() { };

  /// Initialize the tool
  virtual StatusCode initialize();

  /// Initialize the tool
  virtual StatusCode finalize();


  // generic method
  virtual CP::CorrectionCode apply (const xAOD::EventInfo& ei,
				    const xAOD::IParticle* part1,
				    const xAOD::IParticle* part2,
				    const xAOD::MissingET* met,
				    const int & njets);

  // Internal calculation -- Is void the appropriate 
  // return type ? 
  // DR : make it public : allows full control on 4-vectors if necessarys
  virtual void calculate(const xAOD::EventInfo & ei, 
			 const TLorentzVector & vis_tau1,
			 const TLorentzVector & vis_tau2,
			 const int & tau1_decay_type,
			 const int & tau2_decay_type,
			 const xAOD::MissingET & met,
			 const int & njets);


  virtual MissingMassCalculator* get() {return m_MMC;}
  virtual double GetFitStatus(const int & method) {(void) method; return m_MMC->GetFitStatus();}
  virtual double GetFittedMass(const int& method) {return m_MMC->GetFittedMass(method);}
  virtual TLorentzVector GetResonanceVec(const int& method) {return m_MMC->GetResonanceVec(method);}
  virtual TVector2 GetFittedMetVec(const int& method) {return m_MMC->GetFittedMetVec(method);}
  virtual TLorentzVector GetNeutrino4vec(const int& method, const int & index) {return m_MMC->GetNeutrino4vec(method, index);}
  virtual TLorentzVector GetTau4vec(const int& method, const int & index) {return m_MMC->GetTau4vec(method, index);}

  int mmcType(const xAOD::IParticle* part) const; // returns particle type as required by MMC
  CP::CorrectionCode setLFVMode(const xAOD::IParticle* p1, const xAOD::IParticle* p2, int mmcType1=-1, int mmcType2=-1);

 private:

  

  MissingMassCalculator* m_MMC;
  int m_alg_version;
  double m_n_sigma_met;
  int m_tail_cleanup;
  int m_use_verbose;
  int m_use_tau_probability;
  int m_niter_fit_2;
  int m_niter_fit_3;
  int m_use_defaults;
  int m_use_efficiency_recovery;
  std::string m_calib_set;
  std::string m_lfv_mode;
  bool m_decorate;
  bool m_use_met_param_dphiLL;

};
  

#endif
