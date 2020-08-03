AC_INIT([zoo], [2.11-beta1],,, [https://github.com/troglobit/zoo/])
AC_CONFIG_AUX_DIR(build-aux)
AM_INIT_AUTOMAKE([1.11 foreign])
AM_SILENT_RULES([yes])

AC_CONFIG_SRCDIR([src/zoo.c])
AC_CONFIG_HEADER([src/config.h])
AC_CONFIG_FILES([Makefile man/Makefile src/Makefile test/Makefile])

AC_PROG_CC
AC_PROG_INSTALL

AC_HEADER_STDC
AC_CHECK_HEADERS

AC_CANONICAL_HOST
case $host in
  *-linux*)
    MACHINE=-DLINUX
    SYS=-DSYS_IS_UNIX
    ;;
  *-freebsd* | *-openbsd* | *-netbsd* | *-dragonfly* | *-solaris* | *-apple*)
    MACHINE=-DBSD4_3
    SYS=-DSYS_IS_UNIX
    ;;
  *)
    AC_MSG_WARN(Your operating system is not officially supported yet by zoo.)
    AC_MSG_WARN(Set MACHINE=foo manually to one of: ULTRIX, SYS_V, or GENERIC)
    ;;
esac
AC_SUBST(MACHINE)
AC_SUBST(SYS)

AC_OUTPUT
