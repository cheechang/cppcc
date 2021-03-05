<template>
  <header id="headerFlex"> 
    <div class="verify-header">{{headerName}}</div>
  </header>
</template>
<script>
export default {
 props:["headerName"]
}
</script>
<style lang="scss" >
#headerFlex{
  margin: 0 auto;
  margin-top: 13px;
  display: flex;
  justify-content:center;
  .verify-tip{
    padding-right: 5px;
    height:19px;
    position: relative;
    top: 2px;
  }
  .verify-header{
  height: 30px;   
  }
}
</style>
