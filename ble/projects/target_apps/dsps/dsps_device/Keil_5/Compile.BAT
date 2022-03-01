@echo off
chcp 65001
REM 定义相关名称
rem 蓝牙工程名
set BLE_PRJ_NAME=dsps_device.uvprojx
rem 蓝牙编译日志文件名
set BLE_LOG_FILE_NAME=ble_build_log.txt
rem 最终输出蓝牙txt文件名
set BLE_TXT_FILE_NAME=dacode.txt
rem 最终输出蓝牙数组名
set BLE_ARRAY_NAME=src_dacode
rem 蓝牙工程输出目录
set BLE_OUTPUT_PATH=%cd%\out_585
rem 蓝牙编译宏配置文件名
set BLE_MICRO_FILE_NAME=ble_micro.opt
rem 蓝牙配置脚本文件名
set BLE_CONFIG_FILE_NAME=config.bat

REM 寻找 "config.bat" 的路径 默认在在本目录下找
if exist "%BLE_CONFIG_FILE_NAME%" (
	set PATH_CONFIG=%cd%
) else ( 
	echo [31;1m  Interrupt: The script "%BLE_CONFIG_FILE_NAME%" not found ! [0m
	pause 
	exit
)

echo PATH_CONFIG: %PATH_CONFIG%

REM 寻找 "Bin2Array.exe" 的路径 默认在大仓库根目录，否则为单独编译在本目录下找
if "%REPO_ROOT%"=="" ( 
	if exist "Bin2Array.exe" (
		set PATH_BIN2ARRAY=%cd%
	) else ( 
		echo [31;1m  Interrupt: The tool "Bin2Array.exe" not found ! [0m
		pause 
		exit
	)
) else ( 
	if exist "%REPO_ROOT%\Bin2Array.exe" (
		set PATH_BIN2ARRAY=%REPO_ROOT%
	) else (
		echo [31;1m  Interrupt: The tool "Bin2Array.exe" not found ! [0m
		pause 
		exit
	)
) 
echo PATH_BIN2ARRAY: %PATH_BIN2ARRAY%


REM 删除旧的宏配置文件
if exist "%BLE_MICRO_FILE_NAME%"  del %BLE_MICRO_FILE_NAME%

REM 接受产品类型，输出宏配置文件
call %PATH_CONFIG%\%BLE_CONFIG_FILE_NAME% 

REM 打印宏配置文件内容
echo.
echo [36;1m  GET Micro_config File "%BLE_MICRO_FILE_NAME%" : [0m
type %BLE_MICRO_FILE_NAME%
echo.
echo [36;1m  Micro_config File END [0m
echo.

REM 重置输出文件夹
if exist "%BLE_OUTPUT_PATH%" (
	rd /S /Q %BLE_OUTPUT_PATH%
)
md %BLE_OUTPUT_PATH%
if exist "releaseFile" (
	rd /S /Q .\releaseFile
)
md releaseFile


REM This is the keil project path
set UV_PRO_PATH=.\%BLE_PRJ_NAME%
echo [33;1m  Compiling, plz wait about 30 sec ... [0m
echo [33;1m  compile log will be saved as "%BLE_LOG_FILE_NAME%" [0m

REM PLZ ADD "your mdk5 install path\UV4" to system path "Path", so "UV4.exe" can be found
UV4.EXE -j0 -r %UV_PRO_PATH% -o %cd%\releaseFile\%BLE_LOG_FILE_NAME%
set compile_err=%ERRORLEVEL%

REM 打印编译日志
type %cd%\releaseFile\%BLE_LOG_FILE_NAME%
REM 删除生成的宏配置文件
if exist "%BLE_MICRO_FILE_NAME%"  del %BLE_MICRO_FILE_NAME%

REM 拷贝一份日志到大仓库的日志目录
if not "%REPO_ROOT%"=="" ( 
	copy %BLE_COMPILE_ROOT%\releaseFile\%BLE_LOG_FILE_NAME% %REPO_ROOT%\out\%BLE_LOG_FILE_NAME% 
)


REM 编译结果反馈
echo [33;1m  error level is %compile_err% [0m
if %compile_err% == 0 (
	echo [32;1m  No Errors or Warnings ! [0m
)

if %compile_err% == 1 (
	echo [32;1m  Warnings  Only ! [0m
)

if %compile_err% geq 2 (
	echo [31;1m  2   Errors ! [0m
	echo [31;1m  3	Fatal Errors [0m
	echo [31;1m  11	Cannot open project file for writing [0m
	echo [31;1m  12	Device with given name in not found in database [0m
	echo [31;1m  13	Error writing project file [0m
	echo [31;1m  15	Error reading import XML file [0m
	echo [31;1m  20	Error converting project [0m
	pause
	exit
)
REM 拷贝输出的 BIN 文件
copy %BLE_OUTPUT_PATH%\dacode.bin .\releaseFile\dacode.bin


REM 由 bin 生成 txt
%PATH_BIN2ARRAY%\Bin2Array.exe -i .\releaseFile\dacode.bin -o .\releaseFile\%BLE_TXT_FILE_NAME% -a %BLE_ARRAY_NAME%
if %errorlevel%==0 (
    echo [32;1m DA14585 CODE COMPILE SUCCESSFUL!  [0m
) else (
    echo [31;1m DA14585 CODE COMPILE ERROR!  [0m
    pause
    exit
)

REM 如果为单独直接编译蓝牙，则完成后停止
if "%REPO_ROOT%"=="" ( pause )
