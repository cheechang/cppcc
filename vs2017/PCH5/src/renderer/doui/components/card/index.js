
import DCard from './Card';

import { use, Plugin } from '../../utils/plugins';

const plugin = new Plugin(DCard);

use(plugin);

export default plugin;

export {
  DCard
};
