import DAvatar from './Avatar';
import { use, Plugin } from './../../utils/plugins';

const plugin = new Plugin(DAvatar);
use(plugin);

export default plugin;

export {
  DAvatar
};