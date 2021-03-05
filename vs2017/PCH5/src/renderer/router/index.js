import Vue from 'vue';
import Router from 'vue-router';
/**
 * 主窗口
 */
import Main from '../components/Main/index.vue';
/**
 * 用户模块
 */
import Auth from '../components/Auth/index.vue';
import PreLogin from '../components/Auth/Login/PreLogin.vue';
import Login from '../components/Auth/Login/LoginPage.vue';
import LoginInitPage from '../components/Auth/Login/LoginInitPage.vue';
import Advanced from '../components/Auth/Advanced.vue';
import PhoneVerify from './../components/Auth/PhoneVerify.vue'

// import Register from '../components/Auth/Register.vue';
import Register from '../components/Auth/Register/index.vue';
import RegisterPage from '../components/Auth/Register/RegisterPage.vue';
import SetAccountPage from '../components/Auth/Register/SetAccountInfoPage.vue';
import PrivacyPolicy from '../components/Auth/RegAgreement/PrivacyPolicy.vue';
import ServiceAgreement from '../components/Auth/RegAgreement/ServiceAgreement.vue';
/*
 * 激活认证模块 
 */
import Activate from './../components/Activate/index.vue'
import ChangePwd from './../components/Activate/ChangePwd.vue'
import Verify from './../components/Activate/Verify.vue'
import VerifyField from './../components/Activate/VerifyField.vue'
/**
 * 会话模块
 */
import Chat from '../components/Chat/index.vue'
import ChatRightArea from '../components/Chat/ChatContent/SessionWinList.vue'
import ChatSystem from '../components/Chat/ChatContent/ChatSystem.vue'
/**
 * 联系人模块
 */
// import Contact from '../components/Contact/index.vue'
import ContactInfo from '../components/Contact/ContactInfo.vue'
import OfficialAccounts from '../components/Contact/OfficialAccounts.vue'
import MyDevice from '../components/Contact/MyDevice.vue'
import EntAppInfo from '../components/Contact/EntAppInfo.vue'
/**
 * 群模块
 */
import CreateGroup from '../components/Group/CreateGroup.vue'
import GroupInfo from '../components/Group/ContactGroupInfo.vue'
import ChatGroupInfo from '../components/Group/ChatGroupInfo/index.vue'
/**
 * 应用模块
 */
import Work from '../components/Work/index.vue'
/**
 * 用户模块
 */
// import Account from '../components/Account/index.vue'
// import personalAccount from '../components/Account/UserInfo/index.vue'
// import SystemSettings from '../components/Account/Settings/SystemSettings/index.vue'
// import SecuritySettings from '../components/Account/Settings/SecuritySettings/SecuritySettings.vue'
// import aboutDood from '../components/Account/Settings/About/About.vue'
/**
 * 音视频
 */
// import ImagePreview from '../subwindow/ImagePreview.vue'
import ScreenShot from '../subwindow/ScreenShot.vue'
import RTCP2P from '../subwindow/RTCP2P.vue'
import RemoteControl from '../subwindow/RemoteControl.vue'
import RtcFile from '../subwindow/RtcFile.vue'
import MultiMeeting from '../subwindow/MultiMeeting.vue'
/**
 * 首页
 */
import HomePage from '../components/Home/index.vue'
/**
 *履职
 */
import Duty from '../components/Duty/index.vue'
/**
 *咨讯
 */
import News from '../components/News/index.vue'
Vue.use(Router)

const pcroutes = [
  {
    path: '/',
    redirect: '/Auth'
  },
  {
    path: '/Auth',
    name: 'Auth',
    label: '登陆',
    icon: 'textsms',
    component: Auth,
    'children': [
      {
        path: '/Prelogin',
        name: 'Prelogin',
        component: PreLogin
      },
      {
        path: '/LoginInitPage',
        name: 'LoginInitPage',
        component: LoginInitPage
      },
      {
        path: '/Login',
        name: 'Login',
        component: Login
      },
      {
        path: '/Register',
        name: 'Register',
        component: Register,
        'children': [
          {
            path: '/first',
            name: 'Register',
            component: RegisterPage
          },
          {
            path: '/second',
            name: 'Register',
            component: SetAccountPage
          }
        ]
      },
     {
      path: '/Advanced',
      name: 'Advanced',
      component: Advanced
      },

    ]
  },
  {
    path: '/Main',
    name: 'Mains',
    label: '主窗口',
    icon: 'textsms',
    component: Main,
    'children': [
      
      {
        path: '/Chat',
        name: 'Chat',
        label: '消息',
        icon: '&#xe601',
        component: Chat,
        'children': [{
            path: '/ChatRightArea',
            name: 'ChatRightArea',
            component: resolve => require(['../components/Chat/ChatContent/SessionWinList.vue'], resolve)
          },
          {
            path: '/ChatSystem',
            name: 'ChatSystem',
            component: resolve => require(['../components/Chat/ChatContent/ChatSystem.vue'], resolve)
          }
        ]
      },
      {
        path: '/Activate',
        name: 'Activate',
        component: Activate,
        'children':[
          {
            path: '/ChangePwd',
            name: 'ChangePwd',
            component: ChangePwd
          },
          {
            path: '/Verify',
            name: 'Verify',
            component: Verify
          },
          {
            path: '/VerifyField',
            name: 'VerifyField',
            component: VerifyField
          },
        ]
      },
      
      {
        path: '/Contact',
        name: 'Contact',
        label: '联系人',
        icon: '&#xe600',
        component: resolve => require(['../components/Contact/index.vue'], resolve),
        'children': [{
            path: '/ContactInfo',
            name: 'ContactInfo',
            component: ContactInfo
          },
          {
            path: '/GroupInfo',
            name: 'GroupInfo',
            component: GroupInfo
          },
          {
            path: '/OfficialAccounts',
            name: 'OfficialAccounts',
            component: OfficialAccounts
          },
          {
            path: '/MyDevice',
            name: 'MyDevice',
            component: MyDevice
          },
          {
            path: '/EntAppInfo',
            name: 'EntAppInfo',
            component: EntAppInfo
          }
        ]
      },
      {
        path: '/work',
        name: 'Work',
        icon: 'toys',
        component: Work,
      },
      {
        path: '/HomePage',
        name: 'HomePage',
        icon: 'toys',
        component: HomePage
      },
      {
        path: '/Duty',
        name: 'Duty',
        icon: 'toys',
        component: Duty
      },
      {
        path: '/News',
        name: 'News',
        icon: 'toys',
        component: News
      },

      // {
      //   path: '/Account',
      //   name: 'Account',
      //   component: Account,
      //   redirect: '/personalAccount',
      //   'children': [
      //    {
      //       path: '/personalAccount',
      //       name: 'personalAccount',
      //       component: personalAccount
      //     },
      //     {
      //       path: '/SystemSettings',
      //       name: 'SystemSettings',
      //       component: SystemSettings
      //     },
      //     {
      //       path: '/SecuritySettings',
      //       name: 'SecuritySettings',
      //       component: SecuritySettings
      //     },
      //     {
      //       path: '/aboutDood',
      //       name: 'aboutDood',
      //       component: aboutDood
      //     }
      //   ]
      // }
      
      
    ]
  },
  {
    path: '/PrivacyPolicy',
    name: 'PrivacyPolicy',
    component: PrivacyPolicy
  },
  {
    path: '/ServiceAgreement',
    name: 'ServiceAgreement',
    component: ServiceAgreement
  },
  // 外部链接
  {
    path: '/ScreenShot',
    name: 'ScreenShot',
    component: ScreenShot
  },
  {
    path: '/RTCP2P',
    name: 'RTCP2P',
    component: RTCP2P
  },
  {
    path: '/RemoteControl',
    name: 'RemoteControl',
    component: RemoteControl
  },
  {
    path: '/RtcFile',
    name: 'RtcFile',
    component: RtcFile
  },
  {
    path: '/MultiMeeting',
    name: 'MultiMeeting',
    component: MultiMeeting
  }
]

export default new Router({
  history: false,
  routes: pcroutes
})
