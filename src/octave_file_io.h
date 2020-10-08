/*
  Copyright (C) 2020 Carlo de Falco
  This software is distributed under the terms
  the terms of the GNU/GPL licence v3
*/

#ifndef OCTAVE_FILE_IO_H
# define OCTAVE_FILE_IO_H

#include <iostream>
#include <octave/oct.h>
#include <octave/octave.h>

//---------------------------------------------------------------------
//                Singleton class
//---------------------------------------------------------------------

// Do not export the singleton class definition
// and other symbols that are not to be used elsewhere.

//---------------------------------------------------------------------
//                API Functions
//---------------------------------------------------------------------

enum octave_io_mode 
  {
    read_mode = 0,
    gz_read_mode = 1,
    write_mode = 2,
    gz_write_mode = 3
  };

int
octave_io_open (const char*, const octave_io_mode, octave_io_mode*);

int
octave_io_close (void);

int 
octave_load (const char*, octave_value&);

int 
octave_save (const char*, const octave_value&);

int
octave_clear (void);

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

#endif
