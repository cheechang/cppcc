<template>
  <div class="pc-search-list" id="netSearchList">
    <div class="search-find">
      <v-field class="search-filed" :tipLabel="tipLabel" :tipActive="isSearchTipShow" tipPosition="is-bottom">
        <v-input class="search-input" maxlength="24" hasLine :isBorder="false" :isAutoFocus='true' v-model="inputSearch" :placeholder="inputHint" :position="inputSearch==''?'left':'right'" @keyup-enter="searchFromNet">
          <i v-if="inputSearch==''" class="icon search-icon" slot="expand">&#xe68c;</i>
          <i v-else class="icon" slot="expand" @click="clearInput">&#xe650;</i>
        </v-input>
      </v-field>
      <v-button class="theme-botton search-button" type="is-primary" @click="searchFromNet">{{ $t('search.find') }}</v-button>
    </div>
    <div class="search-result" v-if="isLoadingSearch">
      <div class="result" v-if="hasSearchResult">
        <p>{{ $t('search.result', {value: searchContactResult.length+searchAppResult.length+searchGroupResult.length}) }}</p>
        <div class="result-list">
          <card-search :list="contactSearchList" :isApp="false" :subtitle="$t('contacts.friends')" :buttonLists="contactButtonLists" @click-button="args=>requestAddGroup(args,2)"></card-search>
          <div class="v-divder" v-if="appSearchList.length!==0&&contactSearchList.length!==0"></div>
          <card-search :list="groupSearchList" :isApp="false" :sex="4" :subtitle="$t('groups.group')" :buttonLists="groupButtonLists" @click-button="args=>requestAddGroup(args,3)"></card-search>
          <div class="v-divder" v-if="appSearchList.length!==0&&groupSearchList.length!==0"></div>
          <card-search :list="appSearchList" :isApp="true" :sex="3" :subtitle="$t('contacts.application')" :buttonLists="appButtonLists" @click-button="args=>requestAddGroup(args,1)"></card-search>
        </div>
      </div>
      <v-button class="is-loading is-large" :ripple="false" v-else></v-button>
    </div>
  </div>
</template>
<script>
import ContactMixin from '../../Contact/ContactMixin';
import CardSearch from './CardSearch';
import { mapGetters } from 'vuex';
export default {
  mixins: [ContactMixin],
  data() {
    return {
      inputSearch: '',
      tipLabel: this.$t('search.noEmpty'),
      searchContactResult: [],
      searchGroupResult: [],
      searchAppResult: [],
      hasSearchResult: false,
      isLoadingSearch: false,
      isSearchTipShow: false,
      contactButtonLists: [
        { icon: '&#xe62c;', tooltip: this.$t('search.addFriend') },
        { id: 'msg', icon: '&#xe68d;', tooltip: this.$t('contacts.message') }
      ],
      groupButtonLists: [
        { icon: '&#xe62c;', tooltip: this.$t('search.joinGroup') },
        { id: 'msg', icon: '&#xe68d;', tooltip: this.$t('contacts.message') }
      ],
      appButtonLists: [
        { icon: '&#xe62c;', tooltip: this.$t('search.addApp') }
      ]
    };
  },
  components: {
    CardSearch
  },
  computed: {
    ...mapGetters(['user_userFieldName', 'contact_contactList', 'contact_groupList']),
    // 提示内容将根据服务器返回数据填写
    inputHint() {
      return this.$t('search.searchHint', {value: this.user_userFieldName});
    },
    // 联系人搜索结果
    contactSearchList() {
      let checkDuplicate = [];
      this.searchContactResult.forEach((element, index) => {
        // 服务器返回数据异常，过滤重复数据
        if (index !== 0 && checkDuplicate.includes(element.id)) {
          this.searchContactResult.splice(index, 1);
          return;
        }
        checkDuplicate.push(element.id);
        if (element.id !== this.user_account.userId) {
          let result = this.contact_contactList[element.id]?this.$t('search.addedFriend'):''
          this.$set(element, 'relation', result);
        } else {
          this.$set(element, 'relation', this.$t('search.addedSelf'));
        }
      });
      return this.searchContactResult;
    },
    //群搜索结果
    groupSearchList() {
      let checkDuplicate = [];
      this.searchGroupResult.forEach((element, index) => {
        // 服务器返回数据异常，过滤重复数据
        if (index !== 0 && checkDuplicate.includes(element.groupId)) {
          this.searchGroupResult.splice(index, 1);
          return;
        }
        checkDuplicate.push(element.groupId);
        let result = this.contact_groupList[element.groupId]?this.$t('search.joined'):''
        this.$set(element, 'relation', result);
      });
      return this.searchGroupResult;
    },
    // 公众号搜索结果
    appSearchList() {
      let checkDuplicate = [];
      this.searchAppResult.forEach((element, index) => {
        // 服务器返回数据异常，过滤重复数据
        if (index !== 0 && checkDuplicate.includes(element.appID)) {
          this.searchAppResult.splice(index, 1);
          return;
        }
        checkDuplicate.push(element.appID);
        this.$Service.contact.contactIsBuddy({ userId: element.appID }, resp => {
          let result = resp.isBuddy ? this.$t('search.followed') : '';
          this.$set(element, 'relation', result);
        });
      });
      return this.searchAppResult;
    }
  },
  created() {
    this.$signalMonitor.$on('update-network-searchlist', this._updateSearchList)
  },
  methods: {
    // 网络搜索
    searchFromNet() {
      let inputSearch = this.inputSearch.trim();      // 去除搜索内容前后空格
      this.isSearchTipShow = inputSearch === '';
      if (inputSearch === '') {
        setTimeout(() => {
          this.isSearchTipShow = false;
        }, 1000);
        return;
      };
      [this.isLoadingSearch, this.hasSearchResult] = [true, false];
      this.$Service.search.searchFromNet({ key: inputSearch }, res => {
        console.log('网络搜索', res);
        this.$Service.log(`网络搜索：users:${res.users&&res.users.length!==0&&JSON.stringify(res.users[0])}`)
        this.$Service.log(`网络搜索：groups:${res.groups&&res.groups.length}`)
        this.$Service.log(`网络搜索：users:${res.users&&res.users.length!==0&&JSON.stringify(res.users[0])}`)
        this.hasSearchResult = true;
        this.searchContactResult = _.forEach(res.users, (element, index) => {
          if (!element.thumbAvatar) return;
          let fileOperateParam = {
            filepath: element.thumbAvatar,
            type: 0
          }
          if (!this.$Service.file.fileOperate(fileOperateParam)) element.thumbAvatar = ''
        }) || [];
        this.searchGroupResult = _.forEach(res.groups, (element, index) => {
          if (!element.avatar) return;
          let fileOperateParam = {
            filepath: element.avatar,
            type: 0
          }
          if (!this.$Service.file.fileOperate(fileOperateParam)) element.avatar = ''
        })
        // this.searchContactResult = res.users || [];
        // this.searchAppResult = res.vtEntApp || [];
        this.searchAppResult = _.forEach(res.vtEntApp, (element, index) => {
          if (!element.appIcon) return;
          let fileOperateParam = {
            filepath: element.appIcon,
            type: 0
          }
          if (!this.$Service.file.fileOperate(fileOperateParam)) element.appIcon = ''
        }) || [];
      });
    },
    // 清空输入内容
    clearInput() {
      this.inputSearch = '';
      [this.isLoadingSearch, this.hasSearchResult] = [false, false];
    },
    /**
     * 关注公众号/添加好友
     */
    requestAddGroup(item, index) {
      if (index === 1) { // 应用号
        this.$set(item, 'tag', 1);
        this.$Service.contact.addContact({ userId: item.appID }, resp => {
          console.log('addAppAttention:', resp);
          this.$nextTick(() => {
            this.$set(item, 'relation', this.$t('search.followed'));
            this.$set(item, 'tag', null);
          })
        });
      } else if (index === 2){ // 好友
        if (!this.contact_contactList[item.id]) {
          this.$dialog.prompt({
            message: this.$t('search.verfication')+':',
            confirmText: this.$t('common.confirm'),
            cancelText: this.$t('common.cancel'),
            inputAttrs: {value: this.$t('search.iAm') + this.user_account.name, maxlength: 10},
            required: false, // 验证信息选填
            onConfirm: value => {
              let addContactParam = {userId: item.id,info: value};
              this.$Service.contact.addContact(addContactParam, resp=>{
                this.$Service.log(`添加好友请求：code:${resp.code},id:${item.id}`);
                if (resp.code !== 0) {
                  this.$toast.open({message: this.$t(`ErrorCode.${resp.code}`),type: 'is-danger'});
                } else {
                  this.$Service.contact.getVerifyType({userId: item.id}, resp => {
                    console.log('获取对方好友验证方式', resp)
                    // 1:need to verifiy 2:refuse to add 3:add
                    let verifyInfo = {
                      1: this.$t('groups.requestSent'),
                      3: this.$t('contacts.chatNow')
                    }
                    this.$toast.open({message: verifyInfo[resp.type], type: 'is-success'});
                  })
                }
              });
            }
          });
        } else {
          this.$emit('close');
          this.startChat(item, 1)
        }
      } else {
        if (!this.contact_groupList[item.groupId]) {
          this.$dialog.prompt({
            message: this.$t('search.verfication')+':',
            confirmText: this.$t('common.confirm'),
            cancelText: this.$t('common.cancel'),
            inputAttrs: {value: this.$t('search.iAm') + this.user_account.name, maxlength: 60},
            required: false, // 验证信息选填
            onConfirm: value => {
              let addGroupParam = {groupId: item.groupId,verify_info: value};
              this.$Service.group.addGroup(addGroupParam, resp=>{
                this.$Service.log(`添加群请求：code:${resp.code},id:${item.groupId}`);
                let toastMsg = {message: this.$t('groups.groupRequestSent'),type: 'is-success'}
                if (resp.code !== 0) {
                  toastMsg = {message: this.$t(`ErrorCode.${resp.code}`),type: 'is-danger'}
                }
                this.$toast.open(toastMsg);
              });
            }
          });
        } else {
          this.$emit('close');
          this.startChat(item, 2)
        }
      }
    },
    _updateSearchList({avatar, targetId}) {
      let isStopFind = false;
      _.forEach(this.searchContactResult, (element, index) => {
        if (targetId != element.id) return;
        this.isStopFind = true
        this.$set(element, 'updateAvatar', avatar)
      })
      if (isStopFind) return;
      _.forEach(this.searchAppResult, (element, index) => {
        if (targetId != element.appID) return;
        this.$set(element, 'updateAvatar', avatar)
      })
    }
  }
};
</script>
<style lang="scss">
@mixin commom-list {
  .search-find {
    display: flex;
    width: 80%;
    margin-top: 15px;
    .search-filed {
      position: relative;
      margin: 0 !important;
      .search-input {
        flex: 1;
        margin: 0 15px;
        .icon {
          pointer-events: all;
        }
      }
    }
    .search-button {
      width: 80px;
      box-shadow: $--box-shadow-lr;
      &:active{
        box-shadow: $--box-shadow-rd
      }
    }
  }
  .search-result {
    flex: 1;
    display: flex;
    align-items: center;
    justify-content: center;
    .result {
      display: flex;
      flex-direction: column;
      align-items: center;
      height: 100%;
      width: 100%;
      p {
        font-size: 12px;
        margin: 8px 0 0px 38px;
        width: 100%;
        color: get-grey-color(lighten-1);
      }
      .result-list {
        display: flex;
        width: 100%;
        overflow-y: auto;
        flex-wrap: wrap;
        justify-content: space-between;
        .v-divder {
          margin: 30px 16px 7px 16px;
          display: block;
          flex: 1 1 0px;
          max-width: 100%;
          height: 0px;
          max-height: 0px;
          border: solid;
          border-width: thin 0 0 0;
          transition: inherit;
          border-color: rgba(0,0,0,0.12);
        }
      }
    }
  }
}
.pc-search-list {
  height: 100%;
  @include commom-list;
  .search-result {
    height: calc(100% - 40px);
  }
}
</style>
