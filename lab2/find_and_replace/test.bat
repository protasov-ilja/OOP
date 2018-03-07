set PROGRAM="%~1"

REM ������ ��������� ��� ����������
%PROGRAM%
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � ����� ����������
%PROGRAM% OneParameter
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� ��� search string
%PROGRAM% < input.txt > "%TEMP%\out.txt" "" "rapleced string"
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � 6 �����������
%PROGRAM% < input.txt > "%TEMP%\out.txt" "searchString" "replaceString" "someString"
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � ������ ������
%PROGRAM% < empty.txt > "%TEMP%\out.txt" "hello world" "goodbay world"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" outempty.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � 1-� ������� � 1-� �������
%PROGRAM% < string-1-or-more-replace.txt > "%TEMP%\out1.txt" "hello" "world"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out1.txt" outstring-1-or-more-replace1.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � 1-� ������� � �������������� ��������
%PROGRAM% < string-1-or-more-replace.txt > "%TEMP%\out2.txt" "ma" "mama"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out2.txt" outstring-1-or-more-replace2.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � ���������� ����� � ���������� �����
%PROGRAM% < multiline.txt > "%TEMP%\out3.txt" "ma" "mama"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out3.txt" outmultiline1.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � ���������� ����� search � replace ��������� ������ 1 ����� 
%PROGRAM% < multiline.txt > "%TEMP%\out4.txt" "Prince Vasili Kuragin" "Prince Kuragin"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out4.txt" outmultiline2.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� ��� ��� ����� ������� ������ 
%PROGRAM% < withoutstr.txt > "%TEMP%\out6.txt" "Hello" "Prince Kuragin"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out6.txt" outwithoutstr.txt
IF ERRORLEVEL 1 GOTO err


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT