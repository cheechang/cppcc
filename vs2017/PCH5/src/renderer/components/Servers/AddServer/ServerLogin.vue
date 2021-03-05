<template>
    <div class="server-login"><!-- loginAccoutInfo.avatar -->
        <v-avatar class="logo server-login-logo" :sex="6" :shape="'round'" :src="avatar"></v-avatar>
            <!-- 地区码/账号 -->
        <v-input
        class="inputs auth-input server-login-account"
        hasLine
        hasLabel
        v-model="account"
        :isAuth="true"
        :customType="'input-size'"
        :isBorder="false"
        :placeholder="placeholder"
        @input="password=''"
        :maxlength="isNationCode?18:50"
        :disable="!infoCanChange"
        >
        <div slot="auth" v-if="isNationCode" class="auth-icon" :class="[{'icon-account': isNationCode},{'disable-change':!infoCanChange},{'nationCode-position':!infoCanChange}]">
            <div style="width: 100%">
            <v-auto-complete
            class="nation-code"
            ref="vautocomplete"
            v-model="nationCode"
            :data="filteredOptionsArray"
            :originArray="nationArray"
            :placeholder="codePlaceholder"
            hasLine
            :isBorder="false"
            :openOnFocus="true"
            :menuCanShow="isNationShow"
            :isAuth="true"
            @change="active => isNationShow = !active"
            @select="selectedNation"
            >
            </v-auto-complete>
            <i class="icon icon-option" v-if="infoCanChange" :class="{'scale-icon': !isNationShow && infoCanChange}" @click.self.stop="isNationShow=!isNationShow">&#xe77a;</i>
            </div>
        </div>
        </v-input>
        <v-tip
        :isSuccess="isSuccess"
        :tipLabelMsg="errorMsg"
        :isLabelTip="isErrorBox"
        @close="isErrorBox = false"
        class="position-corr  server-login-pwd"
        >
            <v-input
                class="inputs auth-input"
                hasLine
                hasLabel
                ref="passwordInput"
                v-model="password"
                :type="userType==96?'text':'password'"
                :isAuth="true"
                :maxlength="20"
                :inputLineSite="'-1px'"
                :customType="'input-size'"
                :isBorder="false"
                :position="'right'"
                :placeholder="pwdPlacehold"
                :selectPwdShow='true'
                @keyup-enter='login'
            >
              <v-button
                slot="expand"
                v-if="96 === userType"
                class="ver-code"
                :disable="!isCodeDisabled"
                :ripple="false"
                :type="codelodingState"
                @click="onGetVerifyCode"
              >{{regCode}}</v-button>
            </v-input>
        </v-tip>
        <v-btn
            class="auth-button server-login-btn"
            :size="'v-button--max_width'"
            :disable="isDisable"
            :type="lodingState"
            @click="login"
            >{{$t('auth.signin')}}
        </v-btn>
        <div
            class="more-button-layout other-login"
            v-if="infoCanChange"
         >
            <span class="txt-link back"  @click="$emit('goBack')">{{$t('auth.goBack')}}</span>
            <span class="txt-link login-type" @click.self.stop="chooseLoginType" v-if="this.loginTypes.length>1">
                {{$t('auth.otherLoginWay')}}
                <i class="icon xe678" :class="{'scale-xe678': isExpend}">&#xe678;</i>
            </span>
            <list
                :zoomInTop = true
                :listData="loginTypes"
                :isShow="isExpend"
                :selectedIndex="userType"
                @close-select-list="closeSelscList"
                @select-item="selectItem"
                class="list-size"
            ></list>
        </div>
        <!-- 验证码弹框 -->
        <div v-if="isVerfyShow">
          <verfy-code
            :nation="auth_nationCode"
            :account="account"
            :userType="userType"
            :img="verifyImg"
            :multiPleServers = true
            @verfy="isVerfyShow=false"
          ></verfy-code>
        </div>
    </div>
</template>
<script>
import vBtn from '../../Auth/common/button.vue';
import vTip from '../../Auth/common/tooltip.vue';
import List from '../../Auth/common/list.vue';
import VerfyCode from '../../Auth/Verfy/VerfyCode.vue';
import serverLoginMixin from './serverLoginMixin'
import { mapGetters } from 'vuex';
export default {
  mixins:[serverLoginMixin],
  components: {
      vBtn,
      vTip,
      List,
      VerfyCode,
  },
  props:{
      elogo:String,
      loginTypes:Array,
      server:String,
      loginAccoutInfo:Object
  },
}
</script>
<style lang="scss" scoped>
@import '../../Auth/_auth';
.server-login{
    height: 100%;
    width: 280px;
    display: flex;
    flex-direction: column;
    font-size: $--font-size-mid;
    position: fixed;
    .disable-change{
        pointer-events: none;
    }
    .server-login-account{
        top:115px;
        /deep/ .input{
            font-size: $--font-size-mid;
        }
    }
    .server-login-logo{
        top:5px;
    }
    .server-login-btn{
        top:135px;
    }
    .server-login-pwd{
        top:115px;
        /deep/ .input{
            font-size: $--font-size-mid;
        }
    }
    .auth-font{
        font-size: $--font-size-mid;
        line-height: 2.0;
    }
    .icon-account{
        // min-width: 45px;
        max-width: 100px;
        position: relative;
        display: inline-flex;
        align-items: center;
        .nation-code{
            top: 0px!important;
            left: 0px!important;
            font-size: $--font-size-mid;
            color: get-grey-color(base);
            font-family: '\5FAE\8F6F\96C5\9ED1', 'Microsoft YaHei', Arial, Helvetica, sans-serif, '\5B8B\4F53';
            /deep/ .control .input{
                width: 100px;
                padding: calc(0.375em - 1px) calc(0.625em - 4px)!important;
                color: get-grey-color(base)!important;
            }
            /deep/ .dropdown-menu{
                max-width: 300%!important;
                .dropdown-item{
                padding: 0.375rem 1rem;
                }
            }
        }
        .icon-option{
            position: absolute;
            right: 0px;
            height: 100%;
            width: auto;
            @include z-index(btn);
            transition: .5s;
            pointer-events: auto;
            color: #9E9E9E;
            &.scale-icon{
                transform: rotate(180deg);
                transform-origin: 50% 50%;
                transition: 0.3s;
            }
            &:hover{
                cursor: pointer;
            }
        }
    }
    .nationCode-position{
        width: 45px;
    }
    .other-login{
        position: relative;
        top:145px;
        //justify-content: space-between;
        .list-size{
            max-height: 108px;
            overflow-y: auto;
            color: rgba(10, 10, 10, 0.66);
            top: 45px;
            position: absolute;
        }
        .back{
            width: 100%;
            display: flex;
            justify-content: flex-start;
        }
        .login-type{
            width: 100%;
            display: flex;
            justify-content: flex-end;
        }
  }
  .ver-code{
    right: 20px;
    font-size: $--font-size-mid;
    display: inline-block;
    padding-right: 5px;
    color: get-grey-color(darken-3);
    background: $--color-white;
    font-family: '\5FAE\8F6F\96C5\9ED1', 'Microsoft YaHei', Arial, Helvetica, sans-serif, '\5B8B\4F53';
    &:hover{
      background: $--color-white;
      color: get-grey-color(darken-3);
    }
  } 
    
}

</style>