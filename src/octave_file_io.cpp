/*
  Copyright (C) 2020 Carlo de Falco
  This software is distributed under the terms
  the terms of the GNU/GPL licence v3
*/

#include <octave_file_io.h>

/*! \file octave_file_io.cpp
  \brief Classes and methods for files in Octave's (compressed) native binary file format
*/

#include <iostream>
#include <octave/parse.h>
#include <octave/load-save.h>
#include <octave/builtin-defun-decls.h>

using namespace octave;

//---------------------------------------------------------------------
//                    Static utility functions
//---------------------------------------------------------------------

static bool
check_gzip_magic (const std::string& fname)
{
  bool retval = false;
  std::ifstream file (fname.c_str ());
  unsigned char magic[2];

  if (file.read (reinterpret_cast<char *> (magic), 2) 
      && magic[0] == 0x1f 
      && magic[1] == 0x8b)

    retval = true;

  file.close ();
  return retval;
}


static bool 
fexists (const std::string& fname)
{
  std::ifstream ifile (fname.c_str ());
  return (ifile.good ());
}


//---------------------------------------------------------------------
//                Singleton class
//---------------------------------------------------------------------

class octave_file_io_intf {
  
public:

  static octave_file_io_intf* get_instance () {
    static octave_file_io_intf instance;
    return &instance;
  }
  
  octave_file_io_intf (octave_file_io_intf const&) = delete;
  void operator=(octave_file_io_intf const&)  = delete;
  
  octave::interpreter *interp;
  std::string filename;
  octave_io_mode current_mode;
  octave_value_list in, out;
  
private:

  ~octave_file_io_intf ();
  octave_file_io_intf ();
  
};

//---------------------------------------------------------------------
//                Methods in the singleton class
//---------------------------------------------------------------------

/// Singleton class providing an interface to Octave file I/O.
octave_file_io_intf::octave_file_io_intf ()  
{
  filename = "";
  current_mode = read_mode;
  interp = new octave::interpreter ( );
  int status = interp->execute ();
}

octave_file_io_intf::~octave_file_io_intf ()
{
  // FIXME : we are not shutting down and freeing the interpreter as this causes
  // a crash with Octave 6.0.91, the following should be uncommented as soon as
  // the issue is fixed, see https://savannah.gnu.org/bugs/?59228
  //interp->shutdown ();
  //delete interp;
}

//---------------------------------------------------------------------
//       Main API Functions 
//---------------------------------------------------------------------


int
octave_io_open (const char* fname, const octave_io_mode mode_in, 
                octave_io_mode *mode_out)
{
  octave_file_io_intf* io_intf = octave_file_io_intf::get_instance ();

  int retval = 0;
  *mode_out = mode_in;
  io_intf->current_mode = mode_in;
  io_intf->filename = fname;

  io_intf->out = feval ("date", io_intf->in, 1);
  
  if (mode_in == write_mode
      || mode_in == gz_write_mode)
    {
      io_intf->interp->assign ("save_date", io_intf->out(0));
      io_intf->in(0) = "-binary";
      io_intf->in(1) = io_intf->filename;
      io_intf->in(2) = "save_date";
      io_intf->interp->feval ("save", io_intf->in);
      io_intf->in.clear ();
    }
  else if (mode_in == read_mode)
    {
      if (! fexists (fname))
        retval = -1;
    }
  else if (mode_in == gz_read_mode)
    {
      if (! fexists (fname)
          || ! check_gzip_magic (fname))
        retval = -1;
    }
  return (retval);
}

int
octave_io_close (void)
{
  octave_file_io_intf* io_intf = octave_file_io_intf::get_instance ();
  if (io_intf->current_mode == gz_write_mode)
    {
      io_intf->in(0) = io_intf->filename;
      io_intf->interp->feval ("gzip", io_intf->in);
      io_intf->in.clear ();
    }
  return 0;
}

int
octave_load (const char* varname, octave_value &data)
{
  octave_file_io_intf* io_intf = octave_file_io_intf::get_instance ();
  int res = 0;

  try {
    io_intf->in(0) = io_intf->filename;
    io_intf->in(1) = varname;
    data = io_intf->interp->feval ("load", io_intf->in, 1)(0).scalar_map_value ().contents (varname);
    io_intf->in.clear ();
  } catch (octave::execution_exception& e) {
    std::cerr << "exception raised " << e.message () << std::endl;
  }
  return res;
}

int
octave_save (const char* varname, const octave_value &data)
{
  octave_file_io_intf* io_intf = octave_file_io_intf::get_instance ();
  int res = 0;

  io_intf->interp->assign (varname, data);
  
  io_intf->in(0) = "-append";
  io_intf->in(1) = "-binary";
  io_intf->in(2) = io_intf->filename;
  io_intf->in(3) = varname;
  io_intf->interp->feval ("save", io_intf->in);
  io_intf->in.clear ();
  
  return res;
}

int
octave_clear (void)
{
  // only exists to maintain backward compatibility
  int res = 0;
  return res;
}


