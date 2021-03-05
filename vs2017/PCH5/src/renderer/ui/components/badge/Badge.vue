<template>
  <div class="badge" v-if="value" :class="{'is-dot':isDot}" v-text="content">
  </div>
</template>

<script>
export default {
  name: 'vBadge',
  props: {
    value: String | Number,
    max: {
      type: Number,
      default: 99
    },
    isDot: Boolean
  },
  computed: {
    content() {
      if (this.isDot) return
      const value = this.value
      const max = this.max

      if (typeof value === 'number' && typeof max === 'number') {
        return max < value ? `${max}+` : value
      }

      return value
    }
  }
}
</script>