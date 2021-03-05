#pragma once

#include "../model/LoginInfo.h"
#include "../model/Packet.h"
#include "../model/Account.h"
#include "IService.h"

#include <string>

#define VER_ICLOUD INTERFACE_VERSION(1,0)
static const VRVIID IID_ICloudService = { 0x526f54ac, 0x48b2, 0x41ec, 0x87, 0xd8, 0x86, 0x98, 0xfb, 0xb1, 0xf7, 0x3c };

namespace service
{

class ICloudService :public IService
{
public:
    virtual ~ICloudService(){}


	/**
	* \brief 上传文件到云盘
	* @param[in] pid 文件唯一标示
	* @param[in] userId 用户ID
	* @param[in] cb _1 错误信息  _2文件夹下所有子文件和子文件夹信息
	* @param[in] pro  进度回调 _1 extra_req  _2 process  _3 文件当前传入大小/文件总大小
	*/
	virtual void uploadFile(CloudUploadFileInfo &info, SFunction<void(ErrorInfo, const std::string&)> cb, SFunction<void(int32, int32, const std::string&)> pro = SNull) = 0;

	/**
	* \brief 查询文件夹
	* @param[in] pid 文件唯一标示
	* @param[in] userId 用户ID
	* @param[in] cb _1 错误信息  _2文件夹下所有子文件和子文件夹信息
	*/
    virtual void queryFloder(int64 pid, int64 userId, SFunction<void(ErrorInfo, std::vector<CloudFileInfo>&)> cb) = 0;

	/**
	* \brief 添加文件
	* @param[in] info 添加文件需要的信息
	* @param[in] cb _1 错误信息  _2添加的文件的详细信息
	*/
	virtual void addFile(CloudAddFileInfo &info, SFunction<void(ErrorInfo, CloudFileInfo&)> cb) = 0;

	/**
	* \brief 删除文件
	* @param[in] fileCodes 要删除的文件编码集合
	* @param[in] cb _1 错误信息
	*/
	virtual void delFile(std::vector<std::string> &fileCodes, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 重命名文件
	* @param[in] fileId 文件ID
	* @param[in] fileName 文件名
	* @param[in] cb _1 错误信息
	*/
	virtual void renameFile(int64 fileId, const std::string &fileName,  SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 通过文件ID获取文件
	* @param[in] fileId 文件ID
	* @param[in] cb _1 错误信息 _2获取的文件信息
	*/
	virtual void getFileById(int64 fileId, SFunction<void(ErrorInfo, CloudFileInfo&)> cb) = 0;

	/**
	* \brief 通过文件hash码获取文件
	* @param[in] hash  hash码
	* @param[in] cb _1 错误信息 _2获取的文件信息
	*/
	virtual void getFilesByHash(const std::string &hash, SFunction<void(ErrorInfo, std::vector<CloudFileInfo>&)> cb) = 0;

	/**
	* \brief 通过文件hash码获取文件(同步接口)
	*/
	virtual std::vector<CloudFileInfo> getFilesByHashSync(const std::string &hash) = 0;
	
	/**
	* \brief 搜索文件
	* @param[in] userId 用户id
	* @param[in] searchText 搜索的内容
	* @param[in] cb _1 错误信息 _2获取的文件信息
	*/
	virtual void searchFiles(int64 userId, const std::string &searchText, SFunction<void(ErrorInfo, std::vector<CloudFileInfo>&)> cb) = 0;

	/**
	* \brief 创建团队文件夹
	* @param[in] info 添加文件需要的信息
	* @param[in] cb _1 错误信息  _2添加的文件的详细信息
	*/
	virtual void createTeam(CloudAddFileInfo  &info, SFunction<void(ErrorInfo, CloudFileInfo&)> cb) = 0;

	/**
	* \brief 添加团队成员
	* @param[in] members 成员信息
	* @param[in] cb _1 错误信息 
	*/
	virtual void teamAddMember(std::vector<TeamMemberInfo> &members, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 移除团队成员
	* @param[in] members 成员信息
	* @param[in] cb _1 错误信息
	*/
	virtual void teamRemoveMember(std::vector<TeamMemberInfo> &members, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 重置团队成员
	* @param[in] members 成员信息
	* @param[in] cb _1 错误信息
	*/
	virtual void teamResetMember(std::vector<TeamMemberInfo> &members, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取团队文件夹
	* @param[in] userId 用户id
	* @param[in] cb _1 错误信息 _2 team信息集合
	*/
	virtual void getTeams(int64 userId, SFunction<void(ErrorInfo, std::vector<CloudFileInfo>&)> cb) = 0;

	/**
	* \brief 获取团队文件夹所有成员
	* @param[in] fileId 文件ID
	* @param[in] cb _1 错误信息 _2 member信息集合
	*/
	virtual void teamMembers(int64 fileId, SFunction<void(ErrorInfo, std::vector<TeamMemberInfo>&)> cb) = 0;

	/**
	* \brief 获取团队成员角色
	* @param[in] isShow   角色是否在前端显示 目前始终为1
	* @param[in] cb _1 错误信息 _2 role信息集合
	*/
	virtual void getRoles(int8 isShow, SFunction<void(ErrorInfo, std::vector<CloudRoleInfo>&)> cb) = 0;

	/**
	* \brief 通过角色ID获取团队成员角色
	* @param[in] roleId
	* @param[in] cb _1 错误信息 _2 role信息
	*/
	virtual void getRoleById(int64 roleId, SFunction<void(ErrorInfo, CloudRoleInfo&)> cb) = 0;

	/**
	* \brief 增加团队成员角色
	* @param[in] role 角色信息
	* @param[in] cb _1 错误信息
	*/
	virtual void addRole(BaseRoleInfo &role, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 编辑团队成员角色
	* @param[in] role 角色信息
	* @param[in] cb _1 错误信息
	*/
	virtual void editRole(BaseRoleInfo &role, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 移除团队成员角色
	* @param[in] roleId 角色ID
	* @param[in] cb _1 错误信息
	*/
	virtual void removerRole(int64 roleId, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取许可信息
	* @param[in] roleId 角色ID
	* @param[in] fileId 文件ID
	* @param[in] userId 用户ID
	* @param[in] cb _1 错误信息
	*/
	virtual void getPermission(int64 roleId, int64 fileId, int64 userId, SFunction<void(ErrorInfo, CloudPermission&)> cb) = 0;

};



}