@rem  修改windows安装包版本号 && 安装项目依赖的nodejs模块
@rem  参数说明 1源码路径 2版本号

cd /d %1
setlocal enabledelayedexpansion
set file="package.json"
set version="%2"
set "file=%file:"=%"
for %%i in ("%file%") do set file=%%~fi
echo.
for /f "delims=" %%i in ('type "%file%"') do (
set str=%%i
set flags=false
echo !flags!
echo %%i|findstr "version">nul&&set flags=true
if "!flags!"=="true" (
set "str=  "version": %version%,"
)
echo !str!|findstr /v "oneClick allowToChangeInstallationDirectory">>"%file%"_tmp.txt
)
move "%file%"_tmp.txt "%file%"
set PATH=%PATH%;C:\Program Files (x86)\nodejs\;C:\Users\VRV\AppData\Roaming\npm
yarn dist:dir