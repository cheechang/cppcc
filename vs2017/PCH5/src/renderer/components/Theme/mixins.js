import { mapGetters } from 'vuex';
export default {
  computed: {
    ...mapGetters(['clientConfig_system']),
  },
  methods: {
    //加载主题
    setTheme() {
      if (this.$is.isWeb()) {
        //  如果是web环境则不执行
        return 'theme-default';
      }
      console.log('this.$initInfo.appVersion:',this.$initInfo.appVersion);
      let themeList = this.$ConfigIni.getConfig({key:'themeList'});
      if(themeList){
        this.$Service.log(`从本地配置中获取的主题列表:::${JSON.stringify(themeList)}`);
        // 已经设置过主题列表
        if(this.clientConfig_system.openSpecialTheme){
          //开启了特殊主题配置
          let themeVersion = this.$ConfigIni.getConfig({key:'themeVersion'});
          console.log('themeVersion:',themeVersion);
          if(this.$initInfo.appVersion !== themeVersion){
            //主题版本和当前配置的特殊主题版本不一致，加载当前配置主题
            themeList.some((element,index)=>{
              if(element === 'theme-special'){
                themeList.splice(index,1);
                return;
              }
            });
            themeList.unshift('theme-special');
            //记录当前配置的主题版本
            this.$ConfigIni.setConfig({key:'themeVersion', value: this.$initInfo.appVersion});
          }
        }
        else{
          if(themeList[0] === 'theme-special'){
            themeList.splice(0,1);
            themeList.push('theme-special');
            this.$ConfigIni.setConfig({key:'themeList', value: themeList});
          }
        }
      }
      else{
        // 未设置过主题列表,获取旧版本设置的数据
        let theme = this.$ConfigIni.getConfig({key:'themeId'});
        if(!theme){
          theme = 'theme-default';
        }
        themeList = [theme];
        if(this.clientConfig_system.openSpecialTheme){
          //配置了特殊主题，加载该主题
          themeList.unshift('theme-special');
          //记录主题的版本
          this.$ConfigIni.setConfig({key:'themeVersion', value: this.$initInfo.appVersion});
        }
        this.$ConfigIni.setConfig({key:'themeList', value: themeList});
      }
      this.$Service.log(`根据配置生成的主题列表:::${JSON.stringify(themeList)}`);
      this.loadTheme(themeList[0]);
      return themeList[0];
    },
    // 主题载入
    loadTheme(key) {
      if (key === 'theme-default' || !key || (key.indexOf('theme') === -1)) {
        return window.document.documentElement.removeAttribute('data-theme')
      }
      window.document.documentElement.setAttribute('data-theme', key)
    },
  }
}