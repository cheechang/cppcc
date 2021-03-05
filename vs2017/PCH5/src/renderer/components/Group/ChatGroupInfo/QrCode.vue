<template>
  <div ref="qrcodeBox" class="qrcode-box">
    <div class="qrcodes-mix-img">
      <div class="qrcodes" ref="qrcode"></div>
      <v-avatar :src="img" :sex="gender" class="qrcode-logo" size=""></v-avatar>
    </div>
    <div class="qrcode-box-info" v-show="isShowDetail">
      <div class="qrcode-server">{{user_account.server + $t('contacts.server') +" "+ name}}</div>
      <div>{{ $t('contacts.qrScan') }}</div>
      <!--<div class="qrcode-copy" @click="createQrImg">{{ $t('contacts.qrCopy') }}</div>-->
    </div>
    <slot></slot>
  </div>
</template>
<script>
import QRCode from 'qrcodejs2'
import html2canvas from 'html2canvas';
const { clipboard, nativeImage } = require('electron')
import { mapGetters } from 'vuex'
export default {
  props: {
    text: String,
    img: String,
    width: { // 二维码宽度
      type: Number,
      default: 100
    },
    height: { // 二维码高度
      type: Number,
      default: 100
    },
    gender: { // 根据gender作为下标获取Config配置文件的默认头像
      type: Number,
      default: 0
    },
    name: String,
    isShowDetail: { // 好友、群二维码信息和复制功能
      type: Boolean,
      default: true
    }
  },
  data() {
    return {
      qrcode: ''
    };
  },
  computed: {
    ...mapGetters(['user_account'])
  },
  mounted() {
    this.$nextTick(()=>{
      this.createQrcode();
    })
  },
  watch: {
    text(value) {
      this.qrcode.makeCode(value)
    }
  },
  methods: {
    createQrcode () {
      this.qrcode = new QRCode(this.$refs.qrcode, {
        width: this.width,    // 设置宽度
        height: this.height,  // 设置高度
        text: this.text
      })
    },
    createQrImg(event) {
      event.preventDefault();  
      html2canvas(this.$refs.qrcodeBox, {allowTaint: true}).then((canvas)=> {
        this.$toast.open({ message: this.$t('contacts.copied'), type: 'is-info' })
        let qrcodeDataURL = canvas.toDataURL();
        let qrcodeImg = nativeImage.createFromDataURL(qrcodeDataURL)
        clipboard.writeImage(qrcodeImg)
      });
    }
  }
};
</script>
<style lang="scss">
.qrcode-box {
  // position: relative;
  // // position: relative !important;  // xp版本偶现二维码显示偏移问题
  // width: 100%;
  height: 100%;
  display: flex;
  justify-content: center;
  align-items: center;
  flex-direction: column;
  // position: absolute;
  top: 0;
  left: 0;
  width: 100%;
  .qrcodes-mix-img {
    display: flex;
    align-items: center;
    justify-content: center;
    position: relative;
    .qrcodes {
      img {
        margin: 0 auto;
      }
    }
    .qrcode-logo {
      margin: auto;
      position: absolute;
      width: 40px;
      height: 40px;
      top: 0px;
      // top: 60px;  // 窗口最大化二维码上的头像偏移问题
      left: 0px;
      bottom: 0px;
      right: 0px;
      background: #fff;
      border: solid 2px #fff;
      // box-shadow: 0px 0px 12px 1px #dfdfdf;
      border-radius: $--border-radius-base;
    }
  }
}

.qrcode-box-info {
  // position: absolute;
  // bottom: 86px;
  // top: 100%;
  width: 100%;
  font-size: 14px;
  text-align: center;
  color: #000;
  .qrcode-copy {
    cursor: pointer;
    text-decoration: underline;        
  }

  .qrcode-server {
    margin-bottom: 20px;
  }
}
</style>