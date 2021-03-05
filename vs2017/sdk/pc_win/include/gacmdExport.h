/*
 * gacmdExport.h
 *
 *  Created on: 2015年11月16日
 *      Author: corning
 */

#ifndef GACMDEXPORT_H_
#define GACMDEXPORT_H_

#include <string>
#include <vector>
#include <map>
#include <config.h>
#include <cmdExport.h>

using namespace imsdk;

/**
 * 消息枚举类型
 * sdk开发人员加入新的数据结构后，需要同时更新cmdMemger类里面的实现
 */
namespace imsdkga{

	/**
	 * 导出业务类消息号，各个平台的ＡＰＩ层要统一
	 * ** [in] 标识输入参数
	 * ** [out] 标识返回参数
	 * ** 只有[out]没有[in] 标识该消息ＳＤＫ纯推送，只有reponse没有request
	 */
	enum {

	  /// [in] req_promoteinvest 	[out] resp_promoteinvest
	  ga_logic_cmd_promoteinvest = 10000,                          /// 发布协查任务

	  /// [in] req_replyinvest   [out] resp_commonResult
	  ga_logic_cmd_replyinvest = 10001,                            /// 回复协查任务

	  /// [in] req_getinvestcount 	[out] resp_getinvestcount
	  ga_logic_cmd_getinvestcount = 10002,                         /// 获取协查任务数

	  /// [in] req_commentreply 	[out] resp_commonResult
	  ga_logic_cmd_commentreplycontent = 10003,                    /// 评价回复内容

	  /// [in] req_getinvesttasklist 	[out] resp_investbeaninfo
	  ga_logic_cmd_getinvesttasklist = 10004,	                   /// 查询协查任务列表(返回基本信息，DB中获取)

	  /// [in] req_getinvestdetail   [out] resp_investbeaninfo
	  ga_logic_cmd_getinvestdetail = 10005,                        /// 查询协查详情(返回所有信息，服务器中获取)

	  /// [in] req_getinvestreplydetail 	[out]resp_investbeaninfo
	  ga_logic_cmd_getinvestreplydetail = 10006,                   /// 查询协查回复详情

	  /// [in] req_getreplylist  	[out]resp_investbeaninfo
	  ga_logic_cmd_getreplylist = 10007,                           /// 查询回复列表

	  /// [in] null 	[out] resp_investbeaninfo
	  ga_logic_cmd_getallcomment = 10008,                          /// 查询所有评论选项（没用）

	  /// [in] req_commonUserid	 	[out] resp_investbeaninfo
	  ga_logic_cmd_getstatistics = 10009,                          /// 查询统计信息（没用）

	  /// [in] req_getinvestwithidentify 	[out] resp_investbeaninfo
	  ga_logic_cmd_getinvestwithidentify = 10010,                  /// 根据身份证号查询协查信息

	  /// [in] req_isexistinvestrecord 	[out] resp_isexistinvestrecord
	  ga_logic_cmd_isexistinvestrecord = 10011,                    /// 是否存在该身份证号的协查信息

	  /// [in] req_countinvest  	[out] resp_countinvest
	  ga_logic_cmd_countinvest = 10012,	                           /// 协查信息统计（没用）


	  /// [in] req_promotereport  	[out] resp_promotereport
	  ga_logic_cmd_promotereport = 10013,                          /// 发布通报

	  /// [in] req_getreportbyid  	[out] resp_getreportbyid
	  ga_logic_cmd_getreportbyid = 10014,	                       /// 根据id获取通报详情

	  /// [in] req_getreportlist  	[out] resp_getreportlist
	  ga_logic_cmd_getreportlist = 10015,                          /// 获取通报列表


	  /// [in] req_commonUserid 	[out]resp_commonResult
	  ga_logic_cmd_getcachedata = 10016,                           /// 更新缓存数据（包括协查和通报）（没用）

	  
      /// [in] req_querytotalcount		[out]resp_commonResult
      ga_logic_cmd_querytotalcount = 10017,                        /// 获取协查总条数，在推送里用(没用)

      /// [in] req_suggestsearch		[out]resp_suggestsearch
      ga_logic_cmd_suggestsearch = 10018,                          /// （没用）

      /// [in] req_searchinvestigationlist		[out]resp_searchinvestigationlist
      ga_logic_cmd_searchinvestigationlist = 10019,                /// 根据身份证号分页查询协查信息

      /// [in] req_search		[out]resp_search
      ga_logic_cmd_search = 10020,                                 /// 组织机构中的搜索

      /// [in] req_investParam		[out]resp_investRet
	  ga_logic_cmd_qInvestS = 10021,                               /// 关注

	  /// [in] req_enUQSParam	[out]resp_enUQRet
	  ga_logic_cmd_qEnUQS = 10022,                                 /// 公安注册(没用)


      /// [in] req_getappointreport	[out]resp_getappointreport
      ga_logic_cmd_getappointreport = 10023,                       /// 获取指定的通报


      /// [in] req_setread	[out]resp_commonResult
      ga_logic_cmd_setRead = 10024,                                /// 设置已读

      /// [in] req_getunreadCounts	[out]resp_commonResult
      ga_logic_cmd_getUnreadCounts = 10025,                        /// 获取未读数量

      /// [in] req_getappointinvest	[out]resp_getappointinvest
      ga_logic_cmd_getappointinvest = 10026,                       /// 获取指定的核查

      /// [in] req_getreplytypeinvest	[out]resp_getreplytypeinvest
      ga_logic_cmd_getreplytypeinvest = 10027,                     /// 根据是否回复获取核查


	  ga_logic_cmd_max,	                                           /// 最大的命令标识，标识命令个数，无特殊业务意义
	};

    /// =========================================================================================

	/// 用户信息
	struct st_gaUserBean{
        st_gaUserBean() : 
            userid(0), 
            orgid(0), 
            proviceid(0), 
            areaid(0), 
            cityid(0),
            regType(0),
            policeType(0) {}

		int64		userid;      ///< 用户id
		int64		orgid;       ///< 组织id
		int64		proviceid;   ///< 省份id
		int64		areaid;      ///< 区域id
		int64		cityid;      ///< 市id
        int32       policeType;  ///< 警种
        int32       regType;     ///< 核查的权限
		std::string name;        ///< 用户名
		std::string orgname;     ///< 组织名
		std::string orgfullname; ///< 组织全称
		std::string provicename; ///< 省份名
		std::string areaname;    ///< 区域名
		std::string cityname;    ///< 市名
        std::string userHead;    ///< 头像
	};

	/// 协查附件信息
	struct st_gaFileBean {
        st_gaFileBean() : 
            filesize(0), 
            replyid(0), 
            investid(0) {}

		int64       filesize;   ///< 文件大小
		int64		replyid;    ///< 回复id
		int64	    investid;   ///< 协查任务id
		std::string filename;   ///< 文件名
		std::string filepath;   ///< 文件路径
	};

	struct st_gaInvestReplyBean;

	/// 协查任务信息
	struct st_gaInvestTaskBean{
        st_gaInvestTaskBean() :
            status(1),
            replystatus(1),
            replycount(0),
            notreplycount(0),
            commentcount(0),
            investid(0),
            promotetime(0),
            updatetime(0),
            invalidtime(0), 
            remaintime(0), 
            earlyreplytime(0),
            isRead(0),
            investigationType(2) {
                investuserlist.clear();
                filelist.clear();
                replylist.clear();
            }

		int32		status;			 ///< 状态 1.正常 2.已过期
		int32       replystatus;	 ///< 回复状态 1：未回复，2：已按时回复，3：未按时回复
		int32		replycount;		 ///< 回复数
		int32		notreplycount;   ///< 未回复数
		int32		commentcount;	 ///< 评价数
		int64	    investid;		 ///< 协查任务id
		int64		promotetime;	 ///< 发起时间
		int64		updatetime;		 ///< 更新时间
		int64		invalidtime;	 ///< 截至时间
		int64		remaintime;		 ///< 剩余时间,0的时候表示已经过期的时间
		int64		earlyreplytime;  ///< 早期回复时间
		std::string title;			 ///< 标题
		std::string content;		                ///< 内容
		std::vector<st_gaUserBean> investuserlist;  ///< 协查人列表(现在只支持1个协查人)
		std::vector<st_gaFileBean> filelist;	    ///< 附件列表
		std::vector<st_gaInvestReplyBean>replylist; ///< 回复列表
		st_gaUserBean			   promotor;	    ///< 发起人信息
        std::string auditIDcard;                    ///< 核查人身份证号码
        std::string sex;                            ///< 性别
        std::string investigated;                   ///< 检查人
        std::string nation;                         ///< 民族
        std::string phone;                          ///< 手机号
        std::string address;                        ///< 家庭住址
        std::string homePhone;                      ///< 住址电话
        std::string workUnit;                       ///< 工作单位
        std::string occupation;                     ///< 职业
        std::string guardian;                       ///< 监护人
        std::string guardianPhone;                  ///< 监护人电话
        int8 isRead;                                ///< 0:未读  1:已读
        int32 investigationType;                    ///< 核查类型 4.涉恐 3.涉案 2.未知 1.普通
	};

	/// 评论项信息
	struct st_gaCommentItemBean{
        st_gaCommentItemBean() :
            itemkey(0) {}

		int32			itemkey;		///< 键
		std::string 	itemValue;		///< 值
	};

	/// 评价信息结构体
	struct st_gaCommentBean{
        st_gaCommentBean() :
            commentid(0), 
            commentuserid(0), 
            investid(0), 
            replyid(0), 
            commenttime(0) {}

		int64		commentid;			///< 评论id
		int64		commentuserid;		///< 评论者id
		int64		investid;			///< 协查id
		int64		replyid;			///< 回复id
		int64		commenttime;		///< 评论时间
		std::string	commentdesc;		///< 评价说明
		st_gaUserBean replier;		    ///< 回复人信息
		st_gaCommentItemBean result;    ///< 评价结果
	};

	/// 协查任务回复信息
	struct st_gaInvestReplyBean{
        st_gaInvestReplyBean() :
            replytime(0), 
            replyid(0), 
            investid(0),
            investigationType(2) {
                filelist.clear();
                commentlist.clear();
            }

		int64 replytime;			                ///< 回复时间
		int64 replyid;				                ///< 回复者id
		int64 investid;				                ///< 协查任务id
		std::string content;		                ///< 内容
		st_gaUserBean promotor;		                ///< 回复To的人
		st_gaUserBean replier;		                ///< 回复者信息
		std::vector<st_gaFileBean>filelist;         ///< 回复的附件列表
		std::vector<st_gaCommentBean>commentlist;   ///< 评价列表
        int32 investigationType;                    ///< 核查类型 4.涉恐 3.涉案 2.未知 1.普通
	};

	/// 协查任务查询参数
	struct st_gaInvestQueryParam{
        st_gaInvestQueryParam() :
            replystatus(0), 
            commentstatus(0), 
            pageno(0), 
            pagesize(0), 
            begintime(0), 
            endtime(0), 
            investid(0), 
            promoterareaid(0) {}

		int32  replystatus;
		int32  commentstatus;       ///< 状态
		int32  pageno;		        ///< 页码
		int32  pagesize;	        ///< 每页的条数
		int64  begintime;	        ///< 开始时间
		int64  endtime;		        ///< 结束时间
		int64  investid;	        ///< 协查id
		int64  promoterareaid;      ///< 发起人区域id
		std::string title;	        ///< 标题
		std::string identifyid;     ///< 身份证号
		st_gaUserBean promotor;     ///< 发起者信息
		st_gaUserBean receiver;     ///< 接收者信息
	};

	/// 协查统计信息结构体
	struct st_gaInvestStatisticBean {
        st_gaInvestStatisticBean() :
            totalcount(0) {
                commnetcountlist.clear();
            }

		int64  totalcount;								///< 总数
		std::map<int64, int64> commnetcountlist;		///< 评论数统计
	};

	/// 协查分页信息
	struct st_gaInvestPageBean {
        st_gaInvestPageBean() :
            pageno(0), 
            pagesize(0), 
            totalpage(0), 
            totalcount(0) {
                tasklist.clear();
            }

		int32		pageno;		                        ///< 页码
		int32		pagesize;	                        ///< 每页条数
		int64		totalpage;	                        ///< 总页数
		int64		totalcount;                         ///< 总条数
		std::vector<st_gaInvestTaskBean> tasklist;      ///< 协查任务列表
	};

	/// 协查信息返回通用结构体
	struct st_gaInvestInfoBean {
        st_gaInvestInfoBean() :
            counts(0) {
                replybeanlist.clear();
                commtlist.clear();
            };

		int64 counts;
		st_gaInvestTaskBean			investtask;	        ///< 协查任务信息
		st_gaInvestStatisticBean	statistic;	        ///< 统计信息
		st_gaInvestPageBean			pagebean;	        ///< 协查任务分页列表
		st_gaInvestReplyBean		replybean;	        ///< 协查回复信息
		std::vector<st_gaInvestReplyBean> replybeanlist;///<
		std::vector<st_gaCommentItemBean> commtlist;    ///<
	};

	/// 通报数据信息
	struct st_gaReportBean {
        st_gaReportBean() :
            status(2), 
            reportid(0), 
            promotetime(0), 
            updatetime(0),
            auditTimeStamp(0),
            isRead(0),
            reportType(0) {
                allOrgIDList.clear();
                allClassIDList.clear();
            }

		int8		  status;		        ///< 状态值 1：未审核 2：已通过审核 3：未通过审核
		int64		  reportid;		        ///< 通报ID	
		int64		  promotetime;	        ///< 发起时间
		int64		  updatetime;	        ///< 修改时间
		std::string   title;		        ///< 通报标题
		std::string   content;		        ///< 通报内容
		st_gaUserBean promotor;		        ///< 发起人信息
        int64         auditTimeStamp;       ///< 审核时间戳
        int8          reportType;           ///< 通报类型 1:追逃通报 2 : 协查通报 3 : 情况通报 4 : 通知通报
        std::vector<int64> allOrgIDList;    ///< 多选组织范围，组织id集合
        std::vector<int32> allClassIDList;  ///< 多选警种范围，警种id集合
        std::string picURL;                 ///< 图片URL
        int8 isRead;                        ///< 0:未读  1:已读
	};

	/// 通报查询参数
	struct st_gaReportQueryParamBean{
        st_gaReportQueryParamBean() :
            status(0), 
            pageno(0), 
            pagesize(0),
            begintime(0), 
            endtime(0), 
            promotorid(0), 
            promotorproviceid(0) {}

		int8 status;	            ///< 状态值：1:未审核 2：审核通过，3：审核未通过
		int32 pageno;	            ///< 页码
		int32 pagesize;	            ///< 每页条数
		int64 begintime;	        ///< 开始时间
		int64 endtime;		        ///< 结束时间
		int64 promotorid;	        ///< 发起者ID
		int64 promotorproviceid;	///< 发起省份ID
		std::string title;			///< 标题
		std::string promotorname;	///< 发起者姓名
		std::string	fromorg;		///< 发起地点	
	};

	/// 通报分页信息
	struct st_gaReportPageBean {
        st_gaReportPageBean() : 
            pageno(0), 
            pagesize(0), 
            totalpage(0), 
            totalcount(0) {
                reports.clear();
            }

		int32 pageno;		                    ///< 页码
		int32 pagesize;		                    ///< 每页条数
		int64 totalpage;	                    ///< 总页数
		int64 totalcount;	                    ///< 总条数
		std::vector<st_gaReportBean> reports;	///< 通告列表
	};

	/// 协查统计部分
	struct st_gaCountInvestParamBean {
        st_gaCountInvestParamBean() :
            datatype(0), 
            dimension(0), 
            begintime(0), 
            endtime(0), 
            limit(0) {}

		int8 datatype;	    ///< 统计数据类型：0：发布数据；1：回复数据
		int8 dimension;	    ///< 统计维度：0：个人；1：单位 
		int64 begintime;	///< 开始时间
		int64 endtime;		///< 结束时间
		int64 limit;		///< 统计条数（前？条）
	};

	struct st_gaCountInvestResultBean {
        st_gaCountInvestResultBean() :
            id(0), 
            count(0) {}

		int64 id;	        ///< 统计对象ID
		int64 count;	    ///< 统计数量
		std::string name;	///< 统计对象名称
	};

	struct st_gaAttentionQueryParam{
        st_gaAttentionQueryParam() :
            pageNo(0), 
            pageSize(0), 
            userID(0) {}

		int32 pageNo;	    ///< 页码
		int32 pageSize;		///< 每页条数
		int64 userID;		///< 用户ID
		std::string keyword;///< 总条数
	};

	struct st_gaRegisterUser {
        st_gaRegisterUser() :
            sex(0), 
            policeType(0), 
            policeRank(0), 
            orgID(0), 
            orgLevel(0), 
            roleID(0), 
            regType(0) {}

		std::string regID;				///< 注册ID：证书中的机构代码前6位+警种2位+序列码4位组成
		std::string name;				///< 姓名
		int8 sex;						///< 性别：1男 2女
		std::string idCardNo;			///< 身份证号
		int32 policeType;				///< 警种
		int32 policeRank;				///< 警衔
		std::string duty;				///< 职务
		std::string mobile;				///< 电话
		int64 orgID;					///< 单位
		int32 orgLevel;					///< 单位级别：部级、省级、地市级、县市级、派出所级
		int64 roleID; 					///< 角色名称
		int8 regType;					///< 注册类型：1:单位用户，2:自主用户
		std::string departmentInfo;		///< 部门信息：负责人姓名电话 （单位用户填写，其他不用
	};

    /// 组织机构的搜索
    struct st_gaOrgsearchParam {
        st_gaOrgsearchParam() :
            type(0),
            area(0) {
                extendParam.clear();
            }

        std::string condition;                          ///< 条件
        int8  type;                                     ///< 类型 0：所有 1：组织架构 2：人员
        int32 area;                                     ///< 地区项 0：全国 1：新疆 
        std::map<std::string, std::string> extendParam; ///< 扩展字段：第一个string为字段名，第二个string为字段对应的值
    };

    struct st_gaAttention {
        st_gaAttention() :
            attentionType(0){}

        int8 attentionType;                 ///< 关注的类型 1：协查 2：通报
        st_gaInvestTaskBean vestTaskBean;   ///< 每页条数
        st_gaReportBean     reportBean;     ///< 总页数
    };

    struct st_gaAttentionPage{
        st_gaAttentionPage() :
            pageno(0),
            pagesize(0),
            totalpage(0),
            totalcount(0) {
                attentionlist.clear();
            }

        int32 pageno;		                        ///< 页码
        int32 pagesize;	                            ///< 每页条数
        int64 totalpage;	                        ///< 总页数
        int64 totalcount;                           ///< 总条数
        std::vector<st_gaAttention> attentionlist;  ///< 协查任务列表
    };

    struct st_investUser{
        st_investUser() :
            time(0),
            userid(0),
            policeType(0) {}

        int64 userid;	            ///< 用户名
        int64 time;		            ///< 时间
        int32 policeType;	        ///< 警种
        std::string name;           ///< 名称
        std::string orgfullname;    ///< 组织全称
    };

    /// 组织信息
    struct st_organizationInfo
    {
        st_organizationInfo() :
        orgID(0),
        enterpriseID(0),
        leaf(0),
        parentOrgID(0),
        orderNum(0),
        branchID(0),
        departLevel(0),
        subOrgNum(0),
        subUserNum(0),
        isHidden(0),
        provinceID(0),
        cityID(0),
        areaID(0) {}

        int64 orgID;                ///< 组织机构ID orgID.
        int64 enterpriseID;         ///< 企业ID enterpriseID.
        std::string orgName;        ///< 组织机构名称 orgName.
        std::string orgCode;        ///< 组织机构内码 orgCode.
        int8 leaf;                  ///< 是否叶节点 leaf.
        int64 parentOrgID;          ///< 父节点 parentOrgID.
        std::string remark;         ///< 备注 remark.
        int64 orderNum;             ///< 排序 orderNum.
        int64 branchID;             ///< 办公地ID branchID.
        std::string departID;       ///< 删除 departID.
        int8 departLevel;           ///< 组织级别 departLevel.
        int64 subOrgNum;            ///< 递归计算所有下级组织数 subOrgNum.
        int64 subUserNum;           ///< 递归计算所有下级成员数 subUserNum.
        int8 isHidden;              ///< 是否隐藏, 1对本部门公开 2对所有部门公开，3对部分部门公开 isHidden.
        int64 provinceID;           ///< 省份ID provinceID.
        std::string provinceName;   ///< 省份名称 provinceName.
        int64 cityID;               ///< 市ID cityID.
        std::string cityName;       ///< 市名称 cityName.
        int64 areaID;               ///< 县ID areaID.
        std::string areaName;       ///< 县名称 areaName.
        std::string orgNamePinyin;  ///< 拼音 orgNamePinyin.
    };

    /// 企业成员信息
    struct  st_entpriseUserInfo
    {
        st_entpriseUserInfo() :
        userID(0),
        enterpriseID(0),
        orgID(0),
        roleID(0),
        status(0),
        orderNum(0),
        newOrgID(0){}

        int64 userID;               ///< 用户ID userID.
        int64 enterpriseID;         ///< 企业ID enterpriseID.
        int64 orgID;                ///< 组织机构ID orgID.
        int64 roleID;               ///< 角色ID roleID.
        std::string enName;         ///< 企业内用户名称 enName.
        std::string duty;           ///< 企业内用户职位 duty.
        std::string enMail;         ///< 企业内用户email enMail.
        std::string enMobile;       ///< 企业内用户手机号 enMobile.
        int8 status;                ///< 企业账号是否被停用 1：正常 2：停用 status.
        int64 orderNum;             ///< 人员排序 orderNum.
        int64 newOrgID;             ///< 用户修改组织机构使用，表示用户新组织机构，在修改时给用户增加组织机构时，使用newOgrID而不是orgID newOrgID.
        std::string orgName;        ///< 组织名 orgName.
        std::string extend;         ///< 扩展信息 extend.
        std::string accountName;    ///< 账号名称 accountName.
        std::string enNamePy;       ///< 拼音 enNamePy.
        int8  bizStatus;            ///< 业务状态 业务状态：1：初始状态，2：在高管群
        std::string userHead;       ///< 头像
    };

	/// =========================================================================================

	/// ga_logic_cmd_promoteinvest
	struct req_promoteinvest: public _sdkcmd_base {
		st_gaInvestTaskBean investtask;
		CMD_SIZE();
	};

	struct resp_promoteinvest : public _sdkrespcmd_base {
        resp_promoteinvest() :
            investid(0) {}

		int64 investid;
		CMD_SIZE();
        COPY_OTHER(resp_promoteinvest);
	};


	/// ga_logic_cmd_replyinvest
	struct req_replyinvest : public _sdkcmd_base {
		st_gaInvestReplyBean replyinfo;
		CMD_SIZE();
	};


	/// ga_logic_cmd_getinvestcount
	struct req_getinvestcount: public _sdkcmd_base {
        req_getinvestcount() :
            type(0), 
            userid(0) {}

		int32 type;		///< 1 获取未回复的协查任务数 2 获取未回复的协查结果数
        int64 userid;
		CMD_SIZE();
	};

	struct resp_getinvestcount : public _sdkrespcmd_base {
        resp_getinvestcount() :
            count(0),
            type(0) {}

		int64 count;	///< 返回的任务数
        int32 type;
		CMD_SIZE();
        COPY_OTHER(resp_getinvestcount);
	};


	/// ga_logic_cmd_commentreplycontent
	struct req_commentreply : public _sdkcmd_base {
		st_gaCommentBean commtbean;
		CMD_SIZE();
	};


	/// ga_logic_cmd_getinvesttasklist
	struct req_getinvesttasklist: public _sdkcmd_base {
        req_getinvesttasklist() :
            userid(0),
            type(0) {}

        int64                   userid;
		int32					type;			///< 1 (协查人)获取协查任务列表 2 (发起人)获取协查结果列表
		st_gaInvestQueryParam	parambean;		///< 查询条件信息
		CMD_SIZE();
	};

	struct resp_investbeaninfo: public _sdkrespcmd_base {
        resp_investbeaninfo() :
            type(0) {}

        int32 type;
		st_gaInvestInfoBean  investinfobean;   ///< 协查任务信息
		CMD_SIZE();
        COPY_OTHER(resp_investbeaninfo);
	};


	/// ga_logic_cmd_getinvestdetail
	struct req_getinvestdetail: public _sdkcmd_base {
        req_getinvestdetail() :
            type(0),
            investid(0),
            userid(0) {}

		int8 type;		///< 1：发起人，返回协查结果包含回复列表和协查详情 2：协查人,只返回该协查详情
		int64 investid; ///< 协查id
        int64 userid;   ///< 查询人
		CMD_SIZE();
	};


	/// ga_logic_cmd_getinvestreplydetail
	struct req_getinvestreplydetail : public _sdkcmd_base {
        req_getinvestreplydetail() :
            replyid(0),
            userid(0) {}

		int64 replyid; ///< 回复id
        int64 userid;
		CMD_SIZE();
	};


	/// ga_logic_cmd_getreplylist
	struct req_getreplylist: public _sdkcmd_base {
        req_getreplylist() :
            type(0),
            investid(0),
            userid(0) {}

		int32 type;      ///< 1：协查人获取协查的回复列表（查的是协查人自己的回复列表） 2：发起人获取协查的回复列表（查的是该协查的所有回复）
		int32 investid;  ///< 协查任务id
        int64 userid;
		CMD_SIZE();
	};


    /// ga_logic_cmd_getstatistics
    struct req_commonUserid : public _sdkcmd_base {
        req_commonUserid() :
            userid(0) {}

        int64 userid;
        CMD_SIZE();
    };


	/// ga_logic_cmd_getinvestwithidentify
	struct req_getinvestwithidentify : public _sdkcmd_base {
		st_gaInvestQueryParam queryparam;
		CMD_SIZE();
	};


	/// ga_logic_cmd_isexistinvestrecord
	struct req_isexistinvestrecord : public _sdkcmd_base {
		st_gaInvestQueryParam queryparam;
		CMD_SIZE();
	};
	
	struct resp_isexistinvestrecord : public _sdkrespcmd_base {
        resp_isexistinvestrecord() :
            isexist(true) {}

		bool  isexist;   ///< 是否存在
		CMD_SIZE();
        COPY_OTHER(resp_isexistinvestrecord);
	};
  

	/// ga_logic_cmd_promotereport
	struct req_promotereport: public _sdkcmd_base {
		st_gaReportBean reportbean;
		CMD_SIZE();
	};

	struct resp_promotereport: public _sdkrespcmd_base {
        resp_promotereport() :
            reportid(0) {}

		int64 reportid;
		CMD_SIZE();
        COPY_OTHER(resp_promotereport);
	};
	

	/// ga_logic_cmd_getreportbyid
	struct req_getreportbyid: public _sdkcmd_base {
        req_getreportbyid() :
            reportid(0) {}

		int64 reportid;
		CMD_SIZE();
	};

	struct resp_getreportbyid : public _sdkrespcmd_base {
		st_gaReportBean reportbean;
		CMD_SIZE();
        COPY_OTHER(resp_getreportbyid);
	};


	/// ga_logic_cmd_getreportlist
	struct req_getreportlist : public _sdkcmd_base {
        req_getreportlist() :
            userid(0) {}

        int64 userid;
		st_gaReportQueryParamBean param;
		CMD_SIZE();
	};

	struct resp_getreportlist : public _sdkrespcmd_base {
		st_gaReportPageBean reportpagebean;
		CMD_SIZE();
        COPY_OTHER(resp_getreportlist);
	};


	/// ga_logic_cmd_countinvest
	struct req_countinvest: public _sdkcmd_base {
		st_gaCountInvestParamBean param;
		CMD_SIZE();
	};

    struct resp_countinvest : public _sdkrespcmd_base {
        resp_countinvest() {
            countlist.clear();
        }

		std::vector<st_gaCountInvestResultBean> countlist;
		CMD_SIZE();
        COPY_OTHER(resp_countinvest);
	};


    /// ga_logic_cmd_querytotalcount  
    struct req_querytotalcount : public _sdkcmd_base {
        req_querytotalcount() :
            userid(0) {}

        int64 userid;
        std::string type;
        CMD_SIZE();
    };

    /// ga_logic_cmd_suggestsearch
    struct req_suggestsearch : public _sdkcmd_base {
        std::string key;
        CMD_SIZE();
    };

    struct resp_suggestsearch : public _sdkrespcmd_base {
        resp_suggestsearch() {
            vt.clear();
        }

        std::string what;
        std::vector<std::string> vt;
        CMD_SIZE();
        COPY_OTHER(resp_suggestsearch);
    };

    /// ga_logic_cmd_searchinvestigationlist
    struct req_searchinvestigationlist : public _sdkcmd_base {
        st_gaInvestQueryParam vestParam;
        CMD_SIZE();
    };

    struct resp_searchinvestigationlist : public _sdkrespcmd_base {
        std::string what;
        st_gaInvestPageBean pagebean;
        CMD_SIZE();
        COPY_OTHER(resp_searchinvestigationlist);
    };

    /// ga_logic_cmd_search
    struct req_search : public _sdkcmd_base {
        st_gaOrgsearchParam searchParam;
        CMD_SIZE();
    };

    struct resp_search : public _sdkrespcmd_base {
        resp_search() {
            vtOrgInfo.clear();
            vtEntUserInfo.clear();
        }

        std::string what;
        std::vector<st_organizationInfo> vtOrgInfo;
        std::vector<st_entpriseUserInfo> vtEntUserInfo;
        CMD_SIZE();
        COPY_OTHER(resp_search);
    };

	/// ga_logic_cmd_qInvestS
    /**
     * type 类型
     * 0 设置关键字，用户设置关注时用， 需要keywordList(关键字列表), code : 0 成功
     * 1 获取自己的关键字列表, 自己设置的关注的关键字列表, 返回 listStr(如果不为空的话)
     * 2 是否有新关注, value64代表数量
     * 3 拉取新关注列表, gaqp 查询参数, 返回 gap
     * 6 查询核查历史（分页）
     * 参数：queryParam
     * 返回：code : 0：成功，其他失败
     */
	struct req_investParam : public _sdkcmd_base {
        req_investParam() :
            type(0),
            userid(0) {
                keywordList.clear();
            }

	    int8 type;
	    int64 userid;
	    std::vector<std::string> keywordList;
	    st_gaAttentionQueryParam gaqp;
        st_gaInvestQueryParam queryParam;
		CMD_SIZE();
	};

	struct resp_investRet : public _sdkrespcmd_base {
        resp_investRet() :
            type(0),
            value64(0) {
                listStr.clear();
            }

        int8 type;
	    std::string what;
	    int64 value64;
	    std::vector<std::string> listStr;
        st_gaAttentionPage gap;
        st_gaInvestPageBean ipage;
		CMD_SIZE();
        COPY_OTHER(resp_investRet);
	};


	/// ga_logic_cmd_qEnUQS
	struct req_enUQSParam : public _sdkcmd_base {
        req_enUQSParam() :
            type(0) {}

	    int8 type;
	    st_gaRegisterUser gru;
		CMD_SIZE();
	};

	struct resp_enUQRet : public _sdkrespcmd_base {
        resp_enUQRet() :
            value64(0) {}

        int64 value64;
	    std::string what;
		CMD_SIZE();
        COPY_OTHER(resp_enUQRet);
	};

    /// ga_logic_cmd_getappointreport
    struct req_getappointreport : public _sdkcmd_base {
        req_getappointreport() :
            reportType(0),
            pageno(0),
            pagesize(0) {}

        int8 reportType;    ///< 通报类型 1:追逃通报 2 : 协查通报 3 : 情况通报 4 : 通知通报
        int32 pageno;		///< 页码
        int32 pagesize;		///< 每页条数
        CMD_SIZE();
    };

    struct resp_getappointreport : public _sdkrespcmd_base {
        st_gaReportPageBean st;
        CMD_SIZE();
        COPY_OTHER(resp_getappointreport);
    };

    /// ga_logic_cmd_getappointinvest
    struct req_getappointinvest : public _sdkcmd_base {
        req_getappointinvest() :
            type(0),
            investigationType(0),
            pageno(0),
            pagesize(0) {}

        int8 type;                  ///< 1:核查任务 2:核查结果 
        int32 investigationType;    ///< 核查类型 4.涉恐 3.涉案 2.未知 1.普通
        int32 pageno;		        ///< 页码
        int32 pagesize;		        ///< 每页条数
        CMD_SIZE();
    };

    struct resp_getappointinvest : public _sdkrespcmd_base {
		int8 type;                  ///< 1:核查任务 2:核查结果 
        st_gaInvestPageBean st;
        CMD_SIZE();
        COPY_OTHER(resp_getappointinvest);
    };

    /// ga_logic_cmd_getreplytypeinvest
    struct req_getreplytypeinvest : public _sdkcmd_base {
        req_getreplytypeinvest() :
        type(0),
        investigationType(0),
        pageno(0),
        pagesize(0) {}

        int8 type;                  ///< 1:核查任务 2:核查结果 
        int32 investigationType;    ///< 1.未处理   2.已处理
        int32 pageno;		        ///< 页码
        int32 pagesize;		        ///< 每页条数
        CMD_SIZE();
    };

    struct resp_getreplytypeinvest : public _sdkrespcmd_base {
        int8 type;                  ///< 1:核查任务 2:核查结果 
        st_gaInvestPageBean st;
        CMD_SIZE();
        COPY_OTHER(resp_getreplytypeinvest);
    };

    /// ga_logic_cmd_setRead
    struct req_setread : public _sdkcmd_base {
        req_setread() :
            type(0),
            id(0) {}

        int8 type;          ///< 1:协查任务 2:通报任务 
        int64 id;           ///< 协查或者通报的ID
        CMD_SIZE();
    };

    /// ga_logic_cmd_getUnreadCounts
    struct req_getunreadCounts : public _sdkcmd_base {
        req_getunreadCounts() :
            type(0) {}

        int8 type;          ///< 1:协查 2:通报
        CMD_SIZE();
    };
}

#endif