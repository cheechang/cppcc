import DRadio from './Radio.vue';
import {
  use,
  Plugin
} from '../../utils/plugins';

const plugin = new Plugin(DRadio);

use(plugin);

export default plugin;

export {
  DRadio
};
