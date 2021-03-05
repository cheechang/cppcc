import Vue from 'vue';
import {
  resolve
} from 'url';
const contact = {
  state: {
    /*
     * 联系人列表
     */
    ContactList: {},
    /**
     * 联系人在线状态
     */
    ContactOnlineState: {},
    /**
     * 联系人扩展信息集合
     */
    ContactExtension: {},
    /**
     * 联系人在线状态
     */
    ContactOnlineStateList: {},
    /**
     * 应用列表
     */
    AppContactList: {},
    /*
     * 群列表列表
     */
    GroupList: {},
    /**
     * 群扩展信息集合
     */
    GroupExtension: {},
        /**
     * 群可否被搜索状态
     */
    GroupSearchingList: {},
    /*
     * 组织列表-树结构
     */
    OrganizationList: [],
    /**
     * 组织架构结点
     */
    OrgIdList: [],
    /**
     * 组织架构字典id {组织结点(orgId) : 所属用户(Id)}
     */
    OrgUserToId: {},
    /**
     * 组织结构配置
     */
    OrgConfig: {},
    isInOrg: -1,
    /**
     * 企业号
     */
    EntAppList: {},
    /**
     * 后台配置的数据字典信息
     * map<dickey:value>
     */
    EnterpriseDicValues: {},
    /**
     * 隐藏的好友ID集合
     */
    HiddenContactIds: new Set(),
    /**
     * 群公告变更
     */
    GroupNoticeChanged:{}
  },
  mutations: {
    SET_GROUP_NOTICE_CHANGED:(state,data) =>{
      state.GroupNoticeChanged = data;
    },
    /**
     * 注销后清空联系人、群数据
     */
    CLEAR_CONTACT_DATA: (state) => {
      state.ContactList = {};
      state.GroupList = {};
      state.AppContactList = {};
      state.EntAppList = {};
      state.OrganizationList = [];
      state.OrgIdList = [];
      state.OrgUserToId = {};
      state.ContactExtension = {};
      state.ContactOnlineStateList = {};
      state.isInOrg = -1;
      state.HiddenContactIds = new Set();
    },
    /**
     * 添加联系人
     */
    SET_CONTACTLIST: (state, element) => {
      // _.forEach(resp.contacts, (element, i) => {
        if (element.isHidden === 1) 
          state.HiddenContactIds.add(element.id)
        else if (element.isApp === 2)
          Vue.set(state.ContactList, element.id, element);
        else
          Vue.set(state.AppContactList, element.id, element);
      // });
    },
    /**
     * 添加联系人在线状态和设备
     */
    SET_CONTACTS_STATE: (state, resp) => {
      Vue.set(state.ContactOnlineStateList, resp.userID, resp);
    },
    /**
     * 修改联系人在线状态
     */
    UPDATE_CONTACT_ONLINE: (state, resp) => {
      if (!state.ContactOnlineStateList[resp.userID]) return;
      Vue.set(state.ContactOnlineStateList[resp.userID], 'flag', resp.flag);
      Vue.set(state.ContactOnlineStateList[resp.userID], 'deviceType', resp.deviceType);
    },
    /**
     * 更新联系人头像
     */
    UPDATE_CONTACTS_AVATAR: (state, resp) => {
      // if (resp.targetId in state.ContactList)
      // Vue.set(state.ContactList[resp.targetId], 'avatar', resp.imgPath);
      _.values(state.ContactList).find((element, i) => {
        if (element.id !== resp.targetId) return;
        Vue.set(element, 'thumbAvatar', resp.avatar);
        Vue.delete(state.ContactList, element.id);
        Vue.set(state.ContactList, element.id, element);
      });
    },
    /**
     * 联系人增删改操作
     */
    CHANGE_CONTACT_INFO: (state, { flag, contact }) => {
      if (contact.isHidden === 1) {
        state.HiddenContactIds.add(element.id)
      }
      if (contact.isApp===2) {
        switch (flag) {
          case 1: // 增加此项
            {
              Vue.set(state.ContactList, contact.id, contact);
              break;
            }
          case 2: // 修改此项
            {
              Vue.delete(state.ContactList, contact.id);
              Vue.set(state.ContactList, contact.id, contact);
              break;
            }
          case 3: // 删除此项
            {
              Vue.delete(state.ContactList, contact.id);
              break;
            }
        }
      } else
        Vue.set(state.AppContactList, contact.id, contact);
    },
    /**
     * 添加群
     */
    SET_GROUPLIST: (state, element) => {
      Vue.set(state.GroupList, element.groupId, element);
    },
    /**
     * 更新群列表头像
     */
    UPDATE_GROUP_AVATAR: (state, resp) => {
      _.forEach(_.values(state.GroupList), (element, i) => {
        if (element.groupId !== resp.targetId) return;
        Vue.set(element, 'avatar', resp.img);
        Vue.delete(state.GroupList, element.groupId);
        Vue.set(state.GroupList, element.groupId, element);
      });
    },
    /**
     * 更新群主id
     */
    UPDATE_GROUP_CREATERID: (state, resp) => {
      Vue.set(state.GroupList[resp.groupId], 'createrId', resp.groupLeaderId);
      if (state.GroupList[-1]) Vue.delete(state.GroupList, -1);
      else Vue.set(state.GroupList, -1, {});
    },
    /**
     * 群增删改操作
     */
    CHANGE_GROUP_INFO: (state, data) => {
      switch (data.operType) {
        case 1: // 增加此项
          {
            Vue.set(state.GroupList, data.group.info.groupId, data.group.info);
            break;
          }
        case 2: // 修改此项
          {
            Vue.delete(state.GroupList, data.group.info.groupId);
            Vue.set(state.GroupList, data.group.info.groupId, data.group.info);
            break;
          }
        case 31: // 删除此项（解散）
          {
            Vue.delete(state.GroupList, data.group.info.groupId);
            break;
          }
        case 32: // 删除此项 (群主移除)
          {
            Vue.delete(state.GroupList, data.group.info.groupId);
            break;
          }
        case 33: // 删除此项 （退出）
          {
            Vue.delete(state.GroupList, data.group.info.groupId);
            break;
          }
      }
    },
    /**
     * 添加组织架构
     */
    SET_ORGANIZATON_LIST: (state, organization) => {
      state.OrganizationList = organization;
    },
    /**
     * 添加组织架构配置信息
     */
    SET_ORGANIZATON_CONFIG: (state, config) => {
      _.forEach(Object.keys(config), key => {
        Vue.set(state.OrgConfig, key, config[key])
      });
    },
    /**
     * 添加企业号
     */
    SET_ENTAPP_LIST: (state, resp) => {
      _.forEach(resp.EntAppinfos, element => {
        Vue.set(state.EntAppList, element.appID, element);
      });
    },
    /**
     * 删除公众号
     */
    DELETE_APPLSIT: (state, userId) => {
      Vue.delete(state.AppContactList, userId);
    },
    /**
     * 联系人扩展信息集合
     */
    SET_CONATCT_EXTENSION: (state, {id, data}) => {
      Vue.set(state.ContactExtension, id, data);
    },
    /**
     * 群扩展信息集合
     */
    SET_GROUP_EXTENSION: (state, {id, extendInfo}) => {
      Vue.set(state.GroupExtension, id, extendInfo);
    },
    /**
     * 群可否被搜索集合
     */
    SET_GROUPSEARCHING: (state, {id, status}) => {
      Vue.set(state.GroupSearchingList, id, status);
    },
    /**
     * 组织架构 部门（key）：成员（value）
     */
    SET_ORG_ONLINE_LIST: (state, {id, data}) => {
      let arr = []
      _.forEach(data, e => { arr.push(e.userID) });
      Vue.set(state.OrgUserToId, id, arr)
    },
    SET_ORGTAB_STATUS: (state, isInOrg) => {
      state.isInOrg = isInOrg
    },
    /**
     * 后台配置数据字典方法
     */
    SET_ENTDICVALUES: (state, values) => {
      _.forEach(values, item => {
        Vue.set(state.EnterpriseDicValues, item.dicKey, item.value);
      });
    },
    SET_ENTDICVALUE: (state, {dicKey, value}) => {
      Vue.set(state.EnterpriseDicValues, dicKey, value);
    }
  },
  actions: {
    UNITIZED_ACTIONS: (context, {key, value}) => {
      return new Promise(resolve=>{
        setTimeout(() => {
          context.commit(key, value);
          resolve();
        }, 0);
      })
    },
    SET_ENTAPP_LISTS: (context, resp) => {
      return new Promise(resolve => {
        setTimeout(() => {
          context.commit('SET_ENTAPP_LIST', resp);
          resolve();
        }, 0);
      });
    },
    SET_CONTACTS_STATES: (context, resp) => {
      return new Promise(resolve => {
        setTimeout(() => {
          context.commit('SET_CONTACTS_STATE', resp);
          resolve();
        }, 0);
      });
    },
    UPDATE_CONTACT_ONLINES: (context, resp) => {
      return new Promise(resolve => {
        setTimeout(() => {
          context.commit('UPDATE_CONTACT_ONLINE', resp);
          resolve();
        }, 0);
      });
    },
    UPDATE_CONTACTS_AVATARS: (context, resp) => {
      return new Promise(resolve => {
        setTimeout(() => {
          context.commit('UPDATE_CONTACTS_AVATAR', resp);
          resolve();
        }, 0);
      });
    },
    SET_CONTACTLISTS: (context, resp) => {
      return new Promise(resolve => {
        _.forEach(resp.contacts, (element, i) => {
          context.commit('SET_CONTACTLIST', element);
        })
        resolve();
      });
    },
    UPDATE_GROUP_AVATARS: (context, resp) => {
      return new Promise(resolve => {
        setTimeout(() => {
          context.commit('UPDATE_GROUP_AVATAR', resp);
          resolve();
        }, 0);
      });
    },
    SET_GROUPLISTS: (context, resp) => {
      return new Promise(resolve => {
        _.forEach(resp.groups, (element, i) => {
          context.commit('SET_GROUPLIST', element);
        })
        resolve();
      });
    },
    SET_CONATCT_EXTENSIONS: (context, resp) => {
      return new Promise(resolve => {
        setTimeout(() => {
          context.commit('SET_CONATCT_EXTENSION', resp);
          resolve();
        }, 0);
      });
    },
    SET_GROUP_EXTENSIONS: (context, resp) => {
      return new Promise(resolve => {
        setTimeout(() => {
          context.commit('SET_GROUP_EXTENSION', resp);
          resolve();
        }, 0);
      });
    },
    SET_ORG_ONLINE_LISTS: (context, resp) => {
      return new Promise(resolve => {
        setTimeout(() => {
          context.commit('SET_ORG_ONLINE_LIST', resp);
          resolve();
        }, 0);
      });
    }
  }
};
export default contact;
