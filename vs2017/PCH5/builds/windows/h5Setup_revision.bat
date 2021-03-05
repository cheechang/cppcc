@rem  安装包重命名
@rem  参数说明 1源码路径 2安装包名 3打包类型：xian、beijing

rename "%1\package\*.exe" %2

set iscopy=false
echo %3|findstr "beijing" >nul&&set iscopy=true
if "%iscopy%"=="true" (
xcopy %1\bin\*.exe %1\package\ /y/k
xcopy %1\bin\latest.yml %1\package\ /y/k
)
cd /d %1\builds\windows\