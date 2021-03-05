@rem  编译
@rem  参数说明 1源码路径 2打包类型 xp版本 还是标准版

set type=%2
xcopy %1\vrv-static %1\node_modules\vrv-static\ /e/y
xcopy %1\vrv-robotjs %1\node_modules\vrv-robotjs\ /e/y
rmdir /S /Q %1\node_modules\vrv-static\lib\vimsdk\darwin
rmdir /S /Q %1\node_modules\vrv-static\lib\vimsdk\linux
cd /d %1
set PATH=%PATH%;C:\Program Files (x86)\nodejs\;C:\Users\VRV\AppData\Roaming\npm
if "%type%"=="xp" (
 yarn dist:xp
)
if "%type%"=="win7" (
 yarn dist:dir
)
