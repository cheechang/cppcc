import {
    mapGetters
  } from 'vuex';
  const CommonMixin = {
    computed: {
      ...mapGetters(['user_netstat','user_serverstat']),
          // 是否显示离线提示
      showDisconnect() {
        return !this.user_serverstat || !this.user_netstat;
      },
      // 离线提示信息
      disConnectTip() {
        return this.user_serverstat ? this.$t('common.connecting') : this.$t('common.cantConnSer');
      }
    },
  };
  export default CommonMixin;
  