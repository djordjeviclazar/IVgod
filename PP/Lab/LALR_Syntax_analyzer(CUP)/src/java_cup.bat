@echo off
REM ********   PODESAVANJA - MENJA STUDENT *********
set JCUP_HOME="E:\Programi\JCup\java_cup_v10k"
set JAVA_HOME="C:\Program Files\Java\jdk-11.0.2"
set PARSER_CLASS_NAME="MPParser_error_recovery"
set CUP_SPEC_NAME="MPParser_error_recovery.cup"


REM ********   POZIV JAVA CUP APLIKACIJE  ***********
echo vrednost : %JCUP_HOME%
%JAVA_HOME%\bin\java -classpath %JCUP_HOME% java_cup.Main -parser %PARSER_CLASS_NAME% -symbols sym <  %CUP_SPEC_NAME%

PAUSE
