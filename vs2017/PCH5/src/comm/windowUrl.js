import { isDev ,isWindows} from './is'
import { resolve } from 'path'
const path = require('path')

const subWinTypes = {
  'RemoteControl': 0,
  'RTCP2P': 1,
  'RtcFile': 2,
  'MicroVideo': 3,
  'app': 4,
  'mediadood': 5,
  'Imagepreivew': 6,
  'MapPreview': 6,
  'msgRemind': 6,
  'inviteBuyServer':6,
  'versionIntro':7,
  'InternalWindow':8, // 内部窗口 
  'ExternalWindow':9,  // 外部窗口 
  'AbsoluteWindow': 'a' // 绝对链接窗口
}

let url = ''

function getModuleUrl(winUrl) {
  if (winUrl.indexOf('http') !== 0) {
    url = isDev ? (!isWindows 
        ? `file://${path.resolve()}/${winUrl}` 
        : resolve(__dirname, '../../node_modules/', winUrl) )
      : `file://${resolve(__dirname, './node_modules/', winUrl)}`
  }
}

function getIndexUrl(winUrl) {
  url = isDev
    ? `http://localhost:${process.env.ELECTRON_WEBPACK_WDS_PORT}/${winUrl}`
    : `file://${__dirname}/index.html${winUrl}`
}

function getAbsoluteUrl(winUrl){
  url = winUrl;
}

export function getWindowUrl(winType, winUrl) {
  url = ''
  let winObj = [
    [/^[0-2]$/, () => getIndexUrl(winUrl)],
    [/^[3-7]$/, () => getModuleUrl(winUrl)],
    [/^[8]$/, () => getIndexUrl(winUrl)],
    [/^[9]$/, () => getModuleUrl(winUrl)],
    [/^[a]$/, () => getAbsoluteUrl(winUrl)],
  ];
  [...winObj].filter(([key, value]) => key.test(subWinTypes[winType])).forEach(([key, value]) => value.call(this))
  return url
}