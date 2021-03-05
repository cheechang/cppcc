<template>
  <div class="type-card">
    <div class="type-card-info">
      <div class="type-card-title">
        {{getCardType()}}
      </div>
      <!-- 二维码区域 -->
      <div class="type-card-main">
      <qr-code  class="info-img" :isShowDetail="false"  :text="text" :img="cardInfo.thumbAvatar" :width="140" :height="140"></qr-code>
      <div class="type-card-info-user">
         <!-- 名片名称 -->
        <div class="type-card-user-title">
          <a class="type-card-user-name" :title="cardInfo.name" @click="openChat">{{cardInfo.name}}</a>
          <div class="card-icon-bg add-friend" v-if="isAddFrined" :title="$t('organizations.addFriend')">
            <i class="icon"  @click="add()">&#xe62c;</i>
          </div>
         </div> 
          <!-- 名片信息 手机 邮箱 豆豆号 -->
        <!-- <div class="type-card-user-phone" v-for="(item, index) in cardInfo.list"  :key="index">
          <div class="type-card-user-content" :title="item.content">{{item.content}}</div>
          <div class="card-icon-bg" :title="item.title"><i class="icon" v-html="item.icon"></i></div>
        </div> -->
      </div>
    </div>
    </div>
    <!-- 卡片状态显示 -->
    <i v-if="state===-1" class="icon" :class="{'msg-fail-self': message.messageObject.fromId === user_account.userId }" @click="sendCardMsg()">&#xe63b;</i>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import QrCode from '../../Group/ChatGroupInfo/QrCode.vue';
import ContactMixin from '../../Contact/ContactMixin';
import config from '../../../../comm/config.js';
import {getDateDiff} from '../../../../comm/time'
import { getQrcodeLink } from '../../Group/ChatGroupInfo/QrLink.js';
export default {
  data() {
    return {
      cardInfo: {
        id: '',
        name:'',
        thumbAvatar:'',
        gender:0,
        list: []
      },
      text: '',
      isLoadFinished: false,
      localId: '',
      state: 0,
      isAddFrined: false,
      type: 0,
      isFail: false
    };
  },
   mixins: [ContactMixin],
  mounted() {
    this.$nextTick(() => {
      this.cardInfo.id = this.message.messageObject.mediaUrl
      this.getCardInfo();
      /** falg 为1时 发送卡片消息 */
      if (this.message.flag === 1) {
        this.message.flag = 0;
        this.sendCardMsg()
      } else {
        this.getMsgState()
      }
    })
  },
  methods: {
    getCardType() {
      // * chatType 1 个人 chatType 2 群组 3 机器人
      if (this.type === 1) { // 个人
        return this.$t('chat.nameCard')
      } else if (this.type === 2) {  // 群组
        return this.$t('chat.groupCard')
      } else { // 机器人
        return this.$t('chat.robotCard')
      }
    },
    getMsgState() {
      let msgType = this.message.messageObject.msgType
      if (msgType === 519) {
        this.state = -1;
        this.$emit('disableRightClick')
      }
    }, 
    /**
     *  获取名片信息
     *  type 1 个人 2 群
     *  判断该好友是否是好友 是好友则使用contactList 非好友则获取陌生人信息 getUserInfo
     * */
    getCardInfo() {
      this.type = this.$Service.config.getUserTypeById({ targetId: this.cardInfo.id })
      console.log('type: ', this.type);
      console.log('id: ', this.cardInfo.id);
      /**
       *  httpHead 服务器域名
       *  link 不同的类型链接不一样
       *  type 1 uid
       *  type 2 /group/getinfo?gid=
       *  */
      // let link;
      if (this.type === 1) {
        //  link = `?uid=${this.cardInfo.id}`

        this.contact_contactList[this.cardInfo.id] 
          ? this.getContactInfo() 
          : this.getUserInfo(this.cardInfo.id).then(resp => {
              /** 自己的名片不用添加好友按钮 */
              if (this.cardInfo.id !== this.user_account.userId) {
                this.isAddFrined = true;
              }
              [this.cardInfo.name, this.cardInfo.thumbAvatar] = [resp.users.name, resp.users.thumbAvatar || config.defalutAvatar[resp.users.gender]]
              // this.cardInfo.list.push({icon: '&#xe6fa;', content: (resp.users.phones && resp.users.phones[0] && resp.users.phones[0].substring(4)) || this.$t('chat.unknown'),  title:this.$t('auth.phone')})
              // this.cardInfo.list.push({icon: '&#xe817;',  content: (resp.users.emails&&resp.users.emails[0]) || this.$t('chat.unknown'), title:this.$t('user.email')})
              // if (resp.users.acountName) this.cardInfo.list.push({icon: '&#xea29;', content:  resp.users.acountName, title: this.user_userFieldName })
              this.$nextTick(() => {
                 this.isLoadFinished = true
              })
            });
      
      } else if (this.type === 2) {
        // link = `/group/getinfo?gid=${this.cardInfo.id}`
        if (!this.contact_groupList[this.cardInfo.id]) {
          this.isAddFrined = true
        }
        this.getGroupInfo()
      } else {
        // link = `/robot/getinfo?gid=${this.cardInfo.id}`
        let appList = this.contact_appList[this.cardInfo.id]
        if (appList) {
          this.cardInfo.name = appList.name;
          this.cardInfo.thumbAvatar = appList.thumbAvatar || config.defalutAvatar[3];
          this.cardInfo.gender = 3
          this.$nextTick(() => {
            this.isLoadFinished = true
          })
          // this.cardInfo.list.push({icon: '&#xe61b;', content: appList.id, title: 'APPID' })
        } else {
          this.getAppInfo();
        }
      }
      // let httpHead = this.http_head.preLoginAddress;
      // this.text = `${httpHead}${link}&userver=${this.$userver}`
      if (this.contact_contactList[this.cardInfo.id]||this.contact_groupList[this.cardInfo.id]) {
        this.isAddFrined = false
      } else {
        this.isAddFrined = true
      }
      this.qrcode = {
        id: this.$route.query.id, 
        host: this.contact_enterpriseDicValues.isLocalHost,
        elogo: this.user_usever, 
        serverhost: this.user_serverHost,
        type: this.type
      }
      this.text = getQrcodeLink(this.qrcode);
      console.log(this.text);
    },



    /** 获取好友信息   */
    getContactInfo() {
      this.$Service.contact.getContactInfo({ userId: this.cardInfo.id }, resp => {
        console.log('获取好友信息', resp);
        [this.cardInfo.name, this.cardInfo.thumbAvatar] = [resp.name, resp.thumbAvatar || config.defalutAvatar[resp.gender]]
        // this.cardInfo.list.push({icon: '&#xe6fa;', content:  resp.phones[0] && resp.phones[0].substring(4) || this.$t('chat.unknown'), title:this.$t('auth.phone')})
        // this.cardInfo.list.push({icon: '&#xe817;', content:  resp.emails[0] || this.$t('chat.unknown'), title:this.$t('user.email')})
        // if(resp.acountName) this.cardInfo.list.push({icon: '&#xea29;', content:  resp.acountName, title: this.user_userFieldName })
        this.$nextTick(() => {
          this.isLoadFinished = true
        })
      });
    },

    /** 获取陌生人信息 */
    getUserInfo(id) {
      return new Promise(resolve => {
        this.$Service.search.getUserInfo({ userId: id }, resp => {
          console.log('获取陌生人信息', resp);
          if (resp.code === 0) resolve(resp)
        });
      })
    }, 

    /** 获取群信息 */
    getGroupInfo() {
      this.$Service.search.getGroupInfo({ groupId: this.cardInfo.id }, resp => {
        console.log('getGroupInfo', resp);
        [this.cardInfo.name, this.cardInfo.thumbAvatar] = [resp.group.info.groupName, resp.group.info.avatar || config.defalutAvatar[4]] 
        // this.cardInfo.list.push({icon: '&#xe61b;', content: resp.group.info.createrId, title: '创建者' }) 
        //  this.cardInfo.list.push({icon: '&#xe61b;', content: resp.group.info.createrId, title: this.$t('chat.creator') }) 
        // this.cardInfo.list.push({icon: '&#xe642;',  content: this.formatDate(resp.group.createTime), title: this.$t('chat.createdOn')})
        this.$nextTick(() => {
          this.isLoadFinished = true
        })
        let creater = this.contact_contactList[resp.group.info.createrId]
        creater 
         ? this.cardInfo.list[0].content = creater.name 
         :  this.getUserInfo(resp.group.info.createrId).then(resp => { this.cardInfo.list[0].content = resp.users.name })
      });
    },

    // formatDate(time) {
    //   console.log('time:::::', time)
    //   // return getDateDiff(time.toString(), false)
    //   if (time.toString().length < 13) time *= 1000;
    //   return new Date(parseInt(time)).toLocaleString().replace(/:\d{1,2}$/,' ');
    // },
    getAppInfo() {
      this.isAddFrined = true
      this.$Service.user.getAppInfo({ appId: this.cardInfo.id }, resp => {
        console.log('getAppInfo', resp);
        [this.cardInfo.name, this.cardInfo.thumbAvatar] = [resp.info.appName,resp.info.appIcon || config.defalutAvatar[3]]; 
        this.cardInfo.list.push({icon: '&#xe61b;', content: resp.info.appID, title: 'APPID' })
        this.$nextTick(() => {
          this.isLoadFinished = true
        })
      });
    },
    /** 发送名片消息 */
    sendCardMsg() {
      if (this.state !== 0) this.state = 0; // 防止消息发送失败 导致多次点击  多次发送 
      if (this.message.messageObject.msgType !== 7) {
        this.message.messageObject.msgType = 7
      }
      this.$Service.chat.sendMessage(this.message.messageObject, resp => {
        this.$Service.log(`sendCardMsg::  ${resp.code}`)
        console.log('sendCardMsg::', resp)
        /**
         * 消息发送后改变其消息ID
         * 发送成功后改变其messageID
         * 发送失败后改变其localID 防止多发
         */
        if (resp.code === 0) {
          let preMsgId = this.message.messageObject.msgId
          this.$store.commit('UPDATE_MSGID', {id:this.id, preMsgId:preMsgId, msgId: resp.msgId, isFail:this.isFail, time: resp.time})
          this.$emit('hasRead', resp.msgId)
        } else { // code 不为0  消息发送失败  将其状态变为-1
          // this.message.messageObject.localId = this.localId;
          this.state = -1;
          if (!this.isFail) {
           this.isFail = true;
          }
           if (this.$route.query.id !== this.message.messageObject.targetId) {
            this.$store.dispatch('CHANGE_CHAT_LIST_STATE', {id: this.message.messageObject.targetId, type: 2} )
          }
        }
      });
    },

    // 添加按钮操作
    add() {
      if (this.type === 1) {
        this.addFriend();
      } else if (this.type === 2) {
        //  TODO：申请加入群
        this.addGroup()
      } else {
        //  关注公众号
        this.addApplication();
      }
    },
    /** 添加好友 */
    addFriend() {
      this.$dialog.prompt({
        message: this.$t('search.verfication'),
        confirmText: this.$t('common.sure'),
        cancelText: this.$t('common.cancel'),
        inputAttrs: {
          value:  this.$t('search.iAm') + this.user_account.name
        },
        required: false,
        onConfirm: value => {
          let addContactParam = {
            userId: this.cardInfo.id,
            info: value
          };
          this.$Service.contact.addContact(addContactParam, resp => {
            if (resp.code !== 0) {
              this.$toast.open({
                message: this.$t(`ErrorCode.${resp.code}`),
                type: 'is-danger'
              });
            } else {
              this.$Service.contact.getVerifyType({userId: this.cardInfo.id}, resp => {
                console.log('获取对方好友验证方式', resp)
                let verifyInfo = {
                  1: this.$t('groups.requestSent'),
                  3: this.$t('contacts.chatNow')
                }
                console.log(resp.type,verifyInfo[resp.type])
                this.$toast.open({message: verifyInfo[resp.type], type: 'is-success'})
              })
            }
          });
        }
      });
    },

    // * 添加入群
    addGroup() {
      this.$dialog.prompt({
        message: this.$t('search.verfication')+':',
        confirmText: this.$t('common.confirm'),
        cancelText: this.$t('common.cancel'),
        inputAttrs: {value: this.$t('search.iAm') + this.user_account.name, maxlength: 60},
        required: false, // 验证信息选填
        onConfirm: value => {
          let addGroupParam = {groupId: this.cardInfo.id,verify_info: value};
          this.$Service.group.addGroup(addGroupParam, resp=>{
            this.$Service.log(`添加群请求：code:${resp.code},id:${this.cardInfo.id}`);
            let toastMsg = {message: this.$t('groups.groupRequestSent'),type: 'is-success'}
            if (resp.code !== 0) {
              toastMsg = {message: this.$t(`ErrorCode.${resp.code}`),type: 'is-danger'}
            }
            this.isAddFrined = false;
            this.$toast.open(toastMsg);
          });
        }
      });
    },

    /** 关注App 公众号 */
    addApplication() {
      this.$Service.contact.addContact({ userId: this.cardInfo.id }, resp => {
        console.log('addApplication', resp)
        if (resp.code === 0) {
          this.isAddFrined = false;
        }
      })
    },

    openChat() {
      if (this.type === 1) this.startChat(this.cardInfo, this.type)
      else if (this.type === 2) {
        if(!this.contact_groupList[this.cardInfo.id]) return;
        this.startChat(this.cardInfo, this.type)
      }
    }
  },
  computed: {
    ...mapGetters(['contact_contactList', 'contact_appList', 'contact_groupList', 'http_head', 'user_account', 'user_userFieldName', 'contact_enterpriseDicValues', 'user_usever', 'user_serverHost'])
  },
  props: { 
    message: Object,
    id: String 
  },
  components: { QrCode }
};
</script>
<style lang="scss" scoped>
.type-card {
  
  height: 204px;
  // height: 120px;
  @mixin card-flex {
  flex: 1;
  display: flex;
  align-items: center;
  font-size: $--font-size-small;
  color: get-grey-color(base);
  font-weight: 500;
}
.type-card-info {
    width: 190px;
    box-shadow: $--box-shadow-rd;
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    background: #fff;
    border-radius: $--border-radius-large;
  .type-card-title {
    width: 100%;
    color: gray;
    height: 32px;
    line-height: 32px;
    border-bottom: solid 1px gray;
    padding-left: 10px;
  }
  .type-card-main {
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    .info-img {
      // width: 120px;
      // height: 120px;
      padding: 4px;
      border-bottom-left-radius: $--border-radius-base;
      border-top-left-radius: $--border-radius-base;
      display: flex;
      align-items: center;
      img{
        border-radius:$--border-radius-base; 
      }
    }
    .type-card-info-user {
      flex: 1;
      height: 100%;
      display: flex;
      flex-direction: column;
      // padding: 10px;
      user-select: initial;
      max-width: 120px;
      .card-icon-bg {
        width: 20px;
        height: 20px;
        background: $--color-msg-prompt-middle;
        display: flex;
        align-content: center;
        justify-content: center;
        border-radius: $--border-radius-circle; 
        position: absolute;
        top: 6px;
        left: 148px;
        .icon {
          height: 100%;
          width: 100%;
          display: flex;
          align-self: center;
          align-items: center;
          font-size: $--font-size-small;
          color: #fff;
        }
        // .operate-tooltip {
        //     display: none;
        //   }
        //   &:hover .operate-tooltip {
        //     display: block;
        //   }
        //   &.add-friend{
        //     margin-left: 10px;
        //   }
      }

      .type-card-user-title {
        display: flex;
        justify-content: flex-end;
        .type-card-user-name {
          width: 130px;
          @include ellipsis;
          text-decoration:none;
          // color: #000000;
          color: $--color-msg-prompt-low;
          text-align: center;
          text-decoration-skip: $--color-msg-prompt-low;
          &:hover{
            text-decoration:underline;        
          }
        }
      }
      // .type-card-user-content {
      //   flex: 1;
      //   color: #000;
      //   @include ellipsis;
      //   text-align: end;
      //   margin-right: 10px;
      // }
      // .type-card-user-phone {
      //   @include card-flex;
      //   margin-top: 10px;
      // }
    }
  }

  }
}
</style>

