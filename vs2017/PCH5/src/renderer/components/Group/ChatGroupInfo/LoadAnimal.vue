<template>
  <div class="suer-sett-loading" :class="[marginClass]">
    <i class="icon loading-start" v-if="!loadFinished">&#xe6ac;</i>
    <i class="icon loading-success" v-else>&#xe632;</i>
  </div>
</template>
<script>

export default {
  props: {
    loadFinished: Boolean,
    marginClass: String
  }  
}
</script>

<style lang="scss">
.suer-sett-loading {
  margin: 0 4px;
  height: 13px;
}
</style>

