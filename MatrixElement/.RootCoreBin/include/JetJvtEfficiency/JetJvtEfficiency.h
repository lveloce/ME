#ifndef JETJVTEFFICIENCYSCALEFACTORS_H_
#define JETJVTEFFICIENCYSCALEFACTORS_H_

#include "JetJvtEfficiency/IJetJvtEfficiency.h"
#include "PATInterfaces/SystematicsTool.h"
#include "AsgTools/AsgTool.h"

#include <TH2F.h>
#include <string>

namespace CP {

enum SystApplied {
  NONE,
  JVT_EFFICIENCY_DOWN,
  JVT_EFFICIENCY_UP
};

class JetJvtEfficiency: public CP::IJetJvtEfficiency, public asg::AsgTool, public CP::SystematicsTool{
    ASG_TOOL_CLASS( JetJvtEfficiency, CP::IJetJvtEfficiency)

public:
    JetJvtEfficiency( const std::string& name);

    virtual StatusCode initialize();
    virtual StatusCode finalize();

    StatusCode histInitialize();

    virtual CorrectionCode getEfficiencyScaleFactor(const xAOD::Jet& jet,float& sf);
    virtual CorrectionCode applyEfficiencyScaleFactor(const xAOD::Jet& jet);
    virtual CorrectionCode applyAllEfficiencyScaleFactor(const xAOD::IParticleContainer *jets,float& sf);

    virtual bool passesJvtCut(const xAOD::Jet& jet);
    virtual bool isInRange(const xAOD::Jet& jet);

    bool isAffectedBySystematic(const CP::SystematicVariation& var) const{return CP::SystematicsTool::isAffectedBySystematic(var);}
    CP::SystematicSet affectingSystematics() const {return CP::SystematicsTool::affectingSystematics();}
    CP::SystematicSet recommendedSystematics() const {return CP::SystematicsTool::recommendedSystematics();}
    CP::SystematicCode applySystematicVariation(const CP::SystematicSet& set) {return CP::SystematicsTool::applySystematicVariation(set);}
    CP::SystematicCode sysApplySystematicVariation(const CP::SystematicSet&);

    float getJvtThresh() const {return m_jvtCut;}
    float getUserPtMax() const {return m_maxPtForJvt;}

private:

    JetJvtEfficiency();

    SystApplied m_appliedSystEnum;

    std::string m_wp;
    std::string m_file;
    SG::AuxElement::Decorator< float >* m_sfDec;
    TH2F *h_JvtHist;
    std::string m_sf_decoration_name;
    float m_jvtCut;
    std::string m_jetJvtMomentName;
    std::string m_jetEtaName;
    float m_maxPtForJvt;
};

} /* namespace CP */

#endif /* JETJVTEFFICIENCYSCALEFACTORS_H_ */
