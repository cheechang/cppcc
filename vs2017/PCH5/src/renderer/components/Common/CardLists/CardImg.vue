<template>
  <div class="v-lists-header" :style="computedLayout">
    <!-- 宽高比例 -->
    <div class="is-responsive-size" :style="computedRatio"></div>
    <!-- 主题背景 -->
    <div class="is-img theme-bgimg" :style="computedImg" v-if="!isQrcodeLayout"></div>
    <!-- 标题和底色阴影 -->
    <div class="is-responsive-content" v-if="!isQrcodeLayout">
      <div class="is-box-layout" :style="isAddBackImg">
        <div class="is-spacer"></div>
        <div class="is-section">{{name}}</div>
      </div>
    </div>
    <!-- 生成二维码 -->
    <qr-code class="qrcode-info" v-show="isQrcodeLayout" :name="name" :gender="qrcode&&qrcode.gender" :text="computedQrcodeLink" :img="img" :width="200" :height="200"></qr-code>
    <!-- 切换二维码/信息页 -->
    <card-corner v-if="hasCorner" :isQrcodeLayout="isQrcodeLayout" @layout="$emit('layout',isQrcodeLayout)"></card-corner>
  </div>
</template>
<script>
import CardCorner from './CardCorner.vue';
import { getQrcodeLink } from '../../Group/ChatGroupInfo/QrLink.js';
import QrCode from '../../Group/ChatGroupInfo/QrCode.vue';
import config from '../../../../comm/config.js';
import {isWinXp} from '../../../../comm/is.js';
export default {
  components: {
    CardCorner,
    QrCode
  },
  props: {
    img: String,
    ratio: {
      type: String,
      default: '68%'
    },
    name: String,
    sex: Number,
    isQrcodeLayout: Boolean,
    qrcode: Object,
    hasCorner: {
      type: Boolean,
      default: true
    },
    isAvatarBg: {
      type: Boolean,
      default: false
    }
  },
  computed: {
    // 个人或群头像作为背景图
    computedImg() {
      if (!this.isAvatarBg) return;
      let fileOperateParam = {
        filepath: this.img && this.img.replace(/\\/g, '\\\\'),
        type: 0
      }
      if (!this.$Service.file.fileOperate(fileOperateParam)) 
        return { 'background-image': `url(${config.defalutAvatar[this.sex]}) !important` }
      else
        return { 'background-image': `url(${this.img && this.img.replace(/\\/g, '\\\\')}) !important` }
    },
    isAddBackImg() {
      if(!isWinXp){
          return {'background-image':'linear-gradient(to top, rgba(0, 0, 0, 0.3) 0%, transparent 72px)'}
      }
      else{
          return {'background-image':'none'}
      }
    },
    // 宽高比例
    computedRatio() {
      return {
        'padding-bottom': this.ratio
      }
    },
    // 正反页
    computedLayout() {
      return {
        'padding-bottom': this.isQrcodeLayout ? '270px' : ''
      }
    },
    // 二维码链接
    computedQrcodeLink() {
      if (!this.qrcode) return;
      return getQrcodeLink(this.qrcode);
    }
  }
}
</script>
<style lang="scss">
.qrcode-info {
  // position: absolute !important;
  // width: 100%;
  // height: 100%;
  // padding: 8px;
  // display: flex;
  // justify-content: center;
  // align-items: center;
   position: absolute;
  //  top: 120px;
  //  left: -70px;
  .qrcode-logo {
    height: 80px !important;
    width: 80px !important;
    margin: auto;
    // margin: 0 auto; // 窗口最大化二维码上的头像偏移问题
    img {
      border-radius:$--border-radius-base; 
    }
  }
}
.v-lists-header {
  position: relative;
  overflow: hidden;
  flex: 1 0 auto;
  display: flex;
  @include z-index(none);  
  box-shadow: $--box-shadow-navbar;
  justify-content: center;
  .is-responsive-size {
    transition: padding-bottom 0.2s cubic-bezier(0.25, 0.8, 0.5, 1);
    flex: 0 0 0px;
  }
  .is-img {
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    border-radius: $--border-radius-base;
    @include z-index(negative);  
    position: absolute;
    background-repeat: no-repeat;
    background-size: cover;
    background-position: center center;
    @include theme_image($--background-img-primary);
  }
  .is-responsive-content {
    flex: 1 0 0px;
    .is-box-layout {
      flex-direction: column;
      height: 100%;
      display: flex;
      flex: 1 1 auto;
      flex-wrap: nowrap;
      min-width: 0;
      padding: 8px 8px !important;
      color: #fff !important;
      caret-color: #fff !important;
      // box-shadow: 0 0 20px rgba(0, 0, 0, 0.2) inset;
      background-image: linear-gradient(to top, rgba(0, 0, 0, 0.3) 0%, transparent 72px);
      .is-spacer {
        flex-grow: 1 !important;
      }
      .is-section {
        font-size: 20px;
        max-width: calc(100% - 70px);
        flex: 1 1 auto;
        flex-grow: 0 !important;
        flex-shrink: 1 !important;
        word-break: break-word;
      }
    }
  }
}
</style>