<!-- add by hanxing 2019/9/10 -->
<template>
  <div :class="getClass">
    <div :class="`${prefix}-head-box`" v-if="type === 'info'">
      <div :class="`${prefix}-head`"></div>
    </div>
    <div :class="`${prefix}-search-box`" v-if="type === 'info'">
      <div :class="`${prefix}-search`"></div>
    </div>
    <div :class="`${prefix}-member-box`" v-if="type === 'info'">
      <div :class="`${prefix}-count`"></div>
      <div :class="`${prefix}-member`"></div>
    </div>
    <div :class="`${prefix}-list`">
      <div :class="[`${prefix}-item`, {[`${prefix}-item-short`]: index % 2 === 0}]" v-for="index in 7" :key="index">
        <div :class='`${prefix}-avatar`'></div>
        <div :class='`${prefix}-detail`'></div>
      </div>
    </div>
  </div>
</template>

<script>
const prefix = 'chat-group-skeleton'
export default {
  name: 'chat-group-skeleton',
  components: {},
  props: {
    type: {
      type: String,
      validator(val) {
        return ['info', 'list'].includes(val);
      }
    }
  },
  data() {
    return {
      prefix: prefix
    };
  },
  computed: {
    getClass() {
      return [
        `${this.prefix}`,
        `${this.prefix}-${this.type}`
      ]
    }
  },
  watch: {},
  created() {},
  mounted() {},
  methods: {}
}

</script>
<style lang='scss' scoped>
.chat-group-skeleton{
  width: 100%;
  height: 100%;
  overflow: hidden;
  border-left: 1px solid $--border-color-grey-lighten;
  opacity: 0.8;
  .chat-group-skeleton-head-box{
    padding: 13px;
    width: 100%;
    display: flex;
    justify-content: center;
    align-items: center;
    flex-direction: column;
    border-bottom: 1px solid #eeeeee;
    .chat-group-skeleton-head{
      height: 30px;
      width: 100%;
      background: map-get($map: $--color-grey, $key: 'lighten-3');
    }
  }
  .chat-group-skeleton-search-box{
    height: 25px;
    margin: 13px 13px 0px 13px;
    box-sizing: border-box;
    .chat-group-skeleton-search{
      width: 100%;
      border-radius: 15px;
      height: 27px;
      background: map-get($map: $--color-grey, $key: 'lighten-3');
    }
  }
  .chat-group-skeleton-member-box{
    height: 30px;
    display: flex;
    padding: 21px 13px;
    box-sizing: border-box;
    justify-content: space-between;
    align-items: center;
    .chat-group-skeleton-count{
      width: 80px;
      height: 18px;
      background: map-get($map: $--color-grey, $key: 'lighten-3');
    }
    .chat-group-skeleton-member{
      width: 20px;
      height: 20px;
      border-radius: 50%;
      background: map-get($map: $--color-grey, $key: 'lighten-3');
    }
  }
  .chat-group-skeleton-list{
    width: 100%;
    overflow: hidden;
    .chat-group-skeleton-item{
      width: 100%;
      height: 2.9rem;
      padding: 0.5rem;
      box-sizing: border-box;
      display: flex;
      align-items: center;
      .chat-group-skeleton-avatar{
        width: 30px;
        height: 30px;
        background-color: map-get($map: $--color-grey, $key: 'lighten-3');
        border-radius: 50%;
        margin-right: 16px;
      }
      .chat-group-skeleton-detail{
        height: 0.75rem;
        background-color: map-get($map: $--color-grey, $key: 'lighten-3');
        font-size: 0px;
        width: 50%;
        border-radius: $--border-radius-small;
      }
    }
    .chat-group-skeleton-item-short .chat-group-skeleton-detail{
      width: 70%!important;
    }
  }
}
</style>
