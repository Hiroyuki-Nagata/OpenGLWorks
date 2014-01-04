#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([OpenGLWorks], [0.1.1], [newserver002@gmail.com])
AM_INIT_AUTOMAKE([])
AC_CONFIG_SRCDIR([c1-1/c1-1.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

#
# Checks for library functions.
#

# Checks for m
AC_CHECK_LIB(m, exp, LIBS="-lm $LIBS" has_m=1,has_m=0)
if test $has_m = 0; then
   AC_MSG_ERROR("ERROR: cannot find libm.")
fi

# Checks for gl
AX_CHECK_GL()
# Checks for glu
AX_CHECK_GLU()
# Checks for glut
AX_CHECK_GLUT()

# Add Flags
CFLAGS="-std=c11 $CFLAGS $GL_CFLAGS $GLU_CFLAGS $GLUT_CFLAGS"
LIBS="$LIBS $GL_LIBS $GLU_LIBS $GLUT_LIBS"

AC_CONFIG_FILES([Makefile
                 c1-1/Makefile
                 c1-2/Makefile
                 oct/Makefile
                 round/Makefile])
AC_OUTPUT
