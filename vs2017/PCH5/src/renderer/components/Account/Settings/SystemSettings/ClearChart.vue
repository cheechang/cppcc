<template>
	<div class="various-item">
		<div class="">{{$t('setting.clearChat')}}：</div>
    <div class="settings-content">
      <div class="clear-chart-btn theme-botton" @click="clearChartInfo">{{$t('setting.clear')}}</div>
    </div>
	</div>
</template>
<script>
import { mapGetters } from "vuex";
export default {
  data() {
    return {

    };
  },
  methods: {
    clearChartInfo() {
      this.$dialog.confirm({
          confirmText: this.$t('common.confirm'),
          cancelText: this.$t('common.cancel'),
          message: this.$t('account.areYouClear'),
          onConfirm: () => {
          this.$store.commit("EMPTY_ALL_DATA_CACHE", null);
          this.$router.replace({ path: '/Chat' })
          this.$toast.open({
            duration: 3000,
            message: this.$t('account.alreadyCleared'),
            position: 'is-top',
            type: 'is-success'
          });
          this.$Service.chat.deleteAllMessage(
            { clearChatList: true },
            resp => {
              if (resp.code === 0) {
                this.$store.commit('EMPTY_ALL_DATA_CACHE')
              }
              console.log(resp, "偏好设置清空聊天记录");
            }
          );
        }
      })
    }
  }
};
</script>
<style lang="scss" scoped>
.settings-content{
  border-bottom: none!important;
}
</style>
