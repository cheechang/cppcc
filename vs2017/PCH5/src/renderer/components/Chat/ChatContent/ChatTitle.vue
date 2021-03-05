<template>
  <div class="title-area">
    <!-- 显示名称 -->
    <div class="chat-name-area" >
      <div v-text="sessionName||$route.query.name" @click="seeDetail" class='chat-name'></div>
      <div class="input-state" v-if="chatType ===1 && isEntering">{{$t('chat.typing')}}</div>
    </div>
    
    <!-- tab页面 切换聊天区域和群文件区域 -->
    <div class="group-title theme-table" v-if="chatType !== 3" >
      <v-tabs position="is-centered" :isIcon="true" class="block list-area" @change="changeTabView" :value="currentActive">
        <v-tab-item v-for="(tabs, index) in tabList" :key="index" class="items"  :icon="tabs.icon"  :iconTitle="tabs.iconTitle"></v-tab-item>
      </v-tabs>
    </div>
    <contact-info v-if='isShowContactInfo' @close="isShowContactInfo=false"></contact-info>
    <v-modal  cardSize="group-info-area" v-if='isShowGroupInfo'  @close="isShowGroupInfo=false">
      <group-info :isNotAllowMsg='true'></group-info>
    </v-modal>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import contactInfo from '../../Group/ChatGroupInfo/ChatMemberInfo'
import GroupInfo from '../../Group/ContactGroupInfo';
import MsgMxin from '../msgMixin'

export default {

  data() {
    return {
      isEntering: false,
      isEnterTimer: {},
      tabList: [
        {icon: '&#xe6b0;', iconTitle: this.$t('chat.chat'), view: 'chat'},
        {icon: '&#xe7c3;', iconTitle: this.$t('chat.file'), view: 'file', components:'ChatTabFile'},
      ],
      isShowContactInfo: false,
      isShowGroupInfo: false
    }
  },
  mixins: [MsgMxin],
  props: {
    currentActive: Number,
    id: String,
    chatType: Number,
    name: String,
    inputState: Object
  },
  methods: {
    changeTabView(value) {
      console.log('value:::', value)
      this.$emit('changeTab', {index: value, view: this.tabList[value].view, components: this.tabList[value].components});
    },

    // * 查看详情
    seeDetail() {
      switch (this.chatType) {
        case 1 : 
        this.seeContactInfo()
        break
        case 2 :
        this.isShowGroupInfo = true
        break
        case 3 :
        // console.log('work_storeApps', this.work_storeApps)
        // console.log('id', this.id)
        // if (this.work_storeApps[this.id]) {
        //   console.log('work_storeApps')
        //   this.appNewWindow(this.work_storeApps[this.id]);
        // }
        break
        default :
        break
      }
    },

    // * 查看联系人信息
    seeContactInfo() {
      if (this.id === this.user_account.userId) { // 我的设备不显示
        return 
      }
      this.isShowContactInfo = true
      this.$nextTick(() => {
      let memberInfo = this.contact_contactList[this.id]
        if (memberInfo) {
          this.$signalMonitor.$emit('expendChatMemberInfo', memberInfo);
        } else {
          let getUserInfoParam = { userId: this.id }
          let getUserInfoCb = successRes => {
            memberInfo = successRes.users;
            this.$signalMonitor.$emit('expendChatMemberInfo', memberInfo);
          }
          this.$Service.search.getUserInfo(getUserInfoParam, getUserInfoCb)
        } 
      })
    }
  },
  mounted() {
    let type =  this.$Service.config.getUserTypeById({ targetId: this.id })
    if (type === 2) {
      this.tabList.splice(1, 0, {icon: '&#xe6c0;', iconTitle: this.$t('groups.announcement'), view: 'notice', components: 'ChatGroupNotice'})
      //服务是否开启了群消息置顶
      this.isEidGroup(this.id,openGroupMsgTop =>{
        this.tabList.splice(3, 0, {icon: '&#xe6a7;', iconTitle: this.$t('chat.msgRecord'), view: 'msgRecord', components:(type==2&&openGroupMsgTop)?'ChatTabRecord':'ChatMsgRecord'});
      })
    }
  },
  watch: {
    /**
     * 监听用户输入状态
     * status 0 开始输入 1 结束输入
     * 防止用户意外退出 40s后自动置为正常状态
     */
    inputState() {
      /** 非个人不监听状态 */
      if (this.chatType !== 1) { 
        return
      }
     
      if (this.inputState && this.inputState.status === 0) {
        this.$Service.log(`reg user input start  ${this.id}`)
        if (this.isEnterTimer) {
          console.log('clearInterval')
          clearInterval(this.isEnterTimer)
        }
        this.isEntering = true
        let count = 40
        this.isEnterTimer = setInterval(() => {
          if (count < 1) {
            clearInterval(this.isEnterTimer)
            console.log('clearInterval 40 over')
            this.$signalMonitor.$emit('updateInputeState', this.id)
          } else {
            count--
          }
        }, 1000)
      } else {
        this.$Service.log(`reg user input end  ${this.id}`)
        console.log('reg user input end')
        if (this.isEnterTimer) {
          clearInterval(this.isEnterTimer)
        }
        this.isEntering = false
      }
    } 
  },

  beforeDestroy() {
    console.log('beforeDestroy::::  chatTitle')
    if (this.isEnterTimer) {
      clearInterval(this.isEnterTimer)
    }
  },
  components: {
    GroupInfo,
    contactInfo
  },
  computed: {
    // 会话名称展示
    sessionName() {
    
      if (this.id === this.user_account.userId) {
        let myDevice = this.$t('contacts.device')
        this.$emit('updateName', myDevice)
        return myDevice
      } 
      let name
      //chatType 1 个人
      if (this.chatType === 1 && (this.contact_contactList[this.id] && this.contact_contactList[this.id].remark !== undefined) || (this.contact_contactList[this.id] && this.contact_contactList[this.id].name !== undefined)) {
       name = this.contact_contactList[this.id].remark || this.contact_contactList[this.id].name
      // chatType 2 群组
      } else if (this.chatType === 2 && this.contact_groupList[this.id] && this.contact_groupList[this.id].groupName) {
        name = this.contact_groupList[this.id].groupName
      // chatType 3 应用
      } else if (this.chatType === 3 && this.contact_appList[this.id] && this.contact_appList[this.id].name!== undefined) {
        name = this.contact_appList[this.id].name
      // 在contact applist 都查无此Id 使用最近会话的名称
      } else {
        name = this.chat_chatList[this.id].name
      }
       this.$emit('updateName', name)
       return name
    },
     ...mapGetters([
      'contact_contactList',
      'contact_appList',
      'contact_groupList',
      'chat_chatList',
      'user_account',
      'work_storeApps',
      "user_systemConfig"
    ])
  }
};
</script>

<style lang="scss">
.title-area {
  background: #fff;
  height: 42px;
  width: 100%;
  display: flex;
  justify-content: space-between;
  align-items: center;
  border-bottom: solid 1px $--border-color-grey-lighten;
  .chat-name-area {
    color: #000;
    font-weight: blod;
    font-size:$--font-size-primary;
    display: flex;
    margin-left: 18px;
    align-items: center;
    overflow: hidden;
    .input-state {
      font-size: 14px;
      margin-left: 10px;
    }
    .chat-name {
      height: 24px;
      &:hover {
        border-bottom: solid 1px $--color-text-hover;
        cursor: pointer;
        color: $--color-text-hover;
      }
    }
  }
  .group-title {
    margin-right: 32px;
    a {
      padding: 0.5em 0.3rem;
      color: #bdbdbd;
    }
  }
  .group-info-area {
    width: 342px;

    .modal-card-body {
      background: none;
      .contact-group-info {
        width: 342px;
        .v-lists {
          width: 100%;
          .v-dial-list{
            left: -92px;
          }
        }
      }
    }
  }
}
</style>
