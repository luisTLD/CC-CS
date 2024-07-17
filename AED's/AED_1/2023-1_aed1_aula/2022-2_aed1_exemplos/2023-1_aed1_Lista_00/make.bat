REM
REM PUC-Minas - ICEI - CRC
REM make: compilar e executar testes automaticos
REM
REM Uso : make programa
REM       (sem usar extensao) 
REM
REM       make lista_00
REM
@echo off
cls
if exist %1.exe        del  %1.exe
if exist output.txt    del  output.txt
if exist %1.c          gcc -g -o %1 %1.c
if exist %1.exe %1.exe <input.txt >output.txt
if exist output.txt    type output.txt
@echo\

