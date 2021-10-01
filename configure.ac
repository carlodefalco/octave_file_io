#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([octave_file_io], [1.0.91], [carlo.defalco@polimi.it])
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_SRCDIR([src/octave_file_io.cpp])
AC_CONFIG_HEADERS([src/ofio_config.h])

AM_INIT_AUTOMAKE([subdir-objects])

# Init libtool.
LT_PREREQ([2.2.2])
LT_INIT([disable-static dlopen])
AC_SUBST([LIBTOOL_DEPS])


# Checks for programs.
AC_PROG_CXX


AC_LANG_PUSH([C++])
AC_ARG_WITH([octave-home],
            [AS_HELP_STRING([--with-octave-home=DIR],
            [Select the directory where octave mkoctfile is contained.])],
            [OCTAVE_HOME=$withval],
            [OCTAVE_HOME=/usr/bin])


OCTAVE_BINDIR="$OCTAVE_HOME"

AC_PATH_PROG([OCTAVE_MKOCTFILE], [mkoctfile], [], ["${OCTAVE_BINDIR}"])

if [ test "${OCTAVE_MKOCTFILE}" != ""]; then

# use mkoctfile to get info on octave flags
   AC_SUBST(OCTAVE_COMPILE_FLAGS, "$(env -i PATH=$PATH LD_LIBRARY_PATH=$LD_LIBRARY_PATH DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH ${OCTAVE_MKOCTFILE} --link-stand-alone -p INCFLAGS) \
$(env -i PATH=$PATH LD_LIBRARY_PATH=$LD_LIBRARY_PATH DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH ${OCTAVE_MKOCTFILE} --link-stand-alone -p CPPFLAGS) \
$(env -i PATH=$PATH LD_LIBRARY_PATH=$LD_LIBRARY_PATH DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH ${OCTAVE_MKOCTFILE} --link-stand-alone -p CXXPICFLAG) \
$(env -i PATH=$PATH LD_LIBRARY_PATH=$LD_LIBRARY_PATH DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH ${OCTAVE_MKOCTFILE} --link-stand-alone -p ALL_CXXFLAGS)")
   AC_SUBST(OCTAVE_LINK_FLAGS, "$(env -i PATH=$PATH LD_LIBRARY_PATH=$LD_LIBRARY_PATH DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH ${OCTAVE_MKOCTFILE} --link-stand-alone -p ALL_CXXFLAGS) \
$(env -i PATH=$PATH LD_LIBRARY_PATH=$LD_LIBRARY_PATH DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH ${OCTAVE_MKOCTFILE} --link-stand-alone -p RDYNAMIC_FLAG) \
$(env -i PATH=$PATH LD_LIBRARY_PATH=$LD_LIBRARY_PATH DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH ${OCTAVE_MKOCTFILE} --link-stand-alone -p LDFLAGS)")
   AC_SUBST(OCTAVE_LINK_ADD, "$(env -i PATH=$PATH LD_LIBRARY_PATH=$LD_LIBRARY_PATH DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH ${OCTAVE_MKOCTFILE} --link-stand-alone -p LDFLAGS) \
-L$(env -i PATH=$PATH LD_LIBRARY_PATH=$LD_LIBRARY_PATH DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH ${OCTAVE_MKOCTFILE} --link-stand-alone -p OCTLIBDIR) \
$(env -i PATH=$PATH LD_LIBRARY_PATH=$LD_LIBRARY_PATH DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH ${OCTAVE_MKOCTFILE} --link-stand-alone -p OCTAVE_LIBS) \
$(env -i PATH=$PATH LD_LIBRARY_PATH=$LD_LIBRARY_PATH DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH ${OCTAVE_MKOCTFILE} --link-stand-alone -p LAPACK_LIBS) \
$(env -i PATH=$PATH LD_LIBRARY_PATH=$LD_LIBRARY_PATH DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH ${OCTAVE_MKOCTFILE} --link-stand-alone -p BLAS_LIBS) \
$(env -i PATH=$PATH LD_LIBRARY_PATH=$LD_LIBRARY_PATH DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH ${OCTAVE_MKOCTFILE} --link-stand-alone -p FFTW_LIBS) \
$(env -i PATH=$PATH LD_LIBRARY_PATH=$LD_LIBRARY_PATH DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH ${OCTAVE_MKOCTFILE} --link-stand-alone -p LIBREADLINE) \
$(env -i PATH=$PATH LD_LIBRARY_PATH=$LD_LIBRARY_PATH DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH ${OCTAVE_MKOCTFILE} --link-stand-alone -p LIBS) \
$(env -i PATH=$PATH LD_LIBRARY_PATH=$LD_LIBRARY_PATH DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH ${OCTAVE_MKOCTFILE} --link-stand-alone -p FLIBS) \
")
else
   AC_MSG_WARN([You do not seem to have a complete install of Octave on your computer.])
fi


AC_LANG_POP([C++])



# Checks for typedefs, structures, and compiler characteristics.


# Checks for library functions.


AC_CONFIG_FILES([Makefile
                 src/Makefile
                 test/Makefile])
                 
AC_OUTPUT
