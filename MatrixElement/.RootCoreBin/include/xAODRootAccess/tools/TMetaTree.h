// Dear emacs, this is -*- c++ -*-
// $Id: TMetaTree.h 645208 2015-02-09 15:48:59Z krasznaa $
#ifndef XAODROOTACCESS_TOOLS_TMETATREE_H
#define XAODROOTACCESS_TOOLS_TMETATREE_H

// ROOT include(s):
#include <TTree.h>

namespace xAOD {

   // Forward declaration(s):
   class TEvent;
   class TMetaBranch;

   /// Transient TTree for interactive xAOD metadata access
   ///
   /// This is pretty much the same sort of thing that ARA's TTreeTrans was
   /// designed for. In order to implement everything that we need from the
   /// transient tree, we need to override some functions within the class.
   /// But to the outside user we still want to present the usual TTree
   /// interface.
   ///
   /// This class is only meant for interactive and PyROOT access to an xAOD
   /// file. It should not be used in compiled analysis code, or for writing
   /// information into a file. (The first one will be slow, the second
   /// one just impossible.)
   ///
   /// @author Attila Krasznahorkay <Attila.Krasznahorkay@cern.ch>
   ///
   /// $Revision: 645208 $
   /// $Date: 2015-02-09 16:48:59 +0100 (Mon, 09 Feb 2015) $
   ///
   class TMetaTree : public ::TTree {

   public:
      /// Constructor with all the necessary parameters
      TMetaTree( TEvent* event, const char* name = "MetaData",
                 const char* title = "xAOD metadata transient tree" );

      /// Function overriding the base class's GetEntry(...)
      virtual ::Int_t GetEntry( ::Long64_t entry, ::Int_t getall = 0 );

      /// Function adding a new xAOD::TBranch to the tree
      void AddBranch( xAOD::TMetaBranch* br );

   private:
      /// Pointer to the TEvent reading the persistent metadata tree
      TEvent* m_event;

      /// Declare the class to ROOT
      ClassDef( xAOD::TMetaTree, 0 )

   }; // class TMetaTree

} // namespace xAOD

#endif // XAODROOTACCESS_TOOLS_TMETATREE_H
