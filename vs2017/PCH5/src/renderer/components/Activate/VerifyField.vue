<template>
<v-modal>
  <div class="phone-verify">
    <div class="phone-verify-page">
      <headerTip :headerName="$t('auth.userinfoVerify')"></headerTip>
       <v-tip 
        :isSuccess="isSuccess"
        :tipLabelMsg="errorMsg"
        :isLabelTip="isErrorBox"
        @close="isErrorBox = false"
      > 
        <v-input 
          v-for="(item,index) in accountNum" :key="index"
          class="inputs"
          :type="'text'"
          :isBorder="false"
          hasLine
          hasLabel
          :customType="'input-size'"
          :position="'right'"
          :maxlength="50"
          :isAuth="false"
          :placeholder="item"
          v-model="fieldValue[index]"
          @keyup-enter='next'
        ></v-input>
      </v-tip>

      <!-- 下一步 -->
      <v-btn
        class="auth-button"
        :size="'v-button--max_width'"
        :disable="!isDisable"
        :type="lodingState"
        @click="next"
      >{{$t('auth.next')}}</v-btn>
      <div class="back-login">
      <span @click="cancel" class="txt-link">{{$t('auth.cancelLogin')}}</span>
    </div>
    </div>
  </div>
  </v-modal>
</template>

<script>
import Vue from "vue";
import { mapGetters } from "vuex";
import config from "../../../comm/config.js";
import vTip from "../Auth/common/tooltip.vue";
import vBtn from "../Auth/common/button.vue";
import headerTip from "./HeaderTip.vue" ;
import ActivateMixin from "./ActivateMixins.js";
import vClickOutside from "./../Chat/v-click-outside/index.js";
import { versionCompire, getErrorMsg } from "../../utils/utils.js";
export default {
  mixins:[ActivateMixin],
  components: {
    vTip,
    vBtn,
    headerTip
  },
  directives: {
    clickOutside: vClickOutside.directive
  },
  data() {
    return {
      type:1,
      isLightLine: false,
      isOptionHide: true,
      verifyCode: "",
      regCode: this.$t("auth.getVerifyCode"),
      isLoading: false,
      isCodeLoading: false,
      isCodeSend: false,
      errorMsg: "",
      isErrorBox: false,
      isSuccess: false,
      isGetCodeBtnDisable: false,
      clock: 0,
      registryId:'',
      verifyType: this.$route.query.verifyType,
      verifyField:'',
      accountNum:null,
      fieldValue:{},
      userField:[]
    };
  },
  computed: {
    ...mapGetters([
      "user_account",
      "user_loginInfo",
      "user_localConfig",
      "chat_objectInfo",
      'user_systemConfig',
      'auth_extendedField'
     ]),
   

    // 加载动画显示
    lodingState() {
      return this.isLoading ? "is-loading" : "";
    },

    // 获取验证码等待动画
    codelodingState() {
      return this.isCodeLoading ? "is-loading" : "";
    },

    // 下一步按钮可点击状态
    isDisable() {
     let flag = true;
      for(var i in this.fieldValue){
       if(this.fieldValue[i] === ''){
         flag = false;
         break 
       }
      }
      return flag;
    }
  },
  created() {
    this.server = this.user_loginInfo.server;
    this.account = this.user_loginInfo.account;
    this.type = this.user_loginInfo.userType;
    this.accountNum = this.auth_extendedField.verifyField;
     let accountNumArray = Object.keys(this.accountNum);
      accountNumArray.forEach(element => {
        this.$set(this.fieldValue,element,'');
      });
  },
  methods: {
    next() {
      let verifyParam = {
        accountType: this.user_loginInfo.userType,
        userField:JSON.stringify(this.fieldValue)
      }
      if(this.user_loginInfo.userType === 1){
        this.$set(verifyParam,'account',this.user_loginInfo.nation + this.user_loginInfo.account);
      }else{
        this.$set(verifyParam,'account',this.user_loginInfo.account);
      }
      this.$Service.contact.verifyUserInfoField(verifyParam,
       resp=>{
          if(resp.code === 0){ //验证通过
            console.log('激活账号手机验证:::获取验证码:::验证通过');
            this.$router.push({ path: '/ChangePwd'});
          }
          else{
            this.isSuccess = false;
            this.errorMsg = getErrorMsg(resp.code);
            this.isErrorBox = true;
          }
      });
    }
  }
};
</script>

<style lang="scss" >
@import "./../Auth/_auth";
.router-class{
  .modal-card{
  width: 250px;
 border-radius: 4px;
  }
}

.phone-verify {
  display: flex;
  flex-direction: column;

  height: auto;
  position: relative;
    .phone-verify-page {
    width: 90%;
    margin: 0 auto;
  }
  .auth-tip {
    width: 100%;
    
    // border-bottom: 1px solid $--border-color-blue;
  }
  .input-border {
    border-bottom: none !important;
    border: 0px !important;
    box-shadow: none !important;
    border-radius: 0px;
    border-bottom: 1px solid #aec8d4 !important;
    margin-top:10px 0px;
  }
  input {
    font-size: $--font-size-mid;
  }
   .inputs{
    margin-top: 10px;
   }
  .phone-verify-page {
    .tip-table {
      display: inline-flex;
      justify-content: flex-start;
      position: relative;
      .nation-code {
        display: flex;
        justify-content: flex-start;
        align-items: center;
        padding-left: 8px;
        width: 90px;
        position: relative;
        span {
          color: get-grey-color(base);
        }
        .icon-option {
          top: 5px;
          /* margin-left: 20px; */
          position: absolute;
          right: 4px;
        }
        .line {
          display: inline-block;
          border-left: 1px solid $--border-color-grey;
          height: 15px;
          margin: 0 7px 0 10px;
          position: absolute;
          right: -7px;
        }
      }
      .option-list {
        width: 100%;
        height: 200px;
        background: $--color-white;
        padding: 10px 0;
        // max-height: 200px;
        overflow-y: auto;
        position: absolute;
        right: 0;
        top: 34px;
        border-radius: $--border-radius-base;
        @include z-index(btn);
        .nation-item {
          width: 100%;
          padding: 8px 10px;
          cursor: default;
          &:hover {
            background: get-grey-color(lighten-2);
          }
        }
      }
    }
    .control.has-icons-right .icon.is-right {
      right: 0px;
      width: 85px;
    }
    .ver-code {
      font-size: $--font-size-mid;
      display: inline-block;
      padding-right: 5px;
      padding-top: 6px;
      color: get-grey-color(darken-3);
      background: $--color-white;
      font-family: "\5FAE\8F6F\96C5\9ED1", "Microsoft YaHei", Arial, Helvetica,
        sans-serif, "\5B8B\4F53";
      &:hover {
        background: $--color-white;
        color: get-blue-color(blue);
      }
    }
    .already-account {
      font-size: $--font-size-small;
      justify-content: flex-start;
      padding-left: 68px;
    }
    .auth-button {
      margin: 25px 0 0 0;
    }
    .back-login {
    display: flex;
    justify-content: center;
    padding-top: 15px;
    font-size: $--font-size-mid;
    margin-bottom:13px; 
     span {
       padding: 0 5px;
       cursor: pointer;
     }
    }
  }
}
</style>
