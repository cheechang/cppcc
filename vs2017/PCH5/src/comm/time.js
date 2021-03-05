var moment = require('moment');
import I18n from './i18n'

/** ****************************************计算时间戳显示******************************************* */
export const getDateDiff = (nS, simple) => {
  let result;
  let old =  moment(nS)
  let now = moment()
  let diffDay = Math.abs(now.dayOfYear() - old.dayOfYear());
  if (diffDay < 1) {
    result = old.format('HH:mm')
  } else if (diffDay >= 1 && diffDay < 2) {
    result = simple ?I18n.t('chat.yesterday') || old.format('MM-DD') : `${I18n.t('chat.yesterday')|| old.format('MM-DD')} ${old.format('HH:mm')}`;
  } else if (diffDay >= 2 && diffDay < 3) {
    result = simple ?  I18n.t('chat.towDaysAgo') ||old.format('MM-DD'): `${I18n.t('chat.towDaysAgo')|| old.format('MM-DD')} ${old.format('HH:mm')}`;
  } else {
    result = simple ? old.format('MM-DD'): old.format('YYYY-MM-DD HH:mm')
  }
  return result;
};

export const getLocalDate = () => {
  var date = new Date();
  date.setHours(0);
  date.setMinutes(0);
  date.setSeconds(0);
  date.setMilliseconds(0)
  return date.getTime();
}
