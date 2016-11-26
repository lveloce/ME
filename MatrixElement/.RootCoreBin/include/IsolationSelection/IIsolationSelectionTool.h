// Dear emacs, this is -*- c++ -*-
// $Id: IIsolationSelectionTool.h 697402 2015-09-29 14:32:10Z dzhang $
// #ifndef ISOLATIONSELECTION_IISOLATIONSELECTIONTOOL_H
// #define ISOLATIONSELECTION_IISOLATIONSELECTIONTOOL_H
#ifndef ELECTRONISOLATIONSELECTION_IISOLATIONSELECTIONTOOL_H
#define ELECTRONISOLATIONSELECTION_IISOLATIONSELECTIONTOOL_H

// Framework include(s):
#include "AsgTools/IAsgTool.h"
#include "PATCore/TAccept.h"

// EDM include(s):
#include "xAODPrimitives/IsolationType.h"
#include "xAODEgamma/Photon.h"
#include "xAODEgamma/Electron.h"
#include "xAODMuon/Muon.h"
// #include "IsolationSelection/strMuon.h"

// std include(s):
#include <map>
#include <memory>

  ///
  /// @author John Morris <john.morris@cern.ch>
  ///
  /// $Revision: 697402 $
  /// $Date: 2015-09-29 16:32:10 +0200 (Tue, 29 Sep 2015) $
  ///
  /// @brief Select isolated Photons, Electrons and Muons
  ///  
struct strObj;

namespace CP
{
  class IIsolationSelectionTool :  virtual public asg::IAsgTool {

    /// Declare the interface that the class provides
    ASG_TOOL_INTERFACE( CP::IIsolationSelectionTool )

    public: 
      // Cut on object
      virtual const Root::TAccept& accept( const xAOD::Photon& x   ) const = 0;
      virtual const Root::TAccept& accept( const xAOD::Electron& x ) const = 0;
      virtual const Root::TAccept& accept( const xAOD::Muon& x     ) const = 0;
      virtual const Root::TAccept& accept( const strObj& x         ) const = 0;
      virtual const Root::TAccept& accept(const xAOD::IParticle& x ) const = 0;
      virtual StatusCode setIParticleCutsFrom(xAOD::Type::ObjectType ObjType) = 0;
      
      virtual const Root::TAccept& getPhotonTAccept()   const = 0;
      virtual const Root::TAccept& getElectronTAccept() const = 0;
      virtual const Root::TAccept& getMuonTAccept()     const = 0;       
      virtual const Root::TAccept& getObjTAccept()      const = 0;
      
  };
} // end namespace
#endif
