<template>
  <div class="pc-create-group-info">
    <v-modal @close="$emit('close')">
      <!-- 添加background覆盖modal，避免添加/邀请群成员loading时可以进行其他操作 -->
      <div class="group-background" v-if="isLoading"></div>
      <div class="create-group">
        <div class="create-group-left">
          <p class="group-title">{{currentTitle}}</p>
          <v-input class="search-input" v-model="inputSearch" :placeholder="$t('groups.search')" size="is-small" :position="inputSearch==''?'left':'right'" @input="searchFromLocal">
            <i v-if="inputSearch==''" class="icon search-icon" slot="expand">&#xe68c;</i>
            <i v-else class="icon right" slot="expand" @click="clearInput">&#xe650;</i>
          </v-input>
          <div class="search-result-list" v-if="!inputSearch==''">
            <div class="search-background" v-if="!searchContactResult && objectValues(searchOrgResult).length == 0"></div>
            <p class="search-lable" v-if="contact_isInOrg === 1 && searchContactResult">{{$t('contacts.friends')}}</p>
            <div class="result-list" ref="groups" @scroll.passive.stop="loadMoreData">
              <v-card-list>
                <v-card v-for="(item,index) in searchContactResult" :key="index" :title="item.name" @click="changeItemState(item)">
                  <v-avatar size='is-small' :title="item.name" :src='item.thumbAvatar' :sex="item.gender" :offline="false" shape="round"  slot="leftAvatar"></v-avatar>
                  <v-avatar slot="after" class="avatar-bg" :offline="false" shape="round" :src="isSelectItem(item,true)"/>
                </v-card>
              </v-card-list>
            </div>
             <v-card-list>
                <div class="result-list" v-for="(items, title, index) in searchOrgResult" :key="index">
                  <p class="search-lable">{{title||'组织成员'}}</p>
                  <v-card v-for="(item, id) in items" :key="id" :title="item.name" @click="changeItemState(item)">
                    <v-avatar size='is-small' :title="item.name" :src='item.thumbAvatar' :sex="item.gender" :offline="false" shape="round"  slot="leftAvatar"></v-avatar>
                    <v-avatar slot="after" class="avatar-bg" :offline="false" shape="round" :src="isSelectItem(item,true)"/>
                  </v-card>
                </div>
             </v-card-list>
          </div>
          <div class="left-contact-only" v-if="!(this.contact_isInOrg===1)&&inputSearch==''">
            <div class="create-contact-list" ref="groups" @scroll.passive.stop="loadMoreData">
              <v-card-list>
                <v-card v-for="(item,index) in optionalList" :key="index" :title="item.remark||item.name" @click="changeItemState(item)">
                  <v-avatar size='is-small' :title="item.remark||item.name" :src='item.thumbAvatar' :sex="item.gender" :offline="false" shape="round"  slot="leftAvatar"></v-avatar>
                  <v-avatar slot="after" class="avatar-bg" :offline="false" shape="round" :src="isSelectItem(item,true)"/>
                </v-card>
              </v-card-list>
            </div>
          </div>
          <transition name="slide-up" :style="{height: '100%'}" v-if="this.contact_isInOrg===1&&inputSearch==''">
            <v-tabs position="is-centered" class="create-group-tab" v-model="currentTab" size="contact-tab" @change="changeTab">
              <v-tab-item :label="$t('contacts.friends')" class="create-group-items">
                <div class="create-contact-list" ref="groups" @scroll.passive.stop="loadMoreData">
                  <v-card-list>
                    <v-card v-for="(item,index) in optionalList" :key="index" :title="item.remark||item.name" @click="changeItemState(item)">
                      <v-avatar size="is-small" :title="item.remark||item.name" :src="item.thumbAvatar" :sex="item.gender" :offline="false" shape="round" slot="leftAvatar">
                      </v-avatar>
                      <v-avatar
                        slot="after"
                        class="avatar-bg"
                        :offline="false"
                        shape="round"
                        :src="isSelectItem(item,true)"
                      />
                    </v-card>
                  </v-card-list>
                </div>
              </v-tab-item>
              <v-tab-item :label="$t('organizations.organization')" class="create-group-items">
                <org-tab-item
                  :isPullOrgList="isPullOrgList"
                  :isCreateGroup="true"
                  :isSelectItem="isSelectItem"
                  :changeItemState="changeItemState"
                ></org-tab-item>
              </v-tab-item>
            </v-tabs>
          </transition>
        </div>
        <div class="create-group-right">
          <i class="icon" @click="$emit('close')">&#xe603;</i>
          <div class="create-group-name">
            {{`${$t('groups.name')}:`}}
            <v-input
              maxlength="20"
              :placeholder="$t('groups.enterGroupName')"
              v-model="groupName"
              :readonly="isInviteMember"
            ></v-input>
          </div>
          <div class="member-list-area">
            <div class="member-list-title">{{getSelectedNum()}}</div>
            <div class="member-list">
              <v-card-list>
                <v-card v-for="(item,index) in selectRightItem" :key="index" :title="item.remark||item.name">
                  <v-avatar
                    size="is-small"
                    :src="item.thumbAvatar"
                    :sex="item.gender"
                    :title="item.remark||item.name"
                    :offline="false"
                    shape="round"
                    slot="leftAvatar"
                  ></v-avatar>
                  <v-avatar
                    slot="after"
                    class="avatar-bg"
                    :offline="false"
                    shape="round"
                    :src="isSelectItem(item,false)"
                    @icon-click="changeItemState(item)"
                  />
                </v-card>
              </v-card-list>
            </div>
          </div>
          <div class="modal-card-footer" slot="footer-bottom">
            <v-tooltip type="is-danger" :lable="tipLable" :active="tipActive" always>
              <v-button
                :type="`${buttonType} is-primary`"
                :ripple="false"
                :disable="selectMemberIds.length==0||groupName.trim()==''"
                @click.self="handleGroup"
              >{{$t('common.confirm')}}</v-button>
            </v-tooltip>
            <v-button @click="$emit('close'), selectMemberIds=[]">{{$t('common.cancel')}}</v-button>
          </div>
        </div>
      </div>
    </v-modal>
  </div>
</template>
<script>
import { mapGetters } from "vuex";
import ContactMixin from "../Contact/ContactMixin";
import FileMixin from '../Chat/Mixins/FileMixins'
import OrgTabItem from "../Contact/ContactTab/OrgTabItem.vue";
import config from '../../../comm/config.js';
export default {
  mixins: [ContactMixin, FileMixin],
  data() {
    return {
      isLoading: false,
      tipLable: "",
      tipActive: false,
      choosedImg: require("vrv-static/resources/images/contact/groupChoosed.png"),
      noneImg: require("vrv-static/resources/images/contact/groupChooseNone.png"),
      selectImg: require("vrv-static/resources/images/contact/groupChooseSelect.png"),
      deleteImg: require("vrv-static/resources/images/contact/groupChooseDelete.png"),
      manDefault: require("vrv-static/resources/images/contact/manDefault.png"),
      memberCount: 0,
      selectMemberIds: [],
      selectRightItem: [] /** 右侧已选中列表 */,
      currentTitle: this.isInviteMember
        ? this.$t("groups.inviteUser")
        : this.$t("search.createGroup"),
      groupName: "",
      inputSearch: "",
      searchContactResult: null,
      searchOrgResult:{},
      requiredLength: 10,
      totalLength: 0,
      currentTab: 0,
      isPullOrgList: false,
      createGroupId: ''
    };
  },
  props: {
    isInviteMember: true,
    userInfo: Map | Function,
    groupInfo: {
      type: Object,
      default: () => {
        return {
          userId: "",
          groupId: "",
          groupName: ""
        };
      }
    },
    preSelectMemberIds: String
  },
  components: {
    OrgTabItem
  },
  computed: {
    ...mapGetters([
      "contact_contactList",
      "chat_objectInfo",
      "chat_chatList",
      "user_account",
      "contact_isInOrg",
      'user_imgPath'
    ]),
    buttonType() {
      return this.isLoading ? "is-loading" : "";
    },
    /** 左侧可选列表 */
    optionalList() {
      let resultLeftList = [];
      resultLeftList = _.values(this.contact_contactList).filter(
        e => e.id && e.isApp !== 1
      );
      this.totalLength = resultLeftList.length;
      console.log('optionalList',resultLeftList)
      return (
        _.orderBy(resultLeftList, ["pinyin"], ["asc"]).slice(
          0,
          this.requiredLength
        )
      );
    }
  },
  created() {
    this.groupName = this.groupInfo.groupName || this.getDefaultGroupName();
    if(this.preSelectMemberIds){
       this.selectMemberIds.push(this.preSelectMemberIds);
       this.selectRightItem.push(this.contact_contactList[this.preSelectMemberIds])
    } 
    this.memberCount = this.selectMemberIds.length;
    setTimeout(() => {
      if (this.contact_isInOrg !== -1) {
        // 已经存储到vuex
        //this.isLoading = true
      } else {
        // 第一次切换到通讯录
        this.setOrganizationList();
      }
    }, 10);
  },
  watch: {
    inputSearch() {
      if (this.inputSearch !== "") return;
      this.searchOrgResult = {};
      this.searchContactResult= null;
    }
  },
  methods: {
    objectValues(obj) {
       return _.values(obj);
    },
    // 获取组织架构数据
    setOrganizationList() {
      let getVisibleOrgUsersParam = { type: 0, orgId: 0 };
      this.$Service.enterprise.getVisibleOrgUsers(
        getVisibleOrgUsersParam,
        resp => {
          let isShow = resp.orgs && resp.orgs.length !== 0;
          this.$store.commit("SET_ORGTAB_STATUS", isShow ? 1 : 0);
          //this.isLoading = true;
          this.$Service.log(`获取组织架构信息:::是否显示${isShow}:::
          code: ${resp.code}
          orgs: ${resp.orgs && resp.orgs.length}
          users: ${resp.users && resp.users.length}
        `);
        }
      );
    },
    changeTab(value) {
      this.isPullOrgList = false;
      this.$nextTick(() => {
        // 避免重复拉取组织架构数据
        if (value === 1) this.isPullOrgList = true;
      });
    },
    /**
     * 滚动加载更多：避免数据量过大造成的加载卡顿
     */
    loadMoreData() {
      if (this.isScrollToBottom(this.$refs.groups))
        this.requiredLength = this.totalLength.length;
    },
    /**
     * 显示联系人的选中状态：默认/选中/删除按钮
     * @param {Object} id- 用户id
     * @param {Boolean} isLeft- 左侧/右侧默认选中状态不同
     */
    isSelectItem({ id }, isLeft) {
      return isLeft
        ? this.isInGroup({ id }) || id === this.user_account.id ||this.preSelectMemberIds === id
          ? this.choosedImg
          : this.selectMemberIds.indexOf(id) > -1
            ? this.selectImg
            : this.noneImg
        : this.deleteImg;
    },
    getSelectedNum() {
      return `${this.$t("groups.selectedFriend", { value: this.memberCount })}`;
    },
    /**
     * 判断成员是否已在群里面
     */
    isInGroup({ id }) {
      if (this.isInviteMember)
        return this.chat_objectInfo[this.groupInfo.groupId][id];
      return false;
    },
    /**
     * 创建/邀请群验证
     */
    handleGroup() {
      if (this.selectMemberIds.length === 0) {
        this.handleGroupFailed(this.$t("groups.pleaseSelectGM"));
        return;
      }
      if (this.groupName.trim() === "") {
        this.handleGroupFailed(this.$t("groups.pleaseEnterGN"));
        return;
      }
      this.isLoading = true;
      this.createOrInviteGroup(this.isInviteMember);
    },
    /**
     * 创建/邀请群回调
     * @param {Boolean} isInvited- 邀请群成员||创建群
     */
    createOrInviteGroup(isInvited) {
      let params = {};
      if (!isInvited)
        params = {
          level: 1,
          name: this.groupName.trim(),
          members: this.selectMemberIds
        };
      // level:1,临时群2,普通群（限制人数）
      else
        params = {
          groupId: this.groupInfo.groupId,
          members: this.selectMemberIds
        };
      const action = isInvited ? "inviteMember" : "createGroup";
      this.$Service.group[action](params, resp => {
        this.isLoading = false;
        console.log(`${!isInvited ? "创建" : "邀请"}群返回：`, resp);
        if (resp.code !== 0) {
          let errorInfo = this.$t(`ErrorCode.${resp.code}`);
          this.handleGroupFailed(errorInfo);
        } else {
          this.$emit("close");
          // 创建成功直接跳转会话页
          // !isInvited && this.startChat(resp);
          if (!isInvited) {
            this.createGroupId = resp.groupId
            this.startChat(resp)
            console.log('resp', resp)
            this.handleGroupAvatar()
          }
        }
      });
    },
    /**
     * 创建/邀请群失败tooltip提示
     */
    handleGroupFailed(lable) {
      [this.tipLable, this.tipActive] = [lable, true];
      setTimeout(() => {
        this.tipActive = false;
      }, 2000);
    },
    startChat({ groupId }) {
      let serviceTime = this.$Service.user.getServerTimeSync({}) 
      let itemParams = {
        subType: 1,
        msgTime: serviceTime,
        startTime: serviceTime,
        msgType: 2,
        lastMsg: "",
        delSign: "",
        whereFrom: "",
        isTop: 0,
        id: groupId,
        name: this.groupName.trim(),
        chatType: 2,
        thumbAvatar: "",
        gender: 4
      };
      this.$store.commit("PUSH_CHATLIST", itemParams);
      this.$signalMonitor.$emit("toChatPage");
      this.$router.push({
        path: "/ChatRightArea",
        query: { id: itemParams.id, chatType: itemParams.chatType }
      });
    },
    /**
     * 改变选中状态 && 添加删除
     * @param {Object} id- 选中item对应的用户id
     */
    changeItemState(item) {
      if (
        this.isInGroup({ id: item.id }) ||
        item.id === this.user_account.id ||
        item.id === this.preSelectMemberIds
      )
        return;
      if (this.selectMemberIds.indexOf(item.id) > -1) {
        this.selectMemberIds.forEach((element, i) => {
          if (item.id === element) {
            this.selectMemberIds.splice(i, 1);
            this.selectRightItem.splice(i, 1);
          }
        });
      } else {
        this.selectMemberIds.push(item.id);
        this.selectRightItem.push(item);
      }
      this.memberCount = this.selectMemberIds.length;
    },
    /**
     * 默认群名称
     */
    getDefaultGroupName() {
      var today = new Date();
      var yy = today.getFullYear();
      var mm = today.getMonth() + 1;
      if (mm < 10) {
        mm = "0" + mm;
      }
      var dd = today.getDate();
      if (dd < 10) {
        dd = "0" + dd;
      }
      var hh = today.getHours();
      if (hh < 10) {
        hh = "0" + hh;
      }
      var minutes = today.getMinutes();
      if (minutes < 10) {
        minutes = "0" + minutes;
      }
      var seconds = today.getSeconds();
      if (seconds < 10) {
        seconds = "0" + seconds;
      }
      return (
        this.$t("groups.normalGroup") +
        yy +
        mm +
        dd +
        " " +
        hh +
        minutes +
        seconds
      );
    },
    /**
     * 群成员-本地搜索
     */
    searchFromLocal(value) {
      if (!value.trim()) return;
      this.$Service.search.searchFromLocal({ key: value }, resp => {
        console.log("本地搜索", resp);
        this.searchContactResult =
          (resp.users &&
            resp.users.filter(element => {
              return element.id !== this.user_account.userId && element.isUser;
            })) ||
          [];
        if(!this.searchContactResult.length) this.searchContactResult =null;
      });
      console.log('value:',value);
      this.$Service.enterprise.queryEnterpriseUserlist({username:value,pageSize:100},resp=>{
         console.log('企业查找搜索:',resp);
         this.searchOrgResult = {}; // 清空组织架构缓存
         if (resp.total == 0) return;
         _.forEach(resp.users, (element,index)=>{
          _.forEach(_.values(element)[0], (elementUser, i)=>{
            let item={
              id:elementUser.userID,
              thumbAvatar:elementUser.userHead,
              name:elementUser.enName,
              gender:0
            }
            if (!this.searchOrgResult[Object.keys(element)]) {
              this.$set(this.searchOrgResult, Object.keys(element), {})
            }
            this.$set(this.searchOrgResult[Object.keys(element)], item.id, item)
          })
          })
      });
    },
    /**
     * 清空本地搜索输入内容
     */
    clearInput() {
      this.inputSearch = "";
    },

        // * 处理群头像
    handleGroupAvatar() {
      var c = document.createElement('canvas'); //创建一个canvas
      
      var ctx = c.getContext('2d'); //返回一个用于在画布上绘图的2维环境
      c.width = 150; //定义canvas画布的宽度
      
      c.height = 150; //定义canvas画布的高度
      
      ctx.rect(0, 0, c.width, c.height); //画矩形
      
      ctx.fillStyle = '#fff'; //设置矩形颜色
      
      ctx.fill();
      let _this = this
      let maxLength = _this.selectRightItem.length >= 8 ? 8 :  _this.selectRightItem.length
      function drawing(n) {
      let imgSize 
      let a = 0; //初始化需要组合头像的长度
      let b = 0; //初始化需要组合头像的宽度
      _this.selectMemberIds.length + 1 <= 4 ?  imgSize = 75 : imgSize = 50

      switch (_this.selectMemberIds.length + 1) {
          case 2:
            a = n*75
            b = 37.5
          break;
          case 3:
            n === 0 ? (a = 37.5, b = 0) : ( a = (n-1)*75, b = 75)
          break;
          case 4:
            a = n <= 1 ? n*75 : (n-2)*75
            b = n > 1 ? 75 : 0
          break;
          case 5:
          case 6:
            if (n === 0) {
              a = 0
              b = 0
              imgSize = 100
            } else if (n === 1) {
              a = 100
              b = 0
            } else if (n === 2) {
              a = 100
              b = 50
            } else {
              a = (n-3)*50
              b = 100
            }
          break;
          case 7:
            if (n === 0) {
              a = 50
              b = 0
            } else if (n >= 1 && n<4) {
              a = (n-1)*50
              b = 50
            } else {
              a = (n-4)*50
              b = 100
            }
          break;
          case 8:
            if (n === 0) {
              a = 25
              b = 0
            } else if (n === 1) {
              a = 75
              b = 0
            } else if (n > 1 && n<5) {
              a = (n-2)*50
              b = 50
            } else {
              a = (n-5)*50
              b = 100
            }
          break;
          default:
            if(n<=2) {
              a = n*50
              b = 0
            } else if (n>2 && n<=5) {
              a = (n-3)*50
              b = 50
            } else {
              a = (n-6)*50
              b = 100
            }
          break;
        }
        
        console.log('a', n, a, b, maxLength, _this.selectRightItem.length)
        if (n <= maxLength) {
          var img = new Image()

          img.src = n === 0 ? _this.user_account.thumbAvatar : _this.selectRightItem[n-1].thumbAvatar
          
          img.width = imgSize + 'px'
          
          img.height = imgSize + 'px'
          
          img.onload = function() {
            ctx.drawImage(img, a, b, imgSize, imgSize); //在画布上绘制image对象的图片
            drawing(n + 1); //再执行此函数
          }

          img.onerror = function(){
            console.log('_this.selectRightItem[n-1]', _this.selectRightItem[n-1])
            let sex = _this.selectRightItem[n-1].gender || 0
            img.src = config.defalutAvatar[sex]
          }
        } else {
          console.log('c.toDataURL("image/jpg")', c.toDataURL("image/jpg"))
          _this._drawSuccess(c.toDataURL("image/jpg").replace(/^data:image\/\w+;base64,/, ""))
        }
      }
      drawing(0)
    },

    /**
     * @param {*} groupId 群ID
     * @param {*} groupIcon 头像url
     */
    updateGroupAvatar({ thumbJson }) {
      let setGroupInfoParam = {
        groupId: this.createGroupId,
        groupIcon: JSON.parse(thumbJson).files[0].images[1].url
      };
      this.$Service.group.setGroupInfo(setGroupInfoParam, resp => {
          if (resp.code !== 0) {
            this.$Service.log(`set groupAvatar fail   ${resp.code}`)
          } 
        }
      );
    },

    // * 绘制成功
    async _drawSuccess(url) {
      var dataBuffer = new Buffer(url, 'base64');
      let groupAvatar = `${this.user_imgPath}groupAvatar.png`
      console.log('groupAvatar', groupAvatar)
      let result = await this.writeFile(groupAvatar, dataBuffer)
      if (result) {
        // * 上传头像
        this.$Service.file.uploadAvatar({ path: groupAvatar}, resp => {
          if (resp.code !== 0) {
            this.$Service.log(`uploadGroupAvatarError     ${resp.code}`)
          } else {   // * 更新群头像
            this.updateGroupAvatar(resp);
            this.selectMemberIds = []
            this.selectRightItem = []
          }
        });
      } else {
        this.$Service.log(`writeGroupAvatarError`)
      }
    }
  }
};
</script>
<style lang="scss">
.pc-create-group-info {
  .group-background {
    width: 100%;
    height: 100%;
    position: absolute;
    z-index: 9;
  }
  .create-group {
    height: 100%;
    display: flex;
    overflow: hidden;
    .create-group-left {
      width: 240px;
      display: flex;
      flex-direction: column;
      .group-title {
        margin: 5px 0px 0px 10px;
        color: $--color-black;
      }
      .search-input {
        margin-left: 10px;
        margin-top: 15px;
        margin-right: 15px;
        .is-small {
          //border-radius: $--border-radius-large;
          border-radius: 3px;
        }
        .icon {
          pointer-events: all;
          height: 30px;
        }
        .right{
          right: 0px;
        }
      }
      .search-result-list{
        margin-top: 10px;
        overflow-y: auto;
        overflow-x: hidden;
        .search-background{
          width: 150px;
          height: 150px;
          background: url('~vrv-static/resources/images/common/nocontent.png') no-repeat #fff;
          margin-left: 37px;
          margin-top: 100px;
          background-size: contain;
        }
        .search-lable{
          font-size: 12px;
          background: #dcdcdc;
          padding-left: 5px;
          padding-top: 3px;
          color: #000;
          height: 25px
        }
        .result-list{
          .avatar-bg {
            width: 20px;
            height: 20px;
          }
        }
      }
      .left-contact-only{
          flex: 1;
          display: flex;
          flex-direction: column;
          .create-contact-list {
            height: 450px;
            //margin-right: 10px;
            margin-top: 5px;
            overflow-x: hidden;
            .avatar-bg {
              width: 20px;
              height: 20px;
            }
          }
      }
      .create-group-tab {
        //margin-top: 8px;
        flex: 1;
        display: flex;
        flex-direction: column;
        a {
          span {
            font-size: 12px;
          }
        }
        .tab-content {
          height: 420px;
          .create-group-items {
            //overflow: auto;
            width: 100%;
            height: 420px;
            .create-contact-list {
              height: 420px;
              //margin-right: 10px;
              //margin-top: 10px;
              overflow-x: hidden;
              .avatar-bg {
                width: 20px;
                height: 20px;
              }
            }
            .list-title {
              background: #eef4fd;
              font-size: 13px;
              color: $--color-black;
              height: 24px;
              width: 100%;
            }
          }
        }
      }
    }
    .create-group-right {
      margin-left: 10px;
      width: 240px;
      .member-list-area {
        width: 100%;
        height: 415px;
        .member-list-title {
          color: $--color-black;
          width: 100%;
          height: 30px;
          font-size: 13px;
          vertical-align: middle;
          display: table-cell;
        }
        .member-list {
          overflow-x: hidden;
          width: 100%;
          height: 375px;
          .avatar-bg {
            width: 20px;
            height: 20px;
          }
        }
      }
      .modal-card-footer {
        display: flex;
        justify-content: flex-end;
        .button {
          font-size: 14px;
          //border-radius: $--border-radius-large;
          border-radius:3px;
          width: 70px;
          height: 28px;
        }
      }
      .create-group-name {
        width: 100%;
        height: 30px;
        align-items: center;
        margin-top: 43px;
        display: flex;
        flex: 1;
        color: $--color-black;
        @include ellipsis;
        .input {
          font-size: 13px;
          height: 30px;
          margin-left: 5px;
          padding-right: 0px;
        }
      }
      .icon {
        display: flex;
        @include get-grey-color(darken-1);
        font-size: 12px;
        width: 30px;
        height: 30px;
        right: 0px;
        top: 0px;
        position: absolute;
        &:hover {
          background: #8f91b7;
        }
      }
    }
  }
  .modal-card {
    width: 490px;
    height: 535px;
    border-radius: $--border-radius-base;
  }
}
</style>
