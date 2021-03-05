<template>
  <div>
    <!-- 最近回话列表毛玻璃效果 -->
    <div class="theme-frosted-glass">
      <div class="theme-left-bgc"></div>
    </div>
    <!-- 会话为空后显示为空的图片提示  -->
    <div class="empty-list" v-if="loaded && Object.keys(chat_chatList).length === 0"></div>
    <!-- 断线重连提示 -->
    <Disconnect v-if="showDisconnect" :tip="disConnectTip"></Disconnect>
    <!-- 加载动画   -->
    <Animates v-if="isShowAnimate" loadTop="200"></Animates>
    <!-- 最近会话列表 -->
    <!-- <div class="list-area" ref="chatlists"  @scroll.passive.stop="loadMoreData"> -->
    <vue-scroll ref="vs" :ops="ops" @handle-scroll="handleScroll">
      <d-skeleton>
        <ListItem class="theme-list-items"
            v-for="(item,index) in chat_list"
            :key="item.id"
            :item ="item"
            :chatOnlineList="chatOnlineList"
            :class="{'theme-list-items-active':active===item.id}"
            @click.native ="startChat(item, index)"
            @contextmenu.native.stop ="setMenuPos($event, item)">
        </ListItem>
        <chat-list-skeleton slot="skeleton" @skeleton-destroy="skeletonDestroy"></chat-list-skeleton>
      </d-skeleton>
      <!-- 右键菜单 -->
      <v-menu v-if="isShowMenu"
          class="chat-list-meun"
          :menuList="menuList" 
          :currentPos="currentPos"
          @close="isShowMenu = false, menuList=[]"
          @selectItem="selectItem">
      </v-menu>
    </vue-scroll>
  </div>
</template>
<script>
import _ from 'lodash'
import { mapGetters } from 'vuex'
import { getDateDiff } from '../../../comm/time'
import { scrollIntoView, isInVisibleArea } from './At/at.js'
import ListItem from './ListItem'
import Animates from '../Common/Animate.vue'
import Disconnect from '../Common/LogBack'
import MsgMxin from './msgMixin'
import CommonMixin from '../Common/commonMixin.js'
import ChatListSkeleton from './ChatListSkeleton';

export default {
  mounted() {
    /** 监听键盘切换上下键 切换会话 */
    this.$ipc.on('changeChatList', (e, args) => {
      if (
        this.$route.name === 'ChatRightArea' ||
        this.$route.name === 'Chat' ||
        this.$route.name === 'ChatSystem'
      )
        this.selectByKeyboard(args)
    })

    // * 监听是否需要滚动 如排在靠后的列表是否需要滚动置相应位置
    this.$signalMonitor.$on('isScroll', (e) => {
      setTimeout(() => {
        this.index = this.getItemIndex()
        const curEl = this.$el.getElementsByClassName('theme-list-items')[this.index]
        if(!isInVisibleArea(curEl)) {
          this.$Service.log('in not in visibleArea')
          let scrollParent = document.getElementsByClassName('chat-list')[0]
          scrollIntoView(curEl, scrollParent, true)
        }
      }, 20)
    })

    // * 防止首页 公众号跳转
    this.$signalMonitor.$once('activeListItem', ()=> {
      if (!this.active){
        console.log('activeListItem:::')
        this.active = this.$route.query.id;
        this.setMessageRead(this.active) 
      }
    })
  },
  mixins: [MsgMxin,CommonMixin],
  methods: {
    // * 滚动加载更多
    handleScroll(vertical, horizontal, nativeEvent) {
      console.log('handleScroll:::::')
      if (this.initLength >= this.updateChatList.length) return
      if (vertical.process === 1) {
        let num = 20
        if (this.initLength + num > this.updateChatList.length) {
          num = this.updateChatList.length - this.initLength
        }
        this.initLength += num
      }
    },


    /**
     * startChat
     * @param {object} item  每项 Items 数据
     * @param {string} index 每项 items 的下标
     * listItem 处于激活状态
     * 路由跳转 切换会话
     */
    startChat(item, index) {
      if(this.active === item.id) return
      this.active = item.id // 让listItem 处于激活状态
      this.index = index

      if (item.state) {
        this.$store.commit('CHANGE_CHAT_LIST_STATE', { id: item.id, type: 0 })
      }
      let isSystemMsg = item.id === '10000'
       console.log('sysMsg',item)
      /* 跳转路由 */
      !isSystemMsg
        ? this.$router.replace({ path: '/ChatRightArea', query: {id: item.id, name: item.name, chatType: item.chatType, unreadCount: item.unreadCount }})
        : this.$router.replace({ path: '/ChatSystem', query: { id: item.id, name: item.name }})

      if ((isSystemMsg || this.chat_chatContent[item.id]) && item.unreadCount) {
        this.$Service.log(`setMessageRead:::::::    ${item.id}`)
        console.log('sysMsg',item)
       // this.setMessageRead(item.id) 
       let param ={
         type:item.chatType,
         msgs:[item.lastMsgId]
       }
       this.$Service.sysMsg._sysmsg.setMessagRead(param,resp =>{
         this.$Service.log(`setMessageRead:::::::    ${JSON.stringify(resp)}`)
       })
      }
    },

    /**
     * setMenuPos 设置右键menu 位置
     * @param {Event} e 事件
     * @param {Object} item 每项列表对象
     */
    setMenuPos(e, item) {
      if (item.id === '10000') return
      this.isShowMenu = true
      this.currentPos.left = e.clientX + 'px'
      // this.currentPos.top = e.clientY + 'px'

      this.rightActive = item
      this.menuList[0] = item.isTop ? this.$t('common.unpin') : this.$t('common.pin')
      if (item.chatType !== 3) this.menuList[1] = item.disturbStatus !== 3 ? this.$t('chat.oPenDisturb') : this.$t('chat.closeDisturb')
      // this.menuList.push('清空内容')
       this.menuList[2] = this.$t('chat.clearMessage')

      let addHeight = (this.menuList.length) * 33 + 8
      addHeight =
        addHeight + e.clientY < document.body.clientHeight
          ? 0
          : addHeight + 8

      this.currentPos.top = e.clientY - addHeight + 'px'
    },

    // * 选择右键菜单的某项 
    selectItem(index) {
      this.isShowMenu = false
      console.log('index', index)
      console.log('menuList', this.menuList)
      console.log('index', this.menuList[index])
      switch (this.menuList[index]) {
        case this.$t('common.pin'): {
          this.setChatTop(this.rightActive, true)
          break
        }
        case this.$t('common.unpin'): {
          this.setChatTop(this.rightActive, false)
          break
        }
        case this.$t('chat.oPenDisturb'): {
          this.setUserNoDisturbMode('3')
          break
        }
        case this.$t('chat.closeDisturb'): {
          this.setUserNoDisturbMode('1')
          break
        }
        case this.$t('chat.clearMessage'):
        this.deleteMessageById(this.rightActive.id)  
        break
        default: 
        break
      }
    },

    /**
     * setChatTop 设置会话置顶
     * @param {string} targetId 置顶的目标ID
     * @param {boolean} isTop 是否置顶 true 置顶 false 取消置顶
     */
    setChatTop(item, isTop) {
      let chatTopParam = {
        targetId: item.id, // 置顶的目标ID
        isTop: isTop // 是否置顶
      }
      this.$Service.chat.chatTop(chatTopParam, resp => {
        if (item.delSign === '') item.isTop = isTop
      })
    },

    /**
     * setUserNoDisturbMode 设置用户免打扰模式
     * @param {number} chatType 会话类型 1 个人 2 群组
     * @param {string} id 设置目标Id 个人
     * @param {string} groupId 设置目标Id 群组
     * @param {number} disturbSet 设置模式（个人） 1 关闭免打扰 3 开始免打扰
     * @param {String} mode 设置模式（群组） 1 关闭免打扰 3 开始免打扰
     */
    setUserNoDisturbMode(value) {
      if (this.rightActive.chatType === 1) {
        let updateContactInfoParam = {
          id: this.rightActive.id,
          disturbSet: parseInt(value)
        }

        let setUserNoDisturbModeCb = resp => {
          if (resp.code === 0) {
            this.$store.commit('UPDATE_CHATLIST', {id: this.rightActive.id, disturbSet: parseInt(value), disturbStatus: parseInt(value)})
          }
        }

        this.$Service.contact.updateContactInfo( updateContactInfoParam, setUserNoDisturbModeCb)

      } else {
        let setGroupMsgRemindTypeParam = {
          groupId: this.rightActive.id,
          mode: parseInt(value)
        }
        console.log('setGroupMsgRemindTypeParam:::', setGroupMsgRemindTypeParam)

        let setGroupMsgRemindTypeCb = resp => {
          console.log('resp:::', resp)
          if (resp.code === 0) {
            this.$store.commit('UPDATE_CHATLIST', { id: this.rightActive.id, disturbSet: parseInt(value), disturbStatus: parseInt(value)})
          }
        }

        this.$Service.group.setGroupMsgRemindType(setGroupMsgRemindTypeParam, setGroupMsgRemindTypeCb)
      }
    },

    // *  滚动到列表所在位置
    scrollToCur(direction) {
      console.log('this.index', this.index)
      const curEl = this.$el.getElementsByClassName('theme-list-items')[this.index]
      console.log('curEl::', curEl)
      const scrollParent = document.getElementsByClassName('chat-list')[0]
      console.log('scrollParent', scrollParent)
      scrollIntoView(curEl, scrollParent, direction)
    },

    // * 通过上下键盘切换会话
    selectByKeyboard(args) {
      if (!this.$route.query.id) this.index = -1
      let offset = args === 'ArrowDown' ? 1 : -1
      if (this.$route.query.id && this.index !== -1 && this.chat_list[this.index].id !== this.$route.query.id)
      this.index = this.getItemIndex()
      this.index = Math.max(0, Math.min(this.index + offset, this.chat_list.length - 1))
      this.scrollToCur(false)
      this.startChat(this.chat_list[this.index], this.index)
    },

    // *  获取 列表中某一项的index
    getItemIndex() {
      let index
      this.chat_list.filter((e, i) => {if (e.id === this.$route.query.id) index = i})
      return index
    },
    // 骨架屏销毁事件
    skeletonDestroy() {
      setTimeout(() => {
        // 异步处理防止事件阻塞
        this.loaded = true;
      }, 0);
    }
  },
  beforeDestroy() {
    console.log('changeChatList beforeDestroy')
    this.$ipc.removeAllListeners('changeChatList')
    this.$signalMonitor.$off('clearTimer', this.clearRtcTimer)
    this.$signalMonitor.$off('isScroll')
    this.$signalMonitor.$off('activeListItem')
  },
  data() {
    return {
      active: '',
      isShowIcon: false,
      isShowMenu: false,
      activeItme: '',
      menuList: [],
      index: -1,
      currentPos: {
        // 记录右键列表的横纵坐标
        top: String,
        left: String
      },
      rightActive: '',
      listLength: '',
      initLength: 20,
      isLoadMore: false,
      updateChatList: [],
      ops: {
        vuescroll: {
          mode: 'native',
          detectResize: false
        },
        bar: {
          background: '#ccc9c7',
          keepShow: false
        }
      },
      chatOnlineList: {},
      loaded: false
    }
  },
  watch: {
    $route(to, from) { 
      try {
        if (to.name ==='Auth' || to.name === 'Chat'||  to.name === 'ChatSystem' || (this.$route.name === 'ChatRightArea' && !this.$route.query.hasOwnProperty('unreadCount'))) {
          this.active = this.$route.query.id;
          console.log('this.active:::', this.active)
          this.index = this.getItemIndex()
          if (this.index === undefined) return
          if (this.chat_chatList[this.active] && this.chat_chatList[this.active].unreadCount) {
            this.setMessageRead(this.active) 
          }
          this.scrollToCur(true)
        } 
      } catch (error) {
        console.log('route', error)
      }
    }
  },
  props: {
    chatList: Array,
    isShowAnimate: Boolean
  },
  components: {
    ListItem,
    Animates,
    Disconnect,
    ChatListSkeleton
  },
  computed: {
    chat_list() {
      if (false) {//!this.chat_is_loopend
        console.log('chatlist no order..........')
        this.updateChatList = _.values(this.chat_chatList)
      } else {
        console.log('chatlist order..........')
        this.updateChatList = _.orderBy(
          this.chat_chatList,
          ['isTop', 'startTime'],
          ['desc', 'desc']
        )
      }
      console.log('chat_chatList:::', this.chat_chatList)
      console.log('updateChatList:::', this.updateChatList)
      return this.updateChatList.slice(0, this.initLength)
    },
    ...mapGetters([
      'user_account',
      'chat_chatItemState',
      'chat_objectInfo',
      'chat_chatList',
      'chat_chatContent',
      'user_filePath',
      'contact_contactList',
      'chat_P2P_file_state',
      'chat_is_loopend'
    ])
  }
}
</script>
<style lang="scss">
.chat-list {
  .__view {
    width: 100% !important;
    overflow-x: hidden;
  }
  .empty-list {
    width: 100%;
    height: 100%;
    position: absolute;
  }

  .list-area {
    min-width: 226px;
    height: 100%;
    /* 父元素宽度 */
    /* 滚动条宽度 */
    box-sizing: border-box;
    overflow: auto;
    margin-bottom: 10px;
    /* 让元素宽度包含 padding, 否则元素会被滚动条遮挡 */
  }
  // .chat-list-meun {
  //   z-index: 9999999999999;
  //   .dropdown-menu {
  //     z-index: 90;
  //   }
  //   .dropdown-background {
  //     z-index: 190;
  //   }
  // }
  
}

</style>