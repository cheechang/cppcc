@rem 根据指令拷贝特定的库
@rem lxy
@rem 1环境类型 xp 编译支持xp系统的版本  win7编译支持到win7系统的版本 start xp版本启动参数
@echo off
set type=%1

@rem 强制查杀截图进程
taskkill /f /im screenshot.exe
@rem 拷贝xp及以上系统依赖的库
if "%type%"=="xp" (
  xcopy  %cd%\node_modules\vrv-static\lib\vimsdk\win32\xp node_modules\vrv-static\lib\vimsdk\win32\  /I /Y /E /H /F
  xcopy  %cd%\node_modules\vrv-static\lib\robot\win32\xp node_modules\vrv-static\lib\robot\win32\  /I /Y /E /H /F
)

@rem 拷贝win7及以上系统依赖的库
if "%type%"=="win7" (
  xcopy  %cd%\node_modules\vrv-static\lib\vimsdk\win32\win7 node_modules\vrv-static\lib\vimsdk\win32\  /I /Y /E /H /F
  xcopy  %cd%\node_modules\vrv-static\lib\robot\win32\win7 node_modules\vrv-static\lib\robot\win32\  /I /Y /E /H /F
)

@rem 删除平台差异库
if "%type%"=="remove" (
rmdir /S /Q %cd%\node_modules\vrv-static\lib\vimsdk\win32\win7
rmdir /S /Q %cd%\node_modules\vrv-static\lib\vimsdk\win32\xp
rmdir /S /Q %cd%\node_modules\vrv-static\lib\robot\win32\win7
rmdir /S /Q %cd%\node_modules\vrv-static\lib\robot\win32\xp
rmdir /S /Q bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\win7
rmdir /S /Q bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\xp
rmdir /S /Q bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\robot\win32\win7
rmdir /S /Q bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\robot\win32\xp
@rem 执行完毕关闭cmd窗口
exit /B 0
)

if "%type%"=="start" (
  taskkill /f /t /im electron.exe
  xcopy  bin\win-ia32-unpacked\resources\app ..\electron-v1.1.3-win32-cn\resources\app  /I /Y /E /H /F
  rmdir /S /Q ..\electron-v1.1.3-win32-cn\resources\app\node_modules\vrv-static\lib\vimsdk\win32\win7
  rmdir /S /Q ..\electron-v1.1.3-win32-cn\resources\app\node_modules\vrv-static\lib\vimsdk\win32\xp
  rmdir /S /Q ..\electron-v1.1.3-win32-cn\resources\app\node_modules\vrv-static\lib\robot\win32\win7
  rmdir /S /Q ..\electron-v1.1.3-win32-cn\resources\app\node_modules\vrv-static\lib\robot\win32\xp
  start  ..\electron-v1.1.3-win32-cn\electron.exe debug
)
@rem 执行完毕关闭cmd窗口
exit /B 0

