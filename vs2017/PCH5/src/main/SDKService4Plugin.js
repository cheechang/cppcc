import {
  isDev,isWindows
} from '../comm/is';
var request = require('request');
function isJson(str) {
  if (typeof str === 'string') {
    console.log('str:' + str + '!!!');
    try {
      let obj = JSON.parse(str);
      return true;
    } catch (e) {
      console.log('error：' + str + '!!!' + e);
      return false;
    }
  }
}
/**********************************POST***********************************/
function postResponse(url,msg){
  let options = {
    url:url,
    form:msg,
  };
  global.service.log(JSON.stringify(options));
  request(options, function (error, response, body) {
      if (!error && response.statusCode == 200) {
         console.log(body)
      }
  })
}
export default {
  loginState:false,
  /*******************************第三方请求接口*******************************/
  regTheThridPartyMsgCb:()=>{
    global.service.config.regTheThridPartyMsgCb(null,(info)=>{
      //cb(info);
      console.log("regTheThridPartyMsgCb:",info);
      let data = info;
      if(data.type === "wakeUp"){      //唤醒,弹出窗口
        global.postMsgToRender('wakeUp','');
      }
      else if(data.type === "exitLinkdood"){ //退出豆豆
        global.postMsgToRender('exitLinkdood','');
      }      
      else if(data.type === "authRequest"){ //授权登录
        if(isJson(data.body)){
          global.postMsgToRender('thirdParty_authRequest',JSON.parse(data.body));
        }
      }
      else if(data.type === 'uploadFile'){
        if(isJson(data.body)){
          let requestData = JSON.parse(data.body);
          if(!global.callPlugin.loginState){   //豆豆当前未登录
            let responseData = {
              type:2,
              code:-1,
              port:requestData.port,
              fileId:requestData.fileId,
              msg:'not_logged_in'
            }
            console.log('responseData:', responseData);
            global.callPlugin.responseUploadFile(responseData);
            return;
          }
          global.service.file.uploadFile({
            localPath: requestData.localPath
          }, resp => {
            console.log('resp', resp);
            let responseData = {
              type:2,
              code:resp.code,
              port:requestData.port,
              fileId:requestData.fileId,
              json:resp.json
            }
            console.log('responseData:', responseData);
            global.callPlugin.responseUploadFile(responseData);
          }, pro => {
            console.log('pro:', pro);
            let responseData = {
              type:1,
              process:pro.progess,
              port:requestData.port,
              fileId:requestData.fileId
            }
            global.callPlugin.responseUploadFile(responseData);
          })
        }
      }
      else if(data.type === "getLoginState"){
        if(isJson(data.body)){
          let requestData = JSON.parse(data.body);
          if(!global.callPlugin.loginState){
            let responseData = {
              code:-1,
              port:requestData.port,
              loginState:false,
              msg:'not_logged_in',
              accountInfo:''
            }
            console.log('responseData:', responseData);
            global.callPlugin.responseGetLoginState(responseData);
            return;
          }
          else{
            global.service.user.getAccountInfo(null,resp=>{
              let accountInfo = {
                server:resp.server,
                gender:resp.gender,
                name:resp.name,
                thumbAvatar:resp.thumbAvatar,
                phone:resp.phone,
                id:resp.id,
                extends:resp.extends,
                entExtends:resp.entExtends,
              }
              let responseData = {
                code:0,
                port:requestData.port,
                loginState:true,
                msg:'',
                accountInfo:JSON.stringify(accountInfo)
              }
              global.callPlugin.responseGetLoginState(responseData);
            })
          }
        }
      }
      else if(data.type === "sendMessage"){ //发送消息
        //TODO::
      }
      else if(data.type === "regMsgNoticeCb"){ //监听新消息
        //TODO::
      }
      else if(data.type === "login"){ //登录
        //TODO::
      }
    });
  },
  /*******************************响应第三方相关接口*******************************/
  responseStartUp:data=>{
    global.callPlugin.regTheThridPartyMsgCb();
    if(!isDev&&isWindows&&data&&(data.substr(0,4)==='port')){
      let port = data.substr(5);
      postResponse(`http://127.0.0.1:${port}/api/response/startUp`,'{"result":200}')
    }
  },
  responseUploadFile:data=>{
    let port = data.port;
    let info = data;
    delete info.port;
    postResponse(`http://127.0.0.1:${port}/api/response/uploadFile`,JSON.stringify(info))
  },
  responseGetLoginState:data=>{
    let port = data.port;
    let info = data;
    delete info.port;
    postResponse(`http://127.0.0.1:${port}/api/response/getLoginState`,JSON.stringify(info))
},
  responseAuthRequest:data=>{
      let port = data.port;
      let info = data;
      delete info.port;
      postResponse(`http://127.0.0.1:${port}/api/response/authRequest`,JSON.stringify(info))
  },
  sendMsgToTheThirdParty:data=>{
    console.log('sendMsgToTheThirdParty:',data);
    var options = {
      url: 'http://127.0.0.1:7999/api/fun',
      form:data,
    };
    request(options, function (error, response, body) {
        if (!error && response.statusCode == 200) {
           console.log(body)
        }
    })
  }
}
