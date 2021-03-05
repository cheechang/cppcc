<template>
  <div class="d-ripple"></div>
</template>
<script>
import classlist from '../../utils/classlist';
import { resolve } from '../../utils/element-ref';
// import elementRef from '../../utils/element-ref';

export default {
  name: 'd-ripple',
  data() {
    return {
      clickHolder: '',
      rippleStyle: ''
    };
  },
  created() {
    // Instance data, not declared in data() as we don't want reactivity.
    this.triggerEl = null;
  },
  mounted() {
    this.setupRipple();
  },
  beforeDestroy() {
    this.destroyRipple();
  },
  methods: {
    startRipple(eventType, event) {
      // 鼠标点击触发
      let holder = event.currentTarget || event.target;
      this.clickHolder = holder;
      // 判断当前点击的结点有没有“d-ripple”，没有的话返回子结点的'.d-ripple'给holder
      if (holder && !classlist.has(holder, 'd-ripple')) {
        holder = holder.querySelector('.d-ripple');
      }
      if (!holder) {
        return;
      }
      // 获取data-ui-event属性的值
      const prev = holder.getAttribute('data-ui-event');
      if (prev && prev !== eventType) {
        return;
      }
      holder.setAttribute('data-ui-event', eventType);
      // Get ripple position
      const rect = holder.getBoundingClientRect();
      const x = event.clientX - rect.left;
      const y = event.clientY - rect.top;
      // Create the ripple
      const ripple = document.createElement('div');
      this.rippleStyle = ripple;
      let max;
      if (rect.width === rect.height) {
        max = rect.width * 1.412;
      } else {
        max = Math.sqrt((rect.width * rect.width) + (rect.height * rect.height));
      }
      const size = `${max * 2}px`;
      // ripple 的位置
      ripple.style.width = size;
      ripple.style.height = size;
      ripple.style.marginLeft = `${-max + x}px`;
      ripple.style.marginTop = `${-max + y}px`;
      // 添加ripple元素
      ripple.className = 'd-ripple-ink';
      holder.appendChild(ripple);
      setTimeout(() => {
        classlist.add(ripple, 'is-held');
      }, 0);
      const mouseClickEvent = (eventType === 'mousedown' ? 'mouseup' : 'touchend');
      function handleRelease() {
        document.removeEventListener(mouseClickEvent, handleRelease);
        classlist.add(ripple, 'is-done');
        setTimeout(() => {
          holder.removeChild(ripple);
          if (holder.children.length === 0) {
            holder.removeAttribute('data-ui-event');
          }
        }, 650);
      }
      // 鼠标点击的地方根据传值增加事件（判断eventType传入的事件类型
      document.addEventListener(mouseClickEvent, handleRelease);
    },
    handleMouseDown(event) {
      // Trigger on left click only
      if (event.button === 0) {
        this.startRipple(event.type, event);
      }
    },

    handleTouchStart(event) {
      console.log(event);
      if (event.changedTouches) {
        for (let i = 0; i < event.changedTouches.length; i += 1) {
          this.startRipple(event.type, event.changedTouches[i]);
        }
      }
    },
    setupRipple() {
      this.triggerEl = resolve(this.trigger, this.$el.parentElement);
      if (!this.triggerEl) {
        console.error('[UiRippleInk]: Trigger element not found.');
        return;
      }
      this.triggerEl.addEventListener('touchstart', this.handleTouchStart);
      this.triggerEl.addEventListener('mousedown', this.handleMouseDown);
    },
    destroyRipple() {
      if (!this.triggerEl) {
        return;
      }
      this.triggerEl.removeEventListener('mousedown', this.handleMouseDown);
      this.triggerEl.removeEventListener('touchstart', this.handleTouchStart);
    }
  }
};
</script>
