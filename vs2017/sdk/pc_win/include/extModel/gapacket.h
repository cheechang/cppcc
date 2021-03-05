#pragma once

#include "../extModel/packet.h"

namespace model
{
    /// 用户信息
    struct gaUserBean {
        gaUserBean() :
        userid(0),
        orgid(0),
        policeType(0),
		regType(0) {}

        int64		userid;      ///< 用户id
        int64		orgid;       ///< 组织id
        int32       policeType;  ///< 警种
        int32       regType;     ///< 核查的权限
        std::string name;        ///< 用户名
        std::string orgfullname; ///< 组织全称
        std::string userHead;    ///< 头像
    };

    /// 核查附件信息
    struct gaFileBean {
        gaFileBean() :
        filesize(0) {}

        int64       filesize;   ///< 文件大小
        std::string filename;   ///< 文件名
        std::string filepath;   ///< 文件路径
    };

    /// 核查回复
    struct gaInvestReplyBean{
        gaInvestReplyBean() :
        replytime(0),
        replyid(0),
        investid(0),
        investigationType(2) {
            filelist.clear();
        }

        int64 replytime;			                ///< 回复时间
        int64 replyid;				                ///< 回复者id
        int64 investid;				                ///< 核查任务id
        std::string content;		                ///< 内容
        int32 investigationType;                    ///< 核查类型 4.涉恐 3.涉案 2.未知 1.普通
        gaUserBean replier;		                    ///< 回复者信息
        gaUserBean promotor;		                ///< 回复To的人
        std::vector<gaFileBean> filelist;           ///< 回复的附件列表
    };

    /// 核查
    struct gaInvestTaskBean {
        gaInvestTaskBean() :
        invalidtime(0),
        investigationType(2),
        status(0),
        replystatus(0),
        replycount(0),
        notreplycount(0),
        commentcount(0),
        investid(0),
        promotetime(0),
        updatetime(0),
        remaintime(0),
        isRead(0) {}

        int64		invalidtime;	                ///< 截至时间
        int32       investigationType;              ///< 核查类型 4.涉恐 3.涉案 2.未知 1.普通
        std::string title;			                ///< 标题
        std::string content;		                ///< 内容

        gaUserBean  investuser;                     ///< 核查人
        gaFileBean  file;	                        ///< 附件

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

        int32		status;			                ///< 状态 1.正常 2.已过期
        int32       replystatus;	                ///< 回复状态 1：未回复，2：已按时回复，3：未按时回复
        int32		replycount;		                ///< 回复数
        int32		notreplycount;                  ///< 未回复数
        int32		commentcount;	                ///< 评价数
        int64	    investid;		                ///< 协查任务id
        int64		promotetime;	                ///< 发起时间
        int64		updatetime;		                ///< 更新时间
        int64		remaintime;		                ///< 剩余时间,0的时候表示已经过期的时间
        int8        isRead;                         ///< 0:未读  1:已读
        gaUserBean	promotor;	                    ///< 发起人信息
        std::vector<gaInvestReplyBean> replylist;   ///< 回复列表
    };

    /// 评价核查
    struct gaCommentBean {
        gaCommentBean() :
        commentid(0),
        commentuserid(0),
        investid(0),
        replyid(0) {}

        int64 commentid;		                    ///< 评论id
        int64 commentuserid;	                    ///< 评论者id
        int64 investid;			                    ///< 协查id
        int64 replyid;			                    ///< 回复id
    };

    struct investtasklist {
        investtasklist() :
        userid(0),
        type(0) {}

        int64 userid;
        int32 type;			                        ///< 1 (核查人)获取核查任务列表 2 (发起人)获取核查结果列表
        int32 pageno;		                        ///< 页码
        int32 pagesize;	                            ///< 每页的条数
        int64 promoterareaid;                       ///< 发起人区域id
        int64 promotorID;                           ///< 发起者userID
        int64 receiverID;                           ///< 接收者userID
    };

    struct investPageBean {
        investPageBean() :
        pageno(0),
        pagesize(0),
        totalpage(0),
        totalcount(0) {
            tasklist.clear();
        }

        int32		pageno;		                    ///< 页码
        int32		pagesize;	                    ///< 每页条数
        int64		totalpage;	                    ///< 总页数
        int64		totalcount;                     ///< 总条数
        std::vector<gaInvestTaskBean> tasklist;     ///< 协查任务列表
    };

    /// 关注
    struct attentionQueryParam {
        attentionQueryParam() :
        pageNo(0),
        pageSize(0),
        userID(0) {}

        int32 pageNo;	                            ///< 页码
        int32 pageSize;		                        ///< 每页条数
        int64 userID;		                        ///< 用户ID
        std::string keyword;                        ///< 总条数
    };

    /// 通报数据信息
    struct gaReportBean {
        gaReportBean() :
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

        int8		        status;		            ///< 状态值 1：未审核 2：已通过审核 3：未通过审核
        int64		        reportid;		        ///< 通报ID	
        int64		        promotetime;	        ///< 发起时间
        int64		        updatetime;	            ///< 修改时间
        std::string         title;		            ///< 通报标题
        std::string         content;		        ///< 通报内容
        gaUserBean          promotor;		        ///< 发起人信息
        int64               auditTimeStamp;         ///< 审核时间戳
        int8                reportType;             ///< 通报类型 1:追逃通报 2 : 协查通报 3 : 情况通报 4 : 通知通报
        std::vector<int64>  allOrgIDList;           ///< 多选组织范围，组织id集合
        std::vector<int32>  allClassIDList;         ///< 多选警种范围，警种id集合
        std::string         picURL;                 ///< 图片URL
        int8                isRead;                 ///< 0:未读  1:已读
    };

    /// 通报分页信息
    struct gaReportPageBean {
        gaReportPageBean() :
        pageno(0),
        pagesize(0),
        totalpage(0),
        totalcount(0) {
            reports.clear();
        }

        int32                       pageno;		     ///< 页码
        int32                       pagesize;		 ///< 每页条数
        int64                       totalpage;	     ///< 总页数
        int64                       totalcount;	     ///< 总条数
        std::vector<gaReportBean>   reports;	     ///< 通告列表
    };

    /// 通报查询参数
    struct gaReportQueryParamBean {
        gaReportQueryParamBean() :
        status(0),
        pageno(0),
        pagesize(0),
        begintime(0),
        endtime(0),
        promotorid(0),
        promotorproviceid(0) {}

        int8 status;	                            ///< 状态值：1:未审核 2：审核通过，3：审核未通过
        int32 pageno;	                            ///< 页码
        int32 pagesize;	                            ///< 每页条数
        int64 begintime;	                        ///< 开始时间
        int64 endtime;		                        ///< 结束时间
        int64 promotorid;	                        ///< 发起者ID
        int64 promotorproviceid;	                ///< 发起省份ID
        std::string title;			                ///< 标题
        std::string promotorname;	                ///< 发起者姓名
        std::string	fromorg;		                ///< 发起地点	
    };

    /// 企业成员信息
    struct gaEntpriseUserInfo
    {
        gaEntpriseUserInfo() :
        userID(0),
        orgID(0) {}

        int64 userID;               ///< 用户ID userID.
        int64 orgID;                ///< 组织机构ID orgID.
        std::string enName;         ///< 企业内用户名称 enName.
        std::string orgName;        ///< 组织名 orgName.
        std::string extend;         ///< 扩展信息 extend.
        std::string userHead;       ///< 头像
    };

    /// 组织信息
    struct gaOrganizationInfo
    {
        gaOrganizationInfo() :
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
    
}