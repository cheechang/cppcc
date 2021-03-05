import {
  app,
  Tray,
  Menu,
  ipcMain,
  shell,
  globalShortcut,
  BrowserWindow,
  dialog,
  Notification
} from 'electron'
import {
  isWindows,
  isOSX,
  isDev,
  isWinXp,
  isWin7
} from '../comm/is'
import {
  resolve,
  join
} from 'path'
import {
  homedir
} from 'os'
import i18n from '../comm/i18n';
import {getAvatar} from '../comm/util'
import config from '../comm/config'
import Platform from '../comm/platform';

const platform = new Platform();
const path = require('path')
const fs = require('fs');
const archiver = require('archiver');
const log = require('electron-log')
//const dbPath = join(homedir(), isOSX ? '/Library/Containers/com.vrv.Linkdood/Data/Linkdood/' : '/AppData/Local/Linkdood/') // 数据库目录
var screenCallBack;
global.hotKeyActivate = false;
var trayNotification = null;
var notificationTimeout = null;
var trayNotificationAvatars = {};
export const TrayStatus = {
  Normal: 'tray_normal.png',
  Offline: 'tray_offline.png',
  Unread: 'tray_unread.png',
  Flash: 'tray_flash.png'
};

export class TrayWindow {
  initMenu() {
    this.menus = Menu.buildFromTemplate([{
        label: i18n.t('menu.feedback'),
        click: () => this.handleZipFile()
      },
      {
        label: i18n.t('menu.open'),
        click: () => this.mainWindow._window.show()
      },
      {
        label: i18n.t('menu.logout'),
        visible: false,
        click: () => this.logout()
      },
      {
        label: i18n.t('menu.exit'),
        click: () => this.quit()
      }
    ])
    this.menuLogout = this.menus.items[2]
  }

  logout() {
    this.mainWindow._window.show()
    this.mainWindow._window.webContents.send('logout-or-quit', {type: 'logout'})
  }

  quit() {
    console.log('this.menuLogout.visible', this.menuLogout.visible)
    if (!this.menuLogout.visible) {
      this.trayIcon.destroy()
      return this.mainWindow.quit()
    }
    this.mainWindow._window.show()
    //this.mainWindow._window.webContents.send('plugin-notify', false)
    this.mainWindow._window.webContents.send('logout-or-quit', {type: 'quit'})
  }
  initLinstener() {
    ipcMain.on('plugin-notify', (e, arg) => {
      this.mainWindow._window.webContents.send('plugin-notify', arg)
    });
    ipcMain.on('tray-username', (e, arg) => {
      log.info('setUsername', arg);
      global.userInfo = arg;
      global.mutipleServers.setMykey(`${arg.userId}@${arg.server}`);
      if(this.trayIcon){
        this.trayIcon.setToolTip(`${i18n.t('window.title')}-${arg.name}@${arg.server}`); 
      }
    });
    ipcMain.on('netChanged', (e, arg) => {
      arg.netChanged = true;
      this.showNotification(arg);
    });
    ipcMain.on('newMessage', (e, arg) => {
      log.debug('newMessage::focus', this.focus);
      if (this.focus) {
        return;
      }
      if(!this.trayIcon){
        // 此时此服务器为子服务器，需要告知其他服务器收到新消息了
        global.mutipleServers.newMsgToServers();
      }
      if(arg && config.clientConfig.user.openTrayTip && arg.openTrayTip) {
        this.showNotification(arg);
      }
      this.mainWindow._window.flashFrame(true);
      if (this.flash) {
        return;
      }
      this.trayChange = setInterval(() => {
        if(this.trayIcon){
          if (this.judge) {
            this.trayIcon.setImage(`${this.trayIconPath}/${TrayStatus.Unread}`);
          } else {
            this.trayIcon.setImage(`${this.trayIconPath}/${TrayStatus.Flash}`);
          }
        }
        this.judge = !this.judge;
      }, 500)
      this.flash = true;
    });

    //  登录成功事件
    ipcMain.on('login-successed', () => {
      console.log('in login-successed');
      this.initScreenShot();
      global.callPlugin.loginState = true;
      this.menuLogout.visible = true; //
      if(this.trayIcon){
        this.trayIcon.setImage(`${this.trayIconPath}/${TrayStatus.Normal}`);
      } 
    });

    //  注销事件
    ipcMain.on('tray-logout', () => {
      trayNotificationAvatars = {};
      global.mutipleServers.setMykey(process.pid);
      global.callPlugin.loginState = false;
      globalShortcut.unregister(this.hotkey)
      // globalShortcut.unregisterAll();
      if(!isWindows &&this.screenShotWin){
        this.isLockScreenShot = false;
        this.screenShotWin.close();
        this.screenShotWin = null;
      }
      this.menuLogout.visible = false;
      this.mainWindow._window.setSize(960, isOSX ? 622 : 600);
      !this.mainWindow._window.isAlwaysOnTop() && this.mainWindow._window.show();
      if(this.trayIcon){
        this.trayIcon.setToolTip(i18n.t('window.title'));
        this.trayIcon.setImage(`${this.trayIconPath}/${TrayStatus.Offline}`);
      }
    });
  }

  constructor(mainWindow, hotkey) {
    i18n.locale = global.language
    this.initMenu();
    this.initLinstener();
    log.info('TrayWindow constructor')
    this.mainWindow = mainWindow
    this.flash = false
    this.judge = false
    this.focus = false
    this.isLockScreenShot = false
    this.hotkey = hotkey

    this.trayIconPath = isDev ? resolve(__dirname, '../../vrv-static/resources/images/icons') : resolve(__dirname, './node_modules/vrv-static/resources/images/icons');

    this.trayIconPath += isOSX ? "/mac" : (isWindows ? "/windows":"/linux");
    // 不是多服务器启动的隐藏客户端，则去正常的创建图标流程
    if(!global.serversLoginParam){
        this.trayIcon = new Tray(`${this.trayIconPath}/${TrayStatus.Offline}`);
        this.trayIcon.setContextMenu(this.menus);
        this.trayIcon.on('click', () => {
          this.mainWindow._window.show();
          this.onShutFlash();
        });
        this.trayIcon.setToolTip(i18n.t('window.title'));
    }
    this.mainWindow._window.on('focus', () => {
      this.focus = true
      this.onShutFlash()
    });
    this.mainWindow._window.on('blur', () => {
      this.focus = false
    });
    if(isWindows){
      app.setAppUserModelId(`${i18n.t('window.title')}`);
    }
    // ipcMain.on('setUsername',(e, arg)=>{
    //   log.info('setUsername', arg)
    //   this.trayIcon.setToolTip(`Linkdood-${arg.name}@${arg.server}`)
    // })
    // ipcMain.on('newMessage',(e, arg)=>{
    //   log.debug('newMessage::focus', this.focus)
    //   if(this.focus){ return }
    //   this.mainWindow._window.flashFrame(true)
    //   if (!this.flash) {
    //     this.trayChange = setInterval(() => {
    //       if (this.judge) {
    //         this.trayIcon.setImage(`${icoPath}/ImTray_unread_msg.png`)
    //       } else {
    //         this.trayIcon.setImage(`${icoPath}/empty.png`)
    //       }
    //       this.judge = !this.judge
    //     }, 500)
    //     this.flash = !this.flash
    //   } else {
    //     return
    //   }
    // })
  }
  /****************************多服务器相关**************************************** */
  //切换到当前客户端,初始化托盘图标,显示主窗口
  switchToCurrent(){
    this.mainWindow._window.show();
    this.trayIcon = new Tray(`${this.trayIconPath}/${TrayStatus.Normal}`);
    this.trayIcon.setContextMenu(this.menus);
    this.trayIcon.on('click', () => {
      this.mainWindow._window.show();
      this.onShutFlash();
    });
    if(global.userInfo){
      this.trayIcon.setToolTip(`${i18n.t('window.title')}-${global.userInfo.name}@${global.userInfo.server}`); 
    }
  }
  //切换到其他客户端,销毁托盘图标，隐藏主窗口
  switchToOhter(){
    this.mainWindow._window.hide();
    this.trayIcon.destroy();
    this.trayIcon = null;
    this.focus = false;
  }
 /*****************************多服务器相关*************************************** */
  showNotification(arg){
    if(isWinXp || isWin7()) {
      return;
    }
    if(trayNotification){
      clearTimeout(notificationTimeout)
      trayNotification.close();
    }
    // 此时是网络变化通知
    if(arg.hasOwnProperty('netChanged')){
      trayNotification = new Notification({
        title:arg.title,
        body:arg.body,
        icon:isOSX ? '' : (isDev ? resolve(__dirname, '../../vrv-static/resources/images/common/dou.png') : resolve(__dirname, './node_modules/vrv-static/resources/images/common/dou.png')),
        silent: true
      });
    }
    //新消息通知
    else{
      let whereFrom = (arg.chatType === 2 && arg.whereFrom) ? `${arg.whereFrom}: `:'';
      let lastMsg = arg.lastMsg.length>25? arg.lastMsg.substr(0,25)+'......':arg.lastMsg;
      if(!trayNotificationAvatars.hasOwnProperty(arg.id)){ //该头像未缓存
        let tempArg =  Object.assign({},arg);
        if(tempArg.thumbAvatar && !global.service.file.fileOperate({ filepath: tempArg.thumbAvatar, type: 0 })){
          tempArg.thumbAvatar ='';
        }
        trayNotificationAvatars[tempArg.id] = getAvatar(tempArg);
      }
      trayNotification = new Notification({
        title:arg.name,
        body:whereFrom+lastMsg,
        icon:trayNotificationAvatars[arg.id],
        silent: true
      });
    }
    trayNotification.on('click',(e)=>{
      this.mainWindow._window.show()
      if(!arg.hasOwnProperty('netChanged')){
        //新消息通知，打开该会话
        this.mainWindow._window.webContents.send('openChatByNotification', arg)
      }
    })
    trayNotification.show();
    notificationTimeout = setTimeout(()=>{
      if(trayNotification){
        trayNotification.close();
      }  
    },5000)
  };
  initScreenShot(){
    global.setScreenShotCb= callback =>{
      screenCallBack = callback;
    }
    global.service.config.regScreenShotCb(null,resp=>{
      console.log('regScreenShotCb---resp:',resp);
      if(resp.type === 'finished'){ //截图完成后的回调
        if(global.hotKeyActivate){
          console.log('regScreenShotCb---resp:showMainWindow');
          this.mainWindow._window.show();
          this.mainWindow._window.focus();
          global.hotKeyActivate = false;
        }
        if(screenCallBack) {
          if(isOSX){
            this.mainWindow._window.focus();
          }
          screenCallBack(resp.code);
        }
      }
      else if(resp.type === 'hotKeyActivate'){ //当用户设置了截图时隐藏主窗口,则激活快捷键时会触发此回调
        if(this.mainWindow._window.isVisible() && this.mainWindow._window.isFocused()){
          global.hotKeyActivate = true;
          this.mainWindow._window.hide();
        }
      }
    });
  }
  /**
   * 根据日期获取需要的sdk日志
   * @param {Number} -dayCount -2:前天;-1:昨天;0:今天;
   */
  getSdkLogName(dayCount=0) {
    let date = new Date();
    date.setDate(date.getDate()+dayCount)
    let [year, month, day] = [
      date.getFullYear(),
      date.getMonth() + 1,
      date.getDate()
    ]
    if (month < 10) {
      month = "0" + month;
    }
    if (day < 10) {
      day = "0" + day;
    }
    return "sdklog_" + year + "-" + month + "-" + day + (dayCount!==0?".zip":"");
  }

  handleZipFile() {
    dialog.showSaveDialog({ 
      defaultPath: 'suggesitons.zip',
      filters: [
        { name: 'File', extensions: ['zip'] }
      ]
    }, resp => {
    console.log('resp:::::', resp)
    if (!resp) return;
    // if (!this.menuLogout || !this.menuLogout.visible) shell.openExternal(isOSX ? `file://${dbPath}` : dbPath)
    // else {
      this.mainWindow._window.show();
      this.mainWindow._window.webContents.send('forward-file', {
        isOSX,
        dbPath: resp
      })
      // }
      let achiveFileName = resp;
      // let achiveFileName = `${dbPath}suggesitons.zip`;
      // let achiveFileName = `${homedir}/AppData/Local/Linkdood/suggesitons.zip`;
      let archive = archiver('zip', {
        zlib: { level: 9 }
      });
      let output = fs.createWriteStream(achiveFileName);
      output.on('close', () => {
        if (this.menuLogout && this.menuLogout.visible) this.mainWindow._window.webContents.send('send-zip-file', archive.pointer())
        log.debug(archive.pointer() + ' total bytes');
      });
      output.on('end', () => {
        log.debug('Data has been drained');
      });
      archive.on('error', function(err) {
        throw err;
      });

      archive.pipe(output);
      archive.bulk([{
        src: [
          'log/**', 
          'public/coreDump/**', 
          'public/commLog', 
          `public/${this.getSdkLogName(0)}/**`, 
          `public/${this.getSdkLogName(-1)}`, 
          `public/${this.getSdkLogName(-2)}`
        ],
        cwd: join(homedir(), platform.platforminfo().dbPath),
        expand: true
      }]);
      archive.finalize();
    })
  }

  // 停止闪烁
  onShutFlash() {
    if (this.trayChange) {
      if(this.trayIcon){
        this.trayIcon.setImage(`${this.trayIconPath}/${TrayStatus.Normal}`);
      }
      clearInterval(this.trayChange);
      this.trayChange = null;
      this.flash = false;
    }
    if(trayNotification){
      trayNotification.close();
    }
  }
}
