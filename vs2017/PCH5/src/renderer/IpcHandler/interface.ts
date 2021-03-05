export type authServiceParam = loginParam | quickRegisterParam | getRegCodeParam | signupParam | getResetPwCodeParam | resetPasswdParam | autoLoginParam | verifyImgCodeParam | changePasswordParam | getLoginAuthCodeParam | getSecUrlParam
export type contactServiceParam = addContactParam | getVerifyTypeParam | removeContactParam | updateContactInfoParam | getContactOnlineParam | getContactInfoParam | contactIsBuddyParam | removeBlackListParam | addBlackListParam | queryExtendedFieldParam
export type chatServiceParam = removeChatParam | sendMessageParam | forwardMessageParam | chatTopParam | getImgMsgParam | getUrlInfoParam | deleteAllMessageParam | deleteMessageByIdParam | deleteMessageByTimeParam | setMessageReadParam | getMessagesParam | setPrivateKeyParam | decryptMsgParam | getMsgDaysParam | getMsgFromDayParam
export type groupServiceParam = createGroupParam | createGroupParam | addGroupParam | removeGroupParam | transferGroupParam | getGroupSetParam | setGroupSetParam | getGroupInfoParam | setGroupInfoParam | getMemberListParam | inviteMemberParam | removeMemberParam | getMemberInfoParam | setMemberInfoParam | isInGroupParam | getGroupFileListParam | deleteGroupFileParam
export type userServiceParam = setSettingParam | getPersonalDataParam | setPersonalDataParam | updateAccountInfoParam | addLocalSettingParam | getLocalSettingParam | updateLocalSettingParam | deleteLocalSettingParam | getAppInfoParam | queryMarketApplicationParam | addOrDeleteApplicationParam | getInstalledApplicationParam | getEntAppInfoParam
export type enterpriseServiceParam = getVisibleOrgUsersParam | getOrgUserInfosParam | getOrgInfoParam | queryEntUserOneByIdParam
export type rtcServiceParam = createChannelParam | acceptOrRejectParam | joinChannelParam | setConferenceInfoParam | switchChannelParam | getAgoraFuncParam
export type fileServiceParam = fileOperateParam | getFileListParam | uploadAvatarParam | uploadFileParam | downloadFileParam | uploadImageParam | downloadImageParam | decryptFileParam | getFilesInfoParam | cancelTransferParam | getNameByUrlParam
export type searchServiceParam = searchFromNetParam | searchFromLocalParam | searchGlobalMessageParam | searchDetailMessageParam | getUserInfoParam
export type sysMsgServiceParam = respToAddBuddyParam | respToEnterGroupParam | setMessagReadParam | getSysMessagesParam | deleteMessageByTypeParam
export type configServiceParam = setLoginInfoParam | setAutoStartParam | getLoginExDataParam

/**
*写入日志(此接口为同步接口)
* action = 'setLog'
* param = level:number, info:string
* 注：此接口不用传入回调函数
   level: number,       // 等级
   LOG_LEV_DEBUG=1,  ///< 调试日志 详细情况
   LOG_LEV_METHOD_BEGIN,  ///< 输出 运行状态信息
   LOG_LEV_METHOD_END,
   LOG_LEV_NOTICE,  ///< 注意 有可能出错 ,比如内存占用高等
   LOG_LEV_WARN,  ///< 除错,但可以自行修复
   LOG_LEV_ERROR,  ///< 出错,要挂掉.
   LOG_LEV_INFO,   //信息
   LOG_LEV_COUNT  ///< 无意义,标识级别数量 
   info: string     // 写入的日志信息
*/
/********************************************* authService  **************************************************/
/**
 * 注册网络变化通知
 * action = 'regNetChangedCb'
 */

/**
 * 注册重新登录通知
 * action = 'regReLoginCb'
 */

/**
 * 登录
 * action = 'login'
 * param = loginParam
 */
interface loginParam {
    user: string,       // 传入用户名 如果是手机账户格式为“0086158********”
    pwd: string,        // 传入密码
    server: string,     // 传入服务器地址，域名或IP均可
    userType: number    // 账号类型
}

/**
 * 登出
 * action = 'logout'
 */

/**
 * 快速注册
 * action = 'quickRegister'
 * param = quickRegisterParam
 */
interface quickRegisterParam {
    server: string,     // 传入服务器地址，域名或IP均可
    name: string,       // 用户昵称
    account: string,    // 传入注册账号 如果是手机账户格式为“0086158********”
    pwd: string         // 密码
}

/**
 * 获取注册验证码
 * action = 'getRegCode'
 * param = getRegCodeParam
 */
interface getRegCodeParam {
    account: string,    // 传入注册账号 如果是手机账户格式为“0086158********”
    userType: number,   // 账号类型
    server: string      // 服务器
}

/**
 * 注册用户
 * action = 'signup'
 * param = signupParam
 */
interface signupParam {
    regCode: string,    // 验证码
    user: string,       // 传入用户名，建议使用真实姓名
    pwd: string,        // 传入注册密码
}

/**
 * 获取重置密码验证码
 * action = 'getResetPwCode'
 * param = getResetPwCodeParam
 */
interface getResetPwCodeParam {
    server: string,     // 服务器
    userType: number,   // 用户类型
    account: string     // 传入注册账号 如果是手机账户格式为“0086158********”
}

/**
 * 重置密码
 * action = 'resetPasswd'
 * param = resetPasswdParam
 */
interface resetPasswdParam {
    regCode: string,    // 验证码
    user: string,       // 传入用户名，为空代表不改名
    pwd: string         // 传入新密码
}

/**
 * 获取密码复杂度
 * action = 'getPasswordRule'
 */

/**
 * 自动登录
 * action = 'autoLogin'
 * param = autoLoginParam
 */
interface autoLoginParam {
    userId: number,     // 传入用户ID
    userType: number,   // 账号类型
    server: string      // 传入服务器地址，域名或IP均可
}
/**
 * 获取图片验证码
 * action = 'verifyImgCode'
 * param = verifyImgCodeParam
 */
interface verifyImgCodeParam {
    account: string,     // 传入登录账号
    code: string     // 传入验证码内容 code为空则获取下一张验证码
}
/**
 *修改密码
 * action = 'changePassword'
 * param = changePasswordParam
 */
interface changePasswordParam {
    oldPw: string,      // 传入旧密码
    newPw: string       // 传入新密码
}
/**
 *获取Oauth 授权码
 * action = 'getLoginAuthCode'
 * param = getLoginAuthCodeParam
 */
interface getLoginAuthCodeParam {
    userId: string,      // 用户ID
    appId: string,       // appId
    accountType: string, // 账户类型
    account: string,     // 账号
    password: string     // 密码
}
/**
 *获取安全中心URL
 * action = 'getSecUrl'
 * param = getSecUrlParam
 */
interface getSecUrlParam {
    server:string  // 服务器
}

/******************************************** contactService *******************************************************/
/**
 *监听联系人头像更新
 * action = 'regContactHeadImgUpdateCb'
 */

/**
 *监听在线状态更新的回调
 * action = 'regPresentCb'
 */

/**
 *设置好友信息更新的回调
 * action = 'regOperateContactCb'
 */

/**
 *监听好友刷新
 * action = 'regContactListCb'
 */
/**
 * 根据条件查询拓展字段信息
 * action = 'queryExtendedField'
 * param = queryExtendedFieldParam
 */
interface queryExtendedFieldParam {
    parentId: number,
    dicKey: string
}
/**
 *添加联系人
 * action = 'addContact'
 * param = addContactParam
 */
interface addContactParam {
    userId: number,       //传入联系人ID
    remark: string,       //传入联系人备注，可以为空
    info: string          //传入验证信息
}

/**
 *获取联系人验证方式
 * action = 'getVerifyType'
 * param = getVerifyTypeParam
 */
interface getVerifyTypeParam {
    targetId: number  //传入联系人ID
}

/**
 *删除联系人传入参数
 * action = 'removeContact'
 * param = removeContactParam
 */
interface removeContactParam {
    targetId: number   //用户id
}

/**
 *更新联系人信息
 * action = 'updateContactInfo'
 * param = updateContactInfoParam
 */
interface updateContactInfoParam {
    userId: number,       //传入联系人ID
    remark?: string,       //修改的联系人备注，可以不传
    isStar?: boolean,      //修改是否为星标，可以不传
    chatImg?: string       //修改聊天背景，可以不传
}

/**
 *获取联系人列表
 * action = 'getContactList'
 */

/**
 *获取联系人在线状态
 * action = 'getContactOnline'
 * param = getContactOnlineParam
 */
type getContactOnlineParam = Array<number>      //传入联系人ID的数组对象

/**
 *获取联系人信息(此接口为同步接口)
 * action = 'getContactInfo'
 * param = getContactInfoParam
 */
interface getContactInfoParam {
    targetId: number   //用户id
}

/**
 *判断联系人与自己是否是好友关系(此接口为同步接口)
 * action = 'contactIsBuddy'
 * param = contactIsBuddyParam
 */
interface contactIsBuddyParam {
    userId: number       //传入联系人ID
}

/**
 *获取黑名单
 * action = 'getBlackList'
 */

/**
 *添加黑名单
 * action = 'addBlackList'
 * param = addBlackListParam
 */
type addBlackListParam = Array<number> //传入联系人ID

/**
 *删除黑名单
 * action = 'removeBlackList'
 * param = removeBlackListParam
 */
type removeBlackListParam = Array<number> //传入联系人ID

/******************************************** chatService *******************************************************/
/**
 *注册最近会话头像更新
 * action = 'regChatHeadImgUpdateCb'
 */

/**
 *注册新聊天消息的回调
 * action = 'regMsgNoticeCb'
 */

/**
 *注册离线消息的回调
 * action = 'regOfflineMsgCb'
 */

/**
 *注册会话列表更新通知
 * action = 'regRecontactCb'
 */

/**
 *获取会话列表(此接口为同步接口)
 * action = 'getChatList'
 */

/**
 *移除会话
 * action = 'removeChat'
 * param = removeChatParam
 */
interface removeChatParam {
    userId: number       //传入会话ID
}

/**
 *发送消息
 * action = 'sendMessage'
 * param = sendMessageParam
 */
interface sendMessageParam {
    targetId: number,      //传入会话方ID
    message: string,       //消息体
    msgProperties?: string,   //消息属性（文件图片等）
    isBurn?: boolean,       //是否阅后即焚
    messageType: number,   //消息类型
    limitRange?: Array<number>, //限制消息用户范围
    relatedUsers?: Array<number>, //@功能使用，填入@人员的用户ID
}

/**
 *转发消息
 * action = 'forwardMessage'
 * param = forwardMessageParam
 */
interface forwardMessageParam {
    fromTargetId: number, // 转发的消息的当前targetId
    toTargetId: number,    // 转发的消息的接收targetId
    messageId: number,     // 转发的消息ID
}

/**
 *消息置顶
 * action = 'chatTop'
 * param = chatTopParam
 */
interface chatTopParam {
    targetId: number, // 置顶的目标ID
    isTop: boolean    // 是否置顶
}

/**
 *获取图片消息
 * action = 'getImgMsg'
 * param = getImgMsgParam
 */
interface getImgMsgParam {
    targetId: number //个人或群ID
}

/**
 *获取URL的详细信息
 * action = 'getUrlInfo'
 * param = getUrlInfoParam
 */
interface getUrlInfoParam {
    url: string   // 网址
}

/**
 *删除所有消息
 * action = 'deleteAllMessage'
 * param = deleteAllMessageParam
 */
interface deleteAllMessageParam {
    delChatList: boolean   // 是否清空联系人列表
}

/**
 *通过msgId删除消息
 * action = 'deleteMessageById'
 * param = deleteMessageByIdParam
 */
interface deleteMessageByIdParam {
    targetId: number,    // 传入会话对应的ID，群或者人
    msgId: Array<number> // 传入要删除的消息ID集合 msgs为空，清空对应targetId的所有消息
}

/**
 *删除时间段消息
 * action = 'deleteMessageByTime'
 * param = deleteMessageByTimeParam
 */
interface deleteMessageByTimeParam {
    targetId: number,    // 传入会话对应的ID，群或者人 targetId为0，则针对所有用户
    beginTime: number,   // 起始时间
    endTime: number      // 结束时间
}

/**
 *设置消息已读
 * action = 'setMessageRead'
 * param = setMessageReadParam
 */
interface setMessageReadParam {
    targetId: number,    // 传入会话对应的ID，群或者人
    msgId: number // 传入要设置已读的消息ID集合,若为0,则是该会话Id全部消息
}

/**
 *获取消息
 * action = 'getMessages'
 * param = getMessagesParam
 */
interface getMessagesParam {
    targetId: number,    // 传入会话对应的ID，群或者人
    msgId: number,       // 传入查询消息的起始ID，将从该消息的下一条消息开始查询
    count: number,       // 传入查询消息总数
    flag: number         // 传入上一页还是下一页 向上偏移 0；向下偏移 1
}

/**
 *设置私信秘钥
 * action = 'setPrivateKey'
 * param = setPrivateKeyParam
 */
interface setPrivateKeyParam {
    targetId: number,    // 传入会话对应的ID，群或者人
    pwd: string       // 私信秘钥  为空代表清除私信密码
}

/**
 *通过消息ID解密消息
 * action = 'decryptMsg'
 * param = decryptMsgParam
 */
interface decryptMsgParam {
    targetId: number,     // 传入会话对应的ID，群或者人
    msgId: Array<number>  // 要解密的消息ID集合
}

/**
 *获取对象聊天时间数组
 * action = 'getMsgDays'
 * param = getMsgDaysParam
 */
interface getMsgDaysParam {
    targetId: number,     // 对象id
    belately: number      // 是否最近 0是最近 非零是要查询的年份
}

/**
 *根据日期获取消息
 * action = 'getMsgFromDay'
 * param = getMsgFromDayParam
 */
interface getMsgFromDayParam {
    targetId: number,    // 用户ID
    bLately: number,     // 是否最近 0 是最近，非零的话要设置 YMD
    msgId: number,       // 消息Id
    count: number,       // 数量
    day: number          // 日
    year: number         // 年
    month: number        // 月
}

/******************************************** groupService *******************************************************/

/**
 *监听群头像更新
 * action = 'regGroupHeadImgUpdateCb'
 */

/**
 *监听群成员头像更新
 * action = 'regMemberHeadImgUpdateCb'
 */

/**
 *设置监听群信息更新的回调
 * action = 'regGroupRefreshCb'
 */

/**
 *设置监听群主更新的回调
 * action = 'regTransferGroupCb'
 */

/**
 *设置监听群成员信息更新的回调
 * action = 'regGrpMemInfoRefreshCb'
 */

/**
 *设置群成员列表更新的回调
 * action = 'regGrpMemRefreshCb'
 */

/**
 *设置获取群成员列表的回调（不使用,只是为了和getMemberList回调函数一致）
 * action = 'regGetGrpMemListCb'
 */

/**
 *监听群列表刷新
 * action = 'regGroupListCb'
 */

/**
 *创建群
 * action = 'createGroup'
 * param = createGroupParam
 */
interface createGroupParam {
    level: number,        // 传入群等级
    name: string,         // 传入群名称
    member: Array<number> // 传入群成员
}

/**
 *加群
 * action = 'addGroup'
 * param = addGroupParam
 */
interface addGroupParam {
    groupId: number,        // 传入群id
    verify_info: string     // 传入验证信息
}

/**
 *解散群
 * action = 'removeGroup'
 * param = removeGroupParam
 */
interface removeGroupParam {
    groupId: number,    // 传入群id
    type: number        // 传入操作类型
}

/**
 *转让群
 * action = 'transferGroup'
 * param = transferGroupParam
 */
interface transferGroupParam {
    groupId: number,    // 传入群id
    userId: number      // 传入新群主的id
}

/**
 *获取群设置
 * action = 'getGroupSet'
 * param = getGroupSetParam
 */
interface getGroupSetParam {
    groupId: number    // 传入群id
}

/**
 *设置群设置
 * action = 'setGroupSet'
 * param = setGroupSetParam
 */
interface setGroupSetParam {
    groupId: number,      // 传入群id
    verify_type?: number,  // 传入验证类型
    is_allow?: boolean     // 传入是否允许成员邀请用户
}

/**
 *获取群信息
 * action = 'getGroupInfo'
 * param = getGroupInfoParam
 */
interface getGroupInfoParam {
    groupId: number      // 传入群id
}

/**
 *设置群信息
 * action = 'setGroupInfo'
 * param = setGroupInfoParam
 */
interface setGroupInfoParam {
    groupId: number,                // 传入群id
    groupBrief?: string,             // 群简介
    groupBulletin?: string,          // 群公告
    groupName?: string,              // 群名称
    groupIcon?: string,              // 群图标
    groupBackgroundURL?: string,     // 群背景图片
    isSearch?: number,               // 群是否可以被外部检索 1可以 2不可以
    groupMessageContentMode?: string // 群消息通知详情: 1、开启(显示详情)  2、关闭(显示通知源，隐藏内容)  默认开启.
    extendProperties?: string,       // 群扩展字段
}

/**
 *获取群列表(此接口为同步接口)
 * action = 'getGroupList'
 */

/**
 *获取群成员列表
 * action = 'getMemberList'
 * param = getMemberListParam
 */
interface getMemberListParam {
    groupId: number      // 传入群id
}

/**
 *邀请群成员
 * action = 'inviteMember'
 * param = inviteMemberParam
 */
interface inviteMemberParam {
    groupId: number,      // 传入群id
    member: Array<number> // 传入成员名单
}

/**
 *移除群成员
 * action = 'removeMember'
 * param = removeMemberParam
 */
interface removeMemberParam {
    groupId: number,      // 传入群id
    member: Array<number> // 传入成员名单
}

/**
 *获取群成员信息
 * action = 'getMemberInfo'
 * param = getMemberInfoParam
 */
interface getMemberInfoParam {
    groupId: number,      // 传入群id
    memberId: number        // 传入成员id
}

/**
 *设置群成员信息
 * action = 'setMemberInfo'
 * param = setMemberInfoParam
 */
interface setMemberInfoParam {
    groupId: number,      // 传入群id
    memberId: number,     // 传入成员id
    memberType?: number,   // 成员类型
    remark?: string        // 成员备注
}

/**
 *判断用户是否在群里(此接口为同步接口)
 * action = 'isInGroup'
 * param = isInGroupParam
 */
interface isInGroupParam {
    groupId: number,      // 传入群id
    memberId: number      // 传入成员id
}

/**
 *获取群文件列表
 * action = 'getGroupFileList'
 * param = getGroupFileListParam
 */
interface getGroupFileListParam {
    groupId: number,      // 传入群id
    beginId: number,      // 传入起始id number
    count: number,        // 传入数量  number
    flag: number          // 传入偏移标志0为向上1为向下
}

/**
 *删除群文件
 * action = 'deleteGroupFile'
 * param = deleteGroupFileParam
 */
type deleteGroupFileParam = Array<number>

/******************************************** userService *******************************************************/

/**
 *监听个人头像更新
 * action = 'regUserHeadImgUpdateCb'
 */

/**
 *设置监听用户信息更新的回调，服务器推送
 * action = 'regOperateUserCb'
 */

/**
 *监听用户信息修改，登录更新后会主动推送
 * action = 'regGetMyselfCb'
 */

/**
 *获取账户信息(此接口为同步接口)
 * action = 'getAccountInfo'
 */
/**
 * 根据用户id分页获取企业号
 * action = 'getEntAppInfo'
 * param = getEntAppInfoParam
 */
interface getEntAppInfoParam {
    pageNum: number,
    pageSize: number,
    type: number  // 1.企业号 2.应用号
}
/**
 *更新用户信息
 * action = 'updateAccountInfo'
 * param = updateAccountInfoParam
 */
interface updateAccountInfoParam {
    name?: string,           // 名称
    srcAvatar?: string,      // 大图
    avatar?: string,         // 小图
    sign?: string,           // 签名
    sex?: number,            // 性别
    birthday?: number,       // 生日
    nickId?: string,
    phone?: string,   // 手机
    email?: string,   // 邮箱 
}

/**
 *设置账号设置项
 * action = 'setSetting'
 * param = setSettingParam
 * 
	*  type = 1: 设置是否显示在线信息(isonline) flag: 0显示 1不显示 默认0\n
	*  type = 3: 设置豆豆号查找(issearchbybean) flag: 0允许 1不允许 默认0\n
	*  type = 4: 设置手机号查找(issearchbyphone) flag: 0允许 1不允许 默认0\n
	*  type = 5: 设置邮箱号查找(issearchbymail) flag: 0允许 1不允许 默认0\n
	*  type = 6: 设置分享更新(isshareupdate)   flag: 0提示更新 1不提示更新 默认0\n
	*  type = 7: 新消息通知是否提醒(isnewmsgtip) flag: 0提醒 1不提醒 默认0\n
	*  type = 12: 多服务新消息通知是否提醒(ismultiservmsgtip) flag: 0不始终提示 1始终提示 默认0\n
	*  type = 13: 多服务设置V标好友始终提醒(ismultiservfrdtip) flag: 0不始终提示 1始终提示 默认0\n
	*  type = 14: 多服务设置设置@相关人始终提醒(ismultiservpersontip) flag: 0不始终提示 1始终提示 默认0
 */
interface setSettingParam {
    type: number,
    flag: number
}

/**
 *获取账号设置项
 * action = 'getSetting'
 */

/**
 *设置个人设置项
 * action = 'setPersonalData'
 * param = setPersonalDataParam
 * 
 * 	*		type: 1 (生日)，２（电话），３（邮件）\n
	* 　　　　　　value:  1：所有人可见 2：仅好友可见 3：仅自己可见，默认1\n
	*		type: 4 (好友验证方式)\n
	* 　　　　　　value:   1：需要验证信息,2:不允许任何人添加,3:允许任何人添加，默认1\n
	*		type: 5 V标\n
	*			value: 1:表示始终有声音提醒，2：表示始终无声音提醒 3:不始终提醒，默认1\n
	*		type: 6 @相关人提醒模式\n
	*			value: 1:表示始终有声音提醒，2：表示始终无声音提醒 3:不始终提醒，默认1\n
	*		type: 7 全局通知消息内容展现模式\n
	*         value: 1:通知详情，2：通知源，隐藏内容 3:完全隐藏，默认2\n
 */
interface personalData {
    type: number,
    value: number
}
type setPersonalDataParam = Array<personalData> //设置信息集合


/**
 *获取个人设置项
 * action = 'getPersonalData'
 * param = getPersonalDataParam
**/
type getPersonalDataParam = Array<number> //获取的设置信息的type集合

/**
 *增加本地配置，以键值对方式保存
 * action = 'addLocalSetting'
 * param = addLocalSettingParam
 */
interface localSetting {
    key: string,
    value: string
}
type addLocalSettingParam = Array<localSetting> //配置信息集合
/**
 *获取本地配置
 * action = 'getLocalSetting'
 * param = getLocalSettingParam
 */
type getLocalSettingParam = Array<string> //配置信息的键集合

/**
 *更新本地配置
 * action = 'updateLocalSetting'
 * param = updateLocalSettingParam
 */
type updateLocalSettingParam = Array<localSetting> //配置信息集合

/**
 *删除本地配置
 * action = 'deleteLocalSetting'
 * param = deleteLocalSettingParam
 */
type deleteLocalSettingParam = Array<string> //配置信息的键集合

/**
 *通过应用ID获取应用信息
 * action = 'getAppInfo'
 * param = getAppInfoParam
 */
interface getAppInfoParam {
    appId: number
}

/**
 *查询应用市场应用信息
 * action = 'queryMarketApplication'
 * param = queryMarketApplicationParam
 */
interface queryMarketApplicationParam {
    pageNum: number,       // 页码
    pageSize: number,     // 页长
    deviceType: number,   // 类型：1.pc 2.IOS 3.Android
    appName: string,      // 应用名称 模糊查询用.
}

/**
 *删除添加应用
 * action = 'addOrDeleteApplication'
 * param = addOrDeleteApplicationParam
 */
interface addOrDeleteApplicationParam {
    type: number,       // 操作类型
    appID: number       // 页长
}

/**
 *获取已安装的应用
 * action = 'getInstalledApplication'
 * param = getInstalledApplicationParam
 */
interface getInstalledApplicationParam {
    deviceType: number       // PC or 安卓 or IOS
}

/******************************************** enterpriseService *******************************************************/

/**
 *注册企业成员更新完成回调，收到回到代表更新完成
 * action = 'regEntUpdateFinishCb'
 */

/**
 *监听组织成员头像更新
 * action = 'regOrgMemHeadImgUpdateCb'
 */
/**
 * 获取扩展字段json
 * action = 'queryEntUserOneById'
 * param = queryEntUserOneByIdParam
 */
interface queryEntUserOneByIdParam {
    userId: number
}
/**
 *获取组织和成员
 * action = 'getVisibleOrgUsers'
 * param = getVisibleOrgUsersParam
 */
interface getVisibleOrgUsersParam {
    type: number,     // 0:获取登陆时刻的组织机构，如果登陆后对后台组织机构进行了修改，本次登陆拉取不到，下次登陆才可以拉取到
    // 1:获取当前时刻的组织机构 =1 比 =0 速度上慢了很多，建议使用 =0\n
    orgId: number      // orgID  组织ID  传 0 表示获取根组织
}

/**
 *获取企业内用户信息
 * action = 'getOrgUserInfos'
 * param = getOrgUserInfosParam
 */
interface getOrgUserInfosParam {
    userId: number
}

/**
 *获取组织信息
 * action = 'getOrgInfo'
 * param = getOrgInfoParam
 */
interface getOrgInfoParam {
    orgId: number      // orgID  组织ID  传 0 表示获取根组织
}
/******************************************** rtcService ****************************************************/

/**
 *注册音视频事件回调
 * action = 'regChannelEventCb'
 */

/**
 *邀请成员加入音视频会议
 * action = 'createChannel'
 * param = createChannelParam
 */
interface createChannelParam {
    targetId: number, ///< 目标Id 创建/邀请
    reject: boolean, ///< true  代表用于拒绝申请加入会议//保留
    videoType: number, ///< 1，语音  2，视频 3,多人UI语音 ,4多人UI视频 ,5四人广播音频  6四人广播视频
    firstSdp: string,   ///< 生成第一次sdp
    operType: number    ///< 0，普通呼叫 1，innercall 2,声网
}

/**
 *接受或拒绝音视频会议邀请
 * action = 'acceptOrReject'
 * param = acceptOrRejectParam
 */
interface acceptOrRejectParam {
    targetId: number,  ///< 目标Id
    channelId: number,  ///< 房间号 唯一
    videoType: number,  ///< 视频类型 1:音频 2:视频
    secondSdp: string, ///< 第二次sdp
    type: number      ///< 1,接受 2，拒绝,3,声网接受 4,声网拒绝
}

/**
 *关闭音视频会议
 * action = 'leaveChannel'
 */

/**
 *请求加入音视频会议
 * action = 'joinChannel'
 * param = joinChannelParam
 */
interface joinChannelParam {
    addition: string,   // 附加信息
    channelId: number   // 请求加入的房间号
}
/**
 *设置会议信息
 * action = 'setConferenceInfo'
 * param = setConferenceInfoParam
 */
interface setConferenceInfoParam {
    member: number   // 需要设置的成员
}

/**
 *音视频切换
 * action = 'switchChannel'
 * param = switchChannelParam
 */
interface switchChannelParam {
    type: number   // 操作类型
}

/**
 *获取会议信息
 * action = 'getConferenceInfo'
 */

/**
 *获取打洞服务地址
 * action = 'getStunServer'
 */

/**
 *声网相关服务接口
 * action = 'getAgoraFunc'
 * param = getAgoraFuncParam
 */
interface getAgoraFuncParam {
    channelId: number, ///< 房间号 唯一
    type: number, ///1,认证 2.呼叫 3.接听 4.重新申请subKey,5.outChat,6,updataID
    chatTime: number, /// 通话时间 type = 5时 填
    uuid: number ///声网id type = 6时 填
}

/******************************************** fileService ****************************************************/
/**
 *上传头像
 * action = 'uploadAvatar'
 * param = uploadAvatarParam
 */
interface uploadAvatarParam {
    orgiPath: string,  //大图本地路径
    thumPath: string   //缩略图本地路径
}

/**
 *上传文件
 * action = 'uploadFile'
 * param = uploadFileParam
 * process   //用于接收上传进度的回调函数
 */
interface uploadFileParam {
    message?: string,    // 附加信息由上层定义和使用
    type: number,       // 3:音频 5:图片 6:文件
    targetId: number,   // 目标ID,有可能是群或者人
    encryptKey?: string, // 加密KEY encryptKey
    isP2P?: boolean,     // 是否点对点
    localId?: number,    // 本地唯一编号
    localPath: string,  // 本地路径
    isResume?: boolean   // 是否断点上传
}

/**
 *下载文件
 * action = 'downloadFile'
 * param = downloadFileParam
 * process   //用于接收上传进度的回调函数
 */
interface downloadFileParam {
    localId: number,    // localId
    targetId: number,   // 目标ID	有可能是群或者人 targetID
    messageId: number,  // 消息的msgID
    fromId: number,     // 发送者ID fromID
    localPath: string,  // 文件本地保存路径
    remotePath: string,  // 远程路径,从消息JSON中解析出来的路径 remotePath
    isResume?: boolean   // 是否断点上传
}

/**
 *上传图片
 * action = 'uploadImage'
 * param = uploadImageParam
 * process   //用于接收上传进度的回调函数
 */
interface uploadImageParam {
    targetId: number,   // 人或群的id
    thumbPath: string,   // 传入缩略图
    srcPath: string,     // 传入原图
    encryptkey: string // 传入解密密码
}

/**
 *下载图片
 * action = 'downloadImage'
 * param = downloadImageParam
 * process   //用于接收上传进度的回调函数
 */
interface downloadImageParam {
    targetId: number,   // 人或群的id
    url: string         // 传入图片url     
}

/**
 *解密文件(此接口为同步接口)
 * action = 'decryptFile'
 * param = decryptFileParam
 */
interface decryptFileParam {
    encryptkey: string,  // 传入解密密码
    srcpath: string,     // 传入原图路径
    destpath: string     // 传入解密后图片路径     
}

/**
 *获取文件列表
 * action = 'getFileList'
 * param = getFileListParam
 */
interface getFileListParam {
    targetId: number, //群或人的id
    msgOffset: number, //偏移量
    offsetFlag: number, //偏移方向
    msgBeginId: number // 消息起始Id    
}

/**
 *通过文件消息ID得到文件详细信息
 * action = 'getFilesInfo'
 * param = getFilesInfoParam
 */
type getFilesInfoParam = Array<number>

/**
 *取消文件上传或下载
 * action = 'cancelTransfer'
 * param = cancelTransferParam
 */
interface cancelTransferParam {
    localId: number,     // 文件的localId
    type: number         //  1.上传 2.下载 3.外部下载    
}

/**
 *通过url获取名字 生成一个以年月文件夹名的前缀目录如'201704/name(此接口为同步接口)
 * action = 'getNameByUrl'
 * param = getNameByUrlParam
 */
interface getNameByUrlParam {
    url: string        // 服务器相对路径    
}
/**
 * 文件操作
 * action = 'fileOperate'
 * param = fileOperateParam
 */
interface fileOperateParam {
    filepath: string, //路径
    type: number, // 操作类型 0：判断文件或文件夹是否存在 1.创建文件夹 2.删除文件 3.重命名文件
    newName?: string, //重命名文件全路径  
}

/******************************************** searchService ****************************************************/

/**
 *从网络进行查找
 * action = 'searchFromNet'
 * param = searchFromNetParam
 */
interface searchFromNetParam {
    key: string        // 输入关键字    
}

/**
 *从本地数据库进行查找
 * action = 'searchFromLocal'
 * param = searchFromLocalParam
 */
interface searchFromLocalParam {
    key: string        // 输入关键字    
}

/**
 *全局查找消息
 * action = 'searchGlobalMessage'
 * param = searchGlobalMessageParam
 */
interface searchGlobalMessageParam {
    key: string,          // 输入关键字
    start_time: number,   // 开始时间
    end_time: number,     // 结束时间
    msgtype: number,      // 消息类型
    targetId: number,     // 目标Id
    count: number         // 消息数量 
}

/**
 *查找相应targetID的详细消息
 * action = 'searchDetailMessage'
 * param = searchDetailMessageParam
 */
interface searchDetailMessageParam {
    key: string,          // 输入关键字
    messageId: number,    // 消息Id
    start_time: number,   // 开始时间
    end_time: number,     // 结束时间
    msgtype: number,      // 消息类型
    targetId: number,     // 目标Id
    count: number         // 消息数量 
}

/**
 *通过用户ID获取详细信息
 * action = 'getUserInfo'
 * param = getUserInfoParam
 */
interface getUserInfoParam {
    userId: number   // 用户Id 
}

/******************************************** sysMsgService ****************************************************/

/**
 *设置监听离线最后一条系统消息的回调
 * action = 'regSysMsgCb'
 */

/**
 *响应加好友的请求
 * action = 'respToAddBuddy'
 * param = respToAddBuddyParam
 */
interface respToAddBuddyParam {
    userId: number,      // 请求者的用户ID
    msgId: number,       // 请求消息的msgId
    operType: number,    // 操作 1：同意，2：不同意，3：以后不允许添加，4：忽略
    remark: string,      // 好友备注
    refuseReason: string // 附带的拒绝信息 
}

/**
 *响应进群的请求
 * action = 'respToEnterGroup'
 * param = respToEnterGroupParam
 */
interface respToEnterGroupParam {
    groupId: number,     // 要进入的群ID
    msgId: number,       // 请求消息的msgId
    operType: number,    // 1：忽略 2：同意 3： 拒绝  4:拒绝并不允许再次请求; 被邀请进群时，只能同意或拒绝
    refuseReason: string // 附带的拒绝信息
}

/**
 *设置系统消息已读
 * action = 'setMessagRead'
 * param = setMessagReadParam
 */
interface setMessagReadParam {
    type: number,     // 传入操作类型1 好友请求验证框已读|2 好友请求返回框已读| 3 设置群验证请求消息已读|4 设置群验证响应消息已读
    msgIds: Array<number> // 消息Id
}

/**
 *获取系统消息消息
 * action = 'getMessages'
 * param = getSysMessagesParam
 */
interface getSysMessagesParam {
    type: number,  // 传入响应消息类型 0 全部 1 加好友请求 2 加好友响应 3 加群请求 4 加群
    count: number, // 传入数量
    time: number,  // 查找的起始时间
    flag: number   // 传入偏移标志 0 以传入的time起始，向下偏移，拉取小于time的消息 如果time = 0，代表从最新收到的系统消息开始拉取
    // 1 以传入的time起始，向上偏移，拉取大于time的消息
}

/**
 *通过类型删除系统消息
 * action = 'deleteMessageByType'
 * param = deleteMessageByTypeParam
 */
interface deleteMessageByTypeParam {
    type: number,         // 传入操作类型1 好友请求验证框已读|2 好友请求返回框已读| 3 设置群验证请求消息已读|4 设置群验证响应消息已读
    msgIds: Array<number> // 消息Id
}

/**
 * 删除全部系统消息
 * action = 'deleteAllMessage'
 * param = deleteAllMessageParam
 */

/******************************************** configService ****************************************************/

/**
 *获取开机自启动状态(此接口为同步接口)(仅PC端使用)
 * action = 'getAutoStart'
 */

/**
 * 获取服务器登录数据
 * action = 'getLoginExData'
 * param = getLoginExDataParam
 */
interface getLoginExDataParam {
    server: string      // 服务器名称 
}

/**
 *设置开机自启动(此接口为同步接口)(仅PC端使用)
 * action = 'setAutoStart'
 * param = setAutoStartParam
 */
interface setAutoStartParam {
    status: boolean      // 是否开机自启(必填) 
}

/**
 *获取登陆信息(此接口为同步接口)
 * action = 'getLoginInfos'
 */

/**
 *设置登陆信息(此接口为同步接口)
 * action = 'setLoginInfo'
 * param = setLoginInfoParam
 */
interface setLoginInfoParam {
    status: number,
    account: string, // 账号
    email: string, // 绑定的邮箱
    isAutoLogin: number, //< 自动登录
    isRemberPass: number, //< 是否记住密码
    last_login_time: string, //< 上次登陆时间
    name: string, //< 用户名
    nation: string, //< 国家码
    phone: string, //< 绑定的手机
    pwd: string,///< 密码
    server: string, ///<服务器
    userType: number, ///<用户类型
    userId: string, ///<用户id
    user_icon: string ///<头像
}

/**
 *获取该用户聊天中图片信息的保存路径(此接口为同步接口)
 * action = 'userImgPath'
 */

/**
 *获取该用户聊天中文件信息的保存路径(此接口为同步接口)
 * action = 'userFilePath'
 */

/**
 *获取头像路径(此接口为同步接口)
 * action = 'headImgPath'
 */

/**
 * 收到新消息
 * @param {string} userid - 发送方用户ID
//  */
// interface flashParam {
//     flag: boolean,
//     userid: string
// }