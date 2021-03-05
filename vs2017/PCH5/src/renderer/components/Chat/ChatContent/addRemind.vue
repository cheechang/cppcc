<template>
  <v-modal  @close="$emit('close')">
  <!-- <div class="add-remind" @click.stop.self="closeModel"> -->
    <d-card class="add-card" :body-style="{ padding: '0px' }" :style='cardStyle' >
        <d-icon
        icon="d-icon-close-button"
        size="14"
        color="#9CA2A9"
        class="add-close"
        @click="closeModel"
      ></d-icon>
      <div class="remind-title">设置消息提醒</div>
      <date-picker 
       :popupStyle='popupStyle'
       class="date-picker" 
       v-model="timeValue" 
       lang="zh" 
       type="datetime" 
       :use12h="false"
       :clearable="false"
       format="YYYY-MM-DD hh:mm A" 
       valueType='timestamp' 
       :confirm = 'true'
       :editable = 'false'
       :disabledDate="notBeforeDate"
       :disabledTime="notBeforeTime"
       ></date-picker>
      <d-button size='mini' class="button-position" @click='setDateTime'>{{$t('common.confirm')}}</d-button>
    </d-card>
  <!-- </div> -->
    </v-modal>
</template>
<script>

import DatePicker from 'vue2-datepicker';
import 'vue2-datepicker/index.css';
import '../../../../renderer/ui/scss/components/_datepicker.scss';
import 'vue2-datepicker/locale/zh-cn';

const year = new Date().getFullYear();
const month = new Date().getMonth();
const day = new Date().getDate();
const hours = new Date().getHours();
export default {
  name: "Add-remind",
  components: { DatePicker },
  props:['msgBody'],
  data() {
    return {
      timeValue:'',
      cardStyle:{
        width:'260px',
        height:'120px'
      },
      popupStyle:{
        top: '276px',
        left: '277px'
      }
    };
  },
  created() {
  },
  methods: {
    closeModel() {
      this.$emit('closeAddRemind')
    },
    setDateTime() {
      let param = {
        receiverUserId:"0",
        reminderTime:this.timeValue/1000 + '',
        msg:this.msgBody
      }
      this.$Service.chat.createReminderMsg( param, resp => {
        if(resp.code === 0){
          console.log('code == 0')
          this.$emit('settingSuccess');
        }
       console.log('设置消息提醒',resp)
     })
    //  this.$emit('closeAddRemind')
    },
    notBeforeDate(date){
      return date < new Date(year, month, day);
    },
    notBeforeTime(date) {
      return date < new Date(year, month, day, hours + 1);
    },
  }
};
</script>
<style lang="scss" scoped>
// /deep/ .mx-table-date td, .mx-table-date th {
//       text-align: center !important;
//       line-height: 32px !important;
//     }
/deep/ .mx-datepicker-popup{
   .mx-calendar-content{
     .mx-table-date{
      td,tr{
        text-align: center !important;
        line-height: 32px !important;
      }
    }
  }
}
/deep/ .modal-card {
  width: 260px;
  border-radius: 4px;
}
//.add-remind {
  // width: 100%;
  // height: 100%;
  // background-color: rgba(0, 0, 0, 0.5);
  // position: absolute;
  // z-index:2;
//}
.add-card {
  // overflow: visible;
  // position: absolute;
  top: 0;
  bottom: 0;
  right: 0;
  left: 0;
  margin: auto;
  /deep/ .d-card__body {
    box-sizing: border-box;
  }
  .add-close {
    float: right;
    padding:10px 10px 0 0;
    font-size: 14px !important;
    &:hover {
      cursor: pointer;
      color: #3370ff !important;
    }
  }
  .remind-title {
    padding:10px 0 0 22px ;
    font-size: 15px;
    color:#868181;
  }
  .date-picker {
    margin:5px 0 0 21px;
    text-align: center;

    
    // position: relative;
    // top: 0px;
    // left: 5px;
  }
  .button-position {
    float: right;
    margin:10px 25px 0 0;
  }
  .add-card-content {
    width: 100%;
    height: 100%;
    .d-icon-edit {
      position: relative;
      top: 5px;
      left: 18px;
    }
    .add-card-input {
      width: 80%;
      padding: 20px 0px 0px 25px;
    }
  }
}
</style>