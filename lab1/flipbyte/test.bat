set PROGRAM="%~1"

REM run without parameters
%PROGRAM%
IF NOT ERRORLEVEL 1 GOTO err

REM run with 2 parameters
%PROGRAM% 22 hello
IF NOT ERRORLEVEL 1 GOTO err

REM run with a value greater than 255
%PROGRAM% 256
IF NOT ERRORLEVEL 1 GOTO err

REM run with a value less than 0
%PROGRAM% -1
IF NOT ERRORLEVEL 1 GOTO err

REM run with a value greater than the integer type
%PROGRAM% 200000000000000
IF NOT ERRORLEVEL 1 GOTO err

REM run with string type parameter
%PROGRAM% "string"
IF NOT ERRORLEVEL 1 GOTO err

REM 0 - 0
%PROGRAM% 0 > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt out0.txt
IF ERRORLEVEL 1 GOTO err

REM 255 - 255
%PROGRAM% 255 > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt out255.txt
IF ERRORLEVEL 1 GOTO err

REM 1 - 128
%PROGRAM% 1 > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt out128.txt
IF ERRORLEVEL 1 GOTO err

REM 154 - 89
%PROGRAM% 154 > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt out89.txt
IF ERRORLEVEL 1 GOTO err


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT