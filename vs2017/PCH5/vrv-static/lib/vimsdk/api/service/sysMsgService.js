/**
 * @file      Manage the sysmsg's api.
 * @author    linpeiyuan <linpeiyuan@vrvmail.com.cn>
 * @date      2019.11.19
 * @copyright Beijing VRV Software Co.,Ltd
 * 
 */
class SysMsgService {
  constructor(client, utils) {
      this._sysmsg = client.sysMsgService();
      this._utils = utils;
  }
  
  adminRespToEnterGroup(param, cb) {
    return new Promise((resolve, reject)=>{
      this._sysmsg.adminRespToEnterGroup(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  respToAddBuddy(param, cb) {
    return new Promise((resolve, reject)=>{
      this._sysmsg.respToAddBuddy(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  userRespToEnterGroup(param, cb) {
    return new Promise((resolve, reject)=>{
      this._sysmsg.userRespToEnterGroup(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }
}
module.exports = SysMsgService;