/**
 * @file      Manages the file's api.
 * @author    lixin <lixin1@vrvmail.com.cn>
 * @date      2019.11.19
 * @copyright Beijing VRV Software Co.,Ltd
 */
class FileService {
  constructor(client, utils) {
      this._file = client.fileService();
      this._utils = utils;
  }
  //文件/文件夹操作[同步]
  fileOperate(param, cb) {
    return this._file.fileOperate(param, resp=>{
      this._utils.makeCallBack(resp, cb)
    });
  }
  //文件/文件夹操作[异步]
  fileOperateAsync(param) {
    return new Promise((resolve, reject)=>{
      let result = this._file.fileOperate(param, resp=>{
        this._utils.makeCallBack(resp, null, resolve, reject)
      });
      if(typeof(result) !== undefined) {
        resolve(result);
      }
    })
  }
  //获取文件列表
  getFileList(param,cb) {
    return new Promise((resolve, reject)=>{
      this._file.getFileList(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //获取文件信息
  getFilesInfo(param,cb) {
    return new Promise((resolve, reject)=>{
      this._file.getFilesInfo(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //解密文件
  decryptFile(param,cb) {
    return new Promise((resolve, reject)=>{
      this._file.decryptFile(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //加密文件[异步]
  encryptFileAsync(param) {
    return new Promise((resolve, reject)=>{
      this._file.encryptFile(param, resp => {
        this._utils.makeCallBack(resp, null, resolve, reject);
      });
    })
  }
  //加密文件[同步]
  encryptFile(param,cb) {
    return this._file.encryptFile(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }
  //压缩文件[同步]
  compress(param) {
    return this._file.compress(param);
  }
  //压缩文件[异步]
  compressAsync(param) {
    return new Promise((resolve, reject)=>{
      let result = this._file.compress(param);
      resolve(result);
    })
  }
  //解压文件[同步]
  uncompressAsync(param) {
    return this._file.uncompress(param);
  }
  //解压文件[异步]
  uncompressAsync(param) {
    return new Promise((resolve, reject)=>{
      let result = this._file.uncompress(param);
      resolve(result);
    })
  }
  //查询文件是否过期
  queryFileValid(param,cb) {
    return new Promise((resolve, reject)=>{
      this._file.queryFileValid(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //延期文件的有效时长
  delayFiles(param,cb) {
    return new Promise((resolve, reject)=>{
      this._file.delayFiles(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //下载文件
  downloadFile(param,cb,pro) {
    return this._file.downloadFile(param, resp => {
      this._utils.makeCallBack(resp, cb);
      },proResp=>{
        this._utils.makeCallBack(proResp, pro);
    });
  }
  //下载文件[异步]
  downloadFileAsync(param,cb,pro) {
    return new Promise((resolve, reject)=>{
      let localId = this._file.downloadFile(param, resp => {
          this._utils.makeCallBack(resp, null, resolve, reject);
        },proResp=>{
          this._utils.makeCallBack(proResp, pro);
      });
      cb(localId);
    })
  }
  //下载外部文件
  downloadExternalFile(param,cb,pro) {
    return new Promise((resolve, reject)=>{
      this._file.downloadExternalFile(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      },proResp=>{
        this._utils.makeCallBack(proResp, pro);
      });
    })
  }
  //下载图片
  downloadImage(param,cb,pro) {
    return new Promise((resolve, reject)=>{
      this._file.downloadImage(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      },proResp=>{
        this._utils.makeCallBack(proResp, pro);
      });
    })
  }
  //下载九宫格图片
  downloadNineBoxImage(param,cb,pro) {
    return new Promise((resolve, reject)=>{
      this._file.downloadNineBoxImage(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      },proResp=>{
        this._utils.makeCallBack(proResp, pro);
      });
    })
  }
  //上传文件
  uploadFile(param,cb,pro) {
    return this._file.uploadFile(param, resp => {
      this._utils.makeCallBack(resp, cb);
      },proResp=>{
        this._utils.makeCallBack(proResp, pro);
    });
  }
  //上传文件[异步]
  uploadFileAsync(param,cb,pro) {
    return new Promise((resolve, reject)=>{
      let localId = this._file.uploadFile(param, resp => {
          this._utils.makeCallBack(resp, null, resolve, reject);
        },proResp=>{
          this._utils.makeCallBack(proResp, pro);
      });
      cb(localId);
    })
  }
  //上传图片
  uploadImage(param,cb,pro) {
    return new Promise((resolve, reject)=>{
      this._file.uploadImage(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      },proResp=>{
        this._utils.makeCallBack(proResp, pro);
      });
    })
  }
  //上传分享图片
  uploadShareImage(param,cb,pro) {
    return new Promise((resolve, reject)=>{
      this._file.uploadShareImage(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      },proResp=>{
        this._utils.makeCallBack(proResp, pro);
      });
    })
  }
  //上传头像
  uploadAvatar(param,cb) {
    return new Promise((resolve, reject)=>{
      this._file.uploadAvatar(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //上传背景图
  uploadBackground(param,cb) {
    return new Promise((resolve, reject)=>{
      this._file.uploadBackground(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //判断是否有文件在传输[同步]
  isTransmitting(param) {
    return this._file.isTransmitting(param);
  }
  //判断是否有文件在传输[异步]
  isTransmittingAsync(param) {
    return new Promise((resolve, reject)=>{
      let result = this._file.isTransmitting(param);
      resolve(result);
    })
  }
  //判断个人或群是否有文件在传输[同步]
  isTransmittingInTarget(param) {
    return this._file.isTransmittingInTarget(param);
  }
  //判断个人或群是否有文件在传输[异步]
  isTransmittingInTargetAsync(param) {
    return new Promise((resolve, reject)=>{
      let result = this._file.isTransmittingInTarget(param);
      resolve(result);
    })
  }
  //取消所有文件传输
  cancelAllTransfer(param,cb) {
    return new Promise((resolve, reject)=>{
      this._file.cancelAllTransfer(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //取消个人或群的所有文件传输[同步]
  cancelTargetTransfer(param) {
    return this._file.cancelTargetTransfer(param);
  }
  //取消个人或群的所有文件传输[异步]
  cancelTargetTransfer(param) {
    return new Promise((resolve, reject)=>{
      let result = this._file.cancelTargetTransfer(param);
      resolve(result);
    })
  }
  //取消上传或下载
  cancelTransfer(param,cb) {
    return new Promise((resolve, reject)=>{
      this._file.cancelTransfer(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //获取本地唯一文件名
  getNameByUrl(param,cb) {
    return new Promise((resolve, reject)=>{
      this._file.getNameByUrl(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //获取本地已下载大小
  getAlreadyDownload(param,cb) {
    return new Promise((resolve, reject)=>{
      this._file.getAlreadyDownload(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //检查URL是否有效
  checkUrlValid(param,cb) {
    return new Promise((resolve, reject)=>{
      this._file.checkUrlValid(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //获取水印图的频谱水印[同步]
  getMarkFromImageFFT(param) {
    return this._file.getMarkFromImageFFT(param);
  }
  //获取水印图的频谱水印[异步]
  getMarkFromImageFFTAsync(param) {
    return new Promise((resolve, reject)=>{
      let result = this._file.getMarkFromImageFFT(param);
      resolve(result);
    })
  }
  //获取水印图的ID水印[同步]
  getMarkFromImageSimple(param) {
    return this._file.getMarkFromImageSimple(param);
  }
  //获取水印图的ID水印[异步]
  getMarkFromImageSimpleAsync(param) {
    return new Promise((resolve, reject)=>{
      let result = this._file.getMarkFromImageSimple(param);
      resolve(result);
    })
  }
  //给图片添加频谱水印[同步]
  putMarkOnImageFFT(param) {
    return this._file.putMarkOnImageFFT(param);
  }
  //给图片添加频谱水印[异步]
  putMarkOnImageFFTAsync(param) {
    return new Promise((resolve, reject)=>{
      let result = this._file.putMarkOnImageFFT(param);
      resolve(result);
    })
  }
  //给图片添加ID水印[同步]
  putMarkOnImageSimple(param) {
    return this._file.putMarkOnImageSimple(param);
  }
  //给图片添加ID水印[异步]
  putMarkOnImageSimpleAsync(param) {
    return new Promise((resolve, reject)=>{
      let result = this._file.putMarkOnImageSimple(param);
      resolve(result);
    })
  }
  //给图片添加明水印[同步]
  putShowMarkOnImage(param) {
    return this._file.putShowMarkOnImage(param);
  }
  //给图片添加明水印[异步]
  putShowMarkOnImageAsync(param) {
    return new Promise((resolve, reject)=>{
      let result = this._file.putShowMarkOnImage(param);
      resolve(result);
    })
  }
  //压缩图片尺寸[同步]
  reduceImage(param) {
    return this._file.reduceImage(param);
  }
  //压缩图片尺寸[异步]
  reduceImageAsync(param) {
    return new Promise((resolve, reject)=>{
      let result = this._file.reduceImage(param);
      resolve(result);
    })
  }
}
module.exports = FileService;