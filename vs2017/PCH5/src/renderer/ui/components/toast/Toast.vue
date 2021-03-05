<template>
    <transition
        name="slide-fade">
        <div class="toast" v-show="isActive" :class="type">
            <i class="icon" v-html="getIcon"></i>
            <div v-html="message"></div>
        </div>
    </transition>
</template>

<script>
import config from '../../utils/config';
export default {
  props: {
    type: {
      type: String,
      default: 'is-dark'
    },
    message: String,
    duration: Number,
    position: {
      type: String,
      default: 'is-top',
      validator(value) {
        return (
          [
            'is-top-right',
            'is-top',
            'is-top-left',
            'is-bottom-right',
            'is-bottom',
            'is-bottom-left'
          ].indexOf(value) > -1
        );
      }
    },
    container: String
  },
  data() {
    return {
      isActive: false,
      parent: null,
      newContainer: this.container || config.defaultContainerElement,
      newDuration: this.duration || config.defaultToastDuration
    };
  },
  computed: {
    getIcon(){
      switch (this.type) {
        case 'is-success':
          return '&#xe699;';
        case 'is-info':
          return '&#xe692;';
        case 'is-warning':
          return '&#xe63b;';
        case 'is-error':
        case 'is-danger':
          return '&#xe6a1;';

      }
    },
    // transition() {
    //   console.log('type:',this.type);
    //   switch (this.position) {
    //     case 'is-top-right':
    //     case 'is-top':
    //       return {
    //         enter: 'fadeInLinearLeaveActive',
    //         leave: 'fadeInLinearLeaveActive'
    //       };
    //     case 'is-top-left':
    //       return {
    //         enter: 'fadeInLinearLeaveActive',
    //         leave: 'fadeInLinearLeaveActive'
    //       };
    //     case 'is-bottom-right':
    //     case 'is-bottom':
    //     case 'is-bottom-left':
    //       return {
    //         enter: 'fadeInUp',
    //         leave: 'fadeOutDown'
    //       };
    //   }
    // }
  },
  methods: {
    insertEl() {
      this.parent.className = '';
      this.parent.classList.add('notices', this.position);
      this.parent.appendChild(this.$el);
    },
    hasChild(parent) {
      return parent !== null && parent.childElementCount > 0;
    },
    close() {
      clearTimeout(this.timer);
      this.isActive = false;

      // Timeout for the animation complete before destroying
      setTimeout(() => {
        this.$destroy();
        if (typeof this.$el.remove !== 'undefined') {
          this.$el.remove();
        } else {
          this.$el.parentNode.removeChild(this.$el);
        }
      }, 150);
    },
    show() {
      if (this.hasChild(this.parent)) {
        // Add to "queue" (recursive) if already has a notice
        setTimeout(() => this.show(), 250);
        return;
      }
      // This is from Toast or Snackbar
      this.insertEl();
      this.isActive = true;
      this.timer = setTimeout(() => this.close(), this.newDuration);
    },
    init() {
      let parent;
      parent = document.querySelector('.notices');

      const container =
        document.querySelector(this.newContainer) !== null
          ? document.querySelector(this.newContainer)
          : document.body;

      if (!parent) parent = document.createElement('div');

      this.parent = parent;
      if (this.newContainer) parent.style.position = 'absolute';

      container.appendChild(parent);
    }
  },
  beforeMount() {
    this.init();
  },
  mounted() {
    this.show();
  }
};
</script>
<style lang="scss" scoped>

.slide-fade-enter-active {
  transition: all .3s ease;
}
.slide-fade-leave-active {
  transition: all .8s cubic-bezier(1.0, 0.5, 0.8, 1.0);
}
.slide-fade-enter, .slide-fade-leave-to
/* .slide-fade-leave-active for below version 2.1.8 */ {
  transform: translateY(15px);
  opacity: 0;
}
.notices{
  .toast{
    margin-top: 55px;
    border-radius: 0px;
    padding: 0.55em 0.5em;
    min-width: 480px;
    border-top-width: 3px;
    border-top-color: rgba(0,0,0,0.3);
    border-top-style: inset;
    .icon{
      margin-right: 8px;
      font-size: 14px;
      color:rgba(0,0,0,0.3);
    }
  }
  .toast.is-success{
    font-size: 14px;
    background: rgb(0,176,88);
    color: #fff;
  }
  .toast.is-info{
    font-size: 14px;
    background: rgb(0,151,244);
    color: #fff;
  }
  .toast.is-warning{
    font-size: 14px;
    background: rgb(255,133,0);
    color: #fff;
  }
  .toast.is-danger{
    font-size: 14px;
    background: rgb(255,66,67);
    color: #fff;
  }
  .toast.is-error{
    font-size: 14px;
    background: rgb(255,66,67);
    color: #fff;
  }
}

</style>