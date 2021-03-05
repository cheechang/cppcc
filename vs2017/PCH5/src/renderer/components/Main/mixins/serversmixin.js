import { mapGetters } from "vuex";
import MultipleServersMixin from '../../Servers/multipleServersMixin'
import { getCurrentDate } from '../../../utils/utils.js'
/**
 * @mixin
 */
const mixin = {
  mixins:[MultipleServersMixin],
  computed:{
    ...mapGetters(['user_loginInfo','user_account','auth_multipleServers','user_usever'])
  },
  data () {
    return {
        loginAccoutInfo:null,
        isAddServer:false,
        isServerList:false,
        serverListTransition:false,
    };
  },
  methods: {
    newMultipleServersMsg(event,msg){
      let userId = msg.senderKey.split('@')[0];
      if(this.auth_multipleServers.hasOwnProperty(userId) && this.auth_multipleServers[userId].isOnline){
        let newInfo = Object.assign({},this.auth_multipleServers[userId]);
        if(msg.subType === 1){
          // 该服务有新消息
          newInfo.isMsg = true;
        }
        else if(msg.subType === 2){
          // 该服务需要退出
          newInfo.isMsg = false;
          newInfo.isOnline = false;
          let key = `${userId}@${this.auth_multipleServers[userId].server}`;
          this.$mutipleServers.exitChildServer([key]);
          this.$dialog.confirm({
            confirmText: this.$t('common.confirm'),
            disableClickOutside: true,
            canCancel:false,
            message: this.$t('auth.exitServerByPhone', {server: this.auth_multipleServers[userId].server,value: getCurrentDate()}),
          });
        }
        this.$store.commit('SET_MULTIPLE_SERVER', {flag: 1, val: newInfo})
      }
    },
    loginServer(info){
      this.loginAccoutInfo = info;
      this.isServerList = false;
      this.isAddServer = true;
    },
    getMultipleServers(){
        // 如果已经有多服务器信息，则不再去拉取(此时该客户端时启动客户端启动的,多服务器信息由主账号发过来)
        if(Object.values(this.auth_multipleServers).length > 0){
          return;
        }
        let multipleServers = this.$Service.config.getSubServerInfo();
        multipleServers.forEach((el,index)=>{
          multipleServers[index].server = el.addr.split('@')[0];
          multipleServers[index].elogo = el.addr.split('@')[1];
          if(this.user_loginInfo.userId === el.userId){
            multipleServers[index].isOnline = true;
          }
        });
        if(multipleServers.length < 2){
          let serverInfo = {};
          serverInfo.server = this.user_loginInfo.server;
          serverInfo.elogo = this.user_usever;
          serverInfo.addr = `${this.user_loginInfo.server}@${this.user_usever}`;
          serverInfo.type = this.user_loginInfo.userType;
          serverInfo.userId = this.user_loginInfo.userId;
          serverInfo.avatar = this.user_account.thumbAvatar;
          if(serverInfo.type === 1 && this.user_loginInfo.nation){
            console.log('this.user_loginInfo:::::',this.user_loginInfo)
            serverInfo.remark = JSON.stringify({nation:this.user_loginInfo.nation})
              //serverInfo.remark = this.user_loginInfo.nation
          }
          serverInfo.account = this.user_loginInfo.account;
          serverInfo.isOnline = true;
          multipleServers= [serverInfo];
        }
        console.log('getMultipleServers:::',multipleServers)
        this.$store.commit('SET_MULTIPLE_SERVER', {flag: 0, val: multipleServers})
    },
    switchToServer(param){
      console.log('param:',param);
      this.isAddServer = false;
      this.isServerList = false;
      setTimeout(()=>{
        this.$mutipleServers.switchToServer(param.key,JSON.stringify(param.info));
      },300)
    },
    showAddServer(){
      this.isAddMenu = false;
      this.loginAccoutInfo=null;
      if(Object.values(this.auth_multipleServers).length > 4){
        this.$toast.open({
          message: this.$t('auth.serverLimit'),
          type: 'is-danger'
        });
        return;
      }
      this.isAddServer = true;
    },
    showServerList(){
        if(!this.isServerList){
          this.isServerList = true;
          setTimeout(()=>{
            this.serverListTransition = true;
          },10)
          
        }
        else{
          this.serverListTransition = false;
          setTimeout(()=>{
            this.isServerList = false;
          },300)
        }
      },
  },
};

export default mixin;