<template>
  <div class="msg-record-select-member">
    <v-modal @close="cancelSelect">
      <!-- 添加background覆盖modal，避免添加/邀请群成员loading时可以进行其他操作 -->
      <!-- <div class="group-background" v-if="isLoading"></div> -->
      <div class="msg-record-group-member">
        <div class="msg-record-group-member-left">
          <p class="group-title">{{currentTitle}}</p>
          <v-input class="search-input" v-model="inputSearch" :placeholder="$t('groups.search')" size="is-small" :position="inputSearch==''?'left':'right'" :maxlength ="24" @input="searchFromLocal"  @keydown="$emit('keyDown', $event)" >
            <i v-if="inputSearch==''" class="icon search-icon" slot="expand">&#xe68c;</i>
            <i v-else class="icon" slot="expand" @click="clearInput">&#xe650;</i>
          </v-input>

          <transition name="slide-up">
            <div class="create-contact-list" ref="contactlist" @scroll.passive.stop="loadMoreData">
              <v-card-list>
                <v-card v-for="(item,index) in optionalList" :key="index" :title="item.name||item.remark||item.groupName" @click="changeItemState(item)">
                  <v-avatar size='is-small' :src='item.thumbAvatar||item.avatar' :sex="getSex(item)" :offline="false" shape="round"  slot="leftAvatar"></v-avatar>
                  <v-avatar slot="after" class="avatar-bg" :offline="false" shape="round" :src="isSelectItem(item,true)"/>
                </v-card>
              </v-card-list>
            </div>
          </transition>
          <slot name="localSearch"></slot>
        </div>
        <div class="msg-record-group-member-right">
          <i class="icon close-modal" @click="$emit('close')">&#xe603;</i>
          <div class="member-list-area">
            <div class="member-list-title">{{getSelectedNum()}}</div>
            <div class="member-list">
              <tag class="select-item" v-for="(item,index) in selectedList" :key="index" :text="item.name||item.remark" color="#e0e0e0" @closetag="changeItemState(item)"  :closable='true'>
                <v-avatar class="avatar-bg" size='is-small' :sex="getSex(item)" :offline="false" shape="round" :src="item.thumbAvatar"/>
              </tag>
               <!-- <input class="leave-message" v-model="leaveMsg" v-if='isShowMsgBox' :maxlength="3000" placeholder="给对方留言" /> -->
            </div>
          </div>
        
          <div class="modal-card-footer" slot="footer-bottom">
              <v-button :type="`is-primary`" :ripple="false" :disable="selectMemberIds.length==0"  @click.self="handleFilter">{{$t('common.confirm')}}</v-button>
            <v-button  @click="cancelSelect">{{$t('common.cancel')}}</v-button>
          </div>
        </div>
      </div>
    </v-modal>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import ContactMixin from '../../Contact/ContactMixin';
import tag from '../ChatContent/tag.vue'
export default {
  mixins: [ContactMixin],
  data() {
    return {
      // isLoading: false,
      noneImg: require('vrv-static/resources/images/contact/groupChooseNone.png'),
      selectImg: require('vrv-static/resources/images/contact/groupChooseSelect.png'),
      deleteImg: require('vrv-static/resources/images/contact/groupChooseDelete.png'),
      manDefault: require('vrv-static/resources/images/contact/manDefault.png'),
      // memberCount: 0,
      currentTitle: this.$t('chat.selectSender'),
      groupName: '',
      inputSearch: '',
      currentLoadList:[],
      initLength: 10,
      totalLength: 0,
      // searchContactResult: [],
      leaveMsg: ''
    };
  },
  components: {
    tag
  },
  props: {
    // isInviteMember: true,
    userInfo: Map | Function,
    selectMemberIds: Array,
    memberList: Array,
    searchContactResult:  Array,
    isShowMsgBox: {
      type: Boolean,
      default: false
    },
    memberCount: {
      type: Number,
      default: 0
    },
    localSearchList: Map | Function,
  },
  computed: {
    ...mapGetters(['contact_contactList', 'user_account']),
    // buttonType() {
    //   return this.isLoading ? 'is-loading' : '';
    // },
    /** 左侧可选列表 */
    optionalList() {
      if (this.searchContactResult.length > 0) {
        return this.searchContactResult
      }
      // let totalList = _.orderBy(this.userInfo, ["pinyin"], ["asc"])
      this.totalLength = this.memberList.length
      return this.memberList.slice(0, this.initLength);
    },
    /** 右侧已选中列表 */
    selectedList() {
      let selectedList = []
      console.log('user', this.userInfo)
      console.log('this.selectMemberIds', this.selectMemberIds)
      this.selectMemberIds.forEach(id => {
        if (this.userInfo && this.userInfo[id]) {
          selectedList.push(this.userInfo[id])
        } else {
          if (this.localSearchList && this.localSearchList[id]) {
            console.log('this.localSearchList[id]', this.localSearchList[id])
            selectedList.push(this.localSearchList[id])
          }
        }
      })
      return selectedList
    }
  },
  created() {
    console.log('selectMemberIds', this.selectMemberIds)
    // this.memberCount = this.selectMemberIds.length
  },
  watch: {
    inputSearch() {
      if (this.inputSearch !== '') return;
      // this.searchContactResult = [];
      this.$emit('clearSearchList')
    }
  },
  methods: {
    getSex(item) {
      console.log('getSex', item)
      console.log(item.gender || item.chatType== 1 ? 0 : item.chatType == 2 ? 4 : 3)
      if (item.chatType === undefined && item.gender !== undefined) {
        return item.gender
      } else {
        return item.chatType== 1 ? 0 : item.chatType == 2 ? 4 : 3
      }
    
    },
    cancelSelect() {
      this.$emit('clearSelected')
      this.$emit('close')
    },

    handleFilter() {
      console.log('handleFilter::')
      this.$emit('completeSelect', this.leaveMsg)
      this.$emit('close')
    },
    /**
     * 滚动加载更多：避免数据量过大造成的加载卡顿
     */
    loadMoreData() {
      if (this.isScrollToBottom(this.$refs.contactlist)) {
        if (this.initLength >= this.totalLength) {
          console.log('init more')
          return
        };
        let num = 20;
        if (this.initLength + num > this.totalLength) {
          num = this.totalLength - this.initLength;
        }
        this.initLength += num;
        console.log("this.initLength", this.initLength);
      }
    },
    /**
     * 显示联系人的选中状态：默认/选中/删除按钮
     * @param {Object} id- 用户id
     * @param {Boolean} isLeft- 左侧/右侧默认选中状态不同
     */
    isSelectItem({ id, groupId, appId}, isLeft) {
      let selectId = id|| groupId|| appId
      return isLeft
        ? this.selectMemberIds.indexOf(selectId) > -1
          ? this.selectImg
          : this.noneImg
        : this.deleteImg;
    },
    getSelectedNum() {
      // return `已经选择 ${this.memberCount} 个联系人`;
      return this.$t('groups.selectedFriend', {value:this.selectMemberIds.length})
    },

    /**
     * 改变选中状态 && 添加删除
     * @param {Object} id- 选中item对应的用户id
     */
    changeItemState({ id, groupId }) {
      console.log('id::', id)
      let userId = id || groupId || appId
      // if (id === this.preSelectMemberIds) return;
      if (this.selectMemberIds.indexOf(userId) > -1) {
        this.selectMemberIds.forEach((element, i) => {
          id === element && this.$emit('handleSelectMemberIds', {type: 2, id: i})
        });
      } else {
        if (this.selectMemberIds.length > 4) {
          return  this.$dialog.alert({message: '选择用户超出上限', confirmText: this.$t('common.sure'), onConfirm: () => {}});
        }
        console.log('handleSelectMemberIds', userId)
        this.$emit('handleSelectMemberIds', {type: 1, id: userId})
      }
      // this.memberCount = this.selectMemberIds.length;
    },
    /**
     * 群成员-本地搜索
     */
    searchFromLocal(value) {
      if (!value.trim()) {
        // this.searchContactResult = []
        this.$emit('clearSearchList')
        return
      };
      this.$emit('search', value)
      // let groupSearchMemberParam = {
      //   groupId:this.$route.query.id,
      //   key:value
      // }
      // this.$Service.search.groupSearchMember(groupSearchMemberParam, resp=>{
      //   console.log('groupSearchMember::', resp)
      //   if(!resp.members){
      //     return 
      //   }
      //   this.searchContactResult = resp.members
      // })
    },
    /**
     * 清空本地搜索输入内容
     */
    clearInput() {
      this.inputSearch = '';
      this.$emit('clearSearchList')
      // this.searchContactResult = []
    }
  }
};
</script>
<style lang="scss">
.msg-record-select-member {
  width: 466px;
  .group-background {
    width: 100%;
    height: 100%;
    position: absolute;
    z-index: 9;
  }
  .msg-record-group-member {
    display: flex;
    .msg-record-group-member-left {
      width: 233px;
      flex: 1;
      .group-title {
        margin: 5px 0px 0px 10px;
        color: $--color-black;
      }
      .search-input {
        margin-left: 10px;
        margin-top: 15px;
        margin-right: 23px;
        .is-small {
          border-radius: $--border-radius-large;
        }
        .icon {
          pointer-events: all;
          height: 30px;
        }
      }
      .create-contact-list {
        height: 419px;
        margin-right: 10px;
        margin-top: 10px;
        overflow-x: hidden;
        .avatar-bg {
          width: 20px;
          height: 20px;
        }
      }
      .list-title {
        background: #eef4fd;
        font-size: 13px;
        color: $--color-black;
        height: 24px;
        width: 100%;
      }

      .msg-record-search-result-list{
        margin-top: 10px;
        //margin-right: 10px;
        overflow-y: auto;
        overflow-x: hidden;
        // height: 446px;
        height: 300px;
        .msg-record-search-background{
          width: 150px;
          height: 150px;
          background: url('~vrv-static/resources/images/common/nocontent.png') no-repeat #fff;
          margin-left: 37px;
          margin-top: 100px;
          background-size: contain;
        }
        .msg-record-search-lable{
          font-size: 12px;
          background: #dcdcdc;
          padding-left: 5px;
          padding-top: 3px;
          color: #000;
          height: 25px
        }
        .msg-record-result-list{
          .avatar-bg {
            width: 20px;
            height: 20px;
          }
        }
      }
    }
    .msg-record-group-member-right {
      width: 233px;
      flex: 1;
      display: flex;
      flex-direction: column;
      .member-list-area {
        width: 100%;
        flex: 1;
        padding-top: 44px;
        .member-list-title {
          width: 100%;
          height: 32px;
          font-size: 15px;
          display: flex;
          align-items: center;
        }
        .member-list {
          overflow-x: hidden;
          width: 100%;
          height: 350px;
          position: relative;
          .leave-message {
            border: none;
            height: 50px;
            width: 220px;
            outline: 0;
            position: absolute;
            bottom: 0px;
            left: 0px;
            border-top: solid 1px #ccc;
          }
          .select-item {
            margin: 4px;
            .v-chip__text {
              margin-left: 25px;
            }
            .avatar-bg {
              width: 20px;
              height: 20px;
              position: absolute;
           }
           .v-chip__close {
             font-size: 13px;
           }
          }
          
        }
      }
      .modal-card-footer {
          height: 40px;
          display: flex;
          align-items: center;
          justify-content: flex-end;
        .button {
          font-size: 14px;
          border-radius: $--border-radius-large;
          width: 70px;
          height: 28px;
        }
      }
      .msg-record-group-member-name {
        width: 100%;
        height: 30px;
        align-items: center;
        margin-top: 43px;
        display: flex;
        flex: 1;
        color: $--color-black;
        @include ellipsis;
        .input {
          font-size: 13px;
          height: 30px;
          margin-left: 5px;
          padding-right: 0px;
        }
      }
      .close-modal {
        display: flex;
        @include get-grey-color(darken-1);
        font-size: 12px;
        width: 30px;
        height: 30px;
        right: 0px;
        top: 0px;
        position: absolute;
        &:hover {
          background: #8f91b7;
        }
      }
    }
  }
  .modal-card {
    width: 466px;
    border-radius: $--border-radius-base;
  }
}
</style>
