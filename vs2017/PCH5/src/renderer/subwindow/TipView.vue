<template>
  <div class="content">
    <p class="tip-info">{{tipInfo}}</p>
    <div class="operate">
      <div class="hang-up" @click="hangUpByUI">
        <i class="icon" :title="挂断">&#xea2a;</i>
      </div>
    </div>
  </div>
</template>

<script>
const { remote, ipcRenderer } = require("electron");
const rtcplugin = remote.getGlobal("service")["rtcplugin"];
const Service = remote.getGlobal("service");

let type = 0;
let adminId = "";

export default {
  name: "TipView",
  beforeDestroy() {
    rtcplugin.regMultiEventCb(null);
  },
  beforeCreate() {
    // #/MultiMeeting?type=1&adminId=${resp.onwerId}&members=${resp.members}
    const seachParam = new URLSearchParams(window.location.hash.split("?")[1]);

    type = parseInt(seachParam.get("type"));
    adminId = seachParam.get("adminId");

    console.log("zxj::Tip>> 1 ", type, adminId);
  },
  data() {
    return {
      tipInfo: this.$t("groups.multiplayerVideoMsg")
    };
  },
  created() {
    rtcplugin.regMultiEventCb(resp => {
      // 事件类型(1呼叫 2邀请 3进房 4挂断 5结束 6超时 7应答)
      switch (resp.type) {
        case 5:
          // window.close();
          break;
      }
    });
  },
  computed: {},
  components: {},
  methods: {
    hangUpByUI(){
     // window.close();
     setTimeout(() => {window.close();}, 500);
    }
  }
};
</script>

<style lang="scss" scoped>
.content {
  display: flex;
  // align-items: center;
  z-index: 1;
  background: #333333;
  height: 100%;
  width: 100%;
  position: relative;
  justify-content: center;

  .tip-info {
    // height: 50px;
    color: white;
    display: flex;
    /* align-items: center; */
    /* justify-content: center; */
    padding: 16px;
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
    bottom: 30px;

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
    }
  }
}
</style>