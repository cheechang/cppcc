<template>
  <div class="home-detail" :class="{'default-page':!homeUrl}">
    <div class="home-detail-content">
      <div :class="{'home-detail-top-win':!$is.isOSX}"></div>
      <!--<iframe :src="homeUrl"></iframe>-->
      <webview class="home-url" disablewebsecurity nodeintegration :src="homeUrl" autosize="on" :style="{height:!$is.isOSX? 'calc(100% - 27px)':'100%'}"></webview>
    </div>
    <!-- <v-button class="is-loading is-large" :ripple="false" v-if="isLoading"></v-button>  -->
  </div>
</template>
<script>
import { resolve } from 'path';
import ContactMixin from '../Contact/ContactMixin.js'
export default {
  name: 'HomePage',
  data() {
    return {
      homeUrl: '',
      isLoading: true
    }
  },
  created() {
    this.homeUrl = `file:///${this.$is.isDev?'':__dirname+'/'}pcdist/index.html?window=user&path=MyDuty`;
  },
  methods:{
    // 获取处理jquery和electron的冲突处理文件路径
    // getJssdkPath(){
    //   return this.$is.isDev
    //     ?
    //     (this.$is.isOSX ? `${this.$osxDirPath}/`+'node_modules/vrv-static/plugins/doodexplorer/static/js/vrv-jssdk.js' : resolve(__dirname, '../../../../node_modules/vrv-static/plugins/doodexplorer/static/js/vrv-jssdk.js', '') )
    //     :
    //     __dirname+'/node_modules/vrv-static/plugins/doodexplorer/static/js/vrv-jssdk.js';
    // }
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
  mounted() {
    let webview = document.querySelector('webview');
    webview.addEventListener('ipc-message',(e)=>{
      console.log(e,"webview发过来的消息"); //可以
      console.log(e.channel,"webview发过来的消息"); //可以
      if(e.channel.openUrl70){
        this.homeUrl = e.channel.openUrl70;
      }else if(e.channel.userName){
        this.seeContactInfo(e.channel.userName);
      }else {
        this.startChat(e.channel.item, 2)
      }
    })
    webview.addEventListener('dom-ready',()=>{
      this.$is.isDev&&webview.openDevTools();
    })
  },
  mixins: [ContactMixin]
}
</script>

<style lang="scss">
.home-detail {
  width: 100%;
  /*height: calc(100% - 55px);*/
  display: flex;
  .home-detail-top-win{
    width: calc(100% - 100px);
    height: 27px;
    -webkit-app-region: drag;
  }
  .home-detail-content{
    width: 100%;
  }
  .home-url {
    width: 100%;
    height: 100%;
    background: #fff;
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