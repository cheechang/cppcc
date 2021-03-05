<template>
      <div class="rtc-operate">
        <div class="rtc-btn-area"  >
        <span class='file-operate-btns' v-for="(item, index) in operateList" :key="index" @click='fileOpera(index)'>
          {{item}}
        </span>
        </div>
        <!-- <div class="rtc-operate-more" @mouseenter="operateMore=true" @mouseleave="operateMore=false" v-else>
          <i class="icon " >&#xe604;
          </i>
          <transition  name="zoom-in-bottom">
            <v-menu v-show="operateMore" class="file-opera-menu"  @selectItem="selectItem"  :menuList="operateList" ></v-menu>
          </transition>
        </div> -->
      </div>

</template>
<script>
const fileOperateComponent = {
      DOWNLOAD : 1,
      RTCTIP: 2,
      SEND: 3,
      CANCEL: 4
}
export default {
  data() {
    return {
      isNeedList: true,
      operateList: [],
      operateMore: false
    }
  },
  props: {
    operateComponent: Number
  },
  mounted() {
    console.log('operate--mounted', this.operateComponent)
    this.loadBtn()
  },
  methods: {
    fileOpera(index) {
      console.log('index', index)
      this.$emit('receiveEvent', index)
    },
    selectItem(index) {
      console.log('selectItem', index)
      this.$emit('receiveEvent', index)
    },
    loadBtn() {
      if (this.operateComponent === fileOperateComponent.DOWNLOAD) {
        // this.isNeedList = true
        // this.operateList = ['下载', '另存为', '取消']
        this.operateList = [this.$t('chat.download'), this.$t('chat.saveAs'), this.$t('common.cancel')]
      }

      if (this.operateComponent === fileOperateComponent.SEND) {
        // this.isNeedList = true
        // this.operateList = ['离线发送', '取消']
        this.operateList = [this.$t('chat.sendOffline'), this.$t('common.cancel')]
      }

      if (this.operateComponent === fileOperateComponent.CANCEL) {
        // this.isNeedList = true
        // this.operateList = ['取消']
        this.operateList = [this.$t('common.cancel')]
      } else if (this.operateComponent === fileOperateComponent.RTCTIP) {
        // this.isNeedList = true
        // this.operateList = ['重新发送', '离线发送']resend
        this.operateList = [this.$t('chat.resend'), this.$t('chat.sendOffline')]
      }
    }
  },
  watch: {
    operateComponent() {
      console.log('operateComponent', this.operateComponent)
      this.loadBtn()
    }
  }
}
</script>
<style lang="scss" >
.rtc-operate {
  flex: 1;
  display: flex;
  justify-content: flex-end;
  align-items: center;
  .rtc-btn-area{
    display: flex;
    .file-operate-btns {
    margin-left: 4px;
    font-size: $--font-size-small!important;
    line-height: 12px;
    color: get-blue-color(darken-3);
    &:hover {
      cursor: pointer;
      color: #000
    }
    }
  }

  .rtc-operate-more {
    position: relative;
    display: flex;
    .icon {
      height: 12px;
      font-size: 13px;
      line-height: 12px;
      color: #ccc;
      margin-right: 5px;
      transform: rotate(90deg);
    }

    .file-opera-menu {
      position: absolute;
      left: -60px;
      top: 12px;
      .dropdown-item {
        font-size: $--font-size-small;
      }
    }
  }
}
</style>
