#ifndef SAMPLE_HANDLER__DQ2_H
#define SAMPLE_HANDLER__DQ2_H

//          Copyright Nils Krumnack 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// Please feel free to contact me (krumnack@iastate.edu) for bug
// reports, feature suggestions, praise and complaints.



#include <SampleHandler/Global.h>

#include <string>
#include <vector>

namespace SH
{
  /// \brief A module containing helper functions for interacting with
  /// DQ2/rucio.
  ///
  /// This is not actually a class, but just a holder of a lot of
  /// static members that can be called individually.  It's mostly a
  /// class, so that it is easy to make a dictionary for all of them.
  ///
  /// The expectation is that the typical user will not have to deal
  /// with this module directly.
  struct DQ2
  {
    /// \brief get the given dataset using dq2-get.  it will be
    ///   placed inside a directory with the same name inside the
    ///   given location.
    /// \pre (soft) !name.empty()
    /// \pre (soft) name.find('*') == std::string::npos
    /// \pre (soft) name.find('/') == std::string::npos
    /// \par Side effects
    ///   prints the output of dq2-get to the screen
    /// \par Guarantee
    ///   basic, may partially download
    /// \par Failures
    ///   out of memory II\n
    ///   location not found\n
    ///   dq2 errors
    /// \warning this function may fail silently.  you may/should run
    ///   additional checks afterwards to verify that the dataset was
    ///   correctly downloaded
    static void
    get_raw_ds (const std::string& location, const std::string& name);


    /// \copydoc get_raw_ds
    static void
    get_raw_ds (const std::string& location, const std::string& name,
		const std::vector<SH::DQ2FileInfo>& files);


    /// \brief check the size of the files in the given location
    /// \pre (soft) !name.empty()
    /// \pre (soft) name.find('*') == std::string::npos
    /// \pre (soft) name.find('/') == std::string::npos
    /// \par Guarantee
    ///   strong
    /// \par Failures
    ///   out of memory II\n
    ///   file not found or of wrong size
    static void
    get_checkSize_ds (const std::string& location,
		      const std::vector<SH::DQ2FileInfo>& files);


    /// \brief list all the datasets in the given container
    /// \pre (soft) !name.empty()
    /// \pre (soft) name.find('*') == std::string::npos
    /// \pre (soft) name.find('/') == std::string::npos
    /// \par Guarantee
    ///   strong
    /// \par Failures
    ///   out of memory III\n
    ///   dq2 errors
    static std::vector<std::string>
    listDatasetsContainer (const std::string& name);


    /// \brief list all files in the dataset
    /// \pre (soft) !name.empty()
    /// \pre (soft) name.find('*') == std::string::npos
    /// \pre (soft) name.find('/') == std::string::npos
    /// \par Guarantee
    ///   strong
    /// \par Failures
    ///   out of memory III\n
    ///   dq2 errors
    static std::vector<DQ2FileInfo>
    ls_files (const std::string& name);


    /// \brief list all files in the dataset for direct access,
    ///   replacing from with to for the access
    /// \pre (soft) !name.empty()
    /// \pre (soft) name.find('*') == std::string::npos
    /// \par Guarantee
    ///   strong
    /// \par Failures
    ///   out of memory III\n
    ///   dq2 errors
    static std::vector<std::string>
    ls_files_direct (const std::string& name, const std::string& disk,
		     const std::string& from, const std::string& to,
		     unsigned& available, unsigned& total);


    /// \brief the name of the variable containing the local
    ///   cache area
    static const std::string local_area_var;

    /// \brief the name of the file suffix, for the file
    ///   accompanying a complete dataset
    static const std::string local_complete_suffix;


    /// \brief the local cache area
    /// \par Guarantee
    ///   strong
    /// \par Failures
    ///   out of memory II\n
    ///   local cache area not defined
    static std::string local_area ();


    /// \brief: whether the given sample is completely existant in
    ///   the cache area
    /// \pre (soft) !name.empty()
    /// \pre (soft) name.find('*') == std::string::npos
    /// \pre (soft) name.find('/') == std::string::npos
    /// \par Guarantee
    ///   strong
    /// \par Failures
    ///   out of memory II\n
    ///   i/o errors\n
    ///   local cache area not defined
    static bool local_cached (const std::string& name);


    /// \brief the list of files in the given dataset present in the
    ///   cache area
    /// \pre (soft) !name.empty()
    /// \pre (soft) name.find('*') == std::string::npos
    /// \pre (soft) name.find('/') == std::string::npos
    /// \pre (soft) local_cached (name)
    /// \par Guarantee
    ///   strong
    /// \par Failures
    ///   out of memory II\n
    ///   i/o errors\n
    ///   local cache area not defined
    static std::vector<std::string>
    local_sample_ds_files (const std::string& name,
			   const std::string& filter);


    /// \brief access the given dataset in the local cache area,
    ///   downloading it if necessary.  if allowFax is set to true and
    ///   FAX is present it may also be used.
    /// \return the list of files
    /// \pre (soft) !name.empty()
    /// \pre (soft) name.find('*') == std::string::npos
    /// \pre (soft) name.find('/') == std::string::npos
    /// \post: result != 0
    /// \par Guarantee
    ///   basic, may download partially
    /// \par Failures
    ///   out of memory III\n
    ///   local cache area not defined\n
    ///   dq2 errors
    static std::vector<std::string>
    local_sample_ds (const std::string& name,
		     const std::string& filter, bool allowFax);


    /// \brief access the given dataset or container in the local
    ///   cache area, downloading it if necessary.  if allowFax is set
    ///   to true and FAX is present it may also be used.
    /// \return the list of files
    /// \pre (soft) !name.empty()
    /// \pre (soft) name.find('*') == std::string::npos
    /// \post result != 0
    /// \par Guarantee
    ///   basic, may download partially
    /// \par Failures
    ///   out of memory III\n
    ///   local cache area not defined\n
    ///   dq2 errors
    static std::vector<std::string>
    local_sample (const std::string& name,
		  const std::string& filter, bool allowFax);
  };
}

#endif
