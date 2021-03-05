/******************************************** 豆豆表情 ******************************************* */
import DOOD_EMOJI from "./EmojiData/dood_emoji";
import TEXT_EMOJI from "./EmojiData/text_emoji";

const doodReg = /\[[\u4e00-\u9fa5]{1,4}\]/;

/**
 *
 *
 * @export
 * @param {any} msg
 * @returns
 */
export function doudouExpression(msg) {
  let doodExpReg = /\[?[^\[\]]+\]?/g;
  let msgArr = msg.match(doodExpReg);
  let tempMsgArr = [];
  let doodEmoji = JSON.stringify(DOOD_EMOJI);
  for (const m in msgArr) {
    // if (doodReg.test(msgArr[m])) {
      if (doodEmoji.indexOf(msgArr[m]) != -1) {
        for (const w in DOOD_EMOJI) {
          if (msgArr[m] == DOOD_EMOJI[w].name || msgArr[m] == DOOD_EMOJI[w].enname) {
            let pngName = DOOD_EMOJI[w].code;
            let item = `<img class='v-text-emoji' type="emoji" alt='${
              msgArr[m]
            }' src='${
              require('vrv-static/resources/images/emoji/text_emoji/' + pngName + '.png')}'>`;
            tempMsgArr.push(item);
            break;
          }
        }
      } else {
        tempMsgArr.push(msgArr[m]);
      }
    // } else {
    //   tempMsgArr.push(msgArr[m]);
    // }
  }
  return tempMsgArr.join("");
}

/**
 * utf-16转unicode
 *
 * @export
 * @param {any} str
 * @returns
 */
export function utf16toEntities(str) {
  // let patt = /[\ud800-\udbff][\udc00-\udfff]/g; // 检测utf16字符正则
  let patt = /[\uD83C|\uD83D|\uD83E][\uDC00-\uDFFF][\u200D|\uFE0F]|[\uD83C|\uD83D|\uD83E][\uDC00-\uDFFF]|[0-9|*|#]\uFE0F\u20E3|[0-9|#]\u20E3|[\u203C-\u3299]\uFE0F\u200D|[\u203C-\u3299]\uFE0F|[\u2122-\u2B55]|\u303D|[\A9|\AE]\u3030|\uA9|\uAE|\u3030/gi;
  let textEmoji = JSON.stringify(TEXT_EMOJI);
  str = str.replace(patt, function(char) {
    let H;
    let L;
    let code;
    if (char.length === 2) {
      [H, L] = [char.charCodeAt(0), char.charCodeAt(1)]; // 取出高,低位
      code = (H - 0xd800) * 0x400 + 0x10000 + L - 0xdc00; // 转换算法
      if (
        textEmoji.indexOf(code.toString(16)) != -1 ||
        code.toString(16)[0] === "-"
      ) {
        try {
          return `<img class='v-text-emoji' type="emoji" alt='${code.toString(
            16
          )}' src='${require('vrv-static/resources/images/emoji/text_emoji/' +
            code.toString(16) +
            '.png')}'>`;
        } catch (error) {
          return char
        }
      } else {
        return char;
      }
    } else {
      if (textEmoji.indexOf(char.charCodeAt().toString(16)) != -1) {
        try {
          return `<img class='v-text-emoji' type="emoji" alt='${char
            .charCodeAt()
            .toString(
              16
            )}' src='${require('vrv-static/resources/images/emoji/text_emoji/' + char
              .charCodeAt()
              .toString(16) + '.png')}'>`;
        } catch (error) {
          return char;
        }
      } else {
        return char;
      }
    }
  });
  return str;
}

/**
 * unicode 转 utf-16
 *
 * @export
 * @param {any} code
 * @returns
 */
export function toUnicode(code) {
  const codes = code.split("-").map(function(value, index) {
    return parseInt(value, 16);
  });
  return String.fromCodePoint.apply(null, codes);
}

/** 转换所有消息中的表情 */
export function escapeEmoji(msg) {
  // emojob编码集，正则匹配iOS10.2.1及之前的全部emoji表情
  let regs = /[\uD83C|\uD83D|\uD83E][\uDC00-\uDFFF][\ud83d|\ude0c][\u200D|\uFE0F]|[\uD83C|\uD83D|\uD83E][\uDC00-\uDFFF]|[0-9|*|#]\uFE0F\u20E3|[0-9|#]\u20E3|[\u203C-\u3299]\uFE0F\u200D|[\u203C-\u3299]\uFE0F|[\u2122-\u2B55]|\u303D|[\A9|\AE]\u3030|\uA9|\uAE|\u3030/gi;
  if (regs.test(msg)) msg = utf16toEntities(msg); // 将表情转成对应的unicode码

  // let doodReg = /\[[\u4e00-\u9fa5]{1,4}\]/g;
  // if (doodReg.test(msg)) 
  msg = doudouExpression(msg) || msg; //处理收到的豆豆表情

  return msg
}
// 转义字符换成普通字符
export function escape2Html(str) {
  const arrEntities = {
    lt: "<",
    gt: ">",
    nbsp: " ",
    amp: "&",
    quot: '"'
  };
  return str.replace(/&(lt|gt|nbsp|amp|quot);/gi, function(all, t) {
    return arrEntities[t];
  });
}

export function html2Escape(sHtml) {
  return sHtml.replace(/[<>&"]/g, function(c) {
    return {
      '<': '&lt;',
      '>': '&gt;',
      '&': '&amp;',
      '"': '&quot;'
    }[c];
  });
}

export function escapeHTMLString(str) {
  str = str.replace(/</g, '&lt;');
  str = str.replace(/>/g, '&gt;');
  return str;
}


/**
 * 去除多余标签
 *
 * @export
 * @param {any} HTML
 * @param {any} msgContent
 * @returns
 */
export function removeHtml(HTML, msgContent) {
  if (msgContent.indexOf("<br>" > -1)) {
    msgContent = msgContent.replace(/<br>/g, "\n");
  }


  msgContent = escape2Html(msgContent);

  /**
   * 去除span 标签
   */
  const spans = HTML.getElementsByTagName("span");
  for (const s in spans) {
    msgContent = msgContent.replace(/<span\s*[^>]*>(.*?)<\/span>/gi, "$1");
  }

  // const anodes = HTML.getElementsByTagName("span");
  // for (const s in anodes) {
  //   msgContent = msgContent.replace(/<a\s*[^>]*>(.*?)<\/a>/gi, "$1");
  // }
  // 防止在其他编辑软件中复制过来的文字 携带有DIV标签
  // msgContent = msgContent.replace(/<div>|<\/div>/gi, "");
  /**
   * 去除多图片标签
   */
  let fileAndImgMsgList = []
  let relatedUsers = []
  const images = HTML.getElementsByTagName("img");
  for (const img of images) {

    let imgType = img.getAttribute('type')
    console.log('imgType', imgType)
    if (imgType === 'at') {
      relatedUsers.push(img.title)
      msgContent = msgContent.replace(/<img(?:.|\s)*?>/i, img.getAttribute('value'))
    } else if (imgType === 'emoji') {
      let imgAlt = img.getAttribute('alt')
      msgContent = msgContent.replace(/<img(?:.|\s)*?>/i, doodReg.test(imgAlt) ? imgAlt : toUnicode(imgAlt))
    } else {
      fileAndImgMsgList.push(img)
      msgContent = msgContent.replace(/<img(?:.|\s)*?>/i, '')
    }
  }
  return {
    content: msgContent,
    fileAndImgMsgList: fileAndImgMsgList,
    relatedUsers: relatedUsers
  };
}
