export const use = (plugin) => {
  if (typeof window !== 'undefined' && window.Vue) {
    window.Vue.use(plugin);
  }
};

export const registerComponent = (Vue, component) => {
  if (!component.name) {
    console.log('component error,name not found!');
    return;
  }
  Vue.component(component.name, component);
};

export const registerComponentProgrammatic = (Vue, property, component) => {
  Vue.prototype[property] = component;
};

export class Plugin {
  constructor(component) {
    this.component = component;
  }

  install(Vue) {
    console.log('in plugin install: ', this.component);
    registerComponent(Vue, this.component);
  }
}
