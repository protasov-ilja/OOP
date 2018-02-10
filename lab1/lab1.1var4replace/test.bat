REM запуск программы без параметров
lab1.1var4replace.exe
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы с одним параметром
lab1.1var4replace.exe OneParameter
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы без output
lab1.1var4replace.exe input.txt "" "serched string" "rapleced string"
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы без input
lab1.1var4replace.exe "" out.txt "serched string" "rapleced string"
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы без search string
lab1.1var4replace.exe input.txt out.txt "" "rapleced string"
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы с 6 параметрами
lab1.1var4replace.exe input.txt out.txt "searchString" "replaceString" "someString"
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы с пустым файлом
lab1.1var4replace.exe empty.txt out.txt "hello world" "goodbay world"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outempty.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с 1-й строкой и 1-й заменой
lab1.1var4replace.exe string-1-or-more-replace.txt out.txt "hello" "world"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outstring-1-or-more-replace1.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с 1-й строкой и множественными заменами
lab1.1var4replace.exe string-1-or-more-replace.txt out.txt "ma" "mama"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outstring-1-or-more-replace2.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с множеством строк и множеством замен
lab1.1var4replace.exe multiline.txt out.txt "ma" "mama"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outmultiline1.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с множеством строк search и replace параметры больше 1 слова 
lab1.1var4replace.exe multiline.txt out.txt "Prince Vasili Kuragin" "Prince Kuragin"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outmultiline2.txt
IF ERRORLEVEL 1 GOTO err


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT