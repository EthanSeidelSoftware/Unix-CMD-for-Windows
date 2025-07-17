@echo off
setlocal
cd /d "%~dp0"

REM Source directory - where you run this script
set "SRC_DIR=%CD%"

REM Target directory - Windows System32 folder (already in PATH)
set "INSTALL_DIR=%windir%\System32"

echo Installing command pack to %INSTALL_DIR% ...
echo Source directory is "%SRC_DIR%"

if /I "%SRC_DIR%"=="%INSTALL_DIR%" (
    echo ERROR: Source and destination directories are the same!
    echo Please run this script from the directory containing your executables.
    pause
    exit /b 1
)

REM Copy all .exe files from source to System32
echo Copying executables...
copy /Y "%SRC_DIR%\*.exe" "%INSTALL_DIR%\"

if errorlevel 1 (
    echo ERROR: Failed to copy files.
    echo Make sure to run this script as Administrator.
    pause
    exit /b 1
)

echo Installation complete.
echo Your commands should be available immediately since System32 is in PATH.
pause
