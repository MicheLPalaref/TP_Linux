@ REM ######################################
@ REM # Variable to ignore <CR> in DOS
@ REM # line endings
@ set SHELLOPTS=igncr

@ REM ######################################
@ REM # Variable to ignore mixed paths
@ REM # i.e. G:/$SOPC_KIT_NIOS2/bin
@ set CYGWIN=nodosfilewarning

@set QUARTUS_BIN=%QUARTUS_ROOTDIR%\\bin
@if exist %QUARTUS_BIN%\\quartus_pgm.exe (goto DownLoad)

@set QUARTUS_BIN=%QUARTUS_ROOTDIR%\\bin64
@if exist %QUARTUS_BIN%\\quartus_pgm.exe (goto DownLoad)

:: Prepare for future use (if exes are in bin32)
@set QUARTUS_BIN=%QUARTUS_ROOTDIR%\\bin32

:DownLoad
@ echo off

echo ===========================================================
echo = !!!!! Make sure MSEL[4:0] = 10010                    !!!!!
echo ===========================================================



echo ===========================================================
echo = Convert .sof to .jic                                    =
echo ===========================================================
%QUARTUS_BIN%\\quartus_cpf -c -d epcs128 -s 5csxfc6d6 DE10_Standard.sof DE10_Standard.jic

echo ===========================================================
echo = Download Flash Loader                                   =
echo ===========================================================
%QUARTUS_BIN%\\quartus_pgm.exe -m jtag -c 1 -o "p;sfl_enhanced_01_02d020dd.sof%@2"


echo ===========================================================
echo = Programming EPCS with .jic                              =
echo ===========================================================
%QUARTUS_BIN%\\quartus_pgm.exe -m jtag -c 1 -o "p;DE10_Standard.jic@2"

del DE10_Standard.jic
pause