<template>
	<div class="various-item cutting-line-after">
    <div class="">{{$t('setting.autoStartTitle')}}：</div>
    <div class="settings-content">
      <v-checkbox v-model="AutoStartStatus" @change="AutoStart">{{$t('setting.autoStart')}}</v-checkbox>
    </div>
	</div>
</template>
<script>
import { mapGetters } from "vuex";
export default {
  data() {
    return {
      AutoStartStatus: false,
      setAutoStartParam: {
        status: true
      }
    };
  },
  created() {
    //获取开机自启动状态
    this.AutoStartStatus = this.$Service.config.getAutoStart(null).status;
    console.log(this.AutoStartStatus);
  },
  methods: {
    //设置开机自动启动
    AutoStart() {
      this.AutoStartStatus?this.setAutoStartParam.status = false:this.setAutoStartParam.status = true
      let result = this.$Service.config.setAutoStart(this.setAutoStartParam);
      this.AutoStartStatus                        // 当前开机启动状态
      ?
      result?this.AutoStartStatus = false : ''    // 当前为启动状态为true:设置成功后修改试图为选中状态
      :
      result?this.AutoStartStatus = true : ''     // 当前为启动状态为false:设置成功后修改试图为未选中状态
    }
  }
};
</script>
