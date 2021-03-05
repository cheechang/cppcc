<template>
  <div class="multi-meeting">
    <div class="his-info">
      <v-avatar class="user-avatar" :src="tipAvatar" :offline="false" shape="round"/>
      <span class="his-name">{{tipName}}</span>
      <span class="tip-info">{{tipInfo}}</span>
      <!-- <div class="">
            <span class="dian"></span>
            <span class="dian"></span>
            <span class="dian"></span>
      </div>-->
    </div>
    <p
      :style="{'position':'absolute','color':'#fff','font-size':'18px','left':'34%'}"
      v-if="showTargetBusy"
    >{{$t('chat.remoteBusy')}}</p>
    <div class="memberlist">
      <span class="member" v-for="(item,index) in members" :key="index">
        <v-avatar
          class="avatar"
          size="is-small"
          :src="item.thumbAvatar"
          :offline="false"
          shape="round"
          :title="item.remark || item.name"
        />
      </span>
    </div>
    <div class="operate">
      <div class="hang-up" @click="hangUpByUI" v-if="!waitting">
        <i class="icon" :title="$t('chat.hangUp')">&#xea2a;</i>
      </div>
      <div class="deal-Area" v-if="waitting">
        <i
          class="icon"
          @click="hangUpByUI"
          :style="{'color':'red','background':'#fff'}"
          :title="$t('chat.reject')"
        >&#xea2a;</i>
        <i
          class="icon"
          @click="joinMeeting"
          :style="{'background':'#fff','color':'#4cbc3c', 'margin-left': '35px'}"
          :title="$t('chat.accept')"
        >&#xe654;</i>
      </div>
      <!-- <div class="hang-up" @click="hangUpByUI" v-if="!waitting">挂 断</div> -->
      <!-- <div class = "buttonArea" v-if="waitting">
        <div class="accept" @click="acceptVideo" v-if="!waitting">接 受</div>
        <div class="reject" @click="rejectVideo" v-if="!waitting">拒 绝</div>
      </div>-->
    </div>
  </div>
</template>

<style lang="scss">
.notices {
  .toast {
    margin-top: 0px !important;
    // border-radius: 20px!important;
    padding: 0.55em 0.5em;
    min-width: 0px !important;
    border-top-width: 3px;
    border-top-color: rgba(0, 0, 0, 0.3);
    border-top-style: none !important;
    div {
      width: 100%;
    }
  }
}
.multi-meeting {
  display: flex;
  align-items: center;
  // flex-direction: column;
  width: 100%;
  height: 100%;
  z-index: 1;
  position: absolute;
  background: #27354f; //rgba(0, 0, 0, 0.2);
  .his-info {
    flex: 1;
    display: flex;
    position: absolute;
    font-size: 14px;
    flex-direction: column;
    align-items: center;
    width: 100%;
    justify-content: center;
    top: 80px;

    // .tip-name {
    //     height: 100%;
    //     color: white;
    //     flex-direction: row;
    //     align-items: center;

    .user-avatar {
      width: 80px;
      height: 80px;
      border-radius: $--border-radius-circle;
    }

    // }

    .his-name {
      top: 50px;
      font-size: 20px;
      color: white;
      white-space: nowrap;
      text-overflow: ellipsis;
      overflow: hidden;
      max-width: 200px;
      padding: 5px;
    }

    .tip-info {
      height: 50px;
      color: white;
      display: flex;
      align-items: center;
      justify-content: center;
      padding: 5px;
    }
  }

  .memberlist {
    overflow-x: hidden;
    overflow: hidden;
    padding: 0 40px;
    width: 100%;
    height: 80px;
    display: flex;
    justify-content: center;
    /* top: 100px; */
    /* flex: 1; */
    position: relative;
    top: 100px;
    flex-wrap: wrap;
    .member {
      padding: 4px;
      width: 18%;
      /* width: 100px; */
      /* padding: 20px; */
      display: flex;
      justify-content: center;

      .avatar {
        width: 32px;
        height: 32px;
      }
    }
  }

  .operate {
    flex: 1;
    display: flex;
    position: absolute;
    font-size: 14px;
    flex-direction: row;
    height: 40px;
    align-items: center;
    width: 100%;
    justify-content: center;
    bottom: 15px;
    .deal-Area {
      font-size: 12px;
      display: flex;
      //opacity: 0.5;
      align-items: center;
      justify-content: center;
      /* border-radius: 10px; */
      cursor: pointer;
      .icon {
        font-size: 40px;
        height: 20px;
      }
      &:hover {
        opacity: 1;
      }
    }
    .hang-up {
      background: #fff;
      color: red;
      font-size: 12px;
      display: flex;
      opacity: 0.5;
      align-items: center;
      justify-content: center;
      /* border-radius: 10px; */
      cursor: pointer;

      .icon {
        font-size: 40px;
      }

      &:hover {
        opacity: 1;
      }
    }
  }
}
</style>

<script>
const { remote, ipcRenderer } = require("electron");
const rtcplugin = remote.getGlobal("service")["rtcplugin"];
const Service = remote.getGlobal("service");
const user_service = remote.getGlobal("service").user;

// let seachParam = null;
// let video_type;
let adminId;
let roomId;
let memberIds;
let groupId;
let self = null;
let ishangUp = false; // 已经挂断

function multiCallback(resp) {
  console.log("zxj::multiCallback>>", resp);
  // 事件类型(1呼叫 2邀请 3进房 4挂断 5结束 6超时 7应答)
  switch (resp.type) {
    case 3:
      {
        const member = self.members.find(item => {
          return item.id === resp.userId;
        });
        let showName = resp.userId;
        if (member) {
          showName = member.remark || member.name;
        }
        //  self.showToast(`${showName}加入会议`,'is-info');
        // self.showToast(
        //   self.$t("rtc.joinRoomTip", { value: showName }),
        //   "is-info"
        // );
      }
      break;
    case 4:
      {
        const member = self.members.find(item => {
          return item.id === resp.userId;
        });
        let showName = resp.userId;
        if (member) {
          showName = member.remark || member.name;
        }
        self.members = self.members.filter(item => {
          return item.id !== resp.userId;
        });
        console.log("zxj::multiCallback>>4 ", member, self.members);
        // self.showToast(`${showName}退出会议`,'is-info');
        // self.showToast(
        //   self.$t("rtc.leaveRoomTip", { value: showName }),
        //   "is-info"
        // );
      }
      break;
    case 5:
      {
        ishangUp = true;
        if (
          resp.annotation == "local_sdk_deal_ios_intoroom" ||
          resp.annotation == "local_sdk_deal_ios_hungup" ||
          resp.annotation == "local_sdk_deal_android_intoroom" ||
          resp.annotation == "local_sdk_deal_android_hungup"
        ) {
          self.showToast(self.$t("rtc.otherAnswerTip"), "is-warning");
        } else {
          self.showToast(self.$t("rtc.closeRoom"), "is-warning");
        }
        setTimeout(() => {
          self.hangUpByRtcPlugin();
        }, 2000);
      }
      break;
    case 6:
      {
        // self.hangUpByRtcPlugin();
        // self.showToast('超时未响应','is-warning');
        // self.showToast(self.$t("rtc.joinRoomTimeout"), "is-warning");
      }
      break;
    default:
      break;
  }
}

export default {
  name: "multiMeeting",
  beforeDestroy() {
    rtcplugin.regMultiEventCb(null);
  },
  beforeCreate() {
    ipcRenderer.send("plugin-notify", true);
    // #/MultiMeeting?type=1&adminId=${resp.onwerId}&members=${resp.members}
    const seachParam = new URLSearchParams(window.location.hash.split("?")[1]);

    const type = parseInt(seachParam.get("type"));
    roomId = seachParam.get("roomId");
    adminId = seachParam.get("adminId");
    groupId = seachParam.get("groupId");
    // members = JSON.parse(seachParam.get("members"));
    memberIds = seachParam.get("members").split(",");
    console.log(
      "zxj::multiMeeting>>",
      seachParam,
      type,
      adminId,
      memberIds
    );
  },

  created() {
    self = this; 
    ipcRenderer.on('closeRtc', () => {
        ipcRenderer.send("plugin-notify", false);
    })
    if (adminId) {
      // 被叫
      this.waitting = true;
      Service.search.getUserInfo({ userId: adminId }, successRes => {
        let userInfo = successRes.users;
        this.tipName = userInfo.remark || userInfo.name;
        this.tipAvatar = userInfo.thumbAvatar;
      });
      this.tipInfo = this.$t("rtc.inviteMulitVideo"); //'邀请你多人视频';
    } else {
      // 主叫
      this.waitting = false;
      adminId = this.user_account.userId;
      this.tipName = this.user_account.name;
      this.tipAvatar = this.user_account.thumbAvatarUrl;
      this.tipInfo = this.$t("rtc.waitAccept"); //'正在等待对方接受请求';
    }

    Service.group.getMemberList(
      {
        groupId
      },
      result => {
        const map = new Map(result.members);
        memberIds.forEach(id => {
          this.members.push(map.get(id));
        });
      }
    );
  },
  data() {
    return {
      start_time: 0, // 开始时间
      local_id: "",
      showTargetBusy: false, //对方忙提示
      waitting: false, // false:主叫；true：被叫
      isConnection: false, // 是否连通
      tipName: "", // 对方的名字
      tipAvatar: null, // 对方头像
      tipInfo: "", // 提示信息
      userId: "",
      userName: "",
      userAvatar: "",
      members: [],
      webRtcInfoWin: null,
      is_connected: false
    };
  },
  mounted() {
    rtcplugin.regMultiEventCb(multiCallback);
    this.getMultiCbList(roomId);
    let language = Service.config.getLanguage();
    this.$i18n.locale = language;
    console.log("this.$i18n", this.$i18n);
    if (this.waitting === false) {
    }
  },
  methods: {
    /**
     * 顶部提示气泡
     */
    showToast(m, t) {
      this.$toast.open({
        duration: 2000,
        message: m,
        position: "is-top",
        type: t
      });
    },

    joinMeeting() {
      if (ishangUp) return;
      ipcRenderer.send("plugin-notify", false);
      // groupId、roomId、members
      user_service.getAccountInfo(null, account => {
        const userId = account.id;
        const userName = account.name;
        const userAvatar = account.thumbAvatar;
        const request = {
          reqType: 3,
          groupId,
          roomId,
          members: memberIds,
          userId,
          userName,
          adminId
        };
        rtcplugin.joinMeeting(request, cb => {
          window.close();
        });
      });
    },
     getMultiCbList(){
      let list = rtcplugin.getMultiCbList();
      Service.log(`zxj::MultiMeeting::getMultiCbList:roomid=${roomId} --- ${list}`);
      if(list){
        list.forEach(item =>{
            if(item.type == 5){
              ipcRenderer.send("plugin-notify", false);
              rtcplugin.clearMultiCbList();
              this.hangUpByRtcPlugin();
              return;
            }
        });
      }
    },
    hangUpInner(cancel) {
      ipcRenderer.send("plugin-notify", false);
      console.log("RTC_INFO:hangUpInner ", cancel);
      const request = {
        reqType: 5,
        annotation: cancel ? "hungup" : "busy",
        groupId,
        roomId
      };
      rtcplugin.hangUp(request, cb => {
        console.log("RTC_INFO:hangUpByMain1 ", cb);
        rtcplugin.clearMultiCbList();
        window.close();
      });
    },
    hangUpByMain() {
      console.log("RTC_INFO:hangUpByMain");
      this.hangUpInner(true);
    },
    hangUpByRtcPlugin() {
      console.log("RTC_INFO: hangUpByRtcPlugin");
      this.hangUpInner(false);
    },
    hangUpByUI() {
      if (ishangUp) return;
      console.log("RTC_INFO:hangUpByUI");
      this.hangUpInner(true);
      // window.close();
    }
  }
};
</script>
