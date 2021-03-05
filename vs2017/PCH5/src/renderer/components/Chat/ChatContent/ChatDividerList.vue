<template>
  <v-modal cardSize="divider-class" @close="$emit('close')">
    <div class="modal-card-head" slot="header-top">
      <p class="modal-card-title">潜水者名单</p>
      <i class="icon" @click="$emit('close')">&#xe603;</i>
    </div>
    <div class="modal-card-section">
      <div class="chat-divider-list">
        <div class="chat-divider-remark">该名单是超过48小时未查看群内新消息的人员</div>
        <v-card-list class="card-list">
          <v-card v-for="item in dividerList" :key="item.id" :title="item.name" @click="handleSelectItem(item)">
            <v-avatar v-if="!readOnly" size='is-small' slot="extra" class="select-bg" :offline="false" :src="getSelectedStatus(item)"/>
            <v-avatar size='is-small' class="avatar-item" :title="item.groupName" :src='item.avatar' :sex="item.gender" :offline="false" shape="round"  slot="leftAvatar"></v-avatar>
          </v-card>
        </v-card-list>
      </div>
    </div>
    <div class="modal-card-foot" slot="footer-bottom" v-if="!readOnly">
      <span class="select-all-area">
        <v-avatar size='is-small' class="select-all" :src='isAllSelected?selectImg:noneImg' :offline="false" @click.native="setAllSelected"></v-avatar>
        {{ !isAllSelected ? '全选' : '取消全选' }}
      </span>
      <v-button  type="is-primary" @click="publishDividerList">发布</v-button>
      <v-button @click="$emit('close')">{{$t('common.cancel')}}</v-button>
    </div>
  </v-modal>
</template>

<script>
import { mapGetters } from 'vuex'
import { MsgDivider } from '../Msg';
import { encryptionPassword } from '../../../../../src/comm/util.js';
export default {
  props: {
    dividerIdListIds: Array,
    id: String,
    readOnly: false
  },
  data() {
    return {
      noneImg: require("vrv-static/resources/images/contact/groupChooseNone.png"),
      selectImg: require("vrv-static/resources/images/contact/groupChooseSelect.png"),
      dividerList: {},
      isAllSelected: true,
      selectedIds: []
    }
  },
  computed: {
    ...mapGetters(['chat_objectInfo', 'user_account', 'chat_chatContent'])
  },
  mounted() {
    // 初始化选中id数组，默认全选
    this.selectedIds = [...this.dividerIdListIds]
    // 获取潜水者
    this.getDividerList()
  },
  methods: {
    /**
     * @breif 根据id过滤群成员中的潜水者
     */
    getDividerList() {
      _.filter(this.chat_objectInfo[this.id], (element, index) => {
        if (this.dividerIdListIds.includes(element.id)) {
          element.selectImg = this.selectImg
          element.noSelectImg = this.noneImg
          this.$set(this.dividerList, element.id, element)
        }
      })
    },
    /**
     * @breif 点击选中/取消选中：1.修改全选状态 2.更新选中id数组
     * @param {Object} item - 当前选中项
     */
    handleSelectItem(item) {
      let index = _.findIndex(this.selectedIds, e => e === item.id)
      if (index !== -1) {
        this.selectedIds.splice(index, 1)
      } else {
        this.selectedIds.push(item.id)
      }
      this.isAllSelected = this.selectedIds.length === this.dividerIdListIds.length
    },
    /**
     * @breif 更新全选状态
     */
    setAllSelected() {
      this.isAllSelected = !this.isAllSelected
      if (!this.isAllSelected) {
        this.selectedIds = []
      } else {
        this.selectedIds = [...this.dividerIdListIds]
      }
    },
    /**
     * @breif 获取每一项选中状态
     * @param {Object} item - 当前选中项
     */
    getSelectedStatus(item) {
      if (!this.selectedIds.includes(item.id)) {
        return item.noSelectImg
      } else {
        return item.selectImg
      }
    },
    /**
     * @breif 发布潜水者名单
     */
    publishDividerList() {
      if (this.selectedIds.length === 0) {
        this.$toast.open({
          message: '请勾选成员',
          type: 'is-danger'
        })
        return
      }
      let msgbase = {
        fromId: this.user_account.userId,
        targetId: this.id,
        localId: new Date().getTime(),
        msgType: 37,
        msgId: encryptionPassword().toString(),
        body: JSON.stringify(this.selectedIds),
        time: new Date().getTime()
      };
      let msgDivider = new MsgDivider(msgbase, 1);
      this.$store.dispatch('SET_CHATCONTENT', msgDivider)
      this.$emit('close')
    }
  }
}
</script>

<style lang="scss">
.divider-class {
  width: 300px;
  height: 450px;
  .modal-card-section {
    .chat-divider-list {
      display: flex;
      flex-direction: column;
      .chat-divider-remark {
        font-size: 14px;
        display: flex;
        align-items: center;
        justify-content: center;
        border-bottom: 1px solid #ccc;
        user-select: text;
        padding: 6px 0;
        margin: 0 20px;
      }
      .card-list {
        margin: 0 10px;
        .default-content {
          display: flex;
          align-items: center;
          height: inherit;
          .media {
            flex: 1;
          }
          .avatar-item {
            width: 30px;
            height: 30px;
          }
          .select-bg {
            width: 20px;
            height: 20px;
            margin-right: 10px;
          }
        }
      }
    }
  }
  .modal-card-head {
    height: 40px;
    width: 100%;
    border-bottom: none;
    font-weight: bold;
    .modal-card-title {
      margin: 0;
      font-size:$--font-size-mid;
    }
    .icon {
      font-size:$--font-size-mid;
      margin-right: -20px;
      height: 40px;
      width: 40px;
      &:hover{
        background: $--color-msg-prompt-danger;
      }
    }
  }
  .modal-card-foot {
    width: 100%;
    border: none;
    display: flex;
    justify-content: flex-end;
    padding: 10px;
    .select-all-area {
      position: absolute;
      left: 18px;
      display: flex;
      align-items: center;
      font-size: 14px;
      .select-all {
        width: 20px;
        height: 20px;
        margin-right: 6px;
      }
    }
    .button {
      width: 70px;
      height: 30px;
    }
  }
}
</style>