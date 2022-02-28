@echo Read config.bat

set PRD_TYPE_FOR_BLE=-%PRODUCT%-
@ECHO [33;1m BLE: PRD_TYPE IS %PRD_TYPE_FOR_BLE%  [0m
set FUNC_MOD=

if not "%FUNC_MOD%"==""  (
	echo %FUNC_MOD% > %BLE_COMPILE_ROOT%\%BLE_MICRO_FILE_NAME%
) else (
	copy nul %BLE_COMPILE_ROOT%\%BLE_MICRO_FILE_NAME%
)
