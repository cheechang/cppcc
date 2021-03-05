<template>
  <button
   class="d-button"
   :class="[
      `d-button-${type}`,
      `d-button-size-${size}`,
      {'d-disabled': disabled},
      {'is-loading': loading},
      {'d-button-outline': outline},
      {'d-button-circle': circle},
      {'d-button-round': round},
      {'d-button-shadow': shadow},
    ]"
    :disabled="disabled || loading"
    @click="onClicked"
    :style="setButtonStyle"
  >
    <d-ripple v-if="ripple"></d-ripple>
    <d-icon v-if="loading" icon="d-icon-loading-round" :class="{'d-loading': loading}" size="inherit"></d-icon>
    <d-icon v-if="icon" :icon="icon" size="inherit"></d-icon>
    <span v-if="$slots.default"><slot></slot></span>
  </button>
</template>

<script>
/**
 * Created by lpy on 2019/7/31.
 */
import DRipple from '../ripple/Ripple.vue';
import DIcon from '../icon/Icon';

export default {
  name: 'd-button',
  components: {
    [DRipple.name]: DRipple,
    [DIcon.name]: DIcon,
  },
  props: {
    type: {
      type: String,
      default: 'primary',
      validator(val) {
        return ['primary', 'success', 'warning', 'danger', 'info', 'text'].includes(val);
      }
    },
    disabled: {
      type: Boolean,
      default: false,
    },
    size: {
      type: String,
      default: 'normal',
      validator(val) {
        return ['normal', 'medium', 'small', 'mini'].includes(val) || /^[0-9]+$/.test(val);
      }
    },
    shadow: Boolean,
    round: Boolean,
    loading: Boolean,
    outline: Boolean,
    circle: Boolean,
    ripple: {
      type: Boolean,
      default: false
    },
    icon: String,
  },
  computed: {
    setButtonStyle() {
      let styleArray = [];
      if (this.size && /^[0-9]+$/.test(this.size)) {
        styleArray.push({
          width: `${this.size}px`,
          height: `${this.size}px`,
          'line-height': `${this.size}px`
        });
      }
      return styleArray;
    }
  },
  methods: {
    onClicked(event) {
      this.$emit('click', event);
    }
  }
};
</script>
