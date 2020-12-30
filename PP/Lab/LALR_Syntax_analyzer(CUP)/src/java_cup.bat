@echo off
REM ********   PODESAVANJA - MENJA STUDENT *********
set JCUP_HOME="E:\Programi\JCup\java-cup-bin-11b-20160615"
set JAVA_HOME="C:\Program Files\Java\jdk-11.0.2"
set PARSER_CLASS_NAME="MPParser_without_errors"
set CUP_SPEC_NAME="MPParser_without_errors.cup"


REM ********   POZIV JAVA CUP APLIKACIJE  ***********
echo vrednost : %JCUP_HOME%
%JAVA_HOME%\bin\java -classpath %JCUP_HOME% java_cup.Main -parser %PARSER_CLASS_NAME% -symbols sym < %CUP_SPEC_NAME%

PAUSE
