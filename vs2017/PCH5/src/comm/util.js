import Vue from 'vue';
import Platform from '../comm/platform';
import { homedir } from 'os';
import { join, resolve } from 'path';

const fs = require('fs');
const path = require('path');
const crypto = require('crypto');
import config from './config';
let platform = new Platform();
const dbPath = join(homedir(), platform.platforminfo().dbPath);// 数据库目录
const secretKey = Buffer.from('BeiLjing2VRIV0SoftwaNre1CorpKoraDtioon9LimiDted', 'utf8');
/****************************************加密字符串********************************************* */
// 采用crypto aes加密
export function encryStr(str) { //str 为utf-8格式
  const cipher = crypto.createCipher('aes-128-ecb', secretKey);
  let enc = cipher.update(str, 'utf8', 'hex'); //编码方式从utf-8转为hex;
  enc += cipher.final('hex'); //编码方式从转为hex;
  return enc
}

/****************************************解密字符串********************************************* */
export function decryStr(str) { //str 为hex格式
  const decipher = crypto.createDecipher('aes-128-ecb', secretKey);
  let dec = decipher.update(str, 'hex', 'utf8'); //编码方式从hex转为utf-8;
  dec += decipher.final('utf8'); //编码方式从utf-8;
  return dec;
}
/****************************************判断是否为JSON***************************************** */
export function isJson(str) {
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
/** ****************************************获取16位数字 加密使用******************************************* */
export function encryptionPassword() {
  let num = '';
  for (let i = 0; i < 16; i++) {
    num += Math.floor(Math.random() * 10);
  }
  return num;
};

/** ************************************判断消息是否为网址******************************************* */
export function CheckUrl(url) {
  let reg = /(http|ftp|https|www):\/\/[\w\-_]+(\.[\w\-_]+)+([\w\-.,@?^=%&:/~+#]*[\w\-@?^=%&/~+#])?/;
  return (reg.test(url) ? url.replace(reg, function(a, b, c) {
    return '<a class="text-url" target="_blank" href="' + a + '">' + a + '</a>';
  }) : url.replace(/\n/g, '<br/>').replace(/\s/g, '&ensp;'));
};

export function isUrl(url) {
  var Expression = /http(s)?:\/\/([\w-]+\.)+[\w-]+(\/[\w- .\/?%&=]*)?/;
  var objExp = new RegExp(Expression);
  if (objExp.test(url) == true) {
    return true;
  } else {
    return false;
  }
};
/** ************************************绘制进度条******************************************* */
export function drawMain(drawingElem, percent, forecolor, bgcolor) {
  /*
      @drawingElem: 绘制对象
      @percent：绘制圆环百分比, 范围[0, 100]
      @forecolor: 绘制圆环的前景色，颜色代码
      @bgcolor: 绘制圆环的背景色，颜色代码
  */
  console.log(drawingElem, percent, forecolor, bgcolor);
  const context = drawingElem.getContext('2d');
  const centerX = drawingElem.width / 2;
  const centerY = drawingElem.height / 2;
  const rad = Math.PI * 2 / 100;
  let speed = 0;

  // 绘制背景圆圈
  function backgroundCircle() {
    context.save();
    context.beginPath();
    context.lineWidth = 24; // 设置线宽
    var radius = centerX - context.lineWidth;
    context.lineCap = 'round';
    context.strokeStyle = bgcolor;
    context.arc(centerX, centerY, radius, 0, Math.PI * 2, false);
    context.stroke();
    context.closePath();
    context.restore();
  }

  // 绘制运动圆环
  function foregroundCircle(n) {
    context.save();
    context.strokeStyle = forecolor;
    context.lineWidth = 24;
    context.lineCap = 'round';
    var radius = centerX - context.lineWidth;
    context.beginPath();
    context.arc(centerX, centerY, radius, -Math.PI / 2, -Math.PI / 2 + n * rad, false); // 用于绘制圆弧context.arc(x坐标，y坐标，半径，起始角度，终止角度，顺时针/逆时针)
    context.stroke();
    context.closePath();
    context.restore();
  }

  // 绘制文字
  function text(n) {
    context.save(); // save和restore可以保证样式属性只运用于该段canvas元素
    context.fillStyle = forecolor;
    let fontSize = 40;
    context.font = fontSize + 'px Helvetica';
    let textWidth = context.measureText(n.toFixed(0) + '%').width;
    context.fillText(n.toFixed(0) + '%', centerX - textWidth / 2, centerY + fontSize / 2);
    context.restore();
  }

  // 执行动画
  (function drawFrame() {
    window.requestAnimationFrame(drawFrame);
    context.clearRect(0, 0, drawingElem.width, drawingElem.height);
    backgroundCircle();
    text(speed);
    foregroundCircle(speed);
    if (speed >= percent) return;
    speed += 1;
  }());
}
/******************************************************************************** */
export function computeFileSize(fileSize) {
  let k = 1000, // or 1024
    sizes = ['B', 'KB', 'MB', 'GB'],
    i = Math.floor(Math.log(fileSize) / Math.log(k));

  return (fileSize / Math.pow(k, i)).toPrecision(3) + ' ' + sizes[i];
}
/******************************************************************************* */
/*
 * 读取本地配置文件config.ini
 *param = {key:'xxx'} 传入要查询的key
 */
export function getConfig(param) {
  const configPath = `${dbPath}config.ini`;
  if (fs.existsSync(configPath)) {
    let contentTextHex = fs.readFileSync(configPath, 'utf-8');
    try {
      let contentText = decryStr(contentTextHex); //解密字符串
      if (contentText && isJson(contentText)) {
        let contentObj = JSON.parse(contentText);
        if (contentObj.hasOwnProperty(param.key)) {
          return contentObj[param.key]
        }
      }
    } catch (error) {
      console.log('error:', error);
      fs.unlinkSync(configPath); ////如果发生解密字符串失败，则删除配置文件
    }
  }
  return '';
}
/******************************************************************************* */
/*
 * 写入本地配置文件config.ini
 *param = {key:'xxx',value:'xxx'} 传入要查询的key及value
 */
export function setConfig(param) {
  let tempObj = {};
  const configPath = `${dbPath}config.ini`;
  if (fs.existsSync(configPath)) {
    let contentTextHex = fs.readFileSync(configPath, 'utf-8');
    try {
      let contentText = decryStr(contentTextHex); //解密字符串
      if (contentText && isJson(contentText)) {
        tempObj = JSON.parse(contentText);
      }
    } catch (error) {
      fs.unlinkSync(configPath); //如果发生解密字符串失败，则删除配置文件
      console.log('error:', error);
    }
  }
  tempObj[param.key] = param.value;
  let tempStr = JSON.stringify(tempObj);
  fs.writeFileSync(configPath, encryStr(tempStr)); //加密后写入
}

/******************************************************************************** */
// 循环删除非空目录下的文件
export function rmdir(dir) {
  let arr = [dir]
  let current = null
  let index = 0

  while (current = arr[index++]) {
    // 读取当前文件，并做一个判断，文件目录分别处理
    try {
      let stat = fs.statSync(current)
      //如果文件是目录
      if (stat.isDirectory()) {
        //读取当前目录，拿到所有文件
        let files = fs.readdirSync(current)
        // 将文件添加到文件池
        arr = [...arr, ...files.map(file => path.join(current, file))]
      }
    } catch (error) {
      console.log('rmdirError:',error);
    }
  }
  //遍历删除文件
  for (var i = arr.length - 1; i >= 0; i--) {
    // 读取当前文件，并做一个判断，文件目录分别处理
    let stat = fs.statSync(arr[i])
    // 目录和文件的删除方法不同
    if (stat.isDirectory()) {
      try {
        fs.rmdirSync(arr[i])
      } catch (error) {
        console.log('rmdirSync:', error);
      }
    } else {
      try {
        fs.unlinkSync(arr[i])
      } catch (error) {
        console.log('unlinkSyncErr:', error);
      }
    }
  }
}

// 使用随机数和时间戳生成唯一ID
export function genID(length) {
  return Number(Math.random().toString().substr(3, length) + Date.now()).toString(36);
};
//通过gender及chatType获取默认头像
export function getAvatar(param){
  if(param.thumbAvatar){
    return param.thumbAvatar;
  }
  let defaultSrc = require('vrv-static/resources/images/contact/icon_head_unknow@3x.png');
  let sex = param.chatType==1?param.gender:param.chatType==2?4:3;
  if(param.id === '10000'){ //系统消息
    sex = 5;
  }
  let base64Src = config.defalutAvatar[sex] || defaultSrc;
  return Vue.prototype.$nativeImage.createFromDataURL(base64Src)
}

export function utf8ToUnicode(strUtf8) {
  var bstr = "";
  var nTotalChars = strUtf8.length;        // total chars to be processed.
  var nOffset = 0;                                        // processing point on strUtf8
  var nRemainingBytes = nTotalChars;        // how many bytes left to be converted
  var nOutputPosition = 0;
  let iCode = 0;
  let iCode1 = 0;
  let iCode2 = 0;                        // the value of the unicode.

  while (nOffset < nTotalChars) {
    iCode = strUtf8.charCodeAt(nOffset);
    if ((iCode & 0x80) == 0) {                       // 1 byte.
      if ( nRemainingBytes < 1 )                // not enough data
        break;

      bstr += String.fromCharCode(iCode & 0x7F);
      nOffset ++;
      nRemainingBytes -= 1;
    }
    else if ((iCode & 0xE0) == 0xC0) {        // 2 bytes
      iCode1 =  strUtf8.charCodeAt(nOffset + 1);
      if ( nRemainingBytes < 2 ||                        // not enough data
        (iCode1 & 0xC0) != 0x80 )                // invalid pattern
      {
        break;
      }

      bstr += String.fromCharCode(((iCode & 0x3F) << 6) | (         iCode1 & 0x3F));
      nOffset += 2;
      nRemainingBytes -= 2;
    }
    else if ((iCode & 0xF0) == 0xE0) {       // 3 bytes
      iCode1 =  strUtf8.charCodeAt(nOffset + 1);
      iCode2 =  strUtf8.charCodeAt(nOffset + 2);
      if ( nRemainingBytes < 3 ||                        // not enough data
        (iCode1 & 0xC0) != 0x80 ||                // invalid pattern
        (iCode2 & 0xC0) != 0x80 ) {
        break;
      }

      bstr += String.fromCharCode(((iCode & 0x0F) << 12) |
        ((iCode1 & 0x3F) <<  6) |
        (iCode2 & 0x3F));
      nOffset += 3;
      nRemainingBytes -= 3;
    }
    else                                                             // 4 or more bytes -- unsupported
      break;
  }

  if (nRemainingBytes != 0) {
    // bad UTF8 string.
    return "";
  }
  return bstr;
}
/******************************************************************************** */
//获取配置文件中文件直传大小
export function getRtcFileSize() {
  const configPath = `${dbPath}fileConfig.ini`;
  if (fs.existsSync(configPath)) {
    let contentText = fs.readFileSync(configPath, 'utf-8');
    try {
      if (contentText) {
		  return parseInt(contentText);
      }
    } catch (error) {
      console.log('error:', error);
      return 128
    }
  }
  else{
    fs.writeFileSync(configPath, '128');
  }
  return 128;
}