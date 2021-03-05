<template>
  <span class="login-from-disconnection">{{tip}}</span>
</template>
<script>
export default{
  props:{
    tip:String
  }
}
</script>
<style lang="scss">
.login-from-disconnection {
  background: #f9dfbe;
  width: 100%;
  height: 32px;
  line-height: 32px;
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 13px;
  color: #b9996f;
  cursor: default;
}
</style>

