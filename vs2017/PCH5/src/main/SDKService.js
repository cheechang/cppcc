import { homedir } from 'os'
import { join, resolve } from 'path'
import Platform from '../comm/platform';
import { isDev, isOSX, isWindows } from '../comm/is'
const VRVStatic = require('vrv-static')
const log = require('electron-log')
import {getConfig,setConfig} from '../comm/util'
const pkg = require('../../package.json')
import { Rtcplugin } from '../rtc/rtcplugin/rtcplugin'
import DDIOFuncs from './SDKService4DDIO'
import PluginFuncs from './SDKService4Plugin'
log.warn('VRVStatic', VRVStatic)
let client = null
export default {
  init: (newWindow) => {
    //  获取平台相关信息
    this.platform = new Platform();
    console.log('i get platform: ', this.platform.platforminfo().deviceInfo);
    client = new VRVStatic.vimsdk();
    const info = {
      appVersion: pkg.version,
      deviceType: 1,
      deviceInfo: this.platform.platforminfo().deviceInfo,
      appName: 'Linkdood',
      netType: 'wifi',
      mark: 'comm',
      macAddress:getConfig({key:'macAddress'}) //从配置文件获取mac地址，如果没有,nodeService会进行获取赋值
    };
    global.initInfo = info
    // const dbPath = join(homedir(), isOSX 
    //   ? '/Library/Containers/com.vrv.Linkdood/Data/Linkdood/' 
    //   : '/AppData/Local/Linkdood/'); // 数据库目录  linux (~/.local/share/Linkdood)
    console.log('get platforminfo dbpath: ', this.platform.platforminfo().dbPath);
    console.log('get homeidr: ', homedir());
    const dbPath = join(homedir(), this.platform.platforminfo().dbPath);
    console.log('get sdk dbpath: ', dbPath);
    const crtPath = resolve(__dirname,  isDev ? `../../node_modules/vrv-static/lib/vimsdk/${process.platform}/linkdood.crt` : `./node_modules/vrv-static/lib/vimsdk/${process.platform}/linkdood.crt`);
    client.setDataPath(dbPath); //设置nodeService数据库目录
    client.fileService().fileOperate({filepath:dbPath,type:1});
    log.info(dbPath, crtPath)
    const result = client.startup(dbPath, crtPath, info);
    log.verbose('SDKService initSdk result:', result.result);
    if (result.result > 0) {
      if(info.macAddress !== result.macAddress){
        global.ConfigIni.setConfig({key:'macAddress',value:result.macAddress}); //存储mac地址至配置文件
        global.initInfo.macAddress = result.macAddress;
      }
      global.service = {
        auth: client.authService(),
        contact: client.contactService(),
        chat: client.chatService(),
        user: client.userService(),
        group: client.groupService(),
        file: client.fileService(),
        config: client.configService(),
        search: client.searchService(),
        enterprise: client.enterpriseService(),
        sysMsg: client.sysMsgService(),
        cloud: client.cloudService(),
        rtc:client.rtcService(),
        rtcplugin: new Rtcplugin(client.rtcService(), newWindow),
        log(logInfo){
           client.setLog({level:1,info:logInfo});
           if(isDev) log.info(logInfo);
        }
      },
      global.callByDDIOApp = DDIOFuncs;
      global.dbPath = dbPath;
      global.osxDirPath = resolve();
      global.callPlugin = PluginFuncs;
      global.pkg = pkg;
      //初始化oauth
      let oauthClient = null;
      // 成功加载oauth插件
      if(VRVStatic.oauth){
        oauthClient = new VRVStatic.oauth.client();
      }
      global.oauth = oauthClient
    }
    log.warn('SDKService:init, global.service')
    return client  
  },
  shutdown: () => {
    log.info('SDKService:shutdown, client', client)
    if (client !== null) {
      client.shutdown()
    }
  }
}
