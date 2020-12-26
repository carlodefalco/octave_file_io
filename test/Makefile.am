BIMIOLIB    = ../src/liboctave_file_io.la @OCTAVE_LINK_FLAGS@ @OCTAVE_LINK_ADD@


AM_CPPFLAGS      =  -I$(top_srcdir)/src -I$(top_srcdir)/test -I$(top_builddir)/src @OCTAVE_COMPILE_FLAGS@ 
AM_LDFLAGS       = @OCTAVE_LINK_FLAGS@ 
AUTOMAKE_OPTIONS = nostdinc

CLEANFILES = 

check_PROGRAMS = io_test io_test_par.mpi

io_test_SOURCES =  io_test.cpp
io_test_CPPFLAGS =  $(AM_CPPFLAGS)
io_test_LDADD = $(BIMLIB) $(BIMIOLIB)
CLEANFILES += tmp_io_test.octbin.gz tmp_io_test.octbin

io_test_par_mpi_SOURCES =  io_test_par.cpp
io_test_par_mpi_CPPFLAGS =  $(AM_CPPFLAGS)
io_test_par_mpi_LDADD = $(BIMLIB) $(BIMIOLIB)
CLEANFILES += tmp_io_test_par.octbin.gz tmp_io_test_par.octbin

TEST_EXTENSIONS = .m .sh .mpi
M_LOG_COMPILER = octave
SH_LOG_COMPILER = bash
MPIEXEC ?= mpiexec
MPI_LOG_COMPILER = $(MPIEXEC)
AM_M_LOG_FLAGS = -q --no-gui --path $(top_srcdir)/script/m:$(top_srcdir)/data
AM_MPI_LOG_FLAGS = -np 2 

TESTS =

TESTS += io_test io_test_par.mpi
