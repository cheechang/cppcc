import Service from './service';

export default class EnterpriseService extends Service {
  constructor() {
    super("enterprise");
  }

  getVisibleOrgUsers(param, cb) {
    this._process("getVisibleOrgUsers", param, cb);
  }
}