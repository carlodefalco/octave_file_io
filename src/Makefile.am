AM_CPPFLAGS = -I$(top_srcdir)/src -I$(top_builddir)/src 
AUTOMAKE_OPTIONS = nostdinc

lib_LTLIBRARIES = liboctave_file_io.la
include_HEADERS = octave_file_io.h 
liboctave_file_io_la_SOURCES  = octave_file_io.cpp
liboctave_file_io_la_LDFLAGS  = @OCTAVE_LINK_FLAGS@
liboctave_file_io_la_CPPFLAGS = @OCTAVE_COMPILE_FLAGS@ $(AM_CPPFLAGS)
liboctave_file_io_la_LIBADD   = @OCTAVE_LINK_ADD@

