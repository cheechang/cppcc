import { mapGetters } from 'vuex';
import config from '../../../comm/config'
/**
 * 通讯录模块 公共变量、方法、vuex数据
 */
const mixin = {
  data() {
    return {
      active: '',
      baseParams: {
        subType: 1,
        // msgTime: new Date().getTime(),
        msgType: 2,
        lastMsg: '',
        delSign: '',
        whereFrom: '',
        isTop: 0,
        // startTime: new Date().getTime()
      },
      onlineFlag: [1, 3, 4, 5, 6], // is online ?
      onlineDevice: {
        1: require('vrv-static/resources/images/common/computer.png'),
        2: require('vrv-static/resources/images/common/phone.png')
      },
      // 1：PC；2：手机；3：pad；4：网页
      onlineTooltip: {
        1: this.$t('contacts.pcOnline'),
        2: this.$t('contacts.phoneOnline'),
        3: this.$t('contacts.padOnline'),
        4: this.$t('contacts.webOnline'),
      }
    }
  },
  directives: {
    focus: {
      inserted(el, binding) {
        if (binding.value) el.focus();
        else el.blur();
      },
      componentUpdated(el, binding) {
        if (binding.modifiers.lazy) {
          if (Boolean(binding.value) === Boolean(binding.oldValue)) {
            return;
          }
        }
        if (binding.value) el.focus();
        else el.blur();
      }
    }
  },
  computed: {
    ...mapGetters(['user_account', 'user_netstat','user_serverstat', 'contact_contactList'])
  },
  methods: {
    /**
     * 判断滚动条滚动到底部
     * @param {*} el - 绑定的dom元素
     * @returns - 是/否
     */
    isScrollToBottom(el) {
      let [scrollTop, offsetHeight, scrollHeight] = [el.scrollTop, el.offsetHeight, el.scrollHeight];
      return !(scrollTop + offsetHeight < scrollHeight)
    },
    /**
     * 打开联系人/群详情界面
     * @param {Number} to - 0:联系人详情页 1:群详情页
     * @param {Object} item - listItem对应的item
     * @param {Number} index - 0:联系人 1:群
     */
    openDetail(to, item, index) {
      this.id = item.id || item.groupId || item.userID;
      // this.active = index;
      this.$signalMonitor.$emit('change-active', index)
      this.$router.push({
        path: to === 0 ? '/ContactInfo' : '/GroupInfo',
        query: { id: this.id, item: item }
      });
    },
    /**
     * 跳转会话界面
     * @param {Object} item - 会话对象
     * @param {Number} type - 会话类型
     */
    startChat(item, type) {
      let itemParams = {
        id: item.id || item.groupId || item.appID || item.userID,
        name: item.remark || item.name || item.groupName || item.appName || item.enName,
        chatType: type,
        thumbAvatar: item.thumbAvatar || item.avatar || item.appIcon || item.userHead,
        gender: item.gender
      };
      // 当ID等于用户ID时是我的设备会话消息
      if (item.id === this.user_account.id) {
        itemParams.thumbAvatar = config.defalutAvatar[8];
      }
      console.log('this.$Service.user.getServerTimeSync({})', this.$Service.user.getServerTimeSync({}))
      let time = this.$Service.user.getServerTimeSync({}) || new Date().getTime()
      itemParams.msgTime = time;
      itemParams.startTime = time;
      itemParams = Object.assign(itemParams, this.baseParams)
      console.log('itemParams::', itemParams)
      this.$store.commit('PUSH_CHATLIST', itemParams);
      this.$signalMonitor.$emit('toChatPage'); // 发送信号：导航栏选中会话图标
      this.$router.push({
        path: '/ChatRightArea',
        query: { id: itemParams.id, chatType: itemParams.chatType }
      });
    },
    /**
     * 删除好友
     */
    removeContact(id, isJump=false) {
      this.$dialog.confirm({
        message: this.$t('contacts.toDelete', {value: this.contact_contactList[id].remark || this.contact_contactList[id].name}),
        confirmText: this.$t('common.delete'),
        cancelText: this.$t('common.cancel'),
        onConfirm: () => {
          this.$Service.contact.removeContact({userId: id}, resp => {
            let toastMsg = {message:`${this.$t('groups.removeFail')}:`+this.$t(`ErrorCode.${resp.code}`),type:'is-danger'}
            if (resp.code === 0) {
              isJump && this.$router.push('/Contact');
              toastMsg = {message:this.$t('groups.removeSucc'),type:'is-success'};
            }
            this.$toast.open(toastMsg);
          });
        }
      });
    },
    /**
     * 添加好友
     */
    addFriend(id, name) {
      this.$dialog.prompt({
        message: this.$t('search.verfication')+':',
        confirmText: this.$t('common.confirm'),
        cancelText: this.$t('common.cancel'),
        inputAttrs: {
          value: this.$t('search.iAm') + this.user_account.name,maxlength: 60
        },
        required: false,
        onConfirm: value => {
          let addContactParam = {
            userId: id,
            info: value
          };
          this.$Service.contact.addContact(addContactParam, resp => {
            if (resp.code !== 0)
              this.$toast.open({
                message: this.$t(`ErrorCode.${resp.code}`),
                type: 'is-danger'
              });
            else {
              this.$Service.contact.getVerifyType({userId: id}, resp => {
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
    }
  }
};
export default mixin;
