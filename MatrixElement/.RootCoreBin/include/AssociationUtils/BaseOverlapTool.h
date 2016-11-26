#ifndef ASSOCIATIONUTILS_BASEOVERLAPTOOL_H
#define ASSOCIATIONUTILS_BASEOVERLAPTOOL_H

// System includes
#include <string>
#include <memory>

// Framework includes
#include "AsgTools/AsgTool.h"

// Local includes
#include "AssociationUtils/OverlapDecorationHelper.h"
#include "AssociationUtils/OverlapLinkHelper.h"

namespace ORUtils
{

  /// @class BaseOverlapTool
  /// @brief Common base class tool for overlap tools.
  ///
  /// This class was introduced to reduce the code duplication among the
  /// overlap tools. Most implementations use some common functionality such as
  /// input/output decorations, object linking, and output value logic control.
  /// This class then holds the code to handle those things, or holds the
  /// helper objects which implement the logic. It also defines the properties
  /// associated with the shared functionality.
  ///
  /// @author Steve Farrell <Steven.Farrell@cern.ch>
  ///
  class BaseOverlapTool : public asg::AsgTool
  {

      /// Create proper constructor for Athena
      ASG_TOOL_CLASS(BaseOverlapTool, asg::IAsgTool)

    public:

      /// Standalone constructor
      BaseOverlapTool(const std::string& name);

    protected:

      /// Initialize base tool functionality. Must be explicitly called by
      /// the concrete overlap tools in order to use base functionality.
      StatusCode initializeBase();

      /// @name Common configurable properties
      /// @{

      /// Input object decoration which specifies which objects to look at
      std::string m_inputLabel;
      /// Output object decoration which specifies overlapping objects
      std::string m_outputLabel;

      /// Toggle the output flag logic. If true, then non-overlapping
      /// objects will be assigned "true".
      bool m_outputPassValue;

      /// Flag to toggle overlap object links
      bool m_linkOverlapObjects;

      /// @}

      /// @name Utilities
      /// @{

      /// Helper for handling input/output decorations
      std::unique_ptr<OverlapDecorationHelper> m_decHelper;

      /// Helper for linking overlap objects
      std::unique_ptr<OverlapLinkHelper> m_objLinkHelper;

      /// @}

  }; // class BaseOverlapTool

} // namespace ORUtils

#endif
