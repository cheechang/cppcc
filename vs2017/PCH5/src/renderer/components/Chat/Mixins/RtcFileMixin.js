import { mapGetters } from 'vuex';
import { msgStructure } from '../Msg'
import { encryptionPassword} from '../../../../comm/util';
const RtcFileMixin = {
  data() {
    return {
      timer: {}
    }
  },
  computed: {
    ...mapGetters(['chat_P2P_file_state'])
  },
  methods: {
    /**
     * 新建RtcFile 窗口
     * @param {string} id 会话ID
     * @param {string} savePath 文件保存路径
     * @param {string} size 文件尺寸
     * @param {string} isAccept 是否接收
     */
    // newRtcFileWin(id, savePath, size, isAccept) {
    //   let winUrl = '#/RtcFile?id=' + id
    //   winUrl = `${winUrl}&savePath=${savePath}&size=${size}&isAccept=${isAccept}`
    //   let result = this.$ipc.send('new-window', {
    //     winUrl: winUrl,
    //     winType: 'RtcFile',
    //     winTitle: '文件直传',
    //     shapeType: 'normal',
    //     isWinShow: false
    //   })
    // },
    
    /** 
     * 设置RTCFile 的状态
     * 相当于渲染进程传输直传文件的一把锁
     */
    setRtcFileState(id, localId) {
      if (!this.chat_P2P_file_state.value) {
        this.$store.commit('SET_P2P_FILE_STATE', {id: id, value: true, localId: localId})
      } 
    },

    removeRtcFileSate() {
      if (this.chat_P2P_file_state.value) {
        this.$Service.log(`chat_P2P_file_state::endOrBusy  ${this.chat_P2P_file_state.value}`);
        this.$store.commit('DEL_P2P_FILE_STATE')
      }
    },

    // regFileReceiverNotify() {
    //   this.$Service.rtcplugin.regFileReceiverNotify(resp => {
    //     console.log('regFileReceiverNotify', resp)
    //     this.$ipc.send('newMessage')
    //     this.audioNode.play();
    //     let result = this.$judgePlginSubWinStatus('RTCFile')
    //     let localId = new Date().getTime().toString();
    //     this.setRtcFileState(resp.userId, localId)

    //     this.inserChatList(resp.userId)
    //     if (!result.busy) {
    //       let msgBase = {
    //         targetId: resp.userId,
    //         fromId: resp.userId,
    //         fileName: resp.filename,
    //         isResume: true,
    //         filePath: '',
    //         encryptKey: '',
    //         size: resp.filesize,
    //         url: '',
    //         msgType: 6,
    //         preDefined: JSON.stringify({ RtcFile: true }),
    //         localId: localId,
    //         msgId: encryptionPassword().toString()
    //       }
    //       let msg = msgStructure(msgBase)

    //       this.chat_chatContent[resp.userId]
    //         ? this.$store.commit('RTC_FILE', msg)
    //         : this.checkOutRtcTimeout(msg).then(() => {
    //             let savePath = this.user_filePath + resp.filename
    //             this.newRtcFileWin(resp.userId, savePath, resp.filesize, 'reject')
    //             this.$store.commit('UPDATE_CHATLIST_RTCFILE', {id: resp.userId, type: 0})
    //             this.removeRtcFileSate()
    //             this.$ipc.send('RtcFileClose')
    //           })
    //     }
    //   })
    // },

    checkOutRtcTimeout(msg) {
      let conunt = 45
      return new Promise(reslove => {
        this.timer = setInterval(() => {
          console.log('conunt---', conunt)
          if (this.chat_chatContent[msg.messageObject.targetId]) {
            this.$store.commit('RTC_FILE', msg)
            clearInterval(this.timer)
          }
          conunt--
          if (conunt < 1) {
            reslove()
            clearInterval(this.timer)
          }
        }, 1000)
      })
    },
    
    /** 插入最近会话列表 */
    inserChatList(id) {
      let serviceTime = this.$Service.user.getServerTimeSync({}) 
      if (this.chat_chatList[id]) {
        this.$store.commit('UPDATE_CHATLIST_RTCFILE', { id: id, type: 1 , time: serviceTime})
      } else {
        let contactInfo = this.contact_contactList[id]
        this.$store.commit('PUSH_CHATLIST', {
          id: id,
          chatType: 1,
          isRtcFile: 1,
          msgType: 2,
          lastMsg: '',
          delSign: '',
          isTop: 0,
          gender: contactInfo.gender || 1,
          msgTime: serviceTime,
          startTime: serviceTime
        })
      }
    },
    
    clearRtcTimer() {
      if (this.timer) {
        console.log('clearInterval ::timer')
        clearInterval(this.timer)
        }
      }
    }
};
export default RtcFileMixin;
