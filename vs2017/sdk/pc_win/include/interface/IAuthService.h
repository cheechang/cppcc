#pragma once

#include "../model/LoginInfo.h"
#include "../model/Packet.h"
#include "../model/Account.h"
#include "IService.h"
#include <string>

#define VER_IAUTH INTERFACE_VERSION(1,0)
static const VRVIID IID_IAuthSrvice = { 0x3271f2c2, 0xb855, 0x4234, 0x9f, 0x8b, 0x4d, 0x86, 0xd0, 0x6c, 0x2b, 0xb7 };

namespace service 
{

class IAuthService : public IService
{
public:
		
	virtual ~IAuthService(){};

	/*****************************************注册通知回调*******************************************/

	/**
	* \brief 监听网络连接状态
	* @param[out] cb 0代表网络ＯＫ，非零是网络异常
	*/
	virtual void regNetChangedCb(SFunction< void(int) > cb) = 0;

	/**
	* \brief 设置监听数据库升级完成的回调
	* @param[out] cb 0代表开始 1代表升级完成 2升级失败
	*/
	virtual void regDbUpdatedCb(SFunction< void(int) > cb) = 0;

	/**
	* \brief 重新登录时推送
	* @param[out] cb  _1 错误标示,  _2用户ID
	*/
	virtual void regReLoginCb(SFunction< void(int, int64) > cb) = 0;

	/**
	* \brief 版本升级推送
	* @param[out] cb 版本升级信息结构 见packet.h
	*/
	virtual void regUpgrageCb(SFunction< void(UpgradeInfo&) > cb) = 0;

	/*****************************************请求接口*******************************************/

	/**
	* \brief 快速注册
	* @param[in] server 传入服务器地址，域名或IP均可
	* @param[in] name 用户昵称
	* @param[in] account 传入注册账号 如果是手机账户格式为“0086158********”
	* @param[in] passwd 密码
	* @param[out] cb 传入接收结果回调 _1错误信息  _2超时
	*/
	virtual void quickRegister(const std::string &server, const std::string &name, const std::string &account, const std::string &passwd, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取注册验证码
	* @param[in] server 服务器或邀请码
	* @param[in] account 传入注册账号 如果是手机账户格式为“0086********”
	* @param[out] cb 传入接收结果回调 _1错误信息  _2超时
	*/
	virtual void getRegCode(const std::string& server, const std::string &account, SFunction<void(ErrorInfo, int/*超时*/)> cb) = 0;

	/**
	* \brief 注册用户
	* @param[in] regCode 验证码
	* @param[in] user    传入用户名，建议使用真实姓名
	* @param[in] pwd	 传入注册密码
	* @param[out] cb 传入接收结果回调  _1错误信息 _2如果是通过邀请码注册，返回邀请码创建者ID
	*/
	virtual void signup(const std::string& regCode, const std::string &user, const std::string &pwd, SFunction<void(ErrorInfo, int64)> cb) = 0;

	/**
	* \brief 获取重置密码验证码
	* @param[in] server 服务器
	* @param[in] account 传入注册账号 如果是手机账户格式为“0086********”
	* @param[out] cb 传入接收结果回调 _1错误信息  _2超时
	*/
	virtual void getResetPwCode(const std::string& server, const std::string &account, SFunction<void(ErrorInfo, int/*超时*/)> cb) = 0;

	/**
	* \brief 重置密码
	* @param[in] regCode 验证码
	* @param[in] user    传入用户名，为空代表不改名
	* @param[in] pwd	 传入新密码
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void resetPasswd(const std::string& regCode, const std::string &user, const std::string &pwd, SFunction<void(ErrorInfo)> cb) = 0;
		
	/**
	* \brief 获取密码复杂度
	* @param[in] cb 传入接收结果回调 _1错误信息
	*  _2密码规则: 
	*	高8位代表最小长度
	*	低8位，按照最低位开始，依次代表:(1代表必须，0 表示可选)
	*	1. 是否必须有数字
	*	2. 是否必须有小写字母
	*	3. 是否必须有大写字母
	*	4. 是否必须有英文字母
	*	5. 是否必须有字符(特殊字符)
	*	6. 是否允许注册(1允许，0不允许)
	*/
	virtual void getPasswordRule(SFunction<void(ErrorInfo, int)> cb) = 0;

	//////////////////////////////////////////////////////////////////////////
	//	登录相关接口

	/**
	*  \brief 登录
	* @param[in] user 传入用户名 如果是手机账户格式为“0086158********”
	* @param[in] pwd 传入密码
	* @param[in] server 传入服务器地址，域名或IP均可
	* @param[out] cb 传入接收结果回调 _1错误信息  _2 用户Id  _3 帐号被锁定剩余时长  _4 返回1102错误时的验证码路径
	* @return	int64 返回当前localID，用于取消该次执行
	*/
	virtual int64 login(const std::string& user, const std::string& pwd, const std::string& server,
						SFunction<void(ErrorInfo, int64,int64, const std::string&)> cb) = 0;

	//离线转在线接口
	/**
	 * @param[in] server 传入服务器地址，域名或IP均可
	 * @param[out] cb 传入接收结果回调 _1错误信息  _2用户Id  _3 帐号被锁定剩余时长  _4 返回1102错误时的验证码路径
	 * @return	int64 返回当前localID，用于取消该次执行
	 */

	virtual int64 offLineToLogin(const std::string& server,SFunction<void(ErrorInfo, int64, int64, const std::string&)> cb) = 0;
	//登录

	/**
	* \brief 自动登录（不用填密码）
	* @param[in] userid 传入用户ID
	* @param[in] server 传入服务器地址，域名或IP均可
	* @param[out] cb 传入接收结果回调 _1错误信息  _2用户Id  _3 帐号被锁定剩余时长  _4 返回1102错误时的验证码路径
	* @return	int64 返回当前localID，用于取消该次执行
	*/
	virtual int64 autoLogin(int64 userid, const std::string &server, SFunction<void(ErrorInfo, int64, int64, const std::string&)> cb) = 0;

	/**
	* \brief 离线登录
	* @param[in] userId 用户id如果为零，获取最近一次登录成功的用户id
	* @param[in] pwd 密码
	* @param[out] cb 传入接收结果回调 _1错误信息 
	*/
	virtual void offlineLogin(int64 userId, const std::string& pwd, SFunction<void(ErrorInfo)> cb) = 0;
		
	/**
	* \brief 登出
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void logout(SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 取消登录
	* @param[in] operateid 传入对应登录操作的ID
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void abortLogin(int64 operateid, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 验证登录验证码或者获取下一张验证码
	* @param[[in] account 传入登录账号
	* @param[[in] code	 传入验证码内容 code为空则获取下一张验证码
	* @param[[out] cb 传入接收结果回调 _1错误信息  _2 下一张验证图片
	*/
	virtual void verifyImgCode(const std::string& account, const std::string& code, 
							SFunction<void(ErrorInfo, const std::string&)> cb) = 0;

	/**
	* \brief 获取安全中心URL
	* @param[in] server 传入企业服务器
	* @param[out] cb 传入接收结果回调 _1错误信息  _2 url
	*/
	virtual void getSecUrl(const std::string &server, SFunction<void(ErrorInfo, const std::string&)> cb) = 0;

	/**
	* \brief 修改密码
	* @param[in] oldPw 传入旧密码
	* @param[in] newPw 传入新密码
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void changePassword(const std::string &oldPw, const std::string &newPw, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取CLIENTKEY
	* @param[out] cb 传入接收结果回调  _1错误信息  _2 clientkey
	*/
	virtual void getClientKey(SFunction<void(ErrorInfo, const std::string&)> cb) = 0;

	/**
	* \brief 获取绑定手机验证码
	* @param[in] phone 手机号
	* @param[in] language 语言
	* @param[out] cb 传入接收结果回调  _1错误信息  _2超时重发时间  _3注册ID
	*/
	virtual void getBindPhoneCode(const std::string &phone, const std::string &language, SFunction<void(ErrorInfo, int32, int64)> cb) = 0;

	/**
	* \brief 通过获取的验证码绑定手机
	* @param[in] phone 手机号
	* @param[in] code 验证码
	* @param[in] registryID 获取验证码时返回的ID
	* @param[out] cb 传入接收结果回调  _1错误信息 0成功 100参数不正确 120账号不存在 381未指定接受者  382未指定接收者类型 
	*				383验证码已过期 384验证码不正确  385发送间隔时间太短 386发送失败  387：未发送过验证码 
	*/
	virtual void bindPhone(const std::string &phone, const std::string &code, int64 registryID,  SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 绑定邮箱
	* @param[in] mail  邮箱号
    * @param[in] lang  语言 zh_cn:中文 en_us:英文
	* @param[out] cb 传入接收结果回调  _1错误信息 0:成功，100:参数错误，120: 帐号不存在，510:帐号已被使用
	*/
    virtual void bindMail(const std::string &mail, const std::string& lang, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取登录的票据(同步接口)
	*/
	virtual std::string getLoginTicket() = 0;

	/**
	* \brief 获取数据库秘钥(同步接口)
	*/
	virtual std::string getPrivateKey() = 0;


	/**
	* \brief 获取登录信息。(同步接口)
	* @param[out] data  用户传入的内存地址，获取成功后，把信息拷贝到此内存中
	* @param[in] len 用户传入内存地址的长度
	* @param[return] 返回0代表获取失败，否则，返回获取数据的实际长度
	*/
	virtual int getLoginInfo(uint8 *data, int len) = 0;

	/**
	* \brief 获取Oauth 授权码
	* @param[in] oauth oauth请求结构，见packet.h
	* @param[out]  cb 传入接收结果回调  _1错误信息 _2授权码
	*/
	virtual void getLoginAuthCode(oauthReq& oauth, SFunction<void(ErrorInfo, const std::string&)> cb) = 0;
	/**
	*根据用户ID向用户发送短信
	*/
	virtual void getqVerifyCodes(qVerifyCodes&, SFunction<void(ErrorInfo,std::map<int64,std::string>&)> cb) = 0;
	/**
	*\brief    获取授权凭证
	*@param[in] appID         应用ID
	*@param[in] accountType   登陆账号类型
	*@param[in] appSecret     企业应用密钥一个凭证,如果appSecret为空，表示获取授权码，如果不为空表示获取授权凭证
	*@param[out] code  cb 传入接收结果回调  _1错误信息 _2授权凭证
	*/
	virtual void getAuthAccessToken(int64 appID, std::string& accountType, std::string& appSecret, SFunction<void(ErrorInfo, const std::string&)> cb) = 0;
	/**
	*\brief 校验accessToken是否过期
	*@param[in] appID         应用ID
	*@param[in] type		  10,校验accessToken是否过期 11刷新accessToken,获得新的accessToken
	*@param[in] accessToken   授权凭证（accessToken，上一步骤获取的）
	*@param[out] code  cb 传入接收结果回调  _1错误信息 _2新的授权凭证 type = 11时使用
	*/
	virtual void checkOrRefreshAccessToken(int64 appID, int type, std::string& accessToken, SFunction<void(ErrorInfo, const std::string&)> cb) = 0;
	/**
	*\brief 根据应用授权凭证获取用户信息
	*@param[in] appID         应用ID（appID）
	*@param[in] accessToken   app授权凭证
	*@param[out] code  cb 传入接收结果回调  _1错误信息 _2见packet.h
	*/
	virtual void getAuthUserBean(int64 appID, std::string& accessToken, SFunction<void(ErrorInfo, AuthUserBean&)> cb) = 0;
	/**
	* \brief   根据网址链接获取授权码，返回的授权码会拼接到网址后面返回,格式为&auth_code=授权码
	* 如:入参:http(s) ://vrv.linkdood/platform/api2/oauth/authorize?id=APPID&st=STATE&sc=SCOPE&uri=xxxxxx
	*    出参:http(s) ://vrv.linkdood/platform/api2/oauth/authorize?id=APPID&st=STATE&sc=SCOPE&uri=xxxxxx&auth_code=yyyyyy
	*@param[in] webSite       网址链接
        webSite中必须有"/platform/api2/oauth/authorize?id=","&st=","&sc=","&uri="这些字段,否则认为不是合法的网址，返回错误，code值对应err_sdk_paramInvalidat宏表示的值；
	*@param[out] code  cb 传入接收结果回调  _1错误信息 _2授权码
	*/
	virtual void getWebSiteAuth(std::string& webSite, SFunction<void(ErrorInfo,std::string&)> cb) = 0;
	/**
	*\brief 对升级包进行签名认证
	*@Param[in] filePath 下载的升级包文件本地路径
	*@Param[in] certPath 证书路径
	*@Param[in] dsg      签名
	*@return  true 验证通过 false 验证失败
	*/
	virtual bool verifyPKSign(const char* filePath, const char* certPath, std::string& dsg) = 0;


};

} /*namespace service*/