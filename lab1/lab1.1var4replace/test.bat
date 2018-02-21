set PROGRAM="%~1"

REM ������ ��������� ��� ����������
%PROGRAM%
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � ����� ����������
%PROGRAM% OneParameter
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� ��� output
%PROGRAM% input.txt "" "serched string" "rapleced string"
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� ��� input
%PROGRAM% "" out.txt "serched string" "rapleced string"
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� ��� search string
%PROGRAM% input.txt out.txt "" "rapleced string"
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � 6 �����������
%PROGRAM% input.txt out.txt "searchString" "replaceString" "someString"
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � ������ ������
%PROGRAM% empty.txt out.txt "hello world" "goodbay world"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outempty.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � 1-� ������� � 1-� �������
%PROGRAM% string-1-or-more-replace.txt out.txt "hello" "world"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outstring-1-or-more-replace1.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � 1-� ������� � �������������� ��������
%PROGRAM% string-1-or-more-replace.txt out.txt "ma" "mama"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outstring-1-or-more-replace2.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � ���������� ����� � ���������� �����
%PROGRAM% multiline.txt out.txt "ma" "mama"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outmultiline1.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � ���������� ����� search � replace ��������� ������ 1 ����� 
%PROGRAM% multiline.txt out.txt "Prince Vasili Kuragin" "Prince Kuragin"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outmultiline2.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� ��� ��� ����� ������� ������ 
%PROGRAM% withoutstr.txt out.txt "Hello" "Prince Kuragin"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outwithoutstr.txt
IF ERRORLEVEL 1 GOTO err


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT