２０１９－３－２２
涉及程序：
　ListWidgetItem 
  contactwidgetWeb   自定网页访问
  ChatPage.h


  2019-4-14 
   MainWindowCpp 添加测试模式端口7777

   2019-4-29
 
   ContactMgrControl(); 
   
   ControlClient()


   EnterpriseAccountList() 通道获取列表    ==>   ContactWidget()



   FriendListWidgetWeb (web 列表)   



  LoginWindow  登陆界面


  ContactTabWidgetAreaWeb:  左边  ==>FriendListWidgetWeb


  initLocalSearchList() 收索窗口


  窗口关系

  mainwindow 
      ->  title_widget /   首页:   ContactWidgetWeb   
	                                  -ContactTabWidgetAreaWeb   -> GroupListItemWidgetWeb
								      -DefaultWidgetWeb 

                                   ContactWidge
									
												ContactTabWidgetArea   -> EnterpriseWidget  -> EnterpriseInfoWidget  ->UserInfoCommon/UserInfoCommitte

								   ChatPage   -> chatListWidget

								              ContactTabWidgetArea    (1,2,(3)EnterpriseWidget)
											          ChatWidget->ChatTitle

	                                          MsgManagerListItem



	   
	   ---------------------------------------------------
2019-5-8
RSA, loginOut    
2019-5-14

修改了字体大小， 分别在 ListWidgetItem.cpp, GroupListItemWidgetWeb, GroupListItemWidget

增加了下载文件功能。


   font-family:'Microsoft YaHei';
   font-size:10px;


2019-5-15
关闭拖拉,  添加设置调试  url/path , 

2019-5-16
弱提示==> 消息提示   CreateGroupHomeArea.cpp(167):			chat->lastMsg = transfer("[弱提示]").toStdString();
#define  PROMPT_MSG_TIP			(utils::Error::IsChinese() ? QString::fromLocal8Bit("弱提示"):QString::fromLocal8Bit("Notice"))
E:\myWorkspace\zxSrc\src\control\chatmgrcontrol\ChineseInfos.hpp(18)
#define  PROMPT_MSG_TIP			(utils::Error::IsChinese() ? std::string("[弱提示]"):std::string("[Notice]"))

(已恢复上面修改)


2019-5-23


动:
		默认值:设备来源client_id(mrhcweb,mrhcapp)对应web端,app端或PC端;pc端传参的client_id为mrhcapp,client_secret为mrhcapp对应的client_secret
		deviceType设备类型(web,app,pc)
		

	1.get生成图片验证码接口/api/v1/sign/images/imagecode,
				参数deviceType,tid,userName,client_id和deviceId(设备id(只有在app端和PC端才需要传deviceId))
	2.post登录接口/uoauth/token,
				参数tid,client_id,client_secret,deviceType,
					ciphertext(字段tid,userName,password,code,deviceId,deviceModel,deviceIp(暂时没用,可不传)),
					scope,(默认为read)
					grant_type(默认为"password")
	3.post校验token接口/oauth/check_token,
				参数tid,token,
					deviceId,
					deviceModel(设备id,设备型号,没有为空,app和pc有值)
	4.post刷新token接口/oauth/token,
				参数tid,
					grant_type,(默认值为"refresh_token")
					userName,password(暂时不用,为空),
					client_id,client_secret,scope,refresh_token,deviceId,deviceModel,deviceType								
	
2019-5-29
GroupInforWidget,  群信息

2019-6-12

关于登陆3态：  MANUAL, AUTO ,FRE_AUTO

MANUAL:  登陆界面，人工点。
AUTO:    自动登陆， 现在默认都是自动登陆模式， 
FRE_AUTO:  WEB刷新Token的时候使用的。 

通过 login.md 控制当前登陆模式；
流程描述： 默认自动登陆，  出错转人工。 
           注销后， 转人工
		   Web 刷新， 转FRE 自动模式。

		   
2019-6-28
关于版本号：
  APP_VER+ SVN_VER,    当前应用程序版本+流水号   "XXX.XX" + "." + "xxxx "

2020-4-20
增加 读书群的判断和群未读信息的接口 