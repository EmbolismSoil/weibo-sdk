#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.41)
AC_INIT(libWeiboSDK, 2.0, libo.weng@gmail.com)
# AC_CONFIG_SRCDIR([include/compat.hxx])
# AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AM_INIT_AUTOMAKE
AC_PROG_RANLIB
AC_PROG_LIBTOOL

AC_SUBST([PLATFORM_NAME])
PLATFORM_NAME=$(uname)

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([arpa/inet.h float.h inttypes.h limits.h memory.h netdb.h netinet/in.h stdint.h stdlib.h string.h sys/socket.h sys/time.h sys/timeb.h syslog.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_HEADER_TIME
AC_STRUCT_TM

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_TYPE_SIGNAL
AC_FUNC_STRFTIME
AC_CHECK_FUNCS([memset strcasecmp strchr strncasecmp strrchr])

AC_OUTPUT([Makefile])
