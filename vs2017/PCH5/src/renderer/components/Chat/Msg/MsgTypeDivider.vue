<template>
  <div class="type-divider">
    <div class="divider-content">
      <div>超过48小时未查看群内新消息的人员有：</div>
      <span v-for="(item, index) in dividerList" :key="item.id">
        <span class="divider-name" @click="openMemberDetail(item)">{{getDividerName(item, index)}}</span>
      </span>
    </div>
    <divider-info v-if='isShowDividerInfo' @close="closeDividerCard"></divider-info>
  </div>
</template>

<script>
import { mapGetters } from 'vuex'
import DividerInfo from '../../Group/ChatGroupInfo/ChatMemberInfo.vue';
export default {
  props: {
    message: Object,
    id: String
  },
  computed: {
    ...mapGetters(['chat_objectInfo', 'contact_contactList'])
  },
  components: {
    DividerInfo
  },
  data() {
    return {
      dividerList: [],
      isShowDividerInfo: false
    }
  },
  created() {
    console.log('msgtypedivider:::::', this.message)
    if (this.message.flag === 1) {
      this.message.flag = 0
      this.sendDividerMsg()
    }
    this.getDividerList()
  },
  methods: {
    closeDividerCard() {
      console.log('closeDividerCard::::::::::::::::::::::::')
      this.isShowDividerInfo=false
    },
    // 过滤群成员中的潜水者
    getDividerList() {
      // body返回字符串数组id
      let body = JSON.parse(this.message.messageObject.body)
      if (!body) return
      this.dividerList =  _.filter(this.chat_objectInfo[this.id], (element, index) => {
        return body.includes(element.id)
      })
    },
    getDividerName(item, index) {
      return item.name + (index === this.dividerList.length - 1 ? '': '，')
    },
    // 查看潜水者详情资料信息
    openMemberDetail(item) {
      this.isShowDividerInfo = true
      this.$nextTick(() => {
        let memberInfo = this.contact_contactList[item.id]
        console.log(item.id, this.contact_contactList)
        console.log('memberInfo::::', memberInfo)
        if (memberInfo) {
          this.$signalMonitor.$emit('expendChatMemberInfo', memberInfo);
        } else {
          let getUserInfoParam = { userId: item.id }
          let getUserInfoCb = successRes => {
            console.log('successRes::::', successRes)
            memberInfo = successRes.users;
            this.$signalMonitor.$emit('expendChatMemberInfo', memberInfo);
          }
          this.$Service.search.getUserInfo(getUserInfoParam, getUserInfoCb)
        } 
      })
    },
    sendDividerMsg() {
      this.$Service.chat.sendMessage(this.message.messageObject, resp => {
        this.$Service.log(`sendDividerMsg code::: ${resp.code}`)
      });
    }
  }
}
</script>

<style lang="scss">
.type-divider {
  padding: 6px 10px;
  user-select: text;
  font-size: 0.85rem;
  font-weight: 500;
  letter-spacing: 0.5px;
  max-width: 400px;
  word-break: break-word;
  .divider-content {
    text-overflow: -o-ellipsis-lastline;
    overflow: hidden;
    text-overflow: ellipsis;
    display: -webkit-box;
    -webkit-line-clamp: 2;
    line-clamp: 2;
    -webkit-box-orient: vertical;
    .divider-name {
      cursor: pointer;
      &:hover {
        color: darkorange;
      }
    }
  }
}
</style>