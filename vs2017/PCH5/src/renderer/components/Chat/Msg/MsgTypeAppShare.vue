<template>
  <div class="app-share" @click="openApp">
    <div class="app-container">
      <div class="app-info">
        <div class="app-share-avatar">
            <img class="app-img" :src="getImg" @error="imgError" />
        </div>
        <div class="app-content" :class="{'app-content-mine': message.messageObject.fromId === user_account.userId}">
          <div class="app-title" v-if="message.messageObject.appName" v-html="message.messageObject.appName" :title="message.messageObject.appName"></div>
          <div class="app-description" v-if="message.messageObject.appTypeName" v-html="message.messageObject.appTypeName" :title="message.messageObject.appTypeName"></div>
        </div>
      </div>
    </div>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';

import { getErrorMsg } from '../../../utils/utils.js'
export default {

  props: {
    message: Object,
    id: String,
  },
  mounted () {
    this.$nextTick(() => {
      /** falg 为1时 发送卡片消息 */
      if (this.message.flag === 1) {
        this.message.flag = 0;
        this.sendAppShareMsg()
      } else {
        this.getMsgState()
      }
    })
  },
  computed: {
     ...mapGetters(['user_account','user_headImgPath','work_storeApps']),
    getImg () {
      return (this.message.messageObject.appIcon === '' ? this.defaultImg: this.user_headImgPath + this.message.messageObject.appIcon);
    },
  },
  methods: {
    imgError(e) {
      e.target.src = this.defaultImg;
    },
    getMsgState() {
      let msgType = this.message.messageObject.msgType
      if (msgType === 521) {
        this.state = -1;
        this.$emit('disableRightClick')
      }
    }, 
    openApp(){
      // 打开App
      let appInfo = JSON.parse(this.message.messageObject.body);
      appInfo.mainUrl = this.getLocalAppUrlBySign(appInfo);
      this.appNewWindow(appInfo);
      // 如果该应用未安装则进行安装
      if(this.work_storeApps[appInfo.appID.toString()] && (this.work_storeApps[appInfo.appID.toString()] !== 1)){
        this.$Service.user.addOrDeleteApplication(
            {type: 2, appID: appInfo.appID.toString()},
            resp => {
              this.$Service.log(`添加应用返回:::${resp.code}`)
              if (resp.code === 0) {
                this.getSdkSortApps();
                this.$store.commit('SET_STOREAPPS', {flag: 1, val: 1, id: appInfo.appID.toString()});
              }
            }
        );
      }
    },
    sendAppShareMsg () {
       if (this.state !== 0) this.state = 0; // 防止消息发送失败 导致多次点击  多次发送 
       if (this.message.messageObject.msgType !== 36) {
         this.message.messageObject.msgType = 36
       }
       this.$Service.chat.sendMessage(this.message.messageObject, resp => {
        if (resp.code === 0) {
          //this.$toast.open({message: this.$t('common.shareSucc'), type: 'is-success'})
          const preMsgId = this.message.messageObject.msgId
          this.$store.commit('UPDATE_MSGID', { id: this.id, preMsgId: preMsgId, msgId: resp.msgId, isFail: this.isFail, time: resp.time })
          this.$emit('hasRead', resp.msgId)
          // if (this.message.messageObject.activeType === 1)  this.$emit('hasRead',  resp.msgId)
        } else {
          //this.$toast.open({message: getErrorMsg(resp.code), type: 'is-danger'}); 
          // this.message.messageObject.localId = this.localId;
          this.state = -1; // code 不为0  消息发送失败  将其状态变为-1
          if (!this.isFail) {
            this.isFail = true;
          }
          if (this.$route.query.id !== this.message.messageObject.targetId) {
            this.$store.dispatch('CHANGE_CHAT_LIST_STATE', {id: this.message.messageObject.targetId, type: 2} )
          }
        }
      });
    }
  },
  data () {
    return {
      state: 0,
      defaultImg:  require('vrv-static/resources/images/auth/app.png'),
      localId: 0,
      isFail: false
    };
  }
};
</script>
<style lang="scss" scoped>
@mixin ellipsis {
  overflow: hidden;
  text-overflow: ellipsis;
  -webkit-text-overflow: ellipsis;
  white-space: nowrap;
}
  .app-container-self {
    color: #fff!important;
      .app-title {
        color: #fff!important;
      }
      .app-description {
        color: #fff!important;
      }
  }
.app-container {
  width: 225px;
  height: 100px;
  display: flex;
  justify-content: center;
  flex-direction: column;
  padding: 10px;
  color: get-blue-color(accent-3);
  .app-info {
    flex: 1;
    display: flex;
    padding: 6px;
    //border-bottom: solid 1px $--border-color-grey;
    .app-share-avatar{
        width: 80px;
        height: 80px;
        border-radius: 18px;
        //position: relative;
        overflow: hidden;
        flex-shrink: 0;
        //box-shadow: 0px 3px 5px -1px rgba(0, 0, 0, 0.2), 0px 6px 10px 0px rgba(0, 0, 0, 0.14), 0px 1px 18px 0px rgba(0, 0, 0, 0.12);
       .app-img {
          width: inherit;
          height: inherit;
          object-fit: cover;
       }
    }
    .app-content {
      margin-left: 10px;
      flex: 1;
      display: flex;
      flex-direction: column;
      .app-title {
        width: 110px;
        @include ellipsis;
        color: #000;
        padding-top: 10px;
      }
      .app-description {
        color:get-grey-color(base);
        font-size: $--font-size-small;
        width: 110px;
        padding-top: 15px;
        //max-height: 52px;
        display:-webkit-box;
        -webkit-line-clamp:2;
        -webkit-box-orient:vertical;
        overflow:hidden;
      }
    }
    .app-content-mine{
      .app-title {
        color: #fff;
      }
      .app-description {
        color: #fff;
      }
    }
  }
}
</style>
