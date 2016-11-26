// header to define enums for tracking systematics
#pragma once
#include "PATInterfaces/SystematicVariation.h"
#include <unordered_map>

namespace InDet {
  
  enum TrackSystematic {
    // resolution smearing systematics from material and dead sensors
    TRK_RES_LOOSE_D0_MEAS,
    TRK_RES_LOOSE_Z0_MEAS,
    TRK_RES_TIGHT_D0_MEAS,
    TRK_RES_TIGHT_Z0_MEAS,
    TRK_RES_D0_DEAD,
    TRK_RES_Z0_DEAD,
    // weak mode alignment systematics
    TRK_BIAS_D0_WM,
    TRK_BIAS_Z0_WM,
    TRK_BIAS_QOVERP_SAGITTA_WM,
    // a (currently 50%) uncertainty in the fake rate
    TRK_FAKE_RATE,
    // uncertainties in the efficiency for two cut levels, "Loose" and "TightPrimary"
    // evaluated from extra material in the whole ID, in the IBL, and in the barrel/endcap overlap region (PP0 - "patch panel 0")
    TRK_EFF_LOOSE_GLOBAL,
    TRK_EFF_LOOSE_IBL,
    TRK_EFF_LOOSE_PP0,
    TRK_EFF_LOOSE_PHYSMODEL,
    TRK_EFF_TIGHT_GLOBAL,
    TRK_EFF_TIGHT_IBL,
    TRK_EFF_TIGHT_PP0,
    TRK_EFF_TIGHT_PHYSMODEL,
    // uncertainty for tracking efficiency in jets
    TRK_EFF_LOOSE_TIDE
  };

  // without getting too crafty with macros, this map needs to be maintained with the enum above
  static std::unordered_map< InDet::TrackSystematic, CP::SystematicVariation, std::hash<int> > TrackSystematicMap = {
    {TRK_RES_LOOSE_D0_MEAS,      CP::SystematicVariation("TRK_RES_LOOSE_D0_MEAS")},
    {TRK_RES_LOOSE_Z0_MEAS,      CP::SystematicVariation("TRK_RES_LOOSE_Z0_MEAS")},
    {TRK_RES_TIGHT_D0_MEAS,      CP::SystematicVariation("TRK_RES_TIGHT_D0_MEAS")},
    {TRK_RES_TIGHT_Z0_MEAS,      CP::SystematicVariation("TRK_RES_TIGHT_Z0_MEAS")},
    {TRK_RES_D0_DEAD,            CP::SystematicVariation("TRK_RES_D0_DEAD")},
    {TRK_RES_Z0_DEAD,            CP::SystematicVariation("TRK_RES_Z0_DEAD")},
    {TRK_BIAS_D0_WM,             CP::SystematicVariation("TRK_BIAS_D0_WM")},
    {TRK_BIAS_Z0_WM,             CP::SystematicVariation("TRK_BIAS_Z0_WM")},
    {TRK_BIAS_QOVERP_SAGITTA_WM, CP::SystematicVariation("TRK_BIAS_QOVERP_SAGITTA_WM")},
    {TRK_FAKE_RATE,              CP::SystematicVariation("TRK_FAKE_RATE")},
    {TRK_EFF_LOOSE_GLOBAL,       CP::SystematicVariation("TRK_EFF_LOOSE_GLOBAL")},
    {TRK_EFF_LOOSE_IBL,          CP::SystematicVariation("TRK_EFF_LOOSE_IBL")},
    {TRK_EFF_LOOSE_PP0,          CP::SystematicVariation("TRK_EFF_LOOSE_PP0")},
    {TRK_EFF_LOOSE_PP0,          CP::SystematicVariation("TRK_EFF_LOOSE_PHYSMODEL")},
    {TRK_EFF_TIGHT_GLOBAL,       CP::SystematicVariation("TRK_EFF_TIGHT_GLOBAL")},
    {TRK_EFF_TIGHT_IBL,          CP::SystematicVariation("TRK_EFF_TIGHT_IBL")},
    {TRK_EFF_TIGHT_PP0,          CP::SystematicVariation("TRK_EFF_TIGHT_PP0")},
    {TRK_EFF_TIGHT_PP0,          CP::SystematicVariation("TRK_EFF_TIGHT_PHYSMODEL")},
    {TRK_EFF_LOOSE_TIDE,         CP::SystematicVariation("TRK_EFF_LOOSE_TIDE")}    
  };


}
