set PROGRAM="%~1"

REM запуск программы без параметров
%PROGRAM%
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы с одним параметром
%PROGRAM% OneParameter
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы без search string
%PROGRAM% < input.txt > "%TEMP%\out.txt" "" "rapleced string"
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы с 6 параметрами
%PROGRAM% < input.txt > "%TEMP%\out.txt" "searchString" "replaceString" "someString"
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы с пустым файлом
%PROGRAM% < empty.txt > "%TEMP%\out.txt" "hello world" "goodbay world"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" outempty.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с 1-й строкой и 1-й заменой
%PROGRAM% < string-1-or-more-replace.txt > "%TEMP%\out1.txt" "hello" "world"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out1.txt" outstring-1-or-more-replace1.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с 1-й строкой и множественными заменами
%PROGRAM% < string-1-or-more-replace.txt > "%TEMP%\out2.txt" "ma" "mama"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out2.txt" outstring-1-or-more-replace2.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с множеством строк и множеством замен
%PROGRAM% < multiline.txt > "%TEMP%\out3.txt" "ma" "mama"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out3.txt" outmultiline1.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с множеством строк search и replace параметры больше 1 слова 
%PROGRAM% < multiline.txt > "%TEMP%\out4.txt" "Prince Vasili Kuragin" "Prince Kuragin"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out4.txt" outmultiline2.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы где нет такой искомой строки 
%PROGRAM% < withoutstr.txt > "%TEMP%\out6.txt" "Hello" "Prince Kuragin"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out6.txt" outwithoutstr.txt
IF ERRORLEVEL 1 GOTO err


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT