<template>
  <div class="type-text">
    <div class="text-content" :class="{'disable-select': disableSelect}" @click="openLink"  v-html="changeMessage"></div>
    <i class="icon" v-if="state === -1" :class="{'msg-fail-self': message.messageObject.fromId === user_account.userId }" @click="sendMsg">&#xe63b;</i>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import { toUnicode, utf16toEntities, doudouExpression, escapeEmoji, html2Escape, escape2Html } from '../Emoji/emoji';
import { msgStructure, MsgWebLink } from '../Msg';
import DOOD_EMOJI from '../Emoji/EmojiData/dood_emoji';
import { isWinXp } from '../../../../comm/is';
var request = require('request')
export default {
  data() {
    return {
      localId: Number,
      state: 0,
      isFail: false,
      disableSelect: false
    };
  },
  props: {
    message: Object,
    id: String,
    isOpen: Boolean,
    isMixMsg: Boolean
  },
  mounted() {
    console.log('text', this.message)
    // message.flag 1 此时需要发送消息
    if (this.message.flag === 1) {
      this.message.flag = 0; // 发送后要将其变为0 避免反复进入 反复发送
      /* 检测消息内容中是否有合法网址 */
      const reg = "^(((ht|f)tp(s?))\\://)?(www.|[a-zA-Z].)[a-zA-Z0-9\\-\\.]+\\.(com|edu|gov|mil|net|org|biz|info|name|museum|us|ca|uk|cn)(\\:[0-9]+)*(/($|[a-zA-Z0-9\\.\\,\\;?'\\\\+&amp;%\\$#\\=~_\\-]+))*$";

     !this.message.messageObject.body.match(reg) ? this.sendMsg() : this.getUrlInfo()
    } else {
      this.getMsgState()
    }
  },
  methods: {
    getMsgState() {
      let msgType = this.message.messageObject.msgType
      if (msgType === 514) {
        this.state = -1;
        this.$emit('disableRightClick')
      }
    }, 
    /** 打开网页链接 */
    openLink(e) {
      if (e.target.localName === 'a') { // 此时为网页链接
        if(isWinXp){
          console.log('e.target',e.target.textContent)
          this.$ipc.send('new-window-weburl', e.target.textContent);
        }
        else{
          this.$ipc.send('new-window-weburl', e.target.computedName);
        }
      } 
    },

    sendMsg() {
      if (this.state !== 0) this.state = 0; // 防止消息发送失败 导致多次点击  多次发送 
      console.log('sendMessage', this.message.messageObject)
      if (this.message.messageObject.msgType !== 2) {
        this.message.messageObject.msgType = 2;
      }
      this.$Service.chat.sendMessage(this.message.messageObject, resp => {
        this.$Service.log(`sendTetx::  ${resp.code}`)
        console.log('sendTetx::', resp)
        /**
         * 消息发送成功后改变其messageID
         * 消息发送失败后改变其localID 防止多发
         */
        if (resp.code === 0) {
          const preMsgId = this.message.messageObject.msgId
          this.$store.commit('UPDATE_MSGID', { id: this.id, preMsgId: preMsgId, msgId: resp.msgId, isFail: this.isFail, time: resp.time})
          this.$emit('hasRead',  resp.msgId)
        } else { 
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
    },

    /** 获取url详细信息 */
    getUrlInfo() {
      console.log('this.user_webLinkParse', this.user_webLinkParse)
      if (this.user_webLinkParse && this.user_webLinkParse !== 'pro') {
        console.log('news')
        this.$Service.log(`user_webLinkParse    ${this.user_webLinkParse}`)
          let options = {
            url:`http://analysis.linkdood.cn/analysisweb/api/analy/analyUrl?url=${encodeURIComponent(this.message.messageObject.body)}`
          };
          console.log('option', options)
          request(options,  (error, response, body)=> {
              if (!error && response.statusCode == 200) {
                console.log('body', body)
                if (body && JSON.parse(body)) {
                  let res = JSON.parse(body)
                  if (res.code === 0) {
                    let msgObject = Object.assign({}, this.message.messageObject)
                    msgObject.url = res.urlContent.url;
                    msgObject.title = res.urlContent.title;
                    msgObject.msgType = 9;
                    msgObject.desc = res.urlContent.description;
                    msgObject.img = res.urlContent.imgPath;
                    let msgWeb = new MsgWebLink(msgObject, 1);
                    console.log('JSON', JSON.stringify(msgWeb))
                    this.$store.commit('REPLACE_CHATCONTENT', {id: this.id, msg: msgWeb});
                    this.$emit('handleScrollBottom')
                  } else {
                    this.sendMsg(); 
                  }
                }
              } else {
                this.sendMsg(); 
              }
          })
        return
      }
      let getUrlInfoCb = resp => {
        console.log('resp::', resp)
        if (resp.code === 0) {
          let msgObject = Object.assign({}, this.message.messageObject)
          msgObject.url = resp.url;
          msgObject.title = resp.title;
          msgObject.msgType = 9;
          msgObject.desc = resp.des;
          msgObject.img = resp.imgPath;
          let msgWeb = new MsgWebLink(msgObject, 1);
          this.$store.commit('REPLACE_CHATCONTENT', {id: this.id, msg: msgWeb});
        } else {
          this.sendMsg(); 
        }
      }
      this.$Service.chat.getUrlInfo({ url: this.message.messageObject.body }, getUrlInfoCb);
    },
  },
  computed: {
    /**
     * 将各种文本消息转为可视消息
     */
    changeMessage() {
      let msg = this.message.messageObject.body; // 消息正体
      console.log('msg:::', msg)
      /**
       * 消息body 中如果包含&:flash 则为抖一抖消息
       * 手机发过来的抖一抖消息 可能携带内容
       * 若没有携带消息 可直接返回抖一抖
       */
      if (msg.includes('&:flash')) { 
         msg = msg.replace('&:flash', ''); // 如果替换掉&:flash 消息为空 直接返回[抖一抖]
         if (msg === '') {
           this.disableSelect = true
          //  return msg = '[抖一抖]';
          return msg = this.$t('msgType.1003')
         }
      }
      
      if (msg.includes('&:delete|')) {
         this.disableSelect = true
        // return  msg = '[橡皮擦]'
        if (msg.includes('&:delete|today')) {
          return msg = msg.replace('&:delete|today', this.$t('msgType.1004'))
        } else {
          return msg = msg.replace('&:delete|all', this.$t('msgType.1004'))
        }
        //  return msg =  msg.replace('&:delete|today', this.$t('msgType.1004')) ||  msg.replace('&:delete|all', this.$t('msgType.1004'))
      }


      /**
       * 普通字符转换成转意符各种标签
       */
      msg = html2Escape(msg);
      console.log('msg:::::::::', msg)
      /**
       * 恢复所有的消息格式 如 空格 换行
       */
      msg = msg.replace(/\n/g, '<br/>').replace(/\s/g, ' ');



      /**
       * regs 检测所有的表情 正则匹配可能不完全(有待测试)
       * regUrl 检测所有的 网页链接 并将其替换为a链接   /\uD83C[\uDF00-\uDFFF]|\uD83D[\uDC00-\uDE4F]/
       */
      let regUrl = /(http|ftp|https|www):\/\/[\w\-_]+(\.[\w\-_]+)+([\w\-.,@?^=%&:/~+#]*[\w\-@?^=%&/~+#])?/g;
      msg = escapeEmoji(msg)
      if (regUrl.test(msg)) { 
        msg = msg.replace(/&amp;/g, '&')
        let urlText
        if (this.id !== this.user_account.userId) {
           urlText = this.message.messageObject.fromId === this.user_account.userId && !this.isMixMsg ? 'text-url-mine' : 'text-url-other'
        } else {
          urlText = this.message.messageObject.deviceType === 1 ? 'text-url-mine' : 'text-url-other'
        }
        msg = msg.replace(regUrl, (a, b, c) => `<a class=${urlText}>${a}</a>`)
      }
      return msg;
    },
    ...mapGetters(['user_account', 'contact_contactList', 'user_bad_word_mode', 'user_webLinkParse'])
  }
};
</script>
<style lang="scss">
.type-text {
  display: flex;
  .text-content {
    padding: 6px 10px;
    user-select: text;
    font-size: 0.85rem;
    font-weight: 500;
    letter-spacing: 0.5px;
    white-space: pre-wrap;
    max-width: 400px;
    word-break:break-word;
    .text-url-other {
      text-decoration: underline;
      color: get-blue-color(accent-3);
      &:hover {
        color: $--color-text-hover-primary;
      }
    }

    .text-url-mine {
      text-decoration: underline;
      color: #fff;
      &:hover {
        color: $--color-text-extra-light;
      }
    }
    .v-text-emoji {
      width: 21px;
      height: 21px;
      margin-right: 3px;
      user-select: none;
    }
    &.disable-select {
      user-select: none;
    }
  }
}
</style>
