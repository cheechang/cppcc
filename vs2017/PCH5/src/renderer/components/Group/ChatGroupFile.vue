<template>
  <div class="chat-group-file" :style="{background: fileInfo.length > 0?'#fff':''}" @scroll.passive.stop="getFileMore" ref="fileCard">
    <transition name="slide-fade">
      <v-card-list class="group-file" v-if="!isLoading">
        <v-card v-if="item.uploader" class="file-item" v-for="(item,index) in fileInfo" :key="index" :title="item.name" :subtitle="`${$t('chat.uploadeder')}：${item.uploader}`">
          <v-avatar :src="getFileImg(item.name)" size='is-small' slot="leftAvatar"></v-avatar>
          <div class="item-size" slot="subBefore">{{getFileSize(item)}}</div>
          <div class="item-download" slot="subAfter">{{getTimes(item)}}</div>
          <i class="icon theme-txt" slot="rightAvatar" v-if="item.isDownloadFinished" @click="openFileDir(item)">&#xe66f;</i>
          <i class="icon theme-txt" slot="rightAvatar" v-else-if="!item.isDownload" @click="downloadFile(item)">&#xe61d;</i>
          <circle-progress class="theme-txt" slot="rightAvatar" v-else-if="item.isDownload" color="#323a7b" width=20 font-size=0 :pv="item.progressWidth" :isPause="item.isPause" bold=1 text-bg-color='#ffffff' @click="continueDownload(item)"></circle-progress>
        </v-card>
      </v-card-list>
      <v-button class="is-loading is-large" :ripple="false" v-else></v-button> 
    </transition>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import { getDateDiff } from '../../../comm/time';
import contactMixin from '../Contact/ContactMixin';
import CircleProgress from '../Common/Progress';
import fileMixin from '../Chat/Mixins/FileMixins';
export default {
  mixins: [contactMixin, fileMixin],
  data() {
    return {
      fileInfo: [],
      isLoading: true, // 载入数据
      isEndRoll: false, // 没有更多数据，不再触发滚动事件
      isScrollNext: false, // 控制滚动的频繁触发
      localId: new Date().getTime()
    };
  },
  props: {
    id: String
  },
  computed: {
    ...mapGetters(['user_filePath'])
  },
  components: {
    CircleProgress
  },
  mounted() {
    console.log('mounted:::')
    this.getGroupFile();
  },
  methods: {
    getFileMore() {
      if (this.isLoading || this.isEndRoll || this.isScrollNext) return;
      this.$nextTick(() => {
        if(this.isScrollToBottom(this.$refs.fileCard)) this.getGroupFile();
      });
    },
    getGroupFile() {
      this.isScrollNext = true;
      let getGroupFileListParam = {
        groupId: this.$route.query.id,
        beginId:
          this.fileInfo.length === 0
            ? '0'
            : this.fileInfo[this.fileInfo.length - 1].fileid,
        count: 10,
        flag: 0
      };
      console.log('getGroupFileListParam', JSON.stringify(getGroupFileListParam));
      this.$Service.group.getGroupFileList(getGroupFileListParam, resp => {
          console.log('获取群文件', resp);
          if (resp.code !== 0 || resp.files.length === 0) {
            this.isLoading = false;
            return;
          }
          if (resp.files.length < 8) this.isEndRoll = true;
          resp.files.forEach((e, i) => {
            if (this.fileInfo.length !== 0 && i === 0) return;
            this.fileInfo.push(e);
            this.getFileInfo(e);
            this.getFileUploader(e, i);
          });
      });
    },
    /**
     * 文件是否已下载过
     */
    getFileInfo(item) {
      this.$Service.file.getFilesInfo([item.fileid], resp=>{
        console.log('successResult', resp)
        let index = item.url.lastIndexOf('/');
        let path = item.url.substr(index + 1)
        this.$set(item, 'downName', path.substr(0, path.lastIndexOf('.')))
        if (resp.fileInfos.length) {
          this.$set(item, 'encryptFileSavePath', resp.fileInfos[0].path);
        } else {
          this.$set(item, 'encryptFileSavePath', this.user_filePath + item.downName);
          this.$set(item, 'isDownloadFinished', false)
        }
        let fileOperateParam = { filepath: item.encryptFileSavePath,type: 0 }
        if(this.$Service.file.fileOperate(fileOperateParam)) {
          this.$set(item, 'isDownloadFinished', true)
          item.decryptFiles = item.encryptFileSavePath = item.encryptFileSavePath
        }
      })
    },
    /**
     * 不同文件类型对应的图标
     */
    getFileImg(name) {
      // TODO 与MsgTypeFile.vue中代码重复了
      switch (name.substring(name.lastIndexOf('.') + 1)) {
        case 'pdf': return require('vrv-static/resources/images/message/pdf.png')
        case 'txt': return require('vrv-static/resources/images/message/txt.png')
        case 'xls': return require('vrv-static/resources/images/message/execl.png')
        case 'xlsx': return require('vrv-static/resources/images/message/execl.png')
        case 'ppt': return require('vrv-static/resources/images/message/ppt.png')
        case 'exe': return require('vrv-static/resources/images/message/install.png')
        case 'zip': return require('vrv-static/resources/images/message/package.png')
        case 'doc': return require('vrv-static/resources/images/message/word.png')
        case 'docx': return require('vrv-static/resources/images/message/word.png')
        default: return require('vrv-static/resources/images/message/unknown.png')
      }
    },
    /**
     * 文件上传者
     */
    getFileUploader(item, i) {
      this.$Service.search.getUserInfo({ userId: item.userid }, resp => {
        if(!resp.users.name) this.fileInfo.splice(i, 1);
        this.$set(item, 'uploader', resp.users.name);
        this.isScrollNext = false;
        if (i === this.fileInfo.length - 1)
          this.$nextTick(() => {
            this.isLoading = false;
          });
      });
    },
    /**
     * 文件大小
     */
    getFileSize(item) {
      return item.size > 1024 * 1024
        ? (Math.round(item.size * 100 / (1024 * 1024)) / 100).toString() + 'MB'
        : (Math.round(item.size * 100 / 1024) / 100).toString() + 'KB';
    },
    /**
     * 文件上传时间
     */
    getTimes(item) {
      if (item.time.toString().length < 13) item.time *= 1000;
      return `${this.$t('chat.uploadDate')}：${getDateDiff(item.time)}`;
    },
    showSaveDialog(fileName) {
      return new Promise(resolve => {
        /**
         * 文件后缀过滤
         * 若存在文件后缀 限制保存格式
         * 不存在后缀名称 则支持所有文件类型
         */
        let extensionFilter = [{ name: "All Files", extensions: ["*"] }];
        if (fileName.lastIndexOf(".") !== -1) {
          let fileExtension = fileName.substr(fileName.lastIndexOf(".") + 1);
          if (fileExtension) {
            extensionFilter.unshift({
              name: "Files",
              extensions: [fileExtension]
            });
            console.log("extensionFilter::", extensionFilter);
          }
        }
        this.$dialogs.showSaveDialog(
          { defaultPath: fileName, filters: extensionFilter },
          resp => {
            resolve(resp);
          }
        );
      });
    },
    /** 
     * 下载文件
     */
    async downloadFile(item, isReDown=false) {
      console.log(';isReDown', isReDown)
      // 直接给item赋值将作为对象的临时属性不会产生视图更新
      let path
      if (!isReDown || !item.isPause) {
        path = await this.showSaveDialog(item.name)
        if (!path) {
          return 
        }
        item.encryptFileSavePath = path
      }
      console.log('path', path)
      this.$set(item,'isPause', false)
      this.$set(item,'isDownload', true)
      this.$set(item, 'isDownloadFinished', false)
      let downloadFileParam = {
        targetId: item.targetid,
        fromUserId: item.userid,
        msgId: item.fileid,
        localPath: item.encryptFileSavePath,
        encryptKey: item.encrypt_key,
        url: item.url,
        bIsResume: true,
        fileName: item.name,
        localId: item.localId || this.localId
      }
      console.log('downloadFileParam:::', downloadFileParam)
      // 文件下载回调
      let downloadCallback = successResp => {
        console.log('downloadCb:::', successResp)
        if (successResp.code === 0) {
          let index = successResp.localPath.lastIndexOf('\\');
          console.log('name', successResp.localPath.substr(index + 1))
          item.name =  successResp.localPath.substr(index + 1)
          item.encryptFileSavePath = successResp.localPath
          let reNamePath =  `${successResp.localPath}.temp`;
          this.$Service.log(`reNamePath::: ${reNamePath}`)
          // * 无密码 直接 完成
          if (!item.encrypt_key) {
            setTimeout(() => {
              item.isDownload = false;
              item.progressWidth = 0;
              item.isDownloadFinished = true;
            }, 600);
            return 
          }
        
          let decryptFileParam = {
            encryptkey: item.encrypt_key,
            srcpath: item.encryptFileSavePath,
            destpath: reNamePath
          }
          console.log('decryptFileParam', JSON.stringify(decryptFileParam))
          this.$Service.file.decryptFile(decryptFileParam, resp => {
            this.$Service.log(`解密文件  result::${resp.result}`)
            if (resp.result) {
              this.$Service.file.fileOperate({ filepath:item.encryptFileSavePath, type:2 });
              let fileOperateParam = {
                  filepath: reNamePath, //路径
                  type: 3, // 操作类型 0：判断文件或文件夹是否存在 1.创建文件夹 2.删除文件 3.重命名文件
                  newName:item.encryptFileSavePath, //重命名文件全路径  
              }
              let renameRes = this.$Service.file.fileOperate(fileOperateParam)
              this.$Service.log(`renameRes::: ${renameRes}`)
              item.decryptFiles = item.encryptFileSavePath
              setTimeout(() => {
                item.isDownload = false;
                item.progressWidth = 0;
                item.isDownloadFinished = true;
              }, 600);
            }
          })
        } else {
          this.$Service.log('downLoadFile fail in saveAs')
          if (successResp.code === -16777213) {
            item.isPause = true
            return
          }
          if (!item.isPause && successResp.code === -16777206) {
            this.$toast.open({duration: 1500, message: this.$t('groups.resourceExpired'), position: 'is-top', type: 'is-danger'});
          }
          item.isDownload = false;
        }
        // if (resp.code !==0) {
        //   if (!item.isPause) {
        //     this.$toast.open({duration: 1500, message: this.$t('groups.resourceExpired'), position: 'is-top', type: 'is-danger'});
        //     item.isDownload = false;
        //   }
        //   return;
        // };
        // let cachePath = `${this.user_filePath}cache/`
        // this.$Service.file.fileOperate({ filepath: cachePath, type: 1 })
        // this.$set(item, 'decryptFiles', cachePath + item.name) 
        // let fileOperateParam = {
        //   filepath: item.decryptFiles,
        //   type: 0
        // }
        // if (this.$Service.file.fileOperate(fileOperateParam)) this.$Service.file.fileOperate({filepath:item.decryptFiles, type:2});
        // if (!item.encrypt_key) {
        //   this.$fs.createReadStream(item.encryptFileSavePath).pipe(this.$fs.createWriteStream(this.user_filePath +'cache/'+ item.name));
        // }
        // setTimeout(() => {
        //   item.isDownload = false;
        //   item.progressWidth = 0;
        //   item.isDownloadFinished = true;
        // }, 600);
      }
      // 文件下载进度回调
      let downloadProgressCb = resp => {
        console.log('downloadProgressCb:::',resp)
        this.$set(item,'progressWidth', resp.progess)
      }
      let localId = this.$Service.file.downloadFile(downloadFileParam, downloadCallback, downloadProgressCb)
      this.$set(item,'localId', localId)
    },
    /**
     * 继续下载/暂停下载文件 
     */
    continueDownload(item) {
      if (item.isPause) this.downloadFile(item, true);
      else 
        this.$Service.file.cancelTransfer({localId: item.localId, type: 2}, resp=>{
          console.log('取消下载:', resp)
          item.isPause=true;
        }) 
    },
    async openFileDir(item) {
      console.log('item', item)
      // * 新的群文件都为另存为下载
      if (item.encryptFileSavePath === this.user_filePath + item.downName) {
        console.log('encryptFileSavePath::', item)
        await this.decrypted(item)
      }
      this.$shell.showItemInFolder(item.decryptFiles)
    },
    decrypted(item) {
      return new Promise(resolve => {
        let cachePath = `${this.user_filePath}cache/`
        this.$Service.file.fileOperate({ filepath: cachePath, type: 1 })
        item.decryptFiles = cachePath + item.name.replace(/\//g, '_')
        if (!item.encrypt_key) {
          if (!this.$Service.file.fileOperate({filepath: item.decryptFiles, type: 0})) {
            this.$fs.createReadStream(item.encryptFileSavePath).pipe(this.$fs.createWriteStream(item.decryptFiles))
          } 
          resolve()
          return 
        }
        let decryptFileParam = {
          encryptkey: item.encrypt_key,
          srcpath: item.encryptFileSavePath,
          destpath: item.decryptFiles
        }
        console.log('decryptFileParam', JSON.stringify(decryptFileParam))
        this.$Service.file.decryptFile(decryptFileParam, resp => {
          this.$Service.log(`解密文件  result::${resp.result}`)
          if (resp.result) {
            resolve()
          }
        })
      })
    }
  }
};
</script>
<style lang="scss">
.chat-group-file {
  width: 100%;
  height: 100%;
  background: url('~vrv-static/resources/images/common/file_empty.png') 43% 40%
    no-repeat #fff;
  overflow-x: hidden;
  overflow-y: auto;
  margin-top: 2px;
  display: flex;  //fit xp
  flex: 1;//fit xp
  flex-direction: column;//fit xp
  .group-file {
    // min-width: calc(100vw - 250px);
    overflow-y: auto;
    .file-item {
      padding-left: 6px;
      .contents {
        width: 90px;
        font-weight: 300;
      }
      .media-right {
        align-items: center;
      }
    }
    .active {
      background: #ebebeb;
    }
    .icon {
      position: absolute;
      // bottom: 14px;
      font-size: 20px;
      font-weight: 300;
      @include get-grey-color(darken-1);
    }
    .item-download {
      position: absolute;
      left: 162px;
    }
    .item-size {
      width: 62px;
    }
  }
  // &:hover {
  //   overflow-y: auto;
  // }
  .is-loading {
    width:100%;
    height:100%;
    display: flex;  //fit xp
    flex: 1;//fit xp
  }
}
</style>

