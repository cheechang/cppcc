import i18n from './../../comm/i18n';
function getPwdRuleString(rule) {
  let strRule = i18n.t('auth.pwdClaim');
  let minLength = rule.minLength !== 0 ? rule.minLength : 6;
  strRule = strRule + minLength + i18n.t('auth.characters');

  if (rule.digital || rule.low_alp || rule.up_alp || rule.alp || rule.spec_alp) {
    strRule += i18n.t('auth.containing');
  }
  
  if (rule.digital) {
    strRule += i18n.t('auth.number');
  }
  if (rule.low_alp) {
    strRule += i18n.t('auth.lowerCharacters');
  }
  if (rule.up_alp) {
    strRule += i18n.t('auth.uppercaseCharacters');
  }
  if (rule.alp) {
    strRule += i18n.t('auth.englishAlphabet');
  }
  if (rule.spec_alp) {
    strRule += i18n.t('auth.specialCharacters');
  }
  console.log('rule::', strRule, ' index::', );
  if (strRule.indexOf('、') !== -1) {
    strRule = strRule.substring(0, strRule.lastIndexOf('、'));
  }
  
  strRule += '.';
  return strRule;
}

function analysisPwdRule(rule, pwd) {
  if (rule.minLength > pwd.length) {
    return false;
  }
  if (rule.digital) {
    let regDigital = new RegExp('^(?=.*[0-9])');
    if (!regDigital.test(pwd)) {
      return false;
    }
  }
  if (rule.alp) {
    let regAlp = new RegExp('^(?=.*[a-zA-Z])');
    if (!regAlp.test(pwd)) {
      return false;
    }
  }

  if (rule.low_alp) {
    let regLowAlp = new RegExp('^(?=.*[a-z])');
    if (!regLowAlp.test(pwd)) {
      return false;
    }
  }

  if (rule.up_alp) {
    let regUpAlp = new RegExp('^(?=.*[A-Z])');
    if (!regUpAlp.test(pwd)) {
      return false;
    }
  }

  if (rule.spec_alp) {
    let regSpecAlp = new RegExp(/[`~!@#$%^&*()_\-+=<>?:"{}|,.\/;\'\\[\]·~！@#￥%……&*（）——\-+={}|《》？：“”【】、；‘’，。、]/im);
    if (!regSpecAlp.test(pwd)) {
      return false;
    }
  }
  return true;
}

function versionCompire(ver1, ver2) {
  ver1 = ver1.toUpperCase().replace("V", "")
  let version1pre = parseFloat(ver1);
  let version2pre = parseFloat(ver2);
  let version1next = ver1.replace(version1pre + ".", "");
  let version2next = ver2.replace(version2pre + ".", "");
  if (version1pre === version2pre) {
    return version1next >= version2next
  } else {
    return version1pre > version2pre
  }
}

/**
 * @breif 判断两个版本号大小
 * @param {string} ver1
 * @param {string} ver2
 * @return {number} 如果ver1 > ver2 返回 1 ver1 = ver2 返回0 ver1 < ver2 返回-1
 */
function versionCompirePro(ver1, ver2) {
  console.log('in versionCompirePro');
  console.log(ver1);
  console.log(ver2);
  ver1 = ver1.toUpperCase().replace("V", "");
  ver2 = ver2.toUpperCase().replace("V", "");
  let tempV1 = ver1.split('.');
  let tempV2 = ver2.split('.');
  let lens = Math.min(tempV1.length, tempV2.length);
  console.log(tempV1);
  console.log(tempV2);
  console.log(lens);
  for (let i = 0; i < lens; i++) {
    if (tempV1[i] === tempV2[i]) {
      continue;
    }
    return tempV1[i] > tempV2[i] ? 1 : -1;
  }
  return 0;
}

/**
 * 获取是否4.6服务，区分处理4.6服务的群成员优化
 */
// function isOpenedForSaveImg(ver1, ver2) {
//   console.log('isOpenedForSaveImg:::'+ver1, ver2)
//   ver1 = ver1.toUpperCase().replace('V', '')
//   let version1pre = parseFloat(ver1);
//   let version2pre = parseFloat(ver2);
//   console.log(version1pre, version2pre)
//   return version1pre === version2pre
// }

// 统一入口处理错误码提示
function getErrorMsg(code) {
  let ErrorCode = i18n.messages[`${i18n.locale}`].ErrorCode;
  let errorMsg = ErrorCode[code] ? ErrorCode[code] : `${i18n.t('auth.unknown') + code}`
  return errorMsg
}
//根据在线状态获取图标等信息
function getOnlineStatusInfo(flag){
  //1:在线,2:隐身,3:忙碌,4:离开,5:请勿打扰
  let onlineStatusInfo;
  switch (flag) {
    case 1:
    case 6:
      onlineStatusInfo = {key:1,name:i18n.t('user.online'),icon:'&#xe62f;',color:'#57E26D'};
      break;
      case 2:
      onlineStatusInfo = {key:2,name:i18n.t('user.invisible'),icon:'&#xe7ac;',color:'#FEC13E'};
      break;
      case 3:
      onlineStatusInfo = {key:3,name:i18n.t('user.busy'),icon:'&#xe7a0;',color:'#F94A2B'};
      break;
      case 4:
      case -1:
      case 7:
      case 8:
      onlineStatusInfo = {key:4,name:i18n.t('user.offline'),icon:'&#xe60d;',color:'#AEAEAE'};
      break;
      case 5:
      onlineStatusInfo = {key:5,name:i18n.t('user.disturb'),icon:'&#xe6e0;',color:'#E65645'};
      break;
    default:
      onlineStatusInfo = {key:1,name:i18n.t('user.online'),icon:'&#xe62f;',color:'#57E26D'};
      break;
  }
  return onlineStatusInfo;
}
/******************************************************************************** */
//获取当前时间,格式为:yyyy-mm-dd hh:mm:ss
function getCurrentDate() {
  let now = new Date();
  let year = now.getFullYear(); //得到年份
  let month = now.getMonth(); //得到月份
  let date = now.getDate(); //得到日期
  let hour = now.getHours(); //得到小时
  let minu = now.getMinutes(); //得到分钟
  let sec = now.getSeconds(); //得到秒
  month = month + 1;
  if (month < 10) month = "0" + month;
  if (date < 10) date = "0" + date;
  if (hour < 10) hour = "0" + hour;
  if (minu < 10) minu = "0" + minu;
  if (sec < 10) sec = "0" + sec;
  let time = "";
  time = year + "-" + month + "-" + date + " " + hour + ":" + minu + ":" + sec;
  return time;
}
/******************************************************************************** */
export {
  getPwdRuleString,
  analysisPwdRule,
  versionCompire,
  versionCompirePro,
  getErrorMsg,
  getOnlineStatusInfo,
  getCurrentDate,
  // isOpenedForSaveImg
};
