
export function resolve(ref, fallback) {
  if (ref instanceof Element) {
    return ref;
    // eslint-disable-next-line no-underscore-dangle
  } if (ref && ref._isVue) {
    return ref.$el;
  } if (typeof ref === 'string') {
    return document.querySelector(ref);
  }

  return fallback;
}

export default {
  resolve
};
