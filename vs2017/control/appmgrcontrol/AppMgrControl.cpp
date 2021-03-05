#include "AppMgrControl.h"
#include "IControl.h"
#include "../controlmanager/core/ControlManager.h"
#include "interface/IMClient.h"
#include "../../utils/common.h"
#include "../../utils/PinYinConvert.h"
#include "model/Packet.h"
#include "log.h"
const char * filename = 0;
int line = 0;

namespace control{
	service::IMClient* g_client =CNull;

	AppMgrControl::AppMgrControl(const std::string &strName)
		: m_pluginname(strName)
		, m_pUserService(CNull)
		, m_pConfigService(CNull)
	{
	BEGIN;
	END;
	}
	
	AppMgrControl::~AppMgrControl()
	{
	BEGIN;
	END;
	}
	
	std::string AppMgrControl::GetName()
	{
		std::string result("");
		result.append(m_pluginname);
		result.append(".dll");
		return result;
	}
	
	std::string AppMgrControl::GetDisplayName()
	{
		return m_pluginname;
	}
	
	void AppMgrControl::SetSdkClientObj(void* obj)
	{
	BEGIN;
		g_client=static_cast<service::IMClient*>(obj);
		if (CNull == g_client)
		{
			AddLog(LOG_LEV_ERROR,"SDK客户端对象指针失败");
			return;
		}
		m_pUserService = USERSERVICE;
		m_pContactService = CONTACTSERVICE;
		m_pLddService = LDDSERVICE;
		m_pGroupService = GROUPSERVICE;
		m_pFileService = FILESERVICE;
		m_pConfigService = CONFIGSERVICE;
	END;
	}	
	
	/**********************************************
	* @brief 查询应用市场应用信息
	* @param[out] cb 传入接收结果回调 _1返回的应用信息
	***********************************************/
	void AppMgrControl::getAllApplication(
		CFunction<void(std::vector<data::AppInfo>)> cb)
	{
	BEGIN;
		if (m_pUserService)
		{
			m_funcGetAllApplicationCB = cb;
			QueryMarketApplication data;
			data.pageNum = 1;
			data.pageSize = 100;
			data.deviceType = 1;
			m_pUserService->queryMarketApplication(data,
				CBind(&AppMgrControl::onQueryMarketApplication,
					this, CPlaceholders  _1, CPlaceholders  _2));
		}
	END;
	}

	void AppMgrControl::onQueryMarketApplication(service::ErrorInfo err,
		SmallMarketAppPage& page)
	{
	BEGIN;
		AddLog(LOG_LEV_INFO, "err = %d", err);

		if (err == 0) 
		{
			AddLog(LOG_LEV_INFO, "App count = %d", page.appInfoList.size());
			m_pUserService->getInstalledApplication(1,
				CBind(&AppMgrControl::onInstalledAppsRetrieve,
					this, CPlaceholders  _1, CPlaceholders  _2,
					page.appInfoList));
		}
	END;
	}

	void AppMgrControl::onInstalledAppsRetrieve(service::ErrorInfo err,
		std::vector<SmallMarketAppInfo>& vecInstalledAppsInfo,
		std::vector<SmallMarketAppInfo>& vecAllAppsInfo)
	{	
	BEGIN;
		AddLog(LOG_LEV_INFO, "err = %d", err);

		if (err == 0) 
		{
			std::vector<data::AppInfo> vecAppInfo;
			for (int i = 0; i < vecAllAppsInfo.size(); i++)
			{
				SmallMarketAppInfo& info = vecAllAppsInfo[i];
				if ((info.appType == 1 || info.appType == 5)
					&& info.defaultInstall == 2) 
				{
					AddLog(LOG_LEV_INFO, "ID = %lld, Name = %s, Icon = %s,"
						" url = %s, Type = %d", 
						info.appID, info.appName.data(), info.appIcon.data(),
						info.mainUrl.data(), info.appType);

					data::AppInfo appInfo;
					appInfo.appID = info.appID;
					appInfo.name = info.appName;
					appInfo.icon = m_pConfigService->headImgPath() + info.appIcon;
					appInfo.icon = utils::GetHeadPath(4,appInfo.icon);
					appInfo.url = info.mainUrl;
					appInfo.introduction = info.appFunctintroduce;
					appInfo.isInstalled = false;
					
					AddLog(LOG_LEV_INFO, "App count = %d",
						vecAllAppsInfo.size());
					for (int j = 0; j < vecInstalledAppsInfo.size(); j++)
					{
						if (info.appID == vecInstalledAppsInfo[j].appID)
						{
							appInfo.isInstalled = true;
						}
					}

					vecAppInfo.push_back(appInfo);
				}
			}

			m_funcGetAllApplicationCB(vecAppInfo);
		}
	END;
	}
	
	/**********************************************
	* @brief 获取已安装的应用
	* @param[out] cb 传入接收结果回调 _1返回的应用信息
	***********************************************/
	void AppMgrControl::getInstalledApplication(
		CFunction<void(std::vector<data::AppInfo>)> cb)
	{
	BEGIN;
		m_funcGetInstalledApplicationCB = cb;
		m_pUserService->getInstalledApplication(1,
			CBind(&AppMgrControl::onGetInstalledApplication,
				this, CPlaceholders  _1, CPlaceholders  _2));
	END;
	}

	void AppMgrControl::onGetInstalledApplication(service::ErrorInfo err,
		std::vector<SmallMarketAppInfo>& appsInfo)
	{	
	BEGIN;
		AddLog(LOG_LEV_INFO, "err = %d", err);

		if (err == 0) 
		{
			std::vector<data::AppInfo> vecAppInfo;
			for (int i = 0; i < appsInfo.size(); i++)
			{
				SmallMarketAppInfo& info = appsInfo[i];
				if (info.appType == 1 || info.appType == 5) 
				{
					AddLog(LOG_LEV_INFO, "ID = %lld, Name = %s, Icon = %s,"
						" url = %s, Type = %d", 
						appsInfo[i].appID, appsInfo[i].appName.data(),
						appsInfo[i].appIcon.data(), appsInfo[i].mainUrl.data(),
						appsInfo[i].appType);

					data::AppInfo info;
					info.appID = appsInfo[i].appID;
					info.name = appsInfo[i].appName;
					info.icon = m_pConfigService->headImgPath()
						+ appsInfo[i].appIcon;
					info.icon = utils::GetHeadPath(4,info.icon);
					info.url = appsInfo[i].mainUrl;
					info.introduction = appsInfo[i].appFunctintroduce;
					info.isInstalled = false;
					vecAppInfo.push_back(info);
				}
			}

			m_funcGetInstalledApplicationCB(vecAppInfo);
		}
	END;
	}

	/**********************************************
	* @brief 删除添加应用
	* @param[in] type 传入的操作类型，true添加，false删除
	* @param[in] appID 操作的appID
	* @param[out] cb 传入接收结果回调 _1错误信息
	***********************************************/
	void AppMgrControl::addOrDeleteApplication(bool operType, int64 appID,
		CFunction<void(int)> cb)
	{
	BEGIN;
		m_funcAddOrDeleteApplicationCB = cb;
		int type = operType ? 2 : 4;
		m_pUserService->addOrDeleteApplication(type, appID,
			CBind(&AppMgrControl::onAddOrDeleteApplication,
				this, CPlaceholders  _1));
	END;
	}

	void AppMgrControl::onAddOrDeleteApplication(service::ErrorInfo err)
	{
	BEGIN;
		AddLog(LOG_LEV_INFO, "err = %d", err);
		m_funcAddOrDeleteApplicationCB(err);
	END;
	}

	/**********************************************
	* @brief 获取用户信息Json串
	* @return 用户信息Json串
	***********************************************/
	std::string AppMgrControl::getAccountInfoJson(void)
	{
	BEGIN;
		model::Account accountInfo;
		m_pUserService->getAccountInfo(accountInfo);
		std::vector<LoginInfo> vec = m_pConfigService->getLoginInfos();

		std::string exLoginMes = m_pConfigService->getLoginExData(vec[0].server);
		Json::Reader reader;
		Json::Value exDataObj;
		std::string serverHost = "";
		if (reader.parse(exLoginMes, exDataObj))
		{
			if (exDataObj["Serverhost"]["OutterIP"].isString())
			{
				serverHost =  exDataObj["Serverhost"]["OutterIP"].asString();
			}
		}
		
		AddLog(LOG_LEV_INFO, "UserID: %lld, UserName: %s, Portrait: %s, "
			"extend: %s, nickID: %s, phoneNumber: %s, email: %s, Server: %s"
			"serverHost: %s",
			accountInfo.id.value(), accountInfo.name.value().data(),
			accountInfo.thumbAvatarUrl.value().data(),
			accountInfo.extends.value().data(), 
			accountInfo.nickId.value().data(),
			accountInfo.phone.value().data(), accountInfo.email.value().data(),
			vec[0].server.data(), serverHost.data());
		Json::Value obj;
		Json::FastWriter writer;
		obj["mUserId"] = accountInfo.id.value();
		obj["mUserName"] = accountInfo.name.value();
		obj["mPortraitUrl"] = accountInfo.thumbAvatarUrl.value();
		obj["extend"] = accountInfo.extends.value();
		obj["nickID"] = accountInfo.nickId.value();
		obj["phoneNumber"] = accountInfo.phone.value();
		obj["email"] = accountInfo.email.value();
		obj["serverName"] = vec[0].server;
		obj["serverHost"] =  serverHost;
		std::string str = writer.write(obj);
		AddLog(LOG_LEV_INFO, "Json: %s", str.data());
	END;
		return str;
	}

	/**********************************************
	* @brief 获取用户好友信息Json串
	* @return 用户信息Json串
	***********************************************/
	std::string AppMgrControl::getContactListJson(void)
	{
	BEGIN;
		std::vector<CSharedPtr<model::Contact>> vecContacts;
		m_pContactService->getContactList(vecContacts);

		Json::Value arr;
		for (int i = 0; i < vecContacts.size(); i++)
		{
			if (vecContacts[i]->isApp.value() == 2)
			{
				AddLog(LOG_LEV_INFO, "buddyName: %s, serverName: %s, "
					"pinyin: %s, buddyID: %lld",
					vecContacts[i]->name.value().data(),
					vecContacts[i]->server.value().data(),
					vecContacts[i]->pinyin.value().data(),
					vecContacts[i]->id.value());

				char c;
				if (vecContacts[i]->pinyin.value().length() != 0)
				{
					c = vecContacts[i]->pinyin.value().at(0);
				}
				else if (vecContacts[i]->name.value().length() != 0)
				{
					/*c = utils::PinYinConvert::GetTeam(
						vecContacts[i]->name.value());*/
				}
				else
				{
					c = '#';
				}
				
				Json::Value obj;
				if (vecContacts[i]->name.value().size() > 0)
				{
					obj["buddyName"] = vecContacts[i]->name.value();
				}
				else 
				{
					obj["buddyName"] = vecContacts[i]->id.value();
				}
				obj["serverName"] = vecContacts[i]->server.value();
				//obj["portraitURL"] = vecContacts[i]->avatar.value();
				obj["buddyNameInitial"] = c;
				obj["buddyID"] = vecContacts[i]->id.value();
				arr["contacts"].append(obj);
			}
		}
		Json::FastWriter writer;
		std::string str = writer.write(arr);
		AddLog(LOG_LEV_INFO, "Json: %s", str.data());
	END;
		return str;
	}

	/**********************************************
	* @brief 获取组织机构信息Json串
	* @param[in] uuid 传入的参数Json，以解析组织ID
	* @param[out] cb 传入接收结果回调 _1组织机构信息Json串
	***********************************************/
	void AppMgrControl::getOrganizationJson(std::string uuid,
		CFunction<void(std::string)> cb)
	{
	BEGIN;
		AddLog(LOG_LEV_INFO, "uuid: %s", uuid.data());

		m_funcGetOrganizationJsonCB = cb;

		Json::Reader reader;
		Json::Value obj;
		if (reader.parse(uuid, obj))
		{   
			if (obj["orgId"].isInt())
			{
				int64 orgId = obj["orgId"].asInt64();
				m_pLddService->getVisibleOrgUsers(0,0,orgId,
					CBind(&AppMgrControl::onSerGetVisibleOrgUsers,
						this, CPlaceholders  _1, CPlaceholders  _2,
						CPlaceholders  _3, CPlaceholders  _4,
						CPlaceholders  _5));
			}
			else
			{
				AddLog(LOG_LEV_WARN, "org id parse error");
			}
		}
		else 
		{
			AddLog(LOG_LEV_WARN, "uuid parse error");
		}
	END;
	}

	void AppMgrControl::onSerGetVisibleOrgUsers(service::ErrorInfo err,
		int8 allowChat, int8 contactVisiable,
		std::vector<model::OrganizationInfo>& orgs,
		std::vector<model::EntpriseUserInfo>& users)
	{
	BEGIN;
		AddLog(LOG_LEV_INFO, "err = %d", err);
		if(err == 0)
		{
			Json::Value objJson;
			for (int i = 0; i < orgs.size(); i++)
			{
				AddLog(LOG_LEV_INFO, "orgID: %lld, orgName: %s",
					orgs[i].orgID, orgs[i].orgName);

				Json::Value obj;
				obj["orgID"] = orgs[i].orgID;
				obj["orgName"] = orgs[i].orgName;
				objJson["organization"].append(obj);
			}
	
			for (int i = 0; i < users.size(); i++)
			{
				AddLog(LOG_LEV_INFO, "staffID: %lld, staffName: %s",
					users[i].userID, users[i].enName);
				
				Json::Value obj;
				obj["staffID"] = users[i].userID;
				obj["staffName"] = users[i].enName;
				objJson["staff"].append(obj);
			}
	
			std::vector<LoginInfo> vec = m_pConfigService->getLoginInfos();
			objJson["serverName"] = vec[0].server;

			Json::FastWriter writer;
			std::string str = writer.write(objJson);
			AddLog(LOG_LEV_INFO, "Json: %s", str.data());

			m_funcGetOrganizationJsonCB(str);
		}
	END;
	}

	/**********************************************
	* @brief 获取用户群信息Json串
	* @param[out] cb 传入接收结果回调 _1用户群信息Json串
	***********************************************/
	std::string AppMgrControl::getGroupListJson(void)
	{
	BEGIN;
		Json::Value arr;
		std::vector<CSharedPtr<TinyGroup>> groups;
		m_pGroupService->getGroupList(groups);
		for (int i = 0; i < groups.size(); i++)
		{
			AddLog(LOG_LEV_INFO, "groupName: %s, pinyin: %s, serverName: %s, "
				"groupPortraitURL: %s, groupID: %lld",
				groups[i]->groupName.value().data(),
				groups[i]->pinyin.value().data(),
				groups[i]->server.value().data(), 
				groups[i]->avatar.value().data(), 
				groups[i]->groupId.value());

			char c;
			if (groups[i]->pinyin.value().length() != 0)
			{
				c = groups[i]->pinyin.value().at(0);
			}
			else if (groups[i]->groupName.value().length() != 0)
			{
				//c = utils::PinYinConvert::GetTeam(groups[i]->groupName.value());
			}
			else
			{
				c = '#';
			}

			Json::Value obj;
			obj["groupName"] = groups[i]->groupName.value();
			obj["groupNameInitial"] = c;
			obj["serverName"] = groups[i]->server.value();
			//obj["groupPortraitURL"] = groups[i]->avatar.value();
			obj["groupID"] = groups[i]->groupId.value();
			arr["groupsInfo"].append(obj);
		}
		
		Json::FastWriter writer;
		std::string str = writer.write(arr);
		AddLog(LOG_LEV_INFO, "Json: %s", str.data());
	END;
		return str;
	}

	/**********************************************
	* @brief 获取群成员信息Json串
	* @param[in] uuid 传入的参数Json，以解析群ID
	* @param[out] cb 传入接收结果回调 _1群成员信息Json串
	***********************************************/
	void AppMgrControl::getGroupMembersJson(std::string uuid,
		CFunction<void(std::string)> cb)
	{
	BEGIN;
		AddLog(LOG_LEV_INFO, "uuid: %s", uuid.data());

		Json::Reader reader;
		Json::Value obj;
		if (reader.parse(uuid, obj))
		{
			if (obj["groupID"].isInt64())
			{
				int64 groupID = obj["groupID"].asInt64();
				AddLog(LOG_LEV_INFO, "orgid: %d", groupID);
				m_pGroupService->getMemberList(groupID, 
					CBind(&AppMgrControl::onSerGetGroupMembers, this, 
						CPlaceholders  _1, CPlaceholders  _2));
			}
			else
			{
				AddLog(LOG_LEV_INFO, "orgid parse error");
			}
		}
		else
		{
			AddLog(LOG_LEV_INFO, "uuid parse error");
		}

	END;
	}

	void AppMgrControl::onSerGetGroupMembers(service::ErrorInfo err,
		std::vector<CSharedPtr<Member>>& members)
	{
	BEGIN;
		if (err == 0)
		{
			Json::Value arr;
			for (int i = 0; i < members.size(); i++)
			{
				if (!(members[i]->isApp.value()))
				{
					Log(LOG_LEV_INFO, LOG_FILE, "memberName: %s, memberID: %lld",
						members[i]->name.value().data(),
						members[i]->id.value());

					//char c = utils::PinYinConvert::GetTeam(member->name.value());
	
					Json::Value obj;
					obj["memberName"] = members[i]->name.value();
					//obj["portraitURL"] = members[i]->avatar.value();
					obj["memberNameInitial"] = members[i]->pingyin.value().at(0);
					obj["memberID"] = members[i]->id.value();
					arr["members"].append(obj);
				}
			}
	
			Json::FastWriter writer;
			std::string str = writer.write(arr);
			m_funcGetGroupMembersJsonCB(str);
			AddLog(LOG_LEV_INFO, "Json: %s", str.data());
		}
		else 
		{
			AddLog(LOG_LEV_WARN, "err = %d", err);
		}
	END;
	}

	/**********************************************
	* @brief 获取本地图片Json串
	* @param[in] vec 传入的图片本地地址
	* @param[out] cb 传入接收结果回调 _1本地图片Json串
	***********************************************/
	void AppMgrControl::getLocalPhotosJson(std::vector<std::string> images,
		CFunction<void(std::string)> cb,
		CFunction<void(std::string)> pro)
	{
	BEGIN;
		m_funcGetLocalPhotosJsonCB = cb;
		m_funcFileUploadFailureCB = pro;
		Json::Value arr;
		m_pFileService->uploadImage(0, 0, images[0], images[0], "",
			CBind(&AppMgrControl::onSerSendImage, this,
				CPlaceholders  _1, CPlaceholders  _2,
				CPlaceholders  _3, CPlaceholders  _4,
				images, arr, 0));
	END;
	}

	void AppMgrControl::onSerSendImage(service::ErrorInfo err, int64 targetId,
			const std::string& srcJson, const std::string& thumpJson,
			std::vector<std::string> images, Json::Value arrImages, 
			unsigned int time)
	{
	BEGIN;
		std::string imagePath = images[time];
		std::size_t pos = imagePath.find_last_of('/');
		std::string imageName = imagePath.substr(pos + 1);
	
		if (err == 0)
		{
			AddLog(LOG_LEV_INFO, "srcJson: %s", srcJson.data());

			std::vector<LoginInfo> vec = m_pConfigService->getLoginInfos();
			std::string exLoginJson = 
				m_pConfigService->getLoginExData(vec[0].server);
			AddLog(LOG_LEV_INFO, "domainJson: %s", exLoginJson.data());

			Json::Reader reader;
			Json::Value objSrc, objExLogin;
			if (reader.parse(srcJson, objSrc) 
				&& reader.parse(exLoginJson, objExLogin))
			{
				if (objSrc["files"][0]["url"].isString() 
					&& objExLogin["DownURL"].isString())
				{
					std::string url = objSrc["files"][0]["url"].asString();
					std::string domain = objExLogin["DownURL"].asString();
					if (domain.back() == '/')
					{
						url = domain + url;
					}
					else
					{
						url = domain + '/' + url;
					}
					arrImages.append(url);
					AddLog(LOG_LEV_INFO, "url: %s", url.data());
				}
				else
				{
					AddLog(LOG_LEV_INFO, "url or DownURL error");
				}
			}
			else
			{
				AddLog(LOG_LEV_INFO, "url or DownURL parse error");
			}
		}
		else
		{
			m_funcFileUploadFailureCB(imageName);
			AddLog(LOG_LEV_INFO, "%s upload failed", imageName.data());
		}
	
		time++;
		if (time < images.size())
		{
			std::string imagesPath = images[time];
			m_pFileService->uploadImage(0, 0, imagesPath, imagesPath, "",
				CBind(&AppMgrControl::onSerSendImage, this,
					CPlaceholders  _1, CPlaceholders  _2,
					CPlaceholders  _3, CPlaceholders  _4,
					images, arrImages, time));
		}
		else
		{
			Json::Value obj;
			obj["mPhotoPath"] = arrImages;
	
			Json::FastWriter writer;
			std::string str = writer.write(obj);
			m_funcGetLocalPhotosJsonCB(str);
			AddLog(LOG_LEV_INFO, "Json: %s", str.data());
		}
	END;
	}

	/**********************************************
	* @brief 获取本地文件Json串
	* @param[in] vec 传入的文件本地地址
	* @param[out] cb 传入接收结果回调 _1上传的文件Json串
	***********************************************/
	void AppMgrControl::getLocalFilesJson(std::vector<std::string> files,
		CFunction<void(std::string)> cb,
		CFunction<void(std::string)> pro)
	{
	BEGIN;
		m_funcGetLocalFilesJsonCB = cb;
		m_funcFileUploadFailureCB = pro;
		UploadFileProperty fileProperty;
		fileProperty.localid = 0;
		fileProperty.targetid = 0;
		fileProperty.type = 6;
		fileProperty.localPath = files[0];
		fileProperty.msg = "";
		fileProperty.encryptKey = "";
		fileProperty.isP2p = 0;
		Json::Value arr;
		m_pFileService->uploadFile(fileProperty,
			CBind(&AppMgrControl::onSerSendFile, this,
				CPlaceholders  _1, CPlaceholders  _2,
				CPlaceholders  _3, files, arr, 0));
	END;
	}

	void AppMgrControl::onSerSendFile(service::ErrorInfo err, int64 targetId, 
		const std::string& fileJson, std::vector<std::string> files, 
		Json::Value arrFiles, unsigned int time)
	{
	BEGIN;
		std::string filePath = files[time];
		std::size_t pos = filePath.find_last_of('/');
		std::string fileName = filePath.substr(pos + 1);
	
		if (err == 0)
		{
			AddLog(LOG_LEV_INFO, "srcJson: %s", fileJson.data());

			std::vector<LoginInfo> vec = m_pConfigService->getLoginInfos();
			std::string exLoginJson = 
				m_pConfigService->getLoginExData(vec[0].server);
			AddLog(LOG_LEV_INFO, "domainJson: %s", exLoginJson.data());

			Json::Reader reader;
			Json::Value objFile, objExLogin;
			if (reader.parse(fileJson, objFile) 
				&& reader.parse(exLoginJson, objExLogin))
			{
				if (objFile["files"][0]["url"].isString() 
					&& objExLogin["DownURL"].isString())
				{
					std::string url = objFile["files"][0]["url"].asString();
					std::string domain = objExLogin["DownURL"].asString();
					if (domain.back() == '/')
					{
						url = domain + url;
					}
					else
					{
						url = domain + '/' + url;
					}
					arrFiles.append(url);
					AddLog(LOG_LEV_INFO, "url: %s", url.data());
				}
				else
				{
					AddLog(LOG_LEV_INFO, "url or DownURL error");
				}
			}
			else
			{
				AddLog(LOG_LEV_INFO, "url or DownURL parse error");
			}
		}
		else
		{
			m_funcFileUploadFailureCB(fileName);
			AddLog(LOG_LEV_INFO, "%s upload failed", fileName.data());
		}
	
		time++;
		if (time < files.size())
		{
			UploadFileProperty fileProperty;
			fileProperty.localid = 0;
			fileProperty.targetid = 0;
			fileProperty.type = 6;
			fileProperty.localPath = files[time];
			fileProperty.msg = "";
			fileProperty.encryptKey = "";
			fileProperty.isP2p = 0;
			m_pFileService->uploadFile(fileProperty,
				CBind(&AppMgrControl::onSerSendFile, this,
					CPlaceholders  _1, CPlaceholders  _2, 
					CPlaceholders  _3, files, arrFiles, time));
		}
		else
		{
			Json::Value obj;
			obj["mFilePath"] = arrFiles;
	
			Json::FastWriter writer;
			std::string str = writer.write(obj);
			m_funcGetLocalFilesJsonCB(str);
			AddLog(LOG_LEV_INFO, "Json: %s", str.data());
		}
	END;
	}

	/**********************************************
	* @brief 获取服务器名称Json串
	* @return 服务器名称Json
	***********************************************/
	std::string AppMgrControl::getServerNameJson(void)
	{
	BEGIN;
		model::Account accountInfo;
		m_pUserService->getAccountInfo(accountInfo);
		std::vector<LoginInfo> vec = m_pConfigService->getLoginInfos();
		std::string exLoginData = m_pConfigService->getLoginExData(vec[0].server);

		Json::Reader reader;
		Json::FastWriter writer;
		Json::Value exDataObj, obj;
		std::string serverHost = "";
		if (reader.parse(exLoginData, exDataObj))
		{
			if (exDataObj["ImageHost"].isString())
			{
				obj["host"] = exDataObj["ImageHost"].asString() + "/";
				return writer.write(obj);
			}
			else
			{
				AddLog(LOG_LEV_INFO, "ImageHost parse error");
				return "{}";
			}
		}
		else
		{
			AddLog(LOG_LEV_INFO, "exLoginData parse error");
			return "{}";
		}
	END;
	}
	
	extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance()
	{
		IControl* instance = NULL;
		instance = new AppMgrControl();
		return  instance;
	}
	
	extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(
		IControl* instance)
	{
		if(NULL != instance){
			delete instance;
			instance = NULL;
		}
	}
}