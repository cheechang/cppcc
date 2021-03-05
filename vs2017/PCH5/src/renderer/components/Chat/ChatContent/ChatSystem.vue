<template>
 <div class="system-container">
  <div class="system-list" :class="{'empty-system':!systemLists.length}">
      <v-card-list>
         <v-card v-for="(item, i) in systemLists" :key="i" :title="getSysMsg(item)" :subtitle='getSubTitle(item)'>
           <div slot="left" class="system-left">
             <span class="system-left-time">{{getTimes(item.time)}}</span>
             <span class="system-left-name">{{getUserName(item)}}</span>
           </div>
           <div v-if="item.deviceType != 2 && (item.subType===201 || item.subType ===301 || item.subType === 401) " slot="right" class="system-right">
             <v-button  size="is-small" :label="$t('chat.agree')" :disable="isLockRequest" type="is-primary" @click="operClick(item, 0, i)"></v-button>
             <v-button  size="is-small" class="refuse-res" :label="$t('chat.refuse')" :disable="isLockRequest" type="is-primary" @click="operClick(item, 1, i)"></v-button>
           </div>
           <div v-if="(item.deviceType == 2 && (item.subType ===301 || item.subType === 401)) || (item.subType === 202 || item.subType === 203|| item.subType === 302|| item.subType === 303||item.subType === 402||item.subType === 403)" class="opert-info" v-text="getOpertInfo(item)" slot="right"></div>
            <i class="icon del" @click="delSystem(item, i)" slot="rightAvatar"> &#xe650;</i>
         </v-card>
      </v-card-list>
  </div>
  </div>
</template>
<script>
const sysMsgTypes =
{
  sub_buddyApply : 201,            //好友申请通知
  sub_agreeBuddyApply : 202,       //同意好友申请通知
  sub_rejectBuddyApply : 203,      //拒绝好友申请通知
  sub_groupApply : 301,            //申请入群
  sub_adminAgreeGroupAplly : 302,  //管理员同意入群
  sub_adminRejectGroupAplly : 303, //管理员拒绝入群
  sub_inviteEnterGroup : 401,      //邀请入群
  sub_agreeEnterGroup : 402,       //用户同意入群
  sub_rejectEnterGroup : 403,      //用户拒绝入群
  sub_adminKickMember : 501,       //管理员踢出群成员
  sub_dissolveGroup : 503,         //解散群
  sub_groupMemberExit : 504,       //群成员退出
};
import { mapGetters } from 'vuex';
import { getDateDiff } from '../../../../comm/time';
import { encryptionPassword } from '../../../../comm/util'
import MsgMxin from '../msgMixin';
import {  msgStructure }  from '../Msg'
export default {
  name: 'ChatSystem',
  data() {
    return {
      systemList: [],
      isLockRequest: false
    };
  },
  computed: {
    systemLists() {
      return this.systemList.sort((a, b) => b.time - a.time);
    },
    ...mapGetters(['user_account', 'chat_chatList', 'contact_contactList', 'chat_chatContent'])
  },
  created() {
    /**
     * 根据跳转时传入的Id 获取最近会话列表关于此项对应的数据
     * 如果存在unreadCount 要设置已读
     */
    this.$signalMonitor.$on('respsysMsg', resp => {
     // console.log('respsysMsg:::', resp)
     // if (this.user_account.userId !== resp.senderId && resp.subType=== sysMsgTypes.sub_rejectBuddyApply) return
      let isExsist = this.systemList.filter((e, i) => {
        if (e.applicationId === resp.applicationId) {
          this.systemList.splice(i, 1, resp);
          return e;
        }
      });
      console.log('isExsist::', isExsist)
      if (!isExsist.length) this.systemList.unshift(resp);
      // if(resp.isBurn === 0){
      //   let param ={
      //    type:resp.noStore,
      //    msgs:[resp.msgId]
      //  }
      //  this.$Service.sysMsg._sysmsg.setMessagRead(param,res =>{
      //    this.$Service.log(`setMessageRead:::::::    ${JSON.stringify(res)}`)
      //  })
      // }
    });
    /**
     * 获取系统消息
     * @param {srting} targetId 
     * @param {Number} msgId // 传入查询消息的起始ID，将从该消息的下一条消息开始查询
     * @param {Number} count  传入获取数量
     * @param {Number} flag  传入偏移标志 0 以传入的time起始，向下偏移，拉取小于time的消息 如果time = 0，代表从最新收到的系统消息开始拉取
     */
    let getSysMessagesParam = {
        targetId: '10000',
        msgId: 0, // 传入查询消息的起始ID，将从该消息的下一条消息开始查询
        count: 10, // 传入查询消息总数
        flag: 0 // 传入上一页还是下一页 向上偏移 0；向下偏移 1
    };
    this.$Service.chat.getMessages(getSysMessagesParam, resp => {
        console.log('getSysMessages', resp)
        /** 屏蔽掉对方拒绝的消息 */
        // || element.subType!== sysMsgTypes.sub_rejectBuddyApply
        //let filterMsg = resp.msgs.filter(element => this.user_account.userId=== element.senderId) 
        let filterMsg = resp.msgs;
        filterMsg.forEach(item => {
           console.log('item', item)
          if(item.subType == sysMsgTypes.sub_buddyApply && item.isPrivateMsg === 1){
              item.senderId = this.user_account.userId
              item.subType = sysMsgTypes.sub_agreeBuddyApply
           }
          else if(item.subType == sysMsgTypes.sub_buddyApply && item.isPrivateMsg === 2){
              item.senderId = this.user_account.userId
              item.subType = sysMsgTypes.sub_rejectBuddyApply
           }
        });
        this.systemList =  filterMsg
    });
  },
  beforeDestroy() {
    console.log('beforeDestroy ChatSystem.vue');
    this.$signalMonitor.$off('respsysMsg');
    this.systemList = [];
  },
  methods: {
    /** 获取系统消息用户名称 */
    getUserName(item) {
      return item.receiveId === this.user_account.userId ? item.senderName : item.receiveName
    },
    /** 展示系统消息时间 */
    getTimes(time) {
      return getDateDiff(parseInt(time), 'simple');
    },
    /** 获取附加信息 */
    getSubTitle(item) {
      return  (item.subType === sysMsgTypes.sub_buddyApply) ?item.body?`${this.$t('chat.extraInfo')}：${item.body}`: `${this.$t('chat.extraInfo')}:` : ""
    },
    /** 根据操作类型 响应添加好友、群 */
    operClick(item, opt, index) {
      this.isLockRequest = true
      let operType = -1;
      if (item.subType === sysMsgTypes.sub_buddyApply) { // 加好友请求
        if (this.contact_contactList[item.senderId]) {
         // console.log('operType::', operType)
          let toastMsg = {
            message: this.$t('search.addedFriend'),
            type: 'is-danger'
          }
          this.$toast.open(toastMsg);
          this.delSystem(item, index)
          return
        }
        this.resToAddBuddy(item.senderId, item.applicationId, opt).then(() => {
          if (opt === 0) {
            item.subType = sysMsgTypes.sub_agreeBuddyApply
            this.systemList.splice(index, 1, item)
          } else {
            item.subType = sysMsgTypes.sub_rejectBuddyApply
            this.systemList.splice(index, 1, item)
          }
          item.senderId = this.user_account.userId
          this.isLockRequest = false
        });
      } 
     /*else if (item.subType === sysMsgTypes.sub_inviteEnterGroup) {
        this.userRespToEnterGroup(item.groupId, item.applicationId, opt)
        if (opt === 0) {
            item.subType = sysMsgTypes.sub_agreeEnterGroup
        } else {
            item.subType = sysMsgTypes.sub_rejectEnterGroup
        }
        this.systemList.splice(index, 1, item)
      }
       else if (item.subType === sysMsgTypes.sub_groupApply) {
        this.resToEnterGroup(item.groupId, item.applicationId, opt).then(resp => {
          console.log('opt:::', opt,resp)

          if (resp.code === 144) {
            if (opt === 0) {
              item.subType = sysMsgTypes.sub_adminAgreeGroupAplly
              this.systemList.splice(index, 1, item)
            } else {
              item.subType = sysMsgTypes.sub_adminRejectGroupAplly
              this.systemList.splice(index, 1, item)
            }

            let deleteMessageByIdParam = {
                targetId: '10000', // 传入会话对应的ID，群或者人 this.selectActive.targetId
                msgIds: [item.msgId] // 传入要删除的消息ID集合 msgs为空，清空对应targetId的所有消息 this.selectActive.msgId
            };
            let deleteMessageByIdCb = deleteCb => {
              console.log('deleteCb:::', deleteCb)
              this.isLockRequest = false
            };
            this.$Service.chat.deleteMessageById(deleteMessageByIdParam, deleteMessageByIdCb);
          }
        })
      }*/
      else { // 响应进群
        //console.log('resToEnterGroup req',item,opt)
        this.resToEnterGroup(item.groupId, item.msgId, opt).then((resp) => {
          if (opt === 0) {
            item.subType = sysMsgTypes.sub_agreeEnterGroup
          } else {
            item.subType = sysMsgTypes.sub_rejectEnterGroup
          }
          this.systemList.splice(index, 1, item)
        });
      }
    },
    /**
     * 响应加好友的请求 
     * @param {String} userId 请求者的用户ID
     * @param {String} applicationId  请求Id
     * @param {Number} operType 操作 1：忽略，2：同意，3拒绝，4：以后不允许添加
     * @param {String} remark 好友备注
     * @param {String} refuseReason 附带的拒绝信息
     * */
    resToAddBuddy(userId, applicationId, operType) {
      return new Promise((resolve, reject) => {
        //console.log('userId:::', userId)
        let respToAddBuddyParam = {
            userId: userId, // 请求者的用户ID
            applicationId: applicationId, // 请求消息的msgId
            operType: operType, // 操作 0：同意 1拒绝
            remark: '', // 好友备注
            refuseReason: '' // 附带的拒绝信息
        };
       // console.log('respToAddBuddyParam', respToAddBuddyParam)
        this.$Service.sysMsg.respToAddBuddy(respToAddBuddyParam, resp => {
        //  this.$Service.log(`respToAddBuddy:::     ${resp.code}`)
          if (resp.code === 0) {
              resolve()

              /** 添加好友成功后给对方发送一条消息 通知 */
              if (operType === 0) {
                let msgbase = {
                  fromId: this.user_account.userId,
                  targetId: userId,
                  body:  this.$t('chat.addFriendTip'),
                  time:  new Date().getTime().toString(),
                  msgType: 2
                }
                
                this.$Service.chat.sendMessage(msgbase, resp => {
                  this.$Service.log(`sendrespToAddBuddyText::' ${resp.code}`)
                  if (resp.code === 0) {
                    /** 若页面已处于打开状态， 则需要手动显示消息 */
                    if (this.chat_chatContent[userId]) { 
                      msgbase.msgId = resp.msgId
                      msgbase.time = resp.time
                      let addMag = msgStructure(msgbase);
                      console.log('addMag:::', addMag)
                      this.$store.dispatch('SET_CHATCONTENT', addMag)
                    }
                  }
                })
              }
              
              // this.$Service.chat.sendMessage(msgbase, resp => {
              //   this.$Service.log(`sendrespToAddBuddyText::' ${resp.code}`)
              //   if (resp.code === 0) {
              //     /** 若页面已处于打开状态， 则需要手动显示消息 */
              //     if (this.chat_chatContent[userId]) { 
              //       msgbase.msgId = resp.msgId
              //       let addMag = msgStructure(msgbase);
              //       console.log('addMag:::', addMag)
              //       this.$store.dispatch('SET_CHATCONTENT', addMag)
              //     }
              //   }
              // })
          } else {
             reject(resp.code);
          }
        });
      });
    },
    /**
     * 用户被邀请进群的响应
     * @param {stirng} groupId 要进入的群Id
     * @param {stirng} applicationId  请求消息的msgId
     * @param {stirng} operType 对此请求的操作
     * @param {stirng} refuseReson 附带的拒绝消息
     */
    userRespToEnterGroup(groupId, applicationId, operType) {
      let userRespToEnterGroupParam = {
          groupId: groupId, // 请求者的用户ID
          applicationId: applicationId, // 请求消息的msgId
          operType: operType, // 操作 1：忽略，2：同意，3拒绝，4：以后不允许添加
          remark: '', // 好友备注
          refuseReason: '' // 附带的拒绝信息
      };
      console.log('userRespToEnterGroup req', userRespToEnterGroupParam)
      this.$Service.sysMsg.userRespToEnterGroup(userRespToEnterGroupParam, resp => {
        console.log('userRespToEnterGroup', resp)
        this.isLockRequest = false
      })
    },
    /**
     * 管理员同意进群的响应
     * @param {stirng} groupId 要进入的群Id
     * @param {stirng} applicationId  请求消息的msgId
     * @param {stirng} operType 对此请求的操作
     * @param {stirng} refuseReson 附带的拒绝消息
     */
    adminRespToEnterGroup(groupId, applicationId, operType) {
      return new Promise((resolve) => {
        let adminRespToEnterGroupParam = {
            groupId: groupId, // 请求者的用户ID
            applicationId: applicationId, // 请求消息的msgId
            operType: operType, // 操作 1：忽略，2：同意，3拒绝，4：以后不允许添加
            remark: '', // 好友备注
            refuseReason: '' // 附带的拒绝信息
        };
        console.log('adminRespToEnterGroupParam', adminRespToEnterGroupParam)
        this.$Service.sysMsg.adminRespToEnterGroup(adminRespToEnterGroupParam, resp => {
          resolve(resp)
          console.log('adminRespToEnterGroupParam', resp)
        })
      })

    },
    /**
     * 响应进群的请求
     */
    resToEnterGroup(groupId, msgId, operType) {
      return new Promise((resolve, reject) => {
        let respToEnterGroupParam = {
            groupId: groupId, // 要进入的群ID
            msgId: msgId, // 请求消息的msgId
            operType: operType, // 1：忽略 2：同意 3： 拒绝  4:拒绝并不允许再次请求; 被邀请进群时，只能同意或拒绝
            refuseReason: '' // 附带的拒绝信息
        };
       // console.log('respToEnterGroup req', respToEnterGroupParam);
        this.$Service.sysMsg._sysmsg.respToEnterGroup(respToEnterGroupParam, resp => {
         //   console.log('respToEnterGroup', resp);
            this.isLockRequest = false
            resolve(resp)
        });
      });
    },
    /** 删除系统消息 */
    delSystem(item, index) {
      let deleteMessageByIdParam = {
          type: item.noStore, 
          msgs: [item.msgId] 
      };
     // console.log('del sys msg:',deleteMessageByIdParam)
      let deleteMessageByIdCb = data => {
        this.isLockRequest = false
        let res = JSON.parse(data);
        if (res.code === 0){
          //console.log('deleteCb',res,index)
          this.systemList.splice(index, 1);
        }
      };
      this.$Service.sysMsg._sysmsg.deleteMessageByType(deleteMessageByIdParam, deleteMessageByIdCb);
    },
   /** 获取操作结果 */
    getOpertInfo(item) {
    //  console.log('item::', item)
      if (item.subType === sysMsgTypes.sub_agreeBuddyApply ||item.subType === sysMsgTypes.sub_agreeEnterGroup ||item.subType === sysMsgTypes.sub_adminAgreeGroupAplly) {
        return this.$t('chat.agreed');
      } else if (item.subType === sysMsgTypes.sub_rejectBuddyApply || item.subType === sysMsgTypes.sub_rejectEnterGroup ||item.subType === sysMsgTypes.sub_adminRejectGroupAplly) {
        return this.$t('chat.refused');
      }else if(item.subType === sysMsgTypes.sub_groupApply || item.subType === sysMsgTypes.sub_inviteEnterGroup){
        if(item.isFeather === 2){
          return this.$t('chat.agreed');
        }else{
          return this.$t('chat.refused');
        }
      } 
    },
   /** 获取系统消息的正文内容 */
    getSysMsg(msg) {
      //console.log('getSysMsg',msg)
      switch (msg.subType) {
        case sysMsgTypes.sub_buddyApply: { //加好友请求
         return this.$t('chat.requestFri')
        }
        case sysMsgTypes.sub_agreeBuddyApply: { //2:加好友响应
          return msg.senderId === this.user_account.userId? this.$t('chat.requestFri') : msg.body!=='' ? msg.body : this.$t('chat.passedReq')
        }
        case sysMsgTypes.sub_rejectBuddyApply: { //3:加群请求
           return msg.senderId === this.user_account.userId?this.$t('chat.requestFri') : msg.body!=='' ? msg.body : this.$t('chat.refuseReq')
        }
        case sysMsgTypes.sub_groupApply: { //4:加群响应
         return `${this.$t('chat.applyFor')} ${msg.groupName}`
        }
        case sysMsgTypes.sub_adminAgreeGroupAplly: { //4:加群响应
         return `${this.$t('chat.applyFor')} ${msg.groupName}`       
        }
        case sysMsgTypes.sub_adminRejectGroupAplly: { //4:加群响应
         return `${this.$t('chat.applyFor')} ${msg.groupName}`
        }
        case sysMsgTypes.sub_adminAgreeGroupAplly: { //4:加群响应
         return `${this.$t('chat.applyFor')} ${msg.groupName}`
        }
        case sysMsgTypes.sub_inviteEnterGroup: {
          return `${this.$t('chat.inviteJG')} ${msg.groupName}`
        }
        case sysMsgTypes.sub_agreeEnterGroup: {
         return `${this.$t('chat.inviteJG')} ${msg.groupName}`;
        }
        case sysMsgTypes.sub_rejectEnterGroup: {
         return `${this.$t('chat.inviteJG')} ${msg.groupName}`;
        }
        case sysMsgTypes.sub_adminKickMember: {
          return `${this.$t('chat.beRemovedGroup')} ${msg.groupName}`
        }
        case sysMsgTypes.sub_dissolveGroup: {
          return `${this.$t('chat.disbandGroup')} ${msg.groupName}`
        }
        case sysMsgTypes.sub_groupMemberExit: {
          return `${this.$t('chat.quitGroup')} ${msg.groupName}`
        }
      }
    }
  }
};
</script>
<style lang="scss">
.system-container{
  flex: 1;
}
.empty-system{
    background: url('~vrv-static/resources/images/common/file_empty.png')  #fff 43% 40% no-repeat !important;
    width: 100%;
    position: absolute;
}
.system-list {
background: #fff;
    height: 100%;
    padding: 6px;
    border-radius: $--border-radius-base;
    overflow: auto;
  .system-left {
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    width: 100px;
    .system-left-time {
      font-size: $--font-size-small;
      color: get-grey-color( darken-1);
      width:100%;
    }
    .system-left-name {
      font-size:$--font-size-mid;;
      color: #000;
      width:100%;
      overflow: hidden;
      text-overflow: ellipsis;
      white-space: nowrap;
    }
  }
  .system-right {
    display: flex;
    align-items: center;
    margin-right: 30px;
    .refuse-res {
      margin-left: 10px;
    }
  }
  .card {
    &:hover {
      background: none;
    }
    &:hover .del {
      display: block;
    }
    .subtitle {
      max-width: 390px;
    }
    border-bottom: solid 1px $--border-color-grey;
    .del {
      display: none;
      position: absolute;
      right: 0px;
      bottom: 14px;
      font-size: 20px;
      &:hover {
        color: $--color-msg-prompt-danger;
      }
    }
    .opert-info {
      font-size:$--font-size-mid;;
      display: flex;
      align-items: center;
      margin-right: 20px;
      padding-right: 4px;
    }
  }
}
</style>