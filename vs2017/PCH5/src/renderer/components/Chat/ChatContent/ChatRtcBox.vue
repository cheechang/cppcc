<template>
  <div class="rtc-file-box">
    <div class="rtc-file-title">
      {{$t('chat.fileTransfer')}}
      <i class="icon icon-rtc" @click="$emit('close')">&#xe603;</i>
    </div>
    <div class="rtc-file-list">
    <div v-for="(item, index) in rtcFile"  :key="index">
      <RtcItem :rtcFile="item"  @isCloseExpend='isCloseExpend'  :id="id"></RtcItem>
    </div>
    </div>
  </div>
</template>
<script>
import RtcItem from './RtcItem'
import { mapGetters } from 'vuex'
export default {
  props:{
    rtcFile: Object | Array,
    id: String
  },
  computed: {
    ...mapGetters(['user_account'])
  },
  components: {
    RtcItem
  },
  methods: {
    isCloseExpend() {
      if (!Object.keys(this.rtcFile).length) {
        this.$emit('changeExpend', false)
      }
    },

    delAllFile() {
      this.$emit('close')
    }
  }
}
</script>

<style lang="scss" scoped>
 .rtc-file-box {
    width: 240px;
    height: 100%;
    border-left: solid 1px $--border-color-grey-lighten; 
    display: flex; //fit xp 
    flex:1; //fit xp 
    flex-direction: column; //fit xp
}
  .rtc-file-list {
    display: flex;
    overflow-x: hidden;
    overflow-y: auto;
    width: 100%;
    height: calc(100% - 31px);
    flex-direction: column;
  }
.rtc-file-title {
  border-bottom: solid 1px $--border-color-grey-lighten;
  font-size: $--font-size-mid;
  padding: 4px;
  text-align: end;
  .icon-rtc {
    font-size: $--font-size-small;
    color: #000;
    width: 14px;
  }
}
</style>
