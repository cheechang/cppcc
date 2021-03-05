const dialog = require('electron').dialog;
const BrowserWindow = require('electron').BrowserWindow;
import { platform,release } from 'os';
const clipboard = require('electron').clipboard;
const shell = require('electron').shell;
const ipcMain = require('electron').ipcMain;
import { genID } from './../comm/util.js'
import {isOSX} from '../comm/is'
import {
  conversionPinYin
} from '../comm/pinyin';
global.setApHost = host=>{
  global.apHost = host;
}
export default {
  getAccountInfo: param => {
    let content = {};
    console.log(param, '----')
    global.service.user.getAccountInfo(null, resp => {
      console.log(resp);
      content.mUserName = resp.name;
      content.mUserId = resp.id;
      content.mPortraitUrl = resp.thumbAvatarUrl;
      content.nickID = resp.nickId;
      content.phoneNumber = resp.phone;
      content.email = resp.email;
      content.countryCode = resp.area;
      content.serverName = resp.server;
      content.gender = resp.gender;
      if (resp.extend)
        content.extend = (JSON.parse(resp.extend))[0];
      let res = global.service.config.getLoginExData({
        server: resp.server
      });
      if (JSON.parse(res.Orijson).UpURL) {
        content.serverHost = JSON.parse(res.Orijson).UpURL;
      } else {
        content.serverHost = JSON.parse(res.Orijson).serverhost.apHost
      };
      param.success(content);
      console.log('content', content);
    });
  },
  takePhoto: param => {
    //TODO::
    let content = {};
    content.resultCode = 0; //0 成功，-1失败
    content.mPhotoPath = ["http://xxxxxx.jpg"];
    param.success(content);
  },
  getUnreadMessage: param => {
    //TODO::
  },
  sendMessage: param => {
    console.log('sendMessageParam:', param);
    var content = {};
    let msgbase;
    global.service.user.getAccountInfo(null, resp => {
      if (param.type && (param.type === 26 || param.type === 2)) {
        if (param.type === 26) {
          msgbase = {
            fromId: resp.id,
            targetId: param.targetId,
            msgProperties: '',
            msgType: 26,
            relatedUsers: param.toUsers,
            limitRange: param.toUsers,
            title: param.title,
            fields: param.fields,
            content: param.content,
            creator: param.creator,
            titleBGColor: param.titleBGColor,
            titleColor: param.titleColor,
            detailUrl: param.detailUrl,
          };
        } else if (param.type === 2) {
          msgbase = {
            msgType: 2,
            fromId: resp.id,
            targetId: param.targetId.toString(),
            body: param.msgBody
          };
        }
        global.service.chat.sendMessage(msgbase,
          result => {
            if (result.code === 0) {
              msgbase.msgId = result.msgId
              msgbase.time = result.time
              global.postMsgToRender('insertMsgFromDDIO', msgbase);
              content.resultCode = 0;
            } else content.resultCode = -1;

            param.success(content);
          })
      }
      if (param.type && param.type === 6) {
        global.service.chat.sendAppendixMessage({
            msgType: 2,
            fromId: resp.id,
            targetId: param.targetId.toString(),
            filePath: param.msgBody
          },
          result => {
            if (result.code === 0) {
              msgbase.msgId = result.msgId
              msgbase.time = result.time
              global.postMsgToRender('insertMsgFromDDIO', msgbase);
              content.resultCode = 0;
            } else content.resultCode = -1;
            param.success(content);
          })
      }
    });
  },
  portraitUrl: param => {
    //TODO::
  },
  getUserName: param => {
    //TODO::
  },
  getContactList: param => {
    var content = {};
    content.contacts = [];
    global.service.user.getAccountInfo(null, account => {
      global.service.contact.getContactList(null, resp => {
        resp.contacts.forEach((element, i) => {
          if (element.isApp === 2) {
            var contact = {};
            contact.buddyNameInitial = conversionPinYin(element.pinyin);
            contact.serverName = account.server;
            contact.buddyName = element.name;
            contact.buddyID = element.id;
            content.contacts.push(contact);
          }
        });
        param.success(content);
      });
    });

  },
  getLocalFiles: param => {
    var content = {};
    content.mFilePath = [];
    content.mFileName = [];
    dialog.showOpenDialog({
      title: '文件选择',
      properties: ['openFile', 'multiSelections']
    }, files => {
      if (!files) return;
      console.log('files:', files);
      if (files.length > param.size) dialog.showMessageBox({
        title: '提示',
        type: 'warning',
        message: `最多选择${param.size}个文件`
      }, response => {})
      else {
        files.forEach((element, i) => {
          global.service.file.uploadFile({
            localPath: element
          }, resp => {
            console.log('resp', resp);
            if (resp.code === 0) {
              var fileInfo = (JSON.parse(resp.json)).files[0];
              var pathArr = element.split('\\');
              if (pathArr.length > 0) {
                content.mFileName.push(pathArr[pathArr.length - 1]);
              }
              content.mFilePath.push(`${global.apHost}/${fileInfo.url}`);
              if (content.mFilePath.length === files.length) {
                content.resultCode = 0;
                param.success(content);
                console.log('content:', content);
              }
            } else {
              content.resultCode = -1;
              param.success(content);
            }
          }, pro => {})
        })
      }
    })
  },
  getGroupList: param => {
    var content = {};
    content.groupsInfo = [];
    global.service.user.getAccountInfo(null, account => {
      global.service.group.getGroupList(null, resp => {
        resp.groups.forEach((element, i) => {
          var group = {};
          group.groupNameInitial = conversionPinYin(element.pinyin);
          group.serverName = account.server;
          group.groupName = element.groupName;
          group.groupID = element.groupId;
          content.groupsInfo.push(group);
        });
        param.success(content);
      });
    });
  },
  uploadShareImage: param => {
    console.log('uploadShareImage:::', param);
    if (param.size === 1) {
      forEachUploadShareImg(param.urls, param);
      return;
    };
    dialog.showOpenDialog(
      {
        title: '图片选择',
        properties: ['openFile', 'multiSelections'],
        filters: [{
          name: 'Images',
          extensions: ['jpg', 'png', 'gif', 'jpeg', 'webp']
        }],
      },
      files => {
        if (!files) return;
        if (files.length > param.size - param.currentSize) {
          dialog.showMessageBox({
            title: '提示',
            type: 'warning',
            message: `本次最多可选择${param.size - param.currentSize}个图片`
          }, response => {})
        }
        else {
          let tempfiles = [];
          if (param.hasOwnProperty('select')) {
            console.log('files----------', files);
            files.forEach(element => {
              tempfiles.push({
                img: element,
                imgId: genID(8)
              })
            });
            param.select(tempfiles);
          }
          forEachUploadShareImg(tempfiles, param);
        }
      })
  },
  getLocalPhotos: param => {
    var content = {};
    content.mPhotoPath = [];
    content.mThumbPhotoPath = [];
    dialog.showOpenDialog({
      title: '图片选择',
      properties: ['openFile', 'multiSelections'],
      filters: [{
        name: 'Images',
        extensions: ['jpg', 'png', 'gif']
      }],
    }, files => {
      if (!files) return;
      if (files.length > param.size) dialog.showMessageBox({
        title: '提示',
        type: 'warning',
        message: `最多选择${param.size}个图片`
      }, response => {})
      else {
        files.forEach((element, i) => {
          global.service.file.uploadImage({
            thumbimg: element,
            srcimg: element
          }, resp => {
            console.log('resp', resp);
            if (resp.code === 0) {
              var thumbInfo = (JSON.parse(resp.thumbJson)).files[0];
              var srcJson = (JSON.parse(resp.srcJson)).files[0];
              content.mThumbPhotoPath.push(`${global.apHost}/${thumbInfo.url}`);
              content.mPhotoPath.push(`${global.apHost}/${srcJson.url}`);
              if (content.mThumbPhotoPath.length === files.length) {
                content.resultCode = 0;
                param.success(content);
                console.log('content:', content);
              }
            } else {
              content.resultCode = -1;
              param.success(content);
            }
          }, pro => {})
        })
      }
    })
  },
  getPosition: param => {
    //TODO::
  },
  showNavigationBar: param => {
    // BrowserWindow.getFocusedWindow().webContents.browserWindowOptions.frame = param.show;
  },
  getInfoWithSweep: param => {
    //TODO::
  },
  getOrganization: param => {
    var content = {};
    if (!param.orgId)
      param.orgId = 1;
    content.staff = [];
    content.organization = [];
    global.service.enterprise.getVisibleOrgUsers({
      flag: 0,
      type: 0,
      orgId: param.orgId+''
    }, resp => {
      resp.orgs.forEach((element, i) => {
        var org = {};
        org.orgID = element.orgID;
        org.orgName = element.orgName;
        content.organization.push(org);
      });
      resp.users.forEach((element, i) => {
        var user = {};
        user.staffID = element.userID;
        user.staffName = element.enName;
        content.staff.push(user);
      });
      global.service.user.getAccountInfo(null, account => {
        content.serverName = account.name;
        param.success(content);
      });
    });
  },
  closeView: param => {
    console.log('closeView:::DDIO');
    // BrowserWindow.getFocusedWindow() && BrowserWindow.getFocusedWindow().close()
  },
  getLanguage: param => {
    param.success({
      language: 'zh'
    });
  },
  getVersionMark: param => {
    param.success({
      mark: 'comm'
    });
  },
  copyTextToPaste: param => {
    clipboard.writeText(param.url ? param.url : BrowserWindow.getFocusedWindow().webContents.history[0]);
  },
  chatByUserID: param => {
    //TODO::
  },
  getGroupMembers: param => {
    var content = {};
    content.members = [];
    global.service.user.getAccountInfo(null, account => {
      global.service.group.getMemberList({
        groupId: param.groupID.toString()
      }, resp => {
        var members = new Map(resp.members)
        console.log('getMemberList:', members);
        members.forEach((element, i) => {
          var member = {};
          member.memberNameInitial = conversionPinYin(element.pinyin);
          //member.memberNameInitial = '';
          member.serverName = account.server;
          member.memberName = element.remark;
          member.memberID = element.id;
          content.members.push(member);
        });
        content.resultCode = 0;
        param.success(content);
      });
    });
  },
  openFileURL: param => {
    shell.openExternal(param.url);
    param.success({
      resultCode: 0
    });
  },
  openImageURL: param => {
    shell.openExternal(param.url);
    param.success({
      resultCode: 0
    });
  },
  openMsgListView: param => {
    console.log('openMsgListView:',param);
    let routerParam = {index:param.index};
    routerParam.type = 2;
    global.postMsgToRender('jumpRouterFromDDIO', routerParam);//通知主界面跳转路由
    param.success({resultCode:0});
  },
  getClientInfo: param=>{
    console.log('getClientInfo:',param);
    let content = {};
    content.version = global.initInfo.appVersion;
    content.platform = 'pc',
    content.mac = global.initInfo.macAddress;
    content.mark = global.initInfo.mark;
    content.language = global.language === 'zh-CN'?'zh':'en';
    content.deviceBrand = 'pc';
    content.deviceModel = platform();
    content.systemName = platform();
    content.systemVersion = release();
    //content.resultCode = 0; //0 成功，-1失败
    param.success(content);
  },
  openChat: param => {
    console.log('openChat:',param);
    let routerParam = {chatId:param.chatId+''};
    routerParam.type = 1;
    global.postMsgToRender('jumpRouterFromDDIO', routerParam); //通知主界面跳转指定id的会话
    param.success({resultCode:0});
  },
  openChatView: param => {
    console.log('openChatView:',param);
    let routerParam = {chatId:param.chatId+''};
    routerParam.type = 1;
    global.postMsgToRender('jumpRouterFromDDIO', routerParam); //通知主界面跳转指定id的会话
    param.success({resultCode:0});
  },
  // 打开文件或文件位置
  openFilePath:param=>{
    console.log('openFilePath:',param)
    if(!param.hasOwnProperty('path') || !param.path){
      param.path = global.service.config.userFilePath();
    }
    else{
      let sdkPath = global.service.config.rootPath()
      param.path =  param.path.replace(/LinkdoodSDK/g,sdkPath);
    }
    let fileOperateParam = {
      filepath:  !isOSX ? param.path: param.path.replace(/\(/ig, '\\(').replace(/\)/ig, '\\)'), //路径
      type: 7, // 操作类型 0：判断文件或文件夹是否存在 1.创建文件夹 2.删除文件 3.重命名文件
      operType: 1 
    }
    global.service.file.fileOperate(fileOperateParam, resp => {

    })
    param.success({resultCode:0});
  },
  // 打开工作台H5应用
  loadWorkBenchH5:param=>{
    console.log('loadWorkBenchH5:',param);
    let routerParam = {vestAppID:param.vestAppID+''};
    routerParam.type = 3;
    global.postMsgToRender('jumpRouterFromDDIO', routerParam); //通知主界面打开工作台H5应用
    param.success({resultCode:0});
  },
  // 打开推荐好友购买新服务器
  openBuyServerView:param=>{
    console.log('openBuyServerView:',param);
    global.postMsgToRender('jumpRouterFromDDIO', {type:4});
    param.success({resultCode:0});
  },
  // 打开购买自己的新服务 
  openBuyMyServerView:param=>{
    console.log('openBuyMyServerView:',param);
    global.service.contact.queryExtendedField({parentId:68,dicKey:'onlineBuyLink'},resp=>{
      console.log('在线购买地址:',resp);
      if(resp.EnterpriseDictionarys){
        shell.openExternal(resp.EnterpriseDictionarys[0].extend);
      }
    })
    param.success({resultCode:0});
  },
  // 打开信源豆豆相关界面
  openDoodView:param=>{
    console.log('openDoodView:',param);
    switch (param.type) {
      case 1:  //打开邀请好友
      {
        global.postMsgToRender('jumpRouterFromDDIO', {type:5});
        break;
      }
      case 2: //邀请好友购买服务器
      {
        global.postMsgToRender('jumpRouterFromDDIO', {type:4});
        break;
      } 
      case 3: //去购买自己的服务器
      {
        global.service.contact.queryExtendedField({parentId:68,dicKey:'onlineBuyLink'},resp=>{
          console.log('在线购买地址:',resp);
          if(resp.EnterpriseDictionarys&&resp.EnterpriseDictionarys[0].extend){
            shell.openExternal(resp.EnterpriseDictionarys[0].extend);
          }
        })
        break;
      } 
      case 4: //打开聊天界面
      {
        let routerParam = {chatId:param.param.chatId+''};
        routerParam.type = 1;
        global.postMsgToRender('jumpRouterFromDDIO', routerParam); //通知主界面跳转指定id的会话
        break;
      }
      case 5: //切换到最近消息列表
      {
        let routerParam = {index:param.param.index};
        routerParam.type = 2;
        global.postMsgToRender('jumpRouterFromDDIO', routerParam);//通知主界面跳转路由
        break;
      }  
      default:
        break;
    }
    param.success({resultCode:0});
  },
  createGroup: param => {
    var content = {};
    global.service.group.createGroup({
      level: 2,
      name: param.groupName,
      members: param.users.map(String)
    }, resp => {
      content.groupID = resp.groupId;
      content.resultCode = resp.code;
      param.success(content);
    });
  },
  deleteGroup: param => {
    var content = {};
    global.service.group.removeGroup({
      groupId: param.groupId.toString(),
      type: 1
    }, resp => {
      content.resultCode = resp.code;
      param.success(content);
    });
  },
  openAudioCall: param => {
    //TODO::
  },
  openVideoCall: param => {
    //TODO::
  },
  openVideoCallVendor: param => {
    const { vendorType,vendorEntry, userIds, extend  } = param;
    const { subType, roomID, onwerId, groupId, senderId,roomName, startTime, stopTime, mode, desc, selects } = extend;
    global.service.log('SDKService4DDIO::openVideoCallVendor=>>', roomID);
    if(extend && roomID){
      global.service.user.getAccountInfo(null, resp => {
        global.service.rtcplugin.openMeetingUI({
          roomId: roomID,
          userName: resp.name,
          userId: resp.id,
          title: roomName,
          desc: desc,
          groupId: groupId,
          adminId: onwerId,
          startTime:startTime,
          members: selects,
          mode: mode
        });
        param.success({
          resultCode: 0
        });
      });
    }else{
      param.success({
        resultCode: -1
      });
    }
  },
  getOAuthCode: param => {
    //TODO::
  },
  getUserIdMap: param => {
    //TODO::
  },
  callPhone: param => {
    //TODO::
  },
  scanQrCode: param => {
    //TODO::
  },
  shareTo: param => {
    //TODO::
  },
  downloadFile: param => {
    let content={};
    // 获取下载存储的根路径
    let rootPath ='';
    if(param.savePath){
      let sdkPath = global.service.config.rootPath()
      rootPath =  param.savePath.replace(/LinkdoodSDK/g,sdkPath) +'/';
      global.service.file.fileOperate({ filepath: rootPath, type: 1 });
    }
    else{
      rootPath = (param.type === 1 ? global.service.config.userImgPath() : global.service.config.userFilePath());
    }
    // 文件的名称
    let fileName = '';
    if(param.fileName){
      fileName = param.fileName;
    }
    else{
      if(param.url){
        let urls = param.url.split('?')[0];
        let urlsArray = urls.split('/');
        if(urlsArray.length>1){
          fileName = urlsArray[urlsArray.length-1];
        }
        else{
          urlsArray = urls.split('\\');
          fileName = urlsArray[urlsArray.length-1];
        }
      }
    }
    let downloadParam ={
      flag:0,
      localPath: getFullFileName(rootPath,fileName),
      url:param.url
    }
    console.log('downloadParam:',downloadParam)
    global.service.file.downloadExternalFile(downloadParam,
      resp=>{
        console.log('downloadParam:resp',resp) 
        if(resp.code === 0 ){
          content.resultCode = 0;
          content.resultPath = downloadParam.localPath.replace(/\\/g,"\/");
        }
        else{
          content.resultCode = resp.code;
          content.resultPath = "";
        } 
        param.success(content); 
     },pro=>{})
  },
  speech2Text: param => {
    //TODO::
  },
  openExternalUrl: param => {
    shell.openExternal(param.url);
    param.success({
      resultCode: 0
    });
  },
  circleOfFriend: param => {
    let circlePar = {
      reqJson: JSON.stringify(param),
      loginfoPath: ''
    }
    global.service.user.circleOfFriend(circlePar, resp => {
      let json = resp.json;
      json = json.replace(/\d{16,}(?=\s*,|\s*})/g, function(item) {
        return '"' + item + '"';
      });
      try {
        param.success(JSON.parse(json));
      } catch (error) {
        global.service.log(`同事圈字符串解析失败:::${json}`);
        param.success('');
      }
    });
  },
}
function getFullFileName(rootPath,fileName){
  let fullPath = `${rootPath}${fileName}`;
  if(global.service.file.fileOperate({ filepath: fullPath, type: 0 })){
    let fileNameHead = '';
    let fileNameTail = '';
    if(fileName.indexOf('.') === -1){
	    fileNameHead = fileName;
    }
    else{
	    let fileNameArray = fileName.split('.');
	    fileNameTail = fileNameArray.pop();
	    fileNameHead = fileNameArray.join('.');
    }
    for(let i=1;i<1000;++i){
      fullPath = `${rootPath}${fileNameHead}(${i}).${fileNameTail}`;
      if(!global.service.file.fileOperate({ filepath: fullPath, type: 0 })){
        return fullPath;
      }
    }
  }
  else{
    return fullPath;
  }
}
/**
   * @param {Array<string>} files: 图片的本地url
   */
function forEachUploadShareImg(files, param) {
  // var content = {
  //   mPhotoPath: '',
  //   mThumbPhotoPath: ''
  // };
  files.forEach((element, i) => {
    global.service.file.uploadShareImage(
      {thumbimg: element.img, srcimg: element.img},
      resp => {
        console.log('resp', resp);
        if (resp.code === 0) {
          param.success({
            mThumbPhotoPath: JSON.parse(resp.thumbJson).files[0],
            mPhotoPath: JSON.parse(resp.srcJson).files[0],
            resultCode: 0,
            imgId: element.imgId
          });
          // content.mThumbPhotoPath = JSON.parse(resp.thumbJson).files[0];
          // content.mPhotoPath = JSON.parse(resp.srcJson).files[0];
          // content.resultCode = 0;
          // content.imgId = element.imgId;
          // param.success(content);
        } else {
          // content.resultCode = -1;
          param.success({resultCode: -1});
        }
      },
      pro => {
        if (!param.hasOwnProperty('progress')) return
        pro.imgId = element.imgId
        param.progress(pro)
      }
    )
  })
}
