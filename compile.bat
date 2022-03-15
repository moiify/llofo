@echo off

rem //choice to comp ble
set BLE_COMPILE=0
echo [32;1m--- Welcome to llofo --- [0m
echo [33;1mcompile BLE firmware ?[0m
echo 1:Yes
echo 2:No
choice /c 12 /m "Enter"
set USER_BLE=%ERRORLEVEL%
if %USER_BLE% == 1 (
    set BLE_COMPILE=1
)

set REPO_ROOT=%cd%
set PRJ_CONFIG=%REPO_ROOT%\config
set BLE_DA14585_ROOT=%REPO_ROOT%\ble\projects\target_apps\dsps\dsps_device\Keil_5
set PRJ_SOURCE=%REPO_ROOT%\src
set PYTHONPATH=%REPO_ROOT%\prebuilts\win32\python3
set COREPATH=%REPO_ROOT%\core\core_05.02.23

2>NUL CALL :CASE_%USER_BLE%
IF ERRORLEVEL 1 CALL :DEFAULT_CASE

if %BLE_COMPILE% == 0 (
	goto COMPILE_L610
)

set BLE_COMPILE_ROOT=%BLE_DA14585_ROOT%
cd %BLE_COMPILE_ROOT%
echo %cd%
call Compile.bat
cd %REPO_ROOT%

rem //delete old ble firmware
if exist "%PRJ_SOURCE%\user\include\dacode"  rd /S /Q %PRJ_SOURCE%\user\include\dacode
md "%PRJ_SOURCE%\user\include\dacode"

rem //convert to text
copy %BLE_COMPILE_ROOT%\releaseFile\%BLE_TXT_FILE_NAME% %PRJ_SOURCE%\user\include\dacode\dacode.txt
@del /F /S /Q %BLE_COMPILE_ROOT%\releaseFile\%BLE_TXT_FILE_NAME%

:COMPILE_L610
set timef=%time:~0,2%:%time:~3,2%:%time:~6,2%
echo Start at %timef%
call %REPO_ROOT%\tools\core_launch.bat
cd out\appimage_debug
cmake ..\.. -Wwarn -G Ninja
ninja clean
ninja -w dupbuild=err | ..\..\tee.exe ..\output.log

if exist ".\hex\app.pac" (
    echo product [31;1m %PRODUCT_NAME% [0m build [32;1m Successful [0m
) else (
    echo product [31;1m %PRODUCT_NAME% [0m build [31;1m Failed [0m
)

set timef=%time:~0,2%:%time:~3,2%:%time:~6,2%
echo End at %timef%
cd ..\..\..\
@TIMEOUT /T 200
EXIT /B

:CASE_1
    set PRODUCT_NAME=APP_RELEASE_WITH_BLE_UPDATE
    GOTO END_CASE
:CASE_2
    set PRODUCT_NAME=APP_RELEASE
    GOTO END_CASE
:END_CASE
    VER > NUL # reset ERRORLEVEL
    GOTO :EOF # return from CALL






