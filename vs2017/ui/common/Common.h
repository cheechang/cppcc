#pragma once
#include <QString>
extern float gDdpi;
#define PADDING 1
#define SHADOW_WIDTH            2
#define WINDOW_WIDTH            1100 //860
#define WINDOW_HEIGHT           680//712
#define WINDOW_START_X          0
#define WINDOW_START_Y          0
#define WINDOW_PAGE_COUNT       4
#define WINDOW_BUTTON_COUNT     4
#define WINDOW_PAGE_MOVE        20
#define WINDOW_ONEBUTTON_WIDTH  170
#define DEFAULT_SKIN            ":/skin/blue"
#define DEFAULT_UNITGROUP		":/chat/unitgroup_head"
#define DEFAULT_GROUP           ":/base/group_head"
#define DEFAULT_AVATAR          ":/base/default_head"
#define DEFAULT_APP				":/base/app_default"
#define DEFAULT_PICTURE         ":/chat/pic"
#define MYDEVICE_SIGN           "mydevice"
#define TREEVIEW_HOVER_CLOLOR   "#e5e7ec"
#define TREEVIEW_NORMAL_CLOLOR   "#fafafa"
#define HEAD_SIZE               40
#define GIF_SIZE                96
#define APP_ICON_SIZE           50
#define INTERFACE_NAME			"content"
#define USER_AGENT				"qtwebkit"
#define MAX_UNREADMSG_COUNT     5
#define transfer(x) QString::fromLocal8Bit(x)
#define APP_NAME                transfer("ȫ����ЭίԱ�ƶ���ְƽ̨")
#define APP_MARK   "CPPCC"   //2019-5-20 bxy change
#define DEAFALT_SERVER          "qgzx.linkdood.cn" //"qgzx.linkdood.cn"  //����114.255.32.32"
#define APP_ACCOUNT_ID	10001
#define ENTERPRISE_ACCOUNT_ID	10002
#define MYDEVICE_ID     10003
#define ONLY_HOME_PAGE

const  int         WINDOWMARGINS = 1 * gDdpi;
const  int		   WINDOWRADIUS = 4 * gDdpi;
//������Ϣ10����
#define MSG_RECALL_VALID_TIME   10
#define SHAKE_TEXT "&:flash"
#define ORDER_TEXT transfer("ָ�����:")

#define LOGINPASSWD "19a0dff91b2f49049d049a4f7bc59611"
#define Red_AllUnRead rgba(255, 0, 0, 1)
#define Orange_PartialRead rgba(255, 128, 0, 1)
#define Blue_AllRead rgba(20, 163, 255, 1)

const float PICTURE_SCALED = 0.5;
typedef enum{
	UI_EN,
	UI_ZH
}LANGUAGE;

typedef enum{
 ENTER_SEND=1,
 CTRLENTER_SEND,
}SENDSHORTCUT;
typedef enum{
	SAFE,
	SINA,
	RENREN
}LOGIN;

//��Ϣ����
typedef enum{
    MSG_ALWAYS = 1,   //ʼ������
    MSG_MUTE,     //ʼ�վ���
    MSG_CLASSIFY
}MSGNOFIY;

typedef enum{
    CONFLICT_NONE,
    CONFLICT_PRTSCKEY,
    CONFLICT_PUSHMSGKEY
}CONFLICT;

typedef enum{
	HELP_ONLINE,
	PLATFORM_HELP,
	LOGIN_HOME,
	PROTECT
}ACTION;

//ö�ٰ�ť�ļ���״̬
typedef enum{
	NORMAL,
	ENTER,
	PRESS,
	NOSTATUS
}ButtonStatus;

//ҳ���л�ö��
typedef enum{
	APP_PAGE,
	CHAT_PAGE,
	CONTACT_PAGE,
	WORKBENCH_PAGE
}PAGENAME;

//�Ựʱ������
typedef enum {
	CHATLIST_TIME=1,
	CHATWND_TIME
}TIMETYPE;

//�豸����
typedef enum{
	DEVICE_PC =1,
	DEVICE_PHONE,
}DEVICETYPE;

//����ID
typedef enum{
	LOGIN_WINDOW=0xFF,
	UPDATE_WINDOW,
	MAIN_WINDOW,
}DIAGLOGID;

//��������ͼ�ʹ�ͼ�ĳߴ�
enum ImageSize{
	THUMP_PIC_WIDTH   =  400,
	THUMP_PIC_HEIGHT  =  300,
	BIG_PIC_WIDTH      =     1920,
	BIG_PIC_HEIGHT      =    1080
};

//������Ϣ״̬
enum MsgStatus{
	MSG_INIT,
	MSG_SENDING,
	MSG_RECEIVING,
	MSG_FINISH,
	MSG_FAILED,
	MSG_MAX,
};

enum FileMsgStatus{
	FILE_TRANSFORMAT=MSG_MAX,
	FILE_DOWNLOAD,
	FILE_FINISH,
	FILE_FAILED
};

//�ļ�Ĭ��·��
enum FileDefaultPathType{
	DATAPATH_USERIMG=0,
	DATAPATH_USERFILE,
	DATAPATH_USERAUDIO,
	DATAPATH_USERVIDEO,
	DATAPATH_MAX,
};

enum FileCachePathType{
	DATACACHEPATH_USERIMG=DATAPATH_MAX,
	DATACACHEPATH_USERFILE,
	DATACACHEPATH_USERAUDIO,
	DATACACHEPATH_USERVIDEO
};

enum MsgWidgetType{
	GENERAL_MSG=1601,
	TIME_MSG,
	LOADING_MSG
};


//����չʾ��Ϣ��Ҫ����Ϣ
struct UserInfo{
	struct UserInfo():selfid(0),selfavatar(""),selfName(""){}
	qint64  selfid;
	QString selfavatar;
	QString selfName;
};

//�Ự������Ϣ
struct TargetInfo{
	TargetInfo():chattype(0),targetId(0),targetName(""),targetAvatar(""){
	}
	int     chattype; 
	qint64  targetId;
	QString targetName;
	QString targetAvatar;
};

//������Ϣ��Ϣ
struct MsgItemInfo{
	struct MsgItemInfo():status(0),msgtype(0),fromId(0),localId(0),msgid(0),msgtime(0),targetId(0),othername(""),otheravatar(""){};
	qint32  status; //��Ϣ����״̬����������ʱʹ��
	qint32  msgtype;
	qint64  fromId;
	qint64  localId;
	qint64  msgid;
	qint64  msgtime;
	qint64  targetId;
	QString othername;
	QString otheravatar;
};

//ý����Ϣ�ṹ�嶨��
struct MediaMsgItemInfo{
	struct MediaMsgItemInfo():issaveas(false),isdevice(false),targetId(0),msgid(0),fromid(0),size(0),binary(""),encrptkey(""),name(""),url(""),mainurl(""){};
	bool       issaveas;
	bool       isdevice;
	qint64     targetId;
	qint64     msgid;
	qint64     fromid;
	qint64     size;
	QByteArray binary;
	QString    encrptkey;
	QString    name;
	QString    url;
	QString    mainurl;
};
