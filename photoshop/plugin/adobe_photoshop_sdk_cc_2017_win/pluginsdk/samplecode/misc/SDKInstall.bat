echo off
echo.
echo Copy the SDK examples to the common location
echo where Photoshop CC will find them. 
echo Use the Windows Registry to find the location 
echo of installed versions of Photoshop. 
echo This script no longer prompts for options
echo and defaults to 64 bit debug copy.
echo.    
echo Version 1.7
set WinVer=
set WinMajor=
set WinMinor=
set WinBuild=
set RegTokens=2
:; Get Value from 'VER' command output 
FOR /F "tokens=*" %%i in ('VER') do SET WinVer=%%i 
FOR /F "tokens=1-3 delims=]-" %%A IN ("%WinVer%" ) DO ( 
 set Var1=%%A 
) 
:; Get version number only so drop off Microsoft Windows Version 
FOR /F "tokens=1-9 delims=n" %%A IN ("%Var1%" ) DO ( 
 set WinVer=%%C 
 REM echo %WinVer% 
) 
:; Separate version numbers 
FOR /F "tokens=1-8 delims=.-" %%A IN ("%WinVer%" ) DO ( 
set WinMajor=%%A 
set WinMinor=%%B 
set WinBuild=%%C 
) 
:; Fix the extra space left over in the Major 
FOR /F "tokens=1 delims= " %%A IN ("%WinMajor%" ) DO ( 
 set WinMajor=%%A 
) 
:; Display Results	
REM ECHO WinVer = %WinVer% 
REM ECHO WinMajor = %WinMajor% 
REM ECHO WinMinor = %WinMinor% 
REM ECHO WinBuild = %WinBuild% 
IF %WinMajor%==6 (
 REM ECHO Windows 7
) ELSE (
 REM ECHO Windows XP
 set RegTokens=3
)
set ps_cs6_13="NOT INSTALLED"
set ps_cc_14="NOT INSTALLED"
set ps_cc_2014="NOT INSTALLED"
set ps_cc_2015="NOT INSTALLED"
set ps_cc_2015_5="NOT INSTALLED"
set ps_cc_2017="NOT INSTALLED"
set ps_cs6_13_32="NOT INSTALLED"
set ps_cc_14_32="NOT INSTALLED"
set ps_cc_2014_32="NOT INSTALLED"
set ps_cc_15_32="NOT INSTALLED"
set ps_cc_2015_32="NOT INSTALLED"
set ps_cc_15_5_32="NOT INSTALLED"
set ps_cc_2015_5_32="NOT INSTALLED"
set ps_cc_2017_32="NOT INSTALLED"
set ps_install_path="NOT INSTALLED"
set sdk_source_path="NOT INSTALLED"
FOR /F "tokens=%RegTokens%* delims=	 " %%A IN ('REG QUERY "HKLM\SOFTWARE\Adobe\Photoshop\60.0\PluginPath" ') DO SET ps_cs6_13="%%B"
FOR /F "tokens=%RegTokens%* delims=	 " %%A IN ('REG QUERY "HKLM\SOFTWARE\Adobe\Photoshop\70.0\PluginPath" ') DO SET ps_cc_14="%%B"
FOR /F "tokens=%RegTokens%* delims=	 " %%A IN ('REG QUERY "HKLM\SOFTWARE\Adobe\Photoshop\80.0\PluginPath" ') DO SET ps_cc_2014="%%B"
FOR /F "tokens=%RegTokens%* delims=	 " %%A IN ('REG QUERY "HKLM\SOFTWARE\Adobe\Photoshop\90.0\PluginPath" ') DO SET ps_cc_2015="%%B"
FOR /F "tokens=%RegTokens%* delims=	 " %%A IN ('REG QUERY "HKLM\SOFTWARE\Adobe\Photoshop\100.0\PluginPath" ') DO SET ps_cc_2015_5="%%B"
FOR /F "tokens=%RegTokens%* delims=	 " %%A IN ('REG QUERY "HKLM\SOFTWARE\Adobe\Photoshop\110.0\PluginPath" ') DO SET ps_cc_2017="%%B"
IF %PROCESSOR_ARCHITECTURE%==AMD64 (
 FOR /F "tokens=%RegTokens%* delims=	 " %%A IN ('REG QUERY "HKLM\SOFTWARE\Wow6432Node\Adobe\Photoshop\60.0\PluginPath" ') DO SET ps_cs6_13_32="%%B"
 FOR /F "tokens=%RegTokens%* delims=	 " %%A IN ('REG QUERY "HKLM\SOFTWARE\Wow6432Node\Adobe\Photoshop\70.0\PluginPath" ') DO SET ps_cc_14_32="%%B"
 FOR /F "tokens=%RegTokens%* delims=	 " %%A IN ('REG QUERY "HKLM\SOFTWARE\Wow6432Node\Adobe\Photoshop\80.0\PluginPath" ') DO SET ps_cc_2014_32="%%B"
 FOR /F "tokens=%RegTokens%* delims=	 " %%A IN ('REG QUERY "HKLM\SOFTWARE\Wow6432Node\Adobe\Photoshop\90.0\PluginPath" ') DO SET ps_cc_2015_32="%%B"
 FOR /F "tokens=%RegTokens%* delims=	 " %%A IN ('REG QUERY "HKLM\SOFTWARE\Wow6432Node\Adobe\Photoshop\100.0\PluginPath" ') DO SET ps_cc_2015_5_32="%%B"
 FOR /F "tokens=%RegTokens%* delims=	 " %%A IN ('REG QUERY "HKLM\SOFTWARE\Wow6432Node\Adobe\Photoshop\110.0\PluginPath" ') DO SET ps_cc_2017_32="%%B"
) ELSE (
 set ps_cs6_13_32=%ps_cs6_13%
 set ps_cc_14_32=%ps_cc_14%
 set ps_cc_2014_32=%ps_cc_2014%
 set ps_cc_15_32=%ps_cc_15%
 set ps_cc_2015_32=%ps_cc_2015%
 set ps_cc_15_5_32=%ps_cc_15_5%
 set ps_cc_2015_5_32=%ps_cc_2015_5%
 set ps_cc_2017_32=%ps_cc_2017%
)
echo.
echo I found these installed versions:
echo.
echo 1.  Photoshop CS6 32 bit          %ps_cs6_13_32%
echo 2.  Photoshop CC  32 bit          %ps_cc_14_32%
echo 3.  Photoshop CC  2014 32 bit     %ps_cc_2014_32%
echo 4.  Photoshop CC  2015 32 bit     %ps_cc_2015_32%
echo 5.  Photoshop CC  2015.5 32 bit   %ps_cc_2015_5_32%
echo 6.  Photoshop CC  2017 32 bit     %ps_cc_2017_32%
IF %PROCESSOR_ARCHITECTURE%==AMD64 (
 echo 7.  Photoshop CS6 64 bit          %ps_cs6_13%
 echo 8.  Photoshop CC  64 bit          %ps_cc_14%
 echo 9.  Photoshop CC  2014 64 bit     %ps_cc_2014%
 echo A.  Photoshop CC  2015 64 bit     %ps_cc_2015%
 echo B.  Photoshop CC  2015.5 64 bit   %ps_cc_2015_5%
 echo C.  Photoshop CC  2017 64 bit     %ps_cc_2017%
)
REM set /p userinp=Pick the Photoshop to install into:
REM set userinp=%userinp:~0,1%
set userinp=D
if "%userinp%"=="1" goto CS632
if "%userinp%"=="2" goto CC32
if "%userinp%"=="3" goto CC201432
if "%userinp%"=="4" goto CC201532
if "%userinp%"=="5" goto CC2015532
if "%userinp%"=="6" goto CC201732
if "%userinp%"=="7" goto CS664
if "%userinp%"=="8" goto CC64
if "%userinp%"=="9" goto CC201464
if "%userinp%"=="A" goto CC201564
if "%userinp%"=="B" goto CC2015564
if "%userinp%"=="C" goto CC201764
if "%userinp%"=="D" goto DEFAULTCOMMON
echo Invalid Choice, quitting.
goto END
:CS632
echo Photoshop CS6 32
set ps_install_path=%ps_cs6_13_32%
goto SDK
:CC32
echo Photoshop CC 32
set ps_install_path=%ps_cc_14_32%
goto SDK
:CC201432
echo Photoshop CC 2014 32
set ps_install_path=%ps_cc_2014_32%
goto SDK
:CC201532
echo Photoshop CC 2015 32
set ps_install_path=%ps_cc_2015_32%
goto SDK
:CC2015532
echo Photoshop CC 2015.5 32
set ps_install_path=%ps_cc_2015_5_32%
goto SDK
:CC201732
echo Photoshop CC 2017 32
set ps_install_path=%ps_cc_2017_32%
goto SDK
:CS664
echo Photoshop CS6 64
set ps_install_path=%ps_cs6_13%
goto SDK
:CC64
echo Photoshop CC 64
set ps_install_path=%ps_cc_14%
goto SDK
:CC201464
echo Photoshop CC 2014 64
set ps_install_path=%ps_cc_2014%
goto SDK
:CC201564
echo Photoshop CC 2015 64
set ps_install_path=%ps_cc_2015%
goto SDK
:CC2015564
echo Photoshop CC 2015.5 64
set ps_install_path=%ps_cc_2015_5%
goto SDK
:CC201764
echo Photoshop CC 2017 64
set ps_install_path=%ps_cc_2017%
goto SDK
:DEFAULTCOMMON
echo Photoshop CC 64 Common
set ps_install_path="C:\Program Files\Common Files\Adobe\Plug-Ins\CC\SDK\"
REM For CS6 use this path set ps_install_path="C:\Program Files\Common Files\Adobe\Plug-Ins\CS6\SDK\"
:SDK
REM echo.
REM echo Which SDK build to install:
REM echo.
REM echo 1. Debug 32 bit
REM echo 2. Debug 64 bit
REM echo 3. Release 32 bit
REM echo 4. Release 64 bit
REM set /p userinp=Choose a number ( 1 - 4 ):
REM set userinp=%userinp:~0,1%
set userinp=5
if "%userinp%"=="1" goto D32
if "%userinp%"=="2" goto D64
if "%userinp%"=="3" goto R32
if "%userinp%"=="4" goto R64
if "%userinp%"=="5" goto DEF
echo Invalid Choice, quitting.
goto END
:D32
echo Debug 32
set sdk_source_path=..\Output\Win\Debug\*.*
goto COPY
:D64
echo Debug 64
set sdk_source_path=..\Output\Win\Debug64\*.*
goto COPY
:R32
echo Release 32
set sdk_source_path=..\Output\Win\Release\*.*
goto COPY
:R64
echo Release 64
set sdk_source_path=..\Output\Win\Release64\*.*
goto COPY
:DEF
echo Common Debug 64
set sdk_source_path=..\Output\Win\Debug64\*.*
goto COPY

:COPY
echo Copying from here %sdk_source_path% to here %ps_install_path%.
xcopy %sdk_source_path% %ps_install_path%. /E /F /H /R /D /C /Y

:END
set ps_cs6_13=
set ps_cc_14=
set ps_cc_2014=
set ps_cc_2015=
set ps_cc_2015_5=
set ps_cc_2017=
set ps_cs6_13_32=
set ps_cc_14_32=
set ps_cc_2014_32=
set ps_cc_2015_32=
set ps_cc_2015_5_32=
set ps_cc_2017_32=
set ps_install_path=
set sdk_source_path=
set userinp=
set WinVer=
set WinMajor=
set WinMinor=
set WinBuild=
set RegTokens=
set Var1=