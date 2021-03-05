import Service from './service';

export default class ContactService extends Service {
  constructor() {
    super("contact");
  }

  getLocalPhoneBook() {
    //  TODO:
  }

  addLocalPhoneBook(param) {
    //  TODO:
  }

  deleteLocalPhoneBook(param) {
    //  TODO:
  }

  updateLocalPhoneBook(param) {
    //  TODO:
  }

  postContact(param, cb) {
    this._process("postContact", param, cb);
  }

  getContactList(param, cb) {
    this._process("getContactList", param, cb);
  }

  getContactInfo(param, cb) {
    this._process("getContactInfo", param, cb);
  }

  getBuddyInfoFromNet(param, cb) {
    this._process("getBuddyInfoFromNet", param, cb);
  }

  getContactOnline(param, cb) {
    this._process("getContactOnline", param, cb);
  }

  getVerifyType(param, cb) {
    this._process("getVerifyType", param, cb);
  }

  addContact(param, cb) {
    this._process("addContact", param, cb);
  }

  addContactNoVerify(param, cb) {
    this._process("addContactNoVerify", param, cb);
  }

  updateContactInfo(param, cb) {
    this._process("updateContactInfo", param, cb);
  }

  contactIsBuddy(param, cb) {
    this._process("contactIsBuddy", param, cb);
  }

  removeContact(param, cb) {
    this._process("removeContact", param, cb);
  }

  oneWayBuddy() {
    //  TODO:
  }

  queryExtendedField(param, cb) {
    this._process("queryExtendedField", param, cb);
  }

  queryExtendedFieldSync(param, cb) {
    this._process("queryExtendedFieldSync", param, cb);
  }

  canMakeVerifyCode(cb) {
    this._process("canMakeVerifyCode", null, cb);
  }
  
  makeVerifyCode(param, cb) {
    this._process("makeVerifyCode", param, cb);
  }

  getUserIdByInviteCode(param, cb) {
    this._process("getUserIdByInviteCode", param, cb);
  }

  isInviteCode(param) {
    //  todo
  }

  verifyCodeValid(param, cb) {
    this._process("verifyCodeValid", param, cb);
  }

  getBlackList(param, cb) {
    this._process("getBlackList", param, cb);
  }

  addBlackList(param, cb) {
    this._process("addBlackList", param, cb);
  }

  removeBlackList(param, cb) {
    this._process("removeBlackList", param, cb);
  }

  regBuddyListCb(param, cb) {
    this._process("regBuddyListCb", param, cb);
  }

  regContactBackImgUpdateCb(param, cb) {
    this._process("regContactBackImgUpdateCb", param, cb);
  }

  regContactHeadImgUpdateCb(param, cb) {
    this._process("regContactHeadImgUpdateCb", param, cb);
  }

  regContactHeadImgUpdateCb(param, cb) {
    this._process("regContactHeadImgUpdateCb", param, cb);
  }

  regContactOnline(param, cb) {
    this._process("regContactOnline", param, cb);
  }

  regContactOnlineChanged(param, cb) {
    this._process("regContactOnlineChanged", param, cb);
  }

  regOperateBuddyCb(param, cb) {
    this._process("regOperateBuddyCb", param, cb);
  }

  regPresentCb(param, cb) {
    this._process("regPresentCb", param, cb);
  }
}