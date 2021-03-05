<template>
  <div class="account-info">
    <div class="content-account">
      <card-lists
        :lists="userInfos"
        :img="userImg"
        :name="user_account.name"
        :gender="user_account.gender"
        :qrcode="qrcode"
        :title="$t('account.editProfile')"
        @icon-click="isModal = true"
      >
        <template slot-scope="data">
          <!-- <div
            v-if="isShowTitle(data.index)"
            class="edit-info-title"
            :style="{'padding-top':data.index === 0 ? '0px':'10px'}"
          >{{getTitle(data.index)}}</div> -->
          <div class="edit-info-item" v-show="!data.item.hideItem">
            <!-- <div class="right">
              <i class="icon" v-html="data.item.icon.left"></i>
            </div> -->
            <div class="info-item-content">
              <div class="content-title">
                {{data.item.content}}
                <!-- <i
                  class="icon"
                  v-if="(data.index===0||(data.item.isEnabled===1&&data.item.title))&&data.item.type!=='6'&&data.item.type!=='7'"
                  @click.self.stop="editInfo(data.index, data.item)"
                >&#xe67c;</i> -->
              </div>
              <div
                class="content-data edit-Content-Data"
                :ref="'contentAccount'+data.index"
                :class="{'edit-style': data.item.isEdit && data.index !== 1}"
                :contenteditable="data.item.isEdit && data.index !== 1"
                :style="{width: data.index===1?'65px':''}"
                :title="infoContent(data.item, data.index)"
                @keydown="editBoxEvent"
                @input="editText"
              >
                {{infoContent(data.item, data.index)}}
                <!-- <i
                  v-if="data.index===1"
                  class="icon"
                  :class="[
                    {'scale-xe678': isGenderList}
                  ]"
                  @click.self.stop="updataInfo(data.index, data.item)"
                >&#xe77a;</i> -->
              </div>
              <v-tooltip
                class="tool-tips"
                type="is-primary"
                position="is-bottom"
                :lable="getEditRuleTxt(data.item.type)"
                :always="data.item.isEdit&&data.item.type&&data.item.type == '6'"
              ></v-tooltip>
              <!-- <span
                class="tip-msg"
                v-if="!data.item.title && data.index!==1 && !data.item.isEdit && data.item.hasOwnProperty('isEdit')"
                @click.self.stop="editInfo(data.index, data.item)"
              >{{infoTipMsg(data.item)}}</span> -->
              <!-- <list
                class="gender-list"
                :listData="genderList"
                :isShow="isGenderList&&data.index===1"
                :selectedIndex="selectGender"
                @close-select-list="isGenderList = false"
                @select-item="selectItem"
              ></list> -->
            </div>
            <!-- <div class="left">
              <i
                v-if="data.item.isEdit"
                class="icon"
                :class="[data.item.animation]"
                v-html="data.item.icon.right"
                @click.self.stop="updataInfo(data.index, data.item)"
              ></i>
            </div> -->
          </div>
        </template>
      </card-lists>
      <v-modal v-if="isModal" cardSize="modal-style" @close="isModal=false">
        <change-header :isUserCenterModify="true" @close="isModal=false"></change-header>
      </v-modal>
    </div>
  </div>
</template>
<script>
import Vue from "vue";
import { mapGetters } from "vuex";
import changeHeader from "./changeUserAvatar.vue";
import CardLists from "./../../Common/CardLists/index.vue";
import List from "./../../Auth/common/list.vue";
import accountMixin from "./../AccountMixin.js";
import { placeCaretAtEnd, insertNode } from "../../Chat/At/at.js";
import config from "./../../../../comm/config.js";
import { getErrorMsg } from "../../../utils/utils.js";
export default {
  name: "personalAccount",
  mixins: [accountMixin],
  data() {
    return {
      nationCode: "",
      isModal: false,
      isGenderList: false,
      openedEditIndex: 0,
      openedEditType: "0",
      selectGender: 0,
      updataMsg: "",
      updateParam: {},
      titleList: [
        { index: 0, title: this.$t("user.basicInfo") },
        { index: 3, title: this.$t("user.contactInfor") }
      ],
      basicInfo: [
        {
          title: "",
          content: this.$t("user.name"),
          animation: "",
          isEdit: false,
          // icon: { left: "&#xe630;", right: "&#xe81f;" }
        },
        {
          title: "",
          content: this.$t("user.sex"),
          animation: "",
          isEdit: false,
          // icon: { left: "&#xe68b;", right: "&#xe77a;" }
        },
        {
          title:"",
          content: this.$t("cppcc.CommitteeMember"),
          animation:"",
          isEdit: false,
        },
        {
          title:"",
          content: this.$t("cppcc.national"),
          animation:"",
          isEdit: false,
        },
        {
          title:"",
          content: this.$t("cppcc.post"),
          animation:"",
          isEdit: false,
        },
        {
          title:"",
          content: this.$t("cppcc.circles"),
          animation:"",
          isEdit: false,
        },
        {
          title:"",
          content: this.$t("cppcc.group"),
          animation:"",
          isEdit: false,
        },
        {
          title:"",
          content: this.$t("cppcc.specialCommittee"),
          animation:"",
          isEdit: false,
        },
        {
          title:"",
          content: this.$t("cppcc.positionCommittee"),
          animation:"",
          isEdit: false,
        },
        {
          title:"",
          content: this.$t("cppcc.incumbentDuties"),
          animation:"",
          isEdit: false,
        },
        {
          title:"",
          content: this.$t("cppcc.location"),
          animation:"",
          isEdit: false,
        },
      ],
      genderList: [
        { type: 0, val: this.$t("account.secret") },
        { type: 1, val: this.$t("account.male") },
        { type: 2, val: this.$t("account.female") }
      ],
      cppccWork:[
        {
          title: "",
          content: this.$t("user.name"),
          animation: "",
          isEdit: false,
        },
        {
          title: "",
          content: this.$t("user.sex"),
          animation: "",
          isEdit: false,
          // icon: { left: "&#xe68b;", right: "&#xe77a;" }
        },
        {
          title:"",
          content: this.$t("cppcc.national"),
          animation:"",
          isEdit: false,
        },
        {
          title:"",
          content: this.$t("cppcc.company"),
          animation:"",
          isEdit: false,
        },
        {
          title:"",
          content: this.$t("cppcc.department"),
          animation:"",
          isEdit: false,
        },
        {
          title:"",
          content: this.$t("cppcc.position"),
          animation:"",
          isEdit: false,
        },
      ],
      // 个人中心修改信息编辑规则,以前在配置文件config.js中
      editRuleTxt: {
       '6':  this.$t('auth.nickIdRule'),
       '-1': this.$t('auth.userNameRule')
      },
    };
  },
  components: {
    changeHeader,
    CardLists,
    List
  },
  computed: {
    ...mapGetters([
      "user_account",
      "http_head",
      "auth_nationCode",
      "user_serverHost",
      "user_usever",
      "contact_enterpriseDicValues"
    ]),
    qrcode() {
      if (!this.user_account) return;
      console.log('i get qrcode: ', this.contact_enterpriseDicValues.isLocalHost);
      this.$Service.log(`i get qrcode:::${this.contact_enterpriseDicValues.isLocalHost}`);
      console.log('qrcode:::user_account:::',this.user_account);
      return {
        id: this.user_account.id,
        gender: this.user_account.gender,
        host: this.contact_enterpriseDicValues.isLocalHost,
        elogo: this.user_usever,
        serverhost: this.user_serverHost,
        type: 1
      };
    },
    userInfos() {
      // 初始化基础信息
      console.log("userInfos::::changed");
      console.log("basicInfo::::::", this.basicInfo);
      console.log("userInfos::::::", this.user_account);
      let userExtends = JSON.parse(this.user_account.entExtends)[0];
      if(userExtends.type == 0){
        console.log('userExtends',userExtends)
        this.basicInfo[0].title = this.user_account.name;
        this.basicInfo[1].title = userExtends.gender;
        this.basicInfo[2].title = userExtends.memberNum;
        this.basicInfo[3].title = userExtends.nation;
        this.basicInfo[4].title = userExtends.specialCommitteeDuty;
        this.basicInfo[5].title = userExtends.sector;
        this.basicInfo[6].title = userExtends.group;
        this.basicInfo[7].title = userExtends.specialCommittee;
        this.basicInfo[8].title = userExtends.specialCommitteeDuty;
        this.basicInfo[9].title = userExtends.specialCommitteeDuty;
        this.basicInfo[10].title = userExtends.myLocation;
        // this.updatedLoginData();
      
      // if (this.user_account.extends) {
      //   //从扩展字段读取联系方式
      //   try {
      //     let contact = JSON.parse(this.user_account.extends)[0];
      //     if (contact.contactPhones) {
      //       this.setContactPhoneOrMail(3, contact.contactPhones.split(",")[0]);
      //     }
      //     if (contact.contactEmails) {
      //       this.setContactPhoneOrMail(4, contact.contactEmails.split(",")[0]);
      //     }
      //   } catch (error) {
      //     console.log("解析extends出错");
      //   }
      // }
    // if (!this.basicInfo[3].title || !this.basicInfo[4].title) {
      //   //用户未设置联系方式
      //   for (let i = 0; i < this.user_account.accounts.length; i++) {
      //     if (
      //       1 == this.user_account.accounts[i].type &&
      //       !this.basicInfo[3].title &&
      //       this.user_account.accounts[i].accounts
      //     ) {
      //       this.setContactPhoneOrMail(
      //         3,
      //         this.user_account.accounts[i].accounts
      //       );
      //     } else if (
      //       3 == this.user_account.accounts[i].type &&
      //       !this.basicInfo[4].title &&
      //       this.user_account.accounts[i].accounts
      //     ) {
      //       this.setContactPhoneOrMail(
      //         4,
      //         this.user_account.accounts[i].accounts
      //       );
      //     }
      //   }
    // }
      console.log("this.basicInfo::::", this.basicInfo);
        return this.basicInfo;
      }else if(userExtends.type == 1){
        console.log('userExtends',userExtends)
        this.cppccWork[0].title = this.user_account.name;
        this.cppccWork[1].title = userExtends.gender;
        this.cppccWork[2].title = userExtends.memberNum;
        this.cppccWork[3].title = userExtends.nation;
        this.cppccWork[4].title = userExtends.specialCommitteeDuty;
        this.cppccWork[5].title = userExtends.sector;
        console.log("this.cppccWork::::", this.cppccWork);
        return this.cppccWork;
      }
    },
    gender() {
      return this.user_account.gender == 0
        ? this.$t("account.secret")
        : this.user_account.gender == 1
          ? this.$t("account.male")
          : this.$t("account.female");
    },
    userImg() {
      return (
        this.user_account.thumbAvatarUrl &&
        this.user_account.thumbAvatar.replace(/\\/g, "\\\\")
      );
    }
  },
  created() {
    // 初始化性别
    this.selectGender = this.user_account.gender;

    // 获取登录扩展信息
    this.getExtendConfig(66); //登录项拓展字段
    // console.log('this.',this.)
    if (this.user_account.entExtends) {
      this.getExtendConfig(102); //普通扩展字段
    }
    // this.$Service.enterprise.queryEntUserOneById({ userId: this.user_account.id, flag: 1 }, resp => {
    //     console.log('获取用户扩展字段json', resp);
    //     if (resp.code===0 && resp.users.length!==0){
    //        this.getExtendConfig(102); //普通扩展字段
    //        this.getUserExtendInfo()
    //     }
    // });

    this.nationCode =
      this.auth_nationCode === ""
        ? this.$Service.config.getSystemNationCode()
        : this.auth_nationCode;
  },
  methods: {
    updatedLoginData() {
      console.log("basicInfo:::", this.basicInfo);
      console.log("updatedLoginData:::user_account:::", this.user_account.accounts);
      // 遍历数组 匹配basci和推送值
      for (let index = 5; index < this.basicInfo.length; index++) {
        // 豆豆号字段特殊处理
        if (this.basicInfo[index].type === "6") {
          console.log("已修改豆豆号");
          this.basicInfo[index].title = this.user_account.nickId;
        }
        // 定义 索引值变量
        let accountIndex = 0;
        // 匹配索引值
        this.user_account.accounts.some((element, accountsIndex) => {
          if (this.basicInfo[index].type === element.type + "") {
            accountIndex = accountsIndex;
            return true;
          }
          return false;
        });
        console.log("同类项ID为::", accountIndex);
        if (accountIndex > 0) {
          this.basicInfo[index].title = this.user_account.accounts[
            accountIndex
          ].accounts;
          console.log("修改完成");
          console.log("当前basicInfo::", this.basicInfo);
        }
      }
    },
    setContactPhoneOrMail(index, title) {
      this.basicInfo[index].title = title;
      if (!this.basicInfo[index].isEdit) {
        let ele = document.getElementsByClassName("info-item-content"); //此处操作是为了修改过一次后，手机端修改，界面不刷新问题
        if (ele[index] && ele[index].children[1])
          ele[index].children[1].innerText = this.infoContent(
            this.basicInfo[index],
            index
          );
      }
    },
    isShowTitle(position) {
      return this.titleList.some((element, index) => {
        //console.log('element',element,'position:',position)
        if (element.index === position) return true;
      });
    },
    getTitle(position) {
      let title;
      this.titleList.some((element, index) => {
        if (element.index === position) {
          title = element.title;
          return true;
        }
      });
      return title;
    },
    // 编辑框编辑规则
    getEditRuleTxt(type) {
      if (type === undefined) return "";
      let txt = this.editRuleTxt[type];
      return txt;
    },
    // 编辑框为空时，是否可编辑文本提示
    infoTipMsg(item) {
      if (item.hasOwnProperty("isEnabled") && item.isEnabled === 1) {
        return this.$t("account.clickToEdit", { value: item.content });
      }
      return this.$t("groups.empty");
    },
    // 格式化要显示信息
    infoContent(item, index) {
      if (!item.hasOwnProperty("type")) return item.title;
      switch (Number(item.type)) {
        case 1:
        case -1: {
          let nation = item.title.substring(0, 4).replace(/\b(0+)/gi, "");
          return "+" + nation + " " + item.title.substring(4);
        }
        case 6:{
          let resTitle = item.title.replace(/([/][^/]+)$/,'');
          return resTitle;
        }
        default: {
          return item.title;
        }
      }
    },
    // 获取扩展配置
    getExtendConfig(parentId) {
      this.$Service.contact.queryExtendedField(
        { parentId: parentId, dicKey: "" },
        resp => {
          let basicExtend = resp.EnterpriseDictionarys;
          console.log("getExtendConfig:::", basicExtend);
          console.log("getExtendConfig:::user_account:::", this.user_account);
          // 遍历扩展配置，将所有获取的扩展字信息示到页面
          if (basicExtend.length) {
            if (parentId === 66) {
              this.titleList.push({
                index: this.basicInfo.length,
                title: this.$t("user.loginAccount")
              });
            } else {
              this.titleList.push({
                index: this.basicInfo.length,
                title: this.$t("user.extendInfo")
              });
            }
          }
          basicExtend.forEach((e, index) => {
            // console.log("parentId:::", parentId, "e:::", e);
            // console.log('this.$t(`loginType.${e.dickey}`):',this.$t(`loginType.${e.dickey}`));
            this.$set(e, "account", "");
            let extend;
            try {
              extend = JSON.parse(e.extend);
            } catch (error) {}
            let tempObj = {
              title: e.account,
              parentId: parentId,
              dickey: e.dickey,
              content:
                this.$t(`loginType.${e.dickey}`) === `loginType.${e.dickey}`
                  ? e.dicValue
                  : this.$t(`loginType.${e.dickey}`) || e.dicValue,
              type: parentId === 66 ? e.dickey : e.id,
              animation: "",
              isEdit: false,
              //isEnabled: parentId===66?extend.isEnabled:extend.isEdit,  // 客户端是否可编辑
              isEnabled: parentId === 66 ? 0 : extend.isEdit,
              icon: {
                // left: config.account.extendInfoIcon[e.dickey],
                //right: "&#xe81f;"
              }
            };
            // 判断当dickey == 6时，此为豆豆号字段，直接读取用户账户信息豆豆号字段赋值。
            if (parentId === 66 && e.dickey === "6")
              tempObj.title = this.user_account.nickId;
            if (parentId === 66 && e.dickey !== "6") {
              for (let i = 0; i < this.user_account.accounts.length; i++) {
                if (e.dickey == this.user_account.accounts[i].type) {
                  tempObj.title = this.user_account.accounts[i].accounts;
                }
              }
            }
            if (extend.isShow === 1 && parentId === 102) {
              //是扩展字段并且需要在客户端显示
              let entExtends = JSON.parse(this.user_account.entExtends)[0];
              Object.keys(entExtends).some(element => {
                if (element === e.dickey) {
                  tempObj.title =
                    entExtends[element] === "[]" ? "" : entExtends[element];
                  return true;
                }
              });
            }
            // if (e.dickey === '1'){
            //   //tempObj.title = this.user_account.phones[0]||'';
            //   tempObj.isEnabled = 0;
            // }
            // if (e.dickey === '3'){
            //   //tempObj.title = this.user_account.emails[0]||'';
            //   tempObj.isEnabled = 0;
            //   //console.log('tempObj.titletempObj.titletempObj.title:',(!tempObj.title && !tempObj.isEdit && tempObj.hasOwnProperty('isEdit')))
            // }
            // if (extend.isShow === 1 || parentId === 66) {
            //   console.log("添加拓展字段为::", tempObj);
            //   this.basicInfo.push(tempObj);
            // }
          });
        }
      );
    },
    // 获取用户扩展信息       暂未使用
    getUserExtendInfo() {
      this.$Service.enterprise.queryEntUserOneById(
        { userId: this.user_account.id, flag: 0 },
        resp => {
          console.log("获取用户扩展字段json", resp);
          if (resp.code !== 0 || resp.users.length === 0) return;
          let result = JSON.parse(resp.users[0].extend);
          _.forEach(result, (value, key) => {
            this.$Service.contact.queryExtendedField(
              { parentId: -2, dicKey: key },
              resp => {
                console.log(
                  `查字典--key(${key})对应的value:`,
                  resp,
                  "value类型:",
                  typeof value,
                  "value:",
                  value
                );
                if (
                  resp.EnterpriseDictionarys &&
                  resp.EnterpriseDictionarys.length !== 0
                ) {
                  let extend;
                  try {
                    extend = JSON.parse(resp.EnterpriseDictionarys[0].extend);
                  } catch (error) {}
                  let tempObj = {
                    title: value !== "[]" ? value : "",
                    content: resp.EnterpriseDictionarys[0].dicValue,
                    type: resp.EnterpriseDictionarys[0].id,
                    isEdit: false,
                    isEnabled: extend.isEdit, // 客户端是否可编辑
                    animation: "",
                    // icon: { left: "", right: "" }
                  };
                  if (resp.EnterpriseDictionarys[0].id == "1") {
                    tempObj.title = this.user_account.phones[0] || "";
                    tempObj.isEnabled = 0;
                  }
                  if (resp.EnterpriseDictionarys[0].id == "3") {
                    tempObj.title = this.user_account.email;
                    tempObj.isEnabled = 0;
                  }
                  if (extend.isShow === 1) {
                    this.basicInfo = _.filter(
                      this.basicInfo,
                      element => element.type !== tempObj.type
                    );
                    this.basicInfo.push(tempObj);
                  }
                }
              }
            );
          });
        }
      );
    },

    // 阻止contenteditable文本域回车事件
    editBoxEvent(e) {
      if (e.keyCode === 13) {
        e.preventDefault();
      }
    },
    // 输入框填写的文本
    editText(e) {
      if(e.target.innerText.length > 24){
        e.target.innerText = e.target.innerText.slice(0, 24)
        e.target.focus(); //解决ff不获取焦点无法定位问题
        var range = window.getSelection(); //创建range
        range.selectAllChildren(e.target); //range 选择obj下所有子内容
        range.collapseToEnd(); //光标移至最后
      }
      this.updataMsg = e.target.innerText;
    },

    // 激活编辑框
    editInfo(index, item) {
      if ((!item.isEnabled || item.isEnabled === 0) && index !== 0) {
        if (item.hasOwnProperty("isEnabled") && item.isEnabled === 0) {
          this.$toast.open({
            duration: 3000,
            message: this.$t("user.cantChange"),
            position: "is-top",
            type: "is-warning"
          });
        }
        return;
      }
      this.updataMsg = "";
      this.$refs["contentAccount" + this.openedEditIndex].innerText =
        this.openedEditType === "1" || this.openedEditType === "-1"
          ? this.infoContent(
              this.basicInfo[this.openedEditIndex],
              this.openedEditIndex
            )
          : this.basicInfo[this.openedEditIndex].title;
      //if (item.type == 3 || item.type == 7) return;
      this.openedEditIndex = index;
      this.openedEditType = item.type;
      // this.basicInfo[index].isEdit = true;
      let obj = Object.assign({}, this.basicInfo[index]);
      this.basicInfo.splice(index, 1, obj);
      this.basicInfo.forEach((element, i) => {
        if (element.hasOwnProperty("isEdit") && i !== index) {
          element.isEdit = false;
        }
      });
      if (item.type === "1" || item.type === "-1") {
        this.$refs[
          "contentAccount" + this.openedEditIndex
        ].innerText = item.title.substring(4);
      }
      let el = this.$refs["contentAccount" + index];
      document.addEventListener("click", this.clickOutsideAccount);
      setTimeout(() => {
        placeCaretAtEnd(el);
      }, 100);
    },

    // 更新信息
    updataInfo(index, item) {
      // 显示完成图片倒计时未结束时，不可点击。
      let lis = document.getElementsByClassName("edit-Content-Data");
      if (
        (lis[index].innerText === this.basicInfo[index].title && index !== 1) ||
        ((item.type === "1" || item.type === "-1") &&
          this.nationCode + lis[index].innerText ===
            this.basicInfo[index].title)
      ) {
        this.basicInfo[index].isEdit = false;
        this.updataMsg = "";
        if (item.type === "1" || item.type === "-1") {
          this.$refs["contentAccount" + index].innerText = this.infoContent(
            item,
            index
          );
        }
        return;
      }
      // if (item.icon.right === "&#xe632;" || item.icon.right === "&#xe6ac;")
        // return;
      // console.log(index, item);
      if (item.parentId && item.parentId === 102) {
        //此时修改的是企业扩展字段
        this.updateExtExtendInfo(index, item);
        return;
      }
      if (index === 0) {
        console.log("更新用户名");
        this.updataMsg = this.updataMsg.trim(); //去除字符串两头的空格
        console.log(this.updataMsg);
        let nameReg = /^.{1,24}$/;
        if (!nameReg.test(this.updataMsg)) {
          this.errPromptBox(this.$t("user.userNameLimit"), "is-danger");
          return;
        }
        this.updateParam = { name: this.updataMsg };
        this.updateAccountInfo(index);
      } else if (index === 1) {
        console.log("打开下拉列表");
        this.isGenderList = true;
      } else {
        switch (item.type) {
          case "6": {
            //豆豆号修改
            let ruls = /^[a-zA-Z][a-zA-Z0-9]*$/;
            if (!ruls.test(this.updataMsg)) {
              this.errPromptBox(
                this.editRuleTxt[item.type],
                "is-danger"
              );
              return;
            }
            console.log("更新信息登录扩展信息");
            this.updateParam = { nickId: this.updataMsg };
            this.$Service.log(
              `个人中心:::设置豆豆号:::${this.updateParam.nickId}`
            );
            this.updateAccountInfo(index);
            break;
          }
          case "3":
          case "-3": {
            //邮箱修改
            
            //去掉前后的所有空格
            let updataMsg = this.updataMsg.trim();
            let myreg = /^([a-zA-Z0-9]+[_|\_|\.]?)*[a-zA-Z0-9]+@([a-zA-Z0-9]+[_|\_|\.]?)*[a-zA-Z0-9]+\.[a-zA-Z]{2,3}$/;
            if (!(item.type === "-3" && !updataMsg)) {
              if (!myreg.test(updataMsg)) {
                this.errPromptBox(this.$t("auth.emailFormat"), "is-danger");
                return;
              }
            }
            this.updateAccounts(index, item);
            break;
          }
          case "1":
          case "-1": {
            //手机修改
            this.updataMsg = this.updataMsg
              ? this.nationCode + this.updataMsg
              : this.updataMsg;
            this.updateAccounts(index, item);
            break;
          }
          case "4": //4：userID, 5:身份证, 7:自定义帐号(不做限制)
          case "5":
          case "7": {
            this.updateAccounts(index, item);
            break;
          }
          default: {
            //console.log('item::',item);
            this.updateExtendInfo(index, item.type);
            break;
          }
        }
      }
      if (index !== 1) {
        // this.basicInfo[index].icon.right = "&#xe6ac;";
        this.basicInfo[index].animation = "loading-start";
      }
    },

    // 修改性别
    selectItem(type, item) {
      console.log(type, item);
      this.selectGender = type;
      this.updateParam = { gender: type };
      this.$set(this.basicInfo[1], "title", item);
      // this.basicInfo[1].isEdit = true;
      //this.basicInfo[1].icon.right = "&#xe6ac;";
      this.basicInfo[1].animation = "loading-start";
      this.updateAccountInfo(1);
    },
    //更新企业扩展信息
    updateExtExtendInfo(index, item) {
      let entExtends = JSON.parse(this.user_account.entExtends)[0];
      // Object.keys(entExtends).some(element => {
      //   if (element === item.dickey) {
      //     //tempObj.title = entExtends[element]==='[]'?'':entExtends[element]
      //     entExtends[element] = this.updataMsg;
      //     return true;
      //   }
      // });
      entExtends[item.dickey] = this.updataMsg;
      this.updateParam = { entExtends: JSON.stringify([entExtends]) };
      console.log("this.updateParam:", this.updateParam);
      this.updateAccountInfo(index);
    },
    // 更新账户信息
    updateAccounts(index, item) {
      if (item.type === "-1" || item.type === "-3") {
        //用户联系方式
        if (this.user_account.extends) {
          try {
            let extendsArray = JSON.parse(this.user_account.extends);
            let extendInfo = extendsArray[0];
            if (item.type === "-1") {
              if (extendInfo.contactPhones) {
                let phones = extendInfo.contactPhones.split(",");
                phones[0] = this.updataMsg;
                extendInfo.contactPhones = phones.join(",");
              } else {
                extendInfo.contactPhones = this.updataMsg;
              }
            } else {
              if (extendInfo.contactEmails) {
                let emailes = extendInfo.contactEmails.split(",");
                emailes[0] = this.updataMsg.trim();
                extendInfo.contactEmails = emailes.join(",");
              } else {
                extendInfo.contactEmails = this.updataMsg;
              }
            }
            extendsArray[0] = extendInfo;
            this.updateParam = { extends: JSON.stringify(extendsArray) };
          } catch (error) {
            console.log("解析extends出错");
          }
        } else {
          let extend = [
            {
              contactEmails: item.type === "-1" ? "" : this.updataMsg,
              contactPhones: item.type === "-1" ? this.updataMsg : "",
              revicetype: "",
              userId: parseInt(this.user_account.id)
            }
          ];
          this.updateParam = { extends: JSON.stringify(extend) };
        }
      } else {
        let accounts =
          this.user_account.accounts.filter(
            e => e.type !== parseInt(item.type)
          ) || [];
        accounts.push({ accounts: this.updataMsg, type: parseInt(item.type) });
        this.updateParam = { accounts: accounts };
      }
      console.log("this.updateParam:", this.updateParam);
      this.updateAccountInfo(index);
    },
    // 更新扩展信息
    updateExtendInfo(index, type) {
      this.$Service.user.updateExtendInfo(
        { account: this.updataMsg, type: parseInt(type), status: 1 },
        resp => {
          this._updateAccountInfoHandle(resp, index);
        }
      );
    },
    // 设置信息
    updateAccountInfo(index) {
      console.log("this.updateParam:", this.updateParam);
      this.$Service.user.updateAccountInfo(this.updateParam, resp => {
        this._updateAccountInfoHandle(resp, index);
      });
    },
    // 设置信息回调
    _updateAccountInfoHandle(resp, index) {
      this.$Service.log(`个人中心:::更新账号信息返回:::`);
      // this.basicInfo[index].icon.right = index === 1 ? "&#xe77a;" : "&#xe81f;";
      this.basicInfo[index].animation = "";
      if (resp.code !== 0) {
        this.errPromptBox(getErrorMsg(resp.code), "is-danger");
        return;
      }
      if (index !== 1) {
        this.basicInfo[index].title = this.updataMsg.toString();
        //this.$refs['contentAccount'+index].innerText = this.openedEditType === '1'?this.infoContent(this.basicInfo[this.openedEditIndex],this.openedEditIndex): this.basicInfo[this.openedEditIndex].title;
      }
      this.updataMsg = "";
      // this.basicInfo[index].icon.right = "&#xe632;";
      this.basicInfo[index].animation = "loading-success";
      let ele = document.getElementsByClassName("info-item-content");
      if (index !== 1) 
      {
        ele[index].children[1].innerText = this.basicInfo[index].title.slice(0,11);
      }
      setTimeout(() => {
        if (index !== 1)
          ele[index].children[1].innerText = this.infoContent(
            this.basicInfo[index],
            index
          );
        this.basicInfo[index].isEdit = false;
        // this.basicInfo[index].icon.right =
        //   index === 1 ? "&#xe77a;" : "&#xe81f;";
        this.basicInfo[index].animation = "";
        //if (index > 1)  this.$delete(this.basicInfo[index], 'isEdit');
      }, 20);
      // setTimeout(() => {
      //   this.basicInfo[index].isEdit = false;
      //   this.basicInfo[index].icon.right = index === 1 ? '&#xe77a;' : '&#xe81f;'
      //   this.basicInfo[index].animation = '';
      //   if (index > 1)  this.$delete(this.basicInfo[index], 'isEdit');
      // }, 1500);
      // if (this.basicInfo[index].title.length <= 11) return;
      // ele[index].children[1].innerHTML = this.basicInfo[index].title.substr(0, 10)+'...';
    },

    // 点击外部区域关闭编辑框
    clickOutsideAccount(e) {
      let el = this.$refs["contentAccount" + this.openedEditIndex].parentNode.parentNode;
      if (!el.contains(e.target)) {
        this.updataMsg = "";
        // this.$refs["contentAccount" + this.openedEditIndex].innerText = '正在更新请稍后';
        this.$refs["contentAccount" + this.openedEditIndex].innerText =
          this.openedEditType === "1" || this.openedEditType === "-1"
            ? this.infoContent(
                this.basicInfo[this.openedEditIndex],
                this.openedEditIndex
              )
            : this.basicInfo[this.openedEditIndex].title;
        this.basicInfo[this.openedEditIndex].isEdit = false;
        document.removeEventListener("click", this.clickOutsideAccount);
      }
    }
  },
  beforeDestroy() {
    document.removeEventListener("click", this.clickOutsideAccount);
  }
};
</script>
<style lang="scss" >
.account-info {
  height: 100%;
  overflow: hidden;
  box-sizing: border-box;
  display: flex;
  flex-direction: column;
  flex: 1;
  .content-account {
    .v-lists {
      min-width: 300px;
      max-width: 355px;
      .v-lists-content { 
        padding-top: 15px;
        overflow-y: auto;
        &:hover {
          &::-webkit-scrollbar-thumb {
            background-color: #d8d8d885;
          }
        }
        &::-webkit-scrollbar-thumb {
          background-color: rgba(0, 0, 0, 0);
          &:hover {
            background-color: #a8a7a7;
          }
        }
        .v-divder{
          display: none !important;
        }
      }
    }
    height: 100%;
    overflow-y: auto;
    background: $--color-white;
    color: get-grey-color(base);
    font-size: $--font-size-mid;
    padding: 15px;
    display: flex;
    justify-content: center;
    align-items: center;
    border-radius: $--border-radius-base;
    &::-webkit-scrollbar {
      display: none;
    }
    .edit-info-title {
      padding: 10px 0px 5px 15px;
      //color: rgb(129,126,121);
      color: rgba(0, 0, 0, 0.38);
      font-size: 13px;
    }
    .edit-info-item {
      padding: 5px;
      display: flex;
      justify-content: flex-start;
      .right,
      .left {
        width: 40px;
        height: 45px;
        display: flex;
        justify-content: center;
        align-items: center;
        .icon {
          font-size: 22px;
          transition: 0.3s;
          color: rgba(0, 0, 0, 0.38);
        }
        .loading-start {
          font-size: 16px;
          color: red;
          animation: suerSettLoading 0.7s linear infinite;
          transform-origin: 12px 11px;
        }
        .loading-success {
          color: #388e3c;
        }
      }
      .left {
        padding-top: 20px;
      }
      .info-item-content {
        display: inline;
        padding: 5px 5px;
        // display: flex;
        // flex-direction: column;
        position: relative;
        .content-title {
          display: inline;
          color: rgba(0, 0, 0, 0.38);
          // icon {
          //   font-size: 15px;
          // }
        }
        .content-data {
          display: inline;
          padding-left: 10px; 
          align-self: flex-start;
          overflow: hidden;
          white-space: nowrap;
          text-overflow: ellipsis;
          position: relative;
          .scale-xe678 {
            transform: rotate(180deg);
            transform-origin: 12px 12px;
          }
          .icon {
            font-size: 22px;
            transition: 0.3s;
            color: rgba(0, 0, 0, 0.38);
            position: absolute;
            top: 0px;
            right: 0px;
          }
        }
        .tip-msg {
          color: get-grey-color(lighten-1);
          height: 24px;
        }
        .edit-style {
          outline: none;
          text-overflow: clip;
          // border: 1px solid rgba(0, 0, 0, 0.12);
        }
        .gender-list {
          z-index: 999;
          width: 170px;
          left: 0;
          box-shadow: 1px 2px 10px #888888;
          &:hover {
            z-index: 999;
          }
        }
      }
    }
    .modal {
      @include z-index(modal);
      .modal-style {
        border-radius: $--border-radius-base;
        display: flex;
        flex-direction: column;
      }
    }
  }
}
</style>
