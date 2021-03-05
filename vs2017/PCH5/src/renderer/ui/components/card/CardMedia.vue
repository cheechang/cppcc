<template>
<div class="v-card-media">
  <slot></slot>
  <div v-if="mediaTitle || mediaSubTitle" class="v-card-media-title">
    <div class="v-card-title" v-if="mediaTitle" :class="mediaTitleClass">
      {{mediaTitle}}
    </div>
    <div class="v-card-sub-title" v-if="mediaSubTitle" :class="mediaSubTitleClass">
      {{mediaSubTitle}}
    </div>
  </div>
</div>
</template>

<script>
export default {
  name: 'v-card-media',
  props: {
    mediaTitle: {
      type: String
    },
    mediaTitleClass: {
      type: [String, Array, Object]
    },
    mediaSubTitle: {
      type: String
    },
    mediaSubTitleClass: {
      type: [String, Array, Object]
    }
  }
}
</script>

<style lang="scss" scoped>
.v-card-media {
  position: relative;
  > img {
    width: 100%;
    max-width: 100%;
    min-width: 100%;
    display: block;
    vertical-align: top;
  }
}

.v-card-media-title {
  position: absolute;
  left: 0;
  right: 0;
  bottom: 0;
  padding: 16px;
  .v-card-title {
    font-size: 24px;
    line-height: 36px;
  }
  .v-card-sub-title {
    font-size: 14px;
  }
}
</style>
