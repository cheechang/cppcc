/**
 * @file      Manages the DDIO's common methods for the main page.
 * @author    linpeiyuan <linpeiyuan@vrvmail.com.cn>
 * @date      2019.10.14
 * @copyright Beijing VRV Software Co.,Ltd
 * 
 * @mixin
 */
import ContactMixin from '../../Contact/ContactMixin.js';
const mixin = {
  mixins: [ContactMixin],
  data () {
    return {
      ddioHandler: [null, 
                    this._ddioOpenChat, 
                    this._ddioMainPage,
                    this._ddioOpenApp,
                    this._ddioBuy,
                    this._ddioInviteFriend]
    };
  },
  methods: {
    _ddioOpenChat(info) {
      this.$router.push({ path: '/Chat' });
      let type =  this.$Service.config.getUserTypeById({ targetId: info.chatId });
      const CHAT_TYPE_BUDDY = 1,
            CHAT_TYPE_GROUP = 2,
            CHAT_TYPE_APP = 3;
      switch (type) {
        case CHAT_TYPE_BUDDY: {
          this.$Service.search.getUserInfo({userId:info.chatId},resp=>{
            this.startChat(resp.users,type);
          });
          break;
        }
        case CHAT_TYPE_GROUP: {
          this.$Service.search.getGroupInfo({groupId:info.chatId},resp=>{
            this.startChat(resp.group,type);
          });
          break;
        }
        case CHAT_TYPE_APP: {
          this.$Service.user.getAppInfo({appId:info.chatId},resp=>{
            this.startChat(resp.group,type);
          });
          break;
        }
      }
    },

    _ddioMainPage(info) {
      //主界面跳转路由
      let routerList = ['/HomePage','/Chat','/Contact','/work'];
      let hideHomePage = (this.user_systemConfig & 4) != 1<<2;
      if(hideHomePage){
        routerList.splice(0,1);
      }
      let hideAppStore = (this.user_systemConfig & 16) != 1<<4
      if(hideAppStore){
        routerList.splice(routerList.length-1,1);
      }
      this.$router.push({ path: routerList[info.index] });
      setTimeout(()=>{
        this.$signalMonitor.$emit('toChatPage'); // 发送信号：导航栏选中会话图标
      },300)
    },

    _ddioOpenApp(info) {
      this.appNewWindowByVestAppID(info.vestAppID)
    },

    _ddioBuy(info) {
      //邀请好友购买服务器
      const url = 'vrv-static/plugins/inviteBuyServer/index.html'
      this.$ipc.send('new-window', {
       winUrl:url, 
       winType:'Imagepreivew', 
     // winTitle:'图片预览',
       winTitle:`${this.$t('chat.buyServer')}`,
       shapeType:'normal',
     })
    },

    _ddioInviteFriend(info) {
      //  TODO: 未想好此处属性共用
      this.defaultLeftTab = 'InviteFriend';
      this.isAccountCenter = true;
    }
  },
};

export default mixin;