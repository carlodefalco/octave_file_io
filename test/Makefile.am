BIMIOLIB    = ../src/liboctave_file_io.la @OCTAVE_LINK_FLAGS@ @OCTAVE_LINK_ADD@


AM_CPPFLAGS      =  -I$(top_srcdir)/src -I$(top_srcdir)/test -I$(top_builddir)/src @OCTAVE_COMPILE_FLAGS@ 
AM_LDFLAGS       = @OCTAVE_LINK_FLAGS@ 
AUTOMAKE_OPTIONS = nostdinc

CLEANFILES = 

check_PROGRAMS = io_test 

io_test_SOURCES =  io_test.cpp
io_test_CPPFLAGS =  $(AM_CPPFLAGS)
io_test_LDADD = $(BIMLIB) $(BIMIOLIB)
CLEANFILES += tmp_io_test.octbin.gz

TEST_EXTENSIONS = .m .sh .mpi
M_LOG_COMPILER = octave
SH_LOG_COMPILER = bash
MPI_LOG_COMPILER = mpiexec
AM_M_LOG_FLAGS = -q --no-gui --path $(top_srcdir)/script/m:$(top_srcdir)/data
AM_MPI_LOG_FLAGS = -np 2 

TESTS =


TESTS += io_test
