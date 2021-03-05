<!-- add by hanxing 2019/9/4 -->
<template>
  <div class="d-select-dropdown" @click.stop>
    <slot name="filterable"></slot>
    <div class="d-select-lists">
      <slot></slot>
      <slot name="empty"></slot>
    </div>
  </div>
</template>

<script>
import DInput from '../input';

export default {
  name: 'd-select-dropdown',
  components: {
    [DInput.name]: DInput
  },
  data() {
    return {
    };
  },
  computed: {
  },
  watch: {
  },
  created() {},
  mounted() {
  },
  methods: {}
}

</script>
