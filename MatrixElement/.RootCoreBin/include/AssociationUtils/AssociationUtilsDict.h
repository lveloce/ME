#ifndef ASSOCIATIONUTILS_ASSOCIATIONUTILSDICT_H
#define ASSOCIATIONUTILS_ASSOCIATIONUTILSDICT_H

// Reflex dictionary generation
// Following instructions on the CP tools twiki:
// https://twiki.cern.ch/twiki/bin/viewauth/AtlasComputing/DevelopingCPToolsForxAOD

// Special handling for Eigen vectorization
#if defined(__GCCXML__) and not defined(EIGEN_DONT_VECTORIZE)
#define EIGEN_DONT_VECTORIZE
#endif

// Tool headers
#include "AssociationUtils/OverlapRemovalTool.h"
#include "AssociationUtils/BaseOverlapTool.h"
#include "AssociationUtils/DeltaROverlapTool.h"
#include "AssociationUtils/EleEleOverlapTool.h"
#include "AssociationUtils/EleMuSharedTrkOverlapTool.h"
#include "AssociationUtils/EleJetOverlapTool.h"
#include "AssociationUtils/MuJetOverlapTool.h"
#include "AssociationUtils/AltMuJetOverlapTool.h"
#include "AssociationUtils/TauLooseEleOverlapTool.h"
#include "AssociationUtils/TauLooseMuOverlapTool.h"
#include "AssociationUtils/TauJetOverlapTool.h"
#include "AssociationUtils/TauAntiTauJetOverlapTool.h"
#include "AssociationUtils/ObjLinkOverlapTool.h"

// Helpers
#include "AssociationUtils/ORToolBox.h"
#include "AssociationUtils/ToolBox.h"
#include "AssociationUtils/BJetHelper.h"
#include "AssociationUtils/DeltaRMatcher.h"
#include "AssociationUtils/MuJetGhostDRMatcher.h"
#include "AssociationUtils/OverlapDecorationHelper.h"
#include "AssociationUtils/OverlapLinkHelper.h"

#endif
