import DInput from './Input.vue';
import {
  use,
  Plugin
} from '../../utils/plugins';

const plugin = new Plugin(DInput);

use(plugin);

export default plugin;

export {
  DInput
};
