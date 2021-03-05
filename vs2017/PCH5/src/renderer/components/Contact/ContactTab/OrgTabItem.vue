<template>
  <d-skeleton>
    <div class="organization-tab-item" v-if="isLoadFinished">
      <p class="defalut-page" v-if="!contact_organizationList.length"></p>
      <ul v-else :class="isCreateGroup||isCardSearch? 'node-ul-group':'node-ul'" v-for="(value, key, index) in contact_organizationList" :key="key">
        <org-node :model="value" :index="index" v-if="value" :isCreateGroup="isCreateGroup" :isCardSearch="isCardSearch" :sendCard="sendCard" :isSelectItem="isSelectItem" :changeItemState="changeItemState"></org-node>
      </ul>
    </div>
    <contact-skeleton slot="skeleton" type="org"></contact-skeleton>
  </d-skeleton>
</template>
<script>
import OrgNode from './OrgNode.vue';
import mixin from '../ContactMixin.js';
import { mapGetters } from 'vuex';
import ContactSkeleton from './ContactSkeleton'
export default {
  mixins: [mixin],
  data() {
    return {
      isLoadFinished: false
    }
  },
  props: {
    isPullOrgList: Boolean,

    //创建/邀请群相关
    isSelectItem: Function,
    changeItemState: Function,
    isCreateGroup: Boolean,
    isCardSearch: Boolean,
    sendCard: Function
  },
  components: {
    OrgNode,
    ContactSkeleton
  },
  computed: {
    ...mapGetters(['contact_organizationList', 'contact_orgIdList'])
  },
  watch: {
    isPullOrgList(hasFind) {
      hasFind && this.handleDuplicatedData();
    }
  },
  created() {
    setTimeout(() => {
      this.isLoadFinished = true
    }, 300);
  },
  methods: {
    // 处理 树结构 数据重复请求
    handleDuplicatedData() {
      this.user_netstat &&
      !this.contact_orgIdList.includes(0) &&
      this.setOrganizationList();
    },
    // 获取组织架构数据
    setOrganizationList() {
      this.$Service.log('获取根节点组织架构信息start')
      let getVisibleOrgUsersParam = { type: 0, orgId: 0 };
      this.$Service.enterprise.getVisibleOrgUsers(getVisibleOrgUsersParam, resp => {
        console.log('根组织架构信息', resp);
        this.$Service.log(`获取根节点组织架构信息end::::
          code: ${resp.code}
          orgs: ${resp.orgs&&resp.orgs.length}
          users: ${resp.users&&resp.users.length}
        `)
        if (resp.code !== 0) return;
        this.$set(this.contact_orgIdList, 0, 0);
        this.$store.commit('SET_ORGANIZATON_LIST', resp.orgs);
      });
    }
  }
};
</script>
<style lang="scss">
.organization-tab-item {
  width: 100%;
  height: 100%;
  ul {
    font-size: 14px;
    width: 100%;
    height: 100%;
    margin: -6px 0;
  }
  .node-ul {
    margin-top: 0;
    overflow-y: auto;
  }
  .node-ul-group{
    margin-top: 0;
    overflow-y: auto;
    &:hover {
      overflow-y: auto;
    }
  }
  .defalut-page {
    width: 100%;
    height: 100%;
    background: url('~vrv-static/resources/images/common/empty-list.png')
      42% 36% no-repeat;
  }
}
</style>


