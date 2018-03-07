set PROGRAM="%~1"

REM start program without arguments
%PROGRAM% 
IF NOT ERRORLEVEL 1 GOTO err

REM stringfile
%PROGRAM% < input3.txt
IF  NOT ERRORLEVEL 1 GOTO err

REM emptyfile
%PROGRAM% < empty.txt
IF  NOT ERRORLEVEL 1 GOTO err

REM one number
%PROGRAM% < input2.txt > out1.txt
IF ERRORLEVEL 1 GOTO err
FC out1.txt output2.txt
IF ERRORLEVEL 1 GOTO err

REM some numbers
%PROGRAM% < input1.txt > out.txt
IF ERRORLEVEL 1 GOTO err
FC out.txt output1.txt
IF ERRORLEVEL 1 GOTO err


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT