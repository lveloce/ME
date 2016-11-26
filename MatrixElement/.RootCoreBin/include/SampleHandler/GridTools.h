#ifndef SAMPLE_HANDLER__GRID_TOOLS_H
#define SAMPLE_HANDLER__GRID_TOOLS_H

//          Copyright Nils Krumnack 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// Please feel free to contact me (nils.erik.krumnack@iastate.edu) for
// bug reports, feature suggestions, praise and complaints.



#include <SampleHandler/Global.h>

#include <AsgTools/MessageCheck.h>
#include <map>
#include <memory>
#include <set>
#include <vector>

namespace SH
{
  ANA_MSG_HEADER (msgGridTools)

  /// \brief return whether we have a valid VOMS proxy available
  /// \par Guarantee
  ///   basic
  /// \par Failures
  ///   grid utility failures
  bool checkVomsProxy ();


  /// \brief ensure that we have a valid VOMS proxy available
  ///
  /// First this checks whether we have a valid PROXY, and if not it
  /// sets up a new certificate.
  ///
  /// \par Guarantee
  ///   basic
  /// \par Failures
  ///   grid utility failures\n
  ///   failure to set up new VOMS proxy
  void ensureVomsProxy ();


  /// \brief list the FAX URLs for all the files in the dataset or
  /// dataset container matching the given filter (as glob expression)
  /// \par Guarantee
  ///   strong
  /// \par Failures
  ///   grid utility failures
  /// \pre !name.empty()
  /// \pre name.find('*') == std::string::npos
  /// \pre !filter.empty()
  std::vector<std::string>
  faxListFilesGlob (const std::string& name, const std::string& filter);


  /// \brief list the FAX URLs for all the files in the dataset or
  /// dataset container matching the given filter (as regular
  /// expression)
  /// \par Guarantee
  ///   strong
  /// \par Failures
  ///   grid utility failures
  /// \pre !name.empty()
  /// \pre name.find('*') == std::string::npos
  /// \pre !filter.empty()
  std::vector<std::string>
  faxListFilesRegex (const std::string& name, const std::string& filter);


  /// \brief one entry from the rucio-list-dids command
  struct RucioListDidsEntry
  {
    /// \brief the scope
    std::string scope;

    /// \brief the name
    std::string name;

    /// \brief the type
    std::string type;
  };

  /// \brief run rucio-list-dids for the given dataset
  /// \par Guarantee
  ///   strong
  /// \par Failures
  ///   grid utility failures
  /// \pre !dataset.empty()
  std::vector<RucioListDidsEntry> rucioListDids (const std::string& dataset);


  /// \brief run rucio-get-metadata for the given list of datasets
  /// \par Guarantee
  ///   strong
  /// \par Failures
  ///   grid utility failures
  /// \pre !datasets.empty()
  /// \pre !dataset.empty() (for each dataset)
  std::map<std::string,std::unique_ptr<MetaObject> >
  rucioGetMetadata (const std::set<std::string>& datasets);
}

#endif
