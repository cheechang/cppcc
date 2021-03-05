const {regServersMsg,sendMsg,encryStr} = require('./transport')
const {app} = require('electron')
const pkg = require('../../../../package.json')
import { resolve } from 'path'
export class MutipleServers{
    constructor(mainWin,subwins,trayWin){
       // myKey:我的标识，登录成功前为进程id，登录成功或为userId@server
       this.myKey = process.pid;
       this.mainWin = mainWin;
       this.trayWin = trayWin; 
       this.subwins = subwins;
       this.childServerKey = null;
       this.loginResultCb = null;
       this.isMainServer = true;
       this._verifyImgCodeCb = null; //获取验证码的回调函数
       this.regMsg();
    }
    /*
     * 设置我的标识,用于判定广播消息是否是给我的
     * userId 当前登录的用户id
     * server 当前登录的服务器
     */
    setMykey(key){
        this.myKey = key;
    }
    getAppPath(){
      if(process.platform === 'darwin'){
        return `${resolve(__dirname, `../../MacOS/${pkg.productName}`)}`
      }
      else{
        //return `${resolve(__dirname, `../../${pkg.productName}`)}`;
        return'E:/2019-VRV/Linkdood/bin/win-ia32-unpacked/Linkdood'
      }
    }
    /*
     * 请求子服务器进行登录
     * code 登录返回值
     * loginParam 登录传参{server：xxxx, account:xxxx,pwd:xxxx,userType:xxxx}
     * receiverKey 接收登录结果的主服务器标识 格式为userId@server
     */
    serverLogin(loginParam,cb){
        this.loginResultCb = cb;
        if(this.childServerKey){
            //子客户端已经存在，进行子服务器的登录
            let msg = {
                type:1,
                loginParam:loginParam,
                senderKey:this.myKey,
                receiverKey:[this.childServerKey]
            }
            sendMsg(msg);
        }
        else{
            //启动新的客户端进行子服务器的登录
            let param = Object.assign({},loginParam);
            param.senderKey = this.myKey;
            let msg = encryStr(JSON.stringify(param))
            let startParam={
                startParam:`serversLogin${msg}`,
                path:this.getAppPath()
            }
            console.log('startParam:',startParam);
            global.service.config.launchOtherApp(startParam);
        }
    }
    /*
     * 发送登录的结果
     * code 登录返回值
     * receiverKey 接收登录结果的主服务器标识 格式为userId@server
     */
    postLoginResult(code,senderKey){
        if(this.isMainServer){
          this.isMainServer = false;
        }
        let msg = {
            type:2,
            code:code,
            receiverKey:[global.serversLoginParam.senderKey]
        }
        if(code === 0 ){ //登录成功了
            this.myKey = senderKey;
            global.serversLoginParam = null;
        }
        msg.senderKey = this.myKey;
        sendMsg(msg);
    }
    /*
     * 切换到子服务器
     * receiverKey 切入的子服务器标识 格式为userId@server
     */
    switchToServer(receiverKey,serverInfos){
        this.isMainServer = false;
        this.trayWin.switchToOhter();
        let msg = {
            type:3,
            senderKey:this.myKey,
            receiverKey:[receiverKey],
            serverInfos:JSON.parse(serverInfos)
        }
        sendMsg(msg);
    }
    /*
     * 退出或删除子服务器
     * serverInfos 子服务器标识数组 格式为[userId@server,userId1@server1]
     */
    exitChildServer(serverInfos){
        console.log('serverInfos:',serverInfos);
        let msg = {
            type:4,
            senderKey:this.myKey,
        }
        if(serverInfos){
            msg.receiverKey = serverInfos;
            if(this.childServerKey){
                msg.receiverKey.push(this.childServerKey);
            }
        }
        else{
            if(!this.childServerKey){
               return;
            }
            msg.receiverKey = [this.childServerKey];
            this.childServerKey = null;
        }
        sendMsg(msg);
    }
    // 本服务器收到新消息需要告知其他服务器
    newMsgToServers(){
        let msg = {
            type:5,
            senderKey:this.myKey,
            receiverKey:[],
            subType:1,
        }
        sendMsg(msg);
    }
    // 本服务器需要注销(手机端控制下线) serverInfos:其他在线的服务集合
    haveToExitServer(serverInfos){
      if(this.isMainServer){
        this.exitChildServer(serverInfos);
        return;
      }
      let msg = {
          type:5,
          senderKey:this.myKey,
          receiverKey:[],
          subType:2,
      }
      sendMsg(msg);
    }
    // 请求登录验证码(主服务--->子服务)
    verifyImgCode(param,cb){
      this._verifyImgCodeCb = cb;
      let msg = {
        type:6,
        subType:1,
        param:param,
        senderKey:this.myKey,
        receiverKey:[this.childServerKey]
      }
      sendMsg(msg);
    }
    //返回获取的验证码(子服务--->主服务)
    postVerifyImgCodeResult(param){
      let msg = {
        type:6,
        subType:2,
        param:param,
        receiverKey:[global.serversLoginParam.senderKey],
        senderKey:this.myKey
      }
      sendMsg(msg);
    }
    // 注册接收到的消息
    regMsg(){
        regServersMsg(resp=>{
            global.service.log(`this.myKey:${this.myKey}`);
            if(resp.receiverKey.indexOf(this.myKey)<0 && (resp.type !==5)){
                //过滤掉不是发给自己的消息
                return;
            }
            this._handleMsg(resp);
        })
    }
    _handleMsg(resp){
        switch(resp.type){
            case 1:{
                //请求登录
                this.mainWin._window.webContents.send('serversLogin',resp.loginParam)
                break;
            }
            case 2:{
                //子服务器登录返回
                if(resp.code === 0){
                    this.childServerKey = null;
                }
                else{
                    this.childServerKey = resp.senderKey;
                }
                this.loginResultCb(resp);
                break;
            }
            case 3:{
                //切入当前服务器
                global.service.log(`切入当前服务器:${JSON.stringify(resp)}`);
                this.isMainServer = true;
                this.trayWin.switchToCurrent();
                this.mainWin._window.webContents.send('switchToServer',resp)
                break;
            }
            case 4:{
                //退出
                app.quit();
                break;
            }
            case 5:{
                //其他服务有新消息
                if(this.isMainServer){
                  this.mainWin._window.webContents.send('multipleServersNewMsg',resp)
                }
                break;
            }
            case 6:{
              //获取登录验证码
              if(resp.subType === 1){
                global.service.auth.verifyImgCode(resp.param,(verifyImgCodeResp)=>{
                  this.postVerifyImgCodeResult(verifyImgCodeResp);
                })
              }
              //返回登录验证码结果
              else if(resp.subType === 2){
                if(this._verifyImgCodeCb){
                  this._verifyImgCodeCb(resp.param);
                }
              }
              break;
            }
            default:
                break;
        }
    }
}