<template>
  <div class="account-security">
  <!--  <div class="style-margin">{{$t('setting.boundChange')}}:</div>
    <div class="account-security-content">
    // 更改绑定手机号 
      <div class="style-margin">
        {{$t('auth.phone')}}:
      </div>
     
        <v-field class="fields">
          <input class="input-style" type="text" placeholder="绑定手机号">
        </v-field>
     
      // 更改绑定邮箱号 
      <div class="style-margin">
        {{$t('auth.email')}}:
      </div>
      <v-field class="fields">
        <input class="input-style" type="text" placeholder="绑定邮箱号">
      </v-field>
      <v-button class="confirm-change"
        :class="{'theme-botton':true}"
        
        >功能暂未实现</v-button>
    </div> -->
    <!-- 修改密码 -->
    <div class="subject">
      {{$t('account.changePwd')}}:
      <span
        v-if="auth_loginByForgetPwd.isForgetPwdLogin"
        class="change-pwd-tip"
      >*{{$t('account.plchangePwd')}}</span>
    </div>
    <div class="change-password same">
      <change-password></change-password>
    </div>
    <!-- 登录设备管理 -->
    <div class="subject cutting-line-before">
      {{$t('user.loginEquipmentMgt')}}:
    </div>
    <div class="same accounts-manage">
      <div @click.stop="openAccountsManage" class="clear-chart-btn theme-botton accounts-manage-button">{{$t('user.viewLogonDevice')}}</div>
    </div>
    <accountManagemt  v-if="isShowModal" @handleCancel="handleCancel"></accountManagemt>
  </div>
</template>
<script>
import { mapGetters } from "vuex";
import accountManagemt from './AccountManagemt.vue';
import changePassword from "./ChangePwd.vue";
import {getConfig,setConfig} from '../../../../../comm/util';
import _ from 'lodash';
export default {
 data() {
   return {
     isShowModal: false,
   }
 },
  computed: {
    ...mapGetters([ "auth_loginByForgetPwd"]),
  },
  components: {
    changePassword,
    accountManagemt
  },
   methods: {
     openAccountsManage(){
       this.isShowModal = true;
     },
     handleCancel(){
       this.isShowModal = false;
     }
   }
};
</script>
<style lang="scss" scoped>
.account-security-content{
  padding: 0px 0 10px 95px;
  .fields{
		width: 35%;
		position: relative;
    .input-style {
			height: 30px;
			width: 35%;
			border: 0;
			border-radius: $--border-radius-base;
			outline: none;
			background: #d3d3d3;
			padding-left: 10px;
			font-size: $--font-size-small;
      }
    }
    .confirm-change {
      height: 30px;
			color: $--color-white;
			width: 100px;
      padding: 5px 10px !important;
      margin-top:5px; 
			text-align: center;
			border: 0;
      outline: none;
      font-size: $--font-size-mid;
			border-radius: $--border-radius-base;
		}
}
.account-security {
  width: 100%;
  background: #fff;
  padding: 15px;
  font-size: $--font-size-mid;
  padding-top: 15px;
  height: 100%;
  border-radius: $--border-radius-base;
  overflow: hidden;
  &:hover {
    overflow-y: auto;
  }
  &::-webkit-scrollbar {
    display: none;
  }
  .style-margin{
    margin:5px 0;
  }
  .subject {
    div {
      padding-bottom: 5px;
    }
    .change-pwd-tip {
      color: $--color-danger;
      padding-left: 30px;
    }
  }
   .same {
    padding-left: 95px;
    div {
      padding: 3px 0;
    }
  }
  .accounts-manage{
    margin-top: 13px;
    padding-left: 86px;
    .accounts-manage-button{
      padding: 5px 10px;
    }
  }

}
</style>
