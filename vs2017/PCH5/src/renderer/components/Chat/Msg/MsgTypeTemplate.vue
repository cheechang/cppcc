<template>
  <div class="type-template">
    <header
      :title="showTitle(message.messageObject)"
      :style="{ color: message.messageObject.titleColor, background:  message.messageObject.titleBGColor }"
    >{{showTitle(message.messageObject)}}</header>
    <section :class="{'is-radius':!message.messageObject.detailUrl, 'is-section-border': hasShowDetail}">
      <div class="message-content" v-html="templateContent(message.messageObject.content)"></div>
      <!--根据服务器返回的数据动态显示 -->
      <span
        v-for="(key,value) in changeFields(message.messageObject)"
        class="template-fields"
        :key="value"
        v-html="getFields(key)"
      ></span>
    </section>
    <footer v-if="hasShowDetail">
      <a
        class="open-link"
        @click="openNew(message.messageObject)"
        v-text="showBtnText(message.messageObject)"
      ></a>
    </footer>
  </div>
</template>
<script>
import { isDev, isOSX } from "../../../../comm/is";
import { mapGetters } from "vuex";
import { isJson } from "../Msg";
import { read } from "fs";
import { isUrl } from './../../../../comm/util.js'

export default {
  data() {
    return {

    };
  },
  props: {
    message: Object,
    id: String
  },
  mounted() {
    console.log("messageTemplate::", this.message);
  },
  computed: {
    ...mapGetters(["user_account"]),
    hasShowDetail() {
      let url = this.message.messageObject.detailUrl
      return url && !url.includes('https://vrvmail')
    }
  },
  methods: {
    changeFields(data) {
      let locale = this.$i18n.locale;
      data.body = data.body.replace(/[\r\n]/g, '<br>').replace(/\s/g, '&nbsp');
      const body = JSON.parse(data.body);
      let fields;
      if(locale === 'zh-CN'){
          fields = body.fields;
          if(fields){
            return fields;
          }else{
            fields = data.fields;
            if (fields) {
              return JSON.parse(fields.replace('"fields":', ""));
            }
          }
      }else{
        fields = body.fields_eng;
        if (fields) {
          return fields;
        }else{
          fields = body.fields;
          if(fields){
            return fields;
          }else{
            fields = data.fields;
            if (fields) {
              return JSON.parse(fields.replace('"fields":', ""));
            }
          }
        }
      }
      //   const fields = data.fields;
      //   if (fields === undefined || fields === "") return;
      //   return JSON.parse(fields.replace('"fields":', ""));
      // }else{

    },
    showTitle(msg){
      msg.body = msg.body.replace(/[\r\n]/g, '<br>').replace(/\s/g, '&nbsp');
      const body =  JSON.parse(msg.body);
      let locale = this.$i18n.locale;
      if(locale === 'zh-CN'){
        return body.title;
      }else{
        return body.title_eng || body.title; 
      }
    },
    showBtnText(msg) {
      console.log("url:::", msg);
      // return "查看详情";
      return this.$t("chat.details");
    },

    templateContent(content) {
      if (content === undefined || content === "") return;
      content = content.replace(/\n/g, "<br/>").replace(/\s/g, " ");
      return content;
    },

    getFields(name) {
      return `${Object.keys(name)[0]}:${_.values(name)[0]}`;
    },

    openNew(msg) {
      let body = msg.body.replace(/[\r\n]/g, '<br>').replace(/\s/g, '&nbsp');;
      if(typeof body === 'undefined') {
        body = "{}";
      }
      body = JSON.parse(body);
      let extendInfo = "";
      let newSelects = [];
      if (body.type == "rtc") {
        extendInfo = body.extendInfo;
        if (!extendInfo) {
          this.$toast.open({
            duration: 1500,
            message: this.$t("rtc.templateErrorTip"),
            position: "is-top",
            type: "is-danger"
          });
          return;
        }
        newSelects = extendInfo.selects;
        const mode = extendInfo.mode;
        if (this.id != extendInfo.groupId && mode === 'mcalling') {
          this.$toast.open({
            duration: 1500,
            message: this.$t("rtc.groupErrorTip"),
            position: "is-top",
            type: "is-danger"
          });
        } else {
          if(mode === 'mcalling'){
            this.$Service.rtcplugin.joinByTemplate(
              {
                reqType: 8,
                extendJson: msg.body
              },
              cb => {
                console.log("joinByTemplate", cb);
                if (cb.code == 0) {
                  this.openDoodMeeting(extendInfo, newSelects);
                } else if(cb.code == 4) {
                  this.$toast.open({
                    duration: 1500,
                    message: this.$t("rtc.netErrorTip"),
                    position: "is-top",
                    type: "is-danger"
                  });                  
                } else if(cb.code == 13 || cb.code == 14 || cb.code == 17) {
                  this.$toast.open({
                    duration: 1500,
                    message: this.$t("rtc.vesionErrorTip"),
                    position: "is-top",
                    type: "is-danger"
                  });                  
                } else if(cb.code == 15) {
                  this.$toast.open({
                    duration: 1500,
                    message: this.$t("rtc.notMemberErrorTip"),
                    position: "is-top",
                    type: "is-danger"
                  });                  
                }else if(cb.code == 83) {
                  this.$toast.open({
                    duration: 1500,
                    message: this.$t("rtc.timeoutErrorTip"),
                    position: "is-top",
                    type: "is-danger"
                  });                  
                }else{
                  this.$toast.open({
                    duration: 1500,
                    message: this.$t("rtc.joinErrorTip", { code : cb.code }),
                    position: "is-top",
                    type: "is-danger"
                  });
                }
              }
            );
          }else{
            this.openDoodMeeting(extendInfo, newSelects);
          }
        }
      } else if (isJson(msg.detailUrl)) {
        extendInfo = msg.detailUrl;
        if (typeof extendInfo === "string") {
          extendInfo = JSON.parse(extendInfo);
        }
        newSelects = msg.relatedUsers;
        this.openDoodMeeting(extendInfo, newSelects);
      }else {
        let url = msg.detailUrl;
        if(!isUrl(url)){
          url = 'https://mediasoup.linkdood.cn:3443/mcallingupdate.html';
        }
        console.log("openNew::url:", url);
        return this.$ipc.send("new-window", {
          winUrl: url,
          winType: "templateMsg",
          winTitle: this.$t("chat.viewDetails"),
          shapeType: "normal"
        });
      }
    },

    openDoodMeeting(detailUrl, selects) {
      if (!detailUrl.serverUrl || !detailUrl.serverPort) {
        let serverInfo = this.$Service.rtc.getMultiServerSync();
        let { turnAddr } = serverInfo;
        let serverUrl = "";
        let serverPort = "";

        if (turnAddr && turnAddr.indexOf(":") !== -1) {
          serverUrl = turnAddr.split(":")[0];
          serverPort = turnAddr.split(":")[1];
        }
        detailUrl = Object.assign(detailUrl, { serverUrl, serverPort });
      }
      if (!detailUrl.groupId) {
        let groupId = this.message.messageObject.targetId;
        detailUrl = Object.assign(detailUrl, { groupId });
      }
      if (!detailUrl.roomName) {
        detailUrl = Object.assign(detailUrl, {
          roomName: this.$t("chat.douShipin")
        });
      }
      if (!detailUrl.startTime) {
        detailUrl = Object.assign(detailUrl, {
          startTime: new Date().getTime()
        });
      }
      let locale = this.$i18n.locale;
      let members =
        JSON.stringify(selects) ||
        JSON.stringify(this.message.messageObject.relatedUsers);
      // let groupId = this.message.messageObject.targetId;
      // let creatorId = this.message.messageObject.fromId;
      let version = `${this.$pkg.version}-${this.$Service.config.getSdkVersion()}`;
      let platform = isOSX ? "pc-mac" : "pc-win";
      let adminId = detailUrl.onwerId || detailUrl.adminId;
      console.log("version:", version, "platform:", platform);
      let template_static = "vrv-static/plugins";
      const mediadood = template_static + "/mediadood/index.html";
      let url = `${mediadood}?roomId=${detailUrl.roomID}&displayName=${
        this.user_account.name
      }&userID=${this.user_account.userId}&mode=${detailUrl.mode}&startTime=${
        detailUrl.startTime
      }&stopTime=${
        detailUrl.stopTime
      }&adminId=${adminId}&members=${members}&serverUrl=${
        detailUrl.serverUrl
      }&serverPort=${detailUrl.serverPort}&locale=${locale}&groupId=${
        detailUrl.groupId
      }&version=${version}&platform=${platform}&title=${
        detailUrl.roomName
      }&desc=${detailUrl.desc}`;
      let winType = "mediadood";
      let winTitle =
        detailUrl.subType === 14
          ? this.$t("chat.douShipin")
          : this.$t("chat.douZhibo");
      console.log("openDoodMeeting::url:", url);
      return this.$ipc.send("new-window", {
        winUrl: url,
        winType: winType,
        winTitle: winTitle,
        shapeType: "normal"
      });
    }
  }
};
</script> 
<style lang="scss" scoped>
.type-template {
  width: 280px;
  // height: 240px;
  display: flex;
  flex-direction: column;
  padding: 3px;
  overflow: hidden;
  header {
    border-radius: $--border-radius-large $--border-radius-large 0 0;
    min-height: 30px;

    display: -webkit-box;
    -webkit-line-clamp: 3;
    -webkit-box-orient: vertical;
    overflow: hidden;
    padding: 5px;
  }
  .is-section-border {
    border-bottom: solid 1px $--border-color-grey;
  }
  section {
    flex: 1;
    font-size: $--font-size-small;
    display: flex;
    flex-direction: column;
    justify-content: space-around;
    background: #fff;
    padding: 0px 8px;
    .message-content {
      color: #000 !important;
    }
    .template-fields {
      color: #000 !important;
    }
  }
  .is-radius {
    border-radius: 0 0 $--border-radius-large $--border-radius-large;
  }
  footer {
    width: 100%; // align-self: flex-end;
    display: flex;
    justify-content: flex-end;
    padding-right: 10px;
    font-size: $--font-size-mid;
    background: #fff;
    border-radius: 0px 0px $--border-radius-large $--border-radius-large;
    height: 30px;
    align-items: center;
    a {
      color: get-blue-color(accent-3);
      & {
        cursor: pointer;
      }
    }
  }
}
</style>
