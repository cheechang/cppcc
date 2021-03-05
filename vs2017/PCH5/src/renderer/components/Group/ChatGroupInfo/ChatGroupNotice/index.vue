<template>
  <div class="chat-group-notice" :style="computedStyle">
    <div class="group-notice-publish" v-if="getIsAdmin">
      <v-button type="is-primary" class="notice-button theme-bgc_font" @click="isNoticeEdit=true" :ripple="false">{{ $t('groups.groupAnnouncement') }}</v-button>
    </div>
    <v-modal cardSize="notice-class" v-if="isNoticeEdit" @close="isNoticeEdit=false;editItem={}">
      <div class="notice-session">
        <notice-edit :id="id" :item="editItem" :noticeImg="noticeImg" @close="addNoticeItem"></notice-edit>
      </div>
    </v-modal>
    <div class="group-notice-list" :style="{'height': !getIsAdmin?'100%':'calc(100% - 42px)'}" @scroll.passive.stop="getGroupAnnMore" ref="noticeCard">
      <div v-for="(item, index) in computedNoticeList" class="group-notice-item" :key="index">
        <notice-item :id="id" :item="item" :index="index" :hasPermission="getIsAdmin" @edit-notice="openNoticeEdit" @delete-notice="deleteNoticeItem"></notice-item>
      </div>
    </div>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import NoticeItem from './NoticeItem';
import NoticeEdit from './NoticeEdit';
import contactMixin from '../../../Contact/ContactMixin';
import { getDateDiff } from '../../../../../comm/time.js'
import { converseFullPinYin } from '../../../../../comm/pinyin.js';
import { isWinXp } from '../../../../../comm/is';
export default {
  mixins: [contactMixin],
  props: {
    id: String
  },
  data() {
    return {
      isNoticeEdit: false,
      noticeList: {},
      editItem: {},
      scrollEnd: false,
      hasPermission: false,
      noticeImg: '',
      defaultBg: require('vrv-static/resources/images/common/default_bg.png'),
      announcement: {}
    }
  },
  watch:{
    contact_groupNotice(group){
     // console.log('========>value',group)
      if(group.info.groupId == this.id){
        let GroupAnnounce = {
          'announce':group.bulletin,
          'name':''
        }
        this.$set(this.announcement,'content',GroupAnnounce)
      }
    }
  },
  computed: {
    ...mapGetters(['user_account', 'chat_objectInfo','contact_groupNotice']),
    computedStyle() {
      if (!this.announcement||Object.keys(this.announcement).length==0) {
        console.log('no notice...')
        return {
          background: `url(${this.defaultBg}) 50% 40% no-repeat rgba(255, 255, 255, 0)`,
          'background-size': '200px'
        }
      }
      console.log('has notice...')
      return {}
    },
    computedNoticeList() {
      console.log('this.noticeList',this.noticeList)
      setTimeout(()=>{
        // return _.orderBy(this.noticeList, 'announcementID', ['desc'])
        this.$Service.group.getGroupInfo({ groupId: this.id }, resp =>{
        console.log('群信息',resp)
        let Announce = resp.bulletin
        console.log('群公告',Announce)
        if(Announce === ''){
          return
        }
        let GroupAnnounce = {
          'announce':Announce,
          'name':this.user_account.name
        }
        this.$set(this.announcement,'content',GroupAnnounce)
        console.log('announcement',this.announcement)
      })
      },100)
        return this.announcement
    },

    getIsAdmin() {
      let selfInfo = this.chat_objectInfo[this.id][this.user_account.userId]
      return selfInfo.memberType==2||selfInfo.memberType==3
    }
  },
  components: {
    NoticeItem,
    NoticeEdit
  },
  created() {
    /**
     * 公告页面实时更新
     */
    
    console.log('user_account',this.user_account,this.chat_objectInfo)
     
    this.$signalMonitor.$on('sendGroupNotice', resp => {
      console.log('noticeMsg resp:', resp);
      if (resp.fromId !== this.user_account.userId) {
        this.getGroupAnnouncementList(true);
      }
    })
    this.getGroupAnnouncementList();
  },
  beforeDestroy() {
    this.$signalMonitor.$off('sendGroupNotice');
    console.log('beforeDestroy ChatGroupNotice.vue');
  },
  beforeDestroy() {
    this.$signalMonitor.$off('sendGroupNotice');
    console.log('beforeDestroy ChatGroupNotice.vue');
  },
  methods: {
    openNoticeEdit(item, noticeImg) {
      this.isNoticeEdit = true
      this.editItem = item
      this.noticeImg = noticeImg
      console.log('item--open', item)
    },
    addNoticeItem(item) {
      console.log('item--add', item)
      this.isNoticeEdit = false;
      this.editItem = {};
      if(!item) return
      let newItem = Object.values(this.noticeList)[Object.keys(this.noticeList).length - 1]
      item.announcementID = (newItem && newItem.announcementID + 1)||0
      this.$set(this.noticeList, item.announcementID, item)
    },
    deleteNoticeItem(item) {
      console.log('item::::',item)
      console.log('result',this.announcement)
      this.$delete(this.announcement,this.announcement.content)
      // let deleteNoticeParam = {
      //   groupId: this.id,
      //   announcementId: item.announcementID
      // }
      // this.$Service.group.delGroupAnnouncement(deleteNoticeParam, resp => {
      //   console.log('resp::::', resp)
      //   resp.code===0&&this.$delete(this.noticeList, item.announcementID)
      // })
    },
    getGroupAnnMore() {
      this.$nextTick(() => {
        if(this.isScrollToBottom(this.$refs.noticeCard)) {
          if (this.scrollEnd) return;
          this.getGroupAnnouncementList();
        }
      });
    },
    /**
     * 获取群公告列表
     */
    getGroupAnnouncementList(update = false) {
      let lastSourceID = 0
      if (!update) {
        if (Object.keys(this.noticeList).length>0){
          lastSourceID = Object.keys(this.noticeList)[0]
          console.log('lastSourceID::::', lastSourceID)
        }
      }
      let groupAnnouncementParam = {
        groupID: this.id,
        lastSourceID: lastSourceID,
        userID: this.user_account.userId,
        pageSize: 1
      }
      console.log('groupAnnouncementParam::::', groupAnnouncementParam)
      let _handleNoticeList = resp => {
        console.log('resp::::', resp)
        this.scrollEnd = false;
        // this.noticeList = {}
        if (resp.list && resp.list.length > 0) {
          if (resp.list.length < 10) {
            this.scrollEnd = true
          }
          _.forEach(resp.list, element => {
            if (!this.chat_objectInfo[this.id][element.createUserID]) {
              this.$Service.search.getUserInfo({ userId: element.createUserID }, resp=>{
                this.$set(element, 'publisher', resp.users.name)
              });
            } else {
              this.$set(element, 'publisher', this.chat_objectInfo[this.id][element.createUserID].remark)
            }
            this.$set(element, 'time', getDateDiff(parseInt(element.createDt)))
            this.$set(this.noticeList, element.announcementID, element)
          })
        } else {
          this.scrollEnd = true
        }
      }
      this.$Service.group._group.getGroupAnnouncementList(groupAnnouncementParam, _handleNoticeList)
    },
    // getNewAnn() {
    //   let groupAnnouncementParam = {
    //     groupID: this.id,
    //     lastSourceID: 0,
    //     userID: this.user_account.userId,
    //     pageSize: 1
    //   };
    //   console.log('获取新的公告');
    //   console.log('groupAnnouncementParam::::', groupAnnouncementParam);
    //   let _handleNoticeList = resp => {
    //     console.log('resp::::', resp);
    //     _.forEach(resp.list, element => {
    //       if (!this.chat_objectInfo[this.id][element.createUserID]) {
    //         this.$Service.search.getUserInfo({ userId: element.createUserID }, resp=>{
    //           this.$set(element, 'publisher', resp.users.name);
    //         });
    //       } else {
    //         this.$set(element, 'publisher', this.chat_objectInfo[this.id][element.createUserID].remark);
    //       }
    //       this.$set(element, 'time', getDateDiff(parseInt(element.createDt)));
    //       this.$set(this.noticeList, element.announcementID, element);
    //     })
    //   }
    //   this.$Service.group.getGroupAnnouncementList(groupAnnouncementParam, _handleNoticeList);
    // }
  }
}
</script>
<style lang="scss">
.chat-group-notice {
  // height: calc(100vh - 42px);
  flex:1;
  display: flex;
  flex-direction: column;
  // flex: 1;
  .notice-class {
    width: 640px;
    height: 320px;
    border-radius: $--border-radius-base;
    overflow: hidden;
    background: #ffffff;
    .modal-card-body {
      padding: 15px 20px !important;
      width: auto;
      z-index: 1;
      position: relative;
      .notice-session {
        height: 100%;
      }
    }
  }
  .group-notice-publish {
    margin: 5px 17px;
    display: flex;
    justify-content: flex-end;
    .notice-button {
      font-size: 14px;
    }
  }
  .group-notice-list {
    // background: #EAF1F8;
    overflow: auto;
    .group-notice-item {
      // box-shadow: 0 0 10px 0 rgba(101, 111, 122, 0.5);
      margin: 10px;
    }
  }
}
</style>
