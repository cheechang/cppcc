const activateMixin = {
methods:{
 cancel() {
  this.$Service.auth.logout(null, resps => {
    this.$Service.log(`账号激活:点击登录后弹出手机认证界面，未激活直接关闭弹框调用登出接口返回:${JSON.stringify(resps)}`);
    this.$ipc.send("tray-logout");
  });
  this.$router.push({ path: '/Login'});
},
 }
}
export default activateMixin;