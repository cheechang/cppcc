const config = {
  clientConfig:{
    auth:{
      openUnicomAuth:true,//开启联通认证
      openLanguageSet:false,  //开启语言设置
      openForgetPwd:false,    //忘记密码
      openRegister:false,     //注册
      openHighSetting:false,  //高级设置
      openAutoLogin:false,    //自动登录
      openRemeberPwd:true,    //记住密码
      openServerIntro:false,   //开启服务介绍说明
      server: '114.255.32.32', //聊天服务器地址
      webServer:'114.255.32.34', //web服务器地址
      nationCode: '0086',
      isOpenLocalLoginType: true,  //  本地登录类型开关，如果开启，则不再获取服务器配置
      loginTypes: [
        { type: 10, val: '用户名'},
        // { type: 3, val: '邮箱'},
        // { type: 7, val: '账号'}
      ]
    },
    system:{
      openSpecialTheme:false, // 是否开启特殊主题
      disableWebview:false, // 是否禁用加载webview(首页/工作台)
    },
    user:{
      openNickId:true,  //开启显示豆豆号
      openTrayTip:true  //开启消息托盘提醒
    },
    chat:{
      openSendLocationMsg:false, //是否开启发送位置消息
    },
    avatar: {
      male: require('vrv-static/resources/images/contact/icon_head_male@3x.png'),
      female: require('vrv-static/resources/images/contact/icon_head_female@3x.png'),
      unknow: require('vrv-static/resources/images/contact/icon_head_unknow@3x.png'),
      logo: require('vrv-static/resources/images/common/logo.png'),
      app: require('vrv-static/resources/images/auth/app.png'),
      robot: require('vrv-static/resources/images/contact/app_default.png') // 企业号、公众号
    }
  },
  serviceIp: 'https://mediasoup.linkdood.cn:3000',
  defalutAvatar: [
    require('vrv-static/resources/images/contact/icon_head_unknow@3x.png'), // 未知
    require('vrv-static/resources/images/contact/icon_head_male@3x.png'), // 男
    require('vrv-static/resources/images/contact/icon_head_female@3x.png'), // 女
    require('vrv-static/resources/images/contact/app_default.png'), // 企业号、公众号
    require('vrv-static/resources/images/contact/group.png'), // 群
    require('vrv-static/resources/images/common/sys_msg_btn.png'), // 系统消息
    require('vrv-static/resources/images/common/logo.png'), // 默认头像
    require('vrv-static/resources/images/auth/app.png'), // 应用
    require('vrv-static/resources/images/common/mydevice.png'), // 我的设备
  ],
  preLogin: {
    // 默认服务/地区码
    server: '',
    nationCode: '0086'
  },
  auth: {
    isEnableRegistry: 1,
    isEDPRegistry: 0
  },
  account: {
    //是否开启在线状态
    openOnlineStatus: true,
    // 账户扩展信息类型/对应icon
    extendInfoIcon: {
      '1': '&#xe6fa;', // 手机号
      '3': '&#xe68a;', // 邮箱
      '6': '&#xe61b;', // 豆豆号
      '7': '&#xe69a;' // 自定义登录
    },
    localSetting: {
      send_msg_key: 'isSendMsgKey',
      msg_remind: 'isMsgRemind',
      sound_remind: 'isSoundRemind',
      tray_tip: 'isTrayTip',
      online_Remind: 'isOnlineRemind',
      screenshot_key: 'isScreenshotKey',
      top_apps: 'isTopApp',
      media_remind: 'isMediaRemind',
      editBox_mode: 'isEditBoxMode',
      screen_display: 'isScreenDisplay'
    }
  },
  prtSc: {
    osx: 'Shift+Command+X',
    windows: 'Shift+Ctrl+X',
    normal: 'NORMAL',
    hide: 'HIDE'
  },
  restUserConfig: ['send_msg_key', 'screenshot_key', 'screen_display'],
  chat: {
    //是否开启猪表情开关（国际版关闭）
    emoji_pig: false,
    edit: {
      isMode: true,
      mode: [
        {
          key: 'editBox_classic',
          imgPath: '/vrv-static/resources/images/auth/classic.png'
        },
        {
          key: 'editBox_standard',
          imgPath: '/vrv-static/resources/images/auth/standard.png'
        }
      ]
    }
  }
}

export default config