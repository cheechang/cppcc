import Vue from 'vue';
const Hr = {
  state: {
    // 禅道账户信息
    userInfo: {
      username: '',
      password: ''
    },
    hrData: {
      bugs: [],
      stories: [],
      tasks: []
    }
  },

  mutations: {
    SET_HR_USERINFO: (state, data) => {
      state.userInfo = data;
    },
    SET_HR_DATA: (state, data) => {
      state.hrData = data
    }
  }
};
export default Hr;