@echo off
REM Gera o executavel do TP1 em modo pasta (onedir), sem janela de console.
REM Resultado: dist\TP1_CG\TP1_CG.exe e as bibliotecas em dist\TP1_CG\_internal
cd /d "%~dp0"
python -m PyInstaller --noconfirm --clean --windowed --onedir --name TP1_CG main.py
echo.
echo Executavel gerado em: %~dp0dist\TP1_CG\TP1_CG.exe
pause
