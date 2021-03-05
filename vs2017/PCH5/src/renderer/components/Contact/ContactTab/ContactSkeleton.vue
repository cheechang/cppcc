<!-- add by hanxing 2019/9/9 -->
<template>
  <div :class='getClasses'>
    <div :class='`${prefix}-box`' v-for="index in getCount" :key="index">
      <div :class='`${prefix}-avatar`' v-if="type === 'contact'"></div>
      <div :class='`${prefix}-arrow`' v-if="type === 'org'"></div>
      <div :class='`${prefix}-detail`'>
        <!-- <span :class='`${prefix}-loading`'></span> -->
      </div>
    </div>
  </div>
</template>

<script>
const prefix = 'skeleton';
export default {
  name: 'contact-skeleton',
  props: {
    type: {
      type: String,
      validator(val) {
        return ['contact', 'org'].includes(val);
      }
    }
  },
  data() {
    return {
      prefix: prefix,
      parentHeight: 0
    }
  },
  mounted() {
    this.fitContactListHeight()
    if (typeof window !== "undefined") {
      window.addEventListener("resize", this.fitContactListHeight);
    }
  },
  beforeDestroy() {
    if (typeof window !== "undefined") {
      window.removeEventListener("resize", this.fitContactListHeight);
    }
  },
  computed: {
    getClasses() {
      return [
        `${this.prefix}-list`,
        `${this.prefix}-${this.type}`
      ]
    },
    // getCount() {
    //   switch (this.type) {
    //     case 'contact': 
    //       return 9;
    //       break;
    //     case 'org':
    //       return 13;
    //       break;
    //     default: 
    //       return 9;
    //   }
    // }
    getCount() {
      console.log('type:', this.type)
      if (this.type === 'org') {
        return this.parentHeight > 0 ? Math.ceil((this.parentHeight - 55 - 36) / 36) : 13; // 55 为导航栏高度,33 为tab栏高度,36为Item高度
      }
      return this.parentHeight > 0 ? Math.ceil((this.parentHeight - 55 - 36) / 55) : 9; // 55 为导航栏高度,33 为tab栏高度,56为Item高度
    }
  },
  methods: {
    fitContactListHeight() {
      this.parentHeight = this.$root.$el.offsetHeight;
    }
  }
}

</script>
<style lang="scss" >
.skeleton-list{
  width: 100%;
  height: 100%;
  overflow: overlay;
  &.skeleton-org{
    padding: 10px 0px;
    .skeleton-detail{
      height: 10px;
      width: 85%;
    }
  }
  &.skeleton-contact .skeleton-detail{
    height: 20px;
    width: 70%;
    border-radius: $--border-radius-small;
  }
  .skeleton-box{
    width: 100%;
    padding: 0.6rem 1rem;
    display: flex;
    align-items: center;
    justify-content: space-between;
    opacity: 0.4;
    .skeleton-avatar{
      width: 36px;
      height: 36px;
      @include bg_color($--color-active, 'skeleton');
      border-radius: 50%;
    }
    .skeleton-arrow{
      width: 0px;
      height: 0px;
      border: 8px solid transparent;
      @include bg_color($--color-active, 'skeleton');
    }
    .skeleton-detail{
      @include bg_color($--color-active, 'skeleton');
      overflow: hidden;
      font-size: 0px;
      // .skeleton-loading{
      //   display: inline-block;
      //   width: 16px;
      //   height: 100%;
      //   box-shadow: 0px 0px 10px map-get($map: $--color-grey, $key: 'lighten-1');
      //   background: map-get($map: $--color-grey, $key: 'lighten-1');
      //   opacity: 0.3;
      //   margin-top: 0px;
      //   margin-left: -10px;
      //   animation: changePosition 1.5s ease-in-out infinite;
      // }
    }
    @keyframes changePosition{
      100%{
        margin-left:100%;
      }
    }
  }
}
</style>
