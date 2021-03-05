@rem  修改windows安装包版本号 && 安装项目依赖的nodejs模块
@rem  参数说明 1.源码路径 2.版本号 3.版本号的第四位 4.mark值 5.svnaddresskey值 6.打包类型 xp版本 还是标准版 7.deviceinfo pc-h5-win h5版本  pc-xp xp版本 8.是否检测升级

set type=%6
cd /d %1

git tag -a "master-v%2.%3" -m "record version tag"
git push origin "master-v%2.%3"


if "%type%"=="xp" (
@rem 修改版本信息并生成ver.h
echo "=========modify ver.h=============="
call %1\vrv-static\lib\vimsdk\win32\xp\res\modifyver.bat %1 %2 %4
echo "=========generate res info=============="
cd %1\vrv-static\lib\vimsdk\win32\xp\res
ResourceHacker.exe  -open Linkdood.rc -save %1\..\electron-v1.1.3-win32-cn\Linkdood.res -action compile
cd %1\..\electron-v1.1.3-win32-cn
ResourceHacker.exe -open Linkdood.exe -save Linkdood.exe -action addoverwrite -res %1\vrv-static\resources\images\icons\windows\logo.ico -mask ICONGROUP,MAINICON
ResourceHacker.exe -open %1\..\electron-v1.1.3-win32-cn\Linkdood.exe -save %1\..\electron-v1.1.3-win32-cn\Linkdood.exe  -resource %1\..\electron-v1.1.3-win32-cn\Linkdood.res -action modify
del /f /q %1\..\electron-v1.1.3-win32-cn\Linkdood.res
rmdir /S /Q %1\vrv-static\lib\vimsdk\win32\xp\res
cd %1
)

set isupdate = %8

setlocal enabledelayedexpansion
set file="package.json"
set version="%2"
set "file=%file:"=%"
for %%i in ("%file%") do set file=%%~fi
echo.
for /f "delims=" %%i in ('type "%file%"') do (
set str=%%i
set flags=false
set updateflags=false
set updatetypeflags=false
set updatedeviceInfoflags=false
echo !flags!
echo !updateflags!
echo %%i|findstr "version">nul&&set flags=true
echo %%i|findstr "checkUpgrade">nul&&set updateflags=true
echo %%i|findstr "isWinXp">nul&&set updatetypeflags=true
echo %%i|findstr "deviceInfo">nul&&set updatedeviceInfoflags=true
if "!flags!"=="true" (
set "str=  "version": %version%,"
)
if "!updateflags!"=="true" (
if "%isupdate%"=="false" (
set "str=  "checkUpgrade": false,"
)
if "%isupdate%"=="true" (
set "str=  "checkUpgrade": true,"
)
)
if "!updatetypeflags!"=="true" (
if "%type%"=="xp" (
 set "str=  "isWinXp": true,"
)
if "%type%"=="win7" (
 set "str=  "isWinXp": false,"
)
)
if "!updatedeviceInfoflags!"=="true" (
 set "str=  "deviceInfo": "%7","
)
echo !str!>>"%file%"_tmp.txt
)
move "%file%"_tmp.txt "%file%"

set nsisfile="versionctrl.nsh"
set nsisversion=%2
set "file=%nsisfile:"=%"
for %%i in ("%nsisfile%") do set file=%%~fi
echo.
for /f "delims=" %%i in ('type "%nsisfile%"') do (
set nsisstr=%%i
set nsisflags=false
echo !nsisflags!
echo %%i|findstr "PRODUCT_VERSION">nul&&set nsisflags=true
set "nsisstr=^%%i"
if "!nsisflags!"=="true" (
set "nsisstr=  ^!define PRODUCT_VERSION %nsisversion%"
)
echo !nsisstr!>>"%nsisfile%"_tmp.txt
)
move "%nsisfile%"_tmp.txt "%nsisfile%"


cd /d %1\src\main
set markfile="SDKService.js"
set mark='%4'
set "file=%markfile:"=%"
for %%i in ("%markfile%") do set file=%%~fi
echo.
for /f "delims=" %%i in ('type "%markfile%"') do (
set markstr=%%i
set markflags=false
set specialflags=false
echo %%i|findstr "mark">nul&&set markflags=true
echo %%i|findstr "!==">nul&&set specialflags=true
if "!specialflags!"=="true" (    
set "markstr=    if (client ^!== null) {"
)
if "!markflags!"=="true" (
set "markstr=      mark: %mark%,"
)
echo !markstr!>>"%markfile%"_tmp.txt
)
move "%markfile%"_tmp.txt "%markfile%"
del "{"
del "0)"
if "%4"=="inte" (
rename "%1\builds\windows\NsisLinkdood_en.dll" NsisLinkdood.dll
)
if "%4"=="comm" (
rename "%1\builds\windows\NsisLinkdood_zh.dll" NsisLinkdood.dll
)
copy %1\builds\windows\NsisLinkdood.dll %NSIS_PLUGIN_ROOT% /Y
cd /d %1
set PATH=%PATH%;C:\Program Files (x86)\nodejs\;C:\Users\VRV\AppData\Roaming\npm
yarn