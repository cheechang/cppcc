<template>
  <component :is="isComponent" :message="message" :id='id'></component>
</template>

<script>
import MsgTypeTemplate from '../MsgTypeTemplate.vue'
import MsgTypeRemind from '../MsgTypeRemind.vue'
export default {
  props: {
    message: Object,
    id: String
  },
  components: {
    MsgTypeTemplate,
    MsgTypeRemind
  },
  computed: {
    isComponent() {
      return this.message.messageObject.subType !== 1 ? MsgTypeTemplate : MsgTypeRemind
    }
  }
}
</script>

<style>

</style>