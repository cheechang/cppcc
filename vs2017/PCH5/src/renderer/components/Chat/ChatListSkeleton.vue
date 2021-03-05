<!-- add by hanxing 2019/9/10 -->
<template>
  <div :class="`${prefix}-list`">
    <div :class="[`${prefix}-item`, {[`${prefix}-short`]: index % 2 ===0}]" v-for="index in getCount" :key="index">
      <div :class="`${prefix}-avatar`"></div>
      <div :class="`${prefix}-content`">
        <div :class="`${prefix}-title`"></div>
        <div :class="`${prefix}-msg`"></div>
      </div>
    </div>
  </div>
</template>

<script>
const prefix = 'chat-list-skeleton';
export default {
  name: 'chat-list-skeleton',
  data() {
    return {
      prefix: prefix,
      parentHeight: 0
    };
  },
  mounted() {
    this.fitChatListHeight()
    if (typeof window !== "undefined") {
      window.addEventListener("resize", this.fitChatListHeight);
    }
  },
  beforeDestroy() {
    if (typeof window !== "undefined") {
      window.removeEventListener("resize", this.fitChatListHeight);
    }
  },
  destroyed() {
    this.$emit('skeleton-destroy');
  },
  computed: {
    getCount() {
      return this.parentHeight > 0 ? Math.ceil((this.parentHeight - 55) / 61) : 9; // 55 为导航栏高度,61为Item高度
    }
  },
  methods: {
    fitChatListHeight() {
      this.parentHeight = this.$root.$el.offsetHeight;
    }
  }
}

</script>
<style lang='scss' scoped>
.chat-list-skeleton-list{
  height: 95%;
  width: 100%;
  overflow: hidden;
  & .chat-list-skeleton-item:last-child{
    height: 3.6rem!important;
  }
  .chat-list-skeleton-item{
    width: 100%;
    height: 3.8rem;
    padding: 0.5rem;
    box-sizing: border-box;
    display: flex;
    opacity: 0.8;
    .chat-list-skeleton-avatar{
      width: 40px;
      height: 40px;
      border-radius: 50%;
      @include bg_color($--color-active, 'skeleton');
      margin-right: 1rem;
    }
    .chat-list-skeleton-content{
      display: flex;
      flex: 1;
      flex-direction: column;
      justify-content: space-between;
      height: 40px;
      .chat-list-skeleton-title{
        width: 30%;
        height: 16px;
        @include bg_color($--color-active, 'skeleton');
        border-radius: 2px;
      }
      .chat-list-skeleton-msg{
        width: 70%;
        height: 14px;
        @include bg_color($--color-active, 'skeleton');
        border-radius: 2px;
      }
    }
  }
  .chat-list-skeleton-short{
    .chat-list-skeleton-title{
      width: 50%!important;
    }
    .chat-list-skeleton-msg{
      width: 80%!important;
    }
  }
}
</style>
