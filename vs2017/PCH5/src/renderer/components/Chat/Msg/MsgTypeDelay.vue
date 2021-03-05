<template>
  <div class="time-packing">
    <div class="modal-card-head" slot="header-top">
      <p class="modal-card-title">{{$t('chat.setSendTime')}}</p>
      <i class="icon" @click="$emit('close')">&#xe603;</i>
    </div>
    <div class="delay-time-section">
    <div class="delay-pick-area">
    <div class="date-select">
      <v-select  class="selects"  :isBorder="true" :placeholder="delayDate"  v-model="delayDate" >
          <option 
                  v-for="(dates, index) in 30" 
                  :key= index 
                  :value="getFullDate(dates,index)" 
                  >{{getFullDate(dates,index)}}</option>
      </v-select>
    </div>
     <div class="hour-select">
      <v-select :placeholder="delayHours" v-model="delayHours"  class="selects" :isBorder="true">
            <option v-for="hours in 24" :key= hours >{{hours - 1 > 9 ? hours - 1 : `0${hours - 1}`}}</option>
      </v-select>
     </div>
    <div class="min-select">
    <v-select :placeholder="delayMinute" v-model="delayMinute"   class="selects" :isBorder="true">
          <option v-for="min in 60" :key= min>{{min - 1 > 9 ? min - 1 : `0${min - 1}`}}</option>
    </v-select>
    </div>
    </div>
    <div class="send-time-determine">
      <div class="send-time-area">
      <p class="determine-sendingtime">{{$t('chat.sendingTime')}}</p>
      <span class="determine-time">{{delayTimeDetermine}}</span>
      </div>
      <p v-if="delayDanger"  class="delay-danger">{{$t('chat.sendingTimeLimit')}}</p>
    </div>
    </div>
    <div class="modal-card-foot" slot="footer-bottom">
     <v-button  type="is-primary" @click="confireSend">{{$t('common.sure')}}</v-button>
     <v-button @click="$emit('cancel')">{{$t('common.cancel')}}</v-button>
    </div>
  </div>
</template>
<script>
const moment = require('moment')
// const weekDetail = {
//   1: '周一',
//   2: '周二',
//   3: '周三',
//   4: '周四',
//   5: '周五',
//   6: '周六',
//   0: '周日'
// }
export default {
  data() {
    return {
      delayDate: '',
      delayHours: '',
      delayMinute: '',
      delayTimes: '',
      delayDanger: false
    }
  },
  created() {
    let moments = moment()
    let min = moments.minutes() + 5
    let hours = moments.hours(); 
    this.delayDate = `${moments.format('MM-DD')}  ${this.$t(`week.${moments.weekday()}`)}`
    this.delayHours = hours > 9 ? hours.toString() : `0${hours}`
    this.delayMinute = min < 60 ? min > 9 ? min.toString() :`0${min}` : (min -5).toString()
  },
  computed: {
    // getFullMonth() {
    //   let days;
    //   return days = this.getCountDays()
    // },
    // dateNow() {
    //   let moments = moment()
    //   return `${moments.format('MM-DD')}  周${moments.weekday()}`
    // },
    delayTimeDetermine() {
      return this.delayTimes = `${this.delayDate}  ${this.delayHours}:${this.delayMinute}`
    }
  },
  methods: {
    // 获取相对完整的日期
    getFullDate(date, index) {
      let dates = Date.parse(new Date())
      let moments = moment(dates + 86400000*index);
      return `${moments.format('MM-DD')}  ${this.$t(`week.${moments.weekday()}`)}`
    },

    confireSend() {
      let times = this.delayTimes.split('  ')
      let delayTimeUnix = `${moment().year()}-${times[0]} ${times[2]}`
      delayTimeUnix = new Date(Date.parse(delayTimeUnix.replace(/-/g, "/")));
      delayTimeUnix = delayTimeUnix.getTime();
      let dx = delayTimeUnix - new Date().getTime();
      console.log('delay time:',dx)
      if (dx >= 1000*60*4) {
        this.$emit('sendDelayMsg', delayTimeUnix)
        this.$emit('close')
      } else {
        this.delayDanger = true;
        setTimeout(() => {this.delayDanger = false},2000)
      }
    
    },
    getCountDays() {
      let curDate = new Date();
      /* 获取当前月份 */
      let curMonth = curDate.getMonth();
      /*  生成实际的月份: 由于curMonth会比实际月份小1, 故需加1 */
      curDate.setMonth(curMonth + 1);
      /* 将日期设置为0, 这里为什么要这样设置, 我不知道原因, 这是从网上学来的 */
      curDate.setDate(0);
      /* 返回当月的天数 */
      return curDate.getDate();
    }
  }
}
</script>
<style lang="scss" scoped>
.time-packing {
  align-items: center;
  display: flex;
  flex-direction: column;
  .modal-card-head {
    height: 40px;
    width: 100%;
    border-bottom: none;
    font-weight: bold;
    .modal-card-title {
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
  .delay-time-section {
    display: flex;
    flex-direction: column;
    .delay-pick-area{
      margin-top: 14px;
      display: flex;
      div {
        flex: 1;
        padding: 0 4px 0 10px;
      }
    }
    .send-time-determine{
      display: flex;
      
      font-size: 13px;
      margin-top: 20px;
      font-weight: bold;
      padding-left: 20px;
      position: relative;
      height: 46px;
      // margin-top: 20px
      flex-direction: column;
      .send-time-area {
        display: flex;
        height: 24px;
        /* justify-content: center; */
        align-items: center;
        .determine-sendingtime {
          height: 20px;
        }
        .determine-time {
          color: $--color-msg-prompt-low;
          font-weight: normal;
          margin-left: 10px;
          height: 20px;
        }
      }

      .delay-danger {
        margin-left: 4px;
        color: $--color-msg-prompt-danger;
        margin-right: 20px;
        width: 96%;
        display: flex;
        align-self: end;
        justify-content: flex-end;
        height: 20px;
        line-height: 20px;
        font-weight: normal;
      }
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
