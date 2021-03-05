/**
 * @file      Manage the sysmsg's api.
 * @author    lixin <lixin1@vrvmail.com.cn>
 * @date      2019.11.22
 * @copyright Beijing VRV Software Co.,Ltd
 * 
 */
class CloudService {
  constructor(client, utils) {
      this._cloud = client.cloudService();
      this._utils = utils;
  }
  
  getCloudFileInfo(param, cb) {
    return new Promise((resolve, reject)=>{
      this._cloud.getCloudFileInfo(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  addFile(param, cb) {
    return new Promise((resolve, reject)=>{
      this._cloud.addFile(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }
  delFile(param, cb) {
    return new Promise((resolve, reject)=>{
      this._cloud.delFile(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }
  renameFile(param, cb) {
    return new Promise((resolve, reject)=>{
      this._cloud.renameFile(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  moveFile(param, cb) {
    return new Promise((resolve, reject)=>{
      this._cloud.moveFile(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  copyFile(param, cb) {
    return new Promise((resolve, reject)=>{
      this._cloud.copyFile(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  searchFiles(param, cb) {
    return new Promise((resolve, reject)=>{
      this._cloud.searchFiles(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  uploadFile(param, cb,proCb) {
    return new Promise((resolve, reject)=>{
      this._cloud.uploadFile(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      },pro=>{
        this._utils.makeCallBack(pro, proCb);
      });
    });
  }

  createTeam(param, cb) {
    return new Promise((resolve, reject)=>{
      this._cloud.createTeam(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getTeams(param, cb) {
    return new Promise((resolve, reject)=>{
      this._cloud.getTeams(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  createPubDir(param, cb) {
    return new Promise((resolve, reject)=>{
      this._cloud.createPubDir(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  queryFloder(param, cb) {
    return new Promise((resolve, reject)=>{
      this._cloud.queryFloder(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  querySubFolders(param, cb) {
    return new Promise((resolve, reject)=>{
      this._cloud.querySubFolders(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  queryFolderByParam(param, cb) {
    return new Promise((resolve, reject)=>{
      this._cloud.queryFolderByParam(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getPermission(param, cb) {
    return new Promise((resolve, reject)=>{
      this._cloud.getPermission(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getRoleById(param, cb) {
    return new Promise((resolve, reject)=>{
      this._cloud.getRoleById(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getRoles(param, cb) {
    return new Promise((resolve, reject)=>{
      this._cloud.getRoles(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  teamMembers(param, cb) {
    return new Promise((resolve, reject)=>{
      this._cloud.teamMembers(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  teamResetMember(param, cb) {
    return new Promise((resolve, reject)=>{
      this._cloud.teamResetMember(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }
}
module.exports = CloudService;