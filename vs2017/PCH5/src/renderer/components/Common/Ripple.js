'use strict';

Object.defineProperty(exports, "__esModule", {
    value: true
});
function style(el, value) {
    el.style['transform'] = value;
    el.style['webkitTransform'] = value;
}
var ripple = {
    /* eslint-disable max-statements */
    show: function show(e, el) {
        var value = arguments.length > 2 && arguments[2] !== undefined ? arguments[2] : {};

        if (!el._ripple || !el._ripple.enabled) {
            return;
        }
        var container = document.createElement('span');
        var animation = document.createElement('span');
        container.appendChild(animation);
        container.className = 'v-ripple__container';
        if (value.class) {
            container.className += ' ' + value.class;
        }
        var size = Math.min(el.clientWidth, el.clientHeight) * (value.center ? 1 : el.clientWidth / el.clientHeight * 1.6);
        var size = Math.min(el.clientWidth, el.clientHeight) * (value.center ? 1 : el.clientWidth / el.clientHeight);
        var halfSize = size / 2;
        animation.className = 'v-ripple__animation';
        animation.style.width = size + 'px';
        animation.style.height = size + 'px';
        el.appendChild(container);
        var computed = window.getComputedStyle(el);
        if (computed.position === 'static') {
            el.style.position = 'relative';
            el.dataset.previousPosition = 'static';
        }
        var offset = el.getBoundingClientRect();
        var x = value.center ? 0 : e.clientX - offset.left - halfSize;
        var y = value.center ? 0 : e.clientY - offset.top - halfSize;
        animation.classList.add('v-ripple__animation--enter');
        animation.classList.add('v-ripple__animation--visible');
        style(animation, 'translate(' + x + 'px, ' + y + 'px) scale3d(0.5, 0.5, 0.5)');
        animation.dataset.activated = String(performance.now());
        setTimeout(function () {
            animation.classList.remove('v-ripple__animation--enter');
            style(animation, 'translate(' + x + 'px, ' + y + 'px)  scale3d(1, 1, 1)');
        }, 0);
    },
    hide: function hide(el) {
        if (!el || !el._ripple || !el._ripple.enabled) return;
        var ripples = el.getElementsByClassName('v-ripple__animation');
        if (ripples.length === 0) return;
        var animation = ripples[ripples.length - 1];
        if (animation.dataset.isHiding) return;else animation.dataset.isHiding = 'true';
        var diff = performance.now() - Number(animation.dataset.activated);
        var delay = Math.max(300 - diff, 0);
        setTimeout(function () {
            animation.classList.remove('v-ripple__animation--visible');
            setTimeout(function () {
                var ripples = el.getElementsByClassName('v-ripple__animation');
                if (ripples.length === 1 && el.dataset.previousPosition) {
                    el.style.position = el.dataset.previousPosition;
                    delete el.dataset.previousPosition;
                }
                animation.parentNode && el.removeChild(animation.parentNode);
            }, 300);
        }, delay);
    }
};
function isRippleEnabled(value) {
    return typeof value === 'undefined' || !!value;
}
function rippleShow(e) {
    var value = {};
    var element = e.currentTarget;
    if (!element) return;
    value.center = element._ripple.centered;
    if (element._ripple.class) {
        value.class = element._ripple.class;
    }
    ripple.show(e, element, value);
}
function rippleHide(e) {
    ripple.hide(e.currentTarget);
}
function updateRipple(el, binding, wasEnabled) {
    var enabled = isRippleEnabled(binding.value);
    if (!enabled) {
        ripple.hide(el);
    }
    el._ripple = el._ripple || {};
    el._ripple.enabled = enabled;
    var value = binding.value || {};
    if (value.center) {
        el._ripple.centered = true;
    }
    if (value.class) {
        el._ripple.class = binding.value.class;
    }
    if (enabled && !wasEnabled) {
        if ('ontouchstart' in window) {
            el.addEventListener('touchend', rippleHide, false);
            el.addEventListener('touchcancel', rippleHide, false);
        }
        el.addEventListener('mousedown', rippleShow, false);
        el.addEventListener('mouseup', rippleHide, false);
        el.addEventListener('mouseleave', rippleHide, false);
        // Anchor tags can be dragged, causes other hides to fail - #1537
        el.addEventListener('dragstart', rippleHide, false);
    } else if (!enabled && wasEnabled) {
        removeListeners(el);
    }
}
function removeListeners(el) {
    el.removeEventListener('mousedown', rippleShow, false);
    el.removeEventListener('touchend', rippleHide, false);
    el.removeEventListener('touchcancel', rippleHide, false);
    el.removeEventListener('mouseup', rippleHide, false);
    el.removeEventListener('mouseleave', rippleHide, false);
    el.removeEventListener('dragstart', rippleHide, false);
}
function directive(el, binding) {
    updateRipple(el, binding, false);
}
function unbind(el) {
    delete el._ripple;
    removeListeners(el);
}
function update(el, binding) {
    if (binding.value === binding.oldValue) {
        return;
    }
    var wasEnabled = isRippleEnabled(binding.oldValue);
    updateRipple(el, binding, wasEnabled);
}
exports.default = {
    bind: directive,
    unbind: unbind,
    update: update
};
//# sourceMappingURL=ripple.js.map