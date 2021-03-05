const nodeList = [];
const ctx = '@@clickoutsideContext';

let startClick;
let seed = 0;

const on = (function() {
  if (document.addEventListener) {
    return function(element, event, handler) {
      if (element && event && handler) {
        element.addEventListener(event, handler, false);
      }
    };
  } else {
    return function(element, event, handler) {
      if (element && event && handler) {
        element.attachEvent('on' + event, handler);
      }
    };
  }
}());

on(document, 'mousedown', e => {startClick = e});
on(document, 'mouseup', e => {
  nodeList.forEach(node => node[ctx].documentHandler(e, startClick));
});

function createDocumentHandler(el, binding, vnode) {
  return function(mouseup = {}, mousedown = {}) {
    if (!vnode ||
      !vnode.context ||
      !mouseup.target ||
      !mousedown.target ||
      el.contains(mouseup.target) ||
      el.contains(mousedown.target) ||
      el === mouseup.target ||
      (vnode.context.popperElm &&
      (vnode.context.popperElm.contains(mouseup.target) ||
      vnode.context.popperElm.contains(mousedown.target)))) return;
    if (binding.expression &&
      el[ctx].methodName &&
      vnode.context[el[ctx].methodName]) {
      vnode.context[el[ctx].methodName]();
    } else {
      el[ctx].bindingFn && el[ctx].bindingFn();
    }
  };
}

/**
 * v-clickoutside
 * @desc 点击元素外面才会触发的事件
 * ```
 */
export default {
  bind(el, binding, vnode) {
    nodeList.push(el);
    const id = seed++;
    el[ctx] = {
      id,
      documentHandler: createDocumentHandler(el, binding, vnode),
      methodName: binding.expression,
      bindingFn: binding.value
    };
  },

  update(el, binding, vnode) {
    el[ctx].documentHandler = createDocumentHandler(el, binding, vnode);
    el[ctx].methodName = binding.expression;
    el[ctx].bindingFn = binding.value;
  },

  unbind(el) {
    let len = nodeList.length;

    for (let i = 0; i < len; i++) {
      if (nodeList[i][ctx].id === el[ctx].id) {
        nodeList.splice(i, 1);
        break;
      }
    }
    delete el[ctx];
  }
};
// const isTouch = 'ontouchstart' in window || navigator.msMaxTouchPoints > 0
// let seed = 0;
// const directive = {
//   instances: [],
//   events: isTouch ? ['touchstart', 'click'] : ['click', 'contextmenu']
// }

// directive.onEvent = function (event) {
//   directive.instances.forEach(({ el, fn }) => {
//     if (event.target !== el && !el.contains(event.target)) {
//       // console.log('bind', event);
//       fn && fn(event)
//     }
//   })
// }

// directive.bind = function (el, binding) {
//   directive.instances.push({ el, fn: binding.value });
//   if (directive.instances.length === 1) {
//     directive.events.forEach(e => document.addEventListener(e, directive.onEvent))
//   }
// }

// directive.update = function (el, binding) {
//   console.log('update', el, binding);
//   if (typeof binding.value !== 'function') {
//     throw new Error('Argument must be a function')
//   }
//   const instance = directive.instances.find(i => i.el === el)
//   instance.fn = binding.value
// }

// directive.unbind = function (el) {
//   const instanceIndex = directive.instances.findIndex(i => i.el === el)
//   if (instanceIndex >= 0) {
//     directive.instances.splice(instanceIndex, 1)
//   }
//   if (directive.instances.length === 0) {
//     directive.events.forEach(e => document.removeEventListener(e, directive.onEvent))
//   }
// }

// export default typeof window !== 'undefined' ? directive : {}
