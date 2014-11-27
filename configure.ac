#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([OpenGLWorks], [0.1.1], [newserver002@gmail.com])
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([c1-1/c1-1.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC

# Checks for HostOS
case "$host" in
        *-*-mingw*|*-*-cygwin*)
                AC_DEFINE(PLATFORM_WIN32, 1, [Platform is Win32])
                PLATFORM_STRING="Win32"
		AC_SUBST(PLATFORM_STRING)
                ;;
        *-*-linux*)
                AC_DEFINE(PLATFORM_LINUX, 1, [Platform is Linux])
                PLATFORM_STRING="Linux"
		AC_SUBST(PLATFORM_STRING)
                ;;
        *-*-darwin*)
                AC_DEFINE(PLATFORM_APPLE, 1, [Platform is Apple])
                PLATFORM_STRING="Apple"
		AC_SUBST(PLATFORM_STRING)
                ;;
        *-*-*bsd*)
                AC_DEFINE(PLATFORM_BSD, 1, [Platform is BSD])
                PLATFORM_STRING="BSD"
		AC_SUBST(PLATFORM_STRING)
                ;;
        *)
                AC_MSG_WARN([*** Please add $host to configure.ac checks!])
                ;;
esac

# Checks for libraries.
if test "$PLATFORM_STRING" = "Apple"; then
   if hash port 2>/dev/null; then
      CFLAGS="$CFLAGS -I/opt/local/include";
      CXXFLAGS="$CXXFLAGS -I/opt/local/include";
      CPPFLAGS="$CPPFLAGS -I/opt/local/include";
      LIBS="$LIBS -L/opt/local/lib"
   fi
fi

# Checks for header files.
AC_CHECK_HEADERS([GL/glut.h], 
	     	 [AC_DEFINE(HAVE_GL_GLUT_H)], 
		 [AC_MSG_ERROR([ERROR: Please install GL/glut.h])])

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
LDFLAGS="$GL_LDFLAGS $GLU_LDFLAGS $GLUT_LDFLAGS"

AC_CONFIG_FILES([Makefile
                 c1-1/Makefile
                 c1-2/Makefile
                 cube/Makefile
                 oct/Makefile
                 round/Makefile
		 vertex-array/Makefile])
AC_OUTPUT
