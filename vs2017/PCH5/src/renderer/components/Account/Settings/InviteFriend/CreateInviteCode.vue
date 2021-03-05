<template>
  <div class="create-invite-code">
      <div class="modal-card-head" slot="header-top">
        <p class="modal-card-title">{{$t('user.invitaionCode')}}</p>
        <i class="icon" @click="$emit('close')">&#xe603;</i>
      </div>
      <div class="modal-card-section">
        <div class="select-config">
          <span>{{$t('user.validationPeriod') + '：'}}</span>
          <v-select :placeholder="defalutDate" v-model="defalutDate"  class="selects" :isBorder="true">
            <option v-for="(date, index) in dateList" :key= index >{{ index }}</option>
          </v-select>
          <span>{{$t('user.validationCount') + '：'}}</span>
          <v-select :placeholder="defalutCount" v-model="defalutCount"  class="selects" :isBorder="true">
            <option v-for="(count, index) in countList" :key= index >{{ index }}</option>
          </v-select>
        </div>
      </div>
      <div class="modal-card-foot" slot="footer-bottom">
        <v-button  type="is-primary" @click="createInviteCode()">{{$t('common.sure')}}</v-button>
        <v-button @click="$emit('close')">{{$t('common.cancel')}}</v-button>
      </div>
  </div>
</template>
<script>
export default {
  data() {
    return {
      defalutDate: '',
      dateList: {},
      defalutCount: '',
      countList: {}
    }
  },
  created() {
    let limitCount = (count='') => count + this.$t('user.count')
    // type类型 1: 小时， 2: 天
    let limitDay = (day = 1, type = 2) => {
      if (type !== 1 ) { // 天
        if (day !== 1) {
          return day + this.$t('user.day') + 's'
        }
        return day + this.$t('user.day')
      } else { // 小时
        return day + this.$t('user.hours')
      }
    }
    this.initDate(limitDay)
    this.initCount(limitCount)
  },
  methods: {
    initDate(limitDay) {
      this.defalutDate = limitDay(1, '2')
      this.dateList = {
        [limitDay(4, 1)]: 4,
        [limitDay(12, 1)]: 12,
        [limitDay(1, 2)]: 1*24,
        [limitDay(7, 2)]: 7*24,
        [limitDay(30, 2)]: 30*24
      }
    },
    initCount(limitCount) {
      this.defalutCount = limitCount(20)
      this.countList = {
        [limitCount(1)]: 1, 
        [limitCount(5)]: 5, 
        [limitCount(20)]: 20, 
        [limitCount(50)]: 50, 
        [this.$t('user.unlimited')]: 0
      }
    },
    createInviteCode() {
      this.$emit('update-invite-code', {
        effectiveCount: this.countList[this.defalutCount],
        effectiveSeconds: this.dateList[this.defalutDate]
      })
    }
  }
}
</script>
<style lang="scss">
.create-invite-code {
  align-items: center;
  display: flex;
  flex-direction: column;
  height: 100%;
  .modal-card-head {
    height: 40px;
    width: 100%;
    border-bottom: none;
    font-weight: bold;
    .modal-card-title {
      margin: 0;
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
  .modal-card-section {
    display: flex;
    flex: 1;
    flex-direction: column;
    .select-config {
      margin-top: 14px;
      display: flex;
      flex-direction: column;
      div {
        flex: 1;
        font-size: 13px;
        padding: 3px 0;
      }
      .select {
        font-size: 14px;
      }
    }
  }
  .modal-card-foot {
    width: 100%;
    border: none;
    display: flex;
    justify-content: flex-end;
    padding: 10px;
    .button {
      width: 70px;
      height: 30px;
    }
  }
}
</style>
