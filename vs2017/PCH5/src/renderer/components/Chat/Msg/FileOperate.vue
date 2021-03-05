<template>
  <div class="file-operate">
    <span class="file-operate-btn" v-if="appOperate" @click="fileOpera(2)">
      {{addOpeateName}}
    </span>
    <span class="file-operate-btn" @click="fileOpera(1)">
      {{normalOperat}}
    </span>
  </div>
</template>
<script>
/**
 * @file      File message bubble operate display management.
 * @author    linpeiyuan <linpeiyuan@vrvmail.com.cn>
 * @date      2019.11.25
 * @copyright Beijing VRV Software Co.,Ltd
 * 
 */ 
  import { mapGetters } from 'vuex'
  const FILE_DICVALUE = 'isOpenInOtherApp';
  const fileOperateComponent = {
    DOWNLOAD : 1,
    PROGRESS: 2,
    OPEN: 3,
    REDOWN: 4,
    REUPLOAD: 5,
    RTCTIP: 6
  };
  export default {
    name: 'file-operate',
    props: {
      rtcErrorTip: String,
      operateComponent: Number,
      isEcrypted: Boolean
    },
    data() {
      return {
        appOperate: false,
        addOpeateName: ''
      };
    },
    computed: {
      ...mapGetters(['chat_chatDicValue']),
      normalOperat() {
        if (this.operateComponent === fileOperateComponent.DOWNLOAD) {  //  文件未下载情况
          this.appOperate = false;   //  暂时不显示下载按钮
          // this.addOpeateName = this.$t('chat.download');
          return this.$t('chat.saveAs');
        }
        if (this.operateComponent === fileOperateComponent.OPEN) {  //  文件已下载情况
          this.appOperate = false;
          if(!this.chat_chatDicValue[FILE_DICVALUE] || this.chat_chatDicValue[FILE_DICVALUE] === '1') {
            this.appOperate = true;
            this.addOpeateName = this.$t('chat.open');
          }
          console.log(this.chat_chatDicValue, FILE_DICVALUE);
          return this.$t('chat.openFileLocation');
        }

        if (this.operateComponent === fileOperateComponent.REDOWN) {
          this.appOperate = false;
          this.addOpeateName = ''
          return this.$t('chat.saveAs');
        }

        if (this.operateComponent === fileOperateComponent.REUPLOAD) {
          this.appOperate = false;
          this.addOpeateName = ''
          return this.$t('chat.reUpload') 
        }

        if (this.operateComponent === fileOperateComponent.RTCTIP) {
          this.appOperate = true;
          this.addOpeateName = this.$t('chat.resend')
          return this.$t('chat.sendOffline')
        }
        return '';
      },
    },
    methods: {
      fileOpera(op) { 
        this.$emit('receiveEvent', op); 
      }
    }
  }
</script>
<style lang="scss" scoped>
  .file-operate{
    flex: 1;
    display: flex;
    justify-content: flex-end;
    align-items: center;
    font-size: $--font-size-small;
    color:get-blue-color(darken-4);
    padding-right: 12px;
    height: 30px;
    .file-operate-btn{
      margin-right: 4px;
      &:hover {
      cursor: pointer;
      }
    }
  }
</style>