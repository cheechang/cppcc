<template>
  <transition-group :tag="tagName" name="skeleton" style="position: relative;width: 100%;height: 100%"
    @before-enter="(el) => $emit('before-enter', el)"
    @before-leave="(el) => $emit('before-leave', el)"
    @after-enter="(el) => $emit('after-enter', el)"
    @after-leave="(el) => $emit('after-leave', el)"
  >
    <div v-if="isInit" key="component" style="height: 100%" class="real_component">
      <slot :loading="loading"></slot>
    </div>
    <div v-else-if="$slots.skeleton" key="skeleton" class="skeleton_component">
      <slot name="skeleton"></slot>
    </div>
    <div v-else key="loading"></div>
  </transition-group>
</template>

<script>
require('./intersection-observer.js');
export default {
  name: 'd-skeleton',

  props: {
    // 等待时间，如果指定了时间，不论可见与否，在指定时间之后自动加载
    timeout: {
      type: Number
    },
    // 包裹组件的外层容器的标签名
    tagName: {
      type: String,
      default: 'div'
    },
    // 组件所在的视口，如果组件是在页面容器内滚动，视口就是该容器
    viewport: {
      type: typeof window !== 'undefined' ? window.HTMLElement : Object,
      default: () => null
    },
    // 预加载阈值, css单位
    threshold: {
      type: String,
      default: '0px'
    },
    // 参数 direction 视口的滚动方向, vertical代表垂直方向，horizontal代表水平方向
    direction: {
      type: String,
      default: 'vertical'
    },
    // 设置最大等待值
    maxWaitingTime: {
      type: Number,
      default: 50
    }
  },

  data() {
    return {
      isInit: false,
      timer: null,
      io: null,
      loading: false
    };
  },

  created() {
    // 如果指定timeout则无论可见与否都是在timeout之后初始化
    if (this.timeout) {
      this.timer = setTimeout(() => {
        this.init();
      }, this.timeout);
    }
  },

  mounted() {
    if (!this.timeout) {
      // 根据滚动方向来构造视口外边距，用于提前加载
      let rootMargin;
      switch (this.direction) {
        case 'vertical':
          rootMargin = `${this.threshold} 0px`;
          break;
        case 'horizontal':
          rootMargin = `0px ${this.threshold}`;
          break;
      }

      try {
        // 观察视口与组件容器的交叉情况
        this.io = new IntersectionObserver(this.intersectionHandler, {
          rootMargin,
          root: this.viewport,
          threshold: [0, Number.MIN_VALUE, 0.01]
        });		
        this.io.observe(this.$el);
      } catch (e) {
        this.init();
      }
    }
  },

  beforeDestroy() {
    // 在组件销毁前取消观察
    if (this.io) {
      this.io.unobserve(this.$el);
    }
  },

  methods: {
    // 交叉情况变化处理函数
    intersectionHandler(entries) {
      if (
        // 正在交叉
        entries[0].isIntersecting
        // 交叉率大于0
        || entries[0].intersectionRatio
      ) {
        this.init();
        this.io.unobserve(this.$el);
      }
    },

    // 处理组件和骨架组件的切换
    init() {
      // 此时说明骨架组件即将被切换
      this.$emit('beforeInit');
      this.$emit('before-init');

      // 此时可以准备加载懒加载组件的资源
      this.loading = true;

      // 由于函数会在主线程中执行，加载懒加载组件非常耗时，容易卡顿
      // 所以在requestAnimationFrame回调中延后执行
      this.requestAnimationFrame(() => {
        this.isInit = true;
        this.$emit('init');
      });
    },

    requestAnimationFrame(callback) {
      // 防止等待太久没有执行回调
      // 设置最大等待时间
      setTimeout(() => {
        if (this.isInit) return;
        callback();
      }, this.maxWaitingTime);

      // 兼容不支持requestAnimationFrame 的浏览器
      return (window.requestAnimationFrame
      || (callback => setTimeout(callback, 1000 / 60)))(callback);
    }
  }
};
</script>
