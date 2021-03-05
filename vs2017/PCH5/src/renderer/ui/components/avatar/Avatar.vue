<template>
  <div class="avatar v-ripple" :class="[size, shape, type]" @click="handleIconClick">
    <slot></slot>
    <img v-if="type==='is-image'" :class="{'is-offline': offline}" draggable="false" class="imgs" :src="handleSrc" alt="Image" @error="imgError">
    <span v-else class="content">{{userInitial}}</span>
  </div>
</template>

<script type="text/ecmascript-6">
/**
 * Created by lpy on 2017/10/23.
 */
import config from '../../../../comm/config.js';
export default {
  name: 'vAvatar',
  props: {
    size: {
      type: String,
      default: 'is-medium'
    },
    shape: String,
    type: {
      type: String,
      default: 'is-image'
    },
    initials: {
      type: String
    },
    src: {
      type: String
    },
    content: String,
    lighten: {
      type: Number,
      default: 80
    },
    offline: {
      type: Boolean,
      default: false
    },
    isName: {
      type: Boolean,
      default: false
    },
    defaultSrc:{
      type: String,
      default: require('vrv-static/resources/images/contact/icon_head_unknow@3x.png')
    },
    sex: Number | String
  },
  computed: {
    isImage() {
      return this.src !== undefined || this.isName === false;
    },
    userInitial() {
      const initials = this.initials || this.initial(this.content);
      return initials;
    },
    handleSrc() {
      return this.src || (typeof this.sex !== 'undefined' && config.defalutAvatar[this.sex]) || this.defaultSrc;
    }
  },
  methods: {
    imgError(e) {
      e.target.src = typeof this.sex !== 'undefined' && config.defalutAvatar[this.sex] || this.defaultSrc;
    },

    initial(username) {
      let parts = username.split(/[ -]/);
      let initials = '';

      for (let i = 0; i < parts.length; i++) {
        initials += parts[i].charAt(0);
      }

      if (initials.length > 3 && initials.search(/[A-Z]/) !== -1) {
        initials = initials.replace(/[a-z]+/g, '');
      }

      initials = initials.substr(0, 3).toUpperCase();
      return initials;
    },
    handleIconClick() {
      this.$emit('icon-click');
    }
  }
};
</script>