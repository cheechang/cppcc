@rem 动态库签名准备
@rem 参数说明 1源码路径 2打包类型 xp版本 还是标准版

md %1\bin-temp
md %1\bin-signed
set type=%2

if "%type%"=="xp" (
 rmdir /S /Q %1\..\electron-v1.1.3-win32-cn\resources\app
 xcopy  %1\bin\win-ia32-unpacked\resources\app %1\..\electron-v1.1.3-win32-cn\resources\app  /I /Y /E /H /F
 rmdir /S /Q %1\bin\win-ia32-unpacked
 xcopy  %1\..\electron-v1.1.3-win32-cn %1\bin\win-ia32-unpacked /I /Y /E /H /F
)

xcopy %1\bin\win-ia32-unpacked %1\bin-temp\win-ia32-unpacked\  /e/y
xcopy %1\bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\vrvclass.dll %1\bin  /e/y
xcopy %1\bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\vimsdk.node %1\bin  /e/y
xcopy %1\bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\service.dll %1\bin  /e/y
xcopy %1\bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\linkdood.crt %1\bin  /e/y
xcopy %1\bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\libssl-1_1.dll %1\bin  /e/y
xcopy %1\bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\libeay32.dll %1\bin  /e/y
xcopy %1\bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\libcurl.dll %1\bin  /e/y
xcopy %1\bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\libcrypto-1_1.dll %1\bin  /e/y
xcopy %1\bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\imsdkapi.dll %1\bin  /e/y
xcopy %1\bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\commLib.dll %1\bin  /e/y
xcopy %1\bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\cimg.dll %1\bin  /e/y
xcopy %1\bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\libfftw3-3.dll %1\bin  /e/y

xcopy %1\bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\sdkplugins\lddplugin.dll %1\bin  /e/y
xcopy %1\bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\sdkplugins\mrtcplugin.dll %1\bin  /e/y
xcopy %1\bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\sdkplugins\rtcplugin.dll %1\bin  /e/y

xcopy %1\bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\oauth\oauth.node %1\bin  /e/y
xcopy %1\bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\oauth\OAuthAdapter.dll %1\bin  /e/y

xcopy %1\bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\screenShot\QtCore4.dll %1\bin  /e/y
xcopy %1\bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\screenShot\QtGui4.dll %1\bin  /e/y
xcopy %1\bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\screenShot\screenshot.exe %1\bin  /e/y

xcopy %1\bin\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\screenShot\platforms\qwindows.dll %1\bin  /e/y

xcopy %1\bin\win-ia32-unpacked\d3dcompiler_47.dll %1\bin  /e/y
xcopy %1\bin\win-ia32-unpacked\Linkdood.exe %1\bin  /e/y

rmdir /S /Q %1\bin\win-ia32-unpacked
rmdir /S /Q %1\bin\oauth
rmdir /S /Q %1\bin\screenShot
rmdir /S /Q %1\bin\sdkplugins
rmdir /S /Q %1\bin\locales
rmdir /S /Q %1\bin\resources
rmdir /S /Q %1\bin\swiftshader
rmdir /S /Q %1\bin\platforms
del /Q %1\bin\builder-effective-config.yaml
