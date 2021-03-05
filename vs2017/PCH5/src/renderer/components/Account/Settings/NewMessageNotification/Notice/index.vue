<template>
<div class="notice-class">
  <div class="various-item ">
    <div class>{{$t('account.msgNotification')}}:</div>
    <div class="settings-content">
      <div class>{{$t('account.msgAlert')}}:</div>
      <v-radio
        class="sett-radio"
        v-for="(item, index) in radioList"
        v-model="defaultRadio"
        :key="item"
        :lable="item"
        @change="hanleRadioChange(index)"
      ></v-radio>
      <div class="cutting-line-before">{{$t('account.msgSoundAlert')}}:</div>
      <v-checkbox
        v-model="isSoundRemind"
        @change="setSoundRemind"
      >{{$t('account.openMsgSoundAlert')}}</v-checkbox>
      <div v-if ='isShowTrayTipCheckbox' class="cutting-line-before">{{$t('account.trayTip')}}:</div>
      <v-checkbox v-if ='isShowTrayTipCheckbox'
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
      <!-- <div class="cutting-line-before">{{$t('account.disturbMode')}}:</div> -->
      <!-- <v-checkbox v-model="isOpenDisturbMode" @change="setGlobalDisturbMode">{{$t('account.openDisturbMode')}}</v-checkbox>
      <div v-if="isOpenDisturbMode">
        <disturb-modal :mode="nightMode" @change="isOpen=>{nightMode.isOpen=isOpen,setDisturbMode()}" @click="index=>updateTime(nightMode, 1, index)"></disturb-modal>
        <disturb-modal :mode="dayMode" @change="isOpen=>{dayMode.isOpen=isOpen,setDisturbMode()}" @click="index=>updateTime(dayMode, 0, index)"></disturb-modal>
        <disturb-modal :mode="customMode" @change="isOpen=>{customMode.isOpen=isOpen,setDisturbMode()}" @click="index=>updateTime(customMode, 2, index)"></disturb-modal>
      </div> -->
    </div>
    <!-- <v-modal cardSize="disturb-style" v-if="isOpenConfig">
      <disturb-config :currentTime="currentTime" @close="isOpenConfig=false" @update="handleConfigTime"></disturb-config>
    </v-modal> -->
  </div>
  </div>
</template>
<script>
import { mapGetters } from "vuex";
import userMixin from "../../../AccountMixin.js";
import DisturbConfig from "./DisturbConfig.vue";
import DisturbModal from "./DisturbModal";
const { remote } = require("electron");
const rtcplugin = remote.getGlobal("service")["rtcplugin"];
export default {
  mixins: [userMixin],
  data() {
    return {
      radioList: [
        this.$t("account.receiveNotification"),
        this.$t("account.notDisturb")
      ],
      getLocalSettingParam: ["messagesSet"],
      setJudge: false,
      isShowLoading: false,
      isLoading: false,
      isMediaRemind: false,
      isSoundRemind: true,
      isOpenDisturbMode: false,
      isTrayTip:true,
      dayMode: {
        startTime: 45000,
        endTime: 50400,
        isOpen: false,
        name: this.$t('account.dayMode')
      },
      nightMode: {
        startTime: 82800,
        endTime: 28800,
        isOpen: false,
        name: this.$t('account.nightMode')
      },
      customMode: {
        startTime: 0,
        endTime: 0,
        isOpen: false,
        name: this.$t('account.customMode')
      },
      isOpenConfig: false,
      currentTime: "00:00",
      updateMode: {}
    };
  },
  computed: {
    ...mapGetters(["user_localConfig","clientConfig_user"]),
    defaultRadio() {
      let index = this.user_localConfig.msg_remind;
      if (this.user_localConfig.msg_remind === 2) index = 1;
      return this.radioList[index];
    },
    // 是否显示开启托盘消息提醒的选择框
    isShowTrayTipCheckbox(){
       return !this.$is.isWinXp && !this.$is.isWin7() && this.clientConfig_user.openTrayTip;  
    }  
  },
  components: {
    DisturbConfig,
    DisturbModal
  },
  created() {
    this.isMediaRemind = this.user_localConfig.media_remind === "on";
    this.isSoundRemind = this.user_localConfig.sound_remind === "OPEN";
    this.isTrayTip = this.user_localConfig.tray_tip === 'OPEN';
  },
  mounted() {
    this.$Service.user.getGlobalNoDisturbListMode(null, resp => {
      console.log("勿扰模式:::时间段获取:::", resp);
      let modeInfos = resp.modeInfos;
       if (!modeInfos || modeInfos.length === 0) {
         this.isOpenDisturbMode = false;
         return;
       }
      this.nightMode = Object.assign({}, resp.modeInfos[0] || this.nightMode, {name: this.$t('account.nightMode')});
      this.dayMode = Object.assign({}, resp.modeInfos[1] || this.dayMode, {name: this.$t('account.dayMode')});
      this.customMode = Object.assign({}, resp.modeInfos[2] || this.customMode, {name: this.$t('account.customMode')});
      this.isOpenDisturbMode =
      this.dayMode.isOpen || this.nightMode.isOpen || this.customMode.isOpen;
    });
  },
  methods: {
    /**
     * 修改免打扰时间
     * @param {Number} time - 开始时间/结束时间
     */
    handleConfigTime(time) {
      console.log("handleConfigTime::::", time);
      this.isOpenConfig = false;
      let modes = {
        0: this.dayMode,
        1: this.nightMode,
        2: this.customMode
      }
      if (this.updateMode.modeType === 0) { // 开始时间
        modes[this.updateMode.modeIndex].startTime = time;
      } else { // 结束时间
        modes[this.updateMode.modeIndex].endTime = time;
      }
      this.setDisturbMode();
    },
    /**
     * 打开弹出框，准备更新免打扰时间
     * @param {Object} mode - 白天/夜晚/自定义时间段数据
     * @param {Number} index - 选中的下标
     * @param {Number} type - 0：开始时间；1：结束时间
     */
    updateTime(mode, index, type) {
      if (!mode.isOpen) return;
      console.log("handle time update....");
      this.currentTime = this.getTime(
        type === 0 ? mode.startTime : mode.endTime
      );
      console.log("currentTime:::::", this.currentTime);
      this.updateMode = {
        modeIndex: index,
        modeType: type
      };
      this.isOpenConfig = true;
    },
    /**
     * 全局控制勿扰模式（白天、夜晚、自定义）
     * @param {Boolean} isChecked - 是否选中
     */
    setGlobalDisturbMode(isChecked) {
      if (!isChecked) {
        this.nightMode.isOpen = false;
        this.dayMode.isOpen = false;
        this.customMode.isOpen = false;
      } 
       else {
        this.nightMode.isOpen = true;
        this.dayMode.isOpen = true;
      }
      this.setDisturbMode();
    },
    /**
     * 获取免打扰时间段
     * @param {Number} seconds - 秒
     * @param {Boolean} isNextDay - 结束时间是否是次日
     */
    getTime(seconds, isNextDay = false) {
      try {
        let hours = parseInt(seconds / 3600);
        if (hours < 10) hours = "0" + hours;
        let mins = (seconds / 60) % 60;
        if (mins < 10) mins = "0" + mins;
        return (isNextDay ? this.$t('account.nextDay') : "") + hours + ":" + mins;
      } catch (error) {
        console.log("seconds:::", seconds);
      }
    },
    /**
     * 设置免打扰时间段
     * 1.modeInfos固定传入夜晚、白天、自定义
     * 2.isOpen控制开启关闭
     * 3.name暂不用，默认传入""
     */
    setDisturbMode() {
      if(!this.nightMode.isOpen && !this.dayMode.isOpen && !this.customMode.isOpen){
        this.isOpenDisturbMode = false;
      }
      let modeParams = {
        modeInfos: [this.nightMode, this.dayMode, this.customMode]
      };
      console.log("modeParams:::::", JSON.stringify(modeParams));
      this.$Service.user.setGolbalNoDisturbListMode(modeParams, resp => {
        console.log("勿扰模式:::时间段设置:::", resp);
      });
    },
    // 选择按钮设置消息提醒方式
    hanleRadioChange(index) {
      console.log("notice page value index:::", index);
      let val = index === 1 ? 2 : index;
      this.setUserConfigForDatabase(
        this.user_localConfig.isMsgRemind,
        "msg_remind",
        val,
        "isMsgRemind"
      );
    },

    // 音视频消息提醒
    setMediaRemind() {
      console.log("this.isMediaRemind:::", this.isMediaRemind);
      let val = this.user_localConfig.media_remind === "on" ? "off" : "on";
      this.setUserConfigForDatabase(
        this.user_localConfig.isMediaRemind,
        "media_remind",
        val,
        "isMediaRemind"
      );
      if (this.isMediaRemind) {
        rtcplugin.SetNotifySwitch("off");
        return;
      }
      rtcplugin.SetNotifySwitch("on");
    },

    // 设置会话声音提醒
    setSoundRemind() {
      console.log("isSoundRemind:::", this.isSoundRemind);
      let val =
        this.user_localConfig.sound_remind === "OPEN" ? "CLOSE" : "OPEN";
      this.setUserConfigForDatabase(
        this.user_localConfig.isSoundRemind,
        "sound_remind",
        val,
        "isSoundRemind"
      );
    },
    // 设置托盘消息通知
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
<style lang="scss">
.notice-class{
    width: 100%;
  background: #fff;
  padding: 15px;
  font-size: $--font-size-mid;
  padding-top: 15px;
  height: 100%;
  border-radius: $--border-radius-base;
  overflow: hidden;
  &:hover {
    overflow-y: auto;
  }
  &::-webkit-scrollbar {
    display: none;
  }
.various-item {
  .settings-content{
    padding: 10px 0 10px 95px;
  
  .sett-radio {
    padding: 2px 0;
    overflow: hidden;
    margin: 0;
    width: 200px;
  }
  .voice-video-setting {
    display: flex;
    .voice-video-tip {
      font-size: 14px;
      padding-top: 2px;
      padding-left: 2px;
      color: red;
      }
    }
    .time-intervals{
     .fields{
       width: 45% ;
     }
   }
  }
  .disturb-style {
    width: 300px;
  }  
}
}
</style>
