// Dear emacs, this is -*- c++ -*-
// $Id: TFileAccessTracer.h 683789 2015-07-17 12:01:07Z krasznaa $
#ifndef XAODROOTACCESS_TOOLS_TFILEACCESSTRACER_H
#define XAODROOTACCESS_TOOLS_TFILEACCESSTRACER_H

// System include(s):
#include <set>
#include <string>

// ROOT include(s):
#include <TString.h>

// Forward declaration(s):
class TFile;

namespace xAOD {

   /// Helper class keeping track of the files that got accessed
   ///
   /// This class helps in keeping track of which files get accessed during a
   /// job. To be able to report about them to the DDM (Rucio) system in a way
   /// that doesn't rely on the grid middleware. (So backdoor access to files
   /// stored at data centres becomes visible to the DDM system.)
   ///
   /// The class can also send information about which branches/variables got
   /// accessed in the job. This it simply gets from the xAODCore code.
   ///
   /// xAOD::TEvent uses this class to send information about xAOD access to
   /// the central Rucio monitoring infrastructure. This default behaviour can
   /// be influenced in two ways:
   ///   - Use the TFileAccessTrancer::enableDataSubmission function to disable
   ///     data submission from a particular application;
   ///   - Set the environment variable "XAOD_ACCESSTRACER_FRACTION" to a
   ///     floating point value, which is the fraction of jobs that should be
   ///     monitored within that session. This is mostly for grid purposes...
   ///
   /// @author Attila Krasznahorkay <Attila.Krasznahorkay@cern.ch>
   ///
   /// $Revision: 683789 $
   /// $Date: 2015-07-17 14:01:07 +0200 (Fri, 17 Jul 2015) $
   ///
   class TFileAccessTracer {

   public:
      /// Default constructor
      TFileAccessTracer();
      /// Destructor
      ~TFileAccessTracer();

      /// Add information about a new file that got accessed
      void add( const ::TFile& file );

      /// The address of the server that information is sent to
      const std::string& serverAddress() const;
      /// Set the address of the server that information is sent to
      void setServerAddress( const std::string& addr );

      /// Fraction of jobs that should send monitoring information
      ::Double_t monitoredFraction() const;
      /// Set the fraction of jobs that should send monitoring information
      void setMonitoredFraction( ::Double_t value );

      /// Function for turning data submission on/off
      static void enableDataSubmission( ::Bool_t value );

   private:
      /// Helper class storing information about the accessed files
      class AccessedFile {
      public:
         /// The full path to the file
         ::TString filePath;
         /// The name of the file
         ::TString fileName;
         /// Operator to be able to put this into an std::set
         bool operator< ( const AccessedFile& rhs ) const;
         /// Function returning the full file path
         ::TString fullFilePath() const;
      };

      /// List of all the input files that were accessed in the job
      std::set< AccessedFile > m_accessedFiles;

      /// Address of the server to send monitoring information to
      std::string m_serverAddress;

      /// Fraction of jobs that should send monitoring information
      ::Double_t m_monitoredFraction;

      /// Global property for enabling data submission or not
      static ::Bool_t m_enableDataSumbission;

   }; // class TFileAccessTracer

} // namespace xAOD

#endif // XAODROOTACCESS_TOOLS_TFILEACCESSTRACER_H
