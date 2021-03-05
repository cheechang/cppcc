<template>
  <!-- <transition v-bind="$attrs"> -->
    <v-card-list>
      <v-card class="card-item-content" :class="{'full-content':!item.content||!item.title, 'multiple-rows': item.rows}" :title="item.content" :subtitle="item.title" @click.stop="expendContent(item)">
        <v-checkbox slot="subBefore" class="item-checked" v-if="item.hasChecked" v-model="item.checked" :disabled="item.disabled" @change="checkItem(item)"></v-checkbox>
        <i class="icon" slot="subAfter" v-if="hasSubItem" :style="{transform: isOpenDetail?'rotate(180deg)':''}" v-html="item.subIcon&&item.subIcon.right"></i>
        <i class="icon left-icon" slot="leftAvatar" :title="item.tooltip" :style="hasLeftIcon" v-html="item.icon&&item.icon.left" @click="$emit('icon-click')"></i>
        <i class="icon" slot="rightAvatar" :style="hasRightIcon" v-html="item.icon&&item.icon.right" @click="$emit('send')"></i>
      </v-card>
      <div class="sub-card-content" v-if="isOpenDetail&&hasSubItem">
        <!-- <div class="v-divder"></div> -->
        <contents v-for='(content, index) in item.subContent' name="slide-y-transition" :key="index" :item='content' :isChild="true" @update="args=>{isOpenDetail=false,$emit('update', args)}"></contents>
      </div>
    </v-card-list>
  <!-- </transition> -->
</template>
<script>
export default {
  name: 'contents',
  props: {
    item: Object,
    isChild: false
  },
  data() {
    return {
      isOpenDetail: false
    }
  },
  computed: {
    hasSubItem() {
      return this.item.subContent && !this.item.disabled;
    },
    hasLeftIcon() {
      return {
        visibility: this.item.icon && this.item.icon.left ? 'visible' : 'hidden'
      }
    },
    hasRightIcon() {
      return {
        visibility: this.item.icon && this.item.icon.right ? 'visible' : 'hidden'
      }
    }
  },
  methods: {
    expendContent(item) {
      if (!this.isChild) {
        this.isOpenDetail = !this.isOpenDetail;
      } else {
        this.$emit('update', item);
      }
    },
    checkItem(item) {
      if (item.hasChecked && !item.disabled) {
        item.checked = !item.checked;
        this.$emit('check',item)
      }
    }
  }
}
</script>
<style lang="scss">
.sub-card-content {
  position: absolute;
  background-color: #f9f9f9;
  @include z-index(btn);
  width: 100%;
  text-decoration: none;
  transition: 0.3s cubic-bezier(0.25, 0.8, 0.5, 1);
  transform-origin: left top 0px;
  border-radius: $--border-radius-base;
  will-change: transform;
  max-width: 60%;
  margin-top: 1px;
  left: 38px;
  cursor: pointer;
  .media-left,
  .media-right {
    display: none;
  }
}
.full-content {
  .default-content {
    height: 2.6rem !important;
  }
}
.multiple-rows{
  .default-content{
    height: auto!important;
    min-height: 3.9rem!important;
    .media-left{
      height: 46px;
    }
    .subtitle{
      min-height: 15px!important;
      max-height: none!important;
      .contents{
        width: 100%;
        display: -webkit-box;
        -webkit-box-orient: vertical;
        -webkit-line-clamp:5;
        overflow: hidden;
        white-space: normal;
        text-overflow: ellipsis;
        min-height: 15px!important;
      }
    }
    
  }
}
.card-item-content {
  .left-icon {
    width: 22px;
    font-size: 22px;
    color: rgba(0 ,0, 0, 0.38);
  }
  .item-checked {
    margin-right: 6px;
    height: 24px;
    .v-checkbox-inner {
      width: 16px !important;
      height: 16px !important;
      &::after {
        width: 3px !important;
        height: 6px !important;
      }
    }
  }
  .default-content {
    height: 3.6rem;
    .media {
      height: 100%;
      .title {
        color: rgba(0 ,0, 0, 0.38);
      }
      .subtitle {
        color: #000 !important;
        align-items: center;
      }
      .contents {
        user-select: text;
      }
    }
  }
}
</style>


