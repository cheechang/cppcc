<template>
  <v-modal :cardStyle="cardStyle">
    <div class="box-content">
      <div class="box-title theme-bgc_font">
        <span>{{$t('user.manageLoginDevices')}}</span>
        <i class="icon" @click="closeModal">&#xe650;</i>
      </div>
      <table>
        <thead>
          <tr class="thead-trStyle">
            <th>{{$t('user.deviceName')}}</th>
            <th>{{$t('user.loginTime')}}</th>
            <th>{{$t('user.operation')}}</th>
          </tr>
        </thead>
        <tbody>
          <tr v-for="(item,index) in accountsList" :key="index" class="tbody-trStyle">
            <td @click="aaa='&#xe627;'">
              <div class="iconfont-position">
                <i class="icon" v-html="getIcon(item.deviceType)"></i>
                {{getDeviceName(item)}}
              </div>
            </td>
            <td class="time-login">
              <span >{{item.loginTime | getLoginTime}}</span>
            </td>
            <td>
              <v-button @click="confirmDelete(index, item.macCode)">
                <i class="icon" :title="$t('user.removeDevice')">&#xe6bb;</i>
              </v-button>
              <span v-if="item.macCode.indexOf(computerInfo) !== -1">{{$t('user.mine')}}</span>
            </td>
          </tr>
        </tbody>
      </table>
    </div>
    <div class="tipStyle">
      <div>
        <span>*</span>
        {{$t('auth.unitDeletionTips')}}
        </div>
    </div>
    <!-- 弹出提示框 -->
    <v-modal v-if="alertCardModal" :cardStyle="alertCardStyle">
      <div class="modal-card-body">
        <p class="card-body-font">{{$t('user.makeSureRemEquipment')}}</p>
      </div>
      <div class="modal-card-footer">
        <div>
          <button @click="alertCardModal = false">{{$t('common.cancel')}}</button>
          <button @click="clearRecord()">{{$t('work.uninstall')}}</button>
        </div>
      </div>
    </v-modal>
  </v-modal>
</template>

<script>
import { getConfig, setConfig } from "../../../../../comm/util";
import _ from "lodash";
export default {
  //时间戳过滤器
  filters: {
    getLoginTime(value) {
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
      //与其他时间对比,如果相同则只显示目前是几点
      if (
        year === nowTime.getFullYear() &&
        month === nowTime.getMonth() + 1 &&
        day === nowDay
      ) {
        return " " + timeMinutes;
      } else {
        //时间不是当前,则显示全部日期
        return yearMonthDay + " " + timeMinutes;
      }
    }

  },
  data() {
    return {
      macCode: "",
      listIndex: "",
      alertCardModal: false,
      computerInfo: getConfig({ key: "macAddress" }),
      accountsList: [],
      cardStyle: {
        width: "500px",
        height: "470px",
        borderRadius: "4px"
      },
      alertCardStyle: {
        // width: "290px",
        maxWidth:"330px",
        height: "120px",
        borderRadius: "4px"
      },
      deviceIcon: {
        1: "&#xe627;",
        2: "&#xe693;"
      }
    };
  },
  created() {
    let param = null;
    this.$Service.user.getDeviceLoginRecord(param, resp => {
      console.log("reso::::", resp);
      this.accountsList = _.sortBy(resp.records, e => e.loginTime);
      this.accountsList.sort(function(a,b){
        return b.loginTime - a.loginTime;
      })
      console.log('this.accountsList',this.accountsList)
    });
  },
  methods: {
    getDeviceName(item) {
      let deviceName = "";
      if (item.deviceType === 1) {
        // 电脑设备
        deviceName = item.deviceInfo;
      } else if (item.deviceType === 2) {
        // 手机设备
        let system = item.deviceInfo.match(/(\S*?)-/)[1];
        if (system === "an") {
          deviceName = item.deviceInfo.match(/^an-([^\f\r\t\v]*?)#/)[1];
        } else if (system === "ios") {
           deviceName = item.deviceInfo.match(/-([^#]+)#/)[1];
        }
      }
          
      return deviceName;
    },
    clearRecord() {
      let param = [this.macCode];
      this.$Service.user.deleteDeviceLoginRecord(param, resp => {
        if (resp.code === 0) {
          this.accountsList.splice(this.listIndex, 1);
          this.alertCardModal = false;
          this.$toast.open({
          message: this.$t('common.deleteSuccess'),
          position: "is-top",
          type: "is-success"
        });
        }else {
          this.$toast.open({
          message: this.$t('common.deleteFailed'),
          position: "is-top",
          type: "is-danger"
        });
        }
      });
    },
    closeModal() {
      this.$emit("handleCancel");
    },
    confirmDelete(index, macCode) {
      this.macCode = macCode;
      this.listIndex = index;
      this.alertCardModal = true;
    },
    getIcon(deciceType) {
      return this.deviceIcon[deciceType];
    }
  }
};
</script>
<style lang="scss" scoped>
.box-content {
  width: 100%;
  height: 100%;
  display: flex;
  flex-direction: column;
  .box-title {
    padding: 12px 10px;
    display: flex;
    justify-content: space-between;
    font-size: 16px;
  }
  table {
    thead {
      padding: 20px 0px;
      .thead-trStyle {
        background: #715a5a38;
        th {
          text-align: center;
          height: 40px;
          width: 130px;
          line-height: 40px;
          font-size: 15px;
          &:first-child {
            text-align: left;
            position: absolute;
            left: 25px;
          }
        }
      }
    }
    tbody {
      .tbody-trStyle {
        border-bottom: 1px solid #eae0e0;
        background-color: #f5f2f2;
        &:hover {
          opacity: 0.8;
        }
        .time-login{
          text-align: center;
        }
        td {
          text-align: right;
          height: 45px;
          line-height: 45px;
          &:first-child {
            text-align: left;
            width: 165px;
          }
          &:last-child {
            .icon {
              color: #f00;
            }
            span {
              position: absolute;
              right: 12px;
            }
          }
          .button {
            height: 1.5em;
            margin-top: (45px - 24px)/2;
            margin-right: 56px;
          }
          .iconfont-position {
            margin-left: 10px;
            width: 180px;
            overflow: hidden;
            white-space: nowrap;
            text-overflow: ellipsis;
          }
          .icon {
            font-size: 20px;
          }
        }
      }
    }
  }
}
.tipStyle {
  padding: 5px 0px;
  text-align: center;
  background-color: #e8e1e1;
  font-size: 12px;
  span {
    color: red;
    line-height: 1;
    font-size: 18px;
  }
}
.modal-card-body {
  height: 120px;
  border-bottom: 1px solid #dbdbdb;
  .card-body-font {
    color: #4a4a4a;
    font-size: 1rem;
    font-weight: 400;
    line-height: 67px;
    padding-left: 20px;
  }
}
.modal-card-footer {
  background: whitesmoke;
  height: 85px;
  div {
    display: flex;
    justify-content: flex-end;
    margin-right: 5px;
    margin-top: 5.5px;
    button {
      cursor: pointer;
      margin: 0;
      padding: 9px 20px;
      border: none;
      outline: none;
      font-weight: 600;
      font-size: 16px;
      &:first-child {
        color: #000;
        margin-right: 5px;
        background: whitesmoke;
        border-radius: 4px;
        //  &:hover{
        //   background-color:#DDDDDD;
        //  }
      }
      &:last-child {
        color: #fff;
        background-color: #323a7b;
        border-radius: 4px;
      }
    }
  }
}
</style>
