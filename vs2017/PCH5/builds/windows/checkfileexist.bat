@rem 本批处理用来检查package-signed目录下文件是否存在
@rem 1文件路径
@echo off
:loop
if exist %1 (
 echo %1 founded
)else (
	@rem 延时10秒
	echo %1 not find,keep go on check。
	choice /t 10 /d y /n >nul   
	goto loop
)
