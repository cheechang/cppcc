/**
 * Create by lpy 2019.7.5
 * 该模块负责写入和读取Confi.ini的内容
 */
import fs from 'fs';
import crypto from 'crypto';
import AppPath from './AppPath';

const secretKey = Buffer.from('BeiLjing2VRIV0SoftwaNre1CorpKoraDtioon9LimiDted', 'utf8');
const dbPath = AppPath.userCachePath();
console.log('***dbPath: ', dbPath);
// 采用crypto aes加密
function encryStr(str) {   //str 为utf-8格式
  const cipher = crypto.createCipher('aes-128-ecb', secretKey);
  let enc = cipher.update(str, 'utf8', 'hex'); //编码方式从utf-8转为hex;
  enc += cipher.final('hex'); //编码方式从转为hex;
  return enc
}

function decryStr(str) { //str 为hex格式
  const decipher = crypto.createDecipher('aes-128-ecb', secretKey);
  let dec = decipher.update(str, 'hex', 'utf8'); //编码方式从hex转为utf-8;
  dec += decipher.final('utf8'); //编码方式从utf-8;
  return dec;
}

function isJson(str) {
  if (typeof str === 'string') {
    console.log('str:' + str + '!!!');
    try {
      let obj = JSON.parse(str);
      return true;
    } catch (e) {
      console.log('error：' + str + '!!!' + e);
      return false;
    }
  }
}

export default class ConfigIni{
  constructor() {
    this.config = {};
    this._getIni();
  }

  _getIni() {
    const configPath = `${dbPath}config.ini`;
    if (fs.existsSync(configPath)) {
      let contentTextHex = fs.readFileSync(configPath, 'utf-8');
      try {
        let contentText = decryStr(contentTextHex); //解密字符串
        if (contentText && isJson(contentText)) {
          this.config = JSON.parse(contentText);
          console.log('i getIni: ', this.config);
     
          // if (contentObj.hasOwnProperty(param.key)) {
          //   return contentObj[param.key]
          // }
        }
      } catch (error) {
        console.log('error:', error);
        fs.unlinkSync(configPath);  ////如果发生解密字符串失败，则删除配置文件
      }
    }
  }

  /** 
   * 写入本地配置文件config.ini
   * @param {Object} {key:'xxx',value:'xxx'} 传入要查询的key及value
   */
  setConfig(param){
    // let tempObj = {};
    // if (!this.config) {
    //   return;
    // }
    this.config[param.key] = param.value;

    const configPath = `${dbPath}config.ini`;
    //if (fs.existsSync(configPath)) {
    let tempStr = JSON.stringify(this.config);
    fs.writeFileSync(configPath, encryStr(tempStr)); //加密后写入
    //}
  }

  showConfig() {
    return this.config
  }

  /**
   * 读取本地配置文件config.ini
   * @param {Object} {key:'xxx'} 传入要查询的key
   */
  getConfig(param) {
    console.log('getConfig key: ', param.key);
    console.log('getConfig config: ', this.config);

    if (this.config.hasOwnProperty(param.key)) {
      return this.config[param.key];
    }
  }
};