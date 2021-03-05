<template>
  <li class="node-li">
    <div class="node-item" :class="{'theme-left-txt': !isCreateGroup&&!isCardSearch}" @click='toggle'>
      <i class="icon" v-html="isOpenDetail?'&#xe77a;':'&#xe778;'"></i>
      <div class="item-org-name" :title="model.orgName">{{model.orgName}}</div>
    </div>
    <ul v-if="isOpenDetail">
      <div v-if="hasChildOrgNode" :class="{'node-child': !(model.childUserNode&&model.childUserNode.length>0)}">
        <v-card-list>
          <v-card class="item-user-name" :class="{'theme-list-items': !isCreateGroup&&!isCardSearch}" :isSecondBreakpoint="true" v-for="(item, index) in model.childUserNode" :key="index" :title="item.enName" @contextmenu.prevent @click="clickUser(item)" @dbClick="dbClickUser(item)" debounced>
            <v-avatar class="item-user-avatar" size='is-small' :title="item.enName" :src='item.userHead' :sex="0" :offline="false" shape="round"  slot="leftAvatar"></v-avatar>
            <online v-if="hasOpenOnline" :itemId="item.userID" slot="left"></online>
            <v-avatar class="item-choose-mem" v-if="isCreateGroup" slot="after" size="is-small" :offline="false" shape="round" :src="isSelectItem({id:item.userID},true)"/>              
          </v-card>
        </v-card-list>
        <nodes v-for='(cel, index) in model.childOrgNode' :key="index" :model='cel' :isCreateGroup="isCreateGroup" :isSelectItem="isSelectItem" :changeItemState="changeItemState" :isCardSearch="isCardSearch" :sendCard="sendCard"></nodes>
      </div>
      <v-button class="is-loading is-medium" :ripple="false" v-else></v-button>
    </ul>
  </li>
</template>
<script type="text/javascript">
import { mapGetters } from 'vuex';
import mixin from '../ContactMixin.js';
export default {
  name: 'nodes',
  props: ['model', 'index','isCreateGroup','isSelectItem','changeItemState', 'isCardSearch', 'sendCard'],  
  mixins: [mixin],
  components: {
    Online: resolve => require(['../../Common/Online'], resolve)
  },
  data() {
    return {
      isOpenDetail: false, // 组织成员显示或隐藏
      orgId: 0, // 当前选中组织部门id
      orgIdChecked: [], // 当前选中组织部门下成员的id集合   !!!!!!!!!改为vuex，没有缓存，独立组件
      isOnlineLoadFinished: false, // 组织成员在线状态是否加载完毕
      orgUseronlineItem: {}, // 在线组织成员集合
      root: null,
      choosedImg: require("vrv-static/resources/images/contact/groupChoosed.png"),
      noneImg: require("vrv-static/resources/images/contact/groupChooseNone.png"),
      selectImg: require("vrv-static/resources/images/contact/groupChooseSelect.png"),
    };
  },
  computed: {
    ...mapGetters([
      'contact_organizationList',
      'contact_orgIdList',
      'user_netstat',
      'contact_orgUserToId',
      'chat_objectInfo',
      'contact_orgConfig'
    ]),
    hasChildOrgNode() {
      return this.model.childOrgNode || this.model.childUserNode;
    },
    hasOpenOnline() {
      return this.$config && this.$config.account && this.$config.account.openOnlineStatus;
    }
  },
  mounted() {
    this.root = this.$parent.$el
  },
  methods: {
    //创建群相关
    clickUser(item){
      if(this.isCreateGroup){
       this.changeItemState({id:item.userID,name:item.enName,thumbAvatar:item.userHead,gender:0});
      } else if (this.isCardSearch){
        this.sendCard({id:item.userID,name:item.enName,thumbAvatar:item.userHead,gender:0})
      } else {
       this.openOrgDetail(item)
      }
    },
    dbClickUser(item){
      if(!this.isCreateGroup){
        if(item.userID!=this.user_account.userId && this.contact_orgConfig[item.orgID].allowChat){
          this.startChat(item, 1);
        }
      }
    },
    // 结点：展开/收缩
    toggle() {
      // 断网时展开结点，不再获取数据
      if (
        !this.contact_orgIdList.includes(this.model.orgID) &&
        // ((!this.user_netstat && !this.isOpenDetail) || this.model.leaf !== 1)
        ((!this.user_netstat && !this.isOpenDetail))
      )
        return;
      this.isOpenDetail = !this.isOpenDetail;
      this.isOpenDetail && this.handleDuplicatedData(this.model.orgID);
    },
    // 处理树结构数据重复请求时，优先拉取缓存数据
    handleDuplicatedData(id) {
      this.orgId = id;
      this.setOrganizationList();
    },
    // 获取组织架构数据
    setOrganizationList() {
      let getVisibleOrgUsersParam = {
        type: 0,
        orgId: this.orgId
      };
      console.log('getVisibleOrgUsersParam', getVisibleOrgUsersParam);
      this.$Service.enterprise.getVisibleOrgUsers(getVisibleOrgUsersParam, resp => {
        console.log('获取组织架构信息', resp);
        // allowChat : 1 允许聊天
        // contactVisiable : 1 允许查看资料
        this.$Service.log(`获取组织架构信息::::
          code: ${resp.code}
          orgs: ${resp.orgs&&resp.orgs.length}
          users: ${resp.users&&resp.users.length}
          allowChat: ${resp.allowChat}
          contactVisiable: ${resp.contactVisiable}
        `)
        if (resp.code !== 0) {
          return;
        };
        let allowChat = resp.allowChat === 0 ? false : true; // false 不允许聊天  true 允许聊天
        let contactInvisiable = resp.contactVisiable === 0 ? true : false; //  true 隐藏信息 false 不隐藏信息
        this.$set(this.contact_orgIdList, this.contact_orgIdList.length, this.orgId);
        this.buildTreeStructure(this.contact_organizationList, resp);
        let orgConfig = {};
        this.$set(orgConfig, getVisibleOrgUsersParam.orgId, { allowChat, contactInvisiable});
        this.$store.commit('SET_ORGANIZATON_CONFIG', orgConfig);
      });
    },
    // 递归构造组织架构的树结构
    buildTreeStructure(node, { orgs, users }) {
      node && node.find((element, index) => {
        if (element.orgID === this.orgId) {
          this.$set(element, 'childOrgNode', orgs);
          this.$set(element, 'childUserNode', _.orderBy(users, ['pinyin'], ['asc']));
          // 保存到树结构后清空，避免注销或者被挤下线，再次登陆数据异常
          this.orgId = 0;
          this.$store.dispatch('SET_ORG_ONLINE_LISTS', {id:element.orgID, data:users})
          return;
        } else {
          if (element.childOrgNode && element.childOrgNode.length !== 0)
            this.buildTreeStructure(element.childOrgNode, { orgs, users });
        }
      });
    },
    openOrgDetail(item) {
      item.contactInvisiable = this.contact_orgConfig[item.orgID].contactInvisiable;
      item.isOrg = true;
      item.allowChat = this.contact_orgConfig[item.orgID].allowChat;
      this.openDetail(0, item, -1);
    },
    /**
     * 组织成员在线设备类型
     * deviceType 1：PC；2：手机；3：pad；4：网页
     */
    currentOnlineDeviceType({userID}) {
      if(!this.orgUseronlineItem[userID]) return;
      let device = this.orgUseronlineItem[userID].deviceType;
      return device===1 ? '&#xe627;':'&#xe693;'
    }
  }
};
</script>
<style lang="scss">
.node-li {
  padding: 6px;
  padding-right: 0px;
  color: #000;
  .node-item {
    color: #000;
    display: flex;
    @include ellipsis;
    .item-org-name {
      cursor: pointer;
      max-width: 166px;
      overflow: hidden;
      white-space: nowrap;
      text-overflow: ellipsis;
    }
  }
  .is-loading {
    margin: 15px 25px;
    height: 100%;
    background: transparent;
  }
  .item-user-name {
    height: 41px;
    .default-content {
      height: 41px;
      .media-left {
        margin-right: 12px;
      }
      .title {
        color: #000;
        font-size: 14px;
        .title-main {
          cursor: pointer;
        }
      }
    }
    .item-user-avatar {
      width: 25px;
      height: 25px;
    }
    .item-choose-mem{
      width: 20px;
      height: 20px;
    }
    .online-icon {
      right: -2px;
      bottom: -5px;
      background: none;
    }
    .online-icon-compute {
      font-size: 12px;
    }
    .online-icon-2 {
      width: 14px;
      height: 13px;
    }
    .online-icon-1 {
      width: 12px;
      height: 12px;
    }
    &:hover {
      background: transparent;
    }
  }
  ul {
    padding: 2px 0px 2px 6px;
    .node-child {
      &:first-child {
        padding-top: 8px;
      }
    }
  }
}
</style>
