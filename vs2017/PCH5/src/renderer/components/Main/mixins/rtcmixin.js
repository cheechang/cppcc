/**
 * @file      RTC业务模块.
 * @author    linpeiyuan <linpeiyuan@vrvmail.com.cn>
 * @date      2019.9.11
 * @copyright Beijing VRV Software Co.,Ltd
 * 
 * @mixin
 */
const mixin = {
  data () {
    /**
     * @param {Object} - audioPlugin 音视频响铃语音
     * @param {Object} - audioPluginEnd 音视频挂断语音
     */
    return {
      audioPlugin: require("vrv-static/resources/audio/audioPlugin.mp3"),
      audioPluginEnd: require("vrv-static/resources/audio/audioPluginEnd.mp3"),
    };
  },
  methods: {
    onRtcRing(e, arg) {
      if (arg) {
        this.$refs.rtcring.play();
      } else {
        this.$refs.rtcring.pause();
        this.$refs.rtchangup.play();
      }
    }
  },
};

export default mixin;