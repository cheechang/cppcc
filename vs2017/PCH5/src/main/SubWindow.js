import {screen} from 'electron'
import { isDev ,isOSX,isWindows, isWinXp} from '../comm/is'
import { BrowserWindow } from 'electron'
import { resolve } from 'path'

const log = require('electron-log')

export class SubWindow {
  
  constructor(winParams) {
    this.winParams = winParams
    this.createWindow()
  }

  handleShow(preventRtcSubWindows) {
    let winType = this.winParams.winType
    return new Promise(resolve => {
      if(isWinXp){
        this._window.webContents.once('dom-ready',() =>{
          console.log('=====dom-ready=====')
          if(winType === 'mediadood') {
            this._window.maximize();
            this.winParams.showSubwindow(winType, this.winParams.winUrl);
          }
          let typeResult = (winType ==='RTCP2P'||winType === 'RemoteControl'||winType === 'RtcFile')&&preventRtcSubWindows
          if(!typeResult){
            this.winParams.isWinShow&&this._window.show()
          } else {
            if(winType === 'RTCP2P'||winType === 'RemoteControl'){
              log.info('RTCP2P|RemoteControl::')
              this._window.webContents.send('closeRtc')
            }
            if(winType === 'RtcFile') {
              log.info('RtcFile::')
              this._window.webContents.send('colseFile')
            }
          }
          resolve(typeResult)
        })
      }else{
          this._window.once('ready-to-show', () => {
            if(winType === 'mediadood') {
              this._window.maximize();
              this.winParams.showSubwindow(winType, this.winParams.winUrl);
            }
            let typeResult = (winType ==='RTCP2P'||winType === 'RemoteControl'||winType === 'RtcFile')&&preventRtcSubWindows
            if(!typeResult){
              this.winParams.isWinShow&&this._window.show()
            } else {
              if(winType === 'RTCP2P'||winType === 'RemoteControl'){
                log.info('RTCP2P|RemoteControl::')
                this._window.webContents.send('closeRtc')
              }
              if(winType === 'RtcFile') {
                log.info('RtcFile::')
                this._window.webContents.send('colseFile')
              }
            }
            resolve(typeResult)
          })
      }
    })
  }

  handleClose() {
    let winType = this.winParams.winType
    return new Promise(resolve => {
      this._window.once('close',e => {
        if(winType === 'RTCP2P'||winType === 'RemoteControl'){
          e.preventDefault()
          log.info('handleClose>>RTCP2P|RemoteControl::')
          if(!this._window.webContents.isDestroyed()){
            this._window.webContents.send('closeRtc')
          }
        }
        if(winType === 'RtcFile') {
          e.preventDefault()
          log.info('handleClose>>RtcFile::')
          this._window.webContents.send('colseFile')
        }
        if(winType === 'mediadood'){
          // e.preventDefault()
          // log.info('handleClose>>mediadood::', this.winParams)
          // this._window.webContents.send('closeMeeting')
          this.winParams.closeSubwindow('mediadood', this.winParams.winUrl);
        }
        if(winType === 'InternalWindow') {
          global.postMsgToRender('plugin-notify',false);
          // if (this._window) {
          //   this._window.webContents.send('closeRtc')
          // }
          this.winParams.closeSubwindow(winType,this.winParams.winUrl);
          // e.preventDefault()
          // log.info('handleClose>>InternalWindow::')
          // this._window.webContents.send('closeMultiMeeting')
          // if (this._window) {
          //   this._window.webContents.send('closeRtc')
          // }
        }
        if(winType === 'app'){
          //删除云盘缓存文件
          let path = global.service.config.userFilePath() + 'cloudData/cache'
          log.info('removeCloudData::',path);
          global.service.file.fileOperate({filepath:path , type: 2});
        }
        resolve()
      })
    })
  }

  load(winUrl) {
    // this._window.loadURL(winUrl);
    // return;
    log.debug('>>>>>>>>'+this.winParams.winType, winUrl)
    if (this.winParams.winType !== 'app') {
      this._window.loadURL(winUrl)
    } else {
      let path = '/node_modules/vrv-static/plugins/doodexplorer'
      let explorerPath = isDev ? (isOSX 
            ? `file://${resolve(__dirname, `../..${path}/index.html`)}` 
            : resolve(__dirname, `../..${path}/index.html`))
          : `file://${resolve(__dirname, `.${path}/index.html`)}`
      log.debug('explorerPath:::', explorerPath)
      this._window.loadURL(explorerPath)
    }
  }

  createWindow() {
    log.debug('winParams:::', this.winParams)
    let shapeTypes = {
      normal: {frame:this.winParams.winFrame, alwaysOnTop: false, resizable: true, x: (screen.getAllDisplays()[0].size.width - 800) / 2, y: (screen.getAllDisplays()[0].size.height - 600) / 2, fullscreen: false},
      top: {frame:false, alwaysOnTop: true, resizable: false, x:0 , y:0, fullscreen: true}
    }
    let winProperty = {
      title: this.winParams.winTitle,    
      frame: shapeTypes[this.winParams.shapeType]['frame'],
      show: false,
      fullscreen: shapeTypes[this.winParams.shapeType]['fullscreen'],
      alwaysOnTop : shapeTypes[this.winParams.shapeType]['alwaysOnTop'],
      icon: this.winParams.winIcon ? this.winParams.winIcon:resolve(__dirname, '../../node_modules/vrv-static/resources/images/icons/windows/logo.ico'), //MACOS 有问题     
      useContentSize: true,
      autoHideMenuBar: true,
      width: this.winParams.width,
      height: this.winParams.height,
      titleBarStyle:'hiddenInset',
      webPreferences: {
        experimentalFeatures: true,
        webSecurity: false,
        nodeIntegration: true,
        webviewTag: true,
        contextIsolation: false,
        devTools: isDev || global.openDebugModel
      }
    }
    if (this.winParams.winType!=='RTCP2P') {
      Object.assign(winProperty, {
        minWidth: this.winParams.width,
        minHeight: this.winParams.height
      })
    }
    this._window = new BrowserWindow(winProperty)
    if (isWindows && !isWinXp) {
      this._window.setAppDetails({
        appId: 'vrv.linkdood.h5',
        appIconPath: resolve(__dirname, isDev?'../../node_modules/vrv-static/resources/images/icons/windows/logo.ico':'./node_modules/vrv-static/resources/images/icons/windows/logo.ico')
      })
    }
    this.handleWindow()
  }

  handleWindow() {
    this._window.on('maximize', () => {
      this._window.webContents.send('sub-win-state', 'maximize')
    })

    this._window.on('unmaximize', () => {
      this._window.webContents.send('sub-win-state', 'unmaximize')
    })

    this._window.webContents.once('did-finish-load', () => {
      if (isDev || global.openDebugModel) {
        this._window.webContents.openDevTools()
      }
    })
    this._window.webContents.on('before-input-event', (event, input) => {
      if (input.type === 'keyUp') {
        if(input.key === 'Escape')
          this._window.close()
      }
    })
  }
}