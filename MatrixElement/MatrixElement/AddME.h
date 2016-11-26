#include "MadGraphME/CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemepem.h" //VBF from Simona
#include "MadGraphME/CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum.h"					//VH from Simona
#include "MadGraphME/CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg.h"			//ggF1j from Valerio

//VBF:
CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemepem *VBF_m_ud_udepemepem_SM;

CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemepem *VBF_m_ud_udepemepem_bSM_Hvv1;	
CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemepem *VBF_m_ud_udepemepem_bSM_Hvv2p5;	
CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemepem	*VBF_m_ud_udepemepem_bSM_Avv1;
CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemepem	*VBF_m_ud_udepemepem_bSM_Avv2p5;
	
CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemepem	*VBF_m_ud_udepemepem_SMbSM_Hvv1;
CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemepem	*VBF_m_ud_udepemepem_SMbSM_Hvv2p5;	
CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemepem	*VBF_m_ud_udepemepem_SMbSM_Avv1;
CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemepem	*VBF_m_ud_udepemepem_SMbSM_Avv2p5;

//VH:
CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum 	*VH_m_udxepemmupmum_SM;
CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum 	*VH_m_udxepemmupmum_bSM;
CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum 	*VH_m_udxepemmupmum_SMplusbSM;

CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum 	*VH_m_udxepemmupmum_bSM_Hvv1;	
CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum 	*VH_m_udxepemmupmum_bSM_Hvv2p5;	
CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum	*VH_m_udxepemmupmum_bSM_Avv1;
CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum	*VH_m_udxepemmupmum_bSM_Avv2p5;
	
CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum	*VH_m_udxepemmupmum_SMbSM_Hvv1;
CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum	*VH_m_udxepemmupmum_SMbSM_Hvv2p5;	
CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum	*VH_m_udxepemmupmum_SMbSM_Avv1;
CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum	*VH_m_udxepemmupmum_SMbSM_Avv2p5;

//ggF 1jet
CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg *ggF1j_m_gg_epemepemg_SM;
CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg *ggF1j_m_gg_epemepemg_bSM;
CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg *ggF1j_m_gg_epemepemg_SMplusbSM;

CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg *ggF1j_m_gg_epemepemg_bSM_Hvv1;	
CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg *ggF1j_m_gg_epemepemg_bSM_Hvv2p5;	
CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg *ggF1j_m_gg_epemepemg_bSM_Avv1;
CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg *ggF1j_m_gg_epemepemg_bSM_Avv2p5;
	
CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg *ggF1j_m_gg_epemepemg_SMbSM_Hvv1;
CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg *ggF1j_m_gg_epemepemg_SMbSM_Hvv2p5;	
CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg *ggF1j_m_gg_epemepemg_SMbSM_Avv1;
CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg *ggF1j_m_gg_epemepemg_SMbSM_Avv2p5;
