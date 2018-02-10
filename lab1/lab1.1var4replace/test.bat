REM ������ ��������� ��� ����������
lab1.1var4replace.exe
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � ����� ����������
lab1.1var4replace.exe OneParameter
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� ��� output
lab1.1var4replace.exe input.txt "" "serched string" "rapleced string"
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� ��� input
lab1.1var4replace.exe "" out.txt "serched string" "rapleced string"
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� ��� search string
lab1.1var4replace.exe input.txt out.txt "" "rapleced string"
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � 6 �����������
lab1.1var4replace.exe input.txt out.txt "searchString" "replaceString" "someString"
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � ������ ������
lab1.1var4replace.exe empty.txt out.txt "hello world" "goodbay world"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outempty.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � 1-� ������� � 1-� �������
lab1.1var4replace.exe string-1-or-more-replace.txt out.txt "hello" "world"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outstring-1-or-more-replace1.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � 1-� ������� � �������������� ��������
lab1.1var4replace.exe string-1-or-more-replace.txt out.txt "ma" "mama"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outstring-1-or-more-replace2.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � ���������� ����� � ���������� �����
lab1.1var4replace.exe multiline.txt out.txt "ma" "mama"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outmultiline1.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � ���������� ����� search � replace ��������� ������ 1 ����� 
lab1.1var4replace.exe multiline.txt out.txt "Prince Vasili Kuragin" "Prince Kuragin"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outmultiline2.txt
IF ERRORLEVEL 1 GOTO err


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT