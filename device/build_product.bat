@echo off

set COREVERSION=L610_CORE "core_05.02.23"

REM del out\appimage_debug\hex\app.pac

@echo [123;92m05.02.23_product.bat[0m
@echo [101;93mChoose a product set below[0m
echo  B: BM5ÏµÁÐ
echo  D: MX5DÏµÁÐ
echo  E: MX5EÏµÁÐ
echo  F: MX5FÏµÁÐ
echo  H: MX5HÏµÁÐ
echo  K: MX5KÏµÁÐ
echo  L: MX5LÏµÁÐ
echo  S: MX5SÏµÁÐ
echo  Y: MX5YÏµÁÐ
echo  Z: MX5ZÏµÁÐ

choice /c BDEFHKLSYZ /m "Enter"
if %ERRORLEVEL% == 1  GOTO :PRODUCT_B
if %ERRORLEVEL% == 2  GOTO :PRODUCT_D
if %ERRORLEVEL% == 3  GOTO :PRODUCT_E
if %ERRORLEVEL% == 4  GOTO :PRODUCT_F
if %ERRORLEVEL% == 5  GOTO :PRODUCT_H
if %ERRORLEVEL% == 6  GOTO :PRODUCT_K
if %ERRORLEVEL% == 7  GOTO :PRODUCT_L
if %ERRORLEVEL% == 8  GOTO :PRODUCT_S
if %ERRORLEVEL% == 9  GOTO :PRODUCT_Y
if %ERRORLEVEL% == 10 GOTO :PRODUCT_Z

:PRODUCT_B
@echo [101;93mChoose a product type below[0m
echo  1: BM5H          (°ÝÃ×   v15.22.x)
echo  2: BM5           (°ÝÃ×   v15.36.x)
choice /c 12 /m "Enter"
if %ERRORLEVEL% == 1 set USER_CHOSICE=BM5H
if %ERRORLEVEL% == 2 set USER_CHOSICE=BM5
GOTO :PRODUCT_END

:PRODUCT_D
@echo [101;93mChoose a product type below[0m
echo  1: MX5D          (±êÆ·   v15.8.x)
echo  2: MX5D2         (±êÆ·   v15.12.x)
echo  3: MX5D4         (±êÆ·   v15.16.x)
echo  4: MX5D3_RF      (±êÆ·   v15.31.x)
echo  5: MX5D3         (±êÆ·   v15.47.x)
choice /c 12345 /m "Enter"
if %ERRORLEVEL% == 1 set USER_CHOSICE=MX5D
if %ERRORLEVEL% == 2 set USER_CHOSICE=MX5D2
if %ERRORLEVEL% == 3 set USER_CHOSICE=MX5D4
if %ERRORLEVEL% == 4 set USER_CHOSICE=MX5D3_RF
if %ERRORLEVEL% == 5 set USER_CHOSICE=MX5D3
GOTO :PRODUCT_END

:PRODUCT_E
@echo [101;93mChoose a product type below[0m
echo  1: MX5E          (±êÆ·   v15.19.x)
choice /c 1 /m "Enter"
if %ERRORLEVEL% == 1 set USER_CHOSICE=MX5E
GOTO :PRODUCT_END

:PRODUCT_F
@echo [101;93mChoose a product type below[0m
echo  1: MX5F          (±êÆ·   v15.0.x)
echo  2: MX5F3         (±êÆ·   v15.3.x)
echo  3: MX5F_JDY      (½î¶·ÔÆ v15.10.x)
echo  4: MX5F6_DD      (±êÆ·   v15.24.x)
echo  5: MX5F_JC       (½Å³Å°æ±¾ v15.26.x)
echo  6: MX5F7_DD      (±êÆ·   v15.34.x)
echo  7: MX5F3_TK      (???   v15.37.x)
echo  8: MX5F7_RF      (±êÆ·  v15.41.x)
echo  9: MX5F6_RF      (±êÆ·  v15.42.x)
choice /c 123456789 /m "Enter"
if %ERRORLEVEL% == 1 set USER_CHOSICE=MX5F
if %ERRORLEVEL% == 2 set USER_CHOSICE=MX5F3
if %ERRORLEVEL% == 3 set USER_CHOSICE=MX5F_JDY
if %ERRORLEVEL% == 4 set USER_CHOSICE=MX5F6_DD
if %ERRORLEVEL% == 5 set USER_CHOSICE=MX5F_JC
if %ERRORLEVEL% == 6 set USER_CHOSICE=MX5F7_DD
if %ERRORLEVEL% == 7 set USER_CHOSICE=MX5F3_TK
if %ERRORLEVEL% == 8 set USER_CHOSICE=MX5F7_RF
if %ERRORLEVEL% == 9 set USER_CHOSICE=MX5F6_RF
GOTO :PRODUCT_END

:PRODUCT_H
@echo [101;93mChoose a product type below[0m
echo  1: MX5H3         (±êÆ·   v15.4.x)
echo  2: MX5H          (±êÆ·   v15.9.x)
echo  3: MX5H5         (±êÆ·   v15.17.x)
echo  4: MX5H6_DD      (±êÆ·   v15.32.x)
echo  5: MX5H7_DD      (±êÆ·   v15.33.x)
echo  6: MX5H7_RF      (±êÆ·   v15.43.x)
choice /c 123456 /m "Enter"
if %ERRORLEVEL% == 1 set USER_CHOSICE=MX5H3
if %ERRORLEVEL% == 2 set USER_CHOSICE=MX5H
if %ERRORLEVEL% == 3 set USER_CHOSICE=MX5H5
if %ERRORLEVEL% == 4 set USER_CHOSICE=MX5H6_DD
if %ERRORLEVEL% == 5 set USER_CHOSICE=MX5H7_DD
if %ERRORLEVEL% == 6 set USER_CHOSICE=MX5H7_RF
GOTO :PRODUCT_END

:PRODUCT_K
@echo [101;93mChoose a product type below[0m
echo  1: MX5K4         (±êÆ·   v15.1.x)
echo  2: MX5K3         (±êÆ·   v15.5.x)
echo  3: MX5K6         (±êÆ·   v15.13.x)
echo  4: MX5K2_LM      (ÂÌÃË   v15.21.x)
echo  5: MX5K6_DD      (±êÆ·   v15.23.x)
echo  6: MX5K6_LS      (±êÆ·   v15.27.x)
echo  7: MX5K7_DD      (±êÆ·   v15.35.x)
echo  8: MX5K8_RF      (±êÆ·   v15.38.x)
echo  9: MX5K4_XBD     (Ñù»ú   v15.40.x)
echo  A: MX5K5         (±êÆ·   v15.45.x)
echo  B: MX5K6_RF      (±êÆ·   v15.46.x)
choice /c 123456789AB /m "Enter"
if %ERRORLEVEL% == 1 set USER_CHOSICE=MX5K4
if %ERRORLEVEL% == 2 set USER_CHOSICE=MX5K3
if %ERRORLEVEL% == 3 set USER_CHOSICE=MX5K6
if %ERRORLEVEL% == 4 set USER_CHOSICE=MX5K2_LM
if %ERRORLEVEL% == 5 set USER_CHOSICE=MX5K6_DD
if %ERRORLEVEL% == 6 set USER_CHOSICE=MX5K6_LS
if %ERRORLEVEL% == 7 set USER_CHOSICE=MX5K7_DD
if %ERRORLEVEL% == 8 set USER_CHOSICE=MX5K8_RF
if %ERRORLEVEL% == 9 set USER_CHOSICE=MX5K4_XBD
if %ERRORLEVEL% == 10 set USER_CHOSICE=MX5K5
if %ERRORLEVEL% == 11 set USER_CHOSICE=MX5K6_RF
GOTO :PRODUCT_END

:PRODUCT_L
@echo [101;93mChoose a product type below[0m
echo  1: MX5L3         (Ñù»ú   v15.15.x)
choice /c 1 /m "Enter"
if %ERRORLEVEL% == 1 set USER_CHOSICE=MX5L3
GOTO :PRODUCT_END

:PRODUCT_S
@echo [101;93mChoose a product type below[0m
echo  1: MX5S          (±êÆ·   v15.14.x)
echo  2: MX5S2         (±êÆ·   v15.18.x)
choice /c 12 /m "Enter"
if %ERRORLEVEL% == 1 set USER_CHOSICE=MX5S
if %ERRORLEVEL% == 2 set USER_CHOSICE=MX5S2
GOTO :PRODUCT_END

:PRODUCT_Y
@echo [101;93mChoose a product type below[0m
echo  1: MX5Y          (±êÆ·   v15.28.x)
echo  2: MX5Y3         (±êÆ·   v15.29.x)
echo  3: MX5Y6_DD      (±êÆ·   v15.30.x)
echo  4: MX5Y6_RF      (±êÆ·   v15.39.x)
echo  5: MX5Y3_XL_CC   (±êÆ·   v15.44.x)
echo  6: MX5Y4         (±êÆ·   v15.48.x)
choice /c 123456 /m "Enter"
if %ERRORLEVEL% == 1 set USER_CHOSICE=MX5Y
if %ERRORLEVEL% == 2 set USER_CHOSICE=MX5Y3
if %ERRORLEVEL% == 3 set USER_CHOSICE=MX5Y6_DD
if %ERRORLEVEL% == 4 set USER_CHOSICE=MX5Y6_RF
if %ERRORLEVEL% == 5 set USER_CHOSICE=MX5Y3_XL_CC
if %ERRORLEVEL% == 6 set USER_CHOSICE=MX5Y4
GOTO :PRODUCT_END

:PRODUCT_Z
@echo [101;93mChoose a product type below[0m
echo  1: MX5Z3         (±êÆ·   v15.6.x)
echo  2: MX5Z          (±êÆ·   v15.7.x)
echo  3: MX5Z5         (±êÆ·   v15.11.x)
choice /c 123 /m "Enter"
if %ERRORLEVEL% == 1 set USER_CHOSICE=MX5Z3
if %ERRORLEVEL% == 2 set USER_CHOSICE=MX5Z
if %ERRORLEVEL% == 3 set USER_CHOSICE=MX5Z5
GOTO :PRODUCT_END

:PRODUCT_END
ver > nul

REM Ñ¡ÔñÊÇ·ñ±àÒëÀ¶ÑÀ
set BLE_COMPILE=0
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
2>NUL CALL :CASE_%USER_CHOSICE%
IF ERRORLEVEL 1 CALL :DEFAULT_CASE # if label doesn't exist

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
    echo add_definitions^(-DAPP_PRODUCT^)
    
    if %USER_CHOSICE% == BM5 (
        REM ¶¨ÒåBM5£¬Ö÷ÒªÓÃÓÚÇø·ÖÒýÓÃ°ÝÃ×ÏµÁÐµÄ²»Í¬ÓïÒôÎÄ¼þ
        echo add_definitions^(-DBM5^)
    )
    if %USER_CHOSICE% == BM5H (
        REM ¶¨ÒåBM5£¬Ö÷ÒªÓÃÓÚÇø·ÖÒýÓÃ°ÝÃ×ÏµÁÐµÄ²»Í¬ÓïÒôÎÄ¼þ
        echo add_definitions^(-DBM5^)
    )

    )
))>%Cmakelist%

REM ±àÒëCONFIG²¢·µ»Ø
cd %PRJ_CONFIG%
rem Ê×ÏÈÉ¾µôÔ­ÓÐµÄÊý×éÎÄ¼þ
if exist "%PRJ_CONFIG%\default_config.txt" del %PRJ_CONFIG%\default_config.txt
if exist "%REPO_ROOT%\src\user\include\config\default_config.txt" del %REPO_ROOT%\src\user\include\config\default_config.txt
if exist "%PRJ_CONFIG%\product_type.txt" del %PRJ_CONFIG%\product_type.txt
if not "%PRODUCT_CONFIG% "=="" (
echo %PRODUCT_CONFIG%>product_type.txt
)

start %PYTHONPATH%\python.exe conf.py
choice /t 1 /d y /n >nul
cd %REPO_ROOT%
if not exist %REPO_ROOT%\src\user\include\config md %REPO_ROOT%\src\user\include\config
copy %PRJ_CONFIG%\default_config.txt %REPO_ROOT%\src\user\include\config\default_config.txt
@if exist "%PRJ_CONFIG%\product_type.txt" del %PRJ_CONFIG%\product_type.txt
@if exist "%PRJ_CONFIG%\default_config.txt" del %PRJ_CONFIG%\default_config.txt
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
    echo product [31;1m %USER_CHOSICE% [0m build [32;1m Successful [0m
) else (
    echo product [31;1m %USER_CHOSICE% [0m build [31;1m Failed [0m
)

set timef=%time:~0,2%:%time:~3,2%:%time:~6,2%
echo End at %timef%

REM É¾µôµ±Ç°µÄCmakelist.txt
del /f ..\..\%Cmakelist%

cd ..\..\..\
@TIMEOUT /T 200
EXIT /B

:CASE_BM5H
    set PRODUCT_CONFIG=config_BM5H.json
    GOTO END_CASE
:CASE_BM5
    set PRODUCT_CONFIG=config_BM5.json
    GOTO END_CASE

:CASE_MX5D
    set PRODUCT_CONFIG=config_MX5D.json
    GOTO END_CASE
:CASE_MX5D2
    set PRODUCT_CONFIG=config_MX5D2.json
    GOTO END_CASE
:CASE_MX5D4
    set PRODUCT_CONFIG=config_MX5D4.json
    GOTO END_CASE
:CASE_MX5D3_RF
    set PRODUCT_CONFIG=config_MX5D3_RF.json
    GOTO END_CASE
:CASE_MX5D3
    set PRODUCT_CONFIG=config_MX5D3.json
    GOTO END_CASE

:CASE_MX5E
    set PRODUCT_CONFIG=config_MX5E.json
    GOTO END_CASE

:CASE_MX5F
    set PRODUCT_CONFIG=config_MX5F.json
    GOTO END_CASE
:CASE_MX5F3
    set PRODUCT_CONFIG=config_MX5F3.json
    GOTO END_CASE
:CASE_MX5F_JDY
    set PRODUCT_CONFIG=config_MX5F_JDY.json
    GOTO END_CASE
:CASE_MX5F6_DD
    set PRODUCT_CONFIG=config_MX5F6_DD.json
    GOTO END_CASE
:CASE_MX5F_JC
    set PRODUCT_CONFIG=config_MX5F_JC.json
    GOTO END_CASE
:CASE_MX5F7_DD
    set PRODUCT_CONFIG=config_MX5F7_DD.json
    GOTO END_CASE
:CASE_MX5F3_TK
    set PRODUCT_CONFIG=config_MX5F3_TK.json
    GOTO END_CASE
:CASE_MX5F7_RF
    set PRODUCT_CONFIG=config_MX5F7_RF.json
    GOTO END_CASE
:CASE_MX5F6_RF
    set PRODUCT_CONFIG=config_MX5F6_RF.json
    GOTO END_CASE

:CASE_MX5H3
    set PRODUCT_CONFIG=config_MX5H3.json
    GOTO END_CASE
:CASE_MX5H
    set PRODUCT_CONFIG=config_MX5H.json
    GOTO END_CASE
:CASE_MX5H5
    set PRODUCT_CONFIG=config_MX5H5.json
    GOTO END_CASE
:CASE_MX5H6_DD
    set PRODUCT_CONFIG=config_MX5H6_DD.json
    GOTO END_CASE
:CASE_MX5H7_DD
    set PRODUCT_CONFIG=config_MX5H7_DD.json
    GOTO END_CASE
:CASE_MX5H7_RF
    set PRODUCT_CONFIG=config_MX5H7_RF.json
    GOTO END_CASE

:CASE_MX5K4
    set PRODUCT_CONFIG=config_MX5K4.json
    GOTO END_CASE
:CASE_MX5K3
    set PRODUCT_CONFIG=config_MX5K3.json
    GOTO END_CASE
:CASE_MX5K6
    set PRODUCT_CONFIG=config_MX5K6.json
    GOTO END_CASE
:CASE_MX5K2_LM
    set PRODUCT_CONFIG=config_MX5K2_LM.json
    GOTO END_CASE
:CASE_MX5K6_DD
    set PRODUCT_CONFIG=config_MX5K6_DD.json
    GOTO END_CASE
:CASE_MX5K6_LS
    set PRODUCT_CONFIG=config_MX5K6_LS.json
    GOTO END_CASE
:CASE_MX5K7_DD
    set PRODUCT_CONFIG=config_MX5K7_DD.json
    GOTO END_CASE
:CASE_MX5K8_RF
    set PRODUCT_CONFIG=config_MX5K8_RF.json
    GOTO END_CASE
:CASE_MX5K4_XBD
    set PRODUCT_CONFIG=config_MX5K4_XBD.json
    GOTO END_CASE
:CASE_MX5K5
    set PRODUCT_CONFIG=config_MX5K5.json
    GOTO END_CASE
:CASE_MX5K6_RF
    set PRODUCT_CONFIG=config_MX5K6_RF.json
    GOTO END_CASE

:CASE_MX5L3
    set PRODUCT_CONFIG=config_MX5L3.json
    GOTO END_CASE

:CASE_MX5S
    set PRODUCT_CONFIG=config_MX5S.json
    GOTO END_CASE
:CASE_MX5S2
    set PRODUCT_CONFIG=config_MX5S2.json
    GOTO END_CASE

:CASE_MX5Y
    set PRODUCT_CONFIG=config_MX5Y.json
    GOTO END_CASE
:CASE_MX5Y3
    set PRODUCT_CONFIG=config_MX5Y3.json
    GOTO END_CASE
:CASE_MX5Y6_DD
    set PRODUCT_CONFIG=config_MX5Y6_DD.json
	GOTO END_CASE
:CASE_MX5Y6_RF
    set PRODUCT_CONFIG=config_MX5Y6_RF.json
    GOTO END_CASE
:CASE_MX5Y3_XL_CC
    set PRODUCT_CONFIG=config_MX5Y3_XL_CC.json
    GOTO END_CASE
:CASE_MX5Y4
    set PRODUCT_CONFIG=config_MX5Y4.json
    GOTO END_CASE

:CASE_MX5Z3
    set PRODUCT_CONFIG=config_MX5Z3.json
    GOTO END_CASE
:CASE_MX5Z
    set PRODUCT_CONFIG=config_MX5Z.json
    GOTO END_CASE
:CASE_MX5Z5
    set PRODUCT_CONFIG=config_MX5Z5.json
    GOTO END_CASE

:END_CASE
    VER > NUL # reset ERRORLEVEL
    GOTO :EOF # return from CALL
