#ifndef QUICK_ANA__TAU_TOOL_H
#define QUICK_ANA__TAU_TOOL_H

//        Copyright Iowa State University 2014.
//                  Author: Nils Krumnack
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// Please feel free to contact me (nils.erik.krumnack@cern.ch) for bug
// reports, feature suggestions, praise and complaints.


// This module still needs to be documented.  The interface provided
// in this module is intended for experts only.  The module is
// considered to be in the pre-alpha stage.



#include <QuickAna/Global.h>

// #include <TauAnalysisTools/Enums.h>
#include <QuickAna/AnaToolCorrect.h>
#include <AsgTools/AnaToolHandle.h>
#include <QuickAna/AnaToolSelect.h>
#include <QuickAna/AnaToolWeight.h>
#include <QuickAna/SelectionCut.h>
// #include <xAODTau/TauJetContainer.h>

/// Forward declarations
namespace TauAnalysisTools
{
  class ITauSmearingTool;
  class ITauSelectionTool;
  class ITauEfficiencyCorrectionsTool;
  class ITauTruthMatchingTool;
}

namespace ana
{

  /// @brief Tool for the correction of taus
  ///
  /// Applies correction-related systematics as well
  ///
  class TauToolCorrect : virtual public AnaToolCorrect<xAOD::TauJetContainer>
  {

    /// This macro generates a proper constructor for Athena
    ASG_TOOL_CLASS (TauToolCorrect, ana::IAnaTool)

  public:
    // Public interface methods

    /// @brief Standard constructor
    TauToolCorrect (const std::string& name);

    /// @brief Initialize this tool.
    /// Returns failure on configuration error.
    StatusCode initialize() override;

    /// @brief Run the calibration on this event.
    /// The accept flags tells whether we accept the tau.
    virtual StatusCode
    correctObject (xAOD::TauJet& tau) override;

  private:
    // CP tools

    /// The tau CP smearing tool.
    asg::AnaToolHandle<TauAnalysisTools::ITauSmearingTool> m_smear_tool;

    /// Eta selection cut; not currently used.
    SelectionCut cut_maxEta;
    /// Smearing tool cut rejects out-of-validity taus
    SelectionCut cut_smear_tool;

  }; // class TauToolCorrect



  /// @brief Tool for selection of analysis taus
  ///
  /// Applies the common tau selections
  ///
  class TauToolSelect : virtual public AnaToolSelect<xAOD::TauJetContainer>
  {

    /// This macro generates a proper constructor for Athena
    ASG_TOOL_CLASS (TauToolSelect, ana::IAnaTool)

  public:
    // Public interface methods

    /// @brief Standard constructor
    TauToolSelect (const std::string& name);

    /// @brief Initialize this tool.
    /// Returns failure on configuration error.
    StatusCode initialize() override;

    /// @brief Apply selection on this tau.
    /// The accept flag gives the result.
    virtual StatusCode
    selectObject (xAOD::TauJet& tau) override;

  private:

    /// The jet BDT working point.
    /// See TauAnalysisTools::e_JETID
    int m_jetID;
    /// The electron BDT working point.
    /// See TauAnalysisTools::e_ELEID
    int m_eleID;

    /// The tau CP selection tool
    asg::AnaToolHandle<TauAnalysisTools::ITauSelectionTool> m_selectionTool;

    /// The tau CP selection tool cut
    SelectionCut m_selectionToolCut;

  }; // class TauToolSelect



  /// @brief Tool for calculating the weights for analysis taus
  ///
  /// Applies the tau ID efficiency scale factors
  class TauToolWeight : virtual public AnaToolWeight<xAOD::TauJetContainer>
  {

    /// This macro generates a proper constructor for Athena
    ASG_TOOL_CLASS (TauToolWeight, ana::IAnaTool)

  public:
    // Public interface methods

    /// @brief Standard constructor
    TauToolWeight (const std::string& name);

    /// @brief Initialize this tool.
    /// Returns failure on configuration error.
    StatusCode initialize() override;

    /// @brief Calculate the weight for this tau.
    /// Assigns result to weight.
    virtual StatusCode
    objectWeight (const xAOD::TauJet& tau, float& weight) override;

  private:
    // CP tools

    /// The tau CP efficiency tool
    asg::AnaToolHandle<TauAnalysisTools::ITauEfficiencyCorrectionsTool> m_effTool;

  }; // class TauToolWeight



  /// @brief Tool which applies the tau-truth matching.
  /// Applies the TauTruthMatchingTool from TauAnalysisTools which decorates
  /// taus with an ElementLink to their truth particle match. This ElementLink
  /// is needed for tau smearing in the TauToolCorrect. It is possible to
  /// generate the truth link in your derivations, in which case this tool
  /// is not needed.
  ///
  /// @author Steve Farrell <Steven.Farrell@cern.ch>
  ///
  class TauToolTruth : virtual public AnaTool, virtual public IAnaTool
  {

    /// This macro generates a proper constructor for Athena
    ASG_TOOL_CLASS(TauToolTruth, ana::IAnaTool)

  public:

    /// Standard constructor
    TauToolTruth(const std::string& name);

    /// @copydoc IAnaTool::setObjectType
    virtual StatusCode
    setObjectType(ObjectType type, const std::string& workingPoint) override;

    /// @copydoc IAnaTool::step
    virtual AnalysisStep step() const override;

    /// @copydoc IAnaTool::inputTypes
    virtual unsigned inputTypes() const override;
    /// @copydoc IAnaTool::outputTypes
    virtual unsigned outputTypes() const override;

    /// @brief Initialize this tool
    virtual StatusCode initialize() override;

    /// @copydoc IAnaTool::execute
    virtual StatusCode execute(IEventObjects& objects) override;

  protected:

    /// Applies truth matching to a single tau
    //virtual StatusCode matchobject(const xAOD::TauJet& tau) override;

  private:

    /// @brief Cache the last event number.
    /// Used to call the CP tool initializeEvent method only once per event.
    mutable unsigned long long m_lastEventNumber;

    // Configuration

    /// Toggle writing of tau truth container
    bool m_writeTruthTaus;

    // CP tools

    /// The tau truth-match CP tool
    asg::AnaToolHandle<TauAnalysisTools::ITauTruthMatchingTool> m_truthTool;

  }; // class TauToolTruth

} // namespace ana

#endif
