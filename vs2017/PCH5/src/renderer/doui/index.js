import './scss/doui-build.scss';
import './scss/common.scss';
import './static/font/iconfont/iconfont.css';
import * as components from './components';
import config, { setOptions } from './utils/config';
import { use, registerComponentProgrammatic } from './utils/plugins';

const Doui = {
  install(Vue, options = {}) {
    setOptions(Object.assign(config, options));
    console.log('in doui install:', components);
    for (const componentKey in components) {
      if (Object.prototype.hasOwnProperty.call(components, componentKey)) {
        Vue.use(components[componentKey]);
      }
    }

    const DouiProgrammatic = {
      setOptions(Options) {
        setOptions(Object.assign(config, Options));
      },
    };
    registerComponentProgrammatic(Vue, '$doui', DouiProgrammatic);
  },
};

use(Doui);

export default Doui;
