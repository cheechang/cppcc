<template>
  <div class="home-detail" :class="{'default-page':!homeUrl}">
    <!-- <webview class="home-url" :preload="getJssdkPath()" nodeintegration :src="homeUrl" autosize="on"></webview> -->
    <Submenu
            class="model-container-left chat-list theme-left-bgc"
            :menuList="menuList"
            :active="active"
            @toParent="getHomeUrl"
    ></Submenu>
    <div class="home-detail-content">
      <div :class="{'home-detail-top-win':!$is.isOSX}" ></div>
      <webview class="home-url" :src="homeUrl" nodeintegration autosize="on" :style="{height:!$is.isOSX? 'calc(100% - 27px)':'100%'}"></webview>
    </div>
    <!-- <v-button class="is-loading is-large" :ripple="false" v-if="isLoading"></v-button>  -->
    <contact-info v-if='isShowContactInfo' @close="isShowContactInfo=false"></contact-info>
  </div>
</template>
<script>
import { resolve } from 'path';
import ContactMixin from '../Contact/ContactMixin.js'
import Submenu from './Submenu.vue';
import axios from 'axios';
import { mapGetters } from 'vuex';
import contactInfo from '../Group/ChatGroupInfo/ChatMemberInfo'
export default {
  name: 'HomePage',
  data() {
    return {
      homeUrl: '',
      active:'',
      menuList:[],
      isLoading: true,
      isShowContactInfo:false
    }
  },
  created() {
    this.getMenu();
  },
  computed: {
    ...mapGetters([
      'chat_chatList',
    ])
  },
  methods:{
    //获取处理jquery和electron的冲突处理文件路径
    // getJssdkPath(){
    //   return this.$is.isDev
    //     ?
    //     (this.$is.isOSX ? `${this.$osxDirPath}/`+'node_modules/vrv-static/plugins/doodexplorer/static/js/vrv-jssdk.js' : resolve(__dirname, '../../../../node_modules/vrv-static/plugins/doodexplorer/static/js/vrv-jssdk.js', '') )
    //     :
    //     __dirname+'/node_modules/vrv-static/plugins/doodexplorer/static/js/vrv-jssdk.js';
    // }
    getMenu(){
      axios.get(`http://${this.$config.clientConfig.auth.webServer}/cppcc-management/api/appWeight/order`, {
        params: { type: '1' }
      }).then(res=>{
        let config = JSON.parse(localStorage.getItem('loginInfoPc'));
        if (config.authorities) {
          for (let i = 0; i < config.authorities.length; i++) {
            if (config.authorities[i].app) {
              config.authorities = config.authorities[i].app;
              break;
            }
          }
        }
        const authMenus = [{
          "pid" : "00",
          "functionCode" : "First",
          "functionName" : "首页",
        }];
        res.data.data&&res.data.data.forEach((menu) => {
          const path = menu.functionCode;
          if (config.authorities.indexOf(path) !== -1) {
            const auth = [];
            config.authorities && config.authorities.forEach((item) => {
              if (item && item.indexOf(path + "/") === 0) {
                auth.push(item.substring(path.length + 1));
              }
            });
            menu.auth = auth;
            authMenus.push(menu);
          }
        });
        this.menuList=authMenus;
        this.active=this.menuList[0].functionCode;
        this.homeUrl=`file:///${this.$is.isDev?'':__dirname+'/'}pcdist/index.html?window=home&path=${this.menuList[0].functionCode}`;
        }).catch(error=>{
          console.log(error);
        })
    },
    getHomeUrl(data){
      console.log(data);
      this.active = data.functionCode
      this.homeUrl =data.homeUrl;
    },
    // * 查看联系人信息
    seeContactInfo(id) {
      this.isShowContactInfo = true
      this.$nextTick(() => {
        let memberInfo = this.contact_contactList[id]
        if (memberInfo) {
          this.$signalMonitor.$emit('expendChatMemberInfo', memberInfo);
        } else {
          let getUserInfoParam = { userId: id }
          let getUserInfoCb = successRes => {
            memberInfo = successRes.users;
            this.$signalMonitor.$emit('expendChatMemberInfo', memberInfo);
          }
          this.$Service.search.getUserInfo(getUserInfoParam, getUserInfoCb)
        }
      })
    }
  },
  components: {
    Submenu,
    contactInfo
  },
  mounted() {
    let webview = document.querySelector('webview');
    webview.addEventListener('ipc-message',(e)=>{
      console.log(e,"webview发过来的消息"); //可以
      console.log(e.channel,"webview发过来的消息"); //可以
      if(e.channel.openUrl70){
        this.homeUrl = e.channel.openUrl70;
      }else if(e.channel.userName){
        this.seeContactInfo(e.channel.userName);
      }else if(e.channel.unreadCountBook){
        let currentChat = this.chat_chatList[e.channel.unreadCountBook]; //获取群未读消息
        console.log(currentChat,"pc");
        webview.send('unreadCountBook',currentChat)
      } else {
        this.startChat(e.channel.item, 2) //入群
      }
    })
    webview.addEventListener('dom-ready',()=>{
      this.$is.isDev&&webview.openDevTools();
      let config = localStorage.getItem('loginInfoPc');
      webview.send('webParent',config)
    })
    // const loadstart = () => {
    //   console.log('...start')
    //   this.isLoading = true;
    // }

    // const loadstop = () => {
    //   console.log('...stop')
    //   this.isLoading = false;
    //   webview.openDevTools();
    //   console.log('this.jssdkPath:',this.jssdkPath);
    // }

    // webview.addEventListener('did-start-loading', loadstart)
    //webview.addEventListener('did-stop-loading', loadstop)
  },
  mixins: [ContactMixin]
}
</script>

<style lang="scss">
.home-detail {
  width: calc(100% - 55px);
  display: flex;
  .model-container-left{
    width: 226px;
  }
  .home-url {
    width: 100%;
    height: 100%;
    background: #fff;
  }
  .home-detail-top-win{
    width: calc(100% - 100px);
    height: 27px;
    -webkit-app-region: drag;
  }
  .home-detail-content{
    width: calc(100% - 55px);
  }
}
.default-page {
  background: url('~vrv-static/resources/images/common/404page.jpg') no-repeat #fff;
  background-size: contain;
}
// .is-loading {
//   width: 100%;
//   height: 100%;
//   position: absolute;
//   background: #fff;
// }
</style>

