#pragma once
#include "../model/SDKTypes.h"
#include "IService.h"
#include "../extModel/sopstorepacket.h"

#include <string>
#include <vector>

#define VER_SOP INTERFACE_VERSION(1,0)
static const VRVIID IID_ISopStoreService = { 0x92dc7e43, 0x4a6c, 0x4426, 0xad, 0x5d, 0x28, 0x1f, 0xe7, 0x65, 0xbc, 0x1 };

namespace service
{
	class ISopStoreService : public IService
	{
	public:

		virtual ~ISopStoreService(){}
        /**
        * \brief 应用商店查询接口
        * @param[in] type  消息类型 
            1.查询我的应用列表
            2.查询应用商店列表---根据应用发布范围(用户所属组织的在发布范围内的)
            3.模糊查询
            4.应用分类列表
            5.要闻热点列表
            6.添加我的应用
            7.删除我的应用
        * @param[in] appStoreQueryParam  应用商店查询参数
        * @param[in] appRelation  用户与应用关系
        * @param[in] value64  用户与应用关系
        * @param[in] stic  应用统计参数
        * @param[out] cb  传入接收结果回调  _1错误信息 _2查询结果
        */
		virtual void queryAppStore(int8 type, model::AppStoreQueryParam appStoreQueryParam, model::AppRelationBean appRelation, int64 value64, model::AppStatisticsBean& stic, SFunction<void(ErrorInfo, model::respAppStore)> cb) = 0;
        /**
        * \brief 在组织架构中查询
        * @param[in] req  查询请求结构体  
        * @param[out] cb  传入接收结果回调  _1错误信息 _2查询响应结果
        */
        virtual void queryEnOS(model::reqEnOS &req, SFunction<void(ErrorInfo, model::respEnOS &resp)> cb) = 0;
        /**
        * \brief 获取用户信息
        * @param[in] userParam  获取用户信息条件键值对
        * @param[out] cb  传入接收结果回调  _1错误信息 _2错误码 _3获取到的Json串 _4用户信息集合
        */
        virtual void getUsersByParam(std::map<std::string, std::string> &userParam, SFunction<void(ErrorInfo, int32 code, std::string &what, std::vector<model::UserBean> &bean)> cb) = 0;

	};
}