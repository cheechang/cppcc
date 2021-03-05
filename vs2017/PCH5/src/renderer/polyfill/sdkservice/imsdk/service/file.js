import Service from './service';

export default class FileService extends Service {
  constructor() {
    super("file");
  }

  fileOperate(param, cb) {
    this._process("fileOperate", param, cb);
    return true;
  }

  getFileList(param, cb) {
    this._process("getFileList", param, cb);
  }

  getFilesInfo(param, cb) {
    this._process("getFilesInfo", param, cb);
  }

  decrypt(param, cb) {
    this._process("decrypt", param, cb);
  }

  encryptFile(param, cb) {
    this._process("encryptFile", param, cb);
  }

  compress(param, cb) {
    this._process("compress", param, cb);
    return true;
  }

  uncompress(param, cb) {
    this._process("uncompress", param, cb);
    return true;
  }

  queryFileValid(param, cb) {
    this._process("queryFileValid", param, cb);
  }

  delayFiles(param, cb) {
    this._process("delayFiles", param, cb);
  }

  downloadFile(param, cb, pro)  {
    //  TODO: 
    let progress = {extra: 1, progress: 50, info: ""};
    pro(progress);
    this._process("downloadFile", param, resp => {
      progress.progress = 100;
      pro(progress);
      cb(resp);
    });
  }

  downloadImage(param, cb, pro) {
    //  TODO: 
    let progress = { extra: 1, progress: 50, info: "" };
    pro(progress);
    this._process("downloadImage", param, resp => {
      progress.progress = 100;
      pro(progress);
      cb(resp);
    });
  }

  downloadNineBoxImage(param, cb, pro) {
    //  TODO: 
    let progress = { extra: 1, progress: 50, info: "" };
    pro(progress);
    this._process("downloadNineBoxImage", param, resp => {
      progress.progress = 100;
      pro(progress);
      cb(resp);
    });
  }

  uploadFile(param, cb, pro) {
    //  TODO: 
    let progress = { extra: 1, progress: 50, info: "" };
    pro(progress);
    this._process("uploadFile", param, resp => {
      progress.progress = 100;
      pro(progress);
      cb(resp);
    });
    return "";
  }

  uploadImage(param, cb, pro) {
    //  TODO: 
    let progress = { extra: 1, progress: 50, info: "" };
    pro(progress);
    this._process("uploadImage", param, resp => {
      progress.progress = 100;
      pro(progress);
      cb(resp);
    });
  }

  uploadShareImage(param, cb, pro) {
    //  TODO: 
    let progress = { extra: 1, progress: 50, info: "" };
    pro(progress);
    this._process("uploadShareImage", param, resp => {
      progress.progress = 100;
      pro(progress);
      cb(resp);
    });
  }

  downloadExternalFile(param, cb) {
    this._process("downloadExternalFile", param, cb);
  }


  uploadAvatar(param, cb) {
    this._process("uploadAvatar", param, cb);
  }

  uploadBackground(param, cb) {
    this._process("uploadBackground", param, cb);
  }

  isTransmitting(param, cb) {
    this._process("isTransmitting", param, cb);
    return true;
  }

  isTransmittingInTarget(param, cb) {
    this._process("isTransmittingInTarget", param, cb);
    return true;
  }

  cancelAllTransfer(param, cb) {
    this._process("cancelAllTransfer", param, cb);
  }

  cancelTargetTransfer(param, cb) {
    this._process("cancelTargetTransfer", param, cb);
    return true;
  }

  cancelTransfer(param, cb) {
    this._process("cancelTransfer", param, cb);
  }

  getNameByUrl(param, cb) {
    this._process("getNameByUrl", param, cb);
  }

  getAlreadyDownload(param, cb) {
    this._process("getAlreadyDownload", param, cb);
  }

  checkUrlValid(param, cb) {
    this._process("checkUrlValid", param, cb);
  }

  getMarkFromImageFFT(param, cb) {
    this._process("getMarkFromImageFFT", param, cb);
    return 0;
  }

  getMarkFromImageSimple(param, cb) {
    this._process("getMarkFromImageSimple", param, cb);
    return 0;
  }

  putMarkOnImageFFT(param, cb) {
    this._process("putMarkOnImageFFT", param, cb);
    return 0;
  }

  putMarkOnImageSimple(param, cb) {
    this._process("putMarkOnImageSimple", param, cb);
    return 0;
  }

  putShowMarkOnImage(param, cb) {
    this._process("putShowMarkOnImage", param, cb);
    return 0;
  }

  reduceImage(param, cb) {
    this._process("reduceImage", param, cb);
    return 0;
  }
}