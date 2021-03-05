/**
 * @file      Manage the search's api.
 * @author    linpeiyuan <linpeiyuan@vrvmail.com.cn>
 * @date      2019.11.19
 * @copyright Beijing VRV Software Co.,Ltd
 * 
 */
class SearchService {
  constructor(client, utils) {
      this._search = client.searchService();
      this._utils = utils;
  }

  getGroupInfo(param, cb) {
    return new Promise((resolve, reject)=>{
      this._search.getGroupInfo(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getUserInfo(param, cb) {
    return new Promise((resolve, reject)=>{
      this._search.getUserInfo(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getUserInfoByScene(param, cb) {
    return new Promise((resolve, reject)=>{
      this._search.getUserInfoByScene(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getUserInfoEx(param, cb) {
    return new Promise((resolve, reject)=>{
      this._search.getUserInfoEx(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getUserInfoSync(param, cb) {
    return new Promise((resolve, reject)=>{
      this._search.getUserInfoEx(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  groupSearchMember(param, cb) {
    return new Promise((resolve, reject)=>{
      this._search.groupSearchMember(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  searchDetailMessage(param, cb) {
    return new Promise((resolve, reject)=>{
      this._search.searchDetailMessage(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  searchFromLocal(param, cb) {
    return new Promise((resolve, reject)=>{
      this._search.searchFromLocal(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  searchFromNet(param, cb) {
    return new Promise((resolve, reject)=>{
      this._search.searchFromNet(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  searchMessage(param, cb) {
    return new Promise((resolve, reject)=>{
      this._search.searchMessage(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }
  
}
module.exports = SearchService;