:: Script to build libnet with MSVC.
::
:: Open a "Visual Studio Developer Command Prompt" and set the compiler
:: environment:
::
::     "%VSINSTALLDIR%VC\vcvarsall.bat" x86
::   -or-
::     "%VSINSTALLDIR%VC\vcvarsall.bat" x64
::
:: Then cd to this directory and run this script.

:: change this to "on" if you need to debug this script
@echo off

:: test whether this script is executed from a (VS2015) Developer Command Prompt
if not defined INCLUDE goto :FAIL

@echo.
@echo _________________________________ NOTICE _________________________________
@echo This batch file is provided "as is". 
@echo Meaning that not only is it especially primitive, nobody cares about it,
@echo and there is probably something wrong with it too. There are many other
@echo ways to build libnet on Windows. Consider using these instead.
@echo See README.win32 for more information.
@echo __________________________________________________________________________
@echo.

@setlocal
:: set these things accordingly (set paths relative to the "src" directory):
set WINPCAP=..\win32\wpdpack

if not defined platform (
    set LNARCH=x86
    set WINPCAPLIBS=%WINPCAP%\Lib
) else if "%platform%" == "X64" (
    set LNARCH=x64
    set WINPCAPLIBS=%WINPCAP%\Lib\x64
)

:: FIXME adjust version string.
:: There's no agreed naming convention on Windows. If we want to be picky, then
:: debug builds should be named libnet9d.dll/lib or libnet1d.dll/lib
:: This is how most libraries are named on MSVC. Doing so would conflict with
:: the naming style already used by gcc/libtool (libnet-9.x.y.z). However,
:: not doing so means not being able to have both debug and release builds
:: of libnet in MSVC's (cl) lib directory
set LNVERSION=1.2
set LNSOVERSION=9
set LNDLLNAME=libnet.dll
set LNLIBNAME=libnet.lib
set LNSTATIC=libnet-static.lib
set LNCOMPILE=cl /nologo /MD /MP /O2 /W3 /c /DSHUT_UP_WINDOZE
set LNCOMPILEDBG=cl /nologo /MDd /MP /Od /FC /Zi /W3 /c
set LNLINK=link /nologo /DLL /DEF:libnet-%LNSOVERSION%.def ^
/libpath:%WINPCAPLIBS% /out:%LNDLLNAME% /implib:%LNLIBNAME% *.obj *.res
set LNLINKDBG=link /nologo /debug /DLL /DEF:libnet-%LNSOVERSION%.def ^
/libpath:%WINPCAPLIBS% /out:%LNDLLNAME% /PDB:libnet.pdb ^
/implib:%LNLIBNAME% *.obj *.res
set LNRC=rc /nologo /I..\include /d__NOTMINGW__ /v -r
set LNMT=mt /nologo
set LNLIB=lib /nologo
set LNINCLUDE=/I. /I..\include /I%WINPCAP%\Include
set LNRESOURCE=libnet_dll_info.rc
set LNSOURCE=^
libnet_advanced.c libnet_asn1.c ^
libnet_build_802.1q.c libnet_build_802.1x.c libnet_build_802.2.c ^
libnet_build_802.3.c libnet_build_arp.c libnet_build_bgp.c ^
libnet_build_cdp.c libnet_build_data.c libnet_build_dhcp.c ^
libnet_build_dns.c libnet_build_ethernet.c libnet_build_fddi.c ^
libnet_build_gre.c libnet_build_hsrp.c libnet_build_icmp.c ^
libnet_build_igmp.c libnet_build_ip.c libnet_build_ipsec.c ^
libnet_build_isl.c libnet_build_link.c libnet_build_mpls.c ^
libnet_build_ntp.c libnet_build_ospf.c libnet_build_rip.c ^
libnet_build_rpc.c libnet_build_sebek.c libnet_build_snmp.c ^
libnet_build_stp.c libnet_build_tcp.c libnet_build_token_ring.c ^
libnet_build_udp.c libnet_build_vrrp.c ^
libnet_checksum.c libnet_cq.c libnet_crc.c ^
libnet_dll.c ^
libnet_error.c ^
libnet_if_addr.c libnet_init.c libnet_internal.c ^
libnet_link_win32.c ^
libnet_pblock.c libnet_port_list.c libnet_prand.c ^
libnet_raw.c libnet_resolve.c ^
libnet_version.c ^
libnet_write.c

:: checking supplied options
@if "%1"=="" goto :RELEASE
@if "%1"=="debug" goto :DEBUG
@if "%1"=="static" goto :STATIC1
@if "%1"=="clean" goto :CLEAN
@if not "%1"=="debug" @if not "%1"=="static" @if not "%1"=="clean" goto :USAGE

:RELEASE
@color
@echo.
@echo Entering directory ..\src
cd ..\src
@echo on
%LNRC% %LNRESOURCE%
@if errorlevel 1 goto :BAD
%LNCOMPILE% %LNINCLUDE% %LNSOURCE%
@if errorlevel 1 goto :BAD
%LNLINK%
@if errorlevel 1 goto :BAD
@if exist %LNDLLNAME%.manifest^
  %LNMT% -manifest %LNDLLNAME%.manifest -outputresource:%LNDLLNAME%;2
@if errorlevel 1 goto :BAD
@if errorlevel 0 goto :STATIC2

:DEBUG
@color
@echo.
@echo Entering directory ..\src
cd ..\src
@echo on
%LNRC% %LNRESOURCE%
@if errorlevel 1 goto :BAD
%LNCOMPILEDBG% %LNINCLUDE% %LNSOURCE%
@if errorlevel 1 goto :BAD
%LNLINKDBG%
@if errorlevel 1 goto :BAD
@if exist %LNDLLNAME%.manifest^
  %LNMT% -manifest %LNDLLNAME%.manifest -outputresource:%LNDLLNAME%;2
@if errorlevel 1 goto :BAD
@if errorlevel 0 goto :STATIC2

:STATIC1
@color
@echo.
@echo Building static libnet library...
@echo Entering directory ..\src
cd ..\src
@echo on
%LNCOMPILE% %LNINCLUDE% %LNSOURCE%
@if errorlevel 1 goto :BAD
@if errorlevel 0 goto :STATIC2

:STATIC2
@echo on
%LNLIB% /OUT:%LNSTATIC% *.obj
@if errorlevel 1 goto :BAD
@echo off
@if errorlevel 0 del *.obj *.res *.manifest
@goto :SUCCESS

:CLEAN
@color
@echo.
@echo Deleting libnet library files...
del ..\src\*.dll ..\src\*.lib ..\src\*.exp ..\src\*.obj ..\src\*.res ^
..\src\*.manifest ..\src\*.ilk ..\src\*.pdb
@goto :eof

:USAGE
@echo.
@echo Invalid option "%*"
@echo.
@echo Usage: %~nx0 [debug] ^| [static] ^| [clean]
@goto :eof

:BAD
@color 4f
@echo.
@echo *******************************************************
@echo *   BUILD FAILED -- Please check the error messages   *
@echo *******************************************************
@echo.
@echo.
@echo _________________________________ NOTICE _________________________________
@echo This batch file is provided "as is". 
@echo Meaning that not only is it especially primitive, nobody cares about it,
@echo and there is probably something wrong with it too. There are many other
@echo ways to build libnet on Windows. Consider using these instead.
@echo See README.win32 for more information.
@echo __________________________________________________________________________
@echo.
@title BUILD FAILED
@goto :eof

:FAIL
@echo.
@echo You must open a "Visual C++ Developer Command Prompt" to run this script
title ERROR
pause
@goto :eof

:SUCCESS
@echo.
@echo ==================================================================
@echo =         Successfully built libnet-%LNVERSION% for Windows %LNARCH%          =
@echo ==================================================================
@echo.
@goto :eof
