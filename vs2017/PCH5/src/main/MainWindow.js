
import { app, BrowserWindow, dialog,powerMonitor } from 'electron'
import { registerWindowStateChangedEvents } from '../comm/windowState'
import { isDev, isOSX, isWindows, isWinXp } from '../comm/is'
const log = require('electron-log')
import { resolve } from 'path'
import i18n from '../comm/i18n'
export class MainWindow {

  constructor(SDK) {
    // console.log('options:', options)
    // super(options)
    this._window = new BrowserWindow({
      title: i18n.t('window.title'),
      width: 960,
      minWidth: 438,
      height: isOSX ? 622 : 600,
      minHeight: isOSX ? 622 : 600,
      autoHideMenuBar: true,
      show: false,
      frame: isOSX,
      resizable: true,
      icon: resolve(__dirname, isDev?'../../node_modules/vrv-static/resources/images/icons/windows/logo.ico':'./node_modules/vrv-static/resources/images/icons/windows/logo.ico'),
      // transparent: true,
      webPreferences: {
        experimentalFeatures: true,
        webSecurity: false,
        nodeIntegration: true,
        webviewTag: true,
        contextIsolation: false,
        devTools: isDev || global.openDebugModel
      }
    })
    if (isWindows && !isWinXp) {
      this._window.setAppDetails({
        appId: 'vrv.linkdood.h5',
        appIconPath: resolve(__dirname, isDev?'../../node_modules/vrv-static/resources/images/icons/windows/logo.ico':'./node_modules/vrv-static/resources/images/icons/windows/logo.ico')
      })
    }
    this.isQuit = false
    this.SDK = SDK
    this.handleWindow()
  }

  isQuitByTrayMenu(isQuitByTrayMenu) {
    this.isQuit = isQuitByTrayMenu
  }

  exceptionDialog(msg) {
    const options = {
      type: 'info',
      title: 'Linkdood',
      message: msg,
      buttons: ['Reload', 'Close']
    }

    dialog.showMessageBox(options, (index) => {
      if (index === 0) this._window.reload()
      else this._window.close()
    })
  }

  quit() {
    this._window.close()
    //this.SDK.shutdown()
    app.quit()
  }

  handleWindow() {
    this._window.on('close', e => {
      if (!this.isQuit) {
        e.preventDefault()
        isOSX ? app.hide() : this._window.hide()
      }
    })

    this._window.on('maximize', () => {
      this._window.webContents.send('max-state')
    })



    this._window.on('focus', e => {
      console.log('focus::::')
      this._window.webContents.send('window-focus', true)
    })

    this._window.on('blur', () => {
      console.log('blur::::')
      this._window.webContents.send('window-focus', false)
    });

    this._window.on('unmaximize', () => {
      this._window.setSize(960, 600)
      this._window.webContents.send('unmax-state')
    })

    this._window.on('unresponsive', () => {
      this.exceptionDialog(global.language=='en-US'?'Not Responding':'应用无响应')
    })

    this._window.webContents.on('crashed', () => {
      this.exceptionDialog(global.language=='en-US'?'Application Crashed':'应用崩溃')
    })

    this._window.webContents.on('before-input-event', (event, input) => {
      if (input.type === 'keyUp') {
        if(input.key === 'c' && input.alt) {
          event.preventDefault()
        }
        if(input.key === 'f' && input.control) {
          this._window.webContents.send('start-local-search')
        }
      }
      if (input.type === 'keyDown') {
        if (input.key === 'F11') {
          event.preventDefault()
        }
        if ((isOSX?input.meta:input.control) && (input.key === 'ArrowDown' || input.key === 'ArrowUp')) {
          this._window.webContents.send('changeChatList', input.key)
        }
      }
    })

    this._window.webContents.once('did-finish-load', () => {
      if (isDev || global.openDebugModel) {
        this._window.webContents.openDevTools()
     }
    })

    this._window.webContents.on('did-fail-load', () => {
      this._window.show()
    })
  }
  load() {
    log.info('MainWindow load')
    console.log('=====MainWindow load=====')
    registerWindowStateChangedEvents(this._window)

    const url = isDev ?
      `http://localhost:${process.env.ELECTRON_WEBPACK_WDS_PORT}` :
      `file://${__dirname}/index.html`

    this._window.loadURL(url)
    if(isWinXp){
        this._window.webContents.once('dom-ready',() =>{
          console.log('=====dom-ready=====')
          this._window.setTitle(global.language=='en-US'?'Linkdood':'信源豆豆');
          this._window.show();
        })
    }
    this._window.once('ready-to-show', () => {
      console.log('=====ready-to-show=====')
      this._window.show();
      if(global.serversLoginParam){
        this._window.hide();
      }
      powerMonitor.on('resume', () => {
        log.warn('resume::::The system has resumed')
        global.service.user.wakeUp(null,(resp)=>{
          global.service.log(`wakeUpSdk:${JSON.stringify(resp)}`)
        });
      })
      log.warn("process.argv[1]:::",process.argv[1]);
      global.callPlugin.responseStartUp(process.argv[1]);
    })
  }
    // [key: string]: any // missing index defintion
}
