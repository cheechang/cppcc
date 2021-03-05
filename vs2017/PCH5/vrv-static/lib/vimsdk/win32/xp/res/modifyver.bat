@rem 创建版本信息文件ver.h
@rem 参数说明 1源码路径 2版本号 3mark字段值
del /f /q %1\vrv-static\lib\vimsdk\win32\xp\res\ver.h
echo #define APP_VERSION_NUM "%2" >> %1\vrv-static\lib\vimsdk\win32\xp\res\ver.h
echo #define APP_PRODUCTVERSION_NUM "v%2" >> %1\vrv-static\lib\vimsdk\win32\xp\res\ver.h
echo #define APP_PRODUCTNAME "Linkdood_V%2" >> %1\vrv-static\lib\vimsdk\win32\xp\res\ver.h
echo #define APP_MARK "%3" >> %1\vrv-static\lib\vimsdk\win32\xp\res\ver.h
echo #define APP_SERVER_MINIVER "1" >> %1\vrv-static\lib\vimsdk\win32\xp\res\ver.h
echo #define APP_SERVER_ADVVER  "1" >> %1\vrv-static\lib\vimsdk\win32\xp\res\ver.h
echo #define APP_WIN_VER1 0 >> %1\vrv-static\lib\vimsdk\win32\xp\res\ver.h

@rem 分割版本号信息
set str=%2
for /f "tokens=1 delims=." %%a in ("%str%") do set ver2=%%a
for /f "tokens=2 delims=." %%a in ("%str%") do set ver3=%%a
for /f "tokens=3 delims=." %%a in ("%str%") do set ver4=%%a
echo #define APP_WIN_VER2 %ver2% >> %1\vrv-static\lib\vimsdk\win32\xp\res\ver.h
echo #define APP_WIN_VER3 %ver3% >> %1\vrv-static\lib\vimsdk\win32\xp\res\ver.h
echo #define APP_WIN_VER4 %ver4% >> %1\vrv-static\lib\vimsdk\win32\xp\res\ver.h