/**
 * Created by lpy on 2017/11/8.
 */
import Vue from 'vue';
import Vuei18n from 'vue-i18n';
import LangZh from 'vrv-static/data/language/zh.js';
import LangEn from 'vrv-static/data/language/en.js';

Vue.use(Vuei18n);

export const langConfig = {
  locale: 'zh-CN',
  messages: {
    'zh-CN': LangZh,
    'en-US': LangEn
  }
};

export default new Vuei18n(
  langConfig
);