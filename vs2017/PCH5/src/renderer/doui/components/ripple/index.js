
import DRipple from './Ripple';
import { use, Plugin } from '../../utils/plugins';

const plugin = new Plugin(DRipple);

use(plugin);

export default plugin;

export {
  DRipple
};
