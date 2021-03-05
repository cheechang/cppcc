import i18n from '../../../../comm/i18n'
import config from '../../../../comm/config'
/**
 * 获取加好友/群二维码链接
 * @param {String} id 用户id/群id
 * @param {String} host 默认为http://im.linkdood.cn 国际版为http://im.linkdood.com
 * @param {String} elogo 预登录中的 elogo
 * @param {String} serverhost 预登录中 prelist 中的非 ID 地址，如果都为 ID 则任意取
 * @param {Number} type 类型：1个人 2群
 */
export const getQrcodeLink = ({ id, host = 'http://im.vrv.cn', elogo, serverhost, type }) => {
  let qrcodeLink = '';
  elogo = 'qgzx'
  serverhost = config.clientConfig.auth.server
  switch (type) {
    case 1: // 个人
      qrcodeLink = `${host}/user/getinfo?uid=${id}&userver=${elogo}&serverhost=${serverhost}`
      break;
    case 2: // 群
      qrcodeLink = `${host}/group/getinfo?gid=${id}&userver=${elogo}&serverhost=${serverhost}`
      break;
  }
  console.log('qrcodeLink::::::::::::::;', qrcodeLink)
  return qrcodeLink;
}
/**
 * 获取邀请好友二维码链接
 * @param {String} host 国内默认http://im.linkdood.cn  国际版http://im.linkdood.com
 * @param {String} serverhost 预登录中 prelist 中的非 ID 地址，如果都为 ID 则任意取
 * @param {String} code 邀请码
 * @param {String} language 用户语言环境zh/en
 */
export const getInviteCodeLink = ({ host = 'http://im.linkdood.cn', serverhost, code }) => {
  console.log('inviteCodeLink::::::::::::::;', `${host}/regi/invite.html?code=${code}&serverhost=${serverhost}&language=${i18n.locale && i18n.locale.split('-')[0]}`)
  return `${host}/regi/invite.html?code=${code}&serverhost=${serverhost}&language=${i18n.locale && i18n.locale.split('-')[0]}`
}