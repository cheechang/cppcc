<template>
 <div class="privacy-class">
  <!-- 隐私设置 -->
  <div class="subject">
      {{$t('account.privacy')}}:
      <sett-loading class="sett-loading" v-if="isShowLoadingPrivacy"  :isLoading="isLoadingPrivacy"></sett-loading>
    </div>
    <div class="verification same">
      <v-radio
        v-for="(item, index) in addedLimitList"
        v-model="defaultRadio"
        :key="item.title"
        :index="index"
        :lable="item.title"
        @change="setAddedLimit(item, index)"
      ></v-radio>
    </div>
    <!-- 查找方式 -->
    <!-- <div class="subject cutting-line-before">
      {{$t('account.findWay')}}:
      <sett-loading class="sett-loading" v-if="isShowLoadingFindWay" :isLoading="isLoadingFindWay"></sett-loading>
    </div>
    <div class="found-way same">
      <div class="finded-way-item" v-for="(item, index) in findedWayList" :key="index">
        <v-checkbox v-model="item.status" @change="setFindedWay(item, index)">{{item.title}}</v-checkbox>
      </div>
    </div> -->
    <!-- 邀请入群验证 -->
    <!-- <div class="subject cutting-line-before">
     邀请入群验证:
    </div>
    <div class="same">
     <v-button 
        class="confirm-change" 
       :class="{'theme-botton':true}"
      >功能暂未实现</v-button>
    </div> -->
    <!-- 黑名单 -->
    <!-- <black-list></black-list> -->
 </div>
</template>
<script>
import { mapGetters } from "vuex";
import BlackList from "./BlackList.vue";
import SettLoading from "./SettLoading.vue";
export default {
  data() {
    return {
      fieldName: "",
      addedLimitList: [
        {
          type: 4,
          value: 1,
          title: this.$t("account.needVerification")
        },
        {
          type: 4,
          value: 2,
          title: this.$t("account.blockNewRequests")
        },
        {
          type: 4,
          value: 3,
          title: this.$t("account.noVerificationNeeded")
        }
      ],
      findedWayList: [],
      isShowLoadingPrivacy: false,
      isShowLoadingFindWay: false,
      isLoadingPrivacy: false,
      isLoadingFindWay: false,
      defaultRadio: "",
      lodingTopPosition: "29px"
    };
  },
  computed: {
    ...mapGetters(["user_userFieldName"])
  },
  components: {
    BlackList,
    SettLoading
  },
  created() {
    // 获取被查找方式的状态
    this.getSetting();

    //获取账号设置信息
    this.getPersonalData();
    console.log("fieldName::", this.user_userFieldName);
    this.findedWayList = [
      {
        type: 3,
        flag: 0,
        status: false,
        title: this.user_userFieldName
      },
      {
        type: 4,
        flag: 0,
        status: false,
        title: this.$t("user.phone")
      },
      {
        type: 5,
        flag: 0,
        status: false,
        title: this.$t("user.email")
      }
    ];
  },
  methods: {
    // 获取个人设置项
    getPersonalData() {
      let getPersonalDataParamBC = resp => {
        console.log(resp, "获取个人设置项");
        resp.options.forEach(e => {
          if (e.type == 4) {
            this.defaultRadio = this.addedLimitList[e.val - 1].title;
          }
        });
      };
      this.$Service.user.getPersonalData([4], getPersonalDataParamBC);
    },

    // 获取被查找方式的状态
    getSetting() {
      this.$Service.user.getSetting({ type: 0 }, resp => {
        this.findedWayList[0].status = resp.issearchbybean == 1 ? false : true;
        this.findedWayList[1].status = resp.issearchbyphone == 1 ? false : true;
        this.findedWayList[2].status = resp.issearchbymail == 1 ? false : true;
      });
    },

    // 设置被查找的方式
    setFindedWay(item, index) {
      this.isShowLoadingFindWay = true;
      this.isLoadingFindWay = true;
      let setSettingParam = {
        type: item.type,
        flag: item.status ? 1 : 0
      };
      let setSettingCB = resp => {
        console.log(resp, "设置被查找方式接口返回的状态");
        if (resp.code !== 0) {
          this.findedWayList[index].status = !item.status; // 设置不成功
          this.isShowLoadingFindWay = false;
          this.isLoadingFindWay = false;
        } else {
          this.isLoadingFindWay = false;
          setTimeout(() => {
            this.isShowLoadingFindWay = false;
          }, 1500);
        }
      };
      this.$Service.user.setSetting(setSettingParam, setSettingCB);
    },

    //设置添加好友条件
    setAddedLimit(item, index) {
      this.isShowLoadingPrivacy = true;
      this.isLoadingPrivacy = true;
      let [personalData, setAddedLimitCB] = [
        {
          options: [
            {
              type: item.type,
              val: item.value
            }
          ]
        },
        resp => {
          console.log(resp.code);
          if (resp.code === 0) {
            this.defaultRadio = item.title;
            this.isLoadingPrivacy = false;
            setTimeout(() => {
              this.isShowLoadingPrivacy = false;
            }, 1500);
          } else {
            this.isShowLoadingPrivacy = false;
            this.isLoadingPrivacy = false;
          }
        }
      ];
      console.log(personalData, "隐私设置 > 好友验证方式入参");
      this.$Service.user.setPersonalData(personalData, setAddedLimitCB);
    }
  }
};

</script>
<style lang="scss" scoped>
.privacy-class {
  width: 100%;
  background: #fff;
  padding: 15px;
  font-size: $--font-size-mid;
  padding-top: 15px;
  height: 100%;
  border-radius: $--border-radius-base;
  overflow: hidden;
  &:hover {
    overflow-y: auto;
  }
  &::-webkit-scrollbar {
    display: none;
  }
  .subject {
    div {
      padding-bottom: 5px;
    }
  }
    .same {
    padding-left: 95px;
    div {
      padding: 3px 0;
    }
  }
  .confirm-change {
   height: 30px;
			color: $--color-white;
			width: 100px;
			padding: 5px 10px !important;
			text-align: center;
			border: 0;
   outline: none;
   font-size: $--font-size-mid;
			border-radius: $--border-radius-base;
		}
}

</style>

