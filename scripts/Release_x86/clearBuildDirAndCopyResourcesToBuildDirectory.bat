@echo off

REM dll files won't get deleted since these have to be in root folder
del /S /Q "%~dp0..\..\bin\Win32\Release\resources\*"

xcopy "%~dp0..\..\resources\"*.* "%~dp0..\..\bin\Win32\Release\" /s /y /d /r 

@echo off