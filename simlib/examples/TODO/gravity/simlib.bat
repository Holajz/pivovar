@echo off
if "%1"=="" goto USAGE
echo 北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
echo Model: %1
echo 北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
call bcc31 -ml -w -I.. %1 %2 %3 %4 %5 ..\simlib.lib
if errorlevel 1 goto ERR
del *.obj
echo.
goto END
:ERR
echo.
echo CHYBA!
echo Chyba v modelu: %1 >>simlib.log
goto END
:USAGE
echo.
echo SIMLIB.BAT - p齟klad modelu v C++/SIMLIB (TESTOVAC? VERZE!)
echo.
echo Pout?:
echo           SIMLIB  model.cpp
:END
echo.
