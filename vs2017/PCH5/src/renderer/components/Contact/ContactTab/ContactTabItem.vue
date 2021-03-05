<template>
  <d-skeleton>
    <div v-if="!isLoading" class="contacts-tab-item contact-item" ref="contacts" @scroll.passive.stop="loadMoreData">
    <v-card-list>
      <!-- 公众号列表 -->
      <v-card class="theme-list-items" :isSecondBreakpoint="true"  :title="$t('contacts.device')" @click="$router.push('/MyDevice')" @dbClick="startChat(user_account, 1)" debounced>
        <v-avatar :title="$t('contacts.device')" size='is-small' :src='myDevice' :offline="false" shape="round"  slot="leftAvatar"></v-avatar>
      </v-card>
      <p class="sup-title theme-left-splitBar">{{ $t('contacts.application') }}</p>
      <v-card class="theme-list-items" :isSecondBreakpoint="true" :title="$t('contacts.application')" @click="active=-1,$router.push('/OfficialAccounts')">
        <v-avatar :title="$t('contacts.application')" size='is-small' :src='appIcon' :offline="false" shape="round"  slot="leftAvatar"></v-avatar>
      </v-card>
      <p class="sup-title theme-left-splitBar" v-if="hasChilds(contact_entAppList)">{{ $t('contacts.enterprise') }}</p>
      <v-card class="theme-list-items" v-for="(item, index) in contact_entAppList" :key="index" :isSecondBreakpoint="true" :title="item.appName" @click="$router.push({path:'/EntAppInfo',query:{item}})" @dbClick="startChat(item, 3)" debounced>
        <v-avatar size='is-small' :src='item.appIcon' :sex="3" :offline="false" shape="round"  slot="leftAvatar"></v-avatar>
      </v-card>
    </v-card-list>
    <v-card-list @menuClick="contactMenuClick" :menuList="contactMenu">
      <!-- v标/好友列表 -->
      <div class="hidden-vip-item">
        <p class="sup-title theme-left-splitBar" v-if="vipContactList.length!=0">{{ $t('contacts.vip') }}</p>
        <v-card class="theme-list-items" ref="vipContact" :isSecondBreakpoint="true" v-for="item in vipContactList" :key="'v'+item.id" :title="item.remark||item.name" :index="'v'+item.id" @contextmenu="setContactMenu(item)" @click="openDetail(0,item,'v'+item.id)" @dbClick="startChat(item, 1)" debounced>
          <v-avatar :title='item.remark||item.name' size='is-small' :src='item.thumbAvatar' :sex="item.gender" :offline="false" shape="round"  slot="leftAvatar"></v-avatar>
          <lazy-scroll v-if="root" :viewport="root" slot="left">
            <online :itemId="item.izad"></online>
          </lazy-scroll>
        </v-card>
      </div>
      <p class="sup-title theme-left-splitBar" v-if="contactList.length!=0">{{ $t('contacts.buddy') }}</p>
      <v-card class="theme-list-items" ref="contact" :isSecondBreakpoint="true" v-for="item in contactList.slice(0, initLength)" :key="item.id" :title="item.remark||item.name" :index="item.id" @contextmenu="setContactMenu(item)" @click="openDetail(0,item,item.id)" @dbClick="startChat(item, 1)" debounced>
        <v-avatar :title='item.remark||item.name' size='is-small' :src='item.thumbAvatar' :sex="item.gender" :offline="false" shape="round"  slot="leftAvatar"></v-avatar>
        <lazy-scroll v-if="root" :viewport="root" slot="left">
          <online :itemId="item.id"></online>
        </lazy-scroll>
      </v-card>
    </v-card-list>
    </div>
    <contact-skeleton slot="skeleton" type="contact"></contact-skeleton>
  </d-skeleton>
</template>
<script>
import ContactMixin from '../ContactMixin.js'
import { mapGetters } from 'vuex'
import { converseFullPinYin } from '../../../../comm/pinyin.js';
import Online from '../../Common/Online';
import LazyScroll from '../../Common/LazyScroll';
import ContactSkeleton from './ContactSkeleton';

export default {
  data() {
    return {
      updateContactList: [],
      contactMenu: [this.$t('contacts.remark'), this.$t('contacts.delete'), this.$t('contacts.black')],
      appIcon: require('vrv-static/resources/images/contact/app_icon.png'),
      myDevice: require('vrv-static/resources/images/common/mydevice.png'),
      initLength: 20,
      isLoading: true,
      root: null,
      isEnAppFinished: false
    }
  },
  mixins: [ContactMixin],
  components: {
    Online: resolve => require(['../../Common/Online'], resolve),
    LazyScroll,
    ContactSkeleton
  },
  computed: {
    ...mapGetters(['contact_contactList', 'contact_entAppList','chat_chatContent']),
    // 好友列表
    contactList() {
      console.log('好友列表computed:',this.contact_contactList);
      let list = _.orderBy(
        _.filter(this.contact_contactList, e => e.id && e.isApp == 2 && e.isHidden == 2),
        val => {
          return converseFullPinYin(val.pinyin.trim());
        },
        ['asc']
      )
      this.updateContactList = [...list];
      return list
    },
    vipContactList() {
      if (this.updateContactList.length===0) return []
      return _.filter(this.updateContactList, e => e.isStar === 1)
    },
    // 判断是否开启在线状态
    hasOpenOnline() {
      return this.$config && this.$config.account && this.$config.account.openOnlineStatus;
    }
  },
  mounted() {
    setTimeout(() => {
      this.getEntAppList();
      this.isLoading = false;
      // 暂时不用懒加载，根据渲染数量渲染
      if (this.$config.account.openOnlineStatus) {
        this.root = this.$parent.$el
      }
    }, 0);
  },
  methods: {
    hasChilds(obj) {
      var val=[],key;
     for (key in obj) {
        if (Object.prototype.hasOwnProperty.call(obj,key)) {
            val.push(obj[key]);
        }
      }
      console.log('======>objs:',val);
      console.log('obj size:',val.length);
      return val.length>0;
    },
    /**
     * 滚动加载更多
     */
    loadMoreData() {
      console.log('loadMoreData============>')
      this.$nextTick(() => {
        if (this.isScrollToBottom(this.$refs.contacts))
          if (this.initLength < this.updateContactList.length) {
            //是否有更多数据
            if (this.updateContactList.length - this.initLength < 30) {
              this.initLength = this.updateContactList.length;
            } else {
              this.initLength += 20;
            }
          }
      })
    },
    setContactMenu({ isStar }) {
      this.contactMenu = [
        // this.$t('contacts.remark'), 
        this.$t('contacts.delete'),
        //  this.$t('contacts.black')
        ]
      if (isStar !== 1) this.contactMenu.push(this.$t('contacts.addVip'))
      else this.contactMenu.push(this.$t('contacts.removeVip'))
    },
    /**
     * 联系人右键菜单点击
     * @param {String} menuName: 右键菜单内容
     * @param {Number} menuIndex: 右键菜单对应的index
     * @param {String} itemId: listItem对应的id
     */
    contactMenuClick(menuName, menuIndex, itemId) {
      if (itemId.includes('v')) {
        itemId = itemId.replace('v', '')
      }
      let contactActions = {
        // 0: () => this.changeRemark(itemId),
        0: () => this.removeContact(itemId, true),
        // 2: () => this.addBlackList(itemId),
        1: () => this.setVipContact(itemId)
      }
      contactActions[menuIndex].call(this)
    },
    /**
     * 加入黑名单
     * @param {String} -listItem对应的用户id
     */
    addBlackList(id) {
      this.$dialog.confirm({
        message: this.$t('contacts.toBlock', {value: this.contact_contactList[id].remark || this.contact_contactList[id].name}),
        confirmText: this.$t('common.confirm'),
        cancelText: this.$t('common.cancel'),
        onConfirm: () => {
          this.$Service.contact.addBlackList([id], resp => {
            console.log('移入黑名单结果', resp)
            let toastMsg = { message: this.$t('groups.addToBlockedList'), type: 'is-success' }
            if (resp.code !== 0) {
              toastMsg = {
                message: `${this.$t('groups.blockedFailed')}:` + this.$t(`ErrorCode.${resp.code}`),
                type: 'is-danger'
              }
            }
            this.$toast.open(toastMsg)
          })
        }
      })
    },
    /**
     * 设置V标好友
     * @param {String} id: listItem对应的用户id
     */
    setVipContact(id) {
      let isStar = this.contact_contactList[id].isStar === 1
      let info = { id: id, isStar: isStar ? 2 : 1 }
      this.$Service.contact.updateContactInfo(info, resp => {
        console.log('设置V标好友回调：' + JSON.stringify(resp))
        if (resp.code !== 0) {
          let errorInfo = this.$t(`ErrorCode.${resp.code}`)
          this.$toast.open({
            message: this.$t('contacts.addVip') + ':' + errorInfo,
            type: 'is-danger'
          })
        }
      })
    },
    /**
     * 删除好友
     * @param {String} id: listItem对应的用户id
     */
    removeContact(id) {
      this.$dialog.confirm({
        message: this.$t('contacts.toDelete', {value: this.contact_contactList[id].remark || this.contact_contactList[id].name}),
        confirmText: this.$t('common.delete'),
        cancelText: this.$t('common.cancel'),
        onConfirm: () => {
          this.$Service.contact.removeContact({ userId: id }, resp => {
            let toastMsg = { message: this.$t('groups.removeSucc'), type: 'is-success' }
            if (resp.code !== 0) {
              toastMsg = {
                message: `${this.$t('groups.removeFail')}:`+ this.$t(`ErrorCode.${resp.code}`),
                type: 'is-danger'
              }
            }
            this.$toast.open(toastMsg)
          })
        }
      })
    },
    /**
     * 修改联系人备注
     * @param {String} id: listItem对应的用户id
     */
    changeRemark(id) {
      let curItem = this.contact_contactList[id]
      this.$dialog.prompt({
        confirmText: this.$t('common.confirm'),
        cancelText: this.$t('common.cancel'),
        inputAttrs: {
          placeholder: curItem.remark || curItem.name,
          maxlength: 20,
          value: curItem.remark || curItem.name
        },
        // required: true,
        onConfirm: value => {
          let info = { id: id, remark: value.trim() }
          this.$Service.contact.updateContactInfo(info, resp => {
            console.log('更新备注返回：' + JSON.stringify(resp))
            if (resp.code !== 0) {
              let errorInfo = this.$t(`ErrorCode.${resp.code}`)
              this.$toast.open({
                message: this.$t('contacts.remark') +':' + errorInfo,
                type: 'is-danger'
              })
            }
          })
        }
      })
    },
    /**
     * 企业号
     */
    getEntAppList() {
      let getEntAppInfoParam = { pageNum: 1, pageSize: 1000, type: 1 }
      this.$Service.user.getEntAppInfo(getEntAppInfoParam, resp => {
        console.log('获取企业号:', resp)
        this.$store.dispatch('SET_ENTAPP_LISTS', resp)
      })
    }
  }
}
</script>
<style lang="scss">
.contacts-tab-item {
  flex: 1;
  width: 100%;
  height: 100%;
  .sup-title {
    font-size: 14px;
    padding: 5px;
    font-weight: 700;
  }
  &:hover {
    overflow-y: auto;
  }
  .default-content {
    display: flex;
    width: 219px;
    .media {
      flex: 1;
    }
  }
}
</style>

