#include "GroupMgrControl.h"
#include "interface/IMClient.h"
#include "IControl.h"
#include "log.h"
#include "data/GroupData.h"
#include "../../utils/common.h"

#include <iostream>  
#include <vector>  
#include <algorithm>

const char * filename = 0;
int line = 0;
namespace control{
  service::IMClient* g_client =CNull;
  bool GroupListPinyinCmpDesc(const CSharedPtr<data::TinyGroup>& lhs, const CSharedPtr<data::TinyGroup>&rhs){
	  return !lhs->pinyin.value().empty() && !rhs->pinyin.value().empty() && (lhs->pinyin.value().at(0)>rhs->pinyin.value().at(0));
  }
  bool GroupListPinyinCmp(const CSharedPtr<data::TinyGroup>& lhs, const CSharedPtr<data::TinyGroup>&rhs){
	  return !lhs->pinyin.value().empty() && !rhs->pinyin.value().empty() && (lhs->pinyin.value().at(0)<rhs->pinyin.value().at(0));
  }
  bool GroupListSpecialCharCount(const CSharedPtr<data::TinyGroup>& lhs){
	  return lhs->pinyin.value().at(0)<97 || lhs->pinyin.value().at(0)>122;
  }
  GroupMgrControl::GroupMgrControl(const std::string &strName):m_pluginname(strName),m_groupservice(CNull),m_CreateGroupMemCount(0){
BEGIN;

END;
  }
  GroupMgrControl::~GroupMgrControl(){
BEGIN;
END;
  }
	/***********************************************
	* @brief 返回带后缀的插件名
	* @param[in]无
	***********************************************/
    std::string GroupMgrControl::GetName(){
		std::string result("");
		result.append(m_pluginname);
		result.append(".dll");
		return result;
	}
	/***********************************************
	* @brief 返回不带后缀的插件名
	* @param[in]无
	***********************************************/
    std::string GroupMgrControl::GetDisplayName(){
		return m_pluginname;
	}
	/***********************************************
	* @brief 设置sdk客户端实例对象
	* @param[in]无
	***********************************************/
    void GroupMgrControl::SetSdkClientObj(void* obj){
BEGIN;
		g_client =static_cast<service::IMClient*>(obj);
		if (CNull == g_client)
		{
			AddLog(LOG_LEV_ERROR,"SDK客户端对象指针失败");
			return;
		}
		m_groupservice = GROUPSERVICE;
		m_fileservice = FILESERVICE;
		m_searchservice = SEARCHSERVICE;
END;
	}

	void GroupMgrControl::RegGroupHeadImgUpdateCb(CFunction < void(int64, const std::string&)>cb){
		BEGIN;
		  if (IsNullService()) return;
		  m_groupservice->regGroupHeadImgUpdateCb(cb);
		END;
	}

	void GroupMgrControl::RegMemberHeadImgUpdateCb( CFunction < void(int64 targetId, const std::string&head) > cb )
	{
		BEGIN;
		if (IsNullService()) return;
		m_groupservice->regMemberHeadImgUpdateCb(cb);
		END;
	}

	void GroupMgrControl::RegGroupBackImgUpdateCb( CFunction < void(int64 targetId, const std::string&head) > cb )
	{
		BEGIN;
		if (IsNullService()) return;
		m_groupservice->regGroupBackImgUpdateCb(cb);
		END;
	}

	void GroupMgrControl::RegGroupRefreshCb( CFunction< void(int8 code, const data::Group&groupInfo) > cb )
	{
		BEGIN;
		if (IsNullService()) return;
		m_groupRefreshCb.push_back(cb);
		m_groupservice->regGroupRefreshCb(CBind(&GroupMgrControl::OnGroupRefreshCb,this,
			CPlaceholders  _1,CPlaceholders  _2));
		END;
	}

	void GroupMgrControl::RegTransferGroupCb( CFunction< void(int64 creatorId, const std::string&creatorName, int64 groupId, const std::string&groupName) > cb )
	{
		BEGIN;
		if (IsNullService()) return;
		m_transferGroupCb = cb;
		m_groupservice->regTransferGroupCb(CBind(&GroupMgrControl::OnTransferGroupCb,this,
			CPlaceholders  _1,CPlaceholders  _2,CPlaceholders  _3,
			CPlaceholders  _4));
		END;
	}

	void GroupMgrControl::RegGrpMemInfoRefreshCb( CFunction< void(int64 groupId, const data::Member&memberInfo) > cb )
	{
		BEGIN;
		if (IsNullService()) return;
		m_groupMemInfoRefreshCb.push_back(cb);
		m_groupservice->regGrpMemInfoRefreshCb(CBind(&GroupMgrControl::OnGrpMemInfoRefreshCb,this,
			CPlaceholders  _1,CPlaceholders  _2));
		END;
	}

	void GroupMgrControl::RegGrpMemRefreshCb( CFunction< void(int type, int64 groupId, std::vector<CSharedPtr<data::Member> >&members) > cb )
	{
		BEGIN;
		if (IsNullService()) return;
		m_groupMemRefreshCb = cb;
		m_groupservice->regGrpMemRefreshCb(CBind(&GroupMgrControl::OnGrpMemRefreshCb,this,
			CPlaceholders  _1,CPlaceholders  _2,CPlaceholders  _3));
		END;
	}

	void GroupMgrControl::RegGetGrpMemListCb( CFunction<void(int code, std::vector<CSharedPtr<data::Member> >&members)> cb )
	{
		BEGIN;
		if (IsNullService()) return;
		m_getGroupMemListCb = cb;
		m_groupservice->regGetGrpMemListCb(CBind(&GroupMgrControl::OnGetGrpMemListCb,this,
			CPlaceholders  _1,CPlaceholders  _2));
		END;
	}

	void GroupMgrControl::RegGroupListCb( CFunction< void(std::vector<CSharedPtr<data::TinyGroup> >&groups) > cb )
	{
		BEGIN;
		if (IsNullService()) return;
		m_groupListCb = cb;
		m_groupservice->regGroupListCb(CBind(&GroupMgrControl::OnGroupListCb,this,
			CPlaceholders  _1));
		END;
	}

	void GroupMgrControl::CreateGroup( int level, const std::string &name, std::vector<int64> &members, CFunction<void(int, int64)> cb )
	{
		BEGIN;
		if (IsNullService()) return;
		m_CreateGroupMemCount = members.size() + 1;
		m_groupservice->createGroup(level,name,members,cb);
		END;
	}

	void GroupMgrControl::AddGroup( int64 groupid, const std::string &verify_info, CFunction<void(int)> cb )
	{
		BEGIN;
		if (IsNullService()) return;
		m_groupservice->addGroup(groupid,verify_info,cb);
		END;
	}

	void GroupMgrControl::RemoveGroup( int type, int64 groupid, CFunction<void(int)> cb )
	{
		BEGIN;
		if (IsNullService()) return;
		m_groupservice->removeGroup(type,groupid,cb);
		END;
	}

	void GroupMgrControl::TransferGroup( int64 groupid, int64 userid, CFunction<void(int)> cb )
	{
		BEGIN;
		if (IsNullService()) return;
		m_groupservice->transferGroup(groupid,userid,cb);
		END;
	}

	void GroupMgrControl::GetGroupSet( int64 groupid, CFunction<void(int, int8, int8)> cb )
	{
		BEGIN;
		if (IsNullService()) return;

		m_groupservice->getGroupSet(groupid,cb);
		END;
	}

	void GroupMgrControl::SetGroupSet( int64 groupid, int8 verify_type, int8 is_allow, CFunction<void(int)> cb )
	{
		BEGIN;
		if (IsNullService()) return;
		m_groupservice->setGroupSet(groupid,verify_type,is_allow,cb);
		END;
	}

	void GroupMgrControl::GetGroupInfo( int64 groupid, data::Group& groupInfo )
	{
		BEGIN;
		if (IsNullService()) return;
		model::Group group;
		m_groupservice->getGroupInfo(groupid,group);
		DataConvert(group,groupInfo);
		END;
	}

	void GroupMgrControl::SetGroupInfo( int64 groupId, data::GroupUpdate &group, CFunction<void(int)> cb )
	{
		BEGIN;
		if (IsNullService()) return;
		model::GroupUpdate groupUpdateInfo;
		DataConvert(group,groupUpdateInfo);
		m_groupNoticeResultCb = cb;
		m_groupservice->setGroupInfo(groupId,groupUpdateInfo,std::bind(&GroupMgrControl::onSerSetGroupInfoResult, this, std::placeholders::_1));
		END;
	}

	void GroupMgrControl::GetGroupList( std::vector<CSharedPtr<data::TinyGroup> > &groups )
	{
		BEGIN;
		if (IsNullService()) return;
		std::vector<CSharedPtr<model::TinyGroup> > outTinyGroups;
		m_groupservice->getGroupList(outTinyGroups);
		for(int i=0;i<outTinyGroups.size();++i){
			CSharedPtr<model::TinyGroup> tiny = outTinyGroups.at(i);
			if (tiny->groupId == 0){
				continue;
			}
			CSharedPtr<data::TinyGroup> outTiny = CMakePtr<data::TinyGroup>();
			DataConvert(tiny,outTiny);
			if (outTiny->pinyin.value().empty()){
				outTiny->pinyin = "#";
			}

			groups.push_back(outTiny);
		}
		//std::sort(groups.begin(),groups.end(),GroupMgrControl::sort);

		if (groups.size() > 0)
		{
			int32 specialCharCount = std::count_if(groups.begin(), groups.end(), GroupListSpecialCharCount);//统计特殊分组个数
			std::sort(groups.begin(), groups.end(), GroupListPinyinCmpDesc);//根据Pinyin降序排序
			if (groups.size()>specialCharCount){
				std::sort(groups.begin(), groups.end() - specialCharCount, GroupListPinyinCmp);//根据Pinyin升序排序
			}
		}
		END;
	}

	void GroupMgrControl::InviteMember( int64 groupid,std::vector<int64> &members,CFunction<void(int)> cb )
	{
		BEGIN;
		if (IsNullService()) return;
		m_groupservice->inviteMember(groupid,members,cb);
		END;
	}

	void GroupMgrControl::RemoveMember( int64 groupid, int64 userid, CFunction<void(int)> cb )
	{
		BEGIN;
		if (IsNullService()) return;
		m_groupservice->removeMember(groupid,userid,cb);
		END;
	}

	void GroupMgrControl::RemoveMembers( int64 groupid, std::vector<int64> userids, CFunction<void(int)> cb )
	{
		BEGIN;
		if (IsNullService()) return;
		m_groupservice->removeMembers(groupid,userids,cb);
		END;
	}

	void GroupMgrControl::SetMemberInfo( data::Member &member, CFunction<void(int)> cb )
	{
		BEGIN;
		if (IsNullService()) return;
		model::Member outMember;
		if (member.memberType.isSet())
		{
			outMember.memberType = member.memberType.value();
		}
		if (member.remark.isSet())
		{
			outMember.remark = member.remark.value();
		}
		outMember.groupId = member.groupId.value();
		outMember.id = member.id.value();
		//= DataConvert(member);
		m_groupservice->setMemberInfo(outMember,cb);
		END;
	}

	bool GroupMgrControl::IsInGroup( int64 groupId, int64 userId )
	{   if (IsNullService()) return false;
		return m_groupservice->isInGroup(groupId,userId);
	}

	bool GroupMgrControl::GetMemberInfo( int64 groupid, int64 userid, data::Member &member )
	{
		if (IsNullService()) return false;
		model::Member outMember;
		bool ret = m_groupservice->getMemberInfo(groupid,userid,outMember);
		DataConvert(outMember, member);
		if (m_searchservice){
			model::Contact user;
			m_searchservice->getUserInfoSync(userid, user);
			std::string json = user.entExtends.value();
			if (outMember.entExtends.value().empty()){
				member.entExtends = json;
			}
			if (outMember.remark.value().empty()){
				member.remark = user.name.value();
			}
			if (outMember.thumbAvatar.value().empty()){
				member.thumbAvatar = user.thumbAvatar.value();
			}
		}
		return ret;
	}

	void GroupMgrControl::GetMemberList( int64 groupid, CFunction<void(int, std::vector<CSharedPtr<data::Member> >&)> cb )
	{
		BEGIN;
		if (IsNullService()) return;
		m_getMemsListCb = cb;
		AddLog(LOG_LEV_INFO,"======================groupID:%lld",groupid);
		m_groupservice->getMemberList(groupid,CBind(& GroupMgrControl::OnGetMemberListCb,
			this,CPlaceholders  _1,CPlaceholders  _2));
		END;
	}

	/**
	* \brief 获取群文件列表
	* @param[in] groupid 传入群id
	* @param[in] beginid 传入起始id
	* @param[in] count 传入数量
	* @param[in] flag 传入偏移标志0为向上1为向下
	* @param[in] cb  传入接收结果回调   _1错误信息 _2文件信息集合
	*/
	void GroupMgrControl::getGroupFileList(int64 groupid,
		CFunction<void(int, std::vector<CSharedPtr<data::FileInfo>>&)> cb)
	{
		BEGIN;
		if (IsNullService()) return;
		AddLog(LOG_LEV_INFO,"groupID = %lld", groupid);
		m_pGetFileListCb = cb;
		m_groupservice->getGroupFileList(groupid, 0, 100, 0, 
			CBind(&GroupMgrControl::onGetFileListCb, this, CPlaceholders  _1, CPlaceholders  _2));
		END;
	}

	void GroupMgrControl::onGetFileListCb(service::ErrorInfo code, std::vector<Fileinfo>& files)
	{
		BEGIN;
		AddLog(LOG_LEV_INFO,"code = %d", code);

		std::vector<CSharedPtr<data::FileInfo>> outFiles;
		if (code == 0)
		{
			for (int i = 0; i < files.size(); i++)
			{
				AddLog(LOG_LEV_INFO,"fileid = %lld, userid = %lld, size = %lld, time = %lld, name = %s, url = %s",
					files[i].fileid, files[i].userid, files[i].size, files[i].time, files[i].name.data(), files[i].url.data());

				CSharedPtr<data::FileInfo> file = CMakePtr<data::FileInfo>();
				file->fileid = files[i].fileid;
				file->userid = files[i].userid;
				file->size = utils::convert2ReadableSize(files[i].size);
				file->time = files[i].time;
				file->name = files[i].name;
				file->url = files[i].url;
				file->path = files[i].path;
				file->encrypt_key = files[i].encrypt_key;
				outFiles.push_back(file);
			}
		}
		m_pGetFileListCb(code, outFiles);
		END;
	}

	void GroupMgrControl::DeleteGroupFile( std::vector<int64> &files, int64 groupId,CFunction<void(int)> cb )
	{
		BEGIN;
		if (IsNullService()) return;
		if(files.size() > 0)
		{
			m_groupfileDelResultCb[files.at(0)] = cb;
			m_groupservice->deleteGroupFile(files,groupId,std::bind(&GroupMgrControl::onSerDelFileResult,this, std::placeholders::_1,files));
		}	
		END;
	}

	void GroupMgrControl::GetPersonalGroupImg( int64 groupId, CFunction<void(int, const std::string&)> cb )
	{
		BEGIN;
		if (IsNullService()) return;
		m_groupservice->getPersonalGroupImg(groupId,cb);
		END;
	}

	void GroupMgrControl::SetPersonalGroupImg( int64 groupId, const std::string &imgUrl, CFunction<void(int)> cb )
	{
		BEGIN;
		if (IsNullService()) return;
		m_groupservice->setPersonalGroupImg(groupId,imgUrl,cb);
		END;
	}

	void GroupMgrControl::SetGroupMsgRemindType( int64 groupId, int8 mode , CFunction<void(int)> cb )
	{
		BEGIN;
		if (IsNullService()) return;
		m_groupservice->setGroupMsgRemindType(groupId,mode,cb);
		END;
	}

	void GroupMgrControl::GetGroupMsgRemindType( int64 groupId, CFunction<void(int, int8)> cb )
	{
		BEGIN;
		if (IsNullService()) return;
		m_groupservice->getGroupMsgRemindType(groupId,cb);
		END;
	}

	void GroupMgrControl::SetGroupExtraInfo( int64 groupId, int8 vSign, int8 msgContentMode, CFunction<void(int)> cb )
	{
		BEGIN;
		if (IsNullService()) return;
		m_groupservice->setGroupExtraInfo(groupId,vSign,msgContentMode,cb);
		END;
	}

	void GroupMgrControl::DataConvert(const model::Group &group, data::Group &groupInfo )
	{
		groupInfo.brief = group.brief.value();
		groupInfo.bulletin = group.bulletin.value();
		groupInfo.chatImage = group.chatImage.value();
		groupInfo.createTime = group.createTime.value();
		groupInfo.extend = group.extend.value();
		groupInfo.groupMessageContentMode = group.groupMessageContentMode.value();
		groupInfo.info = DataConvert(group.info.value());
		groupInfo.isSearch = group.isSearch.value();
		if(group.memberNums.value() == 0)
		{
			groupInfo.memberNums = m_CreateGroupMemCount;
		}
		else
		{
			groupInfo.memberNums = group.memberNums.value();
		}
		//groupInfo.memberNums = group.memberNums.value();
		groupInfo.personalMessageContentMode = group.personalMessageContentMode.value();
		groupInfo.privateMsgPwd = group.privateMsgPwd.value();
		groupInfo.relatedEntId = group.relatedEntId.value();
		groupInfo.relatedGroupId = group.relatedGroupId.value();
	}

	data::TinyGroup GroupMgrControl::DataConvert( const model::TinyGroup tinyGroup )
	{
		data::TinyGroup groupData;
		groupData.avatar = tinyGroup.avatar.value();
		if (tinyGroup.groupType.value() == "eid")
		{
			groupData.type = 2;
		}
		else if("org" == tinyGroup.groupType.value())
		{
			groupData.type = 1;
		}
		else {
			groupData.type = 0;
		}

		groupData.avatarUrl = tinyGroup.avatarUrl.value();
		groupData.cantExit = tinyGroup.cantExit.value();
		groupData.isVSign = tinyGroup.isVSign.value();
		groupData.createrId = tinyGroup.createrId.value();
		groupData.groupId = tinyGroup.groupId.value();
		groupData.groupName = tinyGroup.groupName.value();
		groupData.level = tinyGroup.level.value();
		groupData.pinyin = tinyGroup.pinyin.value();
		groupData.server = tinyGroup.server.value();
		groupData.groupType = tinyGroup.groupType.value();
		return groupData;
	}

	void GroupMgrControl::DataConvert( const data::GroupUpdate data,model::GroupUpdate& outGroupUpdate )
	{
		if(data.extendProperties.isSet()){
			outGroupUpdate.extendProperties = data.extendProperties.value();
		}
		if(data.groupBackgroundURL.isSet()){
			outGroupUpdate.groupBackgroundURL = data.groupBackgroundURL.value();
		}
		if(data.groupBrief.isSet()){
			outGroupUpdate.groupBrief = data.groupBrief.value();
		}
		if(data.groupBulletin.isSet()){
			outGroupUpdate.groupBulletin = data.groupBulletin.value();
		}
		if(data.groupIcon.isSet()){
			outGroupUpdate.groupIcon = data.groupIcon.value();
		}
		if(data.groupMessageContentMode.isSet()){
			outGroupUpdate.groupMessageContentMode = data.groupMessageContentMode.value();
		}
		if(data.groupName.isSet()){
			outGroupUpdate.groupName = data.groupName.value();
		}
		if(data.groupSearch.isSet()){
			outGroupUpdate.groupSearch =data.groupSearch.value();
		}
	}

	void GroupMgrControl::DataConvert( CSharedPtr<model::TinyGroup>inTiny,CSharedPtr<data::TinyGroup>&outTiny )
	{
		outTiny->avatar = inTiny->avatar.value();
		outTiny->avatarUrl = inTiny->avatarUrl.value();
		outTiny->cantExit = inTiny->cantExit.value();
		outTiny->isVSign = inTiny->isVSign.value();
		outTiny->createrId = inTiny->createrId.value();
		outTiny->groupId = inTiny->groupId.value();
		outTiny->groupName = inTiny->groupName.value();
		outTiny->level = inTiny->level.value();
		outTiny->pinyin = inTiny->pinyin.value();
		outTiny->server = inTiny->server.value();
		if (inTiny->groupType.isSet() && !inTiny->groupType.value().empty())
		{
			if (inTiny->groupType.value() == "org")
			{
				outTiny->type = 1;
			}
			else if (inTiny->groupType.value() == "eid")
			{
				outTiny->type = 2;
			}
			else
			{
				outTiny->type = 0;
			}
		}
		else
		{
			outTiny->type = 0;
		}
	}

	model::Member  GroupMgrControl::DataConvert( data::Member &inMember )
	{
		model::Member outMember;
		outMember.avatar = inMember.avatar.value();
		outMember.avatarUrl = inMember.avatarUrl.value();
		outMember.extends = inMember.extends.value();
		outMember.gender = inMember.gender.value();
		outMember.groupId = inMember.groupId.value();
		outMember.id = inMember.id.value();
		outMember.isApp = inMember.isApp.value();
		outMember.memberType = inMember.memberType.value();
		outMember.name = inMember.name.value();
		outMember.pingyin = inMember.pingyin.value();
		outMember.remark = inMember.remark.value();
		outMember.team = inMember.team.value();
		outMember.thumbAvatar = inMember.thumbAvatar.value();
		outMember.thumbAvatarUrl = inMember.thumbAvatarUrl.value();
		outMember.timeZone = inMember.timeZone.value();
		return outMember;
	}

	void GroupMgrControl::DataConvert(const  model::Member &inMember,data::Member &outMember )
	{
		outMember.avatar = inMember.avatar.value();
		outMember.avatarUrl = inMember.avatarUrl.value();
		outMember.extends = inMember.extends.value();
		outMember.gender = inMember.gender.value();
		outMember.groupId = inMember.groupId.value();
		outMember.id = inMember.id.value();
		outMember.isApp = inMember.isApp.value();
		outMember.memberType = inMember.memberType.value();
		outMember.name = inMember.name.value();
		outMember.pingyin = inMember.pingyin.value();
		outMember.remark = inMember.remark.value();
		outMember.team = inMember.team.value();
		outMember.thumbAvatar = utils::GetHeadPath( inMember.isApp.value()==1?4:inMember.gender.value(),inMember.thumbAvatar.value());
		outMember.thumbAvatarUrl = inMember.thumbAvatarUrl.value();
		outMember.timeZone = inMember.timeZone.value();
		outMember.sector = inMember.sector.value();
	}

	void GroupMgrControl::DataConvert( CSharedPtr<model::Member>inMember,CSharedPtr<data::Member>outMember )
	{
		outMember->avatar = inMember->avatar.value();
		outMember->avatarUrl = inMember->avatarUrl.value();
		outMember->extends = inMember->extends.value();
		outMember->gender = inMember->gender.value();
		outMember->groupId = inMember->groupId.value();
		outMember->id = inMember->id.value();
		outMember->isApp = inMember->isApp.value();
		outMember->memberType = inMember->memberType.value();
		outMember->name = inMember->name.value();
		outMember->pingyin = inMember->pingyin.value();
		outMember->remark = inMember->remark.value();
		outMember->team = inMember->team.value();
		outMember->thumbAvatar = utils::GetHeadPath( inMember->isApp.value()==1?4:inMember->gender.value(),inMember->thumbAvatar.value());;
		outMember->thumbAvatarUrl = inMember->thumbAvatarUrl.value();
		outMember->timeZone = inMember->timeZone.value();
		outMember->sector = inMember->sector.value();
		if (outMember->remark.value().empty())
		{
			outMember->remark = inMember->name.value();
		}
	}

	bool GroupMgrControl::IsNullService()
	{
		return m_groupservice == CNull;
	}

	void GroupMgrControl::OnGroupRefreshCb( int8 type, const model::Group&group )
	{
		BEGIN;
		data::Group outGroup;
		DataConvert(group,outGroup);
		for (int i=0;i<m_groupRefreshCb.size();++i)
		{
			m_groupRefreshCb.at(i)(type,outGroup);
		}
		
		END;
	}

	void GroupMgrControl::OnTransferGroupCb( int64 creatorId, const std::string&creatorName, int64 groupId, const std::string&groupName )
	{
		BEGIN;
		m_transferGroupCb(creatorId,creatorName,groupId,groupName);
		END;
	}

	void GroupMgrControl::OnGrpMemInfoRefreshCb( int64 groupId, const model::Member&member )
	{
		BEGIN;
		data::Member outMem;
		//DataConvert(member,outMem);
		if (member.memberType.isSet())
		{
			outMem.memberType = member.memberType.value();
		}
		if (member.remark.isSet())
		{
			outMem.remark = member.remark.value();
		}
		if (member.thumbAvatar.isSet())
		{
			outMem.thumbAvatar = utils::GetHeadPath( member.gender.value(),member.thumbAvatar.value());
		}
		outMem.id = member.id.value();
		outMem.groupId = groupId;
		for (int i=0;i<m_groupMemInfoRefreshCb.size();++i)
		{
			m_groupMemInfoRefreshCb.at(i)(groupId,outMem);
		}
		
		END;
	}

	void GroupMgrControl::OnGrpMemRefreshCb( int type, int64 groupId, std::vector<SSharedPtr<model::Member> >&mems )
	{
		BEGIN;
		std::vector<CSharedPtr<data::Member> > outMems;
		for(int i=0;i<mems.size();++i){
			CSharedPtr<model::Member> inMem = mems.at(i);
			CSharedPtr<data::Member> outMem = CMakePtr<data::Member>();
			DataConvert(inMem,outMem);
			outMems.push_back(outMem);
		}
		m_groupMemRefreshCb(type,groupId,outMems);
		if(m_groupMemCountRefreshCb.find(groupId) != m_groupMemCountRefreshCb.end())
			m_groupMemCountRefreshCb[groupId](type, mems.size());
		END;
	}

	void GroupMgrControl::OnGetGrpMemListCb( service::ErrorInfo code, std::vector<CSharedPtr<model::Member> >& mems )
	{
		BEGIN;
		std::vector<CSharedPtr<data::Member> > outMems;
		for(int i=0;i<mems.size();++i){
			CSharedPtr<model::Member> inMem = mems.at(i);
			CSharedPtr<data::Member> outMem = CMakePtr<data::Member>();
			DataConvert(inMem,outMem);
			outMems.push_back(outMem);
		}
		m_getMemsListCb(code,outMems);
		END;
	}

	void GroupMgrControl::OnGroupListCb( std::vector<CSharedPtr<model::TinyGroup> >&groups )
	{
		BEGIN;
		std::vector<CSharedPtr<data::TinyGroup> >outGroups;
		for (int i=0;i<groups.size();++i)
		{
			CSharedPtr<model::TinyGroup> inTiny =  groups.at(i);
			CSharedPtr<data::TinyGroup> outTiny = CMakePtr<data::TinyGroup>();
			DataConvert(inTiny,outTiny);
			outGroups.push_back(outTiny);
		}
		std::sort(outGroups.begin(),outGroups.end(),GroupMgrControl::sort);
		m_groupListCb(outGroups);
		END;
	}

	void GroupMgrControl::OnGetMemberListCb( service::ErrorInfo code, std::vector<CSharedPtr<model::Member> >&mems )
	{
		BEGIN;
		AddLog(LOG_LEV_INFO,"================getGroupList size:%d",mems.size());

		std::vector<CSharedPtr<data::Member> > outMems;
		for(int i=0;i<mems.size();++i){
			CSharedPtr<model::Member> inMem = mems.at(i);
			CSharedPtr<data::Member> outMem = CMakePtr<data::Member>();
			DataConvert(inMem,outMem);
			outMems.push_back(outMem);
		}
		if (m_getMemsListCb != CNull){
			m_getMemsListCb(code, outMems);
			m_getMemsListCb = CNull;
		}
		END;
	}

	bool GroupMgrControl::sort( CSharedPtr<data::TinyGroup>& first,CSharedPtr<data::TinyGroup>&second )
	{
		return first->pinyin.value() > second->pinyin.value();
	}

	void GroupMgrControl::SetGroupMemCountCb(int64 id,CFunction<void(int, int64)>cb)
	{
		if(cb != CNull)
		{
			m_groupMemCountRefreshCb[id] = cb;
		}
		else
		{
			m_groupMemCountRefreshCb.erase(id);
		}
	}

	void GroupMgrControl::onSerDelFileResult(int code,std::vector<int64>& files)
	{
		m_groupfileDelResultCb[files.at(0)](code);
		m_groupfileDelResultCb.erase(files.at(0));
		return ;
	}

	int64 GroupMgrControl::uploadFile(data::UploadFileProperty &fileProperty, CFunction<void(int, int64, const std::string&)> cb, CFunction<void(int32, int32, const std::string&)> pro /*= SNull*/)
	{
		if(m_fileservice)
		{
			if(m_fileservice)
			{
				model::UploadFileProperty fileinfo;
				fileinfo.localid =fileProperty.localid;
				fileinfo.dirPath = fileProperty.dirPath;
				fileinfo.encryptKey =fileProperty.encryptKey;
				fileinfo.isP2p =fileProperty.isP2p;
				fileinfo.localPath =fileProperty.localPath;
				fileinfo.msg =fileProperty.msg;
				fileinfo.targetid =fileProperty.targetid;
				fileinfo.type = fileProperty.type;

				m_pFileUpResultCb[fileProperty.localid] = cb;
				m_pFileUpProgressCb[fileProperty.localid] = pro;
				return m_fileservice->uploadFile(fileinfo,
					std::bind(&GroupMgrControl::onSerUpFileResult, this, std::placeholders::_1,
					std::placeholders::_2,
					std::placeholders::_3,
					fileProperty.localid),
					std::bind(&GroupMgrControl::onSerUpfileProgress, this, std::placeholders::_1,
					std::placeholders::_2,
					std::placeholders::_3,fileProperty.localid));
			}
		}
	}

	void GroupMgrControl::getGroupMemberFromNet(int64 groupId, int64 memberID, CFunction<void(int, data::Member&)> cb)
	{
		if (m_groupservice){
			m_groupservice->getGroupMemberFromNet(groupId, memberID,
				CBind(&GroupMgrControl::onSerGetGroupMemberResult,this,
				std::placeholders::_1, std::placeholders::_2, cb));
		}
	}

	void GroupMgrControl::onSerGetGroupMemberResult(service::ErrorInfo code, model::Member& mem, GetGroupMemCb cb){
		data::Member memOut;
		DataConvert(mem, memOut);
		if (m_searchservice){
			model::Contact user;
			m_searchservice->getUserInfoSync(mem.id.value(), user);
			std::string json = user.entExtends.value();
			if (mem.entExtends.value().empty()){
				memOut.entExtends = json;
			}
			if (mem.remark.value().empty()){
				memOut.remark = user.name.value();
			}
			if (mem.thumbAvatar.value().empty()){
				memOut.thumbAvatar = user.thumbAvatar.value();
			}
		}
		if (cb){
			cb(code,memOut);
		}
	}
	void GroupMgrControl::onSerUpFileResult(int error, int64 targetid, const std::string& pjson,int64 localid)
	{
		if(m_pFileUpResultCb[localid])
		{
			m_pFileUpResultCb[localid](error, targetid, pjson);
			m_pFileUpResultCb.erase(localid);
		}
	}

	void GroupMgrControl::onSerUpfileProgress(int32 extra_req, int32 progress, const std::string& result,int64 localid)
	{
		if(m_pFileUpProgressCb[localid])
		{
			m_pFileUpProgressCb[localid](extra_req, progress, result);
			if(progress == 100)
				m_pFileUpProgressCb.erase(localid);
		}
	}

	void GroupMgrControl::onSerSetGroupInfoResult(int code)
	{
		if(m_groupNoticeResultCb)
			m_groupNoticeResultCb(code);
	}

	/**
	* \brief 取消文件上传或下载
	* @param[in] localId 文件的localId
	* @param[in] type  1.上传 2.下载 3.外部下载
	*/
	void GroupMgrControl::cancelTransfer(int64 localId, int type, CFunction<void(int)> cb)
	{
		m_groupfileCancelResultCb[localId] = cb;
		m_fileservice->cancelTransfer(localId, type, std::bind(&GroupMgrControl::onSerCancelFileResult, this, std::placeholders::_1, localId));
	}

	void GroupMgrControl::onSerCancelFileResult(int code, int64 filelocalid)
	{
		if (m_groupfileCancelResultCb.find(filelocalid) != m_groupfileCancelResultCb.end())
		{
			m_groupfileCancelResultCb[filelocalid](code);
			m_groupfileCancelResultCb.erase(filelocalid);
		}
	}

	void GroupMgrControl::getBatchMemberByID(int64 groupId, std::vector<int64>& memberIDs, CFunction<void(int, std::vector<CSharedPtr<data::Member> >&)> cb)
	{
		if (m_groupservice) {
			m_groupservice->getBatchMemberByID(groupId, memberIDs, std::bind(&GroupMgrControl::onSerGetBatchMemberByID,this,std::placeholders::_1, std::placeholders::_2,cb));
		}
	}
	void GroupMgrControl::onSerGetBatchMemberByID(service::ErrorInfo code, std::vector<SSharedPtr<model::Member>>&mems,GetBatchMemberByIDCb cb) {
		std::vector<CSharedPtr<data::Member>> outs;
		for (int i = 0; i < mems.size(); ++i) {
			CSharedPtr<data::Member> data = CMakePtr<data::Member>();
			DataConvert(mems.at(i), data);
			outs.push_back(data);
		}
		if (cb) {
			cb(code,outs);
		}
	}

	extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance(){
		IControl* instance = NULL;
		instance = new GroupMgrControl();
		return  instance;
	}
    extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(IControl* instance){
		if(NULL != instance){
			delete instance;
			instance = NULL;
		}
	}
}