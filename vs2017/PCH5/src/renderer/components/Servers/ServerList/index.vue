<template>
    <div class="server-list-container"
        :style="{height:showTransition?'152px':'0px'}"
    >
        <div class="server-list-bg" :style="{background:serverBg}"></div>
        <div class="server-list-title">
          <i class="icon server-titlt-icon">&#xe684;</i>
          <span class="server-intro">{{$t('auth.serverList')}}:</span>
          <i class="icon close-list" @click="$emit('close')">&#xe603;</i>
        </div>
        <div class="server-list-are">
            <server-item  v-for="(item,index) in serverList" :key="index" :serverData="item"  @delItem="delServer" @dblclickItem="switchServer"></server-item>
        </div>
    </div>
</template>
<script>
import { mapGetters } from 'vuex';
import MultipleServersMixin from '../multipleServersMixin'
export default {
  mixins:[MultipleServersMixin],
  components: {
    ServerItem: resolve => require(["./ServerItem"], resolve)
  },
  created(){
    console.log('serverList:',this.serverList);
    //更新头像
    if(this.user_account.avatar !=this.auth_multipleServers[this.user_account.userId].avatar){
      this._updataMultipleServerAvatar(this.user_account.userId,this.user_account.avatar);
    }
  },
  data(){
      return{
        serverBg:`url(${require('./background/serverBg.webp')})`
      }
  },
  computed:{
     ...mapGetters([
         'auth_multipleServers',
         'user_account'
     ]),
     serverList(){
       let currentServer = this.auth_multipleServers[this.user_account.userId];
       let auth_multipleServers = Object.assign({},this.auth_multipleServers);
       delete auth_multipleServers[this.user_account.userId];
       let serverlist = Object.values(auth_multipleServers);
       serverlist.unshift(currentServer)
       return serverlist
     } 
  },
  props: {
    showTransition:false
  },
  methods:{
      delServer(userId){
          console.log('delServer:userId',userId);
          let key = `${userId}@${this.auth_multipleServers[userId].server}`;
          if(this.auth_multipleServers[userId].isOnline){
            this.$mutipleServers.exitChildServer([key]);
          }
          this.$store.commit('SET_MULTIPLE_SERVER', {flag: 2, val: userId})
          let infos = Object.values(this.auth_multipleServers);
          this.$Service.config.setSubServerInfo({infos:infos});
          this.$emit('close');
      },
      switchServer(userId){
          console.log('switchServer:userId',userId);
          if(this.auth_multipleServers[userId].isOnline){
            //切入此服务器
            let serversInfo = Object.assign({},this.auth_multipleServers);
            serversInfo[userId].isMsg = false;
            let param = {
              key:`${userId}@${serversInfo[userId].server}`,
              info:Object.values(serversInfo)
            }
            this.$emit('switchToServer',param);
          }
          else{
            //登录此服务器
            this.$emit('loginServer',this.auth_multipleServers[userId])
          }
      }
  }
}
</script>
<style lang="scss" scoped>
.server-list-container{
  //background: rgba(0, 0, 0, 0.91);
  //background:#abc;
  overflow: hidden;
  transition: height 0.3s;
  height: auto;
  width: 100%;
  position: absolute;
  top: 55px;
  left:0; //fit xp
  -webkit-app-region: no-drag;
  box-shadow: $--box-shadow-navbar;
  @include z-index(menu);
  .server-list-bg{
    background-size: cover !important;
    filter: blur(3px);
    width: calc(100% + 4px);
    top: -4px;
    left:-4px;
    height: calc(100% + 4px);
    position: absolute;
  }
  .server-list-title{
    color: #fff;
    font-size: 14px;
    margin: 0 26px 0px 10px;
    padding: 10px;
    position: relative;
    .icon{
      width: 20px;
      height: 20px;
      background-repeat: no-repeat;
      background-size: cover;
      background-position: 50%;
    }
    .server-titlt-icon{
      font-size: 20px;
      color:#fff;
      // background-repeat: no-repeat;
      // background-size: cover;
      // background-position: 50%;
    }
    .close-list{
      position: absolute;
      top: 10px;
      right: 10px;
      font-size: 24px;
      &:hover{
        background: $--color-danger
      }
    }
    .server-intro{
      margin-left: 7px
    }
  }
  .server-list-are{
    margin-top: -5px;
    height: 100px;
    width: 100%;
    display: flex;  
  }
}
</style>