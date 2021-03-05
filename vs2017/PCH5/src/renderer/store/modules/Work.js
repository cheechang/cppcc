import Vue from 'vue';
const work = {
  state: {
    storeApps: {},
    sortApps: [],
    loaclApps: {},
    searchList: [],
    isOpenNotes: false
  },

  mutations: {
    /** 清空列表 */
    CLEAR_APPINFO_LIST: (state) => {
      state.sortApps = [];
      state.searchList = [];
      state.loaclApps = {};
      state.storeApps = {};
      state.isOpenNotes = false
    },

    OPEN_NOTES_SWITCH: (state) => {
      state.isOpenNotes = true
    },

    /** 应用商店 */
    SET_STOREAPPS: (state, data) => {
      switch (data.flag) {
        // 更新app商店全部信息
        case 0: {
          state.storeApps = data.val;
          break
        }
        // 更新安装/卸载状态
        case 1: {
          Vue.set(state.storeApps[data.id], 'hasInstall', data.val)
          break
        }
        // 更新置顶状态
        case 2: {
          Vue.set(state.storeApps[data.id], 'isTop', data.state)
          break
        }
      }
    },
    /** 本地应用 */
    SET_LOCALAPP: (state, data) => {
      Vue.set(
        state.loaclApps,
        data.appID,
        {
          apps: [data],
          id: data.appID,
          name: data.appName,
          icon: data.appIcon,
          type: 2
        }
      )
    },
    /**搜索列表 */
    SET_SEARCHAPP: (state, data) => {
      state.searchList = data;
    },
    SET_SORT_APPS: (state, data) => {
      switch (data.flag) {
        // 整体更新app列表
        case 0: {
          state.sortApps = data.val;
          break;
        }
        // 鼠标拖入时，创建app分组之前更改为分组样式
        case 1: {
          state.sortApps.filter((ele, index) => {
            if (data.val.id === ele.id) {
              ele.type = data.val.status
              Vue.set(state.sortApps, index, ele)
            }
          });
          break;
        }
        // 更新文件夹名称
        case 2: {
          for(let i = 0, len = state.sortApps.length; i < len; i++) {
            if (data.val.id === state.sortApps[i].id) {
              state.sortApps[i].name = data.val.name
              let temp = JSON.stringify(state.sortApps[i]);
              Vue.set(state.sortApps, i, JSON.parse(temp));
              break
            }
          }
          break;
        }
        // 创建文件夹
        case 3: {
          // 使用构造的分组替换目标位置的元素
          for(let i = 0, len = state.sortApps.length; i < len; i++) {
            if (data.val.targetId === state.sortApps[i].id) {
              Vue.set(state.sortApps, i, data.val.groupInfo)
              break
            }
          }
          // 删除被拖拽的元素
          for(let i = 0, len = state.sortApps.length; i < len; i++) {
            if (data.val.dragEleId === state.sortApps[i].id) {
              Vue.delete(state.sortApps, i)
              break
            }
          }
          break;
        }
        // 更新文件夹成员
        case 4: {
          if (data.val.type === 1) {
            // 将拖拽的元素添加到目标分组
            for(let i = 0, len = state.sortApps.length; i < len; i++) {
              if (data.val.groupId === state.sortApps[i].id) { // dragAppInfo
                let groupInfo = JSON.parse(JSON.stringify(state.sortApps[i]));
                groupInfo.apps.push(data.val.dragAppInfo);
                Vue.set(state.sortApps, i, groupInfo)
                break
              }
            }
            // 删除原始位置的数据
            for(let i = 0, len = state.sortApps.length; i < len; i++) {
              if (data.val.dragAppInfo.appID === state.sortApps[i].id) {
                Vue.delete(state.sortApps, i)
                break
              }
            };
          };
          if (data.val.type === 2) {
            // 构造要添加到外部的app数据
            let sortAppsItem = {
              apps: [data.val.dragAppInfo],
              icon: '',
              id: data.val.dragAppInfo.appID,
              name: data.val.dragAppInfo.appName,
              type: 2
            }
            // 将数据插入到所有数据的末尾
            state.sortApps.push(sortAppsItem)
            // 删除原来分组中的数据
            for(let i = 0, len = state.sortApps.length; i < len; i++) {
              // 找到对应文件夹
              if (data.val.groupId === state.sortApps[i].id) {
                if (state.sortApps[i].apps.length === 1) {
                  Vue.delete(state.sortApps, i);
                  break
                }
                let groupInfo = JSON.parse(JSON.stringify(state.sortApps[i]));
                groupInfo.apps.forEach((ele, index) => {
                  if (data.val.dragAppInfo.appID === ele.appID) {
                    // 删除找到的app数据
                    Vue.delete(groupInfo.apps, index);
                    Vue.set(state.sortApps, i, groupInfo);
                  }
                })
                break
              }
            }
          }
          break;
        }
      }
      
    },
    ADD_APPINFO_LIST: (state, data) =>{
      state.sortApps[data].hasInstall = 1;
    },
    DELETE_APPINFO_LIST: (state, data) =>{
      state.sortApps[data].hasInstall = 2;
    }
  }
};

export default work
;
