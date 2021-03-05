<template>
  <d-skeleton>
    <div v-if="isLoadFinished" class="group-tab-item" ref="groups" @scroll.passive.stop="loadMoreData" :data-type="groupList">
    <v-card-list class="contact-item" @menuClick="groupMenuClick" :menuList="groupMenu">
      <div class='hidden-vip-item'>
        <p class="sup-title theme-left-splitBar" v-if="vipGroupList.length!=0">{{ $t('groups.vip') }}</p>
        <v-card class="card-item theme-list-items" :isSecondBreakpoint="true" v-for="item in vipGroupList" :key="'v'+item.groupId" :title="item.groupName" :index="'v'+item.groupId" @contextmenu="setGroupMenu(item)" @click="openDetail(1,item,'v'+item.groupId)" @dbClick="startChat(item, 2)" debounced>
          <v-avatar size='is-small' :title="item.groupName" :src='item.avatar' :sex="4" :offline="false" shape="round"  slot="leftAvatar"></v-avatar>
          <img src="../../../../../vrv-static/resources/images/contact/yi.png" class="img-eidOrOrg" v-if="item.isEid">
          <img src="../../../../../vrv-static/resources/images/contact/zuzhi.png" class="img-eidOrOrg" v-if="item.isOrg">
          <i slot="after" class="icon leader-icon" v-if="user_account.userId == item.createrId">&#xe748;</i>
        </v-card>
      </div>
      <p class="sup-title theme-left-splitBar" v-if="groupList.length!=0">{{ $t('groups.group') }}</p>
      <v-card class="card-item theme-list-items" :isSecondBreakpoint="true" v-for="item in groupList" :key="item.groupId" :title="item.groupName" :index="item.groupId" @contextmenu="setGroupMenu(item)" @click="openDetail(1,item,item.groupId)" @dbClick="startChat(item, 2)" debounced>
        <v-avatar size='is-small' :title="item.groupName" :src='item.avatar' :sex="4" :offline="false" shape="round"  slot="leftAvatar"></v-avatar>
        <img src="../../../../../vrv-static/resources/images/contact/yi.png" class="img-eidOrOrg" v-if="item.isEid">
        <img src="../../../../../vrv-static/resources/images/contact/zuzhi.png" class="img-eidOrOrg" v-if="item.isOrg">
        <i slot="after" class="icon leader-icon" v-if="user_account.userId == item.createrId">&#xe748;</i>
      </v-card>
    </v-card-list>
    </div>
    <contact-skeleton slot="skeleton" type="contact"></contact-skeleton>
  </d-skeleton>
</template>
<script>
import mixin from '../ContactMixin.js';
import GroupMixin from '../../Group/GroupMixin';
import { mapGetters } from 'vuex';
import { converseFullPinYin } from '../../../../comm/pinyin.js';
import ContactSkeleton from './ContactSkeleton';

export default {
  data() {
    return {
      updateGroupList: [],
      groupMenu: [],
      initLength: 20,
      isLoadFinished: false,
      isEid:false,
      isOrg:false
    }
  },
  mixins: [mixin, GroupMixin],
  components: {
    ContactSkeleton
  },
  computed: {
    ...mapGetters(['contact_groupList']),
    groupList() {
      this.updateGroupList = _.orderBy(
        _.filter(this.contact_groupList,e=>e.groupId),
        val => {
          return converseFullPinYin(val.pinyin.trim());
        },
        ['asc']
      )
      console.log(this.updateGroupList.slice(0, this.initLength))
      this.updateGroupList.slice(0, this.initLength).forEach(element => {
       console.log(element.groupType) 
       if(element.groupType === 'eid'){
         this.$set(element,'isEid',true)
         this.$set(element,'isOrg',false)
       }else if(element.groupType === 'org'){
         this.$set(element,'isOrg',true)
         this.$set(element,'isEid',false)
       }else{
         this.$set(element,'isOrg',false)
         this.$set(element,'isEid',false)
       }
      });
      return this.updateGroupList.slice(0, this.initLength)
    },
    vipGroupList() {
      if (this.updateGroupList.length===0) return [];
      return this.updateGroupList.filter(e=>e.isVSign);
    }
  },
  created() {
    setTimeout(() => {
      this.isLoadFinished = true;
    }, 800);
  },
  methods: {
    loadMoreData() {
      this.$nextTick(() => {
        if (this.isScrollToBottom(this.$refs.groups))
          if (this.initLength < this.updateGroupList.length) {
            //是否有更多数据
            if (this.updateGroupList.length - this.initLength < 30) {
              this.initLength = this.updateGroupList.length;
            } else {
              this.initLength += 20;
            }
          }
      })
    },
    /**
     * 是否展示列表分组后的title
     * @param {Number} type - 0:V标好友 1:好友
     */
    isShowTitle({type}) {
      return this.updateGroupList.filter(e => type!==0||e.isVSign).length>0;
    },
    /**
     * 判断是否是群主
     */
    isGroupLeader(id) {
      return this.user_account.userId == this.contact_groupList[id].createrId
    },
    /**
     * 设置右键菜单内容
     * @param {Object} [canExit=true] - 该群是否允许退出
     */
    setGroupMenu(item) {
      console.log("item:::::::",item)
      this.groupMenu = [];
      if(!item.isVSign) this.groupMenu.push(this.$t('groups.addVip'));
      else this.groupMenu.push(this.$t('groups.removeVip'));
      // if(!item.canExit) return;
        console.log('item.group',item.groupType)
        if(item.groupType !== 'eid' && item.groupType !== 'org'){
        if(!this.isGroupLeader(item.groupId)) this.groupMenu.push(this.$t('groups.leave'));
        else this.groupMenu.push(this.$t('groups.disband'));
      }
    },
    /**
     * 群右键菜单点击
     * @param[in] menuName: 右键菜单内容
     * @param[in] menuIndex: 右键菜单对应的index
     * @param[in] itemId: 右键选中项的群Id
     */
    groupMenuClick(menuName, menuIndex, itemId) {
      if(itemId.includes('v')) {
        itemId = itemId.replace('v', '');
      }
      if (menuIndex === 0) { //设置V标群
        this.setVipGroup(itemId);
      } else if(menuIndex === 1) { //退出
        this.disbandGroup(itemId)
      }
    },
    setVipGroup(id) {
      let isVSign = this.contact_groupList[id].isVSign;
      let info = {groupId:id, vSign:!isVSign};
      this.$Service.group.setGroupExtraInfo(info,resp=>{
        console.log('设置V标群回调：' + JSON.stringify(resp));
        if (resp.code !== 0) {
          let errorInfo = this.$t(`ErrorCode.${resp.code}`);
          this.$toast.open({message: this.$t('groups.addVip') + ':' + errorInfo, type: 'is-danger'});
        }
      })
    },
    /**
     * 解散/退出群
     * @param {String} itemId - 群Id
     */
    disbandGroup(itemId) {
      let isOwner = this.isGroupLeader(itemId); // 群主(y)/成员(n)
      this.$dialog.confirm({
        message: isOwner 
          ? this.$t('groups.toDisband', {value: this.contact_groupList[itemId].groupName})
          : this.$t('groups.toLeave', {value: this.contact_groupList[itemId].groupName}),
        confirmText: isOwner ? this.$t('groups.disband') : this.$t('groups.leave'),
        cancelText: this.$t('common.cancel'),
        onConfirm: () => {
          let removeGroupParam = { groupId: itemId, type: isOwner ? 1 : 2 }
          this.$Service.group.removeGroup(removeGroupParam, resp => {
            console.log('removeGroup', resp)
            if (resp.code !== 0) {
              let errorInfo = this.$t(`ErrorCode.${resp.code}`)
              this.$toast.open({
                message: `${isOwner ? this.$t('groups.disband') : this.$t('groups.leave')}${this.$t('groups.group')}：` + errorInfo,
                type: 'is-danger'
              })
            }else{
              this.deleteGroupLocalTone(removeGroupParam.groupId);
            }
          })
        }
      })
    }
  }
}
</script>
<style lang="scss">
.group-tab-item {
  flex: 1;
  width: 100%;
  height: 100%;
  overflow-y: hidden;
  .contact-item {
    .card-item {
      .img-eidOrOrg{
        position: absolute;
        top: 28px;
        left: -25px;
        width: 16px;
        height: 16px;
      }
      .media-content {
        max-width: 147px;
      }
    }
  }
  &:hover {
    overflow-y: auto;
  }
  .sup-title {
    font-size: 14px;
    padding: 5px;
    font-weight: 700;
  }
  .leader-icon {
    color: gold;
  }
}
</style>
