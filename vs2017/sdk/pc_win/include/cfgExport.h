/*
 * cfgExport.h
 *  各端通过获取的数据结构定义,此头文件中所有结构体定义以st_开头
 *  Created on: 2015年8月5日
 *      Author: sharp
 */

#ifndef PROTOCOL_CFGEXPORT_H_
#define PROTOCOL_CFGEXPORT_H_

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "config.h"

///获取配置的类型 ,标识<G>的是全局配置，不用登录就可以用．，<U>是用户/客户端实例相关配置.
///接口实际参数为[param] 的指针
enum  {
	///<G>获取终端最近一次登录信息　[param] 写：st_LoginInfoBean　，读：st_loginfoArray
	cfg_lastLogininfo =1,
	///<G>代理配置，ＰＣ专用 [param] st_netProxy
	cfg_netproxy=2,
	///<G>网络设置, PC 专用 [param] st_net
	cfg_net=3,
	///<G>根路径　　[param]　std::string
	cfg_rootpath=4,
	///<G>头像路径 [param]　std::string
	cfg_headImgpath=5,
	///<G>是否插电 [param] bool   true插电，bool不插电 上面设置，在ＳＤＫ里面使用
	cfg_plugPower=6,
	/**
	 * \brief <G>网络状态 [param] int32 　0：断网，１：在线WIFI或者有线,2:在线２Ｇ，３：在线３Ｇ，４在线４Ｇ
	 * 当网络发生变化的时候上面设置，ＳＤＫ使用
	 * 如果是处在IPV6网络环境下
	 */
	cfg_netStatus=7,
	///<U>获取该用户聊天中图片信息的保存路径 [param]　std::string
	cfg_userImgPath=8,
	///<U>获取该用户聊天中音频信息的保存路径 [param]　std::string
	cfg_userAudioPath=9,
	///<U>获取该用户聊天中视频信息的保存路径 [param]　std::string
	cfg_userVideoPath=10,
	///<U>获取该用户聊天中cache           [param]　std::string
	cfg_usercachePath=11,
	///<U>获取该用户聊天中文件信息的保存路径 [param]　std::string
	cfg_userFilePath=12,
	///<G>设置登录地址, 内部调试使用.   [param]　st_loginAddress
	cfg_loginAddress=13,
	/**
	 * \brief <U>日志标识
	 * [param] int32 , 默认开发所有日志
	 * 0   : 关闭所有日志
	 * 0xFF: 打开所有日志
	 * 0x01: 调试日志 详细情况,标识：sdklog_debug
	 * 0x02: 运行状态信息，标识： sdklog_trace
	 * 0x04: 注意 有可能出错 ,比如内存占用高等 标识: sdklog_notice
	 * 0x08: 出错,但可以自行修复	sdklog_warn,
	 * 0x10: 除错，可能无法恢复    sdklog_err,
	 */
	cfg_setLogFlag=14,
	///<U>获取plugin管理接口  [param] IPluginSlot **/
	cfg_getPluginSlot,
	/**
	 * \brief <G>设置安卓消息响应模式,所有客户端实例都受控制,需要在第一次实例前调用
	 * 设置１，ＳＤＫ线程主动调用ＪＡＶＡ层ＡＰＩ
	 * 设置０，虚拟机线程主动调用ＳＤＫ，ＳＤＫ进行回调.
	 * [param] int
	 */
	cfg_setAndroidRespMode=16,
	/**
	 * \brief <U>当cfg_setAndroidRespMode为１时有效,每个实例设置不同的对象
	 * 这个类要和安卓的ＳＤＫAPI层商议好
	 */
	cfg_setJvmInterfaceObjForResp=17,
	/**
	 * \brief 获取ＳＤＫ版本号 [param] std::string
	 */
	cfg_sdkVersion=18,

	/**
	 * \brief 屏幕状态 安卓,IOS专用 [param] int , 0是暗，1是亮
	 */
	cfg_screenStatus=19,

	/**
	 * \brief ＳＤＫ证书路径,全路径,返回失败，标识证书校验失败.需要在initClient之前设置
	 */
	cfg_certificatePath=20,
	/**
	 * \brief 传入的文字编码格式  [param] int , 0是utf-8，1是gb 默认为uft-8,
	 * 需要在initClient之前设置.
	 */
	cfg_textCoding = 21,

	/**
	 * \brief <U>互联功能配置
	 * [param]  int , 0是否没有互联，１是有互联。默认使用互联
	 */
	cfg_InterConnect,

	/**
	 * \brief <G>APP名称， 安卓是包名，IOS是应用ID。
	 * [param] string
	 */
	cfg_appName,

	/**
	 *　\brief <U>获取预登录附加数据
	 *　[param] st_loginExData ,
	 *　[return] true 代表服务器可用
	 */
	cfg_loginExData,

	/**
	 * \brief <U>设置ＮＯＴＩＦＹ状态
	 * [param] int   0代表打开，１代表关闭
	 */
	cfg_notifyStatus,

	/**
	 * \brief <U> 多服务器信息保留,for linkdood json string.
	 * [param] vector<st_subSrv> ,包含当前登录的服务器
	 */
	cfg_subserverInfo ,

	/**
	 * \brief <U> 登录后批量消息推送（for nanjing 移动端多服务器）,通过异步推送到界面
	 */
	cfg_getLoginDatagain,

	/**
	 * \brief <U>当前语言环境
	 * [param] int 1.中文 2.英文
	 */
	cfg_language,


	/**
	* \brief <u>  获取缓存接口
	*/
	cfg_getCache,

	/**
	 * \brief 获取数据库加密密钥
	*/
	cfg_getPrivateKey,
	
	/**
	* \brief <G>  应用版本号
	*/
	cfg_appVersion,

	/**
	* \brief <G>  获取上一次预登录数据
	* [param] std::string , 输入用户账号，返回成功得话，里面是预登录信息
	*/
	cfg_getLastPreLoginData,

	/*
	 * \brief <G> 设置文件加密算法 
	 *    [param] int  可选见aes.h 头文件 
	*/
	cfg_setAlgorithm,
	
	/**
	* \brief <U> 设置是否开启消息漫游，开启后可能会影响获取历史的响应速度,
	* 0为关闭，非零为打开，默认关闭
	*/
	cfg_msgRoaming = 34,

	///<U>获取该用户表情文件信息的保存路径 [param]　std::string
	cfg_userEmotionPath = 35,

	///<G>设置解析消息的接口  [param]　jsonToolInterface 的指针
	cfg_jsonToolInterface=36,

	 /**
	* \brief <U> 设置资源根路径，包括图片，文件，视频，音频路径都受影响
	* 比如设置为/home/sharp/。 图片路径就会成为/home/sharp/{usrid}/image 
	* userid为当时登录的用户ID
	*/
	 cfg_rcRootPath = 37 ,
	 
	 /**
	  *  \brief 登录票， 从外部设置进来绑定该客户端实例上，再进行自动登录的时候使用 。
	  *  参数为st_outterTicket指针
	  */
	cfg_ticket,

	/*
		\brief G  设置密码是否加密
		参数为int32 1为加密， 0 为不加密， 默认加密

	*/
	cfg_isPwCrypt ,

	/**
	 * \brief G 获取邀请码
	 * 参数为char * , 长度最少为128.
	 * 传入为服务器地址, 输出为邀请码
	 */ 
	cfg_getInvitCode,
	/**
	* \brief G 通过邀请码获取IP
	* 参数为std::string
	* 传入邀请码, 输出为服务器地址
	*/
	cfg_getIpByInvitCode,
	/**
	* \brief 是否为https预登录
	* 参数为int8 0 http  1 https
	*/
	cfg_httpsPreLogin,
	/**
	* \brief 是否启用多通道 
	* 参数为int8 0 不启用  1 启用(默认不启用)
	*/
	cfg_multichannel,
	/**
	* \brief 获取预登陆信息
	*/
	cfg_getPreloginInfo,

	/**
	* \brief 是否为消息盒子
	* 参数为int8 0 无消息盒子方式  1 消息盒子方式
	*/
	cfg_MessBoxPreLogin,

	cfg_Export_max,      	//配置导出最大值,无特殊意义
 };

/*
 * \brief 最近一次登录信息基本结构
 */
struct    st_LoginInfoBean{
	st_LoginInfoBean(){
        flag = 0;
        status = 0;
        keepPwd = 0;
        autoLogin = 0;
        userid = 0;
        time = 0;
		userType = 0 ;
	}

	int32 flag;						///< 多账号登录顺序
	int32 status;				    ///< 在线状态-1：离线，1:在线；2:隐身,3:忙碌,4:离开,5:请勿打扰,6:想聊天 移动端用前两个
	int32 keepPwd;					///< 是否记录密码1：是，0：否 PC使用
	int32 autoLogin;			    ///< 是否自动登录1：是，0：否 PC使用
	int64 userid ;				    ///< 用户ID
	int64 time;						///< 上次登录时间
	std::string account;			///< 帐号
	std::string name ;              ///< 用户名称
	std::string pwd;				///< 密码 未加密
	std::string avatar;				///< 头像 PC使用
	std::string entArea;			///< 企业域
	int32 userType;                 ///< 登录账户类型，1：手机，2：QQ，3：邮箱，4：UserID
	std::string nationalCode;       ///< 国家代码
	std::string phone;				///< 绑定的手机
	std::string email;				///< 绑定的邮箱

	const std::string output_parameter()
	{
		std::stringstream ss;
		ss << "st_LoginInfoBean::flag ＝ " << flag << "\n";
		ss << "st_LoginInfoBean::status ＝ " << status << "\n";
		ss << "st_LoginInfoBean::keepPwd ＝ " << keepPwd << "\n";
		ss << "st_LoginInfoBean::userid ＝ " << userid << "\n";
		ss << "st_LoginInfoBean::time ＝ " << time << "\n";
		ss << "st_LoginInfoBean::account ＝ " << account << "\n";
		ss << "st_LoginInfoBean::name ＝ " << name << "\n";
		ss << "st_LoginInfoBean::pwd ＝ " << pwd << "\n";
		ss << "st_LoginInfoBean::avatar ＝ " << avatar << "\n";
		ss << "st_LoginInfoBean::entArea ＝ " << entArea << "\n";
		ss << "st_LoginInfoBean::nationalCode ＝ " << nationalCode << "\n";

#ifdef LOCAL_DEBUG
		std::cout << ss.str();
#endif
		return ss.str();
	}
};

/**
 *  \brief cfg_lastLogininfo  类型返回
 */
struct    st_loginfoArray  {
	/**
	* \brief 移动端只有一条信息,
	*  PC端多条信息
	*/
	std::vector<st_LoginInfoBean>  _vt;

	const std::string output_parameter()
	{
		std::stringstream ss;
		ss << "st_loginfoArray::_vt.size() ＝ " << _vt.size() << "\n";
		for (unsigned int i = 0; i < _vt.size(); i++)
		{
			ss << "st_loginfoArray::_vt[ " << i << " ] ＝ " << _vt[i].output_parameter() << "\n";
		}

#ifdef LOCAL_DEBUG
		std::cout << ss.str();
#endif
		return ss.str();
	}
};

/**
 * \brief 代理配置
 * PC专用
 */
struct st_netProxy {
	int8     type;         ///< 0-不使用，１-http1.1  2-http1.0  3-socket4  4-socket5
	uint16   port;         ///< 端口
	std::string addr;      ///< 地址
	std::string user;      ///< 用户名
	std::string pw;        ///< 密码
	
	const std::string output_parameter()
	{
		std::stringstream ss;
		ss << "st_netProxy::type ＝ " << type << "\n";
		ss << "st_netProxy::port ＝ " << port << "\n";
		ss << "st_netProxy::addr ＝ " << addr << "\n";
		ss << "st_netProxy::user ＝ " << user << "\n";
		ss << "st_netProxy::pw ＝ " << pw << "\n";

#ifdef LOCAL_DEBUG
		std::cout << ss.str();
#endif
		return ss.str();
	}
};
typedef enum {
	NETPROXYTYPE_HTTP = 0, /* CONNECT HTTP/1.1 */
	NETPROXYTYPE_HTTP_1_0 = 1, /* CONNECT HTTP/1.0 */
	NETPROXYTYPE_SOCKS4 = 4,
	NETPROXYTYPE_SOCKS5 = 5,
	NETPROXYTYPE_SOCKS4A = 6,
	NETPROXYTYPE_SOCKS5_HOSTNAME = 7,
} netProxyType;

struct st_netProxyConfig {
	netProxyType   type;
	std::string    addr;
	uint16       port;
	std::string    user;
	std::string    passcode;
};

/**
 * \brief 网络配置
 * PC专用
 */
struct st_net {
	/**
	 * \brief 每条记录格式为　　起始ＩＰ-终止ｉＰ
	 * X.X.X.X-X.X.X.X
	 */
	std::vector<std::string>  addrlist;
	
	const std::string output_parameter()
	{
		std::stringstream ss;
		ss << "st_net::addrlist.size() ＝ " << addrlist.size() << "\n";
		for (unsigned int i = 0; i < addrlist.size(); i++)
		{
			ss << "st_net::addrlist[ " << i << " ] ＝ " << addrlist[i] << "\n";
		}

#ifdef LOCAL_DEBUG
		std::cout << ss.str();
#endif
		return ss.str();
	}
};

/**
 * \brief 登录地址结构
 */
struct st_loginAddress {
	std::string strIp ; ///< IP地址或者域名
	uint16      port  ; ///< 端口
	st_loginAddress() {
		port = 80 ;
	}
	
	const std::string output_parameter()
	{
		std::stringstream ss;
		ss << "st_loginAddress::strIp ＝ " << strIp << "\n";
		ss << "st_loginAddress::port ＝ " << port << "\n";

#ifdef LOCAL_DEBUG
		std::cout << ss.str();
#endif
		return ss.str();
	}
};

/**
 * \brief 预登录附加结构
 */
struct st_loginExData {
	///输入信息
	std::string   srvName ;  ///< 服务器名称,获取时候必须填写 !!!
	/**
	 * \brief 设备信息 , 获取时候必须填写 !!!
	 * 例如 pc-window7,an-xiaomei2,ios-iphone4s
	 */
	std::string   device ;
	std::string   local  ;
	std::string   version ;
	std::string   mark ;
	std::string   mac ;
	std::string   acoount ;
	std::string   cookiet;
	std::string   netType ;
	std::string   loginType;

	///下面为输出信息
	std::string   eLogo ;   ///<　英文ＬＯＧＯ
	std::string   imName ;  ///<　名称
	std::string   bgImg  ;  ///<　背景图片
	std::string   eName  ;  ///<　企业名称
	std::string   logoImg ; ///<　标识图片
	int8   createGroup ; ///<　是否开放组功能开关 关闭：０，打开：１
	int8   tools; 		///<　是否显示"工具"页
	int8   priv ; 		///<　是否允许群内私聊开关 关闭：０，打开：１
	int8   plan ; 		///<　群成员是否可以发起安排　是：　１，否：０
	int8   activity ; 	///<  群成员是否可以发起活动开关　打开：１　，　关闭：　０
	int8   attention ; 	///<  是否显示"关注页" 是:1 否：０
	int8   redBag ;    	///<　是否显示红包 是：１　，否: 0
	int8   offLine ;   	///<　离线配置项　0.默认的,密码离线登陆,1.不需要密码就可以登陆,相应的记住prikey,2.不允许离线口令登陆
	int8   smcMode ;   	///<　通知消息详情模式（1.通知详情，2.通知源隐藏内容 3.完全隐藏）
	int8   bReg ;      	///<  是否允许客户端注册
	std::string Orijson ; ///< 原始的ＪＳＯＮ
};

struct st_subSrv {
	std::string  addr;  ///< 服务器地址
	int64        userid;///< 用户ＩＤ
	std::string  name ; ///< 登录账号名称
	std::string  avatar ; ///< 头像
	std::string  account ;///< 账号
	std::string  remark ;
	int8         type ;  ///< 账号类型
};

///预登录结构体
struct st_preLogincfg {
	std::string  area;     ///< 输入 服务器
	std::string  account ; ///< 输入 账号
	int64 userid ;         ///< 输出 用户ID 
	std::string  json ;    ///< 输出 输出预登录结果
};

///登录票
struct st_outterTicket {
	int64       userid ;     ///用户ID
	std::string ticket ;     ///ID对应的票
};

#endif /* PROTOCOL_CFGEXPORT_H_ */
