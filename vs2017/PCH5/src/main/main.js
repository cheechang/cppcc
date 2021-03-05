import { app, ipcMain, shell, IpcMessageEvent, BrowserWindow, screen, globalShortcut, dialog,crashReporter } from 'electron'
import { autoUpdater } from 'electron-updater'
import { join,resolve } from 'path'
import { isDev ,isOSX,isWindows,isWinXp} from '../comm/is'
import { rmdir,decryStr } from '../comm/util'
import { enableSourceMaps } from '../comm/sourceMapSupport'
import { MainWindow } from './MainWindow'
import { SubWindow } from './SubWindow'
import { getWindowUrl } from '../comm/windowUrl'
import { TrayWindow, TrayStatus } from './trayWindow'
import createMenu from './menu'
import { homedir } from 'os'
import config from '../comm/config';
import SDK from './SDKService'
import pkg from '../../package.json'
import 'url-search-params-polyfill'
import 'babel-polyfill'
import promise from 'es6-promise';
import ConfigIni from '../comm/ConfigIni';
import AppPath from '../comm/AppPath';
import {MutipleServers} from '../renderer/components/Servers/multipleServers'

promise.polyfill();

const path = require('path')
const log = require('electron-log')
const fs = require('fs');
let mainWindow = null
let trayWindow = null
let subWindows = []
let preventRtcSubWindows = false //阻止RTC类窗口开启
let updateUrl = "http://114.255.32.34/pcdisth5/win/"
let globalKey ={
  shortcuts_Key:'Shift+CommandOrControl+X',
  windowshow_Key:'Alt+C'
}
let shortCuts_hideWindow = false;
let mediaMsgPreivewId
// let isLockScreenShot = false

// 监听进程事件 18192826736
function handleProcess() {
}

/**
 * 程序启动前处理的事情
 * 现在是清理升级文件存放目录以及创建OSX的升级包下载目录
 */
function preStartup() {
  let updatePath = `${homedir}\\AppData\\Local\\Linkdood\\update`
  global.service.file.fileOperate({ filepath: updatePath, type: 2 });

  let updateJsonPath = `${homedir}\\AppData\\Roaming\\Linkdood\\update.json`
  global.service.file.fileOperate({ filepath: updateJsonPath, type: 2 });

  if (isOSX) {
    let defaultDownloadLocalUrl = `${homedir}/Library/Containers/com.vrv.Linkdood/Data/updater/`;
    global.service.file.fileOperate({ filepath: defaultDownloadLocalUrl, type: 1 })
  }

}

if(isWinXp){
  try {
    // 2 week licence
    process.setLicence("eac9ad901a044fd9bf17f8e4bcb02ea5")
  } catch(_) {}
}

// 监听应用事件，ready后创建，activate后显示
function handleApp() {
  // log.debug('app:::::::', pkg.build.appId)
  if(!isOSX){
    global.service.config.startUpScreenShot(); //启动截图程序
  }
  app.setAppUserModelId(pkg.build.appId)
  app.commandLine.appendSwitch("--disable-http-cache"); //禁用http缓存
  app.on('ready', () => {
    //  处理启动前的事情
    setLinkdoodLanguage(); //设置语言
    preStartup();
    mainWindow = new MainWindow(SDK)
    trayWindow = new TrayWindow(mainWindow, globalKey.shortcuts_Key)
    // 将多服务器对象注册到全局
    global.mutipleServers = new MutipleServers(mainWindow,subWindows,trayWindow);
    createMenu()
    mainWindow.load()
  })
  // 默认隐藏窗口，设置后关闭窗口
  .on('before-quit', () => {
    mainWindow.isQuitByTrayMenu(true)
  })
  
  .on('activate', () => {
    mainWindow._window && mainWindow._window.show()
  })
}

function newWindow({targetId, winTitle, winType, winUrl, shapeType, isWinShow=true, winIcon, winFrame=true, appID, isLocalApp, isApp,openOAuth={}}, {width=800, height=600, x=0, y=0}) {
  winUrl = getWindowUrl(winType, winUrl) || winUrl
  log.debug('winUrl:::::::', winUrl)
  if(winType=== 'RemoteControl' || winType=== 'RTCP2P' || winType=== 'RtcFile' || winType === 'mediadood' || winType === 'InternalWindow') {
    preventRtcSubWindows = false;
  }
  if (winType === 'app' && subWindows['app']) { // 再次打开App
    openAppData(winUrl, winTitle, appID, winIcon, isLocalApp, isApp,openOAuth);
  }
  let win = subWindows[winType] // TODO 防多开子窗口
  if (winType === 'RtcFile') {
    ipcMain.once('RtcFileClose',()=>{
      win._window.close()
    })
  }

  if (targetId) {
    mediaMsgPreivewId = targetId
    console.log('mediaMsgPreivewId', mediaMsgPreivewId)
  }
  if(!win) {
    // if (winType === 'app') {
    //   winTitle = global.language === 'zh-CN' ? '工作台' : 'Work';
    // }
    win = new SubWindow({winTitle, shapeType, winIcon, winFrame, winType, isWinShow, width, height, winUrl, showSubwindow,closeSubwindow})
    win.load(winUrl)
    subWindows[winType] = win._window
    win.handleShow(preventRtcSubWindows).then((isPrevent) => {
      if (!isPrevent) {
        winType === 'app' && openAppData(winUrl, winTitle, appID, winIcon, isLocalApp, isApp,openOAuth)
      } else {
        preventRtcSubWindows = false;
        delete subWindows[winType]
      }
    })
    win.handleClose().then(() => {
      delete subWindows[winType]
    })
  } else {
    if (winType==='Imagepreivew' || winType==='MapPreview') win.loadURL(winUrl)
    win.show()
  }
  return subWindows[winType]
}

function showSubwindow(winType, winUrl){
  switch(winType){
    case 'mediadood':
      {
        global.service.rtcplugin.regMultiEventCb((resp) =>{
          switch (resp.type) { // 事件类型(1呼叫 2邀请 3进房 4挂断 5结束 6超时 7应答)
            case 5:
              {
                closeMeetingWindow(resp);
              }
              break;
            case 6:
              {
                closeMeetingWindow(resp);
              }
              break;
            }
        });
      }
      break
  }
}

function closeSubwindow(winType, winUrl){
    global.service.log(`main:::closeSubwindow>>${winType}<==>${JSON.stringify(winUrl)}`);
    switch(winType){
      case 'mediadood':
        {
          const seachParam = new URLSearchParams(winUrl.split('?')[1]);
          const roomId = seachParam.get('roomId'); 
          const groupId = seachParam.get('groupId'); 
          closeMeetingWindow({
            roomId,groupId
          });
          openStatsWindow(false);
        }
        break;
      case 'InternalWindow':
        {
          const seachParam = new URLSearchParams(winUrl.split('?')[1]);
          const roomId = seachParam.get('roomId'); 
          const groupId = seachParam.get('groupId'); 
          closeRequestMeetingWindow({
            roomId,groupId
          });
        }
        break;
    }
}
// 监听renderer与main间remote事件，并路由到其他子窗口
function handleIpcMainRoute() {
  ipcMain.on('rtc', e => {
    log.info('IpcMain:rtc')
    mainWindow._window.webContents.send('rtc')
  })

  ipcMain.on('new-window-weburl', (e, url) => {
    log.debug('IpcMain:new-window', url)
    // 浏览器打开外部链接
    shell.openExternal(url)
  })

  ipcMain.on('imagePreviewForward', (event, arg) => {
    log.debug('imagePreviewForward::::', arg)
    mainWindow._window.show()
    mainWindow._window.webContents.send('forward-file', arg)
  })

  ipcMain.on('imagePreview-identifyQrcode', (event, arg) => {
    log.debug('imagePreview-identifyQrcode::::', arg)
    mainWindow._window.show()
    mainWindow._window.webContents.send('addfriend-by-qrcode', arg)
  })

  ipcMain.on('new-window', (e, winParams) => {
    global.service.log(`winUrl=====>${winParams.winUrl}`)
    let coords = {x:0,y:0,width:0,height:0}
    switch (winParams.winType) {
    case 'RemoteControl':
      coords = {x:0,y:0,width:300,height:300}
      break
    case 'RTCP2P':
      const seachParam = new URLSearchParams(winParams.winUrl.split('?')[1]);
      const videoType = seachParam.get('type'); 
      console.log('zxj::main>>',videoType === '1',videoType );
      if(videoType === '1'){
        coords = {x:0,y:0,width:320,height:480}
      }else{
        coords = {x:0,y:0,width:640,height:480}
      }
      break
    case 'RtcFile':
      coords = {x:0,y:0,width:200,height:200}
      break
    case 'MicroVideo':
      coords = {x:0, y:0, width:320, height:560}
      break
    default:
      coords = {x:0, y:0, width:800, height:600}
      break
    }
    if(winParams.winType!=='ScreenShot') newWindow(winParams, coords)
  })



  ipcMain.on('uncaughtException', (event) => {
    if (mainWindow._window) {
      mainWindow._window.destroy()
    }
    app.quit()
  })

  ipcMain.on('change-window-type', (e, winParams) => {
    console.log('zxj::change-window-type', winParams.subType);
      switch (winParams.winType) {
          case 'RTCP2P':
            if(winParams.subType == 'toMoblie' || winParams.subType == 'toAudio'){
              subWindows[winParams.winType].setSize(320, 480);
              subWindows[winParams.winType].setMinimumSize(320, 480);
            }else{
              subWindows[winParams.winType].setSize(640, 480);
              subWindows[winParams.winType].setMinimumSize(640, 480);
            }
            subWindows[winParams.winType].setTitle(winParams.winTitle);
            break;
      }
  })

  ipcMain.on('exit-app', (event) => {
    global.service.rtcplugin.regRtcFileCb(null);
    if(!isOSX){
      global.service.config.shutDownScreenShot(); //关闭截图程序
    }
    trayWindow.trayIcon.destroy()
    mainWindow.quit()
  })

  ipcMain.on('change-window-type', (e, winParams) => {
      switch (winParams.winType) {
          case 'RTCP2P':
            subWindows[winParams.winType].setSize(320, 480);
            break;
      }
  })

  ipcMain.on('close-all-subWin', ()=>{
    Object.keys(subWindows).forEach(e=>{
      log.debug('receive close-all-subWin::::::', e)
      if(e === 'RTCP2P'||e === 'RemoteControl'){
        log.debug('RTCP2P|RemoteControl::::::')
        subWindows[e].webContents.send('closeRtc')
      }
      if(e === 'RtcFile') {
        log.debug('RtcFile::::::')
        subWindows[e].webContents.send('colseFile')
      }
      if(e === 'mediadood' || e === 'Imagepreivew' || e === 'app' || e==='versionIntro'||e === 'inviteBuyServer'||e === 'MicroVideo') subWindows[e].close()
      if (trayWindow.screenShotWin) {
        trayWindow.screenShotWin.close()
        trayWindow.screenShotWin = null
      }
      delete subWindows[e]
    })
    mainWindow._window.webContents.send('before-log-out')
  })

  ipcMain.on('app-window-control', (event, control) => {
    log.debug('IpcMain:app-window-control', control)
    log.debug('IpcMain:app-subwindow', subWindows['app'])
    if (control !== 'close') {
      subWindows['app'][control]()
    } else {
      subWindows['app'].close()
    }
  })

  ipcMain.on('subWin-netstatus-app', (event, status) => {
    console.log('通知应用浏览器当前网络状态:::', status);
    if (!subWindows['app']) return;
    console.log('---------------------');
    subWindows['app'].webContents.send('net-status', !status)
  })

  ipcMain.on('win-size-control', (event, control) => {
    log.debug('IpcMain:win-size-control', control)
    if (mainWindow._window[control]) {
      if(control==='close') {
        mainWindow._window.blur()
        trayWindow.focus = false
      }
      mainWindow._window[control]()
    }
  })

  ipcMain.on('win-shake-event', ()=>{
    mainWindow._window.minimize()
    mainWindow._window.restore()
    setTimeout(() => {
      shakeWin(mainWindow._window.getPosition())
    }, 40);
  })

  ipcMain.on('control-main-window', (event, arg)=> {
    log.info('control-main-window:',arg)
    if(arg){
      mainWindow._window.show()
    }
    else{
      mainWindow._window.hide()
    }
  })

  ipcMain.on('handleSubWinMediaMsg', (event, param) => {
    log.info('handleSubWinMediaMsg:')
    console.log('revokeImageparam::', param)
    if (param.winType === 'image') {
      if(subWindows['Imagepreivew'].webContents){
        subWindows['Imagepreivew'].webContents.send('handleImage', param)
      }
    } else {
      log.info('MicroVideo handleVideo::')
      if(subWindows['MicroVideo'].webContents){
        subWindows['MicroVideo'].webContents.send('handleVideo', param)
      }
    }
  })

  // 注册全局快捷键
  ipcMain.on('globalRegisterKey', (event, param) => {
    global.service.log(`globalRegisterKey:${JSON.stringify(param)}`);
    switch (param.key) {
      case 'register-shortcuts-hideWindow':  //截图隐藏窗口
      {
        shortCuts_hideWindow = param.value;
        break;
      }
      case 'register-shortcuts':    //截屏快捷键
      {
        if(globalKey.shortcuts_Key){
          globalShortcut.unregister(globalKey.shortcuts_Key)
        }
        globalKey.shortcuts_Key = param.value
        if(!param.value) return;
        globalShortcut.register(param.value, () => {
          if (shortCuts_hideWindow && mainWindow._window.isVisible()) {
            mainWindow._window.hide();
            global.hotKeyActivate = true;
            setTimeout(() => {
              global.service.config.screenShot();
            }, 30);
          }
          else {
            global.service.config.screenShot();
          }
        })
        break;
      }
      case 'register-windowshow': //隐藏/显示窗口
      {
        if(globalKey.windowshow_Key){
          globalShortcut.unregister(globalKey.windowshow_Key)
        }
        globalKey.windowshow_Key = param.value
        if(!param.value) return;
        globalShortcut.register(param.value, ()=>{
          console.log(mainWindow._window.isVisible())
          if (mainWindow._window.isVisible()&&(!mainWindow._window.isMinimized())) {
            trayWindow.focus = false
            mainWindow._window.blur()
            mainWindow._window.close()
          } else {
            trayWindow.focus = true
            mainWindow._window.show()
          }
        })
        break;
      }
    
      default:
        break;
    }

  })

  //执行自动更新检查
  ipcMain.on('check-for-update',(event, url)=>{
    if (isWinXp) return
    log.info('[check-for-update]')
    // updateUrl = url;
    autoUpdater.setFeedURL(updateUrl);
    autoUpdater.checkForUpdates();
  })

  // 执行更新下载
  ipcMain.on('download-update', ()=>{
    if (isWinXp) return
    log.info('[download-update]')
    autoUpdater.downloadUpdate();
  })

  // 视频会议退出
  ipcMain.on('exit_meeting',(event,param) =>{
    global.service.log(`main::exit_meeting：${param}`)
    closeMeetingWindow(param);
  })

  ipcMain.on('open_webrtc_stats',(event, isOpen) =>{
    global.service.log(`main::open_webrtc_stats${isOpen}`)
    openStatsWindow(isOpen);
  });

  ipcMain.on('open-filedir', (event, path) => {
    shell.showItemInFolder(path)
  })

  ipcMain.on('send-map-message', (event, positon) => {
    log.debug('send-map-message', JSON.stringify(subWindows));
    subWindows['MapPreview'] && subWindows['MapPreview'].close();
    mainWindow._window.webContents.send('map-message', positon)
  })
}

// 关闭 视频会议界面 并调用插件挂断
function closeMeetingWindow(param) {
  mainWindow._window.webContents.send('plugin-notify', false)
  global.service.log(`main::closeMeetingWindow${param}`)
  if (subWindows['mediadood']) {
    subWindows['mediadood'].close();
    delete subWindows['mediadood'];
  }
  if (param) {
    const request = {
      reqType: 5,
      annotation: 'hungup',
      groupId: param.groupId,
      roomId: param.roomId
    };
    global.service.rtcplugin.hangUp(request, cb => {
      // console.log("RTC_INFO:exit_meeting ", cb);
      global.service.log(`main:closeMeetingWindow:hangUp ${cb}`)
    });
  }
}

function closeRequestMeetingWindow(param) {
  global.service.log(`main::closeRequestMeetingWindow${param}`)
  if (!subWindows['mediadood']) {
    if (param) {
      const request = {
        reqType: 5,
        annotation: 'hungup',
        groupId: param.groupId,
        roomId: param.roomId
      };
      global.service.rtcplugin.hangUp(request, cb => {
        // console.log("RTC_INFO:exit_meeting ", cb);
        global.service.log(`main:closeRequestMeetingWindow:hangUp ${cb}`)
      });
    }
  }
  if(subWindows['InternalWindow']){
    subWindows['InternalWindow'].close();
    delete subWindows['InternalWindow'];
  }
}

// 打开或关闭 webrtcStats 界面
function openStatsWindow(isOpen) {
  if (isOpen) {
    newWindow({
      winTitle: 'chrome://webrtc-internals/',
      winType: 'AbsoluteWindow',
      winUrl: 'chrome://webrtc-internals/',
      shapeType: 'normal'
    }, { width: 800, height: 600 });
  }
  else {
    if (subWindows['AbsoluteWindow']) {
      subWindows['AbsoluteWindow'].close();
      delete subWindows['AbsoluteWindow'];
    }
  }
}

/**
 * 窗口抖动事件     
 * @param {Array} winCoords - 当前窗口x,y坐标
 * @param {Number} offsetDirection - 位移偏移方向
 * @param {Number} maxLimitShakeCycle - 初始位移偏移量/最大抖动周期
 */
function shakeWin(winCoords, offsetDirection=1, maxLimitShakeCycle=6) {
  let [xCoords, yCoords] = [winCoords[0], winCoords[1]]
  if(maxLimitShakeCycle-2>=0) { // 抖动周期设置为4
    switch (offsetDirection%4) {
      case 1: // top
        yCoords-=maxLimitShakeCycle
        break;
      case 2: // left
        xCoords-=maxLimitShakeCycle
        break;
      case 3: // bottom
        yCoords+=maxLimitShakeCycle
        break;
      case 0: // right
      default:
        maxLimitShakeCycle--
        xCoords+=maxLimitShakeCycle
        break;
    }
    offsetDirection++
    setTimeout(() => {
      mainWindow._window.setPosition(xCoords, yCoords)
      shakeWin(winCoords, offsetDirection, maxLimitShakeCycle)
    },40)
  }
}
/************************************************************ */
function postMsgToRender(signalName,param){
  log.info(signalName,":",param);
  if(signalName === 'closeSubWin'){
    preventRtcSubWindows = true;
    return;
  }
  else if(signalName === 'wakeUp'){
    mainWindow._window.show();
    return;
  }
  else if(signalName === 'exitLinkdood'){
    mainWindow.quit();
    return;
  }
  mainWindow._window.webContents.send(signalName,param);
}
function judgePlginSubWinStatus(winType) {
  let judgeResult = {
    busy:false,
    busyType:''
  }
  // if(subWindows['RemoteControl'] || subWindows['RTCP2P'] || subWindows['RtcFile'] || subWindows['mediadood'] || subWindows['InternalWindow']){
    if(subWindows['RemoteControl']){
      judgeResult.busyType = 'RemoteControl';
      judgeResult.busy = true;
    }else if(subWindows['RTCP2P']){
      judgeResult.busyType = 'RTCP2P';
      judgeResult.busy = true;
    }else if(subWindows['RtcFile']){
      judgeResult.busyType = 'RtcFile';
      judgeResult.busy = true;
    }else if(subWindows['mediadood']){
      judgeResult.busyType = 'mediadood';
      judgeResult.busy = true;
    }else if(subWindows['InternalWindow']){
      judgeResult.busyType = 'InternalWindow';
      judgeResult.busy = true;
    }
  // }
  // if(subWindows['RemoteControl']!==undefined ||subWindows['RTCP2P']!==undefined||subWindows['RtcFile']!==undefined ) 
  // {
  //   judgeResult.busyType = subWindows['RemoteControl']!==undefined?'RemoteControl':(subWindows['RTCP2P']!==undefined?'RTCP2P':'RtcFile');
  //   judgeResult.busy = true;
  // }
  return judgeResult;
}

function isOpenMediaMsgPreivew () {
  if(subWindows['Imagepreivew'] || subWindows['MicroVideo']) {
    console.log('Imagepreivew::::')
    return {isOpen: true, mediaMsgPreivewId: mediaMsgPreivewId}
  }
}

// 获取文件图标
function getFileIcon (path, callBack) {
  app.getFileIcon(path, {size: 'normal'},  function (err, icon) {
    console.log('getFileIcon', icon)
    callBack(icon.toDataURL())
  })
}

/************************************************************* */
// 打开app时主进程给应用传递参数
function openAppData(winUrl, winTitle, appID, winIcon, isLocalApp, isApp,openOAuth) {
  let appData = {
    appName: winTitle,
    appIcon: winIcon,
    appID: appID,
    isApp: isApp,
    isLocalApp: isLocalApp,
    mainUrl: winUrl,
    openOAuth:openOAuth
  }
  log.debug(JSON.stringify(appData), '主进程发送给App的参数');
  subWindows['app'].webContents.send('open-appData', appData);
  subWindows['app'].webContents.send('is-dev', isDev);
}

/************************************************************* */
//获取及设置程序语言
function setLinkdoodLanguage(){
  let language = global.service.config.getSystemLanguage(); //获取当前系统语言
  if(!isWindows){ // c++层仅实现了win平台下的系统语言获取
    language = app.getLocale();
  }
  console.log('系统language:::',JSON.stringify(language));

  let configLanguage = global.ConfigIni.getConfig({key:'language'});

  if (config.clientConfig.auth.openLanguageSet && configLanguage) { //如果开启了语言配置
    language = configLanguage;
  }
  global.language = language;
  let result = global.service.config.setLanguage({language: language}); //设置SDK语言
  global.service.log(`将界面显示及sdk的语言设置为：${language},设置SDK语言的结果为：${result}`)
}

/************************************************************* */
// 检测更新
function updateApp() {
  if (isWinXp) return
  autoUpdater.autoDownload = false;
  autoUpdater.autoInstallOnAppQuit = false;
  let message={
    updateError:'检查更新出错',
    updateChecking:'正在检查更新……',
    updateAvailable:'检测到新版本，准备下载……',
    updateNotAvailable:'现在使用的就是最新版本，不用更新'
  };
  // 更新出错
  autoUpdater.on('error', ()=>{
    log.info("更新出错");
    global.service.log(message.updateError)
    mainWindow._window.webContents.send('update-result',{
      message: message.updateNotAvailable,
      isAvaible: false,
      updateUrl
    })
  });
  // 检测更新
  autoUpdater.on('checking-for-update', (mes)=> {
    log.info(mes,"checking-for-update检测更新");
    global.service.log(message.updateChecking)
    // mainWindow._window.webContents.send('update-result', message.updateChecking)
  });
  // 检测到可用更新
  autoUpdater.on('update-available', info=> {
    log.info(info,"update-available");
    // global.service.log(message.updateAvailable)
    // log.info(app.getPath('userData'))
    // mainWindow._window.webContents.send('update-result', {
    //   message: message.updateAvailable,
    //   isAvaible: true,
    //   updateUrl,
    //   info
    // })
    // let fullPath = path.join(app.getPath('userData'), `installer-${info.version}.exe`);
    // global.service.log(fullPath)
    // let fileOperateParam = { filepath: fullPath, type: 0 }
    // global.service.log(global.service.file.fileOperate(fileOperateParam))
    log.info(autoUpdater.getFeedURL())
    mainWindow._window.webContents.send('updateAvailable', info)
    // if(global.service.file.fileOperate(fileOperateParam)) {
    //   log.info('安装包已下载……')
    //   autoUpdater.autoDownload = true
    //   mainWindow._window.webContents.send('downloadedAvailable')
    // }
    // log.info('安装包已下载……')
    // autoUpdater.autoDownload = true
    // mainWindow._window.webContents.send('downloadedAvailable')
  });
  // 目前已是最新更新
  autoUpdater.on('update-not-available', ()=> {
    log.info("update-not-available");
    global.service.log(message.updateNotAvailable)
    mainWindow._window.webContents.send('update-not-available',message.updateNotAvailable)
    // mainWindow._window.webContents.send('update-result', {
    //   message: message.updateNotAvailable,
    //   isAvaible: false,
    //   updateUrl
    // })
  });
  // 更新下载进度
  autoUpdater.on('download-progress', progressObj => {
    log.info('正在下载……', progressObj.percent)
    mainWindow._window.webContents.send('downloadProgress', progressObj)
  })
  // 准备开始安装
  autoUpdater.on('update-downloaded', info=> {
    log.info('准备安装更新……',info)
    ipcMain.on('is-update-now', () => {
      autoUpdater.quitAndInstall()
    })
    mainWindow._window.webContents.send('isUpdateNow', info.version)
  });
}
//解析启动参数
function parseLaunchParam(){
  // global.serversLoginParam = {
  //   account:'008618710372423',
  //   server:'vrv',
  //   userType:1,
  //   pwd:'a1234567'
  // }
  //global.openDebugModel = true;  //开启调试模式 
  if(!process.argv[1]) return;
  if(process.argv[1].toLowerCase() === 'debug'){
    global.openDebugModel = true;  //开启调试模式 
    return;
  }
  if(process.argv[1].substr(0,12) === 'serversLogin'){
    // 多服务器启动参数
    try {
      let data = decryStr(process.argv[1].substr(12));
      global.serversLoginParam = JSON.parse(data);
    } catch (error) {
      app.quit();
    }
  }
}
// 主入口，监听3种事件并分发到子窗口
function main() {
  app.commandLine.appendSwitch('--ignore-certificate-errors')
  // global.openDebugModel = true;// 调试时开启
  global.openDebugModel = false;
  parseLaunchParam();
  enableSourceMaps()
  //  程序运行起来后就获取配置文件内容
  global.ConfigIni = new ConfigIni();
  global.AppPath = AppPath;
  
  SDK.init(newWindow)
  updateApp() //静默安装后提示安装，参照VSCODE

  handleProcess()
  handleApp()
  handleIpcMainRoute()
  global.postMsgToRender = postMsgToRender;
  global.judgePlginSubWinStatus = judgePlginSubWinStatus;
  global.isOpenMediaMsgPreivew = isOpenMediaMsgPreivew;
  global.getFileIcon = getFileIcon;
  global.isWinXpVersion = pkg.isWinXp;
  global.getWindowStatus = () => {
    return mainWindow._window.isFocused() && mainWindow._window.isVisible()
  };

  global.images = require('../comm/images');
}

main()
