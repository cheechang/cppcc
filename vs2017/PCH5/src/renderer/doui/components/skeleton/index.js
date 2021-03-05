import DSkeleton from './Skeleton.vue';

import { use, Plugin } from '../../utils/plugins';

const plugin = new Plugin(DSkeleton);

use(plugin);

export default plugin;

export {
  DSkeleton
};
