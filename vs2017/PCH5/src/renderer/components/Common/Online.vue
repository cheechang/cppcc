<template>
  <div v-if="isLoadFinshed">
    <div class="common-online" v-if="getContactOnlineInfo && onlineFlag.includes(getContactOnlineInfo.flag)">
      <!-- <i v-if="onlineItem.deviceType===1" :class="`icon online-icon online-icon-compute`" :style="updateIconColor" :title="updateOnlineTootip" v-html="updateOnlineIcon"></i> -->
      <img :class="`icon online-icon online-icon-${getContactOnlineInfo.deviceType}`" :title="onlineTooltip[getContactOnlineInfo.deviceType]" :src="onlineDevice[getContactOnlineInfo.deviceType]"/>
      <!-- <div :class="`mask-layer mask-layer-${onlineItem.deviceType}`"></div> -->
    </div>
  </div>
</template>
<script>
import ContactMixin from '../Contact/ContactMixin';
import { getOnlineStatusInfo } from '../../utils/utils.js';
import { mapGetters } from 'vuex';
export default {
  mixins: [ContactMixin],
  data() {
    return {
      isLoadFinshed: false
    }
  },
  props: {
    itemId: String
  },
  computed: {
    ...mapGetters(['contact_contactOnlineStateList']),
    getContactOnlineInfo() {
      return this.contact_contactOnlineStateList[this.itemId] ? this.contact_contactOnlineStateList[this.itemId] : false;
    },
    updateOnlineIcon() {
      return getOnlineStatusInfo(this.contact_contactOnlineStateList[this.itemId].flag).icon
    },
    updateIconColor() {
      return {
        color: getOnlineStatusInfo(this.contact_contactOnlineStateList[this.itemId].flag).color
      }
    },
    updateOnlineTootip() {
      return getOnlineStatusInfo(this.contact_contactOnlineStateList[this.itemId].flag).name
    }
  },
  created() {
    setTimeout(() => {
      this.isLoadFinshed = true;
    }, 200);
    if (!this.contact_contactOnlineStateList[this.itemId]) {
      console.log(`主动注册${this.itemId}用户的在线状态`);
      this.$Service.contact.regContactOnline({user: this.itemId}, resp => {
        if (resp.code === 0) {
          this.$store.dispatch('SET_CONTACTS_STATES', resp)
        }
      })
    } else {
      console.log('已有缓存值,不再拉取');
    }
  }
}
</script>

<style lang="scss">
.common-online {
  position: absolute;
  bottom: -3px;
  right: -3px;
  z-index: 2;
  .online-icon {
    image-rendering: pixelated;
    // position: absolute;
    // right: -3px;
    // bottom: -3px;
    // z-index: 2;
    // color: #448AFF;
  }
  .online-icon-compute {
    width: 12px;
    height: 12px;
    background: #fff;
    border-radius: 50%;
    padding-top: 2px;
  }
  .online-icon-2 {
    // font-size: 14px;
    width: 14px;
    height: 15px;
  }
  .online-icon-1 {
    // font-size: 12px;
    width: 14px;
    height: 13px;
  }
  .mask-layer {
    z-index: 1;
    position: absolute;
    background: #fff;
    border-radius: 3px;
  }
  .mask-layer-1 {
    width: 10px;
    height: 8px;
    right: 4px;
    bottom: 7px;
  }
  .mask-layer-2 {
    width: 8px;
    height: 13px;
    right: 5px;
    bottom: 3px;
  }
}
</style>

