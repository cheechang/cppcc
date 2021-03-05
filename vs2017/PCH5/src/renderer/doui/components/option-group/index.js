import DOptionGroup from '../select/OptionGroup.vue';
import { use, Plugin } from '../../utils/plugins';

const plugin = new Plugin(DOptionGroup);
use(plugin);

export default plugin;

export {
  DOptionGroup
};
