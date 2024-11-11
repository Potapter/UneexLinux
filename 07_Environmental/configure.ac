#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([rhasher], [0.00], [])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_CONFIG_SRCDIR([src/rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash],[rhash_library_init],[],[AC_MSG_ERROR([Rhash is needed])])
AC_CHECK_LIB([readline], [readline])

# Checks for header files.
AC_CHECK_HEADER([rhash.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE

# Optional clues
AC_ARG_ENABLE([readline],
    AS_HELP_STRING([--enable-readline], [Enable readline input]),
    AC_DEFINE(READLINE,[],[Readline])
)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
