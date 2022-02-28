@echo Generate bin...

@SET PATH=%KEIL_BIN%

@fromelf.exe "%BLE_OUTPUT_PATH%\dacode.axf" --bincombined --output "%BLE_OUTPUT_PATH%\dacode.bin"
