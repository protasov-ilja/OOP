REM ������ ��������� ��� ����������
lab0.4.exe
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � ����� ���������� ����������
lab0.4.exe notANumber
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � ������ ������� � �������� ������ �� ����������
lab0.4.exe ""
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � ����� �������� ���������� (� ��������� ���������)
lab0.4.exe -123 > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt -123.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � ����� ��������� �����������
lab0.4.exe 15 2 > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt 15+2=17.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � ����� ��������� �����������
lab0.4.exe 15 2 -8 > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt 15+2+-8=9.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT
