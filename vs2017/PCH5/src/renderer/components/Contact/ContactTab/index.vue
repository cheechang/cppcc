<template>
  <v-tabs position="is-centered" v-model="currentTab" class="block contact-list-area" size="contact-tab" @change="changeTab">
    <div class="tab-list" v-for="(tabItem, index) in computeTabList" :key="index">
      <v-tab-item :label="tabItem.tabName" class="items">
        <!-- 重新登录中 -->
        <log-back v-if="showDisconnect" :tip="disConnectTip"></log-back>
        <!-- 联系人/群/组织架构 -->
        <div class="tab-component">
          <component v-show="selectedTab===index" :is="tabItem.tabView" :isPullOrgList="isPullOrgList"></component>
        </div>
      </v-tab-item>
    </div>
  </v-tabs>
</template>
<script>
import ContactMixin from '../ContactMixin.js';
import CommonMixin from '../../Common/commonMixin.js'
import LogBack from '../../Common/LogBack';
import { mapGetters } from 'vuex';
export default {
  data() {
    return {
      currentTab: 0,
      isPullOrgList: false,
      tabList: [
        { tabName: this.$t('contacts.friends'), tabView: resolve => require(['./ContactTabItem'], resolve) },
        { tabName: this.$t('groups.group'), tabView: resolve => require(['./GroupTabItem'], resolve) },
        // { tabName: this.$t('organizations.organization'), tabView: resolve => require(['./OrgTabItem'], resolve) }
      ],
      selectedTab: 0
    };
  },
  mixins: [ContactMixin,CommonMixin],
  computed: {
    ...mapGetters(['contact_isInOrg']),
    computeTabList() {
      return this.tabList.filter((e, i) => i!==2 || this.contact_isInOrg===1)
    }
  },
  components: {
    LogBack
  },
  created() {
    setTimeout(() => {
      if (this.contact_isInOrg === -1) { // 已经存储到vuex
        this.setOrganizationList();
      } 
    }, 10);
  },
  methods: {
    /**
     * 切换联系人/群/组织架构
     */
    changeTab(value) {
      this.selectedTab= value;
      this.active = '';
      this.isPullOrgList = false;
      this.$nextTick(() => { // 避免重复拉取组织架构数据
        if (value === 2) this.isPullOrgList = true;
      });
    },
    // 获取组织架构数据
    setOrganizationList() {
      let getVisibleOrgUsersParam = { type: 0, orgId: 0 };
      this.$Service.enterprise.getVisibleOrgUsers(getVisibleOrgUsersParam, resp => {
        let isShow = resp.orgs&&resp.orgs.length!==0;
        this.$store.commit('SET_ORGTAB_STATUS', isShow?1:0);
        this.$Service.log(`获取组织架构信息:::是否显示${isShow}:::
          code: ${resp.code}
          orgs: ${resp.orgs&&resp.orgs.length}
          users: ${resp.users&&resp.users.length}
        `);
      });
    }
  }
};
</script>
<style lang="scss">
.contact-tab {
  font-size: 14px;
  margin-bottom: 0;
  &:not(:last-child) {
    margin-bottom: 0;
  }
  .item {
    li {
      flex: 1;
    }
  }
}
.contact-list-area {
  min-width: 226px;
  height: 100%;
  box-sizing: border-box;
  .tab-content {
    display: flex;
    flex-direction: column;
    height: calc(100% - 36px);
    overflow-y: hidden;
    &:hover {
      overflow-y: auto;
    }
    .tab-list {
      height: 100%;
      .items {
        height: 100%;
        display: flex;
        flex-direction: column;
        .tab-component {
          flex: 1;
          display: flex;
          &:hover{
            overflow-y: auto;
          }
        }
      }
    }
  }
}
</style>

