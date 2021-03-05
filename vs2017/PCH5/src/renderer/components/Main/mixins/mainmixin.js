/**
 * @file      主界面通用业务方法.
 * @author    linpeiyuan <linpeiyuan@vrvmail.com.cn>
 * @date      2019.9.10
 * @copyright Beijing VRV Software Co.,Ltd
 * 
 * @mixin
 */
import { mapGetters } from 'vuex';
import ChatMixin from './chatmixin';
import UserMixin from './usermixin';
import ContactMixin from './contactmixin';
import GroupMixin from './groupmixin';
import ServerMixin from './serversmixin.js';
import OAuthMixin from './oauthmixin';
import DDIOMixin from './ddiomixin';
import RtcMixin from './rtcmixin';
const mixin = {
  mixins: [ChatMixin, UserMixin, ContactMixin, GroupMixin, OAuthMixin, DDIOMixin, RtcMixin,ServerMixin],
  data () {
    return {
      isAddMenu: false,
      currentPos: {
        top: String,
        left: String
      },
      isActivate: false,    //  账号激活控制
      bannedRouteType: ['RTCP2P', 'RemoteControl', 'RtcFile', 'MultiMeeting']
    }
  },
  computed: {
    ...mapGetters([
      'auth_server',
      'user_loginInfo',
      'user_waterMark',
      'user_darkWaterMark'
    ]),
    computedWaterMark(){
      return {
        background:`url(${this.user_waterMark})`
      } 
    },
    showWatermark(){
       // 如果打开个人中心，或者当前路由不是工作台和首页，则显示水印
      return (
        this.isAccountCenter || (
        this.$route.name !== 'MyApp' &&
        this.$route.name !== 'SearchList' &&
        this.$route.name !== 'AppStore' &&
        this.$route.name !== 'HomePage')
        )
    },
    getThemeImage() {
      return this.user_waterMark ? 'theme-mark-bg-box' : 'theme-bg-box';
    },
  },
  watch: {
    user_account: {
      handler(newVal, oldVal) {
        //  更新对应的数据
        if (newVal.headpath !== oldVal.headpath) {
          this._updateSessionsAvatar(newVal.headpath);
          //this._updataMultipleServerAvatar(newVal.userId,newVal.headpath);
        }
        if (newVal.name !== oldVal.name || newVal.phone !== oldVal.phone) {
          this.getWaterMark();
        }
      },
      deep: true
    }
  },
  methods: {
    /**
     * @breif 是否强制使用本服务器地址：获取二维码信息的的HOST部分
     */
    getEnterpriseDicValue() {
      this.queryExtendedField(68, 'isLocalHost', flagRes => {
        let qrhost = flagRes === '1' ? `http://${this.auth_server}` : `http://im.linkdood.${this.$initInfo.mark === 'inte' ? 'com' : 'cn'}`;
        this.$store.commit("SET_ENTDICVALUE", {dicKey: 'isLocalHost', value: qrhost});
      })
    },
    /**
     * @breif 是否允许图片另存为
     */
    getImgSaveAsDicValue() {
      this.queryExtendedField(68, 'isSavePicturesToAlbums', flagRes => {
        this.$store.commit("SET_IMG_DICVALUE", {dicKey: 'isSavePicturesToAlbums', value: flagRes});
      })
    },
    /**
     * @breif 是否允许第三方应用打开豆豆中的文档（备注：暂时默认开启，不再根据服务后台配置）
     */
    getFileOpenDicValue() {
      // this.queryExtendedField(68, 'isOpenInOtherApp', flagRes => {
        this.$store.commit("SET_FILE_DICVALUE", {dicKey: 'isOpenInOtherApp', value: "1"});
      // })
    },
    /**
     * @breif 获取后台配置的文件直传大小
     */
    _getP2pFileSize() {
      this.queryExtendedField(0, 'p2pSize', flagRes => {
        let filesize = 500;
        filesize = Number(flagRes);
        this.$store.commit('SET_RTC_FILESIZE', filesize)
      })
    },
    /**
     * @breif 根据条件查询后台配置的数据字典信息
     * @param {Number} parentId
     * @param {String} dickey - 键
     */
    queryExtendedField(parentId, dickey, callback) {
      this.$Service.contact.queryExtendedField({parentId, dickey}, resp => {
        console.log(`get ${dickey} resp: `, resp);
        this.$Service.log(`queryExtendedFieldSync:::${resp.code}`);
        for (let item of resp.EnterpriseDictionarys) {
          if (item.dickey !== dickey) {
            continue;
          }
          //  获取值
          callback(item.extend);
          console.log(`get ${dickey}: `, item);
          this.$Service.log(`获取${dickey}:::${JSON.stringify(item)}`);
        }
      });
    },

    /**
     * @breif 在主界面注册的所有通知在此调用
     */
    regNotifer() {
      this.$store.commit('SET_ONLINE_STATUS', 1);
      this.regNetChangedCb();
      this.regMainEvent();
      this.regUserNotify();
      this.regContactNotify();
      this.regGroupNotify();
      this.regChatNotify();
    },

    /**
     * @breif 网络变化通知推送
     * @param {object} - resp state为0表示网络正常，-1为网络异常，需要显示断线重连
     */
    regNetChangedCb() {
      this.$Service.auth.regNetChangedCb(null, resp => {
        //  修改vuex的网络状态，显示/隐藏断线重连通知
        this.$store.commit('SET_NETSTATE', resp.state);
        //  将在校状态通知给其他子窗口
        this.$ipc.send('subWin-netstatus-app', resp.state === 0);

        //  如果离线则会显示托盘通知
        if (resp.state === 0) {
          return;
        }
        let notifyInfo = {
          title: this.$t('common.netError'),
          body: this.$t('common.connecting')
        }
        this.$ipc.send('netChanged', notifyInfo);
      });
    },

    /**
     * @breif 在主界面注册的与主进程通信的IPC事件
     */
    regMainEvent() {
      if (this.bannedRouteType.includes(this.$route.name)) return;
      this.$ipc.once('before-log-out', event => {
        this.logoutSDK();
        this.$router.push({ path: '/Auth' });
        this.delTempFiles();
        this.$ipc.send('tray-logout');
        localStorage.removeItem('is-regDialog');
      });

      /** 注销时销毁子窗口 */
      this.$ipc.once('cancelOperate', (e, args) => {
        this.$ipc.send('close-all-subWin');
      });

      /** 压缩意见反馈日志 */
      this.$ipc.on('forward-file', this.forwardFile);
      this.$ipc.on('send-zip-file', this.onSendZipFile);
      this.$ipc.on('logout-or-quit', this.logoutOrQuit);
      this.$ipc.on('window-focus', this.onWindowFocus);
      this.$ipc.on('plugin-notify', this.onRtcPluginNotify);
            /** 处理jssdk抛出的信号 */
      this.$ipc.on('jumpRouterFromDDIO',this.dealJumpRouterFromDDIO);
      this.$ipc.on('openChatByNotification',this.openChatByNotification);
      this.$ipc.on('multipleServersNewMsg',this.newMultipleServersMsg)
    },

    getHttpHead() {
      let serverParam = { server: this.user_loginInfo.server };
      this.$Service.config.getMultiChannelAddressAsync(serverParam, resp => {
        console.log(resp, '多通道服务器地址');
        if (resp === {}) {
          return;
        }
        this.$store.commit('SET_HTTPHEAD', resp);
      });
      this.$Service.auth.getSecUrl(serverParam, resp => {
        console.log(resp, '预登录地址');
        this.$store.commit('SET_HTTPHEAD', { preLoginAddress: resp.value });
        console.log(this.http_head, '多通道vuex');
      });
    },

    afterMounted() {
      //  阻止浏览器默认拖拽事件
      this.$nextTick(() => {
        document.addEventListener('drop', e => {
          e.preventDefault();
        });
        document.addEventListener('dragleave', e => {
          e.preventDefault();
        });
        document.addEventListener('dragenter', e => {
          e.preventDefault();
        });
        document.addEventListener('dragover', e => {
          e.preventDefault();
        });
      });

      /** 获取预登录地址/多通道地址 */
      this.getHttpHead();
      // /** 获取用户本地配置 */
      this.getUserLocalConfig();
      // // 获取商店信息
      // this.getAppStore();

      this.getContactList();

      this.getGroupList();
      
      this.getMultipleServers();

      this.getWaterMark()

    },

    afterCreated() {
      this.initChat();
      this.regNotifer();
      this.getEnterpriseDicValue();
      this.getImgSaveAsDicValue();
      this.getFileOpenDicValue();
      //获取配置文件中，文件直传时文件大小
      this._getP2pFileSize();
      if(this.$route.query.loginCode === 1303){
        console.log('进入1303：：：：：：');
        this.isActivate = true;
      }
    },

    removeEvent() {
      this.$ipc.removeListener('forward-file', this.forwardFile)
      this.$ipc.removeListener('send-zip-file', this.onSendZipFile)
      this.$ipc.removeListener('logout-or-quit', this.logoutOrQuit)
      this.$ipc.removeListener('window-focus', this.onWindowFocus) 
      this.$ipc.removeListener('plugin-notify', this.onRtcPluginNotify) 
      this.$ipc.removeListener('jumpRouterFromDDIO', this.dealJumpRouterFromDDIO)
      this.$ipc.removeListener('openChatByNotification',this.openChatByNotification)
      this.$ipc.removeListener('multipleServersNewMsg', this.newMultipleServersMsg)
    },

    // 处理用户点击通知抛出的信号
    openChatByNotification(e,args){
      this.hideAccountCenter();
      //系统消息
      if(args.id === '10000'){
        this.$router.push({path: '/ChatSystem', query: { id: '10000', name: this.$t('user.sysMsg')}});
        return;
      }
      this.startChat(args,args.chatType);
    },

    /**
     * @breif 处理来自DDIO的路由跳转请求
     * @param {*} e 
     * @param {*} args 
     */
    dealJumpRouterFromDDIO(e,args) {
      
      if (args.type === 0 || args.type >= this.ddioHandler.length) {
        console.log('invalid type');
        return;
      }
      this.hideAccountCenter();
      this.ddioHandler[args.type].call(this, args);
    },

    /**
     *@breif 接收音视频通话通知
     *
     * @param {int} type 非0表示有通话通知
     */
    onRtcPluginNotify(event, type) {
      if (type) {
        this.$refs.rtcring.play();
      }
      else {  //  挂断
        this.$refs.rtcring.pause();
        this.$refs.rtchangup.play();
      }
    },

    getAddMenu(obj) {
      this.isAddMenu = !this.isAddMenu;
      this.currentPos.left = event.clientX + 10 + "px";
      this.currentPos.top = event.clientY + 10 + "px";
    },

    logoutSDK() {
      this.$Service.auth.logout(null, resp => {
        console.log("注销 ", resp);
        this.$Service.log(`注销:code:${resp.code}`);
      });
    }
  },
};
export default mixin;
