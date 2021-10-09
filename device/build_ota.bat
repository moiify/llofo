@echo off

set COREVERSION=L610_CORE "core_05.02.23"

REM del out\appimage_debug\hex\app.pac

REM Ñ¡ÔñÊÇ·ñ±àÒëÀ¶ÑÀ
set BLE_COMPILE=0
@echo [123;92m05.02.23_release.bat[0m
@echo [101;93mÊÇ·ñ±àÒëÀ¶ÑÀ¹Ì¼þ[0m
echo  1: ±àÒë
echo  2: ²»±àÒë
choice /c 12 /m "Enter"
set USER_BLE=%ERRORLEVEL%
if %USER_BLE% == 1 (
    set BLE_COMPILE=1
)

REM ¼ÇÂ¼Ïà¹ØÂ·¾¶
rem ²Ö¿â¸ùÄ¿Â¼
set REPO_ROOT=%cd%
rem ¹¤³ÌCONFIGÄ¿Â¼
set PRJ_CONFIG=%REPO_ROOT%\config
rem À¶ÑÀ585¸ùÄ¿Â¼
set BLE_DA14585_ROOT=%REPO_ROOT%\ble\projects\target_apps\dsps\dsps_device\Keil_5
rem ÓÃ»§´úÂëÄ¿Â¼
set PRJ_SOURCE=%REPO_ROOT%\src
rem Python»·¾³Ä¿Â¼
set PYTHONPATH=%REPO_ROOT%\prebuilts\win32\python3
rem ÄÚºËÄ¿Â¼
set COREPATH=%REPO_ROOT%\core\core_05.02.23
REM È·¶¨²úÆ·ÀàÐÍ
2>NUL CALL :CASE_%USER_BLE%
IF ERRORLEVEL 1 CALL :DEFAULT_CASE

REM ÐÞ¸ÄcmakelistÀïµÄÄÚºËºê
setlocal enabledelayedexpansion
set Cmakelist=CMakeLists.txt
set backCmakelist=%REPO_ROOT%\CMakeLists_bk.txt
REM É¾µôµ±Ç°µÄCmakelist.txt
if exist %Cmakelist% del /f %Cmakelist%

(for /f "tokens=*" %%i in (%backCmakelist%) do (
set s=%%i
set s=!s:L610_CORE ""=%COREVERSION%!
if !s!==%%i (
    echo !s! 
    ) else (
    echo !s!
    REM ÓÃÀ´¸øcmakeÌá¹©ºê¶¨Òå (²úÆ·ÐÍºÅ£¬²úÆ·ÄÚºË¶¨Òå)
        echo add_definitions^(-DCOREVERSION23^)
        echo add_definitions^(-DAPP_RELEASE^)
    )
))>%Cmakelist%

if %BLE_COMPILE% == 0 (
	goto COMPILE_L610
)

REM ±àÒëÀ¶ÑÀ²¢·µ»Ø
set BLE_COMPILE_ROOT=%BLE_DA14585_ROOT%
cd %BLE_COMPILE_ROOT%
echo %cd%
call Compile.bat
cd %REPO_ROOT%

REM ÖØÖÃÀ¶ÑÀ¹Ì¼þÎÄ¼þ¼Ð
if exist "%PRJ_SOURCE%\user\include\dacode"  rd /S /Q %PRJ_SOURCE%\user\include\dacode
md "%PRJ_SOURCE%\user\include\dacode"

REM ¿½±´Êä³ö txt   ÎÄ¼þÃûÔÚÀ¶ÑÀ±àÒë½Å±¾Àï¶¨Òå
copy %BLE_COMPILE_ROOT%\releaseFile\%BLE_TXT_FILE_NAME% %PRJ_SOURCE%\user\include\dacode\dacode.txt
@del /F /S /Q %BLE_COMPILE_ROOT%\releaseFile\%BLE_TXT_FILE_NAME%

:COMPILE_L610
set timef=%time:~0,2%:%time:~3,2%:%time:~6,2%
echo Start at %timef%
::×¼±¸±àÒë»·¾³
if exist "%REPO_ROOT%\tools\pacgen.py"  del %REPO_ROOT%\tools\pacgen.py
copy %COREPATH%\pacgen.py %REPO_ROOT%\tools
call tools\core_launch.bat
cd out\appimage_debug

::cmake ninja ¹¹½¨»·¾³
cmake ..\.. -Wwarn -G Ninja

ninja clean

::ninja Ö´ÐÐ±àÒë
ninja -w dupbuild=err | ..\..\tee.exe ..\output.log

if exist ".\hex\app.pac" (
    echo product [31;1m %PRODUCT_NAME% [0m build [32;1m Successful [0m
    ..\..\SecPack\pack.exe .\hex\app.img L610 5.2.23
) else (
    echo product [31;1m %PRODUCT_NAME% [0m build [31;1m Failed [0m
)

set timef=%time:~0,2%:%time:~3,2%:%time:~6,2%
echo End at %timef%

REM É¾µôµ±Ç°µÄCmakelist.txt
del /f ..\..\%Cmakelist%

cd ..\..\..\
@TIMEOUT /T 200
EXIT /B

:CASE_1
    set PRODUCT_NAME=APP_RELEASE_BLE
    GOTO END_CASE
:CASE_2
    set PRODUCT_NAME=APP_RELEASE
    GOTO END_CASE
:END_CASE
    VER > NUL # reset ERRORLEVEL
    GOTO :EOF # return from CALL
