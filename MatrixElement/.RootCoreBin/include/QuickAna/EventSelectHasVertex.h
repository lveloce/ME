#ifndef QUICK_ANA__EVENT_SELECT_HAS_VERTEX_H
#define QUICK_ANA__EVENT_SELECT_HAS_VERTEX_H

//        Copyright Iowa State University 2016.
//                  Author: Nils Krumnack
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// Please feel free to contact me (nils.erik.krumnack@cern.ch) for bug
// reports, feature suggestions, praise and complaints.


#include <QuickAna/Global.h>

#include <QuickAna/AnaTool.h>
#include <QuickAna/SelectionCut.h>
#include <QuickAna/SelectionData.h>

namespace ana
{

  /// @brief An AnaTool used to initialize the EventSelect object
  ///
  class EventSelectHasVertex : virtual public AnaTool
  {
    //
    // public interface
    //

    ASG_TOOL_CLASS (EventSelectHasVertex, ana::IAnaTool)

  public:

    /// effects: standard constructor
    /// guarantee: strong
    /// failures: out of memory II
    EventSelectHasVertex (const std::string& name);

    StatusCode initialize() override;

    /// \copydoc IAnaTool::setObjectType
    virtual StatusCode
    setObjectType (ObjectType type, const std::string& workingPoint) override;

  public:
    virtual StatusCode
    useConfiguration (const InternalConfiguration& configuration)
      override;

    /// returns: the processing step we are working on
    /// guarantee: no-fail
    virtual AnalysisStep step () const override;

    /// \copydoc IAnaTool::inputTypes
    virtual unsigned inputTypes () const override;

    /// \copydoc IAnaTool::outputTypes
    virtual unsigned outputTypes () const override;

    /// effects: apply this analysis tool to the objects
    /// guarantee: basic
    /// failures: tool dependent
    virtual StatusCode execute (IEventObjects& objects) override;


    /// \brief the selection data
  private:
    SelectionData m_selection;

  private:
    SelectionCut cut_vertex;
  };
}

#endif
