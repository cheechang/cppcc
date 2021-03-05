<template>
  <div class="update-remark">
    <p class="nick-name">{{$t('groups.name')}}</p>
    <input class="input is-primary remark-input" size="is-small" maxlength="20" type="text" :disabled="!isGroupLeader" v-model="currentNickName" @keyup.enter="modifyRemark" @blur="modifyRemark">
    <div class="suer-sett-loading" :style="{visibility:isEditLoading?'visible':'hidden'}">
      <i class="icon loading-start" v-if="!isEditFinished">&#xe6ac;</i>
      <i class="icon loading-success" v-else>&#xe632;</i>
    </div>
  </div>
</template>
<script>
import { mapGetters } from 'vuex'
export default {
  props: {
    isGroupLeader: Number|String,
    id: String
  },
  data() {
    return {
      isEditLoading: false,
      isEditFinished: false,
      currentNickName: ''
    }
  },
  computed: {
    ...mapGetters(['contact_groupList', 'user_account'])
  },
  created() {
    this.currentNickName = this.contact_groupList[this.id].groupName;
  },
  methods: {
    modifyRemark() {
      this.currentNickName = this.currentNickName.trim();
      if (!this.currentNickName ||  this.contact_groupList[this.id].groupName == this.currentNickName){
        this.currentNickName = this.contact_groupList[this.id].groupName;
        return
      }
      this.contact_groupList[this.id].groupName = this.currentNickName
      this.isEditLoading = true
      let setGroupInfoParam = {
        groupId: this.contact_groupList[this.id].groupId,
        groupName: this.currentNickName
      };
      this.$Service.group.setGroupInfo(setGroupInfoParam, resp => {
        console.log('setGroup result:', resp);
        if (resp.code === 0) {
          this.isEditFinished = true
          setTimeout(() => {
            this.isEditFinished = false
            this.isEditLoading = false
          }, 1500)
        }
      })
    }
  }
}
</script>
<style lang="scss">
.update-remark {
  width: 100%;
  display: flex;
  align-items: center;
  justify-content: center;
  .nick-name {
    flex: 1;
    display: flex;
    align-items: center;
  }
  .remark-input {
    color: $--color-text-primary;
    font-family: inherit;
    outline: none;
    border: 1px solid $--border-color-grey;
    border-radius: $--border-radius-base;
    height: 24px;
    box-sizing: border-box;
    font-size: 13px;
    flex: 2;
    display: flex;
    align-items: center;
  }
  .suer-sett-loading {
    margin: 0 2px;
  }
}
</style>
