<template>
  <d-card class="remind-card" :body-style="{ padding: '0px' }">
    <d-icon icon='d-icon-alarm-clock' ></d-icon><span class="remind-card-span">豆豆提醒</span>
    <div class="remind-card-from">
      <d-icon icon='d-icon-circle-person' size="small"></d-icon><span class="remind-card-span remind-card-name">{{message.messageObject.userName}}</span>
    </div>
    <div class="remind-card-content">
      <span>{{getRemindContent}}</span>
    </div>
    <div class="remind-card-time">
      {{message.messageObject.time/1000 | LoginTime}}
    </div>
    <div class="remind-card-showlist" @click='toCalenderApp'>
      <span>待提醒</span>
      <d-icon icon='d-icon-double-arrow-right' size='mini'></d-icon>
    </div>
  </d-card>
</template>
<script>
import { mapGetters } from 'vuex';
export default {
  filters: {
    LoginTime(value) {
      //获取当前时间,
      let nowTime = new Date();
      let nowDay =
        nowTime.getDate() < 10
          ? "0" + nowTime.getDate()
          : "" + nowTime.getDate();
      let d = new Date(parseInt(value*1000));
      let year = d.getFullYear();
      let month = d.getMonth() + 1;
      let day = d.getDate() < 10 ? "0" + d.getDate() : "" + d.getDate();
      let hour = d.getHours();
      let minutes =
        d.getMinutes() < 10 ? "0" + d.getMinutes() : "" + d.getMinutes();
      let yearMonthDay = year + "-" + month + "-" + day;
      let timeMinutes = hour + ":" + minutes;
      return yearMonthDay + " " + timeMinutes;
    }
  },
  props: {
    message: Object,
    id: String
  },
  created() {
     console.log('msgTypeRemind>>>>>>>>>>>>>>>>>>>>>>>', this.message.messageObject)
     this.message.messageObject.body = JSON.parse(this.message.messageObject.body)
    //  this.message.messageObject.msgProperties = JSON.parse(this.message.messageObject.msgProperties)
  },
  computed: {
    getRemindContent() {

      if(this.message.messageObject.body.hasOwnProperty('fileName')) {
        return `[文件]`
      }else if(this.message.messageObject.body.hasOwnProperty('url')){
        return `[网页分享]`
      }else if(this.message.messageObject.body.hasOwnProperty('videoFileName')){
        return `[微视频]`
      }else {
        return this.message.messageObject.body.body
      }
    }
  },
  methods: {
    toCalenderApp() {
      let calenderPath = `vrv-static/plugins/localApp/MsgRemind/index.html`
      this.$ipc.send('new-window',{ winUrl: calenderPath, winType:'msgRemind', winTitle: this.$t('account.msgNotification'), shapeType:'normal'})
    },
    
  },
}
</script>
<style lang="scss" scoped>
  .remind-card {
    
    box-sizing: border-box;
    width: 280px;
    height: 182px;
    // position: absolute;
    // top: 90px;
    // left: 27px;
    &:hover {
      cursor: pointer;
    }
    .d-icon-alarm-clock {
      padding-left: 5px;
      color: #3273dc;
    }
    .remind-card-span{
      font-family: '黑体';
      font-weight: 600;
      color: #464141;
      position: relative;
      top: -5px;
      padding-left: 5px;
    }
      .remind-card-name {
        top: -3px !important;
        font-family: '黑体';
        font-weight: 600;
      }
    .remind-card-from{
      color: #999 !important;
      text-align: center;
      .d-icon-circle-person{
        color:#3273dc;
      }

    }
    .remind-card-content {
      overflow: hidden;/*超出部分隐藏*/
      text-overflow:ellipsis;/* 超出部分显示省略号 */
      white-space: nowrap;/*规定段落中的文本不进行换行 */
      width: 80%;/*需要配合宽度来使用*/
      text-align: center;
      margin: 0 auto;
      span {
        font-size: 15px;
        color: #777373;
      }
    }
    .remind-card-time {
      text-align: right;
      color: #4e3636;
      font-size: 15px;
      padding: 20px 15px 0 0;
    }
    .remind-card-showlist{
      width: 90%;
      margin: 0 auto;
      margin-top: 5px !important;
      padding:5px 0px; 
      display: flex;
      justify-content: space-between;
      border-top: 1px solid #ababab;
      color: #464141;
    }
    /deep/ .d-card__body {
      width: 100% !important;
    }
  }
</style>