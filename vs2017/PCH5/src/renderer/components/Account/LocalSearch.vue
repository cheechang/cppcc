<template>
  <div class="search-area" :style="getListStyle" ref="popper">
    <v-button class="is-loading is-large" :ripple="false" v-if="searching"></v-button>
    <v-card-list class="search-item" v-else>
      <p class="sup-title" ref="userTitle" v-if="contactList.length>0">{{$t('contacts.friends')}}</p>
      <v-card ref="userCard" class="item-selected" :class="active===index?'active':''" v-for="(item,index) in getContactSearchList" :key="index" :title="item.remark||item.name||item.appName" :index="index" @click="active = index" @dbClick="selectChat((item.appID&&3)||1,item)">
        <v-avatar size='is-small' :sex="(item.appID&&3)||item.gender" :src='item.thumbAvatar||item.appIcon' :offline="false" shape="round"  slot="leftAvatar"></v-avatar>
      </v-card>
      <p class="sup-title" ref="groupTitle" v-if="!isContact&&groupList.length>0">{{$t('groups.group')}}</p>
      <v-card ref="groupCard" class="item-selected" :class="active===index + contactList.length?'active':''" v-for="(item,index) in getGroupSearchList" :key="index + contactList.length" :title="item.groupName" :index="index" @click="active = index + contactList.length" @dbClick="selectChat(2,item)">
        <v-avatar size='is-small' :src='item.avatar' :sex="4" :offline="false" shape="round"  slot="leftAvatar"></v-avatar>
      </v-card>
      <div v-for="(items, title, index) in orgList" v-if="!isContact" :key="index + contactList.length + groupList.length">
        <p class="sup-title" ref="orgTitle">{{title||'组织成员'}}</p>
        <v-card ref="orgCard" v-for="(item, id) in items" :key="id" class="item-selected" :class="active===(item.index + contactList.length + groupList.length)?'active':''" :title="item.name" @click="active = item.index + contactList.length + groupList.length" @dbClick="selectChat(1,item)">
          <v-avatar size='is-small' :title="item.name" :src='item.thumbAvatar' :sex="item.gender" :offline="false" shape="round"  slot="leftAvatar"></v-avatar>
        </v-card>
      </div>
    </v-card-list>
  </div>
</template>
<script>
import _ from 'lodash';
import { mapGetters } from 'vuex';
import mixin from '../Contact/ContactMixin';
export default {
  mixins: [mixin],
  data() {
    return {
      active: '',
      contactList: [],
      groupList: [],
      orgList: {},
      orgListLength: 0,
      appList: [],
      isContactShow: false,
      listNum: 0, //滚动条滚动的临界值
      groupdefault: require('vrv-static/resources/images/contact/group.png'),
      manDefault: require('vrv-static/resources/images/contact/manDefault.png'),
      contactListIds: [],
      groupListIds: [],
      searching: false
    };
  },
  props: {
    value: String,
    hoverIndex: Number,
    direction: Number,
    height: {
      type: Number,
      defalut: 0
    },
    openChat: {
      type: Boolean,
      defalut: false
    },
    forWard: {
      type: Boolean,
      default: false
    },
    isContact: false
  },
  computed: {
    ...mapGetters(['user_account','contact_contactList','contact_appList','contact_groupList']),
    getListStyle() {
      let result = {};
      if (this.contactList.length !== 0 || this.groupList.length !== 0 || _.values(this.orgList).length !== 0)
        result = { background: '#fff !important' };
      this.$set(result, 'min-height', this.height + 'px');
      return result;
    },
    /**
     * 实现本地搜索结果展示的联系人/应用信息实时更新
     */
    getContactSearchList() {
      if (this.contactListIds.length !== 0 || this.appList.length !== 0) {
        let contacts = _.filter(this.contact_contactList, e => {
          return e.isHidden!==1 && this.contactListIds.includes(e.id);
        })
        this.contactList = this.forWard ? contacts:[ ...this.appList,...contacts];
      } else {
        if (!this.isContact) {
          this.contactList = [];
        }
      }
      return this.contactList;
    },
    /**
     * 实现本地搜索结果展示的群信息实时更新
     */
    getGroupSearchList() {
      if (this.groupListIds.length !== 0 && !this.isContact) {
        if(_.values(this.contact_groupList).length===0) {
          return this.groupList;
        }
        this.groupList = _.filter(this.contact_groupList, e => {
          return this.groupListIds.includes(e.groupId);
        });
      } else {
        this.groupList = [];
      }
      return this.groupList;
    }
  },
  watch: {
    openChat(value) {
      if (value) {
        let index = 2;
        if(this.contactList[this.active]){
          index = this.contactList[this.active].appID && 3 || 1;
        }
        if (this.orgListLength-1 >= this.active) {
          index = 1
        }
        let resultLength = this.active - this.contactList.length - this.groupList.length;
        if (resultLength >= 0)
          _.forEach(this.orgList, (element, tabName) => {
            _.forEach(element, (e, i) => {
              console.log(e.index, resultLength)
              if (e.index!==resultLength) return
              this._handleOpenChat(index, element[i])
            })
          })
        else
          this._handleOpenChat(index)
      }
    },
    hoverIndex(value) {
      this.active = value;
      if(value===-1) return;
      if (this.contactList || this.groupList || this.orgList)
        this.$nextTick(() => this.scrollToItem());
    },
    // value(value) {
    //   console.log('开始搜索');
    //   this.searchList(value);
    // },
    // 防抖处理，减少频繁改变导致的调用次数过多
    value: _.debounce(function(value) {
      this.searchList(value);
    }, 300),
  },
  methods: {
    searchGroupMember(value) {
      if (value.trim() === "") return;
      let groupSearchMemberParam = {
        groupId: this.$route.query.id,
        key: value
      };
      this.$Service.search.groupSearchMember(groupSearchMemberParam, resp => {
        console.log("群成员搜索", resp);
        this.contactList = _.filter(resp.members, e => e.id!==this.user_account.userId);
      });
    },
    _handleOpenChat(index, value) {
      if (!this.forWard) {
        this.selectChat(
          index,
          this.contactList[this.active] || 
          this.groupList[this.active - this.contactList.length] || 
          value
        );
      } else {
        this.$emit(
          'forwardMsg',
          this.contactList[this.active] ||
          this.groupList[this.active - this.contactList.length] ||
          value
        );
      }
    },
    initData() {
      this.contactListIds = [];
      this.groupListIds = [];
      this.orgList = {};
      this.appList = [];
      this.listNum = 0;
      this.orgListLength = 0;
    },
    /**
     * 根据临界值判断到底部/顶部后滚动
     * 两种情况：
     * 1：选中项到底部触发滚动，需要设置临界值
     * 2：键盘直接触发滚动，不需要考虑临界值、鼠标和键盘滚动冲突等各种情况影响
     */
    scrollToItem() {
      let userLength = this.contactList.length || 0;
      let userTitleHeight = (this.$refs.userTitle && this.$refs.userTitle.offsetHeight) || 0;
      
      let groupLength = this.groupList.length || 0;
      let groupTitleHeight = (this.$refs.groupTitle && this.$refs.groupTitle.offsetHeight) || 0;
      
      let orgLength = this.orgListLength || 0;
      let orgTitleHeight = (this.$refs.orgTitle &&this.$refs.orgTitle[0] && this.$refs.orgTitle.length*this.$refs.orgTitle[0].offsetHeight) || 0;
      
      let cardHeight =
        (this.$refs.userCard[0] &&
          this.$refs.userCard[0].$refs.card.offsetHeight) ||
        (this.$refs.groupCard[0] &&
          this.$refs.groupCard[0].$refs.card.offsetHeight) ||
        (this.$refs.orgCard[0] &&
          this.$refs.orgCard[0].$refs.card.offsetHeight);

      let averageHeight = ((userLength+groupLength+orgLength)*cardHeight+orgTitleHeight+userTitleHeight+groupTitleHeight)/(userLength+groupLength+orgLength)
      let totalHeight = this.$refs.popper.offsetHeight;
      if (this.direction === 40) {
        if ((this.listNum + 2) * averageHeight <= totalHeight) this.listNum++;
      } else if (this.listNum > 2) {
        this.listNum--;
      }
      this.$refs.popper.scrollTop =
        (this.hoverIndex - this.listNum + 1) * averageHeight;
    },
    selectChat(index, item) {
      console.log('本地搜索触发成功');
      this.$emit('closeAccountCenter');
      if (!this.forWard) {
        this.startChat(item, index)
      } else {
        this.$emit('forwardMsg',item);
      }
      this.$emit('close');
    },
    searchList(value) {
      this.searching = true;
      if (value.trim() === '') {
        // 值为空时 清空当前数据
        this.searching = false;
        this.initData();
        this.$emit('updateList', 0);
        return;
      }
      if (this.isContact) {
        this.searchGroupMember(value);
        return;
      }
      setTimeout(() => {
        // 监听输入内容改变：初始化滚动条、hover、临界值
        [this.$refs.popper.scrollTop, this.active] = [0, ''];
        // 清空上一次搜索数据
        this.initData();
        console.log('value:::', value)
        this.$Service.search.searchFromLocal({ key: value }, resp => {
          console.log('本地搜索返回结果', resp);
          this.$Service.log(`localsearch--code:${resp.code}--appList--length:${resp.vtEntApp&&resp.vtEntApp.length}`);
          if (this.value !== resp.key) {
            console.log('不是同一次请求,不做处理');
            return;
          }
          // 初始化解决快速本地搜索导致的结果不匹配（两个搜索都处于回调状态，数据不会清空）
          this.initData();
          this.$Service.log(`localsearch--appList--length:${resp.vtEntApp&&resp.vtEntApp.length}`);
          this.$Service.log(`localsearch--contactList--length:${resp.users&&resp.users.length}`);
          this.appList = resp.vtEntApp || []; // 企业应用列表
          this.contactList = (resp.users && _.filter(resp.users, (e) => e.id !== this.user_account.userId)) || []; // 联系人列表，过滤掉自己
          _.forEach(this.contactList, element => {
            element.isUser && this.contactListIds.push(element.id);
          });
          this.$Service.log(`localsearch--groupList--length:${resp.groups&&resp.groups.length}`);
          this.groupList = resp.groups || []; // 群组列表
          _.forEach(this.groupList, element => {
            this.groupListIds.push(element.groupId);
          });
          let entResp = {
            total:0,
            code:0
          }
          this._queryEntUserOneByIdHandler(entResp)
          //this.$Service.enterprise.queryEnterpriseUserlist({username:value, pageSize:100}, this._queryEntUserOneByIdHandler);
        });
      }, 50);
    },
    _queryEntUserOneByIdHandler(entResp) {
      console.log('企业查找搜索:',entResp);
      this.$Service.log(`localsearch--orgList--length:${entResp.users&&entResp.users.length}`);
      this.orgListLength = entResp.total;
      if (entResp.total === 0) {
        this.$Service.log(`localsearch--result--length:${this.appList.length + this.contactListIds.length + this.groupList.length}`)
        this.$emit(
          'updateList',
          this.appList.length + this.contactListIds.length + this.groupList.length
        );
        console.log("搜索完成,总数为：", this.appList.length + this.contactListIds.length + this.groupList.length);
        this.searching = false;
        return;
      }
      let totalIndex = 0;
      _.forEach(entResp.users, (element,index)=>{
        _.forEach(Object.values(element)[0], (elementUser, i)=>{
          let item={
            id: elementUser.userID,
            thumbAvatar: elementUser.userHead,
            name: elementUser.enName,
            gender: 0,
            index: totalIndex,
          }
          totalIndex++;
          if (!this.orgList[Object.keys(element)]) {
            this.$set(this.orgList, Object.keys(element), {});
          }
          this.$set(this.orgList[Object.keys(element)], item.id, item);
        })
      })
      this.$Service.log(`localsearch--result(include orgUser)--length:${this.appList.length + this.contactListIds.length + this.groupList.length + this.orgListLength}`);
      this.$emit(
        'updateList',
        this.appList.length + this.contactListIds.length + this.groupList.length + this.orgListLength
      );
      console.log("搜索完成,总数为：", this.appList.length + this.contactListIds.length + this.groupList.length + this.orgListLength);
      this.searching = false;
    }
  }
};
</script>
<style lang="scss" scoped>
.search-area {
  // height: calc(100% - 32px);
  height: 100%;
  // max-height: 545px;
  overflow: auto;
  .is-loading {
    height: 100%;
    display: flex; //fit xp
    flex: 1; //
  }
  .search-item {
    .item-selected {
      &:hover {
        background: $--color-hover;
      }
    }
  }
  .sup-title {
    font-size: $--font-size-mid;
    // background: $--color-text-extra-light;
    background: #dcdcdc;
    padding: 5px;
  }
  .active {
    background: $--color-active;
  }
}
</style>


