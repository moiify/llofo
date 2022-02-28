:: test compile
@echo off

::set PRODUCT_TYPE=MX3F
::set PRODUCT_TYPE=ME4B
::set PRODUCT_TYPE=ME4C
::set PRODUCT_TYPE=MX3E
set PRODUCT_TYPE=ME4BB
::set PRODUCT_TYPE=SHARINGX3_GJ

::call ./config %PRODUCT_TYPE%

call ./Compile
::call test.bat


pause
