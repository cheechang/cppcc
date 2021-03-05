<template>
  <!-- 仅仅展示更多操作样式、执行代码放在ChatMsgListArea组件中与Message组件数据交互 -->
  <div class="chat-msg-action" :style="computedHeight">
    <div class="action-mask-layer">
      <div class="action-item">
        <i class="icon theme-botton" @click="$emit('forward')">&#xe673;</i>
        <p>{{$t('chat.combine')}}</p>
      </div>
       <div class="action-item">
        <i class="icon theme-botton" @click="handleDelete">&#xe6bb;</i>
        <p>{{$t('chat.delete')}}</p>
      </div>
      <i class="icon action-roll-back" @click="$emit('close')">&#xe603;</i>
    </div>
  </div>
</template>
<script>
export default {
  props: {
    isExpendSidebar: Boolean,
    isExitSelectItems: Boolean,
    id: String
  },
  computed: {
    computedHeight() {
      let editClass = document.getElementsByClassName(`editContainer_${this.id}`)
      if (!editClass[0].clientHeight) return
      return {
        height: editClass[0].clientHeight + 'px'
      }
    }
  },
  methods: {
    handleDelete() {
      if (!this.isExitSelectItems) {
        return
      } 
      this.$dialog.confirm({
      confirmText: this.$t('common.sure'),
      cancelText: this.$t('common.cancel'),
      message: this.$t('chat.delSelectedMsg'),
      onConfirm: () => { 
          this.$emit('handleMixMsgDelete')
        }
      });
    }
  }
}
</script>
<style lang="scss">
.chat-msg-action {
  display: flex;
  width: 100%;
  padding: 10px;
  background: #fff;
  border-radius: $--border-radius-base;
  padding: 12px 24px 9px 24px;
  position: absolute;
  bottom: 0;
  @include z-index(menu);
  border-top: 1px solid $--border-color-grey-lighten;
  .action-mask-layer{
    flex: 1;
    display: flex;
    align-items: center;
    justify-content: center;
    min-height: 62px;
    max-height: 122px;
    .action-item {
      flex: 1;
      display: flex;
      justify-content: center;
      align-items: center;
      flex-direction: column;
      .icon {
        width: 36px;
        height: 36px;
        background: #eaeaea;
        border-radius: $--border-radius-circle;
        color: #fff;
      }
      p {
        font-size:$--font-size-mid;;
        color: #000;
        margin-bottom: -16px;
      }
    }
    .action-roll-back {
      position: absolute;
      right: 0;
      top: 5px;
    }
  }
}
</style>
