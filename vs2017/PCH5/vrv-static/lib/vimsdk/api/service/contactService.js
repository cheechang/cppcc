/**
 * @file      Manage the contact's api.
 * @author    linpeiyuan <linpeiyuan@vrvmail.com.cn>
 * @date      2019.11.19
 * @copyright Beijing VRV Software Co.,Ltd
 * 
 */
class ContactService {
    constructor(client, utils) {
        this._contact = client.contactService();
        this._utils = utils;
    }

    getLocalPhoneBook() {
      return this._contact.getLocalPhoneBook();
    }
  
    getLocalPhoneBookAsync() {
      return new Promise((resolve, reject)=>{
        let resp = this._contact.getLocalPhoneBook();
        resolve(resp);
      });
    }

    addLocalPhoneBook(param) {
      return this._contact.addLocalPhoneBook(param);
    }
  
    addLocalPhoneBookAsync(param) {
      return new Promise((resolve, reject)=>{
        let resp = this._contact.addLocalPhoneBook(param);
        resolve(resp);
      });
    }

    deleteLocalPhoneBook(param) {
      return this._contact.deleteLocalPhoneBook(param);
    }
  
    deleteLocalPhoneBookAsync(param) {
      return new Promise((resolve, reject)=>{
        let resp = this._contact.deleteLocalPhoneBook(param);
        resolve(resp);
      });
    }

    updateLocalPhoneBook(param) {
      return this._contact.updateLocalPhoneBook(param);
    }
  
    updateLocalPhoneBookAsync(param) {
      return new Promise((resolve, reject)=>{
        let resp = this._contact.updateLocalPhoneBook(param);
        resolve(resp);
      });
    }

    postContact(param, cb) {
      return new Promise((resolve, reject)=>{
        this._contact.postContact(param, resp => {
          this._utils.makeCallBack(resp, cb, resolve, reject);
        });
      });
    }

    getContactList(param, cb) {
      return new Promise((resolve, reject)=>{
        this._contact.getContactList(param, resp => {
          this._utils.makeCallBack(resp, cb, resolve, reject);
        });
      });
    }

    getContactInfo(param, cb) {
      return new Promise((resolve, reject)=>{
        this._contact.getContactInfo(param, resp => {
          this._utils.makeCallBack(resp, cb, resolve, reject);
        });
      });
    }

    getBuddyInfoFromNet(param, cb) {
      return new Promise((resolve, reject)=>{
        this._contact.getBuddyInfoFromNet(param, resp => {
          this._utils.makeCallBack(resp, cb, resolve, reject);
        });
      });
    }

    getContactOnline(param, cb) {
      return new Promise((resolve, reject)=>{
        this._contact.getContactOnline(param, resp => {
          this._utils.makeCallBack(resp, cb, resolve, reject);
        });
      });
    }

    getVerifyType(param, cb) {
      return new Promise((resolve, reject)=>{
        this._contact.getVerifyType(param, resp => {
          this._utils.makeCallBack(resp, cb, resolve, reject);
        });
      });
    }

    addContact(param, cb) {
      return new Promise((resolve, reject)=>{
        this._contact.addContact(param, resp => {
          this._utils.makeCallBack(resp, cb, resolve, reject);
        });
      });
    }

    addContactNoVerify(param, cb) {
      return new Promise((resolve, reject)=>{
        this._contact.addContactNoVerify(param, resp => {
          this._utils.makeCallBack(resp, cb, resolve, reject);
        });
      });
    }

    updateContactInfo(param, cb) {
      return new Promise((resolve, reject)=>{
        this._contact.updateContactInfo(param, resp => {
          this._utils.makeCallBack(resp, cb, resolve, reject);
        });
      });
    }

    contactIsBuddy(param, cb) {
      return this._contact.contactIsBuddy(param, resp=>{
        this._utils.makeCallBack(resp, cb)
      });
    }

    contactIsBuddyAsync(param, cb) {
      return new Promise((resolve, reject)=>{
        this._contact.contactIsBuddy(param, resp => {
          this._utils.makeCallBack(resp, cb, resolve, reject);
        });
      });
    }

    removeContact(param, cb) {
      return new Promise((resolve, reject)=>{
        this._contact.removeContact(param, resp => {
          this._utils.makeCallBack(resp, cb, resolve, reject);
        });
      });
    }

    oneWayBuddy() {
      return this._contact.oneWayBuddy();
    }
  
    oneWayBuddyAsync() {
      return new Promise((resolve, reject)=>{
        let resp = this._config.oneWayBuddy();
        resolve(resp);
      });
    }

    queryExtendedField(param, cb) {
      return new Promise((resolve, reject)=>{
        this._contact.queryExtendedField(param, resp => {
          this._utils.makeCallBack(resp, cb, resolve, reject);
        });
      });
    }

    queryExtendedFieldSync(param, cb) {
      return new Promise((resolve, reject)=>{
        this._contact.queryExtendedFieldSync(param, resp => {
          this._utils.makeCallBack(resp, cb, resolve, reject);
        });
      });
    }

    canMakeVerifyCode(param,cb) {
      return new Promise((resolve, reject)=>{
        this._contact.canMakeVerifyCode(resp => {
          this._utils.makeCallBack(resp, cb, resolve, reject);
        });
      });
    }

    makeVerifyCode(param, cb) {
      return new Promise((resolve, reject)=>{
        this._contact.makeVerifyCode(param, resp => {
          this._utils.makeCallBack(resp, cb, resolve, reject);
        });
      });
    }

    getUserIdByInviteCode(param, cb) {
      return new Promise((resolve, reject)=>{
        this._contact.getUserIdByInviteCode(param, resp => {
          this._utils.makeCallBack(resp, cb, resolve, reject);
        });
      });
    }

    isInviteCode(param) {
      return this._contact.isInviteCode(param);
    }
  
    isInviteCodeAsync(param) {
      return new Promise((resolve, reject)=>{
        let resp = this._contact.isInviteCode(param);
        resolve(resp);
      });
    }

    verifyCodeValid(param, cb) {
      return new Promise((resolve, reject)=>{
        this._contact.verifyCodeValid(param, resp => {
          this._utils.makeCallBack(resp, cb, resolve, reject);
        });
      });
    }

    verifyUserInfoField(param, cb) {
      return new Promise((resolve, reject)=>{
        this._contact.verifyUserInfoField(param, resp => {
          this._utils.makeCallBack(resp, cb, resolve, reject);
        });
      });
    }

    getBlackList(param, cb) {
      return new Promise((resolve, reject)=>{
        this._contact.getBlackList(param, resp => {
          this._utils.makeCallBack(resp, cb, resolve, reject);
        });
      });
    }

    addBlackList(param, cb) {
      return new Promise((resolve, reject)=>{
        this._contact.addBlackList(param, resp => {
          this._utils.makeCallBack(resp, cb, resolve, reject);
        });
      });
    }

    removeBlackList(param, cb) {
      return new Promise((resolve, reject)=>{
        this._contact.removeBlackList(param, resp => {
          this._utils.makeCallBack(resp, cb, resolve, reject);
        });
      });
    }

    regBuddyListCb(param, cb) {
      this._contact.regBuddyListCb(param, resp => {
        this._utils.makeCallBack(resp, cb);
      });
    }

    regContactBackImgUpdateCb(param, cb) {
      this._contact.regContactBackImgUpdateCb(param, resp => {
        this._utils.makeCallBack(resp, cb);
      });
    }

    regContactHeadImgUpdateCb(param, cb) {
      this._contact.regContactHeadImgUpdateCb(param, resp => {
        this._utils.makeCallBack(resp, cb);
      });
    }

    regContactHeadImgUpdateCb(param, cb) {
      this._contact.regContactHeadImgUpdateCb(param, resp => {
        this._utils.makeCallBack(resp, cb);
      });
    }

    regContactOnline(param, cb) {
      this._contact.regContactOnline(param, resp => {
        this._utils.makeCallBack(resp, cb);
      });
    }

    regOperateContactCb(param, cb) {
      this._contact.regOperateContactCb(param, resp => {
        this._utils.makeCallBack(resp, cb);
      });
    }

    regOperateBuddyCb(param, cb) {
      this._contact.regOperateBuddyCb(param, resp => {
        this._utils.makeCallBack(resp, cb);
      });
    }

    regPresentCb(param, cb) {
      this._contact.regPresentCb(param, resp => {
        this._utils.makeCallBack(resp, cb);
      });
    }
}
module.exports = ContactService;