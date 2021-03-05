import DIcon from './Icon.vue';
import {
  use,
  Plugin
} from '../../utils/plugins';

const plugin = new Plugin(DIcon);

use(plugin);

export default plugin;

export {
  DIcon
};
