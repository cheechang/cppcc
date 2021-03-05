﻿#include "Error.h"
namespace utils
{
    Error::CodeMap::CodeMap()
    {
    }
	void Error::CodeMap::init(bool isChinese){
		if (isChinese) {
			m_arr[0] = "";
#ifdef _WIN32
			m_arr[-11] ="已登录此账号，不能重复登录";
#else
			m_arr[-11] = "同一个服务器只允许一个账号登录";
#endif
            m_arr[-9] = "该服务器已禁止注册新用户";
			m_arr[-5] = "请联系管理员升级服务器";
			m_arr[-4] = "该企业暂未开放注册"; //根据配置信息开启注册 
			m_arr[-3] = "该群不允许任何人加入";//邀请群成员加入群的返回
			m_arr[-2] = "您未被授权或密码错误，如需使用请联系相关管理员。";
			m_arr[-1] = "网络连接超时，请检查网络或服务器";
			m_arr[1] = "请升级客户端";
			m_arr[101] = "此用户不存在";
			m_arr[102] = "您没有权限访问";
			m_arr[103] = "验证码不符";
			m_arr[104] = "下一个校验图片";
			m_arr[112] = "账号密码不匹配";
			m_arr[113] = "账号已经登录";
			m_arr[115] = "COOKIE过期";
			m_arr[117] = "重试次数太多,需要输入验证码";
			m_arr[120] = "请获取验证码进行校验";
			m_arr[121] = "未发现绑定此手机/邮箱的账号";
			m_arr[131] = "对方设置了隐私权限不允许加关注";
			m_arr[132] = "对方设置了隐私权限不接收好友请求";
			m_arr[133] = "问题回答错误,系统否决你的申请";
			m_arr[134] = "已经是好友关系，不能重复添加";
			m_arr[135] = "已经关注该用户";
			m_arr[136] = "请求已发出,等待对方处理";
			m_arr[137] = "该群组已不存在";
			m_arr[138] = "操作的用户不存在";
			m_arr[139] = "已经申请过好友关系了";
			m_arr[141] = "已经申请过关注了";
			m_arr[142] = "添加好友成功";
			m_arr[143] = "关注成功";
			m_arr[144] = "请求已经被对方处理";
			m_arr[145] = "对方处理请求消息已被阅读";
			m_arr[146] = "拒绝你的好友请求";
			m_arr[147] = "不允许再次提交申请添加为好友";
			m_arr[148] = "关注请求已被拒绝";
			m_arr[149] = "以后不允许再申请添加为关注";
			m_arr[151] = "添加好友到数据库失败";
			m_arr[152] = "修改好友成功";
			m_arr[153] = "修改好友数据库失败";
			m_arr[154] = "删除好友成功";
			m_arr[155] = "删除好友数据失败";
			m_arr[156] = "删除聊天记录失败";
			m_arr[157] = "操作类型有误，不是添加、修改、删除这三种类型";
			m_arr[158] = "请求人ID和响应的对象不是同一人";
			m_arr[159] = "自己不能添加自己为好友";
			m_arr[160] = "忽略、忽视请求或者响应";
			m_arr[161] = "参数为空";
			m_arr[162] = "已经把此用户拉入黑名单";
			m_arr[163] = "已经被此用户拉入黑名单";
			m_arr[181] = "邮箱已经被使用";
			m_arr[182] = "该号码已被使用";
			m_arr[183] = "修改信息userBean中没有值修改";
			m_arr[184] = "修改用户信息失败";
			m_arr[185] = "修改用户联系方式/登录状态失败";
			m_arr[301] = "没有权限创建群";
			m_arr[302] = "有权限创建群";
			m_arr[303] = "该用户创建该级别的群已经超过数量限制";
			m_arr[304] = "没有权限修改群信息";
			m_arr[305] = "没有权限删除群信息";
			m_arr[306] = "该群存在";
			m_arr[307] = "该群已不存在";
			m_arr[308] = "没有权限激活该群";
			m_arr[309] = "该用户不是该群成员";
			m_arr[310] = "群成员已满";
			m_arr[311] = "群成员未满";
			m_arr[312] = "不是群主不能解散该群";
			m_arr[313] = "不是群主不能移除群成员";
			m_arr[314] = "不能移除群主";
			m_arr[315] = "超级管理员不能主动退出群，必须先转让超级管理员";
			m_arr[316] = "非管理员不能添加群成员";
			m_arr[317] = "该用户不是该群成员，不能发出邀请";
			m_arr[318] = "该群不允许普通人员邀请成员";
			m_arr[319] = "该群已经满员，不能再发邀请，请对该群进行升级";
			m_arr[320] = "不存在该邀请信息！";
			m_arr[321] = "该邀请信息已被处理！";
			m_arr[322] = "邀请人已经不在该群里面，邀请信息处理失效！";
			m_arr[323] = "该群不允许任何人添加！";
			m_arr[324] = "提示验证请求信息不存在编码！";
			m_arr[325] = "验证请求已经处理！";
			m_arr[326] = "邀请请求处理成功，请需要发送验证请求！";
			m_arr[327] = "处理人已经不在该群里面！";
			m_arr[328] = "不是群管理员，不能处理验证请求！";
			m_arr[329] = "不是管理员，不能修改其他人群名片";
			m_arr[330] = "不是群成员，不能查看其他人群名片";
			m_arr[331] = "不是群超级管理员，不能转让该群";
			m_arr[332] = "不是群成员，不能转让该群给他";
			m_arr[333] = "您已经在该群中，不能发送验证请求";
			m_arr[334] = "非临时群不允许普通用户邀请。";
			m_arr[335] = "不是群超级管理员，不能设置群管理员。";
			m_arr[336] = "应用成员信息不能修改";
			m_arr[381] = "未指定接收者";
			m_arr[382] = "未指定接收者类型";
			m_arr[383] = "验证码已过期";
			m_arr[384] = "验证码不符";
			m_arr[385] = "发送间隔时间太短";
			m_arr[386] = "发送失败";
			m_arr[387] = "未发送过验证码";
			m_arr[401] = "该推送消息截止日期需要大于当前时间";
			m_arr[402] = "您不是管理员，不能创建推送消息";
			m_arr[403] = "您不是创建者，不能修改投票状态";
			m_arr[404] = "您不是管理员，不能修改投票状态";
			m_arr[405] = "无此推送信息";
			m_arr[406] = "您不在投票人员范围内，不能投票";
			m_arr[407] = "投票已经截止，不能投票";
			m_arr[408] = "您已经投票，不能重复投票";
			m_arr[409] = "您不在投票人员范围内，不能查看投票结果";
			m_arr[410] = "不符合投票最大允许选择项设置";
			m_arr[411] = "不是投票类型的消息，不能投票";
			m_arr[412] = "投票项不允许为空";
			m_arr[413] = "该投票不允许补充";
			m_arr[414] = "您不在任务人员范围内，不能回复";
			m_arr[415] = "任务已经截止，不能回复";
			m_arr[416] = "任务已经完成/取消，不能回复";
			m_arr[417] = "您不在任务人员范围内，不能查看任务结果";
			m_arr[418] = "投票已经取消，不能投票";
			m_arr[419] = "没有推送对象成员，不能创建推送消息";
			m_arr[420] = "没有投票不能查看投票结果";
			m_arr[421] = "投票已经完成/取消,不能再投票";
			m_arr[422] = "不是任务，不能回复";
			m_arr[423] = "该投票信息不允许查看结果";
			m_arr[450] = "对方设置过滤陌生人消息";
			m_arr[451] = "对方不在线";
			m_arr[501] = "已经注册过";
			m_arr[502] = "账号有误";
			m_arr[503] = "账号已经存在";
			m_arr[504] = "已经注册成功无需验证了";
			m_arr[505] = "账号类型有误";
			m_arr[510] = "已经绑定过了";
			m_arr[512] = "已经绑定别的账号了,是否继续绑定";
			m_arr[513] = "还不曾绑定过";
			m_arr[514] = "账号不存在";
			m_arr[515] = "已经申诉了";
			m_arr[516] = "已经邀请过好友";
			m_arr[517] = "未邀请好友";
			m_arr[518] = "已经处理过";
			m_arr[519] = "申诉邀请好友辅助失败";
			m_arr[520] = "没有申诉记录";
			m_arr[521] = "还没到修改密码这一步";
			m_arr[522] = "成功凭证不正确不能设置新密码";
			m_arr[523] = "好友辅助申诉成功，请即时设置新密码无需再申诉";
			m_arr[524] = "邀请的好友已经回复了不能再回复";
			m_arr[525] = "不能邀请好友，不在邀请好友这个阶段或者没有申诉记录";
			m_arr[541] = "用户不存在";
			m_arr[542] = "新密码不合法";
			m_arr[543] = "当前密码不正确";
			m_arr[560] = "送达时间不能早于当前时间";
			m_arr[601] = "您没有创建此新鲜事";
			m_arr[602] = "您不是该新鲜事的创建者，不能删除";
			m_arr[603] = "您没有关注此人，不能获取此人的新鲜事";
			m_arr[604] = "该条新鲜事禁止评论";
			m_arr[605] = "您已经设置屏蔽此人的信息";
			m_arr[650] = "没有此备忘录信息";
			m_arr[701] = "此评论信息不存在";
			m_arr[702] = "您不是此评论信息创建人，不能删除";
			m_arr[1101] = "session丢失,请自动重连";
			m_arr[1102] = "重试次数太多,需要输入验证码";
			m_arr[1303] = "需要修改密码才能登陆";
			m_arr[1304] = "系统禁止本次登录";
            m_arr[1305]  = "账号已被冻结";
			m_arr[1308] = "账号已锁定";
			m_arr[1309] = "账号已锁定,请稍后重试";
			m_arr[11100] = "无法回避的内部错误,服务无法找到";
			m_arr[11101] = "服务器获取数据异常";
			m_arr[10001] = "获取access_token时AppSecret错误，或者access_token无效";
			m_arr[10002] = "不合法的appID";
			m_arr[10003] = "不合法的获取访问凭证类型";
			m_arr[10004] = "不合法的access_token";
			m_arr[11001] = "缺少应用标识参数";
			m_arr[11002] = "缺少应用名称参数";
			m_arr[11003] = "缺少appID参数";
			m_arr[11004] = "缺少appSecret参数";
			m_arr[11005] = "缺少access_token参数";
			m_arr[12001] = "access_token超时";
			m_arr[13001] = "需要接收者关注";
			m_arr[14001] = "POST数据包为空";
			m_arr[14002] = "用户账号参数为空";
			m_arr[14003] = "消息内容为空";
			m_arr[15001] = "应用标识超过长度限制";
			m_arr[15002] = "应用名称超过长度限制";
			m_arr[15003] = "消息内容超过长度限制";
			m_arr[16001] = "企业ID不存在";
			m_arr[16002] = "不存在的用户";
			m_arr[16003] = "企业应用不存在";
			m_arr[16004] = "用户不存在企业中";
			m_arr[20001] = "企业应用服务器未响应";
			m_arr[20002] = "企业应用服务器验证未通过";
			m_arr[30001] = "企业应用服务器响应url不存在";
			m_arr[40001] = "路由服务端异常";
			m_arr[40002] = "不允许连接到外企业";
			m_arr[40003] = "没有外部企业操作权限";
			m_arr[40004] = "外部企业操作失败";
			m_arr[40005] = "非法的参数";

			m_arr[40001001] = "群消息置顶超限";
			m_arr[40001002] = "新增失败";
			m_arr[40001003] = "新增置顶消息置顶人ID不能为空";
			m_arr[40001004] = "新增置顶消息群ID不能为空";
			m_arr[40001005] = "新增置顶消息被置顶人ID不能为空";
			m_arr[40001006] = "新增置顶消息消息体不能为空";
			m_arr[40001007] = "当前置顶人没有权限做此操作";
			m_arr[40001008] = "置顶消息已经存在";
			m_arr[40002001] = "群消息置顶撤销失败";
			m_arr[40002002] = "群消息置顶ID不能为空";
			m_arr[40002003] = "当前人员没有权限做此操作";
			//sdk自定义错误
			m_arr[err_sdk_openDbFailed] = "打开本地数据库失败";
			m_arr[err_sdk_srvUpdate] = "正在更新";
			m_arr[err_sdk_cancle] = "被取消执行";
			m_arr[err_sdk_param] = "参数错误";
			m_arr[err_sdk_rcNoexsit] = "资源不存在";
			m_arr[err_sdk_dbNoAccess] = "数据库不能访问";
			m_arr[err_sdk_dbUpdate] = "数据库正在升级";
			m_arr[err_sdk_dbupdateFail] = "数据库已更新，请重新登陆";//SDK升级失败
			m_arr[err_sdk_certInvalidate] = "证书校验失败，可能是没有设置证书";
			m_arr[err_sdk_rcOverdue] = "资源已过期";
			m_arr[err_sdk_tooOften] = "操作过于频繁";
			m_arr[err_sdk_licTypeFail] = "证书权限不够";
			m_arr[err_sdk_muchOtherEntMem] = "建立群时，邀请互联人员不能大于1";
			m_arr[err_sdk_transferGroupToOtherEnt] = "不能转让群给互联的人员";
			m_arr[err_sdk_setOtherEntMemToAdmin] = "不能设置互联人员为管理员";
			m_arr[err_setMsgreaded_invalidMsgid] = "设置已读消息号大于最大消息ID";
			m_arr[err_sdk_paramInvalidat] = "输入参数有误";
			m_arr[err_sdk_srvCertInvalidat] = "服务器证书检验失败";
			m_arr[err_sdk_mustNetLogin] = "离线登录失败,必须使用网络登录一次";
			m_arr[err_sdk_olLoginPwInvalidat] = "离线密码校验失败";
			m_arr[err_sdk_noAchieve] = "命令没有实现";
			m_arr[err_sdk_offLineLoginStatus] = "离线登录状态，不能执行网络消息";
			m_arr[err_sdk_notHasp2p] = "没有P2P模块";
			m_arr[err_sdk_notp2pUser] = "传输对象不是局域网用户，不能传输";
			m_arr[err_sdk_p2pClose] = "p2p模块关闭";
			m_arr[err_sdk_p2pNotReach] = "对方不可达";
			m_arr[err_sdk_p2pUnAcessable] = "资源无法访问";
			m_arr[err_sdk_p2pTimeOut] = "传输任务超时";
			m_arr[err_sdk_uploadErr] = "文件上传失败";
			m_arr[err_sdk_forceUp] = "需要强制升级";
			m_arr[err_sdk_erroCmd] = "消息错误";
            m_arr[err_sdk_getHostFailed] = "解析域名失败";
		}
		else {
			//不是中文系统
			m_arr[0] = "";
#ifdef _WIN32
			m_arr[-11] = "This account has been logged and cannot be repeated.";
#else
			m_arr[-11] = "You can only log into one account on the same server.";
#endif
			m_arr[-5] = " Please contact administrator to update server";
			m_arr[-4] = "This company's registration is not public";//Enable registration according to configuration information
			m_arr[-3] = "This group doesn't allow anyone to add";//Invite members to join group
			m_arr[-2] = "Not authorized or password is wrong, please contact administrator if you need.";
			m_arr[-1] = "Network connection timeout, please check the network or server";
			m_arr[1] = "Update client";
			m_arr[101] = "This user does not exist";
			m_arr[102] = "You don't have permission to access";
			m_arr[103] = "Verification code does not match";
			m_arr[104] = "Next verification image";
			m_arr[112] = "Invalid Account or Password";
			m_arr[113] = "Your account has logged in";
			m_arr[117] = "Retry too many times, you need to enter verification code";
			m_arr[120] = "The account doesn't exist, please re-verify";
			m_arr[121] = "No account has been found linked this phone/email";
			m_arr[131] = "Unable to follow the user due to his/her privacy permissions";
			m_arr[132] = "Unable to add the user as a friend due to his/her privacy permissions";
			m_arr[133] = "Wrong answer,the system rejected your request";
			m_arr[134] = "Added, cannot re-add";
			m_arr[135] = "Followed this user";
			m_arr[136] = "Request has been sent, waiting for process";
			m_arr[137] = "The group does not exist";
			m_arr[138] = "User does not exist";
			m_arr[139] = "Already sent friend request";
			m_arr[141] = "Already sent follow request";
			m_arr[142] = "Successfully added friend";
			m_arr[143] = "Followed successfully";
			m_arr[144] = "Request has been processed by the user";
			m_arr[145] = "The message that the user processed the request has been read";
			m_arr[146] = "Refuse your friend request";
			m_arr[147] = "Not allowing re-send friends adding request";
			m_arr[148] = "Follow request has been refused";
			m_arr[149] = "Not allowing re-applied follow adding";
			m_arr[151] = "Failed to add friends into database";
			m_arr[152] = "Successfully changed";
			m_arr[153] = "Failed to modify friends database";
			m_arr[154] = "Successfully deleted friends";
			m_arr[155] = "Failed to delete friends data ";
			m_arr[156] = "Failed to delete chat history";
			m_arr[157] = "Wrong operation, not add/change/delete";
			m_arr[158] = "Requester ID is not the person who responds";
			m_arr[159] = "cannot add yourself as a friend";
			m_arr[160] = "Ignore request or response";
			m_arr[161] = "Parameter is empty";
			m_arr[163] = "You have been blocked.";
			m_arr[181] = "Email address has been used";
			m_arr[182] = "The number has been used";
			m_arr[183] = "There's no value change in userBean's change message";
			m_arr[184] = "Failed to change user info";
			m_arr[185] = "Failed to change user's contact information/login status";
			m_arr[301] = "No permissions to create groups";
			m_arr[302] = "Has permissions to create groups";
			m_arr[303] = "The user to create that level of group is beyond limit";
			m_arr[304] = "No permissions to change group messages";
			m_arr[305] = "No permissions to delete group messages";
			m_arr[306] = "The group exists";
			m_arr[307] = "The group does not exist";
			m_arr[308] = "No permissions to activate the group";
			m_arr[309] = "The user is not in this group";
			m_arr[310] = "Members are full";
			m_arr[311] = "Members not full ";
			m_arr[312] = "Can't dissolve group as you're not the group creator";
			m_arr[313] = "Can't remove members as you're not the group creator";
			m_arr[314] = "Can't remove group creator";
			m_arr[315] = "The super administrator should transfer this title to others before quitting group";
			m_arr[316] = "Cannot add group members except you're the administrator";
			m_arr[317] = "The user cannot send invitation as he is not a member of this group";
			m_arr[318] = "The group does not allow ordinary member to invite members";
			m_arr[319] = "The group is full of members and cannot invite people, please upgrade the group";
			m_arr[320] = "The invitation message does not exist";
			m_arr[321] = "The invitation message has been processed";
			m_arr[322] = "The inviter isn't in this group, the invitation message is invaild ";
			m_arr[323] = "This group doesn't allow anyone to add";
			m_arr[324] = "Note: Verification request not allow coding";
			m_arr[325] = "Verification request has been processed";
			m_arr[326] = "Successfully processed invitation request, please send verification request";
			m_arr[327] = "The processed people is not in this group";
			m_arr[328] = "Unable to process verification request as you are not administrator";
			m_arr[329] = "Unable to change members' name card as you are not administrator";
			m_arr[330] = "Unable to view members' name card as you are not a group member";
			m_arr[331] = "Unable to transfer the group as you are not super administrator";
			m_arr[332] = "Unable to transfer the group to him/her as he/ she is not a group member";
			m_arr[333] = "Unable to send verification request as you are in this group";
			m_arr[334] = "Not allowed common users to invite as an non temporary group";
			m_arr[335] = "Unable to set group administrator as you are not super administrator";
			m_arr[336] = "Cannot change members profile ";
			m_arr[381] = "Unspecified receiver";
			m_arr[382] = "Unspecified receiver type";
			m_arr[383] = "Expired verification code ";
			m_arr[384] = "Verification code does not match";
			m_arr[385] = "Sending interval is too short";
			m_arr[386] = "Failed to send";
			m_arr[387] = "Never sent verification code";
			m_arr[401] = "The push message deadline should be later than now";
			m_arr[402] = "Unable to create push message as you are not administrator";
			m_arr[403] = "Unable to change vote status as you are not creator";
			m_arr[404] = "Unable to change vote status as you are not administrator";
			m_arr[405] = "No such push message";
			m_arr[406] = "Unable to vote as you are not a voter";
			m_arr[407] = "Unable to vote as vote has ended";
			m_arr[408] = "Unable to re-vote as you voted";
			m_arr[409] = "Unable to view vote result as you are not a voter";
			m_arr[410] = "Not matched the vote max options settings ";
			m_arr[411] = "Unable to vote as not vote type messgae";
			m_arr[412] = "Vote item is required";
			m_arr[413] = "The vote is not allowed to add";
			m_arr[414] = "Unable to reply as you are not a task member";
			m_arr[415] = "Unable to reply as task has ended";
			m_arr[416] = "Unable to reply as task has finished/canceled";
			m_arr[417] = "Unable to view task result as you are not a task member";
			m_arr[418] = "Unable to vote as vote has canceled";
			m_arr[419] = "Unable to create push message as with no objects";
			m_arr[420] = "Unable to view vote result as you didn't vote";
			m_arr[421] = "Unable to vote as the vote has finished/canceled";
			m_arr[422] = "Unable to reply as it is not a task";
			m_arr[423] = "The vote is not allowed to view result";
			m_arr[450] = "The user has set filtering stranger's message";
			m_arr[451] = "The user is offline";
			m_arr[501] = "Your number has been registered";
			m_arr[502] = "Account error";
			m_arr[503] = "Account exists";
			m_arr[504] = "Registered successfully, no need to verify";
			m_arr[505] = "Account type is incorrect";
			m_arr[510] = "Linked";
			m_arr[512] = "Linked other account, are you sure to link?";
			m_arr[513] = "Never linked";
			m_arr[514] = "Account does not exist";
			m_arr[515] = "Appealed";
			m_arr[516] = "Invited friends already";
			m_arr[517] = "Haven't invited friends";
			m_arr[518] = "Processed already";
			m_arr[519] = "Inviting friends assist appeal failed ";
			m_arr[520] = "No appeal record";
			m_arr[521] = "Not in the step of changing password ";
			m_arr[522] = "Unable to set new password as success proof is incorrect";
			m_arr[523] = "Friends assist appeal succeeded, please set new password immediately";
			m_arr[524] = "The invited friends have replied, cannot re-reply";
			m_arr[525] = "Unable to invite friends as you are not in this step or with no appeal record";
			m_arr[541] = "User does not exist";
			m_arr[542] = "Illegal new password";
			m_arr[543] = "Wrong old password";
			m_arr[601] = "You haven't post this sharing";
			m_arr[602] = "Unable to delete as you are not the creator of this sharing";
			m_arr[603] = "Unable to get his/her sharings as you haven't followed he/she";
			m_arr[604] = "Comment is forbidden for this sharing";
			m_arr[605] = "You have set to block this person's message";
			m_arr[650] = "No such memo";
			m_arr[701] = "The comment does not exist";
			m_arr[702] = "Unable to delete as you are not the creator of this comment";
			m_arr[1101] = "session lost, please reconnect automatically";
			m_arr[1102] = "Too many attempts, you need to enter verification code";
			m_arr[1304] = "The system forbid log in";
            m_arr[1305] = "Account has been frozen";
			m_arr[1309] = "Account locked. Please try later";
			m_arr[11100] = "Internal error, service can not be found";
			m_arr[11101] = "Server exception when getting data";
			m_arr[10001] = "AppSecret error when getting access_token or access_token is invalid ";
			m_arr[10002] = "Illegal appID";
			m_arr[10003] = "Illegal type of getting access proof";
			m_arr[10004] = "Illegal access_token";
			m_arr[11001] = "Lack application identification parameter ";
			m_arr[11002] = "Lack application name parameter";
			m_arr[11003] = "Lack appID parameter";
			m_arr[11004] = "Lack appSecret parameter";
			m_arr[11005] = "Lack access_token parameter";
			m_arr[12001] = "access_token timeout";
			m_arr[13001] = "Need receiver's follow";
			m_arr[14001] = "POST data is null";
			m_arr[14002] = "Account parameter is null";
			m_arr[14003] = "Message is null";
			m_arr[15001] = "App ID exceeds length limits";
			m_arr[15002] = "App Name exceeds length limits ";
			m_arr[15003] = "Message exceeds length limits";
			m_arr[16001] = "Company ID does not exist";
			m_arr[16002] = "Non-existent user";
			m_arr[16003] = "Company application does not exist";
			m_arr[16004] = "The user is not in the company";
			m_arr[20001] = "Company application server does not respond";
			m_arr[20002] = "Verification failed of company application server ";
			m_arr[30001] = "Response url of company application server does not exist";
			m_arr[40001] = "Routing service side error";
			m_arr[40002] = "You cannot connect external enterprises.";
			m_arr[40003] = "You have no access to external enterprises.";
			m_arr[40004] = "Operation failed.";
			m_arr[40005] = "Invalid parameter";
			//sdk自定义错误
			m_arr[err_sdk_openDbFailed] = "Failed to open local database";
			m_arr[err_sdk_srvUpdate] = "Updating";
			m_arr[err_sdk_cancle] = "Execution being canceled";
			m_arr[err_sdk_param] = "Parameter error";
			m_arr[err_sdk_rcNoexsit] = "Resource does not exist";
			m_arr[err_sdk_dbNoAccess] = "Unable to access database";
			m_arr[err_sdk_dbUpdate] = "Updating database";
			m_arr[err_sdk_dbupdateFail] = "SDK Update Failed";
			m_arr[err_sdk_certInvalidate] = "Failed to verify certificate, certificate might not have been set yet";
			m_arr[err_sdk_rcOverdue] = "Resource expired";
			m_arr[err_sdk_tooOften] = "Too frequent operation";
			m_arr[err_sdk_licTypeFail] = "Limited certificate authority";
			m_arr[err_sdk_muchOtherEntMem] = "You can only invite one member from associated enterprise(associate) at a time when creating a group";
			m_arr[err_sdk_transferGroupToOtherEnt] = "Group cannot be transferred to associates.";
			m_arr[err_sdk_setOtherEntMemToAdmin] = " Associates cannot be set as administrator.";
			m_arr[err_setMsgreaded_invalidMsgid] = "Invalid message ID: message ID length has exceeded limit";

			m_arr[err_sdk_paramInvalidat] = "Input parameter error";
			m_arr[err_sdk_srvCertInvalidat] = "Failed to verify server certificate";
			m_arr[err_sdk_mustNetLogin] = "Failed to log in offline. You have to try again online";
			m_arr[err_sdk_olLoginPwInvalidat] = "Failed to check offline password";
			m_arr[err_sdk_noAchieve] = "Command unimplemented";
			m_arr[err_sdk_offLineLoginStatus] = "Offline login. Network informtation unavailable.";
			m_arr[err_sdk_notHasp2p] = "No P2P module";
			m_arr[err_sdk_notp2pUser] = "User is not connected to LAN, cannot be transfered";
			m_arr[err_sdk_p2pClose] = "P2P module closed";
			m_arr[err_sdk_p2pNotReach] = "P2P module closed";
			m_arr[err_sdk_p2pUnAcessable] = "Resource unavailable";
            m_arr[err_sdk_getHostFailed] = "Resolved domain name failed";
		}
	}
    const char* Error::CodeMap::info(int code) const
    {
        std::map<int, const char*>::const_iterator it = m_arr.find(code);
		if (it == m_arr.end()) return (m_isChinese ? ("未知错误") : ("unknow error"));
        else return it->second;
    }
	bool Error::m_isChinese=true;
}
