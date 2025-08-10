@echo off

@REM set "BUILD_DIR=%~1"

@REM if "%BUILD_DIR%"=="" (
@REM 	echo Compiling build folder...
@REM 	cmake --build build
@REM )

@REM if exist "%BUILD_DIR%\" (
@REM 	echo Building build folder...
@REM 	cmake -S . -B "%BUILD_DIR%"
@REM ) else (
@REM 	echo Folder does not exist. Creating "%BUILD_DIR%"
@REM 	mkdir "%BUILD_DIR%"
@REM 	cmake -S . -B "%BUILD_DIR%"
@REM )

cmake --build build