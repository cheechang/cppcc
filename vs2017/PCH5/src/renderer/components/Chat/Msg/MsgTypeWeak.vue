<template>
  <div class="type-tip-msg">
    <span class="tip-body">
      <i class="icon icon-tip-msg">&#xe7fb;</i>
      <span v-html="msgBodyTypes"></span>
    </span>
  </div>
</template>
<script>
import { mapGetters } from "vuex";
import { getDateDiff } from "../../../../comm/time";
import { SubType } from  '../../../../rtc/file/constant'
export default {
  props: {
    message: Object
  },
  data() {
    return {
      isMine: false
    }
  },
  mounted() {
    console.log("message weak", this.message);
    this.isMine = this.message.messageObject.fromId === this.user_account.userId
  },
  computed: {
    ...mapGetters(["user_account"]),
    msgBodyTypes() {
      let result = "";
      console.log("weakmsgBodyTypes",this.message.messageObject);
      switch (parseInt(this.message.messageObject.tipType)) {
        case 8: {
          // 下载文件后发送的弱提示
          console.log("file-weak");

          let deviceInfo =
            this.message.messageObject.deviceType === 1
              ? this.$t("chat.compute")
              : this.$t("chat.mobile");
          result =
            this.isMine
              ? this.$t("chat.receiveFile", {
                  value: this.message.messageObject.fileInfo
                })
              : this.$t("chat.sendFileTip", {
                  device: deviceInfo,
                  value: this.message.messageObject.fileInfo
                });
          break;
        }
        case 3: {
          // 群弱提示
          //operType取值： 0：usersInfo加入该群 1：operUser邀请usersInfo加入该群 2：operUser同意usersInfo加入该群
          //3：usersInfo退出该群  4：usersInfo被operUser移除该群
          console.log("group-weak");
          // result = this.message.messageObject.body;
          switch (this.message.messageObject.operType) {
            case -1:
            case 0: { // 加入该群
              //  joinGroupTip: "{ userInfo } 加入该群",
              // inventGroupTip: "{operUser} 邀请 {userInfo} 加入该群",
              // agreenGroupTip: "{operUser} 同意 {userInfo} 加入该群",
              // quitGroupTip: "{ userInfo } 退出该群",
              // removeGroupTip: "{ userInfo } 被 { operUser } 移除该群",
              // result = `${this.message.messageObject.userInfo}加入该群`
              result = this.$t("chat.joinGroupTip", {
                userInfo: this.message.messageObject.userInfo
              });
              break;
            }
            case 1: { // 邀请加入该群
              // result = `${this.message.messageObject.operUser}邀请${this.message.messageObject.userInfo}加入该群`
              result = this.$t("chat.inventGroupTip", {
                operUser: this.message.messageObject.operUser,
                userInfo: this.message.messageObject.userInfo
              });
              break;
            }
            case 2: { // 同意
              // result =  `${this.message.messageObject.operUser}同意${this.message.messageObject.userInfo}加入该群`
              result = this.$t("chat.agreenGroupTip", {
                operUser: this.message.messageObject.operUser,
                userInfo: this.message.messageObject.userInfo
              });
              break;
            }
            case 3: { // 退出该群
              // result = `${this.message.messageObject.userInfo}退出该群`
              result = this.$t("chat.quitGroupTip", {
                userInfo: this.message.messageObject.userInfo
              });
              break;
            }
            case 4: { // 移除该群
              // result = `${this.message.messageObject.userInfo}被${this.message.messageObject.operUser}移除该群`
              result = this.$t("chat.removeGroupTip", {
                operUser: this.message.messageObject.operUser,
                userInfo: this.message.messageObject.userInfo
              });
              break;
            }
            case 5: { // 群名称修改
              result = this.$t('chat.reNameGroup', {operUser : this.message.messageObject.operUser})
			      	break;
            }
            case 6: { // 群转让
              result = this.message.messageObject.operUser+ ' 新增一条置顶消息'
              break;
              }
            case 7: { // 群转让
              result = this.message.messageObject.operUser+' 撤销一条置顶消息'
			      	break;
            }
            default: {
              result = this.message.messageObject.body
              break;
            }
          }
          break;
        }

        case 4: {
          // 阅后回执
            // 手机缺少time字段，翻译英文时特殊处理
            let devices = this.message.messageObject.deviceType
            let deviceType = devices === 1 ?  this.$t("chat.fromPC") : this.$t("chat.fromMobile");
            let time;
            // * 移动端目前传过来的tipTime 有误  暂不显示 
            this.$Service.log(`tipTime:::${this.message.messageObject.tipTime||''} `)
            if (devices === 1) {
              time = this.message.messageObject.tipTime ? getDateDiff(parseInt(this.message.messageObject.tipTime)) : '';
            } else {
              time = ''
            }
            this.$Service.log(`receiptTime:::${time||''} `)
            if (!this.isMine) { // 我响应的阅后回执
              if(this.message.messageObject.limitRange&&this.message.messageObject.limitRange.length) {
                result = devices === 1 ? 
                        this.$t("chat.respondReadReceipt", { value: this.message.messageObject.operUser, device: deviceType, time: time }) 
                        : this.$t("chat.respondReadReceiptByMobile", { value: this.message.messageObject.operUser, device: deviceType, time: time }) 
              } else if (this.message.messageObject.relatedUsers&& this.message.messageObject.relatedUsers.length) {
                console.log('this.message.messageObject.relatedUsers', this.message.messageObject.relatedUsers)
                if (this.message.messageObject.relatedUsers.includes(this.user_account.userId)) { // XX 已看过我的消息
                  result = devices === 1 ? 
                        this.$t("chat.respondReadReceipt", { value: this.message.messageObject.operUser, device: deviceType, time: time }) 
                        : this.$t("chat.respondReadReceiptByMobile", { value: this.message.messageObject.operUser, device: deviceType, time: time }) 
                } else {  //  operUser 看过 userInfo 的消息
                  // result = `${this.message.messageObject.operUser}已经看过${this.message.messageObject.userInfo}的阅后回执消息`
                  result = this.$t("chat.respondOtherReceipt", { operUser: this.message.messageObject.operUser, userInfo: this.message.messageObject.userInfo, device: deviceType, time: time}) 
                }
              } else { // 人和人
                result = devices === 1 ? 
                        this.$t("chat.respondReadReceipt", { value: this.message.messageObject.operUser, device: deviceType, time: time }) 
                        : this.$t("chat.respondReadReceiptByMobile", { value: this.message.messageObject.operUser, device: deviceType, time: time }) 
              } 
            } else { // 自动回复XX 的阅后回执
              result = this.$t("chat.respondAutoReadReceipt", { value: this.message.messageObject.userInfo, device: deviceType, time: time });
            }
          break;
        }
        case 5: {
          // 橡皮擦
          // result = this.readReceipt(this.message, false, true);
          // result = this.message.messageObject.fromId === this.user_account.userId
          //  ?  `您${this.message.messageObject.operType == 1 ? '接受' : '拒绝'}了${this.message.messageObject.userInfo}的删除请求`
          //  : `${this.message.messageObject.operUser}${this.message.messageObject.operType == 1 ? '同意' : '拒绝'}了我的删除请求`
          result =
            this.isMine
              ? this.$t("chat.respondOtherDelMsg", {
                  value:
                    this.message.messageObject.operType == 1
                      ? this.$t("chat.accept")
                      : this.$t("chat.reject"),
                  user: this.message.messageObject.userInfo
                })
              : this.$t("chat.respondDelMsg", {
                  value:
                    this.message.messageObject.operType == 1
                      ? this.$t("chat.agree")
                      : this.$t("chat.reject"),
                  user: this.message.messageObject.operUser
                });
          break;
        }
        case 6: {
          // result = this.message.messageObject.fromId !== this.user_account.userId
          // ? `我响应了${ this.message.messageObject.userInfo } 的抖一抖`
          // : `${ this.message.messageObject.operUser }响应了我的抖一抖 `;
          result =
            !this.isMine
              ? this.$t("chat.respondMeShaking", {
                  value: this.message.messageObject.operUser
                })
              : this.$t("chat.respondOtherShaking", {
                  value: this.message.messageObject.userInfo
                });
          break;
        }
        case 12: {
          //音视频提示信息
          switch (this.message.messageObject.operType) {
            case 1: 
            {
              let userInfo = this.parseP2pUserInfo(this.message.messageObject.userInfo);
              result = this.$t("chat.videoWeakMsgOperType1", {
                  userName: userInfo.userName,
                  recvMediaName: userInfo.recvMediaName,
                  deviceName: userInfo.deviceName
              })
              break;
            }
            case 2:
            {
              let userInfo = this.parseP2pUserInfo(this.message.messageObject.userInfo);
              result = this.$t("chat.videoWeakMsgOperType2", {
                  userName: userInfo.userName,
                  recvMediaName: userInfo.recvMediaName,
                  deviceName: userInfo.deviceName
              })
              break;
            }
            case 3:
            {
              let userInfo = this.parseP2pUserInfo(this.message.messageObject.userInfo);
              result = this.$t("chat.videoWeakMsgOperType3", {
                  userName: userInfo.userName,
                  sendMediaName: userInfo.sendMediaName,
                  deviceName: userInfo.deviceName
              })
              break;
            }
            case 4:
            {
              let userInfo = this.parseP2pUserInfo(this.message.messageObject.userInfo);
              result = this.$t("chat.videoWeakMsgOperType4", {
                  userName: userInfo.userName,
                  sendMediaName: userInfo.sendMediaName
              })
              break;
            }
            case 5: {
              result = this.$t('rtc.weaknet');
              break
            }
            case 21:
            {
              let userInfo = this.parseMulUserInfo(this.message.messageObject.userInfo);
              result = this.$t("chat.videoWeakMsgOperType21", {
                  operUserName: userInfo.operUserName,
              })
              break;
            }
           case 22:
            {
              result = this.$t("chat.videoWeakMsgOperType22")
              break;
            }
            case 23:
            {
              let userInfo = this.parseMulUserInfo(this.message.messageObject.userInfo);
              result = this.$t("chat.videoWeakMsgOperType23", {
                  operUserName: userInfo.operUserName,
                  callName:userInfo.callName
              })
              break;
            }
            case 24:
            {
              let userInfo = this.parseMulUserInfo(this.message.messageObject.userInfo);
              result = this.$t("chat.videoWeakMsgOperType24", {
                  operUserName: userInfo.operUserName,
                  callName:userInfo.callName
              })
              break;
            }
            case 25:
            {
              let userInfo = this.parseMulUserInfo(this.message.messageObject.userInfo);
              result = this.$t("chat.videoWeakMsgOperType25", {
                  operUserName: userInfo.operUserName,
                  deviceName:userInfo.deviceName,
                  callName:userInfo.callName
              })
              break;
            }
            case 26:
            {
              let userInfo = this.parseMulUserInfo(this.message.messageObject.userInfo);
              result = this.$t("chat.videoWeakMsgOperType26", {
                  operUserName: userInfo.operUserName,
                  deviceName:userInfo.deviceName,
                  callName:userInfo.callName
              })
              break;
            }
            default: {
              try {
                let type = this.message.messageObject.operType
                let fileName = JSON.parse(this.message.messageObject.fileInfo).filename
                let isSenderActed = this.message.messageObject.body.includes('发送方')
                console.log('default::::', type, fileName)
                console.log('isMine:::'+this.message.messageObject.fromId, this.user_account.userId)
                if (type===SubType.CANCEL_SENDER||type===SubType.CANCEL_RECEIVER) { // 发送方（接收方）取消
                  result = this.isMine ?
                        `您取消了【${fileName}】的${isSenderActed?'发送':'接收'}，文件传输失败`
                        :`对方取消${isSenderActed?'发送':'接收'}【${fileName}】，文件传输失败`
                } else if (type===SubType.BUSY_SENDER||type===SubType.BUSY_RECEIVER) { // 发送方（接收方）忙
                  result = `${this.isMine ? '您':'对方'}正在文件直传`
                } else if (type===SubType.TIMEOUT) { // 发送方（接收方）超时
                  result = `${this.isMine?'对方':'您'}长时间未响应，文件【${fileName}】被取消`
                } else if (type===SubType.REFUSE) {
                  result = `${this.isMine?'您':'对方'}取消${isSenderActed?'发送':'接收'}【${fileName}】，文件传输失败`
                } else {
                  result = this.message.messageObject.body;
                } 
              } catch (error) {
                result = this.message.messageObject.body;
              }
              break;
            }
          }
          break;
        }
        case 9: { // ios单次阅读截屏后，管理员/群主/发送人将接收并显示对方已截屏弱提示
          let isBurnMsgSender = this.message.messageObject.relatedUsers.includes(this.user_account.userId)
          result = this.$t("chat.burnMsgScreenTip", {
            time: this.message.messageObject.tipTime ? getDateDiff(parseInt(this.message.messageObject.tipTime)) : '',
            userName: this.message.messageObject.operUser,
            operUserName: isBurnMsgSender?this.$t('chat.your'):this.message.messageObject.userInfo,
          });
          break;
        }
        default: {
          result = "";
          break;
        }
      }
      return result;
    }
  },
  methods: {
    /**
     * 当音视频提示信息时且为单点音视频版本时解析userInfo字段
     * 如:"deviceType=1,mediaType=2,userId=123456789,userName=王某某"
     */
    parseP2pUserInfo(userInfo) {
      let info = {};
      userInfo.split(",").forEach(element => {
        let tempArry = element.split("=");
        console.log(tempArry[0]);
        info[tempArry[0]] = tempArry[1];
      });
      if (info.deviceType) {
        if (info.deviceType === "1") {
          info.deviceName  = this.$t("chat.computerSide");
        } else {
          info.deviceName  = this.$t("chat.phoneSide");
        }
      }
      if (info.mediaType) {
        if (info.mediaType === "1") {
          info.mediaType = this.$t("chat.audio");
          info.recvMediaName = this.$t("chat.answer");
          info.sendMediaName = this.$t("chat.videoAudio");
        } else if (info.mediaType === "2") {
          info.mediaType = this.$t("chat.video");
          info.recvMediaName = this.$t("chat.answer");
          info.sendMediaName = this.$t("chat.videoAudio");
        } else if (info.mediaType === "7") {
          info.mediaType = this.$t("chat.directTransfer");
          info.recvMediaName = this.$t("chat.receive");
          info.sendMediaName = this.$t("chat.directTransfer");
        } else if (info.mediaType === "9") {
          info.mediaType = this.$t("chat.remoteAssistance");
          info.recvMediaName = this.$t("chat.receive");
          info.sendMediaName = this.$t("chat.remoteAssistance");
        }
      }
      return info;
    },
    /**
     * 当音视频提示信息时且为多点音视频版本时解析userInfo字段
     * 如:"groupId=123345566,roomId=3495858_34534545,operUserName=王某某"
     */
    parseMulUserInfo(userInfo) {
      let info = {};
      userInfo.split(",").forEach(element => {
        let tempArry = element.split("=");
        console.log(tempArry[0]);
        info[tempArry[0]] = tempArry[1];
      });
      if (info.deviceType) {
        if (info.deviceType === "1") {
          info.deviceName  = this.$t("chat.computerSide");
        } else {
          info.deviceName  = this.$t("chat.phoneSide");
        }
      }
      if (info.callType) {
        if (info.deviceType === "2") {
          info.callName= this.$t("chat.invite");
        } else {
          info.callName= this.$t("chat.request");
        }
      }
      return info;
    },
    /**
     * 阅后回执弱提示
     * @param {Object} messageObject - 弱提示消息内容
     * @param {Boolean} weakInfo - 读和发起阅后回执用户姓名
     * @return {String} 会话显示弱提示内容
     */
    readReceipt({ messageObject }, isFlash, isEraser) {
      // 获取配置中的阅后回执发起时间
      let replyMsgTime = messageObject.tipTime || new Date();
      // 是否自己发的阅后回执
      let isMine = messageObject.fromId === this.user_account.userId;
      // 谁发的阅后回执、谁读的阅后回执
      let [receiptSender, receiptReader] = [
        `自动回复${messageObject.usersInfo || ""} ${getDateDiff(
          replyMsgTime
        )}的阅后回执消息`,
        `${messageObject.operUser}已看过我的消息`
      ];
      let [receiptFlashSender, receiptFlashReader] = [
        `我响应了${messageObject.usersInfo}的抖一抖`,
        `${messageObject.operUser}响应了我的抖一抖`
      ];
      let [receiptEraserSender, receiptEraserReader] = [
        `您${messageObject.operType == 1 ? "接受" : "拒绝"}了${
          messageObject.usersInfo
        }的删除请求`,
        `${messageObject.operUser}${
          messageObject.operType == 1 ? "同意" : "拒绝"
        }了您的删除请求`
      ];
      let [senderInfo, readerInfo] = [
        (isFlash && receiptFlashReader) ||
          (isEraser && receiptEraserReader) ||
          receiptReader,
        (isFlash && receiptFlashSender) ||
          (isEraser && receiptEraserSender) ||
          receiptSender
      ];
      return (isMine && readerInfo) || senderInfo;
    }
  }
};
</script>
<style lang="scss" scoped>
// .type-weak {
//   display: flex;
//   width: 100%;
//   justify-content: center;
//   align-items: center;
//   margin-bottom: 6px;
//   .weak-body {
//     .icon {
//       display: flex;
//       align-items: center;
//       margin-right: 10px;
//     }
//     display: flex;
//     align-items: center;
//     background: #dcdcdc;
//     border-radius: 8px;
//     padding: 1px 8px;
//     font-size: $--font-size-small;
//   }
// }
// @media screen and (max-width: 769px) {
//   .type-weak {
//     padding: 0 !important;
//   }
// }
</style>