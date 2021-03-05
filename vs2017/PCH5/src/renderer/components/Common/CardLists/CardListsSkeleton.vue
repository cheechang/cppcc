<template>
  <div :class="`${prefix}-list`">
    <div :class="[`${prefix}-item`, {[`${prefix}-short`]: index % 2 ===0}]" v-for="index in 9" :key="index">
      <div :class="`${prefix}-content`">
        <div :class="`${prefix}-left-icon`"></div>
        <div :class="`${prefix}-right-info`">
          <div :class="`${prefix}-title`"></div>
          <div :class="`${prefix}-subtitle`"></div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
const prefix = 'card-lists-skeleton';
export default {
  name: 'card-lists-skeleton',
  data() {
    return {
      prefix: prefix
    };
  }
}

</script>
<style lang='scss' scoped>
.card-lists-skeleton-list{
  height: 95%;
  width: 100%;
  overflow: hidden;
  & .card-lists-skeleton-item:last-child{
    height: 3.6rem!important;
  }
  .card-lists-skeleton-item{
    width: 100%;
    height: 3.8rem;
    padding: 0.5rem;
    box-sizing: border-box;
    display: flex;
    opacity: 0.5;
    .card-lists-skeleton-content{
      display: flex;
      flex: 1;
      justify-content: space-between;
      height: 40px;
      .card-lists-skeleton-left-icon{
        width: 22px;
        height: 24px;
        background: rgba(0,23,69,.15);
        margin-right: 1rem;
      }
      .card-lists-skeleton-right-info {
        display: flex;
        flex: 1;
        justify-content: space-between;
        flex-direction: column;
        .card-lists-skeleton-title{
          width: 30%;
          height: 16px;
          background: rgba(0,23,69,.15);
        }
        .card-lists-skeleton-subtitle{
          width: 70%;
          height: 14px;
          background: rgba(0,23,69,.15);
        }
      }
    }
  }
  .card-lists-skeleton-short{
    .card-lists-skeleton-title{
      width: 50%!important;
    }
    .card-lists-skeleton-subtitle{
      width: 80%!important;
    }
  }
}
</style>
