AC_INIT([zoo], [2.11-rc1],,, [https://github.com/troglobit/zoo/])
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
AC_CHECK_FUNC([nftw],
	AC_DEFINE([HAVE_NFTW], [1], [System has nftw(), we can add recursively.]))

AC_ARG_ENABLE([fiz],
	AS_HELP_STRING([--enable-fiz], [enable zoo archive repair utility tool]),,
	enable_fiz=no)
AC_ARG_ENABLE([ooz],
	AS_HELP_STRING([--enable-ooz], [enable legacy ooz unarchiver, same as unzoo/booz]),,
	enable_ooz=no)
AC_ARG_ENABLE([unzoo],
	AS_HELP_STRING([--disable-unzoo], [disable unzoo, standard zoo unarchiver tool]),,
	enable_unzoo=yes)
AM_CONDITIONAL([ENABLE_FIZ],   [test "x$enable_fiz"    = "xyes"])
AM_CONDITIONAL([ENABLE_OOZ],   [test "x$enable_ooz"    = "xyes"])
AM_CONDITIONAL([ENABLE_UNZOO], [test "x$enable_unzoo" != "xno"])

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

cat <<EOF

------------------ Summary ------------------
 $PACKAGE_NAME version $PACKAGE_VERSION
  Prefix................: $prefix
  Sysconfdir............: `eval echo $sysconfdir`
  Localstatedir.........: `eval echo $localstatedir`
  C Compiler............: $CC $CFLAGS $CPPFLAGS $LDFLAGS $LIBS

Optional features:
  fiz...................: $enable_fiz
  ooz...................: $enable_ooz
  unzoo.................: $enable_unzoo

------------- Compiler version --------------
$($CC --version || true)
---------------------------------------------

Check the above options and compile with:
 ${MAKE-make}

EOF
