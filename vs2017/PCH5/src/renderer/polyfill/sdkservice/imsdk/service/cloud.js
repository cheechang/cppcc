import Service from './service';

export default class CloudService extends Service {
  constructor() {
    super("cloud");
  }

  addFile(param, cb) {
    this._process("addFile", param, cb);
  }

  delFile(param, cb) {
    this._process("delFile", param, cb);
  }

  renameFile(param, cb) {
    this._process("renameFile", param, cb);
  }

  moveFile(param, cb) {
    this._process("moveFile", param, cb);
  }

  searchFiles(param, cb) {
    this._process("searchFiles", param, cb);
  }

  uploadFile(param, cb) {
    this._process("uploadFile", param, cb);
  }

  createTeam(param, cb) {
    this._process("createTeam", param, cb);
  }

  getTeams(param, cb) {
    this._process("getTeams", param, cb);
  }

  createPubDir(param, cb) {
    this._process("createPubDir", param, cb);
  }

  queryFloder(param, cb) {
    this._process("queryFloder", param, cb);
  }

  getPermission(param, cb) {
    this._process("getPermission", param, cb);
  }

  getRoleById(param, cb) {
    this._process("getRoleById", param, cb);
  }

  getRoles(param, cb) {
    this._process("getRoles", param, cb);
  }

  teamMembers(param, cb) {
    this._process("teamMembers", param, cb);
  }

  teamResetMember(param, cb) {
    this._process("teamResetMember", param, cb);
  }
}