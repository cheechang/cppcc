import Vue from 'vue';
import { mapGetters } from 'vuex';
import axios from 'axios';
import fs from 'fs'

export default {
  methods: {
    getNewVerifyCodeInfo(username,cb){
      let mac = this.$initInfo.macAddress.replace(/:/gi,'');
      const url=`http://${this.$config.clientConfig.auth.webServer}/cppcc-iam-user/api/v1/sign/images/imagecode?deviceType=pc&client_id=mrhcapp&deviceId=${mac}&tid=a7e1ee6f40d6502fabf4878fa0ea2584&userName=${username}`;
      console.log('====url',url)
      axios.get(url,{
        responseType:'arraybuffer'
      })
      .then(response => {
        //将从后台获取的图片流进行转换
        return 'data:image/jpg;base64,' + btoa(
          new Uint8Array(response.data).reduce((data, byte) => data + String.fromCharCode(byte), '')
        );
      }).then(function (data) {
      //接收转换后的Base64图片
        cb(data)
      }).catch(function (err) {
        cb("")
      })
    },
    /**
     * 获取客服电话
     * @param {*} cb 
     */
    getPhone(cb){
      const url=`http://${this.$config.clientConfig.auth.webServer}/cppcc-management/dic/system/telephone`;
      axios.get(url)
      .then(resp => {
          cb(resp.data.data.codeText);
      })
      .catch(err => {
        cb("");
      })
    },
    /**
     * 生成rsa
     * @param {*} param 
     * @param {*} cb 
     */
    makeRSA(param,cb){
      let mac = this.$initInfo.macAddress.replace(/:/gi,'');
      console.log(this.$dbPath,mac);
      let data = {
        tid:'a7e1ee6f40d6502fabf4878fa0ea2584',
        userName:param.user,
        password:param.pwd,
        code:param.code+'',
        deviceId:mac,
        deviceModel:'pc',
        deviceIp:'127.0.0.1'
      };
      console.log('in config',data)
      this.$Service.log(`rsa config:::${JSON.stringify(data)}`);
      let exePath = this.$AppPath.staticPath()+'\\lib\\rsa';
      let infile = this.$AppPath.userCachePath()+"\\"+param.user+'.in';
      fs.writeFileSync(infile,JSON.stringify(data));

      if(!fs.existsSync(exePath+'/getRSA.exe')){
        cb({
          code:-1,
          msg:'认证程序不存在!',
          mac
        });
      }else{
        console.log('exeParam=>',exePath);
        this.$Service.auth._auth.getRSA({
            path:exePath,
            param:infile
          },resp =>{
            let rsa="";
            fs.unlinkSync(infile);
            if(fs.existsSync(infile+'.rsa')){
              rsa = fs.readFileSync(infile+'.rsa');
              fs.unlinkSync(infile+'.rsa');
              this.$Service.log(`new rsa:::${rsa}`);
              cb({
                code:0,
                msg:rsa,
                mac
              });
            }else{
              cb({
                code:-2,
                msg:'生成rsa失败!',
                mac
              });
            }
          })
      }
    },
    /**
     * http POST
     * @param {*} param 
     * @param {*} cb 
     */
    reqPost(param,cb){
      let xhr = new XMLHttpRequest();
      this.$Service.log(`xhr is:::${xhr !== undefined}`);
      xhr.timeout = 5000;
      xhr.onreadystatechange = e =>{
        if(xhr.readyState === 4){
          console.log('onreadystatechange',xhr.responseText)
          cb({
            result:xhr.responseText!== ""?JSON.parse(xhr.responseText):{},
            status:xhr.status
          })
          this.$Service.log(`xhr responseText:::${xhr.responseText}`);
        }
        this.$Service.log(`xhr status:::${xhr.status}`);
      }
      xhr.open('POST', param.url);
      xhr.send(param.postData);
    },
    /**
     * 认证登录
     * @param {*} param 
     * @param {*} cb 
     */
    unicomLogin(param,cb){
        this.makeRSA(param,resp =>{
          if(resp.code == 0){
            let loginMode = "MANUAL";
            if(this.isRemberPass){
              loginMode = 'AUTO';
            }
            let rsa=resp.msg;
            console.log('rsa:',rsa);
            let data = "tid=a7e1ee6f40d6502fabf4878fa0ea2584&client_id=mrhcapp&client_secret=98890563be65564991e223b6eadc5c0a&scope=read&grant_type=password&deviceType=pc&loginType=" + loginMode+"&ciphertext=" + rsa;
            const url = `http://${this.$config.clientConfig.auth.webServer}/cppcc-iam-user/uoauth/token?${data}`;
            const postData = data+rsa;
            this.$Service.log(`postData:::${postData}`);
            this.reqPost({
              url,
              postData
              }
              ,resData => {
                let obj = {
                  code:resData.result.resultCode,
                  msg:resData.result.resultMsg
                }
                this.$Service.log(`resData:::${JSON.stringify(resData)}`);
                if(resData.status === 200){
                  //校验TOKEN
                  this.checkToken({
                    token:resData.result.access_token,
                    mac:resp.mac
                  },cb,resData);
              }else{
                console.log(`status:${resData.status}`)
                switch(resData.status){
                  case 500:{
                    obj.msg = '提示用户服务器错误(500), 请联系管理员!';
                    break;
                  }
                  case 404:{
                    obj.msg = '提示用户服务器错误(404), 请联系管理员!';
                    break;
                  }
                  case 0:{
                    obj.msg = '网络异常，请稍后重试!';
                    break;
                  }
                }
                cb(obj);
              }
              })
          }else{
            cb(resp)
          }
        })
    },
    checkToken(param,cb,resData){
      let postData ="tid=a7e1ee6f40d6502fabf4878fa0ea2584&deviceModel=pc&deviceId=" + param.mac+"&token="+param.token;
      const url = `http://${this.$config.clientConfig.auth.webServer}/cppcc-iam-user/oauth/check_token?${postData}`;
      this.reqPost({
        postData,
        url
      },resp => {
        let mac = this.$initInfo.macAddress.replace(/:/gi,'');
        let config = Object.assign(resData.result,resp.result,{deviceId:mac, deviceModel:'pc'});
        localStorage.setItem('loginInfoPc',JSON.stringify(config))
        if(resp.status === 200){
          cb({
            code:0,
            msg:''
          })
        }else{
          cb({
            code:-1,
            msg:resp.result.resultMsg
          })
        }
      })
    }
  },
};