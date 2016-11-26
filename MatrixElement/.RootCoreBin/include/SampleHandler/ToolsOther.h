#ifndef SAMPLE_HANDLER__TOOLS_OTHER_H
#define SAMPLE_HANDLER__TOOLS_OTHER_H

//        Copyright Iowa State University 2015.
//                  Author: Nils Krumnack
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// Please feel free to contact me (nils.erik.krumnack@cern.ch) for bug
// reports, feature suggestions, praise and complaints.


#include <SampleHandler/Global.h>

#include <memory>

class TFile;

namespace SH
{
  /// \brief open a file with the given options
  ///
  /// for now this is to allow opening files with retries, but in the
  /// future there may be other options as well.
  /// \par Guarantee
  ///   strong
  /// \par Failures
  ///   i/o errors\n
  ///   file not found
  /// \post result != nullptr
  std::unique_ptr<TFile>
  openFile (const std::string& name, const MetaObject& options);
}

#endif
