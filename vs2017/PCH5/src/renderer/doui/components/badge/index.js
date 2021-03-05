import DBadge from './Badge.vue';
import { use, Plugin } from '../../utils/plugins';

const plugin = new Plugin(DBadge);
use(plugin);

export default plugin;

export {
  DBadge
};
