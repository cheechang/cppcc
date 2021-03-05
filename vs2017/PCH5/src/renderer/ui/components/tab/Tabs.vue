<template>
  <div class="b-tabs">
    <slot name="topbar"></slot>
    <nav class="tabs" :class="[type, size, position, { 'is-fullwidth': expanded }]">
      <ul class="item">
        <li v-for="(tabItem, index) in tabItems" :key="index" :class="{ 'is-active': newValue === index }">
          <a @click="tabClick(index)">
            <span v-if="!isIcon">{{ tabItem.label }}</span>
            <i v-else class="icon" :title="tabItem.iconTitle" v-html="tabItem.icon"></i>
          </a>
        </li>
      </ul>
    </nav>
    <section class="tab-content">
      <slot></slot>
    </section>
  </div>
</template>

<script>
export default {
  name: 'vTabs',
  props: {
    value: [String, Number],
    expanded: Boolean,
    type: String,
    size: String,
    position: String,
    tabList: Array,
    isIcon: {
      type: Boolean,
      default: false
    },
    animated: {
      type: Boolean,
      default: true
    },
    iconfont: String
  },
  data() {
    return {
      newValue: this.value || 0,
      tabItems: [],
      contentHeight: 0,
      _isTabs: true // Used internally by TabItem
    };
  },
  watch: {
    /**
     * When v-model is changed set the new active tab.
     */
    value(value) {
      this.changeTab(this.newValue, value);
      this.newValue = value;
    },

    /**
     * When tab-items are updated, set active one.
     */
    tabItems() {
      if (this.tabItems.length) {
        console.log('tabItems:::::', this.tabItems)

        this.tabItems[this.newValue].isActive = true;
      }
    }
  },
  methods: {
    /**
     * Change the active tab.
     */
    changeTab(oldIndex, newIndex) {
      if (oldIndex === newIndex) return;
      this.tabItems[oldIndex].deactivate(oldIndex, newIndex);
      this.tabItems[newIndex].activate(oldIndex, newIndex);
    },

    /**
     * Tab click listener, emit events and set new active tab.
     */
    tabClick(value) {
      this.$emit('input', value);
      this.$emit('change', value);
      this.changeTab(this.newValue, value);
      this.newValue = value;
    }
  },
  mounted() {
    if (this.tabItems.length) {
      console.log('tabItems::', this.tabItems)
      this.tabItems[this.newValue].isActive = true;
    }
  }
};
</script>
<style lang="scss" scoped>
.tabs {
  margin-bottom: -1px;
  .item{
    margin: 0;
  }
  li {
    margin: 0 2px;
    .icon {
      font-size: 18px;
      color: inherit;
    }
  }
}
.tab-content {
  // height: 100%;
}
</style>

