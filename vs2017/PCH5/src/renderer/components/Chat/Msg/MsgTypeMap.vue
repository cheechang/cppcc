<template>
  <div class="type-map" @click="openUrl">
    <div class="type-map-title" :title="message.messageObject.name">{{message.messageObject.name}}</div>
    <v-avatar class="type-map-img" :src="mapsrc"></v-avatar>
  </div>
</template>

<script>
export default {
  props: {
    message: Object
  },
  data() {
    return {
      mapsrc: require('vrv-static/resources/images/message/map.png')
    }
  },
  created() {
    if (this.message.flag === 1) {
      this.message.flag = 0
      this.sendMapMsg()
    }
  },
  methods: {
    openUrl() {
      let mapPath = `vrv-static/plugins/mappreview/index.html?mode=normal`
      let winUrl = `${mapPath}&latitude=${this.message.messageObject.latitude}&longitude=${this.message.messageObject.longitude}&isSearch=false`
      this.$ipc.send('new-window', { winUrl: winUrl, winType:'MapPreview',  winTitle: '地图详情', shapeType:'normal'}) 
    },
    sendMapMsg() {
      this.$Service.chat.sendMessage(this.message.messageObject, resp => {
        this.$Service.log(`sendMapMsg code::: ${resp.code}`)
      });
    }
  }
}
</script>

<style lang="scss">
.type-map {
  display: flex;
  flex-direction: column;
  width: 215px;
  height: 105px;
  overflow: hidden;
  color: #000 !important;
  border-radius: 4px !important;
  cursor: pointer;
  .type-map-title {
    flex: 1;
    white-space: nowrap;
    text-overflow: ellipsis;
    overflow: hidden;
    padding: 3px 10px 0px 10px;
    background: #fff;
  }
  .type-map-img {
    height: 80px;
    width: 100%;
  }
}
</style>