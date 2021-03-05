; 该脚本使用 HM VNISEdit 脚本编辑器向导产生
!include "VersionCtrl.nsh"
!include "logiclib.nsh"
!include "WinVer.nsh"
!define PRODUCT_PUBLISHER "全国政协办公厅信息中心"
!define PRODUCT_DIR_NAME  "CPPCC"
!define PRODUCT_NAME      "$(LNG_Name)"
!define PRODUCT_OLD_NAME  "$(LNG_OldName)"
!define PRODUCT_WEB_SITE   "http://www.cppcc.gov.cn"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\AppPaths\${PRODUCT_NAME}"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define PRODUCT_FONT_REGKEY "SOFTWARE\Microsoft\Avalon.Graphics\MyDisplay1"

; 设置压缩方式
SetCompressor lzma
; 设置在当前用户目录下创建程序快捷方式，否则默认是在所有用户下创建快捷方式，导致卸载不干净
SetOverwrite on 
RequestExecutionLevel admin
; ------ MUI 现代界面定义 (1.67 版本以上兼容) ------
; 安装程序初始定义常量
!include "MUI.nsh"
!include "FileFunc.nsh"

!define MUI_CUSTOMFUNCTION_GUIINIT myGUIInit  ;自定义界面
!define SC_CLOSE 0xF060
 
!define MF_GRAYED 1

 
; MUI 预定义常量
!define MUI_ABORTWARNING  ;点击取消按钮就退出安装程序
!define MUI_ICON "Install.ico"
!define MUI_UNICON "UnInstall.ico"
!define MUI_WELCOMEFINISHPAGE_BITMAP "shortup.bmp"


; 欢迎页面
!insertmacro MUI_PAGE_WELCOME
; 许可协议页面
!insertmacro MUI_PAGE_LICENSE "agree.rtf"

; 安装目录选择页面
!insertmacro MUI_PAGE_DIRECTORY

; 安装过程页面
!insertmacro MUI_PAGE_INSTFILES
; 安装完成页面
#!define MUI_FINISHPAGE_RUN "$INSTDIR\VrvTalk.exe"
#!define MUI_FINISHPAGE_RUN_TEXT "运行${PRODUCT_NAME}程序"
!insertmacro MUI_PAGE_FINISH

; 安装卸载过程页面
!insertmacro MUI_UNPAGE_INSTFILES

; 安装界面包含的语言设置
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "SimpChinese"


 Var /Global ISSHOW_DESKTOPLINK

 
LicenseLangString LNG_License ${LANG_ENGLISH}     "agree_en.rtf"
LicenseLangString LNG_License ${LANG_SIMPCHINESE} "agree.rtf"
LangString LNG_Name ${LANG_ENGLISH}     "全国政协委员移动履职平台"
LangString LNG_Name ${LANG_SIMPCHINESE} "全国政协委员移动履职平台"
LangString LNG_OldName ${LANG_ENGLISH}     "全国政协委员移动履职平台"
LangString LNG_OldName ${LANG_SIMPCHINESE} "全国政协委员移动履职平台"
LangString LNG_Tip_1 ${LANG_SIMPCHINESE} "${PRODUCT_NAME} 安装向导将把 ${PRODUCT_NAME} 安装在下列文件夹，如果要安装到其他文件夹请单击 [浏览(B)] 进行选择."
LangString LNG_Tip_1 ${LANG_ENGLISH} "${PRODUCT_NAME} will be installed in the following folder.If you want to install it in other folder, please click [Browse(B)] to select."
LangString LNG_Tip_2 ${LANG_SIMPCHINESE} "卸载程序检测到 ${PRODUCT_NAME} 正在运行，请关闭之后再卸载！"
LangString LNG_Tip_2 ${LANG_ENGLISH}     "${PRODUCT_NAME} is running. Please close the application before uninstall."
LangString LNG_Tip_3 ${LANG_SIMPCHINESE} "您确实要完全移除 ${PRODUCT_NAME}，及其所有的组件？"
LangString LNG_Tip_3 ${LANG_ENGLISH}     "Are you sure to totally remove ${PRODUCT_NAME} and remove all of its component?"
LangString LNG_Tip_4 ${LANG_SIMPCHINESE} "${PRODUCT_NAME}已成功地从您的计算机中移除。"
LangString LNG_Tip_4 ${LANG_ENGLISH}     "${PRODUCT_NAME} has been successfully removed from your computer"
LangString LNG_Tip_5 ${LANG_SIMPCHINESE} "${PRODUCT_NAME} 已安装在计算机中。是否覆盖安装？"
LangString LNG_Tip_5 ${LANG_ENGLISH}     "${PRODUCT_NAME} is already installed in your computer, are you sure you want to replace it?"
LangString LNG_Tip_6 ${LANG_SIMPCHINESE} "安装程序检测到 ${PRODUCT_NAME} 正在运行，请关闭之后再安装！"
LangString LNG_Tip_6 ${LANG_ENGLISH}     "Detected ${PRODUCT_NAME} is running, please close it before uninstallation!"
LangString LNG_Tip_7 ${LANG_SIMPCHINESE} "全国政协办公厅信息中心"
LangString LNG_Tip_7 ${LANG_ENGLISH}     ""

; 安装预释放文件
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI 现代界面定义结束 ------
Name "${PRODUCT_NAME}"
OutFile "${PRODUCT_SETUPPACKAGE_NAME}"
;InstallDir "$PROGRAMFILES\${PRODUCT_DIR_NAME}"
;InstallDir "${intalledpath}"
InstallDirRegKey HKLM "${PRODUCT_UNINST_KEY}" "UninstallString"
ShowInstDetails hide
ShowUnInstDetails hide
DirText "$(LNG_Tip_1)"
BrandingText "${PRODUCT_NAME}"
Section "IMainSection" SEC01
  ;设置安装到当前用户账户下
  SetShellVarContext current
  SetOutPath "$INSTDIR"
  CreateDirectory "$LOCALAPPDATA\${PRODUCT_DIR_NAME}"
   
  Delete "$INSTDIR\*.*"
  File "UnInstall.ico"
  File "Install.ico"
  SetOutPath "$INSTDIR"
  SetOverwrite try
  File /r /x ".svn" /x "*.iobj"  /x "*.ipdb"  "..\..\bin\*.*"
  
  
  
 
  SetOutPath "$INSTDIR"
  
  ;删除旧快捷方式
  Delete   "$DESKTOP\${PRODUCT_NAME}.lnk"
  RMDir /r "$SMPROGRAMS\${PRODUCT_NAME}"
  Delete   "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_NAME}.lnk"
  Delete   "$SMPROGRAMS\${PRODUCT_NAME}\Uninstall.lnk"
  

 StrCpy $ISSHOW_DESKTOPLINK "1"
 ${If} $ISSHOW_DESKTOPLINK == "1"
  ;创建新的快捷方式
  CreateShortCut  "$DESKTOP\${PRODUCT_NAME}.lnk" "$INSTDIR\cppcc.exe" "" "$INSTDIR\Install.ico"
  CreateDirectory "$SMPROGRAMS\${PRODUCT_NAME}"
  CreateShortCut  "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_NAME}.lnk" "$INSTDIR\cppcc.exe" "" "$INSTDIR\Install.ico"
  CreateShortCut  "$SMPROGRAMS\${PRODUCT_NAME}\LogAssistantTool.lnk" "$INSTDIR\XpLogExplorer.exe" "" "$INSTDIR\Install.ico"
  CreateShortCut  "$SMPROGRAMS\${PRODUCT_NAME}\Uninstall.lnk" "$INSTDIR\uninst.exe"  "" "$INSTDIR\UnInstall.ico"
 ${EndIf}  
SectionEnd

Section -Post
   AccessControl::GrantOnRegKey HKLM "${PRODUCT_DIR_REGKEY}" "(S-1-5-32-545)" "FullAccess" 
   AccessControl::GrantOnRegKey HKLM "${PRODUCT_UNINST_ROOT_KEY}" "(S-1-5-32-545)" "FullAccess" 
   AccessControl::GrantOnRegKey HKLM "${PRODUCT_UNINST_KEY}" "(S-1-5-32-545)" "FullAccess" 
  ;在安装脚本中，将是否已安装的标记Installed写入注册表中
   WriteRegDWORD HKLM "${PRODUCT_DIR_REGKEY}" "Installed" 1     
   WriteRegStr   HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\cppcc.exe"
   WriteRegStr   HKLM "${PRODUCT_DIR_REGKEY}" "Instdir" "$INSTDIR"
   WriteUninstaller "$INSTDIR\uninst.exe"
   WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
   WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
   WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\cppcc.exe"
   WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
   WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
   WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "$(LNG_Tip_7)"
SectionEnd

/******************************
 *  以下是安装程序的卸载部分  *
 ******************************/
Section Uninstall
  
  RMDir /r "$INSTDIR"
  RMDir /r "$LOCALAPPDATA\${PRODUCT_DIR_NAME}"
  Delete   "$DESKTOP\${PRODUCT_NAME}.lnk"
  DeleteRegKey   ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey   HKLM "${PRODUCT_DIR_REGKEY}"
  DeleteRegValue HKLM "${PRODUCT_DIR_REGKEY}" "Installed"
  SetAutoClose true
SectionEnd

#-- 根据 NSIS 脚本编辑规则，所有 Function 区段必须放置在 Section 区段之后编写，以避免安装程序出现未可预知的问题。--#
#开始安装
Function .onInit
 Call  .CheckProcess
 Call  .KillScreenShot
 Call  .CheckHasRun
 Call  .mulu
 Call  .ISMultiInstall
 Call  .CheckSomething
 Call  .KillSingleLoginServer
 Call  .KillEdpscr
 ${RefreshShellIcons}
FunctionEnd

#安装成功
Function .onInstSuccess
  nsExec::Exec "$INSTDIR\install.bat"
 ${If} ${IsWinXP}
  nsExec::Exec "$INSTDIR\CleanIconCache.bat" 
 ${EndIf} 
 ${RefreshShellIcons}
FunctionEnd


#卸载程序入口代码
Function un.onInit
  Call un.CheckProcess
  Call un.KillScreenShot
  Call un.KillSingleLoginServer
  Call un.KillEdpscr
  nsExec::Exec "$INSTDIR\uninstall.bat" 
  ${RefreshShellIcons}
FunctionEnd

#卸载完成
Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(LNG_Tip_4)"
  ${RefreshShellIcons}
FunctionEnd

#检查程序是否运行中
Function un.CheckProcess
  FindProcDLL::FindProc "cppcc.exe"
  Pop $R0
  IntCmp $R0 1 0 no_run
  MessageBox MB_ICONSTOP "$(LNG_Tip_2)"
  Quit
  no_run:
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "$(LNG_Tip_3)" IDYES +2
  Abort
FunctionEnd

#检测screenshot.exe是否运行，如果运行则关闭进程
Function un.KillScreenShot
loop:
	FindProcDLL::FindProc "screenshot.exe"
	Pop $R0
    IntCmp $R0 1 0 no_run
	KillProcDLL::KillProc "screenshot.exe"
	goto loop
	no_run:
FunctionEnd


#检测singlelogin.exe是否运行，如果运行则关闭进程
Function un.KillSingleLoginServer
loop:
	FindProcDLL::FindProc "singlelogin.exe"
	Pop $R0
    IntCmp $R0 1 0 no_run
	KillProcDLL::KillProc "singlelogin.exe"
	goto loop
	no_run:
FunctionEnd

#检测edpscr_s.exe是否运行，如果运行则关闭进程
Function un.KillEdpscr
loop:
	FindProcDLL::FindProc "edpscr_s.exe"
	Pop $R0
    IntCmp $R0 1 0 no_run
	KillProcDLL::KillProc "edpscr_s.exe"
	goto loop
	no_run:
FunctionEnd


;禁止多次安装实例函数
Function .ISMultiInstall
	ReadRegDWORD $0 HKLM '${PRODUCT_DIR_REGKEY}' "Installed"
	IntCmp $0 +1 +4
	MessageBox MB_ICONQUESTION|MB_YESNO "$(LNG_Tip_5)" IDYES +2
	Abort
;禁止多次安装实例 end
FunctionEnd

;判断是否存在images目录，存在则删除
;add by lpy
Function .CheckSomething
	IfFileExists $LOCALAPPDATA\images 0 +2
	  RMDir /r "$LOCALAPPDATA\images"
FunctionEnd

;检查是否有程序正在运行有则强制结束
Function .CheckProcess
   ;检测程序是否运行
  FindProcDLL::FindProc "cppcc.exe"
  Pop $R0
  IntCmp $R0 1 0 no_run
  MessageBox MB_ICONSTOP "$(LNG_Tip_6)"
  Quit
  no_run:
FunctionEnd

;检查是否是xp sp3以下版本的系统
Function .CheckSystemVersion
  ${If} ${AtMostWinXP} 
    Push $R0
    ReadRegDWORD $R0 HKLM  "SYSTEM\CurrentControlSet\Control\Windows" CSDVersion
	IntCmp $R0 768  run  no_run
  no_run:
    MessageBox MB_OK "本软件不支持Windows Xp Sp2及以下版本的系统" 
	Quit
  run:
  ${EndIf} 
FunctionEnd
;创建互斥防止重复运行
Function .CheckHasRun
  System::Call 'kernel32::CreateMutexA(i 0, i 0, t "WinSnap_installer") i .r1 ?e'
  Pop $R0
  StrCmp $R0 0 +3
    MessageBox MB_OK|MB_ICONEXCLAMATION "安装向导已经运行"
    Abort
FunctionEnd


#检测singlelogin是否运行，如果运行则关闭进程
Function .KillSingleLoginServer
FindProcDLL::FindProc  "singlelogin.exe"
   Pop $R0
   IntCmp $R0 1 0 no_run
   KillProcDLL::KillProc "singlelogin.exe"
   no_run:
FunctionEnd

#检测edpscr_s.exe是否运行，如果运行则关闭进程
Function .KillEdpscr
loop:
	FindProcDLL::FindProc "edpscr_s.exe"
	Pop $R0
    IntCmp $R0 1 0 no_run
	KillProcDLL::KillProc "edpscr_s.exe"
	goto loop
	no_run:
FunctionEnd

;自定义界面Function 实现隐藏最大最小化的代码   
Function myGUIInit   
  System::Call 'user32::GetWindowLong(i $hwndparent,i -16)i.r0' 
  intop $1 0x30000 ~
  intop $0 $0 & $1
  System::Call 'user32::SetWindowLong(i $hwndparent,i -16,i $0)i' ;最大化不可用
  System::Call 'user32::GetSystemMenu(i $hwndparent, i 0) i .r0'
  System::Call 'user32::EnableMenuItem(i s, i ${SC_CLOSE}, i ${MF_GRAYED})'
FunctionEnd   

;找到以前的安装目录
Function .mulu
StrCpy $INSTDIR "$PROGRAMFILES\${PRODUCT_DIR_NAME}"
ReadRegStr $0 HKLM '${PRODUCT_DIR_REGKEY}' "Instdir"
${If} $0 != ""
	StrCpy $INSTDIR "$0"
${EndIf} 

FunctionEnd

#检测screenshot.exe是否运行，如果运行则关闭进程
Function .KillScreenShot
loop:
	FindProcDLL::FindProc "screenshot.exe"
	Pop $R0
    IntCmp $R0 1 0 no_run
	KillProcDLL::KillProc "screenshot.exe"
	goto loop
	no_run:
FunctionEnd