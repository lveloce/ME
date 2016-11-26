#ifndef SAMPLE_HANDLER__DQ2_FILE_INFO_H
#define SAMPLE_HANDLER__DQ2_FILE_INFO_H

//          Copyright Nils Krumnack 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// Please feel free to contact me (krumnack@iastate.edu) for bug
// reports, feature suggestions, praise and complaints.



#include <SampleHandler/Global.h>

#include <string>
#include <Rtypes.h>

namespace SH
{
  /// \brief this class contains the information about a single file
  ///   managed by DQ2/rucio.
  ///
  /// This class is mostly used by the DQ2 module.
  /// \relates DQ2
  struct DQ2FileInfo
  {
    /// \brief the name of the file
  public:
    std::string name;

    /// \brief the size of the file or -1 if it is not known
  public:
    Long64_t size;


    /// \brief standard constructor
    ///
    /// \par Guarantee
    ///   no-fail
  public:
    DQ2FileInfo ();
  };
}

#endif
