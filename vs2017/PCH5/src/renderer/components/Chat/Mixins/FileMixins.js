import {
  mapGetters
} from 'vuex';
import {
  resolve
} from 'dns';
const FileMixin = {
  data() {
    return {
      encryptFileSavePath: '',
      downName: '',
      isExistFile: false,
      isdowns: 0
    }
  },
  computed: {
    ...mapGetters(['user_account'])
  },
  methods: {
    /**
     * 获取文件信息
     * messageId 消息ID
     */
    getFileInfo(headPath, url) {
      return new Promise((resolve, reject) => {
        let getFilesInfoCb = result => {
          console.log('getFilesInfo', result)
          /**
           * 加密文件 
           * encryptFiles 加密文件路径
           * 如果获取文件信息存在路径，则加密文件为
           * 如果不存在文件路径，使用默认路径
           */

          let index = url.lastIndexOf('/');
          let path = url.substr(index + 1)
          this.downName = path.substr(0, path.lastIndexOf('.'))
          console.log('this.downName::', this.downName)
          /** 特殊处理无后缀名文件 */
          if (!this.downName) {
            this.downName = path
          }
          if (result.fileInfos.length) {
            this.encryptFileSavePath = result.fileInfos[0].path
          } else {
            this.encryptFileSavePath = headPath + this.downName;
          }
          console.log('this.encryptFileSavePath', this.encryptFileSavePath)
          this.$Service.log(`encryptFileSavePath   ${this.encryptFileSavePath}`)
          /**
           * 判断加密过的文件是否存在
           * fileOperate
           * @param filepath  加密文件路径
           * @param type  操作类型 0：判断文件或文件夹是否存在 1.创建文件夹 2.删除文件 3.重命名文件
           * 下载过 或者 自己发的 显示打开
           **/
          let fileOperateParam = {
            filepath: this.encryptFileSavePath, //路径
            type: 0 // 操作类型 0：判断文件或文件夹是否存在 1.创建文件夹 2.删除文件 3.重命名文件
          }

          this.isExistFile = this.$Service.file.fileOperate(fileOperateParam)
          resolve(this.isExistFile)
        }
        this.$Service.file.getFilesInfo([this.message.messageObject.msgId], getFilesInfoCb)
      })
    },

    /*
     *下载文件
     *targetId 发送者的targetId
     *fileMsgId 文件消息的msgID
     *localPath 传入下载路径
     *remotePath 传入url
     *cb  传入接收结果回调 _1错误信息  _2本地路径 _3发送者ID
     *pro  进度回调
     *isDownLoad
     *0   下载  1 进度条 2 打开 3 重新下载
     */
    downLoadFile(downloadFileProcessCB) {
      return new Promise((resolve, reject) => {
        //  let paths = this.isdowns>0 ? '' : 'c://'
        //  this.isdowns++
        //  console.log('his.isdowns', this.isdowns)
        if (this.state !== 0) {
          this.localId = this.localId || this.message.messageObject.localId
          this.$Service.log(`downLoadFile localId:::  ${this.localId}`)
        }
        let downloadFileCb = resp => {
          resolve(resp) // 下载文件回调
          this.$Service.log(`downLoadFile mixin  code::${resp.code}`)
          if (resp.code === -16777206) {
            this.$toast.open({
              duration: 1500,
              message: this.$t('groups.resourceExpired'),
              position: 'is-top',
              type: 'is-danger'
            });
          }
        }

        let downloadFileParam = {
          targetId: this.message.messageObject.targetId, // 目标ID	有可能是群或者人 targetID
          msgId: this.message.messageObject.msgId, // 消息的msgID
          fromUserId: this.message.messageObject.fromId, // 发送者ID fromID
          localPath: this.encryptFileSavePath, // 文件本地保存路径
          encryptKey: this.message.messageObject.encryptKey,
          url: this.message.messageObject.url, // 远程路径 remotePath
          bIsResume: true, // 是否断点续传
          fileName: this.message.messageObject.fileName,
          localId: this.localId // 本地唯一Id
        }
        console.log('downloadFileParam', downloadFileParam)
        this.localId = this.$Service.file.downloadFile(downloadFileParam, downloadFileCb, downloadFileProcessCB)
        console.log('this.localId', this.localId)
      })
    },

    /**
     * 创建缓存文件路径
     * @param {*} path
     * @returns {String} 返回解密路径 
     */
    createCachePath(path, fileName, uid) {
      // let cachePath = `${path}cache/${uid}/` // cache路径
      let cachePath = `${path}cache/${uid?(uid+'/'):''}` // cache路径
      let isCreateCache = this.$Service.file.fileOperate({
        filepath: cachePath,
        type: 1
      })
      this.$Service.log(`创建解密缓存文件  result::${isCreateCache}`)
      console.log('this.message.messageObject.fileName', fileName)
      return cachePath + fileName.replace(/\//g, '_')
    },

    /**
     * @param {String} encryptkey 解密密码
     * @param {String} srcpath 原图路径
     * @param {String} destpath 保存路径
     * @param {Number} flag 是否可读  1 可读可写  2只读 
     */
    decrypted(encryptkey, srcpath, destpath, flag = 1) {
      return new Promise((resolve, reject) => {
        let decryptFileParam = {
          encryptkey: encryptkey,
          srcpath: srcpath,
          destpath: destpath,
          flag: flag
        }
        this.$Service.log(`decryptFile Flag  ${decryptFileParam.flag}`)
        console.log('decryptFileParam', JSON.stringify(decryptFileParam))
        this.$Service.file.decryptFile(decryptFileParam, resp => {
          this.$Service.log(`解密文件  result::${resp.result}`)
          resolve(resp)
        })
      })
    },

    /** 
     * 剩余时间格式化 hour : minute : second;
     */
    timeToFormat(times) {
      let result;
      let hour, minute, second
      if (times > 0) {
        hour = Math.floor(times / 3600);
        if (hour < 10) {
          hour = "0" + hour;
        }
        minute = Math.floor((times - 3600 * hour) / 60);
        if (minute < 10) {
          minute = "0" + minute;
        }

        second = Math.floor((times - 3600 * hour - 60 * minute) % 60);
        if (second < 10) {
          if (second === 0) {
            second = 1
          }
          second = "0" + second;
        }
        if (hour === '00') {
          result = minute + ':' + second;
        } else {
          result = hour + ':' + minute + ':' + second;
        }

      }
      return result;
    },

    /**
     * writeFile 将文件写入本地
     * @param {*} path 文件写入路径
     * @param {*} dataBuffer 文件写入缓存
     */
    writeFile(path, dataBuffer) {
      return new Promise(resolve => {
        this.$fs.writeFile(path, dataBuffer, (err) => {
          if (err) {
            this.$Service.log(`writeFile err`)
            resolve(false)
          } else {
            resolve(true)
            this.$Service.log(`writeFile success`)
          }
        });
      })
    }

  }
};
export default FileMixin;
