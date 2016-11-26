/*
 * EfficiencyScaleFactor.h
 *
 *  Created on: Apr 10, 2014
 *      Author: goblirsc
 */

#ifndef EFFICIENCYSCALEFACTOR_H_
#define EFFICIENCYSCALEFACTOR_H_



// EDM include(s):
#include "xAODMuon/Muon.h"
// Infrastructure include(s):
#ifdef ROOTCORE
#   include "xAODRootAccess/Init.h"
#   include "xAODRootAccess/TEvent.h"
#endif // ROOTCORE

// EDM include(s):
#include "xAODEventInfo/EventInfo.h"
#include "xAODMuon/MuonContainer.h"


#include "PATInterfaces/CorrectionCode.h"
#include "MuonEfficiencyCorrections/HistHandler.h"
#include "PATInterfaces/ISystematicsTool.h"

// further ROOT includes
#include <TFile.h>
#include <TDirectory.h>

// STL includes
#include <string>
#include <iostream>
#include <exception>
#include <map>
#include <cmath>

namespace CP {


class EfficiencyScaleFactor {

    /// @class EfficiencyScaleFactor
    /// @brief Utility class to manage scale factor histograms
    /// Simple container class for scale factor information
    /// Contains histograms for Efficiency, Scale Factor and Systematic errors
    /// Handles loading from files and manages the histos
    /// The user should not have to interact with this directly!

public:


    /// default constructor - will create the histos as NULL pointers
    EfficiencyScaleFactor();
    /// constructor to use in real life - will read in the histos from the given file
    EfficiencyScaleFactor(std::string file, std::string time_unit, SystematicSet sys, std::string effType="EFF", bool is_lowpt=false, bool hasPtDepSys = false);
    
    EfficiencyScaleFactor(const EfficiencyScaleFactor & other);
    EfficiencyScaleFactor & operator = (const EfficiencyScaleFactor & other);

    /// Read SF histrograms from a given input file.
    bool ReadFromFile(std::string file, std::string time_unit);
    HistHandler* ReadHistFromFile(std::string name, TFile* f, std::string time_unit);

    // mangle the histograms as required by the systematic being run
    void ApplySysVariation();


    /// a few utility methods used to average the SF over run periods

    /// Add further SF's (used for creating weighted averages)
    bool Add (EfficiencyScaleFactor & to_add, float weight );
    // loads an SF set from a file and adds it to the current one
    bool AddPeriod (std::string file, std::string time_unit, float weight );

    /// Scale the histograms (again, used for weighted averages)
    bool Scale (float scale );


    /// check the consistency - all histograms should be well defined
    bool CheckConsistency();

    /// the important bits - extract SF info

    /// scale factors...
    CorrectionCode ScaleFactor(const xAOD::Muon& mu, float & SF);
    CorrectionCode ScaleFactorReplicas(const xAOD::Muon& mu, std::vector<float> & SF);

    /// ... and absolute efficiencies
    CorrectionCode Efficiency(const xAOD::Muon& mu, float & Eff);
    CorrectionCode EfficiencyReplicas(const xAOD::Muon& mu, std::vector<float> & eff);

    /// debug method
    void DebugPrint ();


    virtual ~EfficiencyScaleFactor();

    // a string name assigned to each sys variation
    std::string sysname();

    // directly interact with a histo
    HistHandler* get_sf(){
        return m_sf;
    }
    HistHandler* get_eff(){
        return m_eff;
    }
    HistHandler* get_sf_sys(){
        return m_sf_sys;
    }
    HistHandler* get_eff_sys(){
        return m_eff_sys;
    }
    HistHandler* get_sf_PtDepsys(){
        return m_sf_PtDepsys;
    }
    HistHandler* get_eff_PtDepsys(){
        return m_eff_PtDepsys;
    }


private:

    // use some maps for easy histo loading / arithmetics by name

    typedef std::vector<HistHandler*> SFvec;
    typedef std::vector<HistHandler*>::iterator iSFvec;
    typedef std::vector<HistHandler*>::const_iterator ciSFvec;


    /// read the content of the correct bin in one of my histos
    CorrectionCode GetContentFromHist(std::string hist, const xAOD::Muon& mu, float & SF);
    /// read a vector of replica contents in the correct bin in one of my histos
    CorrectionCode GetContentReplicasFromHist(std::string hist, const xAOD::Muon& mu, std::vector<float> & SF);

    // adds weight*staterr to each bin (used for systematics)
    void AddStatErrors (float weight);
    void AddStatErrors_histo (HistHandler* h, float weight);
    // adds weight*syserr to each bin (used for systematics)
    void AddSysErrors (float weight);
    void AddSysErrors_histo (HistHandler* h, HistHandler* hsys, float weight);

    // package a TH1 in a HistHandler
    HistHandler *package_histo (TH1* h);

    /// two more auxiliary methods that handle adding and scaling for
    /// any histo type, including the dreadful TH2Poly...
    void AddHistos (HistHandler* & add_to, HistHandler* add_this, float weight);
    void ScaleHisto (HistHandler* & h, float weight);

    // replica generation
    void GenerateReplicas(int nrep, int seed);
    SFvec GenerateReplicasFromHist(HistHandler* h, int nrep, int seed);



    /// the histograms needed to run
    HistHandler* m_sf;
    HistHandler* m_eff;
    HistHandler* m_sf_sys;
    HistHandler* m_eff_sys;
    // these are for the continuous pt dependent systematic if we have one
    HistHandler* m_sf_PtDepsys;
    HistHandler* m_eff_PtDepsys;

    // replicas, in case we use them
    SFvec m_sf_replicas;
    SFvec m_eff_replicas;

    // utility class to work with a fine eta phi binning
    fineEtaPhiBinning m_etaphi;

    // the systematic variation associated with this instance
    SystematicSet m_sys;

    std::string m_effType;
    
    // states that this SF should respond to low pt systematics rather than high pt ones
    bool m_is_lowpt;    
    // steers the pt dependent systematics
    bool m_respond_to_PtDepsys;
    float m_PtDepsys_weight;

};
} /* namespace CP */

#endif /* EFFICIENCYSCALEFACTOR_H_ */
