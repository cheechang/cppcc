/******************************************最后一条消息处理****************************************/
import I18n from '../../../comm/i18n'

const msgType = {
  2: '[文本]',
  3: '[音频]',
  4: '[位置]',
  5: '[图片]',
  6: '[文件]',
  7: '[名片]',
  8: '[弱提示]',
  9: '[网页链接]',
  12: ' ',
  13: '[聊天记录]',
  14: '[音视频消息]',
  15: '[音视频消息]',
  18: '[撤回]',
  19: '[动态表情]',
  26: '[模板消息]',
  28: '[图片]',
  36: '[应用分享]',
  37: '[潜水者]',
  64: "[群公告]",
  89: '[微视频]',
  100: '[系统消息]',
  147: '[文件直传...]'
}
// "1001": "[密聊模式]",
// "1002": "[阅后即焚]",
// "1003": "[抖一抖]",
// "1004": "[橡皮擦]",
// "1005": "[暂不支持类型]"

function changeText(text) {
  function html2Escape(text) {
    return text.replace(/[<>&"]/g, function(c) {
      return {
        '<': '&lt;',
        '>': '&gt;',
        '&': '&amp;',
        '"': '&quot;'
      }[c];
    });
  }
  text = html2Escape(text);
  text = text.replace(/\n/g, '<br/>').replace(/\s/g, '&nbsp');
  return text;
}

export function getLastMessage(msg, cb) {
  // try {
  // const msgProps = msg.msgProp && JSON.parse(msg.msgProp) // 密聊优先级高于阅后即焚
  // if (msgProps.hasOwnProperty('enVchat')) return '[密聊消息]'

  // } catch (error) {
  // }
  console.log('msg:::', msg)
  try {
    const msgProps = msg.msgProp && JSON.parse(msg.msgProp) // 密聊优先级高于阅后即焚
    // console.log('msgProps:::', msgProps)
    if (msgProps && msgProps['enVchat']) {
      return I18n.t(`msgType.1001`)
    }
    //   } catch (error) {
    // }
    // if (msg.operType === 1) return '[阅后即焚]' // 阅后即焚
    if (msg.operType === 1) {
      return I18n.t(`msgType.1002`)
    }

    const msgTypeID = msg.msgType & 0x00ff
    if (msgTypeID === 2) {
      // try {

      if (msg.hasOwnProperty('delSign')) { /** delSign 自己手动添加的最近会话标识 */
        if (msg.lastMsg) {
          return JSON.parse(msg.lastMsg).body
        } else {
          cb(msg)
          return ' '
        }
      }

      let msgBody = JSON.parse(msg.lastMsg).body || ' '

      if (msgBody.includes('&:delete|')) { // 橡皮擦消息 
        return I18n.t(`msgType.1004`)
      }

      if (msgBody.includes('&:flash')) {
        msgBody = msgBody.replace('&:flash', I18n.t(`msgType.1003`));
        if (msgBody === I18n.t(`msgType.1003`)) {
          return I18n.t(`msgType.1003`) // 抖一抖
        }
      }
      // 不进行文本的格式转换
      if(!msg.hasOwnProperty('banChangeText')){
        msgBody = changeText(msgBody)
      }
      // return msg.lastMsg ? msg.chatType === 2 && msg.whereFrom !== '' ? `${msg.whereFrom}:${msgBody}` : msgBody : ' '
      return msgBody || ' '
      // } catch (error) {
      //   console.log('text msg error:', error)
      // }

    } else if (msg.lastMsg && msgTypeID === 12) { // 网页链接消息
      return JSON.parse(msg.lastMsg)[0].title
    } else if (msgTypeID === 112 && msg.info) {
      return msg.info
    } else if (msgTypeID === 14) { // 音视频消息
      // let type = JSON.parse(msg.lastMsg).VideoType
      // if (type === '7') return '[弱提示]'
      // return  '[弱提示]';
      return I18n.t(`msgType.8`)
    } else if (msgTypeID === 15) { // 音视频消息

      let lastMsg = JSON.parse(msg.lastMsg)
      if (lastMsg.VideoType === '7' && lastMsg.VideoStatus === 'p2p_file') {
        //  return lastMsg.VideoStatus === 'p2p_file'? '[文件]' : '[弱提示]' 
        return I18n.t(`msgType.6`)
      }
      // return  '[弱提示]';
      return I18n.t(`msgType.8`)
    } else if (msgTypeID === 26) { // 模板消息
      msg.lastMsg = msg.lastMsg.replace(/[\r\n]/g, '<br>').replace(/\s/g, '&nbsp');
      return JSON.parse(msg.lastMsg).title
    } else if (msgTypeID === 64) {
      if (msg.subType === 2 || msg.subType === 3) {
        return '[置顶]'
      } else {
        return I18n.t(`msgType.${msgTypeID.toString()}`)
      }
    } 
    


    if (!msgType.hasOwnProperty(msgTypeID)) {
      // return "<暂不支持类型>"
      return I18n.t(`msgType.1005`) 
    } else {
      return I18n.t(`msgType.${msgTypeID.toString()}`)
    }

  } catch (error) {
    console.log('text msg error:', error)
    return ' '
  }
}

