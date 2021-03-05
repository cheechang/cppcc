<template>
  <div class="modal is-active">
    <div class="modal-background" :class="[modalBg]" @click="$emit('close')"></div>
    <div class="modal-card" :class="[cardSize]" :style="cardStyle">
      <header>
        <slot name="header-top"></slot>
      </header>
      <section class="modal-card-body">
        <slot></slot>
      </section>
      <footer>
        <slot name="footer-bottom"></slot>
      </footer>
    </div>
  </div>
</template>
<script>
export default {
  name: 'vModal',
  props: {
    width: Number,
    cardSize: String,
    cardStyle: Object,
    modalBg: String
  }
};
</script>
<style lang="scss" scoped>
.modal{
  z-index: 999;
  position: fixed;
  .modal-card-body {
    display: flex;
    height: 100%;
    flex-direction: column;
    overflow-x: hidden;
    padding: 0;
  }
}
.modal-card-head {
  .icon {
    color: #000;
    &:hover {
      position: relative;
      &:hover::before {
        background: currentColor;
      }
      &:before {
        border-radius: 50%;
        color: inherit;
        content: '';
        position: absolute;
        left: 0;
        top: 0;
        height: 100%;
        opacity: 0.12;
        transition: 0.3s cubic-bezier(0.25, 0.8, 0.5, 1);
        width: 100%;
      }
    }
  }
}
</style>



