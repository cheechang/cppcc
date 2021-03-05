<template>
  <div class="rtc-file-area">
  </div>
</template>
<script>
import { Rtcfile } from '../../rtc/file/rtcfile'
const { ipcRenderer } = require('electron');
const log = require('electron-log')

export default {
  name: 'rtcFile',
  created() {
    ipcRenderer.once('colseFile',() => {
      console.log('closeRtc::::::::::::::::')
      log.debug('closeRtc::::::>>>>>>>>>>>>>')
      this.rtcfile.Close()
      log.debug('closeRtc::::::>>>>>>>>>>>>>22222222222222222222')
      setTimeout(() => {window.close();}, 500);
    })

    let rtcfileCb = function() {};
    /**
     * @param {string} id 发送对象id
     * @param {string} path 发生文件所在地址
     * @param {string} isSend '1' 发送 '2' 接收
     */
    const searchParams = new URLSearchParams(window.location.href)
    let id = searchParams.get("senderId")
    let path = searchParams.get("path")
    let isSend = searchParams.get("isSend")
    
    console.log('id::', id, path, isSend)
    log.debug('closeRtc::::::>>>>>>>>>>>>>3333333333333333333333333')
    this.rtcfile = new Rtcfile( isSend=== '1' ? true : false, rtcfileCb)
   
    if (isSend === '1') {
      this.rtcfile.SendFile(id, path)
    } else {
      /**
       * @param {string} savePath 文件保存地址
       * @param {string} size 接收文件尺寸
       * @param {string} isAccept true 接收 false 拒绝
       */
      console.log('RecvFile')
      let savePath = searchParams.get("savePath")
      let size = searchParams.get("size")
      let fileName = searchParams.get("fileName")
      let isAccept = searchParams.get("isAccept") === 'accept' ? true : false
      console.log('savePath', savePath)
      console.log('size', size)
      console.log('isAccept', isAccept)
      console.log('fileName', fileName)
      this.rtcfile.RecvFile(isAccept , savePath, fileName, size)

      if (isAccept === false) {
        setTimeout(() => {
          window.close()
        },800)
      }
    }
  },
  data () {
    return {
      waitting: false, // false:主叫；true：被叫
      tipName: "TEST", // 对方的名字
      tipAvatar: null, // 对方头像
      tipInfo: '音视频', //
      rtcfile: null
    }
  },
  beforeDestroy() {
    console.log('rtcFle beforeDestroy')
    // this.rtcfile.Close()
    ipcRenderer.removeAllListeners(['colseFile']);
  },
  
  mounted() {
  },
  methods: {
  }
}
</script>

<style scoped lang="scss">
.video-area {
  display: flex;
  align-items: center;
  flex-direction: column;
  width: 100%;
  height: 100%;
  z-index: 1;
  position: absolute;
  background: rgba(0, 0, 0, 0.2);
}
</style>
