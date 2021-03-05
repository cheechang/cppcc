<template>
  <transition-group :tag="tagName" name="lazy-component"
    @before-enter="el => $emit('before-enter', el)"
    @before-leave="el => $emit('before-leave', el)"
    @after-enter="el => $emit('after-enter', el)"
    @after-leave="el => $emit('after-leave', el)"
  >
    <div v-if="isInit" key="component">
      <slot :loading="loading"></slot>
    </div>
    <div v-else-if="$slots.skeleton" key="skeleton">
      <slot name="skeleton"></slot>
    </div>
    <div v-else key="loading"></div>
  </transition-group>
</template>

<script>
export default {
  props: {
    timeout: {
      type: Number
    },
    tagName: {
      type: String,
      default: 'div'
    },
    viewport: {
      type: typeof window !== 'undefined' ? window.HTMLElement : Object,
      default: () => null
    },
    threshold: {
      type: String,
      default: '0px'
    },
    direction: {
      type: String,
      default: 'vertical'
    },
    maxWaitingTime: {
      type: Number,
      default: 50
    }
  },

  data () {
    return {
      isInit: false,
      timer: null,
      io: null,
      loading: false
    }
  },

  created () {
    // 如果指定timeout则无论可见与否都是在timeout之后初始化
    if (this.timeout) {
      this.timer = setTimeout(() => {
        this.init()
      }, this.timeout)
    }
  },

  mounted () {
    if (!this.timeout) {
      let rootMargin
      switch (this.direction) {
        case 'vertical':
          rootMargin = `${this.threshold} 0px`
          break
        case 'horizontal':
          rootMargin = `0px ${this.threshold}`
          break
      }

      this.io = new window.IntersectionObserver(this.intersectionHandler, {
        rootMargin,
        root: this.viewport,
        threshold: [ 0, Number.MIN_VALUE, 0.01]
      })
      this.io.observe(this.$el)
    }
  },

  beforeDestroy () {
    if (this.io) {
      this.io.unobserve(this.$el)
    }
  },

  methods: {
    intersectionHandler (entries) {
      if (
        entries[0].isIntersecting ||
        entries[0].intersectionRatio
      ) {
        this.init()
        this.io.unobserve(this.$el)
      }
    },

    init () {
      this.$emit('beforeInit')
      this.$emit('before-init')

      this.loading = true

      this.requestAnimationFrame(() => {
        this.isInit = true
        this.$emit('init')
      })
    },

    requestAnimationFrame (callback) {
      setTimeout(() => {
        if (this.isInit) return
        callback()
      }, this.maxWaitingTime)
      return (window.requestAnimationFrame || ((callback) => setTimeout(callback, 1000 / 60)))(callback)
    }
  }
}
</script>


