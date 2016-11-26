// Dear emacs, this is -*- c++ -*-
// $Id: PMGSherpa22VJetsWeightTool.h 756220 2016-06-20 09:46:20Z krasznaa $
#ifndef PMGTOOLS_PMGSHERPA22VJETSWEIGHTTOOL_H
#define PMGTOOLS_PMGSHERPA22VJETSWEIGHTTOOL_H

// System include(s):
#include <array>

// Infrastructure include(s):
#include "AsgTools/AsgTool.h"

// Interface include(s):
#include "PATInterfaces/IWeightTool.h"

/// Tool calculating correct event weights for Sherpa V+jets samples
///
/// Longer documentation to be written...
///
/// @author Paul Thompson <Paul.Thompson@cern.ch>
///
/// $Revision: 756220 $
/// $Date: 2016-06-20 11:46:20 +0200 (Mon, 20 Jun 2016) $
///
class PMGSherpa22VJetsWeightTool : public virtual IWeightTool,
                                   public asg::AsgTool { 

public:
   //constructor for athena can be created using special macro
   ASG_TOOL_CLASS( PMGSherpa22VJetsWeightTool, IWeightTool )

   /// Standard tool constructor, with name
   PMGSherpa22VJetsWeightTool( const std::string& name =
                               "PMGSherpa22VJetsWeightTool" );

   /// @name Interface inherited from asg::IAsgTool
   /// @{

   /// Initialize is required by AsgTool base class
   virtual StatusCode  initialize() override final;

   /// @}

   /// @name Interface inherited from IWeightTool
   /// @{

   /// Sherpa 2.2 V+jets jet multiplicity reweight to fix issue from scale
   /// settings used in pTV sliced samples
   ///
   /// Finds truth collections on the input file and returns weight
   /// (returns 0 if no collections found)
   ///
   /// @returns The weight to be used. Or 0 if no truth het container is found.
   ///
   virtual double getWeight() const override;

   /// @}

   /// @name Functions used in calculating the event weight
   /// @{

   /// Return correction for given jet multiplicity
   double getSherpa22VJets_NJetCorrection( size_t ntag ) const;
   /// Input is the truth collection string Antikt4TruthJets or
   /// Antikt4TruthWZJets
   double
   getSherpa22VJets_NJetCorrection( const std::string &jetcontainer ) const;
   /// Function returns number of jets required for correction
   size_t getSherpa22VJets_NJet( const std::string &jetcontainer ) const;

   /// @}

private:
   /// Number of jet multiplicities that we have a correction for
   static const size_t NJET_CORRECTION_BINS = 9;
   /// Correction factors used in the weight calculation
   std::array< double, NJET_CORRECTION_BINS > m_corrFactors;

   /// @name Tool properties
   /// @{

   /// The truth jet container to use for the calculation
   std::string m_truthJetContainer;
   /// The truth particle container to use for the calculation
   std::string m_truthParticleContainer;

   /// @}

}; // class PMGSherpa22VJetsWeightTool

#endif //> !PMGTOOLS_PMGSHERPA22VJETSWEIGHTTOOL_H
