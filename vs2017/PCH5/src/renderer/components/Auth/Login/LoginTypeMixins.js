export default {
    methods: {
        parseOauthResp(resp,obj){
            let loginType = [];
            console.log('oauthresp:',resp);
            if(resp.code === 0){
              if(resp.loginTypes.indexOf(0) > -1){
                loginType = Object.assign([],this.getLoginTypeByServer(obj)) ; //加载服务配配置的登录方式
              }
              if(resp.loginTypes.indexOf(94) > -1) {
                let tempObj = {type: 94, val: this.$t(`loginType.94`)};
                loginType.push(tempObj); //加载域登录的登录方式
              }
            }
            else{
              loginType = Object.assign([],this.getLoginTypeByServer(obj)) ; //加载服务配配置的登录方式
            }
            return loginType;
        },
        getLoginTypeByServer(obj){
            let loginTypes = [];
            //  如果开启只获取本地登录类型，则不再获取服务器类型，直接返回
            if (this.$config.clientConfig.auth.isOpenLocalLoginType) {
              return this.$config.clientConfig.auth.loginTypes;
            }
            if ('accounts' in obj && obj.accounts.length > 0) {
              for (let account of obj.accounts) {
                console.log('account: ', account);
                console.log('keys: ', Object.keys(account));
                let type = parseInt(Object.keys(account)[0]);
                let val = account[type];
                let tempObj = {type: type, val: (this.$t(`loginType.${type}`) ===`loginType.${type}`) ? val : (this.$t(`loginType.${type}`) || val)}
                loginTypes.push(tempObj);
              }
              console.log('logintype: ', loginTypes);
            } else {
              loginTypes = this.$config.clientConfig.auth.loginTypes;
            }
            function compare(property){
              return function(a,b){
                let value1 = a[property];
                let value2 = b[property];
                return value1 - value2;
              }
            }
            loginTypes.sort(compare('type'));
            return loginTypes;
        }
    },
  };