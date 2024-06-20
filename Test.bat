@echo off
setlocal enabledelayedexpansion

REM type nul > source.txt
REM type nul > target.txt
set SHARED_MEMORY_NAME=shared_memory

echo File creation completed.

set "startTime=%time%"

REM Set source and target file names
set SOURCE_FILE=source.txt
set TARGET_FILE=target.txt

REM echo Creating 10MB source file...
REM set CHARS=ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789

REM Delete the file if it already exists
REM if exist %SOURCE_FILE% del %SOURCE_FILE%

REM Loop to create the file
REM for /L %%i in (1,1,10240) do (
REM    set LINE=
REM    for /L %%j in (1,1,1024) do (
REM        set /A RAND=!random! %% 62
REM        for %%k in (!RAND!) do (
REM            set "LINE=!LINE!!CHARS:~%%k,1!"
REM        )
REM    )
REM    echo !LINE! >> %SOURCE_FILE%
REM )

REM Record start time
set "startTime=%time: =0%"
for /F "tokens=1-4 delims=:.," %%a in ("%startTime%") do (
    set /a startMilliseconds=1%%a*3600000 + 1%%b*60000 + 1%%c*1000 + 1%%d - 10000000
)
REM Run the copy program
REM First run - reading
echo Starting the program for reading...
..\Debug\Copy_Tool_.exe %SOURCE_FILE% %DEST_FILE% %SHARED_MEMORY_NAME%

REM Second run - writing
echo Starting the program for writing...
..\Debug\Copy_Tool_.exe %SOURCE_FILE% %DEST_FILE% %SHARED_MEMORY_NAME%




REM Record end time
set "endTime=%time: =0%"
for /F "tokens=1-4 delims=:.," %%a in ("%endTime%") do (
    set /a endMilliseconds=1%%a*3600000 + 1%%b*60000 + 1%%c*1000 + 1%%d - 10000000
)

REM Calculate elapsed time
set /a elapsedTime=endMilliseconds-startMilliseconds

REM Get the size of the source file in bytes
for %%A in (%SOURCE_FILE%) do set fileSize=%%~zA

if !elapsedTime! gtr 0 (
    set /a speed=fileSize*1000/elapsedTime
) else (
    set speed=0
)

REM Convert speed to megabytes per second
set /a speedMBps=speed/(1024*1024)

echo Elapsed Time: %elapsedTime% milliseconds
echo File Size: !fileSize! bytes
echo Speed: !speedMBps! MB/second

REM del source.txt
REM del target.txt

endlocal
pause