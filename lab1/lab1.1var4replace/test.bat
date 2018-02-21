set PROGRAM="%~1"

REM запуск программы без параметров
%PROGRAM%
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы с одним параметром
%PROGRAM% OneParameter
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы без output
%PROGRAM% input.txt "" "serched string" "rapleced string"
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы без input
%PROGRAM% "" out.txt "serched string" "rapleced string"
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы без search string
%PROGRAM% input.txt out.txt "" "rapleced string"
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы с 6 параметрами
%PROGRAM% input.txt out.txt "searchString" "replaceString" "someString"
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы с пустым файлом
%PROGRAM% empty.txt out.txt "hello world" "goodbay world"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outempty.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с 1-й строкой и 1-й заменой
%PROGRAM% string-1-or-more-replace.txt out.txt "hello" "world"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outstring-1-or-more-replace1.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с 1-й строкой и множественными заменами
%PROGRAM% string-1-or-more-replace.txt out.txt "ma" "mama"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outstring-1-or-more-replace2.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с множеством строк и множеством замен
%PROGRAM% multiline.txt out.txt "ma" "mama"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outmultiline1.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с множеством строк search и replace параметры больше 1 слова 
%PROGRAM% multiline.txt out.txt "Prince Vasili Kuragin" "Prince Kuragin"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outmultiline2.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы где нет такой искомой строки 
%PROGRAM% withoutstr.txt out.txt "Hello" "Prince Kuragin"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outwithoutstr.txt
IF ERRORLEVEL 1 GOTO err


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT