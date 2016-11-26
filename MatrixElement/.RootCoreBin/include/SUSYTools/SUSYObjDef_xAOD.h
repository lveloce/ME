// This file's extension implies that it's C, but it's really -*- C++ -*-.
// $Id$
/**
 * @file SUSYTools/SUSYTools/SUSYObjDef.h
 * @author Renaud Bruneliere <Renaud.Bruneliere@cern.ch>
 * @date Feb, 2011
 * @brief Baseline SUSY object definitions.
 */

#ifndef SUSYTOOLS_SUSYOBJDEF_XAOD_H
#define SUSYTOOLS_SUSYOBJDEF_XAOD_H

// Framework include(s):
#include "AsgTools/AsgMetadataTool.h"

#include "SUSYTools/ISUSYObjDef_xAODTool.h"

///////////////////////// -*- C++ -*- /////////////////////////////
#include "PATInterfaces/SystematicCode.h"
#include "PATInterfaces/SystematicSet.h"
#include "PATInterfaces/SystematicRegistry.h"
#include "PATInterfaces/SystematicVariation.h"

#include "AsgTools/ToolHandle.h"
#include <AsgTools/AnaToolHandle.h>
#include "TEnv.h"
#include "AssociationUtils/ORToolBox.h"

#include "JetSubStructureUtils/BosonTag.h"

#include <map>
#include <set>
#include <iterator>

// Tool interfaces

class IJetCalibrationTool;
class IJERTool;
class IJERSmearingTool;
class ICPJetUncertaintiesTool;
class IJetSelector;
class IJetUpdateJvt;
class IJetModifier;

class IAsgElectronLikelihoodTool;
class IAsgElectronEfficiencyCorrectionTool;
class IEGammaAmbiguityTool;

class IAsgPhotonIsEMSelector;
class IAsgPhotonEfficiencyCorrectionTool;
class IElectronPhotonShowerShapeFudgeTool;

class IBTaggingEfficiencyTool;
class IBTaggingSelectionTool;

class IMETMaker;
class IMETSystematicsTool;

namespace CP {
class IMuonSelectionTool;
class IMuonCalibrationAndSmearingTool;
class IMuonEfficiencyScaleFactors;
class IMuonTriggerScaleFactors;

class IEgammaCalibrationAndSmearingTool;
class IIsolationSelectionTool;
class IIsolationCorrectionTool;
class IPileupReweightingTool;
class IJetJvtEfficiency;
}


namespace TauAnalysisTools {
class ITauSelectionTool;
class ITauSmearingTool;
class ITauEfficiencyCorrectionsTool;
class ITauOverlappingElectronLLHDecorator;
}

namespace ORUtils {
class IOverlapRemovalTool;
}

namespace TrigConf {
class ITrigConfigTool;
}
namespace Trig {
class TrigDecisionTool;
class IMatchingTool;
}


namespace ST {


//  class SUSYObjDef;
class SUSYObjDef_xAOD : public virtual ISUSYObjDef_xAODTool,
			public asg::AsgMetadataTool {

    // Create a proper constructor for Athena
    ASG_TOOL_CLASS( SUSYObjDef_xAOD, ST::ISUSYObjDef_xAODTool)

  public:
    SUSYObjDef_xAOD( const std::string& name );
    ~SUSYObjDef_xAOD();

    // Function initialising the tool
    StatusCode initialize();

    bool isData() {return m_dataSource == Data;}
    bool isAtlfast() {return m_dataSource == AtlfastII;}

    StatusCode setBoolProperty(const std::string& name, const bool& property);

    // Hack to make thisx configurable from python
    // 0 = data, 1 = full sim, 2 = AF-II
    void setDataSource(int source);

    // Apply the correction on a modifyable object
    StatusCode FillJet(xAOD::Jet& input, const bool doCalib = true, bool isFat = false);
    StatusCode FillTau(xAOD::TauJet& input);
    StatusCode FillMuon(xAOD::Muon& input, const float ptcut, const float etacut);
    StatusCode FillElectron(xAOD::Electron& input, const float etcut, const float etacut);
    StatusCode FillPhoton(xAOD::Photon& input, const float ptcut, const float etacut);

    const xAOD::Vertex* GetPrimVtx();

    StatusCode GetJets(xAOD::JetContainer*& copy, xAOD::ShallowAuxContainer*& copyaux, const bool recordSG = false, const std::string& jetkey = "", const xAOD::JetContainer* containerToBeCopied = 0);
    StatusCode GetJetsSyst(const xAOD::JetContainer& calibjets, xAOD::JetContainer*& copy, xAOD::ShallowAuxContainer*& copyaux, const bool recordSG = false, const std::string& jetkey = "");
    StatusCode GetFatJets(xAOD::JetContainer*& copy, xAOD::ShallowAuxContainer*& copyaux, const bool recordSG = false, const std::string& jetkey = "", const bool doLargeRdecorations = false, const xAOD::JetContainer* containerToBeCopied = 0);
    StatusCode GetTaus(xAOD::TauJetContainer*& copy, xAOD::ShallowAuxContainer*& copyaux, const bool recordSG = false, const std::string& taukey = "TauJets", const xAOD::TauJetContainer* containerToBeCopied = 0);
    StatusCode GetMuons(xAOD::MuonContainer*& copy, xAOD::ShallowAuxContainer*& copyaux, const bool recordSG = false, const std::string& muonkey = "Muons", const xAOD::MuonContainer* containerToBeCopied = 0);
    StatusCode GetElectrons(xAOD::ElectronContainer*& copy, xAOD::ShallowAuxContainer*& copyaux, const bool recordSG = false, const std::string& elekey = "Electrons", const xAOD::ElectronContainer* containerToBeCopied = 0);
    StatusCode GetPhotons(xAOD::PhotonContainer*& copy, xAOD::ShallowAuxContainer*& copyaux, const bool recordSG = false, const std::string& photonkey = "Photons", const xAOD::PhotonContainer* containerToBeCopied = 0);
    StatusCode GetMET(xAOD::MissingETContainer& met,
                      const xAOD::JetContainer* jet,
                      const xAOD::ElectronContainer* elec = 0,
                      const xAOD::MuonContainer* muon = 0,
                      const xAOD::PhotonContainer* gamma = 0,
                      const xAOD::TauJetContainer* taujet = 0,
                      bool doTST = true, bool doJVTCut = true,
                      const xAOD::IParticleContainer* invis = 0);

    StatusCode GetTrackMET(xAOD::MissingETContainer& met,
                           const xAOD::JetContainer* jet,
                           const xAOD::ElectronContainer* elec = 0,
                           const xAOD::MuonContainer* muon = 0
                                   // const xAOD::PhotonContainer* gamma = 0,
                                   // const xAOD::TauJetContainer* taujet = 0,
                          );

    StatusCode setRunNumber(const int run_number);

    bool passTSTCleaning(xAOD::MissingETContainer& met);

    static bool passTSTCleaning(float MET, float TST, float MET_phi, float TST_phi);

    bool IsSignalJet(const xAOD::Jet& input, const float ptcut, const float etacut);

    bool IsBadJet(const xAOD::Jet& input);

    bool IsSignalMuon(const xAOD::Muon& input, const float ptcut, const float d0sigcut, const float z0cut);

    bool IsSignalElectron(const xAOD::Electron& input, const float etcut, const float d0sigcut, const float z0cut);

    bool IsCosmicMuon(const xAOD::Muon& input, const float z0cut, const float d0cut);

    bool IsHighPtMuon(const xAOD::Muon& input); // See https://indico.cern.ch/event/371499/contribution/1/material/slides/0.pdf and https://indico.cern.ch/event/397325/contribution/19/material/slides/0.pdf and https://twiki.cern.ch/twiki/bin/view/Atlas/MuonSelectionTool

    bool IsSignalTau(const xAOD::TauJet& input, const float ptcut, const float etacut);

    bool IsBadMuon(const xAOD::Muon& input, const float qopcut);

    bool IsSignalPhoton(const xAOD::Photon& input, const float ptcut);

    //rel20 0.77 eff value (22/6/15) from https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/BTaggingBenchmarks#MV2c20_tagger_AntiKt4EMTopoJets
    //assumes JVT>0.64 working point
    bool IsBJet(const xAOD::Jet& input);

    bool IsTruthBJet(const xAOD::Jet& input);

    int IsBJetContinuous(const xAOD::Jet& input);

    float BtagSF(const xAOD::JetContainer* goodJets);

    float BtagSFsys(const xAOD::JetContainer* goodJets, const CP::SystematicSet& systConfig);

    double JVT_SF(const xAOD::JetContainer* goodJets);

    double JVT_SFsys(const xAOD::JetContainer* goodJets, const CP::SystematicSet& systConfig);

    //SF helpers
    //muons
    float GetSignalMuonSF(const xAOD::Muon& mu, const bool recoSF = true, const bool isoSF = true);

    double GetMuonTriggerEfficiency(const xAOD::Muon& mu, const std::string& trigExpr = "HLT_mu20_iloose_L1MU15_OR_HLT_mu50"); //to be obsoleted!
    double GetMuonTriggerEfficiencySF(const xAOD::Muon& mu, const std::string& trigExpr = "HLT_mu20_iloose_L1MU15_OR_HLT_mu50");

    double GetTotalMuonSF(const xAOD::MuonContainer& muons, const bool recoSF = true, const bool isoSF = true, const std::string& trigExpr = "HLT_mu20_iloose_L1MU15_OR_HLT_mu50");

    double GetTotalMuonSFsys(const xAOD::MuonContainer& muons, const CP::SystematicSet& systConfig, const bool recoSF = true, const bool isoSF = true, const std::string& trigExpr = "HLT_mu20_iloose_L1MU15_OR_HLT_mu50");

    //electrons
    float GetSignalElecSF(const xAOD::Electron& el, const bool recoSF = true, const bool idSF = true, const bool triggerSF = true, const bool isoSF = true, const std::string& trigExpr = "e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose");

    double GetEleTriggerEfficiency(const xAOD::Electron& el, const std::string& trigExpr = "e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose"); //to be obsoleted!!
    double GetEleTriggerEfficiencySF(const xAOD::Electron& el, const std::string& trigExpr = "e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose");

    float GetTotalElectronSF(const xAOD::ElectronContainer& electrons, const bool recoSF = true, const bool idSF = true, const bool triggerSF = true, const bool isoSF = true, const std::string& trigExpr = "e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose");

    float GetTotalElectronSFsys(const xAOD::ElectronContainer& electrons, const CP::SystematicSet& systConfig, const bool recoSF = true, const bool idSF = true, const bool triggerSF = true, const bool isoSF = true, const std::string& trigExpr = "e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose");

    //taus
    double GetSignalTauSF(const xAOD::TauJet& tau, const bool idSF = true, const bool triggerSF = true, const std::string& trigExpr = "tau25_medium1_tracktwo");
  
    double GetSignalTauSFsys(const xAOD::TauJet& tau, const CP::SystematicSet& systConfig, const bool idSF = true, const bool triggerSF = true, const std::string& trigExpr = "tau25_medium1_tracktwo");

    double GetTauTriggerEfficiencySF(const xAOD::TauJet& tau, const std::string& trigExpr = "tau25_medium1_tracktwo");

    double GetTotalTauSF(const xAOD::TauJetContainer& taus, const bool idSF = true, const bool triggerSF = true,  const std::string& trigExpr = "tau25_medium1_tracktwo");

    double GetTotalTauSFsys(const xAOD::TauJetContainer& taus, const CP::SystematicSet& systConfig, const bool idSF = true, const bool triggerSF = true, const std::string& trigExpr = "tau25_medium1_tracktwo");
  
    //photons
    double GetSignalPhotonSF(const xAOD::Photon& ph, const bool effSF = true, const bool isoSF = true);

    double GetSignalPhotonSFsys(const xAOD::Photon& ph, const CP::SystematicSet& systConfig, const bool effSF = true, const bool isoSF = true);

    double GetTotalPhotonSF(const xAOD::PhotonContainer& photons, const bool effSF = true, const bool isoSF = true);

    double GetTotalPhotonSFsys(const xAOD::PhotonContainer& photons, const CP::SystematicSet& systConfig, const bool effSF = true, const bool isoSF = true);

    //jets
    double GetTotalJetSF(const xAOD::JetContainer* goodJets, const bool btagSF = true, const bool jvtSF = true);

    double GetTotalJetSFsys(const xAOD::JetContainer* goodJets, const CP::SystematicSet& systConfig, const bool btagSF = true, const bool jvtSF = true);

    //Trigger
    bool IsTrigPassed(const std::string&, unsigned int condition=TrigDefs::Physics);

    bool IsTrigMatched(const xAOD::IParticle *part, const std::string& tr_item);

    bool IsTrigMatched(const xAOD::IParticle *part1, const xAOD::IParticle *part2, const std::string& tr_item);

    float GetTrigPrescale(const std::string&);

    const Trig::ChainGroup* GetTrigChainGroup(const std::string&);

    float GetPileupWeight();

    ULong64_t GetPileupWeightHash();

    float GetDataWeight(const std::string&);

    float GetCorrectedAverageInteractionsPerCrossing();

    double GetSumOfWeights(int channel);

    unsigned int GetRandomRunNumber();

    StatusCode ApplyPRWTool();

    int treatAsYear();

    StatusCode OverlapRemoval(const xAOD::ElectronContainer *electrons, const xAOD::MuonContainer *muons, const xAOD::JetContainer *jets,
                              const xAOD::PhotonContainer* gamma = 0, const xAOD::TauJetContainer* taujet = 0);

    StatusCode IsoOverlapRemoval(const xAOD::IParticleContainer *parts);

    CP::SystematicCode resetSystematics();

    CP::SystematicCode applySystematicVariation( const CP::SystematicSet& systConfig );

    //truth helpers
    bool isPrompt(const xAOD::IParticle* part);

    StatusCode FindSusyHP(int& pdgid1, int& pdgid2);

    StatusCode FindSusyHP(const xAOD::TruthParticleContainer *truthP, int& pdgid1, int& pdgid2, bool isTruth3=false);

    static bool FindSusyHardProc(const xAOD::TruthParticleContainer *truthP, int& pdgid1, int& pdgid2, bool isTruth3=false);

    StatusCode FindSusyHP(const xAOD::TruthEvent *truthE, int& pdgid1, int& pdgid2);

    static bool FindSusyHardProc(const xAOD::TruthEvent *truthE, int& pdgid1, int& pdgid2);

    std::vector<ST::SystInfo> getSystInfoList();

    // Temporary function for Sherpa 2.2 V+jets n-jets reweighting 
    // (see https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/CentralMC15ProductionList#NEW_Sherpa_v2_2_V_jets_NJet_rewe)
    float getSherpaVjetsNjetsWeight();
    float getSherpaVjetsNjetsWeight(const std::string& jetContainer);
    float getSherpaVjetsNjetsWeight(int njets);

  private:

    StatusCode SUSYToolsInit();

    //map ConfigFile names to Property names
    std::map<std::string, std::string> m_conf_to_prop;

    //book boolean properties already set
    std::set<std::string> m_bool_prop_set;


  protected:

    StatusCode readConfig(); 
    StatusCode validConfig(bool strict = false); 

    void configFromFile(bool& property, const std::string& propname, TEnv& rEnv,
                        bool defaultValue);
    void configFromFile(double& property, const std::string& propname, TEnv& rEnv,
                        double defaultValue);
    void configFromFile(int& property, const std::string& propname, TEnv& rEnv,
                        int defaultValue);
    void configFromFile(std::string& property, const std::string& propname, TEnv& rEnv,
                        const std::string& defaultValue);

    //little helpers for WP configurations / handling
    bool check_isOption(std::string wp, std::vector<std::string>& list);
    bool check_isTighter(std::string wp1, std::string wp, std::vector<std::string>& list);
  
    std::string EG_WP(std::string wp); //translate our WPs to make egamma selectors happy

#ifdef XAOD_STANDALONE // more convenient for property setting
    DataSource m_dataSource;
    xAOD::JetInput::Type m_jetInputType; // permit switching between LC, PFlow, EM jets
    // xAOD::Muon::Quality m_muId;
    // xAOD::Muon::Quality m_muIdBaseline;
    int m_muId;
    int m_muIdBaseline;
    ORUtils::ORToolBox m_orToolbox;
#else
    int m_dataSource;
    int m_jetInputType;
    int m_muId;
    int m_muIdBaseline;
#endif
    std::string m_configFile;

    int m_jesNPset;
    bool m_useBtagging;
    bool m_debug;
    std::string m_badJetCut;

    std::string m_fatJetUncConfig;

    bool m_tool_init;
    bool m_subtool_init;

    std::string m_eleTerm    ;
    std::string m_gammaTerm  ;
    std::string m_tauTerm    ;
    std::string m_jetTerm    ;
    std::string m_muonTerm   ;
    std::string m_inputMETSuffix;
    std::string m_inputMETMap;
    std::string m_inputMETCore;
    std::string m_inputMETRef;
    std::string m_outMETTerm;
    bool m_metRemoveOverlappingCaloTaggedMuons;
    bool m_metDoMuonJetOR;

    bool m_trkMETsyst;
    bool m_caloMETsyst;

    int m_prwDefaultChannel;
    std::vector<std::string> m_prwConfFiles;
    std::vector<std::string> m_prwLcalcFiles;
    double m_muUncert;

    //bookkeep supported configurations (in increasing order of tightness)
    std::vector<std::string> el_id_support;
    std::vector<std::string> ph_id_support;
    int mu_id_support; //max value

    std::vector<std::string> tau_trig_support;

 
    std::string m_eleId;
    std::string m_eleIdBaseline;
    std::string m_photonId;
    std::string m_photonIdBaseline;
    std::string m_tauId;
    std::string m_eleIso_WP;
    std::string m_photonIso_WP;
    std::string m_muIso_WP;
    std::string m_BtagWP;
    std::string m_BtagTagger;

    //configurable cuts here
    double m_eleBaselinePt;
    bool   m_eleBaselineCrackVeto;
    double m_elePt;
    double m_eleEta;
    bool   m_eleCrackVeto;
    double m_eled0sig;
    double m_elez0;

    double m_muBaselinePt;
    double m_muPt;
    double m_muEta;
    double m_mud0sig;
    double m_muz0;
    bool m_murequirepassedHighPtCuts;

    double m_muCosmicz0;
    double m_muCosmicd0;

    double m_badmuQoverP;

    double m_photonBaselinePt;
    double m_photonEta;
    double m_photonPt;

    double m_tauPrePtCut;
    double m_tauPt;
    double m_tauEta;
    std::string m_tauConfigPath;

    double m_jetPt;
    double m_jetEta;
    double m_jetJvt;
    std::string m_JVT_WP;

    bool   m_doFwdJVT;
    double m_fwdjetEtaMin;
    double m_fwdjetPtMax;
    bool   m_fwdjetTightOp;

    bool m_orDoTau;
    bool m_orDoPhoton;
    bool m_orDoBjet;
    bool m_orDoElBjet;
    bool m_orDoMuBjet;
    bool m_orDoBoostedElectron;
    double m_orBoostedElectronC1;
    double m_orBoostedElectronC2;
    double m_orBoostedElectronMaxConeSize;
    bool m_orDoBoostedMuon;
    double m_orBoostedMuonC1;
    double m_orBoostedMuonC2;
    double m_orBoostedMuonMaxConeSize;
    double m_orMuJetPtRatio;
    double m_orMuJetTrkPtRatio;
    double m_orMuJetInnerDR;
    bool m_orDoMuonJetGhostAssociation;
    bool m_orRemoveCaloMuons;
    bool m_orApplyJVT;
    std::string m_orBtagWP;

    bool m_doIsoSignal;

    std::string m_metJetSelection;

    int  m_showerType;

    std::string m_defaultJets;
    std::string m_fatJets;

    CP::SystematicSet m_currentSyst;
    //std::string m_currentSyst;

    std::string m_EG_corrModel;

    std::string m_EG_corrFile_reco;
    std::string m_EG_corrFile_id;
    std::string m_EG_corrFile_trig_singleLep;
    std::string m_EG_corrFile_trig_diLep;
    std::string m_EG_corrFile_trig_mixLep;
    std::string m_EG_corrFile_iso;

    std::string m_EG_corrFile_trigEff_singleLep;
    std::string m_EG_corrFile_trigEff_diLep;
    std::string m_EG_corrFile_trigEff_mixLep;

    std::string m_bTaggingCalibrationFilePath;

    ToolHandle<IJetCalibrationTool> m_jetCalibTool;
    ToolHandle<IJetCalibrationTool> m_jetFatCalibTool;
    ToolHandle<IJERTool> m_jerTool;
    ToolHandle<IJERSmearingTool> m_jerSmearingTool;
    ToolHandle<ICPJetUncertaintiesTool> m_jetUncertaintiesTool;
    ToolHandle<ICPJetUncertaintiesTool> m_fatjetUncertaintiesTool;
    ToolHandle<IJetSelector> m_jetCleaningTool;
    ToolHandle<IJetUpdateJvt> m_jetJvtUpdateTool;
    ToolHandle<IJetModifier> m_jetFwdJvtTool;
    ToolHandle<CP::IJetJvtEfficiency> m_jetJvtEfficiencyTool;

    std::string m_WtagWP;
    std::string m_ZtagWP;

    JetSubStructureUtils::BosonTag* m_WTaggerTool;
    JetSubStructureUtils::BosonTag* m_ZTaggerTool;

    //
    ToolHandle<CP::IMuonSelectionTool> m_muonSelectionTool;
    ToolHandle<CP::IMuonSelectionTool> m_muonSelectionToolBaseline;
    ToolHandle<CP::IMuonCalibrationAndSmearingTool> m_muonCalibrationAndSmearingTool;
    ToolHandle<CP::IMuonEfficiencyScaleFactors> m_muonEfficiencySFTool;
    ToolHandle<CP::IMuonEfficiencyScaleFactors> m_muonIsolationSFTool;
    ToolHandle<CP::IMuonTriggerScaleFactors> m_muonTriggerSFTool;
    //
    ToolHandle<IAsgElectronEfficiencyCorrectionTool> m_elecEfficiencySFTool_reco;
    ToolHandle<IAsgElectronEfficiencyCorrectionTool> m_elecEfficiencySFTool_id;
    ToolHandle<IAsgElectronEfficiencyCorrectionTool> m_elecEfficiencySFTool_trig_singleLep;
    ToolHandle<IAsgElectronEfficiencyCorrectionTool> m_elecEfficiencySFTool_trig_diLep;
    ToolHandle<IAsgElectronEfficiencyCorrectionTool> m_elecEfficiencySFTool_trig_mixLep;
    ToolHandle<IAsgElectronEfficiencyCorrectionTool> m_elecEfficiencySFTool_iso;
    //
    ToolHandle<IAsgElectronEfficiencyCorrectionTool> m_elecEfficiencySFTool_trigEff_singleLep;
    ToolHandle<IAsgElectronEfficiencyCorrectionTool> m_elecEfficiencySFTool_trigEff_diLep;
    ToolHandle<IAsgElectronEfficiencyCorrectionTool> m_elecEfficiencySFTool_trigEff_mixLep;
    //
    ToolHandle<CP::IEgammaCalibrationAndSmearingTool> m_egammaCalibTool;
    ToolHandle<IAsgElectronLikelihoodTool> m_elecSelLikelihood;
    ToolHandle<IAsgElectronLikelihoodTool> m_elecSelLikelihoodBaseline;
    ToolHandle<IAsgPhotonIsEMSelector>     m_photonSelIsEM;
    ToolHandle<IAsgPhotonIsEMSelector>     m_photonSelIsEMBaseline;
    ToolHandle<IAsgPhotonEfficiencyCorrectionTool> m_photonEfficiencySFTool;
    ToolHandle<IAsgPhotonEfficiencyCorrectionTool> m_photonIsolationSFTool;
    ToolHandle<IElectronPhotonShowerShapeFudgeTool> m_electronPhotonShowerShapeFudgeTool;
    ToolHandle<IEGammaAmbiguityTool> m_egammaAmbiguityTool;
    //
    ToolHandle<TauAnalysisTools::ITauSelectionTool> m_tauSelTool;
    ToolHandle<TauAnalysisTools::ITauSmearingTool> m_tauSmearingTool;
    ToolHandle<TauAnalysisTools::ITauEfficiencyCorrectionsTool> m_tauEffTool;
    ToolHandle<TauAnalysisTools::ITauEfficiencyCorrectionsTool> m_tauTrigEffTool0;
    ToolHandle<TauAnalysisTools::ITauEfficiencyCorrectionsTool> m_tauTrigEffTool1;
    ToolHandle<TauAnalysisTools::ITauEfficiencyCorrectionsTool> m_tauTrigEffTool2;
    ToolHandle<TauAnalysisTools::ITauEfficiencyCorrectionsTool> m_tauTrigEffTool3;
    ToolHandle<TauAnalysisTools::ITauEfficiencyCorrectionsTool> m_tauTrigEffTool4;
    ToolHandle<TauAnalysisTools::ITauOverlappingElectronLLHDecorator> m_tauElORdecorator;
    //
    ToolHandle<IBTaggingEfficiencyTool> m_btagEffTool;
    ToolHandle<IBTaggingSelectionTool> m_btagSelTool;
    ToolHandle<IBTaggingSelectionTool> m_btagSelTool_OR;
    //
    ToolHandle<IMETMaker> m_metMaker;
    ToolHandle<IMETSystematicsTool> m_metSystTool;
    //
    ToolHandle<TrigConf::ITrigConfigTool> m_trigConfTool;
    ToolHandle<Trig::TrigDecisionTool> m_trigDecTool;
    ToolHandle<Trig::IMatchingTool> m_trigMatchingTool;
    //
    ToolHandle<CP::IIsolationCorrectionTool> m_isoCorrTool;
    ToolHandle<CP::IIsolationSelectionTool> m_isoTool;
    //
    ToolHandle<CP::IPileupReweightingTool> m_prwTool;
    //
    ToolHandle<ORUtils::IOverlapRemovalTool> m_orTool;

}; // Class SUSYObjDef_xAOD

} // namespace ST


#endif // not SUSYTOOLS_SUSYOBJDEF_XAOD_H
