<template>
  <div class="add-server">
    <v-modal cardSize="add-server-class">
        <div class="is-operating" v-if="isOperating"></div>
        <div class="modal-card-head" slot="header-top">
          <p class="modal-card-title">{{ getTitle }}</p>
          <i class="icon" @click="closeAddServer">&#xe603;</i>
        </div>
        <div v-if="showPreLogin" class="add-server-pre-login">
            <server-pre-login @pre-login-succ="preLoginSucc"></server-pre-login>
        </div>
        <div v-else :class="['add-server-login',{'server-login-height':!!loginAccoutInfo || reduceHeight}]">
           <server-login :loginTypes="loginTypes" :loginAccoutInfo="loginAccoutInfo" :elogo="elogo" :server="server" @goBack="showPreLogin=true,server=''" @close="$emit('close')" @is-shading="getIsShading" @switchToServer="switchToServer" @reduceHeight="reduceHeight = true"></server-login>
        </div>
    </v-modal>
  </div>
</template>
<script>
import ServerLogin from './ServerLogin.vue';
import ServerPreLogin from './ServerPreLogin.vue';
export default {
  data(){
      return{
          elogo:'',
          server:this.loginAccoutInfo ? this.loginAccoutInfo.server:'',
          infos:{},
          showPreLogin:this.loginAccoutInfo ? false:true,
          loginTypes:[],
          isOperating:false,
          reduceHeight:false
      }
  },
  props:{
      loginAccoutInfo:Object
  },
  computed:{
      getTitle(){
          if(this.server){
            return `[${this.server}]${this.$t('auth.server')}`
          }
          return this.$t('auth.childServerLogin');
      }
  },
  methods:{
      switchToServer(param){
           this.$emit('switchToServer',param);
      },
      closeAddServer(){
          this.$mutipleServers.exitChildServer();
          this.$emit('close');
      },
      preLoginSucc(infos){
          console.log('infos:',infos);
          this.elogo = infos.elogo;
          this.server = infos.server;
          this.infos.server = infos.server;
          this.loginTypes = infos.loginTypes;
          this.showPreLogin = false;
      },
     getIsShading(e){
         this.isOperating = e;
     }
  },
  components: {
    ServerLogin,
    ServerPreLogin
  }
};
</script>
<style lang="scss">
.add-server {
    .add-server-class {
        width: auto;
        height: auto;
        position: absolute;
        z-index: 9;
        border-radius: $--border-radius-base;
        overflow: hidden;
        background: #ffffff;
        .is-operating{
            z-index: 1;
            top:0px;
            width: 100%;
            height: 100%;
            position: absolute;
            -webkit-app-region: no-drag;
        }
        .modal-card-head {
            height: 20px;
            background: #f0f0f0;
            border-bottom: none;
            .modal-card-title {
                font-size: 14px;
            }
            .icon {
                font-size: 14px;
                margin-right: -15px;
            }
        }
        .add-server-pre-login{
            width: 310px;
            height: 270px;
            display: flex;
            justify-content: center;
        }
        .add-server-login{
            display: flex;
            justify-content: center;
            width: 310px;
            height: 350px;
            overflow-y: hidden;
        }
        .server-login-height{
            height: 330px;
        }
    }
}
</style>
