import DOption from '../select/Option.vue';
import { use, Plugin } from '../../utils/plugins';

const plugin = new Plugin(DOption);
use(plugin);

export default plugin;

export {
  DOption
};
