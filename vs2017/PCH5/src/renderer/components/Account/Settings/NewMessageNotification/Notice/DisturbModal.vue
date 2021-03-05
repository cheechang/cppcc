<template>
  <div class="disturb-mode-status">
      <v-checkbox
        v-model="mode.isOpen"
        @change="isOpen=>$emit('change', isOpen)"
      >{{mode.name}}</v-checkbox>
      <div class="time-intervals">
        <v-field class="fields">
          <input class="input-style" v-model="computedStartTime" :customType="'input-size'" readonly @click="$emit('click', 0)">
          —
          <input class="input-style" v-model="computedEndTime" :customType="'input-size'" readonly @click="$emit('click', 1)">
        </v-field>
      </div>
    </div>
</template>
<script>
export default {
  props: {
    mode: Object
  },
  computed:{
    computedStartTime() {
      return this.getTime(this.mode.startTime)
    },
    computedEndTime() {
      return this.getTime(this.mode.endTime, this.mode.startTime>this.mode.endTime)
    }
  },
  methods: {
    getTime(seconds=0, isNextDay=false) {
      try {
        let hours = parseInt(seconds/3600)
        if (hours<10) hours = '0' + hours
        let mins = seconds/60 % 60
        if (mins<10) mins = '0' + mins
        return (isNextDay ? this.$t('account.nextDay') : '') + hours + ':' + mins
      } catch (error) {
        console.log('seconds:::', seconds)
      }
    }
  }
}
</script>
<style lang="scss">
.disturb-mode-status {
  margin-left: 22px;
  .time-intervals {
    width: 100%;
    padding: 3px 0;
    display: flex;
    .fields {
      width: 35%;
      position: relative;
      .has-addons {
        display: flex;
        align-items: center;
        .icon {
          position: absolute;
          right: 5px;
          top: 10px;
          font-size: $--font-size-mid;
        }
        .input-style {
          height: 30px;
          width: 100%;
          border: 0;
          border-radius: $--border-radius-base;
          outline: none;
          background: #d3d3d3;
          font-size: $--font-size-small;
          margin-right: 10px;
          text-align: center;
          margin-left: 10px;
          cursor: pointer;
        }
      }
    }
  }
}
</style>

