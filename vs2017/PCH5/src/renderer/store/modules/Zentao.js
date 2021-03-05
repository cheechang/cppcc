import Vue from 'vue';
const zentao = {
  state: {
    // 禅道账户信息
    userInfo: {
      account: '',
      password: ''
    },
    zentaoData: {
      bugs: [],
      stories: [],
      tasks: []
    }
  },

  mutations: {
    CLEAR_ZENTAO: (state) => {
      state.userInfo.account = '';
      state.userInfo.password = '';
      for(let key of Object.keys(state.zentaoData)){
        state.zentaoData[key] = [];
      }
    },
    SET_ZENTAO_USERINFO: (state, data) => {
      state.userInfo = data;
    },
    SET_ZENTAO_DATA: (state, data) => {
      if (data.bugs.length > 0) {
        data.bugs.forEach(element => {
          element.lastEditedDate = element.lastEditedDate.split(" ", 1)[0];
          switch (element.status) {
            case "active": {
              element.status = "激活";
              break;
            }
          }
        });
      }
      if (data.tasks.length > 0) {
        data.tasks.forEach(element => {
          switch (element.status) {
            case "doing": {
              element.status = "进行中";
              break;
            }
          }
        });
      }
      state.zentaoData = data;
    }
  }
};
export default zentao;