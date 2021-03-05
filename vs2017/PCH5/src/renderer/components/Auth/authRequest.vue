<template>
  <div class="auth-request">
    <v-modal  cardSize="auth-request-class">
      <i class="icon" :style="{'align-self':'flex-end',height:'16px'}" @click="$emit('close')">&#xe603;</i>
       <v-avatar class="app-avatar"  :src="getAppIcon" :offline="false" size='is-big' :sex="7"></v-avatar>
       <!-- <p></p>
        -->
        <div class="auth-request-info">
         <div class="auth-request-account">
            <span>{{$t('auth.currentAccount')}}:</span>
            <span class="auth-request-appname">{{`${user_account.phone}@${user_account.server}`}}</span>
        </div>
            <div class="auth-request-account">
            <span>{{$t('auth.appName')}}:</span>
            <span class="auth-request-appname">{{appName}}</span>
            </div>
        </div>
      
       <v-button
        class="auth-request-btn"
        :type="`is-primary`" 
        @click="$emit('responseRequest',0)"
       >{{$t('auth.permission')}}</v-button>
    </v-modal>
  </div>
</template>
<script>
import { mapGetters } from "vuex";
export default {
  data() {
    return {
      appName: this.thirdParty_authRequest.appName||'',
      appIcon:this.thirdParty_authRequest.appIcon||''
    };
  },
  components: {},
  watch: {},
  methods: {},
  computed: {
    ...mapGetters([
    "user_account", 
    "user_localConfig",
    'user_headImgPath'
    ]),
    getAppIcon(){
      if(this.appIcon){
       // console.log("this.appIcon:",this.user_headImgPath+this.appIcon);
        return this.user_headImgPath + this.appIcon;
      }
      return '';
    }
  },
  props: {
    thirdParty_authRequest:null
  }
};
</script>
<style lang="scss" >
.auth-request-class {
  width: 310px;
  height: 360px;
}
.auth-request {
  .modal-card-body {
    border-radius: $--border-radius-base;
  }
  .auth-request-info {
    margin: auto;
    height: 100px;
    font-size: $--font-size-mid;
    color: get-grey-color(darken-2);
    .auth-request-account {
      margin-top: 15px;
      .auth-request-appname {
        color: $--color-info;
      }
    }
  }
  .auth-request-btn {
    margin: 0 auto;
    margin-bottom: 40px;
    width: 220px;
    height: 35px;
    background-color: rgb(10,99,241);
    border-radius: $--border-radius-large;
     &:hover{
      background-color: rgb(8,86,211);
    }
  }
  .app-avatar {
    width: 115px;
    height: 115px;
    margin: 20px auto;
    margin-bottom: 0px;
  }
}
</style>
