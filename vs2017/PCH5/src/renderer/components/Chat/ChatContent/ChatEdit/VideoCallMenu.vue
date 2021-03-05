<template>
  <!-- 编辑框二级菜单功能页：音视频相关 -->
  <div class="video-call-menu" @mouseleave.passive="$emit('close')"> 
    <div class="menu-container">    
      <!-- 音频通话、视频通话、远程协助  -->
      <li class="theme-hover-bgc_font" v-for="(item, key, index) in menuType" :key="key" @click="handleSubWinType(item.type, index)">
        <i class="icon" v-html="item.icon"></i><span>{{item.text}}</span>
      </li>
      </div>
  </div>
</template>
<script>
export default {
  data() {
    return {
      noCamera: this.$t('chat.noCamera'),
      noMIC: this.$t('chat.noMIC'),
      channelBusy: this.$t('chat.channelBusy'),
      menuType: {
        'audio': { icon: '&#xe6e4;', text: this.$t('chat.audioCall'), type: 'RTCP2P'},
        'video': { icon: '&#xe631;', text: this.$t('chat.videoCall'), type: 'RTCP2P'},
        // 'remote': { icon: '&#xe669;', text: this.$t('chat.remoteAssistance'), type: 'RemoteControl'}
      }
    }
  },
  methods: {
    /**
     * @breif 音视频通话、远程协助
     */
    async handleSubWinType(type, index) {
      let find_camera_device = await this.findCameraDevice();
      let find_audio_device = await this.findAudioDevice();

      if (index === 1) { // 此时发起视频会话，但是没有摄像头
        if (!find_camera_device) {
          this.dialogShow(this.noCamera)
          return;
        } else if (!find_audio_device) {
          this.dialogShow(this.noMIC)
          return;
        }
      } else if (index===0 && !find_audio_device) {
        this.dialogShow(this.noMIC)
        return;
      }
      
      this.containBusyStatus(type)
      this.getContactInfo(this.$route.query.id, type, index)
    },

    /**
     * @breif toast弹框提示
     * @param {String} - message 提示内容
     */
    dialogShow(message, type='is-warning') {
      this.$toast.open({ duration: 3000, message, position: 'is-top', type});
    },

    /**
     * @breif 判断是否有摄像头
     */
    async findCameraDevice(){
      let find_camera_device = false;
      await navigator.mediaDevices.enumerateDevices().then(device_infos => {
      for (let i=0; i!==device_infos.length; ++i)
        if (device_infos[i].kind === 'videoinput') {
            find_camera_device = true;
            break;
        }
       });
      return find_camera_device;
    },

    async findAudioDevice(){
      let find_audio_device = false;
      await navigator.mediaDevices.enumerateDevices().then(device_infos => {
        for (let i=0; i!==device_infos.length; ++i)
          if (device_infos[i].kind === 'audioinput') {
            find_audio_device = true;
            break;
          }
      });
      return find_audio_device;
    },
    
    /**
     * @breif 是否通道繁忙
     * @param {String} - type 窗口类型
     */
    containBusyStatus(type) {
      let result = this.$judgePlginSubWinStatus(type)
      if (result.busy) {
        this.dialogShow(this.channelBusy, 'is-danger');
        return
      }
      this.isShowEditBox = false
    },

    /**
     * @brief 获取联系人信息
     * @param {String} - userId 好友id
     * @param {String} - type 窗口类型
     */
    getContactInfo(userId, type, index) {
      this.$Service.contact.getContactInfo({ userId },  info => this.createSubWindow(info, type, index))
    },
    
    /**
     * @breif 携带子窗口信息向主进程发送信号，接收到信号后主进程创建子窗口
     * @param {Object} -info 好友信息
     * @param {String} -winType 窗口类型
     */
    createSubWindow(info, winType, index) {
      let [winUrl, winTitle] = ['', ''];
      let typeActions = {
        'RemoteControl': () => {
          winUrl = '#/RemoteControl?' + info.id,
          winTitle = `${this.menuType['remote'].text}[${info.remark||info.name}]`
        },
        'RTCP2P': () => {
          winUrl = '#/RTCP2P?type=' + (index + 1) + '&Id=' + info.id + '&isBurn='  + this.$attrs.isBurn,
          winTitle = `${ index === 0 ? this.menuType['audio'].text : this.menuType['video'].text }[${info.remark||info.name}]`
        }
      }

      typeActions[winType].call(this)

      console.log(winUrl, winTitle, winType)

      this.$ipc.send('new-window', { winUrl, winType, winTitle, winIcon: info.thumbAvatar, shapeType: 'normal'})
    }
  }  
}
</script>
<style lang="scss">
.video-call-menu {
  position: absolute;
  right: -124px;
  width: 130px;
  top: -10px;
  .menu-container {
    margin-left: 10px;
    background: #fff;
    width: 120px;
    border-radius: 3px;
    padding: 10px 1px;
    box-shadow: $--box-shadow-elevation;
  }
}
</style>