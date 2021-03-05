/**
 * @file      Manage the group's api.
 * @author    linpeiyuan <linpeiyuan@vrvmail.com.cn>
 * @date      2019.11.19
 * @copyright Beijing VRV Software Co.,Ltd
 * 
 */
class GroupService {
  constructor(client, utils) {
      this._group = client.groupService();
      this._utils = utils;
  }
  
  createGroup(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.createGroup(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  addGroup(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.addGroup(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  setGroupSet(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.setGroupSet(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getGroupSet(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.getGroupSet(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  transferGroup(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.transferGroup(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  removeGroup(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.removeGroup(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getGroupInfo(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.getGroupInfo(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  setGroupInfo(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.setGroupInfo(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getGroupList(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.getGroupList(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getGroupOnlineStatus(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.getGroupOnlineStatus(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  setGroupExtraInfo(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.setGroupExtraInfo(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getGroupMsgRemindType(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.getGroupMsgRemindType(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  setGroupMsgRemindType(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.setGroupMsgRemindType(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getGroupBeepTone(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.getGroupBeepTone(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  setGroupBeepTone(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.setGroupBeepTone(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getGroupAnnouncementList(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.getGroupAnnouncementList(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  addGroupAnnouncement(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.getGroupAnnouncementList(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  checkGroupAnnouncementExist(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.checkGroupAnnouncementExist(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  delGroupAnnouncement(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.delGroupAnnouncement(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getMemberList(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.getMemberList(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getMemberListFromNet(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.getMemberListFromNet(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getMemberInfo(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.getMemberInfo(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  setMemberInfo(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.setMemberInfo(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  inviteMember(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.inviteMember(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  isInGroup(param) {
    return this._group.isInGroup(param);
  }

  isInGroupAsync(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.isInGroup(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  removeMembers(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.removeMembers(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  removeMember(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.removeMember(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getPersonalGroupImg(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.getPersonalGroupImg(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  setPersonalGroupImg(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.setPersonalGroupImg(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getGroupFileList(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.getGroupFileList(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  deleteGroupFile(param, cb) {
    return new Promise((resolve, reject)=>{
      this._group.deleteGroupFile(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  regGetGrpMemListCb(param, cb) {
    this._group.regGetGrpMemListCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }

  regGroupBackImgUpdateCb(param, cb) {
    this._group.regGroupBackImgUpdateCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }

  regGroupHeadImgUpdateCb(param, cb) {
    this._group.regGroupHeadImgUpdateCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }

  regGroupListCb(param, cb) {
    this._group.regGroupListCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }

  regGroupRefreshCb(param, cb) {
    this._group.regGroupRefreshCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }

  regGrpMemInfoRefreshCb(param, cb) {
    this._group.regGrpMemInfoRefreshCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }

  regGrpMemRefreshCb(param, cb) {
    this._group.regGrpMemRefreshCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }

  regMemberHeadImgUpdateCb(param, cb) {
    this._group.regMemberHeadImgUpdateCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }

  regTransferGroupCb(param, cb) {
    this._group.regTransferGroupCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }
}
module.exports = GroupService;