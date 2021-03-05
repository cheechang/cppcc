import Vue from 'vue';
import { converseFullPinYin } from '../../../comm/pinyin.js';
import {
  resolve
} from 'path';
const chat = {
  state: {
    ChatList: {},
    /* 聊天内容 */
    ChatContent: {},
    /*
     * 聊天对象（人、群）
     */
    ChatObject: {},
    ChatObjectSortInofObject: {}, // add by hx 8.18
    RtcFileList: {},
    rtcBusyList: {},
    isReceiveRtc: {},
    ChatContentTop: {},
    rtcDelModel : '',
    shouldUpdate: new Set(), // add by hx 9.4
    // ImgSaveAsDicValue: '1', // 图片右键菜单“另存为”选项默认显示
    // FileOpenDicValue: '1', // 文件气泡“打开”按钮默认显示
    ChatDicValue: {},
    rtcFileSize:500,
    isLoopEnd: true,
    sectorOpen:true
  },
  mutations: {
      //设置显示界别开关
      SET_SECTOROPEN(state, data){
        state.sectorOpen = data;
      },
      //设置文件直传文件大小
      SET_RTC_FILESIZE(state, data){
        state.rtcFileSize = data;
      },

     /** 会话列表的增删改查 监听会话列表更新通知 
      *  @param[in] cb _1 传入列表标志
      *全部更新:
      *  0x01 第一个包, 需要清理原来的数据
      *  0x02 中间的包， 在原来的数据后面追加
      *  0x04 最后的包， 最近会话发送完毕
      *部分更新:
      *  0x08 更新
      *  0x10 新增
      *  0x20 删除
      *全部删除
      *  0x40 删除所有最近联系人
      *  _2 传入会话集合
      */
     SET_CHATLIST: (state, {element, flag}) => {
      const OPERTYPE_SET_FIRST = 0x01,
            OPERTYPE_SET_CONTINUE = 0x02,
            OPERTYPE_SET_LAST = 0x04,
            OPERTYPE_SET_LIST = 0x05,
            OPERTYPE_UPDATE = 0x08,
            OPERTYPE_ADD = 0x10,
            OPERTYPE_DELETE = 0x20; 
      switch (flag) {
        case OPERTYPE_SET_FIRST:
        case OPERTYPE_SET_CONTINUE:
        case OPERTYPE_SET_LIST: {
          // _.forEach(resp.chats, element => {
            Vue.set(state.ChatList, element.id, element);
          // });
          break;
        }
        case OPERTYPE_SET_LAST: {
          state.isLoopEnd = true
          // _.forEach(resp.chats, element => {
            Vue.set(state.ChatList, element.id, element);
          // });
          break;
        }
        case OPERTYPE_UPDATE:
        case OPERTYPE_ADD: {
          Vue.set(state.ChatList, element.id, element);
          break;
        }
        case OPERTYPE_DELETE: {
          Vue.delete(state.ChatList, element.id);
          break;
        }
      }
    },


    /** 更新最近会话列表 */
    UPDATE_CHATLIST: (state, data) => {
      let newChatList = { ...state.ChatList[data.id], ...data}
      Vue.set(state.ChatList, data.id, newChatList)
    },


    /** 手动插入最近会话列表 */
    PUSH_CHATLIST: (state, resp) => {
      if (!state.ChatList[resp.id]) Vue.set(state.ChatList, resp.id, resp)
      else {
        let chatMember = state.ChatList[resp.id]
        chatMember.startTime = resp.startTime
        Vue.delete(state.ChatList, resp.id)
        Vue.set(state.ChatList, resp.id, chatMember)
      }
    },

    /** 删除最近会话列表 */
    DEL_CHATLIST: (state, id) => {
      Vue.delete(state.ChatList, id);
    },

    /** 修改最近会话状态 */
    CHANGE_CHAT_LIST_STATE: (state, data) => {
      Vue.set(state.ChatList[data.id], 'state', data.type)
    },

    /** 更新最近会话rtc文件状态 */
    UPDATE_CHATLIST_RTCFILE: (state, data) => {
      Vue.set(state.ChatList[data.id], 'isRtcFile', data.type)
      if (data.type === 1) {
        Vue.set(state.ChatList[data.id], 'startTime', data.time)
      }
    },

    /**
     * 聊天内容的增加
     * id 用户id
     * ChatContent 每个id对应的聊天内容
     * */
    SET_CHATCONTENT: (state, data) => {
      let id = !data.forWardId ? data.targetId ? data.targetId : data.messageObject.targetId : data.forWardId;
      let ChatContent = state.ChatContent[id];
      if (!state.ChatContent[id]) {
        Vue.set(state.ChatContent, id, data.msgs);
      } else {
        // if (data.isHistory) {
        //   Vue.set(state.ChatContent, id, data.msgs);
        // } else {
          Vue.set(ChatContent, `id_${data.messageObject.msgId}`, data);
        // }
      }
    },

    /** 删除消息 */
    DEL_MESSAGE: (state, data) => {
      Vue.delete(state.ChatContent[data.targetId], `id_${data.msgId}`)
    },

    /**
     * 已读未读改造
     * 修改消息的未读数 
     * */
    UPDATE_UNREADCOUNT: (state, data) => {
      console.log('UPDATE_UNREADCOUNT::')
      if (!data.targetIsGroup) {
        _.forEach(state.ChatContent[data.targetId], element => {
          if (element.messageObject.msgId <= data.msgId && element.messageObject.maxUnReadCount === 0) {
            Vue.set(element.messageObject, 'maxUnReadCount', 1)
          }
        })
      } else {
        if (!state.ChatContent[data.targetId][`id_${data.msgId}`]) return
        Vue.set(state.ChatContent[data.targetId][`id_${data.msgId}`].messageObject, 'unReadCount', data.unReadCount)
        Vue.set(state.ChatContent[data.targetId][`id_${data.msgId}`].messageObject, 'maxUnReadCount', data.maxUnReadCount)
        Vue.set(state.ChatContent[data.targetId][`id_${data.msgId}`].messageObject, 'snapshotId', data.snapshotId)
      }
    },

    /*
     * ADD_CHATCONTENT 加载更多聊天记录
     * isDown true 向上加载更多消息 向下添加离线消息
     * */
    ADD_CHATCONTENT: (state, data) => {
      if (!data.isDown) {
        state.ChatContent[data.message.targetId] = Object.assign(data.message.msgs, state.ChatContent[data.message.targetId])
      } else {
        // * 离线消息推送的可能携带已经展示的消息 或者离线推送比较晚 在连上时自己又发了一条消息 特殊处理 保证正常显示
        let chatContents = state.ChatContent[data.message.targetId]
        chatContents = _.orderBy(Object.assign(data.message.msgs, chatContents),['messageObject.time'],['esc'])
        let msg = {}
        _.forEach(chatContents, element => {
          Vue.set(msg, `id_${element.messageObject.msgId}`, element)
        })
        state.ChatContent[data.message.targetId] = msg
        // let msgLength = Object.keys(chatContents).length || 0
        // let lastMsgId = msgLength ?  chatContents[Object.keys(chatContents)[msgLength - 1]].messageObject.msgId : 0
        // console.log('lastMsgId::', lastMsgId)
        // for (let i in data.message.msgs) {
        //   console.log('ADD_CHATCONTENT', i, data.message.msgs[i].messageObject.msgId)
        //   if (!chatContents[i] && data.message.msgs[i].messageObject.msgId > lastMsgId) {
        //     Vue.set(state.ChatContent[data.message.targetId], i, data.message.msgs[i])
        //   }
        // }
      }
    },
    /** 删除对应的id者的所有聊天内容 */
    DEL_CHATCONTENT_BYID: (state, deleteId) => {
      Vue.delete(state.ChatContent, deleteId);
    },

    /**
     * 替换聊天内容 
     * 解密消息替换
     * 文本转web替换
     * */
    REPLACE_CHATCONTENT: (state, data) => {
      Vue.set(state.ChatContent[data.id], `id_${data.msg.messageObject.msgId}`, data.msg)
    },


    /** 减少聊天缓存内容 */
    REDUCE_CACHE_CONTENT(state, id) {

      if (!state.ChatContent[id]) return
      let msglistArray = Object.keys(state.ChatContent[id])
      if (msglistArray.length < 30) return 
      return new Promise (resolve => {
        state.ChatContent[id] =  _.pick(state.ChatContent[id], msglistArray.slice(-10));
        resolve()
      })
    },

    UPDATE_MSGID: (state, data) => {
      Vue.set(state.ChatContent[data.id][`id_${data.preMsgId}`].messageObject, 'msgId', data.msgId)
      // state.ChatContent[data.id][`id_${data.preMsgId}`].messageObject.time = data.time
      Vue.set(state.ChatContent[data.id][`id_${data.preMsgId}`].messageObject, 'time', data.time)
      if (!data.isFail) {
        console.log('data.isnoFail')
        state.ChatContent[data.id][`id_${data.msgId}`] = state.ChatContent[data.id][`id_${data.preMsgId}`];
        delete(state.ChatContent[data.id][`id_${data.preMsgId}`])
        // state.ChatContent[data.id][`id_${data.msgId}`].messageObject.time = data.time
      } else {
        console.log('data.isFail')
        let updateMsg = state.ChatContent[data.id][`id_${data.preMsgId}`]
        Vue.delete(state.ChatContent[data.id], `id_${data.preMsgId}`)
        Vue.set(state.ChatContent[data.id], `id_${data.msgId}`, updateMsg)
      }
    },

    /** 更新聊天内容  */
    UPDATE_CHATCONTENT: (state, data) => {
      if (!state.ChatList[data.groupId]) return;
      if (state.ChatList[data.groupId].isRefresh) Vue.delete(state.ChatList[data.groupId], 'isRefresh');
      else Vue.set(state.ChatList[data.groupId], 'isRefresh', true);
      if (state.ChatList[data.groupId].sendUserId === data.member.id)
        Vue.set(state.ChatList[data.groupId], 'whereFrom', data.member.remark);

      if (!state.ChatContent[data.groupId]) return;
      _.forEach(state.ChatContent[data.groupId], element => {
        if (element.messageObject.fromId !== data.member.id) return;
        if (element.isRefresh) Vue.delete(element, 'isRefresh');
        else Vue.set(element, 'isRefresh', true);
      })
    },

    /**
     * 解散群 被T除 自己退出群
     * data.operType 31 解散群 32 被T除 33 自己退出
     * 删除最近会话列表
     */
    CHAT_GROUP_CHANGE: (state, data) => {
      if (data.operType === 31 || data.operType === 32 || data.operType === 33) Vue.delete(state.ChatList, data.group.info.groupId);
    },


    /**
     * 清空聊天所有缓存
     * 最近会话列表
     * 聊天内容
     * 聊天对象信息
     */
    EMPTY_ALL_DATA_CACHE: (state, data) => {
      state.ChatList = {};
      state.ChatContent = {};
      state.ChatObject = {};
      state.ChatObjectSortInofObject ={};
      state.shouldUpdate.clear();
      state.RtcFileList = {};
      state.isReceiveRtc = {};
      state.ChatDicValue = {};
      state.isLoopEnd = false
    },

    /** 储存聊天对象 */
    SET_CHAT_OBJECT: (state, data) => {
      let chatObject = {}
      _.forEach(data.chatObject, (e, i)=> {
        Vue.set(chatObject, e[0], e[1])
      })
      Vue.set(state.ChatObject, data.id, chatObject);
      state.shouldUpdate.add(data.id);
    },
    SET_CHAR_SORTINFO: (state, data) => {
      Vue.set(state.ChatObjectSortInofObject, data.id, data.sortArray);
    },
    /** 更新聊天对象（4.6离线或首次拉取群成员） */
    UPDATE_CHAT_OBJECT_OFFLINE: (state, data) => {
      let offlineMember = data.offlineMemberRes
      // 离线：添加/更新
      if (!state.ChatObject[data.groupId]) { //避免首次拉取群成员没有对应数据
        Vue.set(state.ChatObject, data.groupId, {});
      }
      _.forEach(offlineMember.changeMembers, ([key, value]) => {
        // console.log('离线：该成员已被添加进群>'+'id:'+key+'name:'+value.remark || value.name)
        Vue.set(state.ChatObject[data.groupId], key, value);
      })
      // 离线：删除
      _.forEach(offlineMember.removeMemberIds, memberId => {
        // console.log('离线：该成员已被移除>'+'id:'+memberId)
        Vue.delete(state.ChatObject[data.groupId], memberId);
      })
    },
    /** 更新聊天对象 */
    UPDATA_CHAT_OBJECT(state, data) {
      _.forEach(data.chatObject, ([key, value]) => {
        let isExist = key in state.ChatObject[data.id];
        if(!isExist) {
          // console.log('离线：该成员已被添加进群>'+'id:'+key+'name:'+value.remark || value.name)
          Vue.set(state.ChatObject[data.id], key, value);
          state.shouldUpdate.add(data.id);
        }
      });
      _.forEach(state.ChatObject[data.id], (element, index) => {
        let memberIndex = _.findIndex(data.chatObject, ([key, value]) => 
        {
          console.log('key=== index',key,index,value)
          return  key === index
        })

        if (memberIndex===-1) {
           console.log('离线：该成员已被移除>'+'id:'+index+'name:'+element.remark || element.name)
          // Vue.delete(state.ChatObject[data.id], index); 
          // state.shouldUpdate.add(data.id);
        }
      });
    },

    UPDATE_MEMBER_AVATAR: (state, data) => {
      console.log('UPDATE_MEMBER_AVATAR:::', data)
      let objectInfo = state.ChatObject[data.id][data.userId]
      objectInfo.thumbAvatar = data.avatar
      Vue.delete(state.ChatObject[data.id], data.userId)
      Vue.set(state.ChatObject[data.id], data.userId, objectInfo)
      state.shouldUpdate.add(data.id);
    },

    /** 删除聊天对象 */
    DEL_CHAT_OBJECT: (state, id) => {
      if (state.ChatObject[id]) {
        Vue.delete(state.ChatObject, id);
        Vue.delete(state.ChatObjectSortInofObject, id);
      }
    },


    /** 更新群成员类型  */
    UPDATE_MEMBER_TYPE: (state, data) => {
      if (!state.ChatObject[data.groupId]) return;
      _.forEach(state.ChatObject[data.groupId], element => {
        if (element.memberType == 3) Vue.set(element, 'memberType', 1);
        if (element.id !== data.groupLeaderId) return;
        Vue.set(element, 'memberType', 3);
      });
      // let ChatObjectSortObject = _.orderBy(
      //   state.ChatObject[data.groupId],
      //   [
      //     "memberType",
      //     val => {
      //       return converseFullPinYin(val.pingyin.trim());
      //     }
      //   ],
      //   ["desc", "asc"]
      // );
      // Vue.set(state.ChatObjectSortObject, data.groupId, ChatObjectSortObject);
      // console.log('更新群成员类型>', state.ChatObjectSortObject[data.groupId]);
      if (state.ChatObject[-1]) Vue.delete(state.ChatObject, -1);
      else Vue.set(state.ChatObject, -1, {});
      state.shouldUpdate.add(data.groupId);
    },

    /** 更新群成员信息 */
    UPDATE_MEMBER_INFO: (state, data) => {
      if (!state.ChatObject[data.groupId]) return;
      Vue.set(state.ChatObject[data.groupId], data.member.id, data.member);
      // let ChatObjectSortObject = _.orderBy(
      //   state.ChatObject[data.groupId],
      //   [
      //     "memberType",
      //     val => {
      //       return converseFullPinYin(val.pingyin.trim());
      //     }
      //   ],
      //   ["desc", "asc"]
      // );
      // Vue.delete(state.ChatObjectSortObject, data.groupId);
      // Vue.set(state.ChatObjectSortObject, data.groupId, ChatObjectSortObject);
      // console.log('更新群成员信息>', state.ChatObjectSortObject[data.groupId]);
      if (state.ChatObject[-1]) Vue.delete(state.ChatObject, -1);
      else Vue.set(state.ChatObject, -1, {});
      state.shouldUpdate.add(data.groupId);
    },

    UPDATE_GROUP_MEMBER: (state, data) => {
      if (data.members.length <= 0) return;
      if (!state.ChatObject[data.groupId]) return;
      if (data.operType === 1) { // 添加群成员
        data.members.forEach(element => {
          Vue.set(state.ChatObject[data.groupId], element.id, element)
        });
      } else if (data.operType === 32 || data.operType === 33) { // 删除群成员、退群
        Vue.delete(state.ChatObject[data.groupId], data.members[0].id)
      }
      // let ChatObjectSortObject = _.orderBy(
      //   state.ChatObject[data.groupId],
      //   [
      //     "memberType",
      //     val => {
      //       return converseFullPinYin(val.pingyin.trim());
      //     }
      //   ],
      //   ["desc", "asc"]
      // );
      // Vue.set(state.ChatObjectSortObject, data.groupId, ChatObjectSortObject);
      // console.log('更新群成员>', state.ChatObjectSortObject[data.groupId]);
      if (state.ChatObject[-1]) Vue.delete(state.ChatObject, -1);
      else Vue.set(state.ChatObject, -1, {});
      state.shouldUpdate.add(data.groupId);
    },

    SET_P2P_FILE_STATE: (state, arg) => {
      Vue.set(state.isReceiveRtc, 'id', arg.id)
      Vue.set(state.isReceiveRtc, 'value', arg.value)
      Vue.set(state.isReceiveRtc, 'localId', arg.localId)
    },

    DEL_P2P_FILE_STATE: (state, arg) => {
      state.isReceiveRtc = {}
    },

    UPDATE_FILE_DEL_MODE: (state, arg) => {
      state.rtcDelModel = arg
    },
    // RTC_FILE: (state, resp) => {
    //   if (!state.RtcFileList[resp.messageObject.targetId]) {
    //     let file = {}
    //     file[resp.messageObject.time] = resp
    //     Vue.set(state.RtcFileList, resp.messageObject.targetId, file);
    //   } else {
    //     let RtcFileList = state.RtcFileList[resp.messageObject.targetId];
    //     Vue.set(RtcFileList, resp.messageObject.time, resp);
    //   }
    // },
    SET_RTC_FILE: (state, resp) => {
      if (!state.RtcFileList[resp.messageObject.targetId]) {
        let file = {}
        Vue.set(file, resp.messageObject.time, resp)
        Vue.set(state.RtcFileList, resp.messageObject.targetId, file);
        console.log('state.RtcFileList', JSON.stringify(state.RtcFileList))
      } else {
        let RtcFileList = state.RtcFileList[resp.messageObject.targetId];
        Vue.set(RtcFileList, resp.messageObject.time, resp);
      }
    },

    UPDATE_RTC_MSGID: (state, data) => {
      console.log('UPDATE_RTC_MSGIDS', JSON.stringify(data))
      Vue.set(state.RtcFileList[data.id][data.preMsgId].messageObject, 'msgId', data.msgId)
      state.RtcFileList[data.id][data.msgId] = state.RtcFileList[data.id][data.preMsgId];
      delete(state.RtcFileList[data.id][data.preMsgId])
      console.log('UPDATE_RTC_MSGID', state.RtcFileList[data.id])
    },

    FILTER_DEL_RTC_FILE: (state, resp)=> {
      if (!state.RtcFileList[resp.id]) return
      _.forEach(state.RtcFileList[resp.id], element => {
       if (element.messageObject.msgId === resp.msgId) {
         Vue.delete(state.RtcFileList[resp.id], element.messageObject.time)
       }
      });
    },

    DEL_RTC_FILE: (state, resp) => {
      if (!state.RtcFileList[resp.id]) return
      Vue.delete(state.RtcFileList[resp.id], resp.msgId);
      if (!Object.keys(state.RtcFileList[resp.id]).length) {
        Vue.delete(state.RtcFileList, resp.id)
      }
    },

    REMOVE_CHATTER_RTCLIST: (state, id) => {
      if (!state.RtcFileList[id]) return
      Vue.delete(state.RtcFileList, id)
    },

    // REMOVE_ALL_RTCLIST: ()

    SET_RTCBUSY_LIST:(state, data) => {
      Vue.set(state.rtcBusyList, data.targetId, data);
    },

    // DEL_BUSY_FILE: (state, data) => {
    //   if (!state.rtcBusyList[data.messageObject.time]) return
    //   Vue.delete(state.rtcBusyList, data.messageObject.time);
    // },

    /**
     * 【消息置顶】清空数据
     */
    CLEAR_CHATCONTENT_TOP: (state, data) => {
      // Vue.set(state.ChatContentTop, {})
      state.ChatContentTop = {};
    },
    /**
     * 【消息置顶】数据管理--添加
     */
    SET_CHATCONTENT_TOP: (state, data) => {
      /*
      if (!state.ChatContentTop[data.id])
        Vue.set(state.ChatContentTop, data.id, data)
      else 
        Vue.set(state.ChatContentTop[data.id], data.msg.fromId, data.msg)
      */
      if(state.ChatContentTop[data.msgId]){
        return;
      }
      Vue.set(state.ChatContentTop, data.msgId, data)
    },
    /**
     * 【消息置顶】数据管理--删除
     */
    DEL_CHATCONTENT_TOP: (state, data) => {
      /*
      if (!state.ChatContentTop[data.id] && !state.ChatContentTop[data.id][data.msgId]) return
      Vue.delete(state.ChatContentTop[data.id], data.msgId)
      */
      _.forEach(Object.values(state.ChatContentTop), (element) =>{
        console.log('===========',data.msgId,element.msgId)
        if(data.msgId == element.msgId){
          Vue.delete(state.ChatContentTop, element.msgId)
        }
      });
    },
    /**
     * 设置是否需要更新
     */
    SET_SHOULDUPDATE: (state, data) => {
      state.shouldUpdate.delete(data);
    },
    /**
     * 配置图片右键菜单“另存为”选项显示/隐藏
     */
    SET_IMG_DICVALUE: (state, {dicKey, value}) => {
      console.log('SET_IMG_DICVALUE>>>>>>>>>>>>>>>>>>>>>>>>>>>'+dicKey, value)
      Vue.set(state.ChatDicValue, dicKey, value);
    },
    /**
     * 配置文件气泡“打开”按钮显示/隐藏
     */
    SET_FILE_DICVALUE: (state, {dicKey, value}) => {
      console.log('SET_FILE_DICVALUE>>>>>>>>>>>>>>>>>>>>>>>>>>>'+dicKey, value)
      Vue.set(state.ChatDicValue, dicKey, value);
    }
  },
  actions: {
    SET_SECTOROPEN:(context,param) => {
      new Promise(resolve => {
        setTimeout(() => {
          context.commit('SET_SECTOROPEN', param);
          resolve()
        });
      })
    },
    SET_CHAT_OBJECT: (context, param) => {
      new Promise(resolve => {
        setTimeout(() => {
          context.commit('SET_CHAT_OBJECT', param);
          resolve()
        });
      })
    },
    SET_CHAR_SORTINFO: (context, param) => {
      setTimeout(() => {
        context.commit('SET_CHAR_SORTINFO', param);
      })
    },
    SET_CHATLIST: (context, param) => {
      _.forEach(param.chats, element => {
        context.commit('SET_CHATLIST', {element, flag: param.flag});
      })
    },
    SET_CHATCONTENT: (context, param) => {
      setTimeout(() => {
        context.commit('SET_CHATCONTENT', param);
      });
    },
    UPDATE_CHATLIST: (context, param) => {
      setTimeout(() => {
        context.commit('UPDATE_CHATLIST', param);
      });
    },
    UPDATE_UNREADCOUNT: (context, param) => {
      setTimeout(() => {
        context.commit('UPDATE_UNREADCOUNT', param);
      });
    },
    CHANGE_CHAT_LIST_STATE: (context, param) => {
      setTimeout(() => {
        context.commit('CHANGE_CHAT_LIST_STATE', param);
      });
    },
    PUSH_CHATLIST: (context, param) => {
      setTimeout(() => {
        context.commit('PUSH_CHATLIST', param);
      });
    },
    PENDING_MSG: (context, param) => {
      setTimeout(() => {
        context.commit('PENDING_MSG', param);
      });
    },
    UPDATE_MEMBER_INFO: (context, param) => {
      new Promise(resolve => {
        setTimeout(() => {
          context.commit('UPDATE_MEMBER_INFO', param);
          resolve();
        });
      });
    },

    REDUCE_CACHE_CONTENT: (context, param) => {
      setTimeout(() => {
        context.commit('REDUCE_CACHE_CONTENT', param);
      })
    },

    UPDATE_CHATCONTENT: (context, param) => {
      new Promise(resolve => {
        setTimeout(() => {
          context.commit('UPDATE_CHATCONTENT', param);
          resolve();
        });
      });
    },
    UPDATE_GROUP_MEMBER: (context, param) => {
      new Promise(resolve => {
        setTimeout(() => {
          context.commit('UPDATE_GROUP_MEMBER', param);
          resolve();
        });
      });
    },
    SET_CHATCONTENT_TOP: (context, param) => {
      new Promise(resolve => {
        setTimeout(() => {
          context.commit('SET_CHATCONTENT_TOP', param);
          resolve();
        });
      });
    },
    DEL_CHATCONTENT_TOP: (context, param) => {
      new Promise(resolve => {
        setTimeout(() => {
          context.commit('DEL_CHATCONTENT_TOP', param);
          resolve();
        });
      });
    },
    CLEAR_CHATCONTENT_TOP: (context, param) => {
      new Promise(resolve => {
        setTimeout(() => {
          context.commit('DEL_CHATCONTENT_TOP', param);
          resolve();
        });
      });
    },
    UPDATA_CHAT_OBJECT: (context, param) => {
      new Promise(resolve => {
        setTimeout(() => {
          context.commit('UPDATA_CHAT_OBJECT', param);
          resolve();
        });
      });
    },
    UPDATE_CHAT_OBJECT_OFFLINE: (context, param) => {
      new Promise(resolve => {
        context.commit('UPDATE_CHAT_OBJECT_OFFLINE', param);
        resolve();
      });
    }
  }
};
export default chat;
