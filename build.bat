@echo off

set "BUILD_DIR=%~1"

if "%BUILD_DIR%"=="" (
	echo Compiling build folder...
	cmake --build build
) else (

if exist "%BUILD_DIR%\" (
	echo Building build folder...
	cmake -S . -B "%BUILD_DIR%"
) else (
	echo Folder does not exist. Creating "%BUILD_DIR%"
	mkdir "%BUILD_DIR%"
	cmake -S . -B "%BUILD_DIR%"
)

)


@REM cmake --build build
