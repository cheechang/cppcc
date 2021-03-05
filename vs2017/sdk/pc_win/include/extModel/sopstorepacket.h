#pragma once

#include "../extModel/packet.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN ///防止重复包含
#include <Windows.h>
#else
//
#endif

namespace model
{

    /// 结果
    struct Result {
        int32	    code;           ///< 是否处理成功
        std::string message;        ///< 失败原因
        int64       result;         ///< 处理的结果
    };

    /// 应用实体
    struct AppInfoBean {
        int64       id;             ///< 应用主键
        std::string name;           ///< 应用名称
        std::string	icon;           ///< 应用图标(图片路径)
        int32	    classify;       ///< 应用分类(分类ID)
        int32       type;           ///< 软件应用类型(1:原生APK,2:H5)
        std::string homeUrl;        ///< h5首页访问地址
        std::string version;        ///< 版本号
        std::string packageName;    ///< 包名
        std::string downloadUrl;    ///< 下载地址
        std::string activityName;   ///< 安卓调取本地应用名称
        std::string orgIds;         ///< 发布范围(多个orgID以’，’拼接)
        int32       status;         ///< 状态(1:启用,2:停用，3：删除)
        std::string key;            ///< app_key
        std::string secret;         ///< app_secret
        int64       createUserID;   ///< 创建者userID
        std::string createTime;     ///< 创建时间
        std::string updateTime;     ///< 更新时间-新建分类时初始值与创建时间一致
        int32	    sort;           ///< 排序字段-未设置排序值时默认为1
        std::string column1;        ///< 预留字段1
        std::string column2;        ///< 预留字段2
        std::string column3;        ///< 预留字段3
        int64 createUnitID;
    };

    /// 应用分类实体
    struct AppClassifyBean {
        int32       classifyID;     ///< 分类主键
        std::string classifyName;   ///< 分类名称
        int64       createUserID;   ///< 创建者userID
        int32       classifyStatus; ///< 分类状态 1：正常 2：已删除
        std::string createTime;     ///< 创建时间
        std::string updateTime;     ///< 更新时间-新建分类时初始值与创建时间一致
        int32       classifySort;   ///< 排序字段-未设置排序值时默认为1
        std::string classifyColumn1;///< 预留字段1
        std::string classifyColumn2;///< 预留字段2
        std::string classifyColumn3;///< 预留字段3
        int32 classifyType;
    };

    /// 要闻热点实体
    struct HotNewsBean {
        int32       id;             ///< 要闻主键
        std::string newsTitle;      ///< 要闻标题
        std::string newsCover;      ///< 封面图片路径
        std::string newsContent;    ///< 正文内容
        int64       createUserID;   ///< 创建者Id
        std::string createTime;     ///< 创建时间
        std::string updateTime;     ///< 更新时间
        int32       newsSort;       ///< 排序字段
        std::string newsColumn1;    ///< 预留字段1
        std::string newsColumn2;    ///< 预留字段2
        std::string newsColumn3;    ///< 预留字段3
    };

    /// 用户与应用关系
    struct AppRelationBean {
        int32       id;             ///< 关系id
        int64       userID;         ///< 用户id
        int64       appID;          ///< 应用id
        int32       classifyID;     ///< 应用类型id
        int32       relationStatus; ///< 关系状态 1：正常 2：已删除
        std::string createTime;     ///< 创建时间
        std::string updateTime;     ///< 更新时间
        int32       sort;           ///< 排序字段
        std::string relationColumn1;///< 预留字段1
        std::string relationColumn2;///< 预留字段2
        std::string relationColumn3;///< 预留字段3
    };

    /// 我的应用信息
    struct MyAppInfo {
        AppClassifyBean appClassify;            ///< 应用分类
        std::vector<AppInfoBean> appInfoList;   ///< 应用集合
        int64 code;                             ///< 响应码
        std::string msg;                        ///< 响应码描述语
    };

    /// 应用商店
    struct AppStore {
        std::vector<AppInfoBean> appInfoList;   ///< 应用集合
        int64       pageSize;                   ///< 每页显示的条数
        int64       pageNum;                    ///< 当前页数
        int64       totalCount;                 ///< 总条数
        int64       totalPage;                  ///< 总页数
        int64       code;                       ///< 响应码
        std::string msg;                        ///< 响应码描述语
    };

    /// 应用商店查询参数
    struct AppStoreQueryParam {
        std::string appName;                    ///< 应用名称
        int64       userId;                     ///< 应用类型
        int64       appClassifyId;              ///< id
        int64       pageSize;                   ///< 每页显示的条数
        int64       pageNum;                    ///< 当前页数
        int32       searchType;
    };

    struct reqAppStore {
        int8 type;
        AppStoreQueryParam appStoreQueryParam;
        AppRelationBean appRelation;
        int64 value64;
    };
    /**
    * 应用统计结果实体
    * zhaorujia
    */
    struct AppStatisticsResult{
        /* 结果描述 */
        std::string msg;
        /* 结果码 */
        std::string code;
    };

    struct EnterpriseUserBean {
        int64 userID;                           /// 用户ID
        int64 enterpriseID;                     /// 企业ID
        int64 orgID;                            /// 组织机构ID
        int64 roleID;                           /// 角色ID
        std::string Enname;                     /// 企业内用户名称
        std::string duty;                       /// 企业内用户职位
        std::string Enmail;                     /// 企业内用户email
        std::string Enmobile;                   /// 企业内用户手机号
        int8 status;                            /// 企业账号是否被停用 1：正常 2：停用
        int64 orderNum;                         /// 人员排序
        int64 newOrgID;
        std::string orgName;                    /// 组织名
        std::string extend;                     /// 扩展信息
        std::string accountName;                /// 账号名称
        int8 bizStatus;                         /// 业务状态：1：初始状态，2：在高管群
        std::string userHead;                   /// 头像
        std::string userExtend;
    };

    struct OrganizationBean {
        OrganizationBean() :
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
        std::string extend;         ///< 拓展字段
        int32 resCode;              ///< 导入组织机构时,返回的错误码
        int32 exlRow;
    };

    struct UserBean {
        int64 userID;               ///<用户ID
        std::string phoneNum;       //<可以删除
        std::string email;          ///<可以删除
        int16 userType;             ///<目前没有意义
        std::string name;           ///<用户名
        std::string pwd;            ///<用户密码
        int8 sex;                   ///<性别
        std::string area;           ///<区域
        YMD birthday;               ///<生日
        std::string school;         ///<毕业学校
        int64 qqNum;                ///<可以删除
        std::string maccode;        ///<目前无意义
        int8 status;                ///<用户状态 1：正常 2：停用 3: 注册邀请4: 影子用户，5:锁定，6:冻结
        std::string portraitURL;    ///<头像地址
        std::string sign;           ///<签名
        int8 timeZone;              ///<时区
        std::vector<std::string> phoneNums; ///<电话号码清单
        std::vector<std::string> emails;    ///<邮箱清单
        std::string oriPortraitURL;        ///<原始头像地址
        std::string idcard;                 ///<可以删除
        std::string accountName;            ///<账号名称
        std::string extend;                 ///<扩展信息
        int64 lockDeadline;                 ///<锁定截止时间，毫秒
        int64 remainLockDuration;           ///<剩余锁定时长，毫秒
        int64 SDKID;                        ///<SDKID
        std::string entExtend;              ///<企业扩展信息
        std::vector<model::AccountType> accounts;  ///<联系方式集合
        int8 regFlag;                       ///<注册标识0为更新1为注册
        int8 pwdStrength;                   ///<密码强度:1:弱,2:中,3:强
        std::string orgID;                  ///<组织结构id,多个用逗号分隔
        int64 roleID;                       ///<角色ID
        int8 bizStatus;                     ///<业务状态，1：初始默认，2：在高管层
        int8 uploadFlag;                    ///<上传标识, 1:未上传,2:已上传,3:已忽略
        int8 oldStatus;                     ///<保存冻结之前用户状态status的值
    };
    struct OrgUserAndChildNodes {
        int32 code;
        std::string what;
        std::vector<EnterpriseUserBean> users;
        std::vector<OrganizationBean> obeans;
        std::string oPower;
    };

    struct OrgSearchUserRet {
        EnterpriseUserBean ub;
        std::string power;
    };

    struct OrgSearchResult {
        std::vector<EnterpriseUserBean> uBeans;
        std::string resultFlag;
    };
    struct respAppStore{
        int32 code;
        std::string what;
        std::vector<MyAppInfo> appInfos;
        AppStore appStore;
        std::vector<AppInfoBean> appBeans;
        std::vector<AppClassifyBean> classifyBeans;
        std::vector<HotNewsBean> hotNewsBeans;
        Result ret;
        AppStatisticsResult statResult;
    };

    struct reqEnOS{
        int8 type;
        int64 value64;
        int64 value64_2;
        int64 value64_3;
        std::string valuestr;
        std::vector<int64> list_i64;
        std::map<std::string, std::string> params;
    };

    struct respEnOS{
        int32 code;
        std::string what;
        OrgUserAndChildNodes nodes;
        std::vector<OrgSearchUserRet> orgSearchUsers;
        OrgSearchResult searchRet;
        std::vector<EnterpriseUserBean> entUsers;
        std::vector<OrganizationBean> depts;
    };
    ///客户端统计接口
    struct AppStatisticsBean{
        /* 应用类型：
        * 1：门户应用类型 2.普通应用类型
        */
        std::string appType;
        /* 应用ID */
        std::string appID;
        /* 用户ID */
        std::string userID;
        /* 组织机构ID*/
        std::string orgID;
        /* 组织机构CODE */
        std::string orgCode;
        /* 组织机构CODE */
        std::string unitID;
    };
}