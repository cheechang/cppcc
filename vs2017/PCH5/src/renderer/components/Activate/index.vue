<template>
  <div class="activate-index" >
    <router-view class="router-class" style="-webkit-app-region: no-drag;" v-if="showRouterView"></router-view>
  </div>
</template>
<script>
import { mapGetters } from "vuex";
export default {
  data() {
    return {
      showRouterView:false
    };
  },
  computed: {
    ...mapGetters([
      "user_account",
      "user_loginInfo",
      'user_systemConfig',
      'auth_extendedField'
    ])
  },
  created() {
     if((this.user_systemConfig & 128) === 128 ){ 
      console.log('this.user_systemConfig',this.user_systemConfig)
      this.$Service.contact.queryExtendedField({ parentId: 68, dicKey: "accountActivate" },
        resp => {
          console.log("resp:::::::",resp)
          this.showRouterView = resp.code === 0;
          let obj = JSON.parse(resp.EnterpriseDictionarys[0].extend);
          this.$store.commit('SET_EXTENDEDFIELD', obj);
          let userType = this.user_loginInfo.userType;
          console.log("this.user_systemConfig::::",this.user_systemConfig);
          console.log('是否包含了128  :::1',this.user_systemConfig & 128 === 128);
        if((userType === 1 && obj.phone === 'code') || (userType === 3 && obj.email === 'code')){
           this.$router.push({ path:'/Verify'});
          }else{
          this.$router.push({ path:'/VerifyField'});
          } 
        }) 
      }else{
        console.log('ChangePwd');
        this.showRouterView = true;
        this.$router.push({ path: '/ChangePwd'});
      }
    }
}

</script>
<style lang="scss">  
.router-class{
  .modal-background{
    background: #000;
    opacity: 0.3;
  }
  .modal-card{
    width:250px;
  }
}
  
</style>
