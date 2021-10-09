@echo off

set COREVERSION=L610_CORE "core_05.02.23"

REM del out\appimage_debug\hex\app.pac

@echo [123;92m05.02.23_product.bat[0m
@echo [101;93mChoose a product set below[0m
echo  B: BM5系列
echo  D: MX5D系列
echo  E: MX5E系列
echo  F: MX5F系列
echo  H: MX5H系列
echo  K: MX5K系列
echo  L: MX5L系列
echo  S: MX5S系列
echo  Y: MX5Y系列
echo  Z: MX5Z系列

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
echo  1: BM5H          (拜米   v15.22.x)
echo  2: BM5           (拜米   v15.36.x)
choice /c 12 /m "Enter"
if %ERRORLEVEL% == 1 set USER_CHOSICE=BM5H
if %ERRORLEVEL% == 2 set USER_CHOSICE=BM5
GOTO :PRODUCT_END

:PRODUCT_D
@echo [101;93mChoose a product type below[0m
echo  1: MX5D          (标品   v15.8.x)
echo  2: MX5D2         (标品   v15.12.x)
echo  3: MX5D4         (标品   v15.16.x)
echo  4: MX5D3_RF      (标品   v15.31.x)
echo  5: MX5D3         (标品   v15.47.x)
choice /c 12345 /m "Enter"
if %ERRORLEVEL% == 1 set USER_CHOSICE=MX5D
if %ERRORLEVEL% == 2 set USER_CHOSICE=MX5D2
if %ERRORLEVEL% == 3 set USER_CHOSICE=MX5D4
if %ERRORLEVEL% == 4 set USER_CHOSICE=MX5D3_RF
if %ERRORLEVEL% == 5 set USER_CHOSICE=MX5D3
GOTO :PRODUCT_END

:PRODUCT_E
@echo [101;93mChoose a product type below[0m
echo  1: MX5E          (标品   v15.19.x)
choice /c 1 /m "Enter"
if %ERRORLEVEL% == 1 set USER_CHOSICE=MX5E
GOTO :PRODUCT_END

:PRODUCT_F
@echo [101;93mChoose a product type below[0m
echo  1: MX5F          (标品   v15.0.x)
echo  2: MX5F3         (标品   v15.3.x)
echo  3: MX5F_JDY      (筋斗云 v15.10.x)
echo  4: MX5F6_DD      (标品   v15.24.x)
echo  5: MX5F_JC       (脚撑版本 v15.26.x)
echo  6: MX5F7_DD      (标品   v15.34.x)
echo  7: MX5F3_TK      (???   v15.37.x)
echo  8: MX5F7_RF      (标品  v15.41.x)
echo  9: MX5F6_RF      (标品  v15.42.x)
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
echo  1: MX5H3         (标品   v15.4.x)
echo  2: MX5H          (标品   v15.9.x)
echo  3: MX5H5         (标品   v15.17.x)
echo  4: MX5H6_DD      (标品   v15.32.x)
echo  5: MX5H7_DD      (标品   v15.33.x)
echo  6: MX5H7_RF      (标品   v15.43.x)
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
echo  1: MX5K4         (标品   v15.1.x)
echo  2: MX5K3         (标品   v15.5.x)
echo  3: MX5K6         (标品   v15.13.x)
echo  4: MX5K2_LM      (绿盟   v15.21.x)
echo  5: MX5K6_DD      (标品   v15.23.x)
echo  6: MX5K6_LS      (标品   v15.27.x)
echo  7: MX5K7_DD      (标品   v15.35.x)
echo  8: MX5K8_RF      (标品   v15.38.x)
echo  9: MX5K4_XBD     (样机   v15.40.x)
echo  A: MX5K5         (标品   v15.45.x)
echo  B: MX5K6_RF      (标品   v15.46.x)
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
echo  1: MX5L3         (样机   v15.15.x)
choice /c 1 /m "Enter"
if %ERRORLEVEL% == 1 set USER_CHOSICE=MX5L3
GOTO :PRODUCT_END

:PRODUCT_S
@echo [101;93mChoose a product type below[0m
echo  1: MX5S          (标品   v15.14.x)
echo  2: MX5S2         (标品   v15.18.x)
choice /c 12 /m "Enter"
if %ERRORLEVEL% == 1 set USER_CHOSICE=MX5S
if %ERRORLEVEL% == 2 set USER_CHOSICE=MX5S2
GOTO :PRODUCT_END

:PRODUCT_Y
@echo [101;93mChoose a product type below[0m
echo  1: MX5Y          (标品   v15.28.x)
echo  2: MX5Y3         (标品   v15.29.x)
echo  3: MX5Y6_DD      (标品   v15.30.x)
echo  4: MX5Y6_RF      (标品   v15.39.x)
echo  5: MX5Y3_XL_CC   (标品   v15.44.x)
echo  6: MX5Y4         (标品   v15.48.x)
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
echo  1: MX5Z3         (标品   v15.6.x)
echo  2: MX5Z          (标品   v15.7.x)
echo  3: MX5Z5         (标品   v15.11.x)
choice /c 123 /m "Enter"
if %ERRORLEVEL% == 1 set USER_CHOSICE=MX5Z3
if %ERRORLEVEL% == 2 set USER_CHOSICE=MX5Z
if %ERRORLEVEL% == 3 set USER_CHOSICE=MX5Z5
GOTO :PRODUCT_END

:PRODUCT_END
ver > nul

REM 选择是否编译蓝牙
set BLE_COMPILE=0
@echo [101;93m是否编译蓝牙固件[0m
echo  1: 编译
echo  2: 不编译
choice /c 12 /m "Enter"
set USER_BLE=%ERRORLEVEL%
if %USER_BLE% == 1 (
    set BLE_COMPILE=1
)

REM 记录相关路径
rem 仓库根目录
set REPO_ROOT=%cd%
rem 工程CONFIG目录
set PRJ_CONFIG=%REPO_ROOT%\config
rem 蓝牙585根目录
set BLE_DA14585_ROOT=%REPO_ROOT%\ble\projects\target_apps\dsps\dsps_device\Keil_5
rem 用户代码目录
set PRJ_SOURCE=%REPO_ROOT%\src
rem Python环境目录
set PYTHONPATH=%REPO_ROOT%\prebuilts\win32\python3
rem 内核目录
set COREPATH=%REPO_ROOT%\core\core_05.02.23
REM 确定产品类型
2>NUL CALL :CASE_%USER_CHOSICE%
IF ERRORLEVEL 1 CALL :DEFAULT_CASE # if label doesn't exist

REM 修改cmakelist里的内核宏
setlocal enabledelayedexpansion
set Cmakelist=CMakeLists.txt
set backCmakelist=%REPO_ROOT%\CMakeLists_bk.txt
REM 删掉当前的Cmakelist.txt
if exist %Cmakelist% del /f %Cmakelist%

(for /f "tokens=*" %%i in (%backCmakelist%) do (
set s=%%i
set s=!s:L610_CORE ""=%COREVERSION%!
if !s!==%%i (
    echo !s! 
    ) else (
    echo !s!
    REM 用来给cmake提供宏定义 (产品型号，产品内核定义)
    echo add_definitions^(-DCOREVERSION23^)
    echo add_definitions^(-DAPP_PRODUCT^)
    
    if %USER_CHOSICE% == BM5 (
        REM 定义BM5，主要用于区分引用拜米系列的不同语音文件
        echo add_definitions^(-DBM5^)
    )
    if %USER_CHOSICE% == BM5H (
        REM 定义BM5，主要用于区分引用拜米系列的不同语音文件
        echo add_definitions^(-DBM5^)
    )

    )
))>%Cmakelist%

REM 编译CONFIG并返回
cd %PRJ_CONFIG%
rem 首先删掉原有的数组文件
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

REM 编译蓝牙并返回
set BLE_COMPILE_ROOT=%BLE_DA14585_ROOT%
cd %BLE_COMPILE_ROOT%
echo %cd%
call Compile.bat
cd %REPO_ROOT%

REM 重置蓝牙固件文件夹
if exist "%PRJ_SOURCE%\user\include\dacode"  rd /S /Q %PRJ_SOURCE%\user\include\dacode
md "%PRJ_SOURCE%\user\include\dacode"

REM 拷贝输出 txt   文件名在蓝牙编译脚本里定义
copy %BLE_COMPILE_ROOT%\releaseFile\%BLE_TXT_FILE_NAME% %PRJ_SOURCE%\user\include\dacode\dacode.txt
@del /F /S /Q %BLE_COMPILE_ROOT%\releaseFile\%BLE_TXT_FILE_NAME%

:COMPILE_L610
set timef=%time:~0,2%:%time:~3,2%:%time:~6,2%
echo Start at %timef%
::准备编译环境
if exist "%REPO_ROOT%\tools\pacgen.py"  del %REPO_ROOT%\tools\pacgen.py
copy %COREPATH%\pacgen.py %REPO_ROOT%\tools
call tools\core_launch.bat
cd out\appimage_debug

::cmake ninja 构建环境
cmake ..\.. -Wwarn -G Ninja

ninja clean

::ninja 执行编译
ninja -w dupbuild=err | ..\..\tee.exe ..\output.log

if exist ".\hex\app.pac" (
    echo product [31;1m %USER_CHOSICE% [0m build [32;1m Successful [0m
) else (
    echo product [31;1m %USER_CHOSICE% [0m build [31;1m Failed [0m
)

set timef=%time:~0,2%:%time:~3,2%:%time:~6,2%
echo End at %timef%

REM 删掉当前的Cmakelist.txt
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
