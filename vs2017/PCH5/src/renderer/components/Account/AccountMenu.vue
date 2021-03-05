<template>
  <div class="menu-user-info">
    <div class="menu-background" @click="$emit('close')"></div>
    <div class="menu-dropdown" :style="{top:MaxWindow?'55px':'', left:MaxWindow?'1px':''}">
      <div class="menu">
        <div class="menu-list" :style="{padding:'8px 0px 8px 0px'}">
          <span class="menu-item hover-color" @click="opneUserAccount">
            <i class="icon">&#xea27;</i>
            <span :style="{paddingLeft: '8px'}">{{$t('user.personalCenter')}}</span>
            <span v-if="auth_loginByForgetPwd.isForgetPwdLogin" class="forget-pwd-tip"></span>
          </span>
        </div>
        <div class="menu-list">
          <div v-for="(item,index) in menuList" :key="index" @mouseover="hoverEvent(item)">
            <span class="menu-item hover-color" @click="clickEvent(item)" :style="{borderBottom: index == 1 ? '1px solid #eeeeee' : 'none'}">
              <i class="icon" v-html="item.icon" :style="{color:item.color}"></i>
              <span class="text">{{item.name}}</span>
              <i class="icon" v-if="item.key===1" :style="{fontSize:'8px'}">&#xe613;</i>
            </span>
          </div>
        </div>
      </div>
      <div class="sub-menu" :style="isSubMenuDisplay" @mouseleave="isMenuShow = false">
        <div v-for="(item,index) in statusList" :key="index">
          <span class="menu-item hover-color" @click="clickStatusEvent(item)">
            <i class="icon" v-html="item.icon" :style="{color:item.color}"></i>
            <span class="text">{{item.name}}</span>
          </span>
        </div>
      </div>
    </div>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import userMixin from './AccountMixin.js'
import ContactMixin from '../Contact/ContactMixin.js'
import { getErrorMsg,getOnlineStatusInfo} from '../../utils/utils.js';
import { connect } from 'tls';
export default {
  name: 'account-menu',
  mixins: [userMixin,ContactMixin],
  data() {
    return {
      // 一级菜单
      defaultMenuList:[
        {key:2,name:this.$t('user.sysMsg'),icon:'&#xe6b6;',color:''},
        {key:3,name:this.$t('setting.about'),icon:'&#xe692;',color:''},
        {key:4,name:this.$t('user.logout'),icon:'',color:''},
        {key:5,name:this.$t('user.exit'),icon:'',color:''},
      ],
      //1:在线,2:隐身,3:忙碌,4:离开,5:请勿打扰
      statusList:[
        {key:1,name:this.$t('user.online'),icon:'&#xe62f;',color:'#57E26D'},
        {key:2,name:this.$t('user.invisible'),icon:'&#xe7ac;',color:'#FEC13E'},
        {key:3,name:this.$t('user.busy'),icon:'&#xe7a0;',color:'#F94A2B'},
        {key:4,name:this.$t('user.offline'),icon:'&#xe60d;',color:'#AEAEAE'},
        {key:5,name:this.$t('user.disturb'),icon:'&#xe6e0;',color:'#E65645'},
      ],
      isMenuShow: false
    };
  },
  props: {
    MaxWindow: Boolean
  },
  computed: {
    ...mapGetters(['user_account', 'auth_loginByForgetPwd','auth_onlineStatus']),
    isSubMenuDisplay() {
      return {display: this.isMenuShow?'block':'none'}
    },
    menuList(){
      // 暂时将 在线状态屏蔽
      // if(this.$config.account.openOnlineStatus){
      //   let onlineStatus = Object.assign({},getOnlineStatusInfo(this.auth_onlineStatus));
      //    if(onlineStatus){
      //      let tempList =[...this.defaultMenuList];
      //      onlineStatus.key = 1;
      //      tempList.splice(0, 0, onlineStatus);
      //      return tempList;
      //    }
      // }
      return this.defaultMenuList;
    }
    
  },
  methods: {
    // 点击选中后关闭用户下拉列表
    selectHide() {
      let accountMenu = document.getElementsByClassName('menu-user-info')[0];
      accountMenu.style.display = 'none';
    },
    /**
     * 跳转到用户账户页面
     */
    opneUserAccount(){
      this.selectHide();
      this.$emit('close');
      console.log('account-menu');
      this.$emit('show-account', 'UserInfo');
    },
    /**
     * 鼠标滑过
     */
    hoverEvent(item) {
      // if(item.key === 1){
      //   this.isMenuShow = true;
      // }
      this.isMenuShow = item.key === 1;
      //[this.indexItem, this.isMenuShow] = [index, index === 5];
    },
    /**
     * 用户下拉列表操作
     */
    clickEvent(item) {
      switch (item.name) {
        case this.$t('user.sysMsg'): { this.systemMsg(); break }
        case this.$t('setting.about'): { this.openAbout(); break }
        case this.$t('user.online'): { this.onlineStatus(); break }
        case this.$t('user.logout'): { this.logout(); break }
        case this.$t('user.exit'): { this.quit(); break }
      };
      this.selectHide();
      this.$emit('close');
    },
    systemMsg(){
      this.$emit('animation-start');
      let systemObj = {
        id:'10000',
        name:this.$t('user.sysMsg'),
        chatType:1,
        msgTime: new Date().getTime(),
        lastMsg:'',
        delSign: '',
        subType: 1,
        whereFrom: '',
        isTop: 0,
        msgType: 2,

      }
      this.$store.commit('PUSH_CHATLIST',systemObj );
      this.$router.push({path: '/ChatSystem', query: { id: '10000', name: this.$t('user.sysMsg')}});
    },
    /** 转到系统消息, 暂时设置为跳转到关于页面 */
    openAbout() {
      this.$emit('show-account', 'AboutDood');
    },

    /** 打开在线状态设置 */
    onlineStatus() {
      console.log('在线状态');
    },

    /** 在线状态设置 */
    clickStatusEvent(item){
      console.log(item)
      this.$store.commit('SET_ONLINE_STATUS', item.key);
      this.$Service.user.setOnlineState({flag:item.key},resp=>{
        console.log('setOnlineStateResult:',resp);
      });
      this.isMenuShow = false;
    }
  }
};
</script>
<style lang="scss" scoped>
.menu-user-info {
  width: 160px;
  bottom: 0;
  left: 0px;
  right: 0;
  top: 43px;
  position: absolute;
  @include z-index(menu);
  .menu-background {
    bottom: 0;
    height: 100%;
    width: 100%;
    left: 0;
    position: fixed;
    right: 0;
    // -webkit-app-region: no-drag;
    overflow: hidden;
  }
  .menu-dropdown {
    position: absolute;
    display: flex;
    top: 12px;
    left: 0;
    @include z-index(menu);
    margin-top: -10px;
    padding-top: 10px;
    .menu {
      width: 160px;
      background: $--color-white;
      flex-direction: column;
      display: flex;
      box-shadow: $--box-shadow-rd;
      .menu-header {
        cursor: pointer;
        display: flex;
        align-items: center;
        padding-left: 10px;
        color: $--color-black;
        font-size: $--font-size-big;
        height: 55px;
      }
      .menu-list {
        color:$--color-black;
        border-top: 1px solid $--border-color-grey-lighten;
        padding: 0px 0px 8px 0px;
        .menu-item {
          cursor: pointer;
          padding: 5px 0px 5px 6px;
          font-size: $--font-size-mid;
          display: flex;
          height: 40px;
          line-height: 40px;
          align-items: center;
          .forget-pwd-tip{
            top: 35px;
            left: 145px;
          }
          &:hover {
            background: $--color-hover;
          }
          i {
            display: flex;
            color: get-grey-color(darken-3);
          }
          .text {
            flex: 1;
            margin-left: 8px;
          }
        }
      }
    }
    .sub-menu {
      position: relative;
      background: $--color-white;
      display: flex;
      // display: none;
      box-shadow: $--box-shadow-elevation;
      flex-direction: column;
      align-items: center;
      top: 58px;
      height: 200px;
      margin-left: 3px;
      border-radius: $--border-radius-base;
      overflow: hidden;
      .menu-item {
        cursor: context-menu;
        padding: 5px 0px 5px 6px;
        font-size: $--font-size-mid;
        flex: 1;
        width: 130px;
        display: flex;
        height: 40px;
        line-height: 40px;
        align-items: center;
        &:hover {
          background: $--color-hover;
        }
        i {
          display: flex;
          color: $--icon-color-primary;
        }
        .text {
          flex: 1;
          margin-left: 8px;
        }
      }
    }
  }
}
</style>
