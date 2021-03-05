/**
 * @file      Manage the enterprise's api.
 * @author    linpeiyuan <linpeiyuan@vrvmail.com.cn>
 * @date      2019.11.19
 * @copyright Beijing VRV Software Co.,Ltd
 * 
 */
class EnterpriseService {
  constructor(client, utils) {
      this._enterprise = client.enterpriseService();
      this._utils = utils;
  }
  
  addNote(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.addNote(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  addNotebook(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.addNotebook(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  addNoteEntry(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.addNoteEntry(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  addRoomMember(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.addRoomMember(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  changRoomIcon(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.changRoomIcon(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  changRoomName(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.changRoomName(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  editNote(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.editNote(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  delNote(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.delNote(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  editNotebook(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.editNotebook(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  editNoteEntry(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.editNoteEntry(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  deleRoom(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.deleRoom(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  delNotebook(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.delNotebook(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  delNotebookById(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.delNotebookById(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  delNoteEntry(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.delNoteEntry(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  delRoomMember(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.delRoomMember(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getAllRoom(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.getAllRoom(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getApTask(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.getApTask(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getBodyTask(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.getBodyTask(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getHistoryTask(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.getHistoryTask(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getMsgCountByTargetID(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.getMsgCountByTargetID(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getMsgTopNAtGroup(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.getMsgTopNAtGroup(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getMsgTopNGroup(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.getMsgTopNGroup(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getMsgTopNSession(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.getMsgTopNSession(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getNote(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.getNote(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getNotebook(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.getNotebook(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getNoteEntry(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.getNoteEntry(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getOrgInfo(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.getOrgInfo(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getOrgInfos(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.getOrgInfos(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getOrgInfoSync(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.getOrgInfos(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getRecvMsg(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.getRecvMsg(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getRecvTask(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.getRecvTask(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getRoom(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.getRoom(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getVisibleOrgUsers(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.getVisibleOrgUsers(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getVisibleOrgUsersSync(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.getVisibleOrgUsersSync(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  queryEntUserAll(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.queryEntUserAll(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  queryEntUserOneById(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.queryEntUserOneById(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  queryEntUserOneByName(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.queryEntUserOneByName(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  createRoom(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.createRoom(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  archiveNote(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.archiveNote(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  checkNoteEnkey(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.checkNoteEnkey(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  decryptNotebook(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.decryptNotebook(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  encryptNotebook(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.encryptNotebook(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  finishTask(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.finishTask(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  orgAndUserSearch(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.orgAndUserSearch(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  queryEnterpriseUserlist(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.queryEnterpriseUserlist(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  recoveryTask(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.recoveryTask(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  regEntUpdateFinishCb(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.regEntUpdateFinishCb(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  regGetAllRoomsCb(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.regGetAllRoomsCb(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  regOrgMemHeadImgUpdateCb(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.regOrgMemHeadImgUpdateCb(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  searchNote(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.searchNote(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  searchNoteEntry(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.searchNoteEntry(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  sendTaskMsg(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.sendTaskMsg(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  setReadTask(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.setReadTask(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  topNote(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.topNote(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  topRoom(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.topRoom(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  topTask(param, cb) {
    return new Promise((resolve, reject)=>{
      this._enterprise.topTask(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }
}
module.exports = EnterpriseService;