/**
 * @file      Manages the contact's infomation for the main page.
 * @author    linpeiyuan <linpeiyuan@vrvmail.com.cn>
 * @date      2019.9.19
 * @copyright Beijing VRV Software Co.,Ltd
 * 
 * @mixin
 */ 
import { mapGetters } from 'vuex';
// import Mixin from '../../Contact/ContactMixin.js';
const mixin = {
  data () {
    /**
     * @param {string} - lastRouteId 最后一次会话路由ID，为了切换路由后，下次切换回来打开之前的会话
     */
    return {
      lastRouteId: ''  
    };
  },
  computed: {
    ...mapGetters([
      'contact_contactList',
      'chat_chatContent',
      'chat_chatList'
    ])
  },
  methods: {
    /**
     * @breif 联系人相关通知回调注册
     */
    regContactNotify() {
      this.regContactHeadImgUpdateCb();
      this.regBuddyListCb();
      this.regOperateBuddyCb();
      // if (this.$config.account.openOnlineStatus) {
      //   this.regContactOnlineChanged();
      // }
    },

    /**
     * @breif 注册联系人头像更新
     * @todo 移至导航栏联系人按钮模块
     */
    regContactHeadImgUpdateCb() {
      this.$Service.contact.regContactHeadImgUpdateCb(null, resp => {
        this.$store.dispatch("UPDATE_CONTACTS_AVATARS", resp);
        //  判断是否显示了搜索列表，如果显示则需要更新搜索列表中的头像
        if (document.getElementById("netSearchList")) {
          this.$signalMonitor.$emit("update-network-searchlist", resp);
        }

        //  更新会话页对应会话的头像,只更新当前打开的会话
        if (!this.chat_chatContent[resp.targetId]) {
          return;
        }
        this._updateChatConatctAvatar({id: resp.targetId, avatar: resp.avatar, userId: resp.targetId});
      });
    },

    /**
     * @breif 联系人列表变化推送
     * @todo 移至导航栏联系人按钮模块
     */
    regBuddyListCb() {
      this.$Service.contact.regBuddyListCb(null, resp => {
        console.log("regBuddyListCb",resp.flag)
        if (!resp.contacts || resp.contacts.length === 0) {
          this.$Service.log('contact.regBuddyListCb failed');
          return;
        }
        this.$store.dispatch("SET_CONTACTLISTS", resp);
      });
    },

    /**
     * @breif 联系人信息变化推送
     * @todo 移至导航栏联系人按钮模块
     */
    regOperateBuddyCb() {
      console.log('this.$Service.contact',this.$Service.contact)
      this.$Service.contact.regOperateBuddyCb(null, this._regOperateBuddyCbHandler);
    },
    _regOperateBuddyCbHandler(resp) {
      console.log('_regOperateBuddyCbHandler',resp)
      if (resp.contact.thumbAvatar) {
        let fileOperateParam = {
          filepath: resp.contact.thumbAvatar,
          type: 0
        };
        if (!this.$Service.file.fileOperate(fileOperateParam)) {
          this.$Service.log(
            `contact avatar has change but no exsist:::   ${resp.contact.id}`
          );
          resp.contact.thumbAvatar = "";
        }
        //  头像更新操作
        let contact = this.contact_contactList[resp.contact.id];
        if (contact && resp.contact.thumbAvatar !== contact.thumbAvatar) {
          //  如果是头像变更则需要更新头像
          if (this.chat_chatContent[resp.contact.id]) {
            this._updateChatConatctAvatar({id: resp.contact.id, avatar: resp.contact.thumbAvatar, userId: resp.contact.id});
          }
        }
      }

      //  更新详细信息
      this._updateContactInfo(resp);
    },

    /**
     * @breif 联系人头像变化，更改对应的个人会话中的头像
     * @param {object} - {id: '会话ID', avatar: '头像', userId: '联系人ID'}
     * 
     * @todo 移至导航栏联系人按钮模块/是否能够移至会话模块监听，深度监听对应的联系人信息
     */
    _updateChatConatctAvatar({id,avatar,userId}) {
      this.$store.commit("UPDATE_MEMBER_AVATAR", {id, avatar, userId});
    },

    /**
     * @breif 联系人信息的变更，可能会变更会话列表及会话项的内容，如果flag为3的话需要删除会话列表的内容
     * @param {object} - info 更新的联系人信息
     */
    _updateContactInfo({flag, contact}) {
      console.log('_updateContactInfo,',flag,contact)
      this.$store.commit("CHANGE_CONTACT_INFO", {flag: flag, contact: contact});
      if (flag !== 3) {
        return;
      }

      //  如果需要删除联系人
      if (!this.chat_chatList[contact.id]) {
        return;
      }

      //  移除会话列表中的内容
      this.$store.commit("DEL_CHATLIST", contact.id); // TODO: 最好是监听chatlist变化来调用removechat
      let param = { targetId: contact.id };
      this.$Service.chat.removeChat(param, resp => {
        if (resp.code !== 0) {
          return;
        }
        this.lastRouteId = contact.id === this.lastRouteId ? '' : this.lastRouteId;
      });

      //  判断是否打开了这个联系人的会话，如果打开了 则需要删除对应的缓存
      if (!this.chat_chatContent[contact.id]) {
        return;
      }
      console.log('DEL_CHATCONTENT_BYID',contact.id)
      this.$store.commit("DEL_CHATCONTENT_BYID", contact.id);
      this.$store.commit("DEL_CHAT_OBJECT", contact.id);

      //  判断当前路由页是否是删除联系人的相关页
      if (!this.$route.query || this.$route.query.id !== contact.id) {
        return;
      }
      const routepath = {
        '/ChatRightArea': '/Chat',
        '/ContactInfo': '/Contact'
      };
      if (!routepath.hasOwnProperty(this.$route.path)) {
        return;
      }
      this.$router.push(routepath[this.$route.path]);
    },

    /**
     * @breif 联系人在线状态更新推送
     * @todo 废弃
     */
    // regContactOnlineChanged() {
    //   //  判断是否开启了显示联系人在线状态
    //   if (!this.$config.account.openOnlineStatus) {
    //     return;
    //   }
    //   this.$Service.contact.regContactOnlineChanged(null, resp => {
    //     this.$store.dispatch('SET_CONTACTS_STATES', resp);
    //   });
    // },
    
    /**
     * @breif 获取联系人列表
     */
    getContactList() {
      this.$Service.contact.getContactList(null).then(resp => {
      // this.$Service.contact.getContactList(null, resp => {
        if (!resp.contacts || resp.contacts.length === 0) {
          this.$Service.log('contact.getContactList failed');
          return;
        }
        this.$Service.log(`主动拉取联系人列表: length:${resp.contacts.length}\n lastConatct:${JSON.stringify(resp.contacts[resp.contacts.length - 1])}`);
        this.$store.dispatch("SET_CONTACTLISTS", resp);
      });
    }
  },
}

export default mixin;