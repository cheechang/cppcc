������������������
�漰����
��ListWidgetItem 
  contactwidgetWeb   �Զ���ҳ����
  ChatPage.h


  2019-4-14 
   MainWindowCpp ��Ӳ���ģʽ�˿�7777

   2019-4-29
 
   ContactMgrControl(); 
   
   ControlClient()


   EnterpriseAccountList() ͨ����ȡ�б�    ==>   ContactWidget()



   FriendListWidgetWeb (web �б�)   



  LoginWindow  ��½����


  ContactTabWidgetAreaWeb:  ���  ==>FriendListWidgetWeb


  initLocalSearchList() ��������


  ���ڹ�ϵ

  mainwindow 
      ->  title_widget /   ��ҳ:   ContactWidgetWeb   
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

�޸��������С�� �ֱ��� ListWidgetItem.cpp, GroupListItemWidgetWeb, GroupListItemWidget

�����������ļ����ܡ�


   font-family:'Microsoft YaHei';
   font-size:10px;


2019-5-15
�ر�����,  ������õ���  url/path , 

2019-5-16
����ʾ==> ��Ϣ��ʾ   CreateGroupHomeArea.cpp(167):			chat->lastMsg = transfer("[����ʾ]").toStdString();
#define  PROMPT_MSG_TIP			(utils::Error::IsChinese() ? QString::fromLocal8Bit("����ʾ"):QString::fromLocal8Bit("Notice"))
E:\myWorkspace\zxSrc\src\control\chatmgrcontrol\ChineseInfos.hpp(18)
#define  PROMPT_MSG_TIP			(utils::Error::IsChinese() ? std::string("[����ʾ]"):std::string("[Notice]"))

(�ѻָ������޸�)


2019-5-23


��:
		Ĭ��ֵ:�豸��Դclient_id(mrhcweb,mrhcapp)��Ӧweb��,app�˻�PC��;pc�˴��ε�client_idΪmrhcapp,client_secretΪmrhcapp��Ӧ��client_secret
		deviceType�豸����(web,app,pc)
		

	1.get����ͼƬ��֤��ӿ�/api/v1/sign/images/imagecode,
				����deviceType,tid,userName,client_id��deviceId(�豸id(ֻ����app�˺�PC�˲���Ҫ��deviceId))
	2.post��¼�ӿ�/uoauth/token,
				����tid,client_id,client_secret,deviceType,
					ciphertext(�ֶ�tid,userName,password,code,deviceId,deviceModel,deviceIp(��ʱû��,�ɲ���)),
					scope,(Ĭ��Ϊread)
					grant_type(Ĭ��Ϊ"password")
	3.postУ��token�ӿ�/oauth/check_token,
				����tid,token,
					deviceId,
					deviceModel(�豸id,�豸�ͺ�,û��Ϊ��,app��pc��ֵ)
	4.postˢ��token�ӿ�/oauth/token,
				����tid,
					grant_type,(Ĭ��ֵΪ"refresh_token")
					userName,password(��ʱ����,Ϊ��),
					client_id,client_secret,scope,refresh_token,deviceId,deviceModel,deviceType								
	
2019-5-29
GroupInforWidget,  Ⱥ��Ϣ

2019-6-12

���ڵ�½3̬��  MANUAL, AUTO ,FRE_AUTO

MANUAL:  ��½���棬�˹��㡣
AUTO:    �Զ���½�� ����Ĭ�϶����Զ���½ģʽ�� 
FRE_AUTO:  WEBˢ��Token��ʱ��ʹ�õġ� 

ͨ�� login.md ���Ƶ�ǰ��½ģʽ��
���������� Ĭ���Զ���½��  ����ת�˹��� 
           ע���� ת�˹�
		   Web ˢ�£� תFRE �Զ�ģʽ��

		   
2019-6-28
���ڰ汾�ţ�
  APP_VER+ SVN_VER,    ��ǰӦ�ó���汾+��ˮ��   "XXX.XX" + "." + "xxxx "

2020-4-20
���� ����Ⱥ���жϺ�Ⱥδ����Ϣ�Ľӿ� 