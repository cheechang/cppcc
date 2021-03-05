<template>
  <div class="app-edit">
    <div class="app-btn-area"  v-click-outside="onClickOutside">
      <div class="app-btn-item" v-for="(item, index) in appMenulist" @click.stop="operaClick(item, index)" :key="index">
        <div class="app-menu-btn" >
          <i v-if='item.sub_menu' class="icon">&#xe66c;</i>
          {{item.name}}
            <transition name="move"> 
             <ul  class="app-sub-menu" v-show="item.sub_menu && subMenuIndex === index">
              <li class="app-sub-menu-list" v-for="(subItem, subIndex) in item.sub_menu" @click.stop="operaClick(subItem, item)" :key="subIndex">
                <span class="sub-menu-list-item">{{subItem.name}}</span>
              </li>
             </ul>
            </transition>
        </div>
      </div>
    </div>
    <div class="switch-edit-model" @click="$emit('changeEditType')">
      <i class="icon">&#xe67b;</i>
    </div>
  </div>
</template>
<script>
import { mapGetters } from 'vuex'
import { MsgTxt } from '../../Msg'
import vClickOutside from '../../v-click-outside/index.js'
export default {
  data() {
    return {
      // appMenulist: [
      //   {key : 'DEVICE_INFO', name: '现场云', name_en:'cloud', type: 'deviceInfo', sub_menu:[{"type":"click","name":"第一期","key":"3033896253430627",sub_menu:[{"type":"click","name":"上的阿斯顿","key":"3033896253430627"},{"type":"click","name":"上的阿斯顿上的阿斯顿","key":"3045161309262713"},{"type":"click","name":"上的阿斯顿上的阿斯顿","key":"3060792776118062"},{"type":"click","name":"上的阿斯顿上的阿斯顿上的阿斯顿","key":"3084901379141673"},{"type":"click","name":"第五期","key":"3133256918864819"}]},{"type":"click","name":"第二期","key":"3045161309262713"},{"type":"click","name":"第三期","key":"3060792776118062"},{"type":"click","name":"第四期","key":"3084901379141673"},{"type":"click","name":"第五期","key":"3133256918864819"}]},
      //   {key : 'DEVICE_INFO', name: '新青年', name_en:'young', type: 'deviceInfo'},
      //   // {key : 'DEVICE_INFO', name: '现场云', name_en:'cloud', type: 'deviceInfo'},
      //   {key : 'DEVICE_INFO', name: '新华矩阵', name_en:'xinhua', type: 'deviceInfo'}
      // ]
      appMenulist: [],
      subMenuIndex: Number
    }
  },
  mounted() {
    this.getAppInfo()
  },
  props: {
    id: String
  },
  /**
   * 点击指令
   * 点击除元素自身外的区域 触发事件
   * 目前用于关闭区域
   */
  directives: {
    clickOutside: vClickOutside.directive
  },
  computed: {
    ...mapGetters(['user_account'])
  },
  methods: {
    onClickOutside() {
      this.subMenuIndex = -1
    },
    getAppInfo() {
      /**
       * 获取应用信息
       * @param {Stirng} appId 目标应用的id
       */
      let getAppInfoParam = { appId: this.id }
      let getAppInfoCb = resp => {
        console.log('getAppInfoCb', resp)
        if (resp.info.appMenus) {
          this.appMenulist = JSON.parse(resp.info.appMenus).menu
        }
      }
      this.$Service.user.getAppInfo(getAppInfoParam, getAppInfoCb)
    },
    operaClick(item, index) {
      if (item.type === 'view') {
        /** 开启子窗口 加载url */
        if (item.sub_menu) {
           this.subMenuIndex = this.subMenuIndex === index ? -1 : index
        } else {
          if (!item.url) return
          this.subMenuIndex = -1
          this.$ipc.send('new-window', {
            winUrl: item.url,
            winType: 'app',
            winTitle: item.name,
            winFrame: false,
            shapeType: 'normal'
          })
        }
      } else if (item.type === 'click') {
        /**
         * 存在子菜单 则展开
         * 不存在 发送消息给公众号 或 订阅号
         */
        if (item.sub_menu) {
          this.subMenuIndex = this.subMenuIndex === index ? -1 : index
        } else {
          this.subMenuIndex = -1
          this.sendMsg(item.key)
        }
      }
    },
    sendMsg(key) {
      let msg = {
        targetId: this.id,
        fromId: this.user_account.userId,
        msgType: 2,
        body: key,
        isRbtMsg: true,
        noStore: 1
      }
      let msgtxt = new MsgTxt(msg, 1)
      console.log('msgtxt::', msgtxt.messageObject)
      this.$Service.chat.sendMessage(msgtxt.messageObject, resp => {
        console.log('sendMessage::', resp)
      })
    }
  }
}
</script>
<style lang="scss" scoped>
.app-edit {
  display: flex;
  height: 60px;
  border-top: solid 1px $--border-color-grey-lighten;
  font-size: $--font-size-mid;
  .app-btn-area {
    flex: 1;
    display: flex;
    .app-btn-item {
      flex: 1;
      height: 100%;
      display: flex;
      justify-content: center;
      align-items: center;
      border-right: solid 1px $--border-color-grey-lighten;
      position: relative;
      color: get-grey-color(darken-1);
      .icon {
        font-size: 10px;
      }
      &:hover {
        cursor: pointer;
        background: $--color-hover;
      }
      .app-sub-menu {
        text-align: start;
        position: absolute;
        bottom: 62px;
        border-radius: $--border-radius-base;
        box-shadow: $--box-shadow-elevation;
        padding: 10px 0px;
        min-width: 100px;

        .app-sub-menu-list {
          height: 36px;
          line-height: 36px;
          .sub-menu-list-item {
            padding: 0px 10px;
            font-size: $--font-size-small;
          }
          &:hover {
            background: $--color-hover;
          }
        }
      }
    }
  }
  .switch-edit-model {
    width: 60px;
    display: flex;
    justify-content: center;
    align-items: center;
    font-size: inherit;
    color: get-grey-color(darken-1);
    &:hover {
      background: $--color-hover;
      color: #000;
    }
  }
  .move-enter-active {
     animation-name: move-in;
     animation-duration: .15s;
  }

  .move-leave-active {
     animation-name: move-out;
     animation-duration: .15s;
  }

  @keyframes move-in {
  0% {
    transform:scaleY(0);
    opacity: 0;	
    transform-origin: 100% 100% 0
  }
  50% {
    transform:scaleY(0.4);	
    opacity: 0.4;	
    transform-origin: 100% 100% 0
  }
  100% {
    transform:scaleY(1);	
    opacity: 1;	
    transform-origin: 100% 100% 0
  }
}
  @keyframes move-out {
    0% {
      transform:scaleY(1);	
      opacity: 1;	
      transform-origin: 100% 100% 0
    }
    50% {
      transform:scaleY(.4);	
      opacity: .2;	
      transform-origin: 100% 100% 0
    }
    100% {
      transform:scaleY(0);	
      opacity: 0;	
      transform-origin: 100% 100% 0
    }
  }
}
</style>
