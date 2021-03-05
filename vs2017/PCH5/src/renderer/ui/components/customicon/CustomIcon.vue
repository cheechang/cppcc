<template>
  <span :class="[type,size]" @click="$emit('click')">
    <span class="path1"></span><span class="path2"></span>
  </span>
</template>
<script>
export default {
  name:'vCustomIcon',
  props: {
    type: String,
    size: String
  }
};
</script>

