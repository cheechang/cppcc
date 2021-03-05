import DSelect from './Select.vue';
import { use, Plugin } from '../../utils/plugins';

const plugin = new Plugin(DSelect);

use(plugin);

export default plugin;

export {
  DSelect
};
