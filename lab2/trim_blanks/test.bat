set PROGRAM="%~1"



REM emptyfile
%PROGRAM% < empty.txt > "%TEMP%\out3.txt"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out3.txt" outempty.txt
IF ERRORLEVEL 1 GOTO err

REM one simbol
%PROGRAM% < one_simbol.txt > "%TEMP%\out1.txt"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out1.txt" output1.txt
IF ERRORLEVEL 1 GOTO err

REM some strings
%PROGRAM% < some_strings.txt > "%TEMP%\out.txt"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" output2.txt
IF ERRORLEVEL 1 GOTO err


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT