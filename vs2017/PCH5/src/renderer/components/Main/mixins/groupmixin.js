/**
 * @file      Manages the group's infomation for the main page.
 * @author    linpeiyuan <linpeiyuan@vrvmail.com.cn>
 * @date      2019.9.24
 * @copyright Beijing VRV Software Co.,Ltd
 * 
 * @mixin
 */ 
import {versionCompirePro} from '../../../utils/utils.js';
const mixin = {
  methods: {
    /**
     * @breif 特殊情况下，根据用户是否在北信源西安分公司内判断是否升级西安版本
     */
    checkSpecialUpdateFromLocal({groups}) {
      _.forEach(groups, groupItem => {
        // 北信源西安分公司群
        if (groupItem.groupId !== '4336927693') return;
        // 正在升级中则不再检测
        let updateModal = document.getElementsByClassName('updater-modal')[0]
        console.log('updateModal:::::::::', updateModal)
        if (updateModal&&updateModal.length !== 0) return;
        this.$nextTick(() => {
          this.$signalMonitor.$emit('check-for-update')
        })
      })
    },
    /**
     * @breif 群相关通知回调注册
     * 
     * @todo 可以移至导航栏对应通讯录模块
     */
    regGroupNotify() {
      this.regGroupHeadImgUpdateCb();
      this.regGroupListCb();
      this.regTransferGroupCb();
      this.regGroupRefreshCb();
      if (versionCompirePro(this.$pkg.version, '4.6') !== 0) {
        this.regGetGrpMemListCb();
      }
    },

    /**
     * @breif 群头像更新推送
     */
    regGroupHeadImgUpdateCb() {
      this.$Service.group.regGroupHeadImgUpdateCb(null, resp => {
        this.$store.dispatch('UPDATE_GROUP_AVATARS', resp);
      });
    },

    /**
     * @breif 群成员头像更新推送
     */
    regMemberHeadImgUpdateCb() {

    },

    /**
     * @breif 群列表推送
     */
    regGroupListCb() {
      this.$Service.group.regGroupListCb(null, resp => {
        console.log('regGroupListCb::::', resp)
        if (resp.groups.length === 0) {
          return;
        }
        this.$store.dispatch('SET_GROUPLISTS', resp);
      });
      
    },

    /**
     * @breif 群主更新推送
     */
    regTransferGroupCb() {
      this.$Service.group.regTransferGroupCb(null, resp => {
        this.$store.commit('UPDATE_GROUP_CREATERID', resp);
        this.$store.commit('UPDATE_MEMBER_TYPE', resp);
      });
    },

    /**
     * @breif 群信息更新推送
     */
    regGroupRefreshCb() {
      this.$Service.group.regGroupRefreshCb(null, this._regGroupRefreshCbHandler);
    },
    _regGroupRefreshCbHandler(resp) {
      //  处理群头像更新
      let avatar = resp.group.info.avatar;
      resp.group.info.avatar = (avatar !== '') && this.$fs.existsSync(avatar) ? avatar : '';
      console.log('_regGroupRefreshCbHandler',resp)
      this.$store.commit('CHAT_GROUP_CHANGE', resp);
      this.$store.commit('CHANGE_GROUP_INFO', resp);
      if(resp.operType === 2){
        this.$store.commit('SET_GROUP_NOTICE_CHANGED', resp.group);
      }
      //  如果是更新，则更新对应的扩展信息
      let extend = resp.group.extend && JSON.parse(resp.group.extend);
      let extendInfo = {
        burnMsg: extend.isSelfDestruct || '0',
        privateMsg: extend.privateMsg || '0',
        disallowStrangerChat: extend.disallowStrangerChat || '0'
      };
      this.$store.dispatch('SET_GROUP_EXTENSIONS', {id: resp.group.info.groupId, extendInfo: extendInfo});
      // 更新vuex 群可搜索状态
      this.$store.commit('SET_GROUPSEARCHING', {id: resp.group.info.groupId, status: resp.group.isSearch});

      //  如果是删除操作则更新对应会话的信息
      if (![31, 32, 33].includes(resp.operType)) {
        return;
      }
      if (this.chat_chatContent[resp.group.info.groupId]) {
        this.$store.commit('DEL_CHATCONTENT_BYID', resp.group.info.groupId);
        this.$store.commit('DEL_CHAT_OBJECT', resp.group.info.groupId);
      }

      if (!this.$route.query || this.$route.query.id !== resp.group.info.groupId ) {
        return;
      }

      const routepath = {
        '/ChatRightArea': '/Chat',
        '/GroupInfo': '/Contact'
      };
      if (!routepath.hasOwnProperty(this.$route.path)) {
        return;
      }
      this.$router.push(routepath[this.$route.path]);
    },

    /**
     * @breif 群成员数据同步结束后推送（主动拉取群成员数据如果已同步则不推送），类似图片下载完成后推送更新
     */
    regGetGrpMemListCb() {
      this.$Service.group.regGetGrpMemListCb(null, resp => {
        if (!resp.members.length) {
          return;
        }
        this.$store.dispatch('UPDATA_CHAT_OBJECT', {
          /**
           * resp.members是二维数组
           * resp.members[0][0] : group member id
           * resp.members[0][1] : group member info
           */
          id: resp.members[0][1].groupId,
          chatObject: resp.members
        });
      });
    },

    /**
     * @breif 获取群列表
     */
    getGroupList() {
      this.$Service.group.getGroupList(null).then(resp => {
      // this.$Service.group.getGroupList(null, resp => {
        if (!resp.groups || resp.groups.length <= 0) {
          this.$Service.log('group.getGroupList failed');
          return;
        }
        this.$Service.log(`主动拉取群列表: length:${resp.groups.length}\n lastGroup:${JSON.stringify(resp.groups[resp.groups.length - 1])}`);
        this.$store.dispatch('SET_GROUPLISTS', resp);
        // 登录触发预登录升级推送，导致这里不升级
        this.checkSpecialUpdateFromLocal(resp)
      });
    }
  },
};

export default mixin;