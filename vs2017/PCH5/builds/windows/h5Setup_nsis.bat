@rem  ǩ����ɺ���
@rem  ����˵��   1Դ��·��
xcopy %1\bin-temp\win-ia32-unpacked %1\bin-signed\win-ia32-unpacked\  /e/y

xcopy %1\bin-signed\vrvclass.dll %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\  /y
xcopy %1\bin-signed\vimsdk.node %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\  /y
xcopy %1\bin-signed\service.dll %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\  /y
xcopy %1\bin-signed\linkdood.crt %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\  /y
xcopy %1\bin-signed\libssl-1_1.dll %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\  /y
xcopy %1\bin-signed\libeay32.dll %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\  /y
xcopy %1\bin-signed\libcurl.dll %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\  /y
xcopy %1\bin-signed\libcrypto-1_1.dll %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\  /y
xcopy %1\bin-signed\imsdkapi.dll %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\  /y
xcopy %1\bin-signed\commLib.dll %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\  /y
xcopy %1\bin-signed\cimg.dll %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\  /y
xcopy %1\bin-signed\libfftw3-3.dll %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\  /y

xcopy %1\bin-signed\lddplugin.dll %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\sdkplugins\  /y
xcopy %1\bin-signed\mrtcplugin.dll  %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\sdkplugins\ /y
xcopy %1\bin-signed\rtcplugin.dll %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\sdkplugins\  /y

xcopy %1\bin-signed\oauth.node  %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\oauth\  /y
xcopy %1\bin-signed\OAuthAdapter.dll  %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\oauth\  /y

xcopy %1\bin-signed\QtCore4.dll  %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\screenShot\  /y
xcopy %1\bin-signed\QtGui4.dll  %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\screenShot\  /y
xcopy %1\bin-signed\screenshot.exe  %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\screenShot\  /y

xcopy %1\bin-signed\qwindows.dll  %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\screenShot\platforms\  /y

xcopy %1\bin-signed\d3dcompiler_47.dll %1\bin-signed\win-ia32-unpacked\  /y
xcopy %1\bin-signed\Linkdood.exe %1\bin-signed\win-ia32-unpacked\  /y

xcopy %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\dependent\*.dll  %1\bin-signed\win-ia32-unpacked\  /y
xcopy %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\dependent\*.dll  %1\bin-signed\win-ia32-unpacked\resources\app\node_modules\vrv-static\lib\vimsdk\win32\  /y

md %1\package
md %1\package-signed

del /Q %1\bin-signed\*.*

cd /d %1\bin-signed\win-ia32-unpacked

7z a -t7z Linkdood.7z locales resources swiftshader *.pak *.exe *.dll *.html *.dat *.txt *.bin

cd /d %1

makensis %1\installer.nsi