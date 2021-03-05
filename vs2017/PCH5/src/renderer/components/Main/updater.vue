<template>
<div class="updater-modal" v-if="isUpdateShow&&isUpdateShy">
  <v-modal>
    <div class="modal-card-head" slot="header-top" v-if="!isDownloadShow">
      <v-avatar size='is-small' :src="logo" ></v-avatar>
      <p class="modal-card-title">{{$t('upgrade.newVersion')}}</p>
      <!--<p class="modal-card-title">{{$t('upgrade.newVersion')+` (${updateInfo.version})`}}</p>-->
    </div>
    <div class="card-body-content">
      <div v-if="!isDownloadShow">
        <div class='dialog-text' v-html="message||updateInfo.message&&updateInfo.message.replace(/\n/g, '<br/>')"></div>
      </div>
      <div class="card-body-progress" v-else>
        <div class='dialog-text'>{{tips}}：{{parseInt(downloadPercent)+'%'}}</div>
        <div class='grade-progress-bar-bg'>
          <div class='progress-bar-bg'>
            <div class='progress-bar theme-botton' :style="{width: downloadPercent+'%'}"></div>
          </div>
        </div>
      </div>
    </div>
    <div class="modal-card-footer" slot="footer-bottom">
      <div class='btn-wrap' v-if="isUpdateNow">
        <v-button type="is-primary" class='btn btn-minor' v-if="!updateInfo.isForceUpdate" @click.once="close()">{{$t('upgrade.updateLater')}}</v-button>
        <v-button type="is-primary" class='btn' @click.once="startUpdate">{{$t('upgrade.update')}}</v-button>
      </div>
      <div class='btn-wrap' v-else-if="!isDownloadShow">
        <v-button type="is-primary" class='btn btn-minor' v-if="!updateInfo.isForceUpdate" @click.once="close()">{{$t('upgrade.downloadLater')}}</v-button>
        <v-button type="is-primary" class='btn' @click.once="startDownload">{{$t('upgrade.download')}}</v-button>
      </div>
      <div class='btn-wrap btn-wrap-download' v-else-if="isDownloadShow&&!updateInfo.isForceUpdate">
        <v-button type="is-primary" class='btn' @click.once.native="slientDownload">{{$t('upgrade.background')}}</v-button>
      </div>
    </div>
  </v-modal>
  </div>
</template>
<script>
  const log = require('electron-log')
export default {
  data() {
    return {
      tips: this.$t('upgrade.progress'),
      downloadPercent: 0,
      isDownloadShow: false,
      isUpdateNow: false,
      isUpdateShy: true, // 内部控制界面显示/隐藏
      message: null,
      logo: require('vrv-static/resources/images/common/dou.png')
    }
  },
  props: {
    isUpdateShow: Boolean, // 外部控制界面显示/隐藏
    isDownloadFinished: Boolean, // 是否升级包已下载
    updateInfo: String | Object // 升级信息 
  },
  watch: {
    isUpdateShow(value) {
      if (!value) return;
      console.log('isUpdateShy:::', this.isUpdateShy)
      console.log('isDownloadFinished:::', this.isDownloadFinished)
      if (!this.isUpdateShy) {
        this.isUpdateShy = true;
        return;
      };
      if (this.isDownloadFinished) {
        this.isUpdateShy = true;
        this.isUpdateNow = true;
        this.isDownloadShow = false;
        this.message = this.$t('upgrade.restartTip', {value: this.updateInfo.version});
      }
    }
  },
  created() {
    /** 注册更新监听 */
    this.$ipc.on('message', (event, text)=> {
      console.log('watch message...')
      this.tips = text;
    });
    this.$ipc.on('downloadedAvailable', ()=> {
      console.log('watch downloadedAvailable...')
      this.isUpdateShy = false;
    });
    this.$ipc.on('downloadProgress', this._handleProgress);
    this.$ipc.on('isUpdateNow', this._handleRestart);
  },
  beforeDestroy() {
    this.$ipc.removeAllListeners(['message', 'downloadProgress', 'isUpdateNow']);
  },
  methods: {
    /**
     * @breif 下载完成提示重启
     * @param {String} version - 版本号
     */
    _handleRestart(event, version) {
      log.info('isUpdateNow...', version)
      this.isUpdateShy = true;
      this.isUpdateNow = true;
      this.isDownloadShow = false;
      this.$emit('open-update-info')
      this.message = this.$t('upgrade.restartTip', {value: version});
    },
    /**
     * @breif 下载进度
     * @param {Object} progressObj - 进度信息
     */
    _handleProgress(event, progressObj) {
      log.info(progressObj.percent,"---")
      // console.log('watch downloadProgress...')
      // this.$Service.log(`downloading...${progressObj&&progressObj.progess}`)
      this.downloadPercent = progressObj.percent || 0;
      // this.downloadPercent = progressObj.progess || 0;
    },
    /**
     * @breif 开始下载
     */
    _handleDownload() {
      let downloadParam = {
        flag: 0,
        url: this.updateInfo.downloadNetUrl,
        localPath: this.updateInfo.downloadLocalUrl
      }
      console.log('downloadParam=====>', downloadParam)
      this.$Service.file.downloadExternalFile(downloadParam, result => {
        console.log('downloadExternalFile=======>result', result)
        if (result.code!==0) {
          this.$Service.log('download failed, please retry...')
          this.$toast.open({
            duration: 3000,
            message: '下载失败，请重试',
            position: 'is-top',
            type: 'is-danger'
          });
          this.close();
        } else {
          this.$Service.log('download success, ready to restart...')
          if (!this.isUpdateShow) { // 后台下载完成后弹窗提示
            this.$emit('open-update-info')
          }
          this._handleRestart(null, this.updateInfo.version)
        }
      }, progress => {
        console.log('downloadExternalFile=======>progress', progress)
        this._handleProgress(null, progress)
      })
    },
    /**
     * @breif 关闭升级窗口
     * 稍后更新、稍后下载、下载失败、重启更新、后台下载
     */
    close() {
      this.isUpdateNow = false;
      this.isUpdateShy = true;
      this.downloadPercent = 0;
      this.isDownloadShow = false;
      this.message = null;
      this.$emit('close')
    },
    /**
     * @breif 后台下载
     */
    slientDownload(e) {
      this.isUpdateShy=false
      this.$emit('close')
    },
    /**
     * @breif 点击下载
     */
    startDownload() {
      this.$Service.log('ready to download...')
      this.isDownloadShow = true;
      this.$ipc.send('download-update');
      // this._handleDownload()
    },
    /**
     * @breif 开始重启安装
     */
    startUpdate() {
      this.$Service.log('begin to restart...')
      this.$ipc.send('is-update-now');
      this.$Service.config.launchOtherApp({
        path: this.updateInfo.downloadLocalUrl,
        runByAdmin: true,
        startParam: ''
      })
      if(this.$is.isOSX) {
        this.$ipc.send('exit-app');
      }
      this.close();
    }
  }
}
</script>
<style lang="scss">
.updater-modal {
.modal-card {
  width: 340px;
  border-radius: 6px;
}
.modal-card-head {
  height: 60px;
  border-bottom: 1px solid #dbdbdb;
  border-top-left-radius: 5px;
  border-top-right-radius: 5px;
  .modal-card-title {
    font-size: 1.2rem;
    margin-left: 8px;
  }
}
.modal-card-body {
  display: flex;
  height: 100%;
  flex-direction: column;
  overflow-x: hidden;
  align-items: center;
  justify-content: center;
  max-height: 240px;
}
.modal-card-footer {
  -webkit-app-region: no-drag !important;
  border-bottom-left-radius: 6px;
  border-bottom-right-radius: 6px;
  border-top: 1px solid #dbdbdb;
  background: #fff;
  align-items: center;
  background-color: #f5f5f5;
  display: flex;
  flex-shrink: 0;
  padding: 10px;
  position: relative;
  justify-content: flex-end;
}
.is-primary {
  font-size: 15px;
}
.card-body-content {
  width: 100%;
  max-height: 240px;
  .card-body-progress {
    margin: 10px 0px;
    .grade-progress-bar-bg {
      padding: 0 20px;
      align-items: center;
      display: flex;
      height: 10px;
      .progress-bar-bg {
        background-color: #e3f2fd;
        border-radius: $--border-radius-base;
        height: 7px;
        width: 340px;
        margin-top: 6px;
        .progress-bar {
          background-color: #1e88e5;
          height: 6px;
          margin-bottom: 1px;
          display: block;
          border-radius: $--border-radius-base;
        }
      }
    }
  }
}
.dialog-text {
  padding: 15px 20px;
  color: #555;
}
.btn-minor {
  // background: rgba(0,0,0,0.12);
  background: #fff;
  border: 1px solid rgba(0, 0, 0, 0.12);
  color: rgb(50, 58, 123);
  &:hover {
    background: rgba(0,0,0,0.12);
  }
}

.update-dialog {
  .dialog-wrap {
    position: fixed;
    box-sizing: border-box;
    padding: 20px;
    width: 300px;
    left: 50%;
    display: flex;
    flex-direction: column;
    top: 50%;
    transform: translate(-50%, -50%);
    border-radius: $--border-radius-base;
    background: #fff;
    @include z-index(modal);

    box-shadow: $--box-shadow-rd;
    &:hover {
      box-shadow: $--box-shadow-hover;
    }
    .dialog-title {
      text-align: center;
    }
    .dialog-text {
      padding: 15px 20px;
      font-size: 15px;
      color: #555;
    }
    .grade-progress-bar-bg {
      align-items: center;
      display: flex;
      height: 10px;
      .progress-bar-bg {
        background-color: #e3f2fd;
        border-radius: $--border-radius-base;
        height: 7px;
        width: 340px;
        margin-top: 6px;
        .progress-bar {
          background-color: #1e88e5;
          height: 6px;
          margin-bottom: 1px;
          display: block;
          border-radius: $--border-radius-base;
        }
      }
    }
    .btn-wrap {
      display: flex;
      justify-content: flex-end;
      .btn-minor {
        background: rgba(0,0,0,0.12);
      }
      .btn {
        padding: 0px 8px;
        font-size: 14px;
        cursor: pointer;
        &:last-child {
          color: #76D49B;
        }
      }
    }
    .btn-wrap-download {
      margin-bottom: -10px;
      padding-top: 10px;
    }
  }
  .dialog-mask {
    position: fixed;
    width: 100%;
    margin: 0 auto;
    top: 0;
    left: 0;
    bottom: 0;
    right: 0;
    z-index: 1;
    @include z-index(modal);

    background: rgba(10, 10, 10, 0.4);
  }
}
}
</style>

