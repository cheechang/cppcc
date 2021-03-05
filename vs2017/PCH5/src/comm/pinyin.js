/** ****************************************插 入 的 index 位 置 ******************************************* */
export function getListIndex(list, pinyin) {
  if (list.length === 0) {
    return 0;
  }
  if (pinyin === '#') {
    return list.length;
  }
  for (let key = 0; key < list.length; key++) {
    if (list[key].pinyin === '#') {
      return key;
    }
    if (list[key].pinyin < pinyin) {
      continue;
    } else if (list[key].pinyin === pinyin) {
      return key;
    } else {
      return key;
    }
  }
  return list.length;
};
/** ****************************************插 入 项 的 首 字 母（大写） ******************************************* */
export function conversionPinYin(pinyin) {
  let pinyinType =  /[^\a-\z\A-\Z]/g;
  if(!pinyin||!pinyinType.test(pinyin.substr(0, 1)))
  return '#';
  pinyin = pinyin.substr(0, 1).toUpperCase();
  if ((pinyin < 'A') || (pinyin > 'Z')) {
    pinyin = '#';
  }
  return pinyin;
};

export function converseFullPinYin(pinyin) {
  let pinyinType =  /^[a-zA-Z]/g;
  if(!pinyin||!pinyinType.test(pinyin.substr(0, 1)))
  return `|${pinyin}`;
  let newPinyin = pinyin.substr(0, 1).toUpperCase();
  if ((newPinyin < 'A') || (newPinyin > 'Z')) {
    pinyin = `|${pinyin}`;
  }
  return pinyin;
};
