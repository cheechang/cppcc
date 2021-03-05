import i18n from '../../comm/i18n';
import { getErrorMsg,getCurrentDate } from "./utils.js";
//创建一个叫PresentTipByFlag的类
export default class PresentTipByFlag { 
//constructor构造函数
 constructor() {
   //先加载构造函数
  this.PresentTipByFlag = [
    {
      flag: -1,
      popupTip: i18n.t('auth.forcedOffLine', {value: getCurrentDate()})
    },
    {
     flag: 7,
     popupTip: i18n.t('account.pwdHasChanged')
    },
    {
     flag: 10,
     popupTip: getErrorMsg(10)
    },
    {
     flag: 11,
     popupTip: getErrorMsg(11)
    },
    {
     flag: 12,
     popupTip: getErrorMsg(12)
    },
    {
     flag: 13,
     popupTip: getErrorMsg(13)
    }
  ];
 }
 //getPresentTipByFlag方法 传入flag值
 getPresentTipByFlag(flag) {
   //map方法 var result = arr.map(function (item,index,array) {})
   //info => 代表function(item,index,array)
  this.PresentTipByFlag.map(info => {
    if (info.flag === flag) {
      this.PresentTipByFlag =  {flag: info.flag, popupTip: info.popupTip};
      return;
    }
  });
  console.log('--------------1 ', this.PresentTipByFlag);
  return this.PresentTipByFlag.popupTip;
  //返回popupTip值
 }
}