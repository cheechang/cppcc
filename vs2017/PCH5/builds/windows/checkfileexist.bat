@rem ���������������package-signedĿ¼���ļ��Ƿ����
@rem 1�ļ�·��
@echo off
:loop
if exist %1 (
 echo %1 founded
)else (
	@rem ��ʱ10��
	echo %1 not find,keep go on check��
	choice /t 10 /d y /n >nul   
	goto loop
)
