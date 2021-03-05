import pkg from '../../package.json';
import { release } from 'os'
export const isDev =process.env.NODE_ENV == 'development'
export const isProd = process.env.NODE_ENV == 'production'
export const isTest = process.env.NODE_ENV == 'test'

export const isWinXp   = pkg.isWinXp
export const isWindows = process.platform === 'win32'
export const isOSX = process.platform === 'darwin'
export const isLinux = process.platform === 'linux'
export const isMobile = process.env.DEVICE_TYPE === 'mobile'

export const isRenderer = process.type === 'renderer'
export const isMain = process.type === 'browser'

export const isX86 = process.arch === 'ia32'
export const isX64 = process.arch === 'x64'

export const isSandbox = 'APP_SANDBOX_CONTAINER_ID' in process.env
export const isMas = process.mas === true
export const isWindowsStore = process.windowsStore === true;

export function isWeb() {
  let agent = navigator.userAgent.toLowerCase();
  return agent.indexOf("electron") === -1;
};
export function isWin7() {
  if(process.platform === 'win32'){
    let releaseArray = release().split('.');
    if(releaseArray[0] !== '10'){
      return true;
    }
  }
  return false;
};