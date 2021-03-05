#pragma once
#include <string>
#include <vector>
#include "IDRangeJuge.hpp"

const int buffersize = 10000;
//����ƥ���
#define EMOJI_IMAGE   "[4f072095e2574b66aa0c6c09acfb3f3e]"
#define EMOJI_REG       "(\\[4f072095e2574b66aa0c6c09acfb3f3e\\](.*?)\\[4f072095e2574b66aa0c6c09acfb3f3e\\])"

//���͵�����ļ�����
#define 	MAX_FILE_LIMIT   128*1024*1024 
#define		SYS_MSG_ID -5
#define		SUBSCRIPTION_NUM_ID -6  //�Ự�б��ĺ�ID
#define		APP_TMP_ITEM_ID -4
#define		VIDEO_MSG_TYPE 254
#define     ENTAPP_TMP_ITEM_ID  -7
#define     CIRCLE_OF_COLLEAGUES_ID 1 //����ȦID

//�Ự Ⱥ ��ϵ�� ��ҵ ����һ�α�ʾ������
#define    CHAT_FLAG     0x01
#define    CONTACT_FLAG  0x02
#define    GROUP_FLAG    0x04
#define    ENTPRISE_FLAG 0x08

//��Ϣ����
//1:html 2:�ı���3:��Ƶ 4:λ�� 5:ͼƬ6:�ļ� 7:��Ƭ 8:����ʾ
enum MsgType{
	MEDIA_MSG_HTML = 1,										//HTML�ļ�
	MEDIA_MSG_TEXT = 2,										//�ı��ļ�
	MEDIA_MSG_AUDIO = 3,									//������Ϣ
	MEDIA_MSG_POS = 4,										//λ��
	MEDIA_MSG_PIC = 5,										//ͼƬ
	MEDIA_MSG_FILE = 6,										//�ļ�
	MEDIA_MSG_CARD = 7,										//��Ƭ
	MEDIA_MSG_TIP = 8,										//����ʾ
	MEDIA_MSG_WEBLINK = 9,                                //��ҳ������Ϣ
	MEDIA_MSG_IMAGETXT = 12,                        //ͼ����Ϣ
	MEDIA_MSG_MULTIMSG = 13,								//�����Ϣ
	MEDIA_MSG_VIDEO = 14,									//��Ƶ��Ϣ
	MEDIA_MSG_AUDIOONLINE = 15,                   //��Ƶ��Ϣ
	MEDIA_MSG_TASK = 17,                 //������Ϣ
	MEDIA_MSG_REVOKE = 18,									//������Ϣ
	MEDIA_MSG_DYNAMIC_EMOJI = 19,							//��̬����
	MEDIA_MSG_TEMPLATE=26,									//ģ����Ϣ
	MEDIA_MSG_MOREPIC  =28,							   //�Ź�����Ϣ
	MEDIA_MSG_RED_PARKET = 88,								//���
	MEDIA_MSG_MICRO_VIDEO = 89,
	MEDIA_MSG_SUPER = 0xFF									//�ļ�ֱ��
};
//����Ƶ��Ϣ��չ����
enum VedioMsgExtendMsg{
	VEDIO_REQUEST= 201,		 //����
	VEDIO_REQUEST_CANCEL = 202,    //����ȡ��
	VEDIO_REQUEST_REFUSE = 203,    //���оܾ�
	VEDIO_USER_BUSY = 204,		 //�û�����ͨ����
	VEDIO_CALLCLOSED = 205,        //�û��Ҷ�
	VEDIO_CALLBACK_SDP = 207,      //�ص�sdp
};

//Ӧ�����Ͷ���
enum AppType{
	APP_H5=1,//1(H5Ӧ��), 2(IOSӦ��), 3(AndroidӦ��), 4(�ڲ�Ӧ��), 5(���Ӧ��)
	APP_IOS,
	APP_ANDROID,
	APP_INNER,
	APP_QUICK,
};


