/**
 * @file      Manage the rtc's api.
 * @author    linpeiyuan <linpeiyuan@vrvmail.com.cn>
 * @date      2019.11.19
 * @copyright Beijing VRV Software Co.,Ltd
 * 
 */
class RtcService {
  constructor(client, utils) {
      this._rtc = client.rtcService();
      this._utils = utils;
  }
  
  extraEventCall(param, cb) {
    return new Promise((resolve, reject)=>{
      this._rtc.extraEventCall(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  setConferenceInfo(param, cb) {
    return new Promise((resolve, reject)=>{
      this._rtc.setConferenceInfo(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  createChannel(param, cb) {
    return new Promise((resolve, reject)=>{
      this._rtc.createChannel(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  joinChannel(param, cb) {
    return new Promise((resolve, reject)=>{
      this._rtc.joinChannel(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  acceptOrReject(param, cb) {
    return new Promise((resolve, reject)=>{
      this._rtc.acceptOrReject(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  switchChannel(param, cb) {
    return new Promise((resolve, reject)=>{
      this._rtc.switchChannel(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  leaveChannel(param, cb) {
    return new Promise((resolve, reject)=>{
      this._rtc.leaveChannel(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  multiTalkRequest(param, cb) {
    return new Promise((resolve, reject)=>{
      this._rtc.multiTalkRequest(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  multiExtraRequest(param, cb) {
    return new Promise((resolve, reject)=>{
      this._rtc.multiExtraRequest(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getConferenceInfo(param, cb) {
    return new Promise((resolve, reject)=>{
      this._rtc.getConferenceInfo(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getStunServer(param, cb) {
    return new Promise((resolve, reject)=>{
      this._rtc.getStunServer(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getStunServerList(param, cb) {
    return new Promise((resolve, reject)=>{
      this._rtc.getStunServerList(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getMultiServerSync(param, cb) {
    return this._rtc.getMultiServerSync();
    // return new Promise((resolve, reject)=>{
    //   this._rtc.getMultiServerSync(param, resp => {
    //     this._utils.makeCallBack(resp, cb, resolve, reject);
    //   });
    // });
  }

  regChannelEventCb(param, cb) {
    return new Promise((resolve, reject)=>{
      this._rtc.regChannelEventCb(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  regExtraEventNotifyCb(param, cb) {
    return new Promise((resolve, reject)=>{
      this._rtc.regExtraEventNotifyCb(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  regMultiEventCb(param, cb) {
    return new Promise((resolve, reject)=>{
      this._rtc.regMultiEventCb(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }
}
module.exports = RtcService;