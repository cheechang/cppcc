
#pragma once

#include "../model/SDKTypes.h"
//#include "../model/Packet.h"
#include "IService.h"
#include "../extModel/gapacket.h"

#include <string>
#include <vector>

#define VER_IGA INTERFACE_VERSION(1,0)
static const VRVIID IID_IGaService = { 0x581a32a, 0xe8fb, 0x4ea2, 0x9c, 0xae, 0x86, 0x16, 0x9e, 0x33, 0x51, 0x77 };

namespace service
{

class IGaService : public IService
{
public:
	
    virtual ~IGaService() {}

	/*****************************************注册通知回调*******************************************/

	/**
	 *\brief 公安推送接口
	 * @param[out] cb _1 查看结构体定义
	 */
    virtual void regGaPushMessageCb(SFunction< void(pushMessage &)> cb) = 0;

	/*****************************************请求接口*******************************************/

	// 核查

	/**
	 * @brief 发布核查
	 * @param[in] invest 核查结构体
	 * @param[out] cb  传入接收结果回调 _1 错误号; _2 核查ID
	 */
    virtual void promoteInvest(gaInvestTaskBean & invest, SFunction<void(ErrorInfo, int64)> cb) = 0;

    /**
     * @brief 回复核查
     * @param[in] investRep 核查回复结构体
     * @param[out] cb  传入接收结果回调 _1 错误号; _2
     */
    virtual void replyinvest(gaInvestReplyBean & investRep, SFunction<void(ErrorInfo, int64)> cb) = 0;

    /**
     * @brief 获取核查任务数
     * @param[in] type = 1 获取未回复的协查任务数; type = 2 获取未回复的协查结果数
     * @param[out] cb  传入接收结果回调 _1 错误号; _2 数量
     */
    virtual void getinvestcount(int32 type, int64 userid, SFunction<void(ErrorInfo, int64)> cb) = 0;
    
    /**
     * @brief 评价回复内容
     * @param[in] comm 评价回复内容结构体
     * @param[lout] cb  传入接收结果回调 _1 错误号
     */
    virtual void commentreplycontent(gaCommentBean & comm, SFunction<void(ErrorInfo)> cb) = 0;

    /**
     * @brief 查询核查任务列表
     * @param[in] invest
     * @param[out] cb  传入接收结果回调 _1 错误号 _2 数量
     */
    virtual void getinvesttasklist(investtasklist & invest, SFunction<void(ErrorInfo, int64, investPageBean &)> cb) = 0;

    /**
     * @brief 查询核查详情
     * @param[in] type = 1 发起人，返回协查结果包含回复列表和协查详情 type = 2 协查人,只返回该协查详情
     * @param[in] userid 查询人
     * @param[out] cb  传入接收结果回调 _1 错误号
     */
    virtual void getinvestdetail(int8 type, int64 investid, int64 userid, SFunction<void(ErrorInfo, gaInvestTaskBean &)> cb) = 0;

    /**
     * @brief 查询核查回复详情
     * @param[in] replyid  回复id
     * @param[out] cb  传入接收结果回调 _1 错误号
     */
    virtual void getinvestreplydetail(int64 replyid, int64 userid, SFunction<void(ErrorInfo, gaInvestReplyBean &)> cb) = 0;

    /**
     * @brief 查询核查回复详情
     * @param[in] type1=1：协查人获取协查的回复列表（查的是协查人自己的回复列表） type=2：发起人获取协查的回复列表（查的是该协查的所有回复）
     * @param[in] investid  核查任务id
     * @param[out] cb  传入接收结果回调 _1 错误号
     */
    virtual void getreplylist(int32 type, int32 investid, int64 userid, SFunction<void(ErrorInfo, std::vector<gaInvestReplyBean>&)> cb) = 0;

    /**
     * @brief 获取指定核查
     * @param[in] type：1:核查任务 2:核查结果
     * @param[in] investigationType  核查类型 4.涉恐 3.涉案 2.未知 1.普通
     * @param[in] pageno 页码
     * @param[in] pagesize 每页条数
     * @param[out] cb  传入接收结果回调 _1 错误号
     */
    virtual void getappointinvest(int8 type, int32 investigationType, int32 pageno, int32 pagesize, SFunction<void(ErrorInfo, investPageBean &)> cb) = 0;

    /**
     * @brief 根据是否回复获取核查
     * @param[in] type：1:核查任务 2:核查结果
     * @param[in] investigationType 1.未处理   2.已处理
     * @param[in] pageno 页码
     * @param[in] pagesize 每页条数
     * @param[out] cb  传入接收结果回调 _1 错误号
     */
    virtual void getreplytypeinvest(int8 type, int32 investigationType, int32 pageno, int32 pagesize, SFunction<void(ErrorInfo, investPageBean &)> cb) = 0;
    
    /**
     * @brief 根据身份证号查询核查信息
     * @param[in] str 身份证号码
     * @param[out] cb  传入接收结果回调 _1 错误号
     */
    virtual void getinvestwithidentify(std::string & str, SFunction<void(ErrorInfo, investPageBean &)> cb) = 0;

    /**
     * @brief 是否存在该身份证号的核查信息
     * @param[in] str 身份证号码
     * @param[out] cb  传入接收结果回调 _1 错误号
     */
    virtual void isexistinvestrecord(std::string & str, SFunction<void(ErrorInfo, bool)> cb) = 0;

    /**
     * @brief 根据身份证号分页查询协查信息
     * @param[in] pageno 页码
     * @param[in] pagesize 每页条数
     * @param[in] str 身份证号码
     * @param[out] cb  传入接收结果回调 _1 错误号
     */
    virtual void searchinvestigationlist(int32 pageno, int32 pagesize, std::string & str, SFunction<void(ErrorInfo, investPageBean &)> cb) = 0;

    /**
     * @brief 关注
     * @param[in] type 类型
     * 0 设置关键字，用户设置关注时用， 需要keywordList(关键字列表), code : 0 成功
     * 1 获取自己的关键字列表, 自己设置的关注的关键字列表, 返回 listStr(如果不为空的话)
     * 2 是否有新关注, value64代表数量
     * 3 拉取新关注列表, gaqp 查询参数, 返回 gap
     * 6 查询核查历史（分页）
     * @param[out] cb  传入接收结果回调 _1 错误号
     */
    virtual void qInvestS(int8 type, int64 userid, std::vector<std::string> & keywordList, attentionQueryParam & atten, SFunction<void(ErrorInfo, int8, int64, std::vector<std::string>&)> cb) = 0;

    // 通报

    /**
     * @brief 发通报
     * @param[out] cb  传入接收结果回调 _1 错误号
     */
    virtual void promotereport(gaReportBean & report, SFunction<void(ErrorInfo, int64)> cb) = 0;

    /**
     * @brief 根据id获取通报详情
     * @param[out] cb  传入接收结果回调 _1 错误号
     */
    virtual void getreportbyid(int64 reportid, SFunction<void(ErrorInfo, gaReportBean &)> cb) = 0;

    /**
     * @brief 获取通报列表
     * @param[out] cb  传入接收结果回调 _1 错误号
     */
    virtual void getreportlist(gaReportQueryParamBean & para, SFunction<void(ErrorInfo, gaReportPageBean &)> cb) = 0;

    /**
     * @brief 获取指定通报
     * @param[in] reportType  通报类型 1:追逃通报 2 : 核查通报 3 : 情况通报 4 : 通知通报
     * @param[in] pageno 页码
     * @param[in] pagesize 每页条数
     * @param[out] cb  传入接收结果回调 _1 错误号
     */
    virtual void getappointreport(int8 reportType, int32 pageno, int32 pagesize, SFunction<void(ErrorInfo, gaReportPageBean &)> cb) = 0;
    
    /**
     * @brief 获取未读数量
     * @param[in] type  1:核查 2:通报
     * @param[out] cb  传入接收结果回调 _1 错误号
     */
    virtual void getUnreadCounts(int8 type, SFunction<void(ErrorInfo, int32)> cb) = 0;

    /**
     * @brief 获取未读数量
     * @param[in] type  1:核查 2:通报
     * @param[in] id   核查或者通报的ID
     * @param[out] cb  传入接收结果回调 _1 错误号
     */
    virtual void setRead(int8 type, int64 id, SFunction<void(ErrorInfo)> cb) = 0;

    /**
     * @brief 按名称搜索组织
     * @param[in] type  类型 0：所有 1：组织架构 2：人员
     * @param[in] area   地区项 0：全国 1：新疆
     * @param[in] condition  条件
     * @param[out] cb  传入接收结果回调 _1 错误号
     */
    virtual void search(int8 type, int32 area, std::string &condition, SFunction<void(ErrorInfo, std::vector<gaEntpriseUserInfo>&, std::vector<gaOrganizationInfo>&)> cb) = 0;
};

} /*namespace service*/
