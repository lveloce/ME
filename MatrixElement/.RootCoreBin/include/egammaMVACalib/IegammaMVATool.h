// Dear Emacs, this is -*- C++ -*-

#ifndef IMVA_CALIBRATION_H_
#define IMVA_CALIBRATION_H_

#include "AsgTools/IAsgTool.h"

// EDM includes
#include "xAODEgamma/EgammaFwd.h"
#include "xAODEgamma/ElectronFwd.h"
#include "xAODEgamma/PhotonFwd.h"
#include "xAODEgamma/EgammaEnums.h"
#include "xAODCaloEvent/CaloClusterFwd.h"
#include "xAODTracking/VertexFwd.h"

class egammaRec;

class IegammaMVATool : virtual public asg::IAsgTool{
  /// Declare the interface that the class provides
  ASG_TOOL_INTERFACE( IegammaMVATool )
public:
  virtual ~IegammaMVATool() {};

  /** @brief initialize method*/
  virtual StatusCode initialize() = 0;
  /** @brief finalize method*/
  virtual StatusCode finalize() = 0;
 /** @brief execute method*/
  virtual StatusCode execute(xAOD::CaloCluster* cluster,const xAOD::Egamma* eg)=0;
  virtual StatusCode execute(xAOD::CaloCluster* cluster,const egammaRec* egRec,
			     xAOD::EgammaParameters::EgammaType egType)=0;
  virtual StatusCode hltexecute(xAOD::CaloCluster* cluster, const std::string& egType)=0;
};

#endif
