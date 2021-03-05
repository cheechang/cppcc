import { mapGetters } from "vuex";

/**
 * @mixin
 */
const mixin = {
  computed:{
    ...mapGetters(['user_loginInfo','user_account','auth_multipleServers'])
  },
  methods: {
    _exitMultipleServers(isForced){
      let auth_multipleServers = Object.values(this.auth_multipleServers);
      let serverInfos = [];
      auth_multipleServers.forEach((el,index)=>{
        if(el.isOnline && (el.userId !== this.user_account.userId)){
          serverInfos.push(`${el.userId}@${el.server}`);
        }
      })
      if(isForced){
        // 被挤下线，此时需要告知其他服务,具体操作交给multipleServers.js 去完成
        this.$mutipleServers.haveToExitServer(serverInfos);
      }
      else{
        this.$mutipleServers.exitChildServer(serverInfos);
      }
    },
    _updataMultipleServerAvatar(userId,avatar){
      console.log('_updataMultipleServerAvatar:',avatar);
        if(this.auth_multipleServers[userId]){
            if(this.auth_multipleServers[userId].avatar !== avatar){
                let newInfo = Object.assign({},this.auth_multipleServers[userId]);
                newInfo.avatar = avatar;
                console.log('_updataMultipleServerAvatar:',newInfo);
                this.$store.commit('SET_MULTIPLE_SERVER', {flag: 1, val: newInfo})
                if(Object.values(this.auth_multipleServers).length>1){
                  this.$Service.config.setSubServerInfo({infos:Object.values(this.auth_multipleServers)});
                }
            }
        }
    },
  }
};

export default mixin;