#ifndef SAMPLE_HANDLER__DISK_WRITER_LOCAL_H
#define SAMPLE_HANDLER__DISK_WRITER_LOCAL_H

//        Copyright Iowa State University 2013.
//                  Author: Nils Krumnack
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// Please feel free to contact me (nils.erik.krumnack@cern.ch) for bug
// reports, feature suggestions, praise and complaints.



#include <SampleHandler/Global.h>

#include <SampleHandler/DiskWriter.h>

namespace SH
{
  /// \brief an implementation of DiskWriter for local files
  /// \sa DiskOutputLocal
  class DiskWriterLocal : public DiskWriter
  {
    //
    // public interface
    //

    /// \brief test the invariant of this object
    ///
    /// \par Guarantee
    ///   no-fail
  public:
    void testInvariant () const;


    /// \brief standard constructor
    ///
    /// \par Guarantee
    ///   strong
    /// \par Failures
    ///   out of memory I
    /// \pre !val_path.empty()
  public:
    DiskWriterLocal (const std::string& val_path);


    /// \brief standard destructor
    ///
    /// \par Guarantee
    ///   no-fail
  public:
    ~DiskWriterLocal ();



    //
    // inherited interface
    //

    /// \copydoc DiskWriter::getPath()
  private:
    virtual std::string getPath () const;


    /// \copydoc DiskWriter::getFile()
  private:
    virtual TFile *getFile ();


    /// \copydoc DiskWriter::doClose()
  private:
    virtual void doClose ();



    //
    // private interface
    //

    /// \brief the path being used
  private:
    std::string m_path;

    /// \brief the actual file object
  private:
    TFile *m_file;
  };
}

#endif
