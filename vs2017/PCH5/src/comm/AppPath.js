import { homedir } from 'os'
import { join, resolve } from 'path'
import Platform from './platform';
import { isDev } from './is'

let platform = new Platform();

export default {
  userCachePath() {
    return join(homedir(), platform.platforminfo().dbPath);
  },

  staticPath() {
    return resolve(__dirname, isDev ? '../../node_modules/vrv-static' : './node_modules/vrv-static');
  }
}