import {
  mapGetters
} from 'vuex';
const CommonMixin = {
  data() {
    return {}
  },
  computed: {
    ...mapGetters(['user_account'])
  },
  methods: {
    addFriend(addContactId) {
      return new Promise(resolve => {
        this.$dialog.prompt({
          message: this.$t('search.verfication') + ':',
          confirmText: this.$t('common.confirm'),
          cancelText: this.$t('common.cancel'),
          inputAttrs: {
            value: this.$t('search.iAm') + this.user_account.name,
            maxlength: 60
          },
          required: false, // 验证信息选填
          onConfirm: value => {
            let addContactParam = {
              userId: addContactId,
              info: value
            };
            this.$Service.contact.addContact(addContactParam, resp => {
              this.$Service.log(`添加好友请求：code:${resp.code}`);
              let toastMsg = {
                message: this.$t('groups.requestSent'),
                type: 'is-success'
              }
              if (resp.code !== 0) {
                this.$toast.open({
                  message: this.$t(`ErrorCode.${resp.code}`),
                  type: 'is-danger'
                })
                resolve()
              } else {
                this.$Service.contact.getVerifyType({userId: addContactId}, resp => {
                  console.log('获取对方好友验证方式', resp)
                  let verifyInfo = {
                    1: this.$t('groups.requestSent'),
                    3: this.$t('contacts.chatNow')
                  }
                  console.log(resp.type,verifyInfo[resp.type])
                  this.$toast.open({message: verifyInfo[resp.type], type: 'is-success'})
                  resolve()
                })
              }
            });
          },
          onCancel() {
            resolve()
          }
        });
      })
    },
    /**
     * 判断滚动条滚动到底部
     * @param {*} el - 绑定的dom元素
     * @returns - 是/否
     */
    isScrollToBottom(el) {
      let [scrollTop, offsetHeight, scrollHeight] = [el.scrollTop, el.offsetHeight, el.scrollHeight];
      return !(scrollTop + offsetHeight < scrollHeight)
    },
  }
};
export default CommonMixin;
