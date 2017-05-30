#
# Libnet autoconfiguration information file
# Copyright (c) 1998 - 2002 Mike D. Schiffman <mike@infonexus.com>
# Modified by Ali Abdulkadir <autostart.ini@gmail.com>
# All rights reserved.
#
# Process this file with autoconf to produce a configure script.

# First things first:
# Set and worry about package and library version here
# (and HERE only)

define([PACKAGE_VERSION_MAJOR], [1])
define([PACKAGE_VERSION_MINOR], [2])
define([PACKAGE_VERSION_PATCH], [0])
define([PACKAGE_VERSION_NANO], [0])
define([PACKAGE_SUFFIX], [-rc3])

define([LN_CURRENT], [9])
define([LN_REVISION], [0])
define([LN_AGE], [0])

# Package versioning note:
# ========================
# If libnet package version logic has not already, it will follow the so-called
# Semantic Versioning Specification (SemVer)
# See this if you have no idea what that means:
#   http://semver.org/
#
# This means that PACKAGE_VERSION_PATCH may NOT be omitted from version string
# even if set to 0.
# PACKAGE_VERSION_NANO may be used for Windows internal versioning.
# 0 means unused.
# PACKAGE_SUFFIX may be things like "-rc", "-alpha", "-beta" ect.
# Leave blank if none of this applies.
#
# Library versioning note:
# ========================
# The library version should NOT simply be the version of the libnet package.
# See:
#   https://www.sourceware.org/autobook/autobook/autobook_61.html#Library-Versioning
#   http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
# for the rules.
#
# Library versioning history:
# 1.1.2.1-fork is 5:0:4
# 1.1.3 will be 6:0:5  -> new interfaces, backwards compatible
# 1.1.4 was 6:0:5 -> probably an error on my part
# 1.1.5 is 7:0:6 -> new APIs, backwards compatible
# 1.1.6 is 8:0:7 -> new APIs, backwards compatible
# 1.2.0 is 9:0:0 -> new APIs, removed __libnet_print_vers (internal, should not have been used, but linkable) APIs


AC_INIT(
    [libnet],
    [PACKAGE_VERSION_MAJOR.PACKAGE_VERSION_MINOR.PACKAGE_VERSION_PATCH[]PACKAGE_SUFFIX],
    [https://github.com/sgeto/libnet/issues],
    [libnet],
    [https://github.com/sgeto/libnet])

AC_CONFIG_AUX_DIR([build-aux])

# the autotools and libtool should be at least these versions
AC_PREREQ([2.69])
LT_PREREQ([2.4.2])

AC_COPYRIGHT([Copyright 1998 - 2017 The libnet Developer Community])
AS_BOX([            Configuring AC_PACKAGE_TARNAME AC_PACKAGE_VERSION            ])
echo

AC_PROG_SHELL
AC_CANONICAL_TARGET
AC_CONFIG_SRCDIR([src/libnet_build_ip.c])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([1.14 foreign no-dependencies nostdinc tar-pax dist-zip])
AM_SILENT_RULES([yes])
AC_CONFIG_HEADERS([include/config.h])

# no default compiler flags.
: ${CFLAGS=""}

# To speed up the configure process on Windows, we will define a WIN32
# variable this early and use it to exclude those checks that are not​
# needed or will always fail on Windows.

case "$target_os" in
*mingw*)
    WIN32=yes;;
*)
    WIN32=no;;
esac

AC_SUBST(WIN32)
AM_CONDITIONAL([WIN32], [test "$WIN32" = "yes"])

# Check for the usual programs
AC_PROG_CC
AC_PROG_INSTALL
AC_USE_SYSTEM_EXTENSIONS
AX_COMPILER_VENDOR
AX_COMPILER_VERSION

# The default is to use only PIC objects.
# This can still be overwritten with --without-pic
LT_INIT([pic-only win32-dll])
AC_SUBST(LT_VERSION, [LN_CURRENT:LN_REVISION:LN_AGE])

if test "$WIN32" != yes ; then
AC_CHECK_HEADERS(sys/sockio.h)
AC_CHECK_FUNCS([gethostbyname2])
AC_CHECK_FUNCS([getifaddrs])
fi
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T

if test "$WIN32" != yes ; then
AC_MSG_CHECKING(for socklen_t)
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
        #include <sys/types.h>
        #include <sys/socket.h>
        ]], [[ socklen_t x; ]])],[have_socklen_t=yes],[have_socklen_t=no])
if test "x$have_socklen_t" = "xyes"; then
        AC_DEFINE(HAVE_SOCKLEN_T, 1, [define if socklen_t is defined])
fi
AC_MSG_RESULT($have_socklen_t)
fi

#
# And some custom things
#

AC_LIBNET_ENDIAN_CHECK
# AC_LBL_LIBRARY_NET
AC_SUBST(ENDIANESS)

# check if this is any good
#if test "$WIN32" != yes ; then
AC_SUBST(HAVE_PACKET_SOCKET)
#fi
AC_SUBST(ADDITIONAL_LIBS)
AC_SUBST(LIBNET_CONFIG_DEFINES)
AC_SUBST(LIBNET_CONFIG_LIBS)
# FIXME this variable is unused
AC_SUBST(LIBNET_CONFIG_CFLAGS)
AC_SUBST(LTLIBOBJS)


# Guess the root install directory (if none is provided)
if test "${prefix}" = "NONE"; then
    if test -w /usr/local; then
        prefix=/usr/local
    else
        AC_PREFIX_PROGRAM($CC)
    fi
fi

if test "${exec_prefix}" = "NONE"; then
    exec_prefix=$prefix
fi
# libdir and includedir must be fully qualified paths (not ${prefix}/lib)
eval libdir="$libdir"
eval includedir="$includedir"

# Get link-layer interface type
AC_ARG_WITH(
	[link-layer],
	[AS_HELP_STRING([--with-link-layer],[when cross-compiling, one of * from libnet_link_*.c @<:@autodetect@:>@])]
)

if test "$WIN32" != yes ; then
AC_CHECK_HEADERS([net/pfilt.h sys/net/nit.h net/raw.h sys/dlpi.h linux/socket.h])
fi

AC_MSG_CHECKING(link-layer packet interface type)

if test -n "${with_link_layer}"; then
    case "${with_link_layer}" in
        bpf)   AC_LIBOBJ([libnet_link_bpf]) ;;
        pf)    AC_LIBOBJ([libnet_link_pf]) ;;
        snit)  AC_LIBOBJ([libnet_link_snit]) ;;
        nit)   AC_LIBOBJ([libnet_link_nit]) ;;
        snoop) AC_LIBOBJ([libnet_link_snoop]) ;;
        dlpi)  AC_LIBOBJ([libnet_link_dlpi]) ;;
        win32) AC_LIBOBJ([libnet_link_win32]) ;;
        none)  AC_LIBOBJ([libnet_link_none]) ;;
        linux) AC_LIBOBJ([libnet_link_linux])
           AC_LIBNET_CHECK_PF_PACKET
           AC_LIBNET_LINUX_PROCFS ;;
        none) AC_LIBOBJ([libnet_link_none]) ;;
        *) AC_MSG_ERROR([Invalid link type "${with_link_layer}"]) ;;
    esac
    AC_MSG_RESULT(user selected link layer ${with_link_layer})
elif test "${cross_compiling}" != "yes" -a -r /dev/bpf0 ; then
    AC_LIBOBJ([libnet_link_bpf])
    AC_MSG_RESULT(found link layer bpf)
elif test "${ac_cv_header_net_pfilt_h}" = "yes" ; then
    AC_LIBOBJ([libnet_link_pf])
    AC_MSG_RESULT(found link layer pf)
elif test "${cross_compiling}" != "yes" -a -r /dev/nit ; then
    AC_LIBOBJ([libnet_link_snit])
    AC_MSG_RESULT(found link layer snit)
elif test "${ac_cv_header_sys_net_nit_h}" = "yes" ; then
    AC_LIBOBJ([libnet_link_nit])
    AC_MSG_RESULT(found link layer nit)
elif test "${ac_cv_header_net_raw_h}" = "yes" ; then
    AC_LIBOBJ([libnet_link_snoop])
    AC_MSG_RESULT(found link layer snoop)
elif test "${ac_cv_header_sys_dlpi_h}" = "yes" ; then
    AC_LIBOBJ([libnet_link_dlpi])
    AC_MSG_RESULT(found link layer dlpi)
    AC_DEFINE(HAVE_DLPI, 1, [Define if the <sys/dlpi.h> header exists.])
elif test "${ac_cv_header_linux_socket_h}" = "yes" ; then
    AC_LIBOBJ([libnet_link_linux])
    AC_MSG_RESULT(found link layer linux)
    AC_LIBNET_CHECK_PF_PACKET
    AC_LIBNET_LINUX_PROCFS
elif test "${cross_compiling}" != "yes" -a -c /dev/bpf0 ; then           # check again in case not readable
    AC_LIBOBJ([libnet_link_bpf])
    AC_MSG_RESULT(found link layer bpf)
elif test "${cross_compiling}" != "yes" -a -c /dev/nit ; then            # check again in case not readable
    AC_LIBOBJ([libnet_link_snit])
    AC_MSG_RESULT(found link layer snit)
elif test "$target_os" = "cygwin" ; then
    AC_LIBOBJ([libnet_link_win32])
    AC_MSG_RESULT(found link layer win32 wpcap)
elif test "$host" = "i686-w64-mingw32" -o "x86_64-w64-mingw32" -o "x86_64-pc-mingw64"; then
    AC_LIBOBJ([libnet_link_win32])
    AC_MSG_RESULT(found link layer win32 @<:@WinPcap@:>@)
else
    AC_LIBOBJ([libnet_link_none])
    AC_MSG_WARN(could not find a link-layer packet interface)
    AC_MSG_WARN(link-layer packet injection will not be available)
fi

# This is necessary so that .o files in LIBOBJS are also built via
# the ANSI2KNR-filtering rules.
# FIXME Isn't this nowadays already taken care of by AC_PROG_CC?
LIB@&t@OBJS=`echo "$LIB@&t@OBJS" |
       sed 's,\.[[^.]]* ,$U&,g;s,\.[[^.]]*$,$U&,'`
LTLIBOBJS=`echo "$LIB@&t@OBJS" |
       sed 's,\.[[^.]]* ,.lo ,g;s,\.[[^.]]*$,.lo,'`

link_layer=`"echo"${LTLIBOBJS}"" | cut -c 13- | awk -F$ '/U.lo/ {print $1}'`

# Inform user about the packet builders we've got
echo -n "scanning available packet construction modules: "
for dir in src/*build*c ; do
    echo $dir | sed -e /src\\/libnet_build_/s/// | sed -e /\\.c/s/// | tr \\n \\040
done
echo ""

# # Check for Doxygen and enable its features
# # See m4/ax_prog_doxygen.m4
DX_DOXYGEN_FEATURE(OFF)
DX_DOT_FEATURE(ON)
DX_HTML_FEATURE(ON)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(ON)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(ON)
DX_PS_FEATURE(OFF)
DX_INIT_DOXYGEN(${PACKAGE_NAME}, [doc/libnet.doxygen.conf], [doc])
AM_CONDITIONAL(ENABLE_DOXYGEN,[test "x${DX_FLAG_doc}" = x1])

if test ${DX_FLAG_doc} -eq 1; then
    rebuild_docs=yes
else
    rebuild_docs=no
fi

# Check for sample building
AC_MSG_CHECKING([whether to build sample programs])
AC_ARG_ENABLE([samples],
    [AS_HELP_STRING([--disable-samples],[do not build sample programs @<:@default=no@:>@])],
    [enable_samples=$enableval],
    [enable_samples=yes]
)
AC_MSG_RESULT([$enable_samples])

AM_CONDITIONAL([ENABLE_SAMPLES], [test "$enable_samples" = "yes"])

# Check for debug
AC_MSG_CHECKING([whether to compile in debug mode])
AC_ARG_ENABLE([debug],
    [AS_HELP_STRING([--enable-debug],[compile with extra debugging output @<:@default=no@:>@])],
    [use_debug=$enableval],
    [use_debug=no]
)
AC_MSG_RESULT([$use_debug])

AM_CONDITIONAL([USE_DEBUG], [test "$use_debug" = "yes"])

# Check for max speed
AC_MSG_CHECKING([whether to enable additional optimizations])
AC_ARG_ENABLE([fast],
    [AS_HELP_STRING([--enable-fast],[compile with optimizations @<:@default=no@:>@])],
    [use_fast=$enableval],
    [use_fast=no]
)
AC_MSG_RESULT([$use_fast])

if test "x${use_fast}" != "xno"
then
    if test "x${use_debug}" != "xno"
    then
        AC_MSG_ERROR([Cannot specify --enable-fast and --enable-debug at the same time.])
    fi
fi

if test "x$use_fast" = "xyes" ; then
CC_MAYBE_FAST="-Wall -Wextra -Wno-sign-compare -Wdisabled-optimization 
-Wunsafe-loop-optimizations -Wno-aggressive-loop-optimizations \
-funsafe-math-optimizations -funsafe-loop-optimizations -fgcse-sm \
-fgcse-las"

# invalidate cached value if MAYBE_FAST has changed
    if test "x$libnet_cv_fast_maybe" != "x$CC_MAYBE_FAST"; then
        unset libnet_cv_fast_cflags
    fi
    AC_CACHE_CHECK([for supported optimizations flags], libnet_cv_fast_cflags, [
    echo
    CC_FAST_CFLAGS=""

    for F in $CC_MAYBE_FAST; do
        LIBNET_CC_TRY_FLAG([$F], [CC_FAST_CFLAGS="$CC_FAST_CFLAGS $F"])
    done

    libnet_cv_fast_cflags=$CC_FAST_CFLAGS
    libnet_cv_fast_maybe=$CC_MAYBE_FAST
    AC_MSG_CHECKING([which optimizations flags were supported])])

    CFLAGS="$CFLAGS -g0 -Ofast $libnet_cv_fast_cflags"

AX_CHECK_LINK_FLAG([-Wl,--strip-all],
[LDFLAGS="$LDFLAGS -Wl,--strip-all"], [])

AX_CHECK_LINK_FLAG([-Wl,--strip-debug],
[LDFLAGS="$LDFLAGS -Wl,--strip-debug"], [])

AX_CHECK_LINK_FLAG([-Wl,--relax],
[LDFLAGS="$LDFLAGS -Wl,--relax"], [])

AX_CHECK_LINK_FLAG([-Wl,--warn-common],
[LDFLAGS="$LDFLAGS -Wl,--warn-common"], [])
fi

if test "x$use_debug" = "xyes" ; then
    if test "${ax_cv_c_compiler_vendor}" = clang ; then
# -Weverything is “all current and future warnings forever, except those that we disable”.
        CFLAGS="$CFLAGS -g3 -Weverything -DDEBUG -D_DEBUG"
    else
# Use lots of warning flags with gcc and compatible compilers
#
# Note: if you change the following variable, the cache is automatically
# skipped and all flags rechecked. So there's no need to do anything
# else. If for any reason you need to force a recheck, just change
# MAYBE_WARN in an ignorable way (like adding whitespace)
#
# There are some order dependencies here.
# Specifically, an option that disables a warning will
# have no net effect if a later option then enables that
# warnings, (perhaps implicitly). So we put some grouped
# options (-Wall and -Wextra) up front and the -Wno options
# last.
    CC_MAYBE_WARN="-Wall -Wextra -Wpedantic\
    -Wundef -Wnested-externs -Wwrite-strings -Wpointer-arith -Wmissing-declarations \
    -Wmissing-prototypes -Wstrict-prototypes -Wredundant-decls \
    -Wno-unused-parameter -Wno-missing-field-initializers \
    -Wdeclaration-after-statement -Wformat=2 -Wold-style-definition -Wcast-align \
    -Wformat-nonliteral -Wformat-security -Wsign-compare -Wstrict-aliasing -Wshadow \
    -Winline -Wpacked -Wmissing-format-attribute -Wmissing-noreturn -Winit-self \
    -Wmissing-include-dirs -Wunused-but-set-variable -Warray-bounds \
    -Wimplicit-function-declaration -Wreturn-type -Wswitch-enum -Wswitch-default \
    -Wno-suggest-attribute=format -fno-strict-aliasing"

# invalidate cached value if MAYBE_WARN has changed
    if test "x$libnet_cv_warn_maybe" != "x$CC_MAYBE_WARN"; then
        unset libnet_cv_warn_cflags
    fi
    AC_CACHE_CHECK([for supported warning flags], libnet_cv_warn_cflags, [
    echo
    CC_WARN_CFLAGS=""

    for W in $CC_MAYBE_WARN; do
        LIBNET_CC_TRY_FLAG([$W], [CC_WARN_CFLAGS="$CC_WARN_CFLAGS $W"])
    done

    libnet_cv_warn_cflags=$CC_WARN_CFLAGS
    libnet_cv_warn_maybe=$CC_MAYBE_WARN
    AC_MSG_CHECKING([which warning flags were supported])])

    CFLAGS="$CFLAGS -g3 $libnet_cv_warn_cflags -DDEBUG -D_DEBUG"
    fi

AX_CHECK_LINK_FLAG([-Wl,--no-as-needed],
[LDFLAGS="$LDFLAGS -Wl,--no-as-needed"], [])

AX_CHECK_LINK_FLAG([-Wl,--fatal-warnings],
[LDFLAGS="$LDFLAGS -Wl,--fatal-warnings"], [])

AX_CHECK_LINK_FLAG([-Wl,--warn-common],
[LDFLAGS="$LDFLAGS -Wl,--warn-common"], [])

fi

# what (not) to do if the user disables shared libraries
AM_CONDITIONAL([COND_SHARED], [test "x$enable_shared" != xno])

# Check and set OS specific parameters
case "$target_os" in

*linux*)
    AC_DEFINE(_BSD_SOURCE, 1,
        [Define as necessary to "unhide" header symbols.])
    AC_DEFINE(__BSD_SOURCE, 1,
        [Define as necessary to "unhide" header symbols.])
    AC_DEFINE(__FAVOR_BSD, 1,
        [Define if we should favor the BSD APIs when possible in Linux.])

    LIBNET_CONFIG_DEFINES="-D_BSD_SOURCE -D__BSD_SOURCE -D__FAVOR_BSD"
    AC_CHECK_HEADERS(net/ethernet.h, \
        LIBNET_CONFIG_DEFINES="$LIBNET_CONFIG_DEFINES -DHAVE_NET_ETHERNET_H")
    ;;

*freebsd*)
    AC_DEFINE(LIBNET_BSDISH_OS, 1,
        [Define if our build OS supports the BSD APIs])
    AC_DEFINE(LIBNET_BSD_BYTE_SWAP, 1,
        [Define if libnet should byteswap data.])
    AC_DEFINE(HAVE_SOCKADDR_SA_LEN, 1,
        [Define if the sockaddr structure includes a sa_len member.])

    LIBNET_CONFIG_DEFINES="-DLIBNET_BSDISH_OS -DLIBNET_BSD_BYTE_SWAP -DHAVE_SOCKADDR_SA_LEN"
    ;;

*netbsd*)
    AC_DEFINE(LIBNET_BSDISH_OS, 1,
        [Define if our build OS supports the BSD APIs])
    AC_DEFINE(LIBNET_BSD_BYTE_SWAP, 1,
        [Define if libnet should byteswap data.])

    LIBNET_CONFIG_DEFINES="-DLIBNET_BSDISH_OS -DLIBNET_BSD_BYTE_SWAP"
    ;;

*openbsd*)
    AC_DEFINE(LIBNET_BSDISH_OS, 1,
        [Define if our build OS supports the BSD APIs])
    AC_DEFINE(HAVE_SOCKADDR_SA_LEN, 1,
        [Define if the sockaddr structure includes a sa_len member.])
    LIBNET_CONFIG_DEFINES="-DLIBNET_BSDISH_OS"
    ;;

*bsdi*)
    AC_DEFINE(LIBNET_BSDISH_OS, 1,
        [Define if our build OS supports the BSD APIs])
    AC_DEFINE(LIBNET_BSD_BYTE_SWAP, 1,
        [Define if libnet should byteswap data.])
    LIBNET_CONFIG_DEFINES="-DLIBNET_BSDISH_OS -DLIBNET_BSD_BYTE_SWAP"
    ;;

*darwin*)
    AC_DEFINE(HAVE_SOCKADDR_SA_LEN, 1,
        [Define if the sockaddr structure includes a sa_len member.])
    AC_DEFINE(LIBNET_BSD_BYTE_SWAP, 1, [Define if libnet should byteswap data.])
    AC_DEFINE(LIBNET_BSDISH_OS)
    AC_DEFINE(LIBNET_BSD_BYTE_SWAP)
    LIBNET_CONFIG_DEFINES="-DHAVE_SOCKADDR_SA_LEN -DLIBNET_BSDISH_OS -DLIBNET_BSD_BYTE_SWAP"
    ;;

*solaris*)
    AC_DEFINE(HAVE_SOLARIS, 1, [Define if we are running on Solaris.])
    AC_CHECK_HEADERS(sys/bufmod.h sys/dlpi_ext.h)
    AC_MSG_CHECKING(for /dev/dlpi device)
    if test -c /dev/dlpi; then
        AC_MSG_RESULT(yes)
        AC_DEFINE(HAVE_DEV_DLPI, 1, [Define if /dev/dlpi is available.])
    else
        AC_MSG_RESULT(no)
        dir="/dev/dlpi"
        AC_MSG_CHECKING(for $dir directory)
        if test -d $dir ; then
            AC_MSG_RESULT(yes)
            AC_DEFINE_UNQUOTED(DLPI_DEV_PREFIX, "$dir",
                [Define if /dev/dlpi is a directory.])
        else
            AC_MSG_RESULT(no)
        fi
    fi
    AC_CHECK_LIB(socket, socket, ,AC_MSG_ERROR(libsocket not found.))
    AC_CHECK_LIB(nsl, gethostbyname, ,AC_MSG_ERROR(libnsl not found.))
    AC_CHECK_LIB(resolv, hstrerror, ,AC_MSG_ERROR(libresolv not found.))

# 
# Broken checksums?
#
    case "`uname -r`" in
    5.4)
        AC_DEFINE(STUPID_SOLARIS_CHECKSUM_BUG, 1,
            [Define if our version of Solaris has broken checksums.])
        ;;
    5.5*)
        AC_DEFINE(STUPID_SOLARIS_CHECKSUM_BUG, 1,
            [Define if our version of Solaris has broken checksums.])
        ;;
    5.8)
        AC_DEFINE(STUPID_SOLARIS_CHECKSUM_BUG, 1,
            [Define if our version of Solaris has broken checksums.])
        AC_DEFINE(HAVE_SOLARIS_IPV6, 1,
            [Define if our version of Solaris supports IPv6.])

        ;;
    5.9)
        AC_DEFINE(STUPID_SOLARIS_CHECKSUM_BUG, 1,
            [Define if our version of Solaris has broken checksums.])
        AC_DEFINE(HAVE_SOLARIS_IPV6, 1,
            [Define if our version of Solaris supports IPv6.])
        ;;
    5.10|5.11|5.12)
        AC_DEFINE(HAVE_SOLARIS_IPV6, 1,
            [Define if our version of Solaris supports IPv6.])
        ;;

    esac

    ADDITIONAL_LIBS="-lresolv -lsocket -lnsl"
    LIBNET_CONFIG_LIBS="$LIBNET_CONFIG_LIBS -lresolv -lsocket -lnsl"

    ;;

*hpux11*)
    AC_DEFINE(HAVE_HPUX11, 1, [Define if we are building on HP/UX.])
    AC_CHECK_HEADERS(sys/dlpi_ext.h)
    ;;

*cygwin*)
    AC_DEFINE(LIBNET_BSDISH_OS, 1,
        [Define if our build OS supports the BSD APIs])
    AC_DEFINE(NO_SNPRINTF, 1,
        [Define if snprintf() is unavailable on our system.])
    LIBNET_CONFIG_DEFINES="-DLIBNET_BSDISH_OS -DNO_SNPRINTF"
    CFLAGS="$CFLAGS -mno-cygwin -O0 -fnative-struct -DNO_SNPRINTF -I/usr/include/pcap"
    AC_CHECK_LIB(packet, PacketSetMode, ,AC_MSG_ERROR(packet lib not found.))
    AC_CHECK_LIB(wpcap, pcap_setmode, ,AC_MSG_ERROR(pcap lib not found.))
    LIBS="$LIBS -lws2_32"
    ;;

*mingw*)
    PACKAGE_VERSION_DLL=PACKAGE_VERSION_MAJOR,PACKAGE_VERSION_MINOR,PACKAGE_VERSION_PATCH,PACKAGE_VERSION_NANO

    if test "$enable_shared" = "yes"; then
        AC_CHECK_TOOL(WINDRES, windres, :)
    fi

    AC_DEFINE(WIN32_LEAN_AND_MEAN, 1, 
        [Define to limit the scope of <windows.h>])

    AC_DEFINE_UNQUOTED([PACKAGE_VERSION_DLL], [$PACKAGE_VERSION_DLL], 
        [Define to the DLL-preferred version of this package.])

    AC_DEFINE_UNQUOTED([PACKAGE_DLL_NAME], ["libnet-LN_CURRENT.dll"], 
        [Define to the libtool-preferred DLL name of this package.])

    AC_CHECK_LIB(packet, PacketSetMode, ,AC_MSG_ERROR(libpacket.a not found. See README.win32 for more information))
    AC_CHECK_LIB(wpcap, pcap_setmode, ,AC_MSG_ERROR(libwpcap.a not found. See README.win32 for more information))
    LIBS="$LIBS -lws2_32 -liphlpapi"

    if test "$host" = "i686-w64-mingw32" ; then
    CFLAGS="$CFLAGS -march=i686"
    else
    CFLAGS="$CFLAGS -march=native"
# the default GCC toolchains on Debian & Co are so old
     AX_CHECK_LINK_FLAG([-Wl,--high-entropy-va],
     [LDFLAGS="$LDFLAGS -Wl,--high-entropy-va"],
     [AC_MSG_NOTICE([Consider updating your toolchain.])])
    fi

    if test "${cross_compiling}" = "yes" ; then
    CFLAGS="$CFLAGS -static-libgcc"
    fi
    ;;

*irix*)
    CFLAGS="$CFLAGS -DINET6=1"
    ;;

*)
    AC_MSG_WARN(apparently your OS is not officially supported yet)
    AC_MSG_WARN(this may not work)
    AC_MSG_RESULT(please send diffs to autostart.ini@gmail.com)
    ;;

esac

# some finishing touches for clang
if test "${ax_cv_c_compiler_vendor}" = clang ; then
case "$target_os" in
*mingw*)
    LDFLAGS="$LDFLAGS -L$prefix/lib -L$prefix/$host/lib";;
*)
    CFLAGS="$CFLAGS -march=native";;
esac
fi

AC_CONFIG_FILES([Makefile \
                 libnet.pc \
                 include/Makefile \
                 include/libnet.h \
                 src/Makefile \
                 sample/Makefile])
AC_CONFIG_FILES([libnet-config], [chmod +x libnet-config])
AC_CONFIG_FILES([doc/fixmanpages], [chmod +x doc/fixmanpages])
AC_OUTPUT

AC_MSG_RESULT([
-=-=-=-=-=-=-=-=-= $PACKAGE Configuration Complete =-=-=-=-=-=-=-=-=-=-


Configuration Summary

    Version : ..................... ${VERSION}
    Protocols: .................... 32

    Host : ........................ ${host}
    Operating System: ............. ${host_os}
    Host CPU : .................... ${host_cpu}
    Host Vendor : ................. ${host_vendor}
    Host OS : ..................... ${host_os}
    Prefix: ....................... ${prefix}

Compilation Environment

    Cross-compiling: .............. ${cross_compiling}
    Compiler (CC): ................ ${ax_cv_c_compiler_vendor}
    Compiler Version: ............. ${ax_cv_c_compiler_version}
    CFLAGS:........................ ${CFLAGS}
    LD: ........................... ${LD}
    LDFLAGS: ...................... ${LDFLAGS}
    LIBS: ......................... ${LIBS}

Features and Examples

    Link Layer: ................... ${link_layer}
    Shared Libraries: ............. ${enable_shared}
    Static Libraries: ............. ${enable_static}
    PIC ........................... ${pic_mode}
    Debugging: .................... ${use_debug}
    Additional Optimizations: ..... ${use_fast}
    Build Sample Programs: ........ ${enable_samples}
    Rebuild Docs: ................. ${rebuild_docs}

To override options, see ./configure --help

To disable silent building and print the full command line of every stage, run "make V=1"
])

if test "$WIN32" = yes ; then
AC_MSG_WARN([To compile shared libraries on MinGW, use the WinPcap libraries in $(pwd)/win32/.
GCC is NOT able to produce x64 compatible images using the official WinPcap Developer Pack.
See README.win32 for more information.

Report bugs to ${PACKAGE_BUGREPORT}])
elif test "$rebuild_docs" = "yes" ; then
AC_MSG_RESULT([To build just the Documentation run "make doc"

Report bugs to ${PACKAGE_BUGREPORT}])
else
AC_MSG_RESULT([Report bugs to ${PACKAGE_BUGREPORT}])
fi

# EOF
