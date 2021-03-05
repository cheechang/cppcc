<template>
  <div class="disturb-config">
    <div class="modal-card-head" slot="header-top">
      <p class="modal-card-title">{{$t('account.setTime')}}</p>
      <i class="icon" @click="$emit('close')">&#xe603;</i>
    </div>
    <div class="disturb-time-section">
      <div class="disturb-select hour-select">
        <v-select v-model="checkedHours"  class="selects" :isBorder="true">
          <option v-for="hours in 24" :key= hours >{{hours - 1 > 9 ? hours - 1 : `0${hours - 1}`}}</option>
        </v-select>
      </div>
      {{$t('account.hours')}}
      <div class="disturb-select min-select">
        <v-select v-model="checkedMinute" class="selects" :isBorder="true">
          <option v-for="min in 60" :key= min>{{min - 1 > 9 ? min - 1 : `0${min - 1}`}}</option>
        </v-select>
      </div>
      {{$t('account.minutes')}}
    </div>
    <div class="modal-card-foot" slot="footer-bottom">
      <v-button type="is-primary" @click="$emit('update',checkedHours*3600+checkedMinute*60)">{{$t('common.sure')}}</v-button>
      <v-button @click="$emit('close')">{{$t('common.cancel')}}</v-button>
    </div>
  </div>
</template>
<script>
export default {
  props: {
    currentTime: {
      type: String,
      default: '0:0'
    }
  },
  data() {
    return {
      checkedHours: 0,
      checkedMinute: 0
    }
  },
  created() {
    this.checkedHours = this.currentTime.split(':')[0]
    this.checkedMinute = this.currentTime.split(':')[1]
    console.log(this.checkedHours, this.checkedMinute)
  }
}
</script>
<style lang="scss">
.disturb-config {
  align-items: center;
  display: flex;
  flex-direction: column;
  .modal-card-head {
    height: 40px;
    width: 100%;
    border-bottom: none;
    font-weight: bold;
    .modal-card-title {
      margin-bottom: 0 !important;
      font-size:$--font-size-mid;
    }
    .icon {
      font-size:$--font-size-mid;
      margin-right: -20px;
      height: 40px;
      width: 40px;
      &:hover{
        background: $--color-msg-prompt-danger;
      }
    }
  }
  .disturb-time-section {
    display: flex;
    align-items: center;
    height: 60px;
    .disturb-select {
      margin-left: 10px;
      margin-right: 10px;
    }
  }
 .modal-card-foot{
   width: 100%;
   border: none;
   display: flex;
   justify-content: flex-end;
   padding: 10px;
   .button{
     width: 70px;
     height: 30px;
   }
 }
}
</style>
