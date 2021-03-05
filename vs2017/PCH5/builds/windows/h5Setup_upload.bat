@rem  安装包拷贝到jenkins工作目录下
@rem  参数说明 1源码路径 2git分支名称


xcopy %1\package\*.exe C:\Jenkins\workspace\h5-windows\%2\ /y/k