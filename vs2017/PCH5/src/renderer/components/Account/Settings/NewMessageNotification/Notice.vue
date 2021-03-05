<template>
  <div class="notice-class">
    <div class="various-item ">
      <div class="">{{$t('account.msgNotification')}}:</div>
      <div class="settings-content">
        <div class="">{{$t('account.msgAlert')}}:</div>
        <v-radio
          class="sett-radio"
          v-for="(item, index) in radioList"
          v-model="defaultRadio"
          :key="item" :lable="item"
          @change="hanleRadioChange(index)"
        ></v-radio>
        <div class="cutting-line-before">{{$t('account.msgSoundAlert')}}:</div>
        <v-checkbox
          v-model="isSoundRemind"
          @change="setSoundRemind"
        >{{$t('account.openMsgSoundAlert')}}</v-checkbox>
        <div v-if ='clientConfig_user.openTrayTip' class="cutting-line-before">{{$t('account.trayTip')}}:</div>
        <v-checkbox v-if ='clientConfig_user.openTrayTip'
          v-model="isTrayTip"
          @change="setTrayTip"
        >{{$t('account.openTrayTip')}}</v-checkbox>
        <div class="cutting-line-before">{{$t('account.voiceVideo')}}:</div>
        <div class="voice-video-setting">
          <v-checkbox
            v-model="isMediaRemind"
            @change="setMediaRemind"
          >{{$t('account.openVoiceVideo')}}</v-checkbox>
          <p class="voice-video-tip">({{$t('account.openVoiceVideoTip')}})</p>
        </div>
      </div>
    </div>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import userMixin from './../../AccountMixin.js';
const { remote } = require('electron');
const rtcplugin = remote.getGlobal('service')['rtcplugin'];
export default {
  mixins: [userMixin],
  data() {
    return {
      radioList: [this.$t('account.receiveNotification'), this.$t('account.notDisturb')],
      getLocalSettingParam:['messagesSet'],
      setJudge:false,
      isShowLoading: false,
      isLoading: false,
      isMediaRemind: false,
      isSoundRemind: true,
      isTrayTip:true
    }  
  },
  computed: {
    ...mapGetters(['user_localConfig','clientConfig_user']),
    defaultRadio() {
      let index = this.user_localConfig.msg_remind
      if (this.user_localConfig.msg_remind === 2) index = 1;
      return this.radioList[index]
    }
  },
  created() {
    this.isMediaRemind = this.user_localConfig.media_remind === 'on';
    this.isSoundRemind = this.user_localConfig.sound_remind === 'OPEN';
    this.isTrayTip = this.user_localConfig.tray_tip === 'OPEN';
  },
  methods: {
    // 选择按钮设置消息提醒方式
    hanleRadioChange(index) {
      console.log('notice page value index:::', index);
      let val = index === 1 ? 2 : index;
      this.setUserConfigForDatabase(
        this.user_localConfig.isMsgRemind,
        'msg_remind',
        val,
        'isMsgRemind'
      )
    },

    // 音视频消息提醒
    setMediaRemind() {
      console.log('this.isMediaRemind:::', this.isMediaRemind);
      let val = this.user_localConfig.media_remind === 'on'?'off':'on'
      this.setUserConfigForDatabase(
        this.user_localConfig.isMediaRemind,
        'media_remind',
        val,
        'isMediaRemind'
      );
      if (this.isMediaRemind) {
        rtcplugin.SetNotifySwitch('off');
        return;
      }
      rtcplugin.SetNotifySwitch('on');
    },

    // 设置会话声音提醒
    setSoundRemind() {
      console.log('isSoundRemind:::', this.isSoundRemind);
      let val = this.user_localConfig.sound_remind === 'OPEN'?'CLOSE':'OPEN'
      this.setUserConfigForDatabase(
        this.user_localConfig.isSoundRemind,
        'sound_remind',
        val,
        'isSoundRemind'
      )
    },
    setTrayTip() {
      console.log('isTrayTip:::', this.isTrayTip);
      let val = this.user_localConfig.tray_tip === 'OPEN'?'CLOSE':'OPEN'
      this.setUserConfigForDatabase(
        this.user_localConfig.isTrayTip,
        'tray_tip',
         val,
        'isTrayTip'
      )
    }
  }
};
</script>
<style lang="scss" scoped>
.notice-class {
  width: 100%;
  height: 100%;
  padding: 15px;
  color: get-grey-color(base);
  font-size: $--font-size-mid;
  background: $--color-white;
  box-sizing: border-box;
  overflow: hidden;
  border-radius: $--border-radius-base;
  &:hover {
    overflow-y: auto;
  }
  &::-webkit-scrollbar {
    display: none;
  }
  .various-item {
    color: get-grey-color(darken-3);
    width: 100%;
    .settings-content {
      padding: 10px 0 10px 95px;
      .sett-radio{
        padding: 2px 0;
        overflow: hidden;
        margin: 0;
        width: 200px;
      }
      .voice-video-setting{
        display: flex;
        .voice-video-tip{
          padding-top: 2px;
          padding-left: 2px;
          color: red;
        }
      }
    }
  }
}

</style>
