/*
  Copyright (C) 2015,2016,2017,2019 Carlo de Falco
  This software is distributed under the terms
  the terms of the GNU/GPL licence v3
*/

#include <iostream>
#include <octave_file_io.h>
#include <cassert>

int
main ()
{

  
  std::vector<octave_idx_type>      n;
  std::vector<double>               x;
 
  n.resize (10);
  x.resize (10);
            
  // fill in local entries
  for (int ii = 0; ii < 10; ++ii)
    { n[ii] = ii; x[ii] = ii * 0.1413; };

  // save data to file
  ColumnVector oct_x (x.size (), 0.0);
  Array<octave_idx_type> oct_n (dim_vector (n.size (), 1), 0);

  std::copy_n (x.begin (), x.size (), oct_x.fortran_vec ());
  std::copy_n (n.begin (), n.size (), oct_n.fortran_vec ());

  octave_scalar_map the_map;
  the_map.assign ("x", oct_x);
  the_map.assign ("n", oct_n);

  octave_io_mode m = gz_write_mode, mm;
  assert (octave_io_open ("tmp_io_test.octbin", m, &mm) == 0);
  assert (octave_save ("the_map", octave_value (the_map)) == 0);
  assert (octave_io_close () == 0);
  
  // load data from file and print
  octave_value tmp;
  m = gz_read_mode;
  assert (octave_io_open ("tmp_io_test.octbin.gz", m, &m) == 0);
  assert (octave_load ("the_map", tmp) == 0);
  std::cout << "data loaded" << std::endl;

  ColumnVector x_new;
  Array<octave_idx_type> n_new;
  try {
    x_new = tmp.scalar_map_value ().contents ("x").column_vector_value ();
    n_new = tmp.scalar_map_value ().contents ("n").column_vector_value ();   
  
  } catch (octave::execution_exception& e) {
    std::cerr << "exception your honour!" << e.message () << std::endl;
  }

  for (int ii = 0; ii < x_new.numel (); ++ii)
    //   //assert (x_new(ii) == x[ii]);
    std::cout << "x_new(" << ii<< ") = " << x_new(ii)
              << " x[" << ii<< "] = " << x[ii] << std::endl;
      
  for (int ii = 0; ii < n_new.numel (); ++ii)
    //assert (n_new(ii) == n[ii]);
    std::cout << "n_new(" << ii<< ") = " << n_new(ii)
              << " n[" << ii<< "] = " << n[ii] << std::endl;

  assert (octave_io_close () == 0);
   
  std::cerr << "shut down!" << std::endl;
  return 0;
}
