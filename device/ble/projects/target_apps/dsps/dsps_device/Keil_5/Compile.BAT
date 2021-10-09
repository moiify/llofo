@echo off

REM ¶¨ÒåÏà¹ØÃû³Æ
rem À¶ÑÀ¹¤³ÌÃû
set BLE_PRJ_NAME=dsps_device.uvprojx
rem À¶ÑÀ±àÒëÈÕÖ¾ÎÄ¼şÃû
set BLE_LOG_FILE_NAME=ble_build_log.txt
rem ×îÖÕÊä³öÀ¶ÑÀtxtÎÄ¼şÃû
set BLE_TXT_FILE_NAME=dacode.txt
rem ×îÖÕÊä³öÀ¶ÑÀÊı×éÃû
set BLE_ARRAY_NAME=src_dacode
rem À¶ÑÀ¹¤³ÌÊä³öÄ¿Â¼
set BLE_OUTPUT_PATH=%cd%\out_585
rem À¶ÑÀ±àÒëºêÅäÖÃÎÄ¼şÃû
set BLE_MICRO_FILE_NAME=ble_micro.opt
rem À¶ÑÀÅäÖÃ½Å±¾ÎÄ¼şÃû
set BLE_CONFIG_FILE_NAME=config.bat

REM Ñ°ÕÒ "config.bat" µÄÂ·¾¶ Ä¬ÈÏÔÚÔÚ±¾Ä¿Â¼ÏÂÕÒ
if exist "%BLE_CONFIG_FILE_NAME%" (
	set PATH_CONFIG=%cd%
) else ( 
	echo [31;1m  Interrupt: The script "%BLE_CONFIG_FILE_NAME%" not found ! [0m
	pause 
	exit
)

echo PATH_CONFIG: %PATH_CONFIG%

REM Ñ°ÕÒ "Bin2Array.exe" µÄÂ·¾¶ Ä¬ÈÏÔÚ´ó²Ö¿â¸ùÄ¿Â¼£¬·ñÔòÎªµ¥¶À±àÒëÔÚ±¾Ä¿Â¼ÏÂÕÒ
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


REM É¾³ı¾ÉµÄºêÅäÖÃÎÄ¼ş
if exist "%BLE_MICRO_FILE_NAME%"  del %BLE_MICRO_FILE_NAME%

REM ½ÓÊÜ²úÆ·ÀàĞÍ£¬Êä³öºêÅäÖÃÎÄ¼ş
call %PATH_CONFIG%\%BLE_CONFIG_FILE_NAME% 

REM ´òÓ¡ºêÅäÖÃÎÄ¼şÄÚÈİ
echo.
echo [36;1m  GET Micro_config File "%BLE_MICRO_FILE_NAME%" : [0m
type %BLE_MICRO_FILE_NAME%
echo.
echo [36;1m  Micro_config File END [0m
echo.

REM ÖØÖÃÊä³öÎÄ¼ş¼Ğ
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

REM ´òÓ¡±àÒëÈÕÖ¾
type %cd%\releaseFile\%BLE_LOG_FILE_NAME%
REM É¾³ıÉú³ÉµÄºêÅäÖÃÎÄ¼ş
if exist "%BLE_MICRO_FILE_NAME%"  del %BLE_MICRO_FILE_NAME%

REM ¿½±´Ò»·İÈÕÖ¾µ½´ó²Ö¿âµÄÈÕÖ¾Ä¿Â¼
if not "%REPO_ROOT%"=="" ( 
	copy %BLE_COMPILE_ROOT%\releaseFile\%BLE_LOG_FILE_NAME% %REPO_ROOT%\out\%BLE_LOG_FILE_NAME% 
)


REM ±àÒë½á¹û·´À¡
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
REM ¿½±´Êä³öµÄ BIN ÎÄ¼ş
copy %BLE_OUTPUT_PATH%\dacode.bin .\releaseFile\dacode.bin


REM ÓÉ bin Éú³É txt
%PATH_BIN2ARRAY%\Bin2Array.exe -i .\releaseFile\dacode.bin -o .\releaseFile\%BLE_TXT_FILE_NAME% -a %BLE_ARRAY_NAME%
if %errorlevel%==0 (
    echo [32;1m DA14585 CODE COMPILE SUCCESSFUL!  [0m
) else (
    echo [31;1m DA14585 CODE COMPILE ERROR!  [0m
    pause
    exit
)

REM Èç¹ûÎªµ¥¶ÀÖ±½Ó±àÒëÀ¶ÑÀ£¬ÔòÍê³ÉºóÍ£Ö¹
if "%REPO_ROOT%"=="" ( pause )
