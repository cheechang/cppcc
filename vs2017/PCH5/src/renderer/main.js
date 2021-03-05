import Vue from 'vue';
import App from './App'
import router from './router'
import store from './store'
import vrvui from './ui'
import doui from './doui'
import i18n from '../comm/i18n'
import * as is from '../comm/is'
import VueChatScroll from './components/Chat/V-chat-scroll/vue-chat-scroll'
import vuescroll from 'vuescroll/dist/vuescroll-native';
import DatePicker from 'vue2-datepicker'
import 'vuescroll/dist/vuescroll.css';
import './polyfill';
Vue.use(vuescroll);
i18n.locale = Vue.prototype.$language;
/** 给vue添加属性 */
Vue.prototype.$is = is
Vue.prototype.$signalMonitor = new Vue()
Vue.prototype.$fs = require('fs')
Vue.prototype.$bus = new Vue()

Vue.use(vrvui);
Vue.use(doui);
Vue.use(VueChatScroll);
Vue.use(DatePicker);


new Vue({
  router,
  store,
  i18n,
  el: '#app',
  render: h => h(App)
});
