@echo off

xcopy "%~dp0..\..\resources\"*.* "%~dp0..\..\bin\Win32\Release\" /s /y /d /r 

@echo off