<template>
  <div class="v-lists">
    <card-img :img="img" :name="name" :qrcode="qrcode" :isQrcodeLayout="isQrcode" @edit="$emit('edit')" @layout="args=>isQrcode=!args"></card-img>
    <div class="v-lists-content" v-if="!isQrcode">
      <!-- 详情页 头像 开始 -->
      <div class="card-feature">
        <v-button class="is-button" :ripple="false" @mouseenter.native="openDialList" @mouseleave.native="closeDialList">
          <v-avatar class="v-ripple" :title="title" :src="img" :sex="gender" shape="round" @icon-click="$emit('icon-click')"></v-avatar>
          <card-dial-button :isShow="isDialListShow&&dialList" :dialList="dialList" @click="index=>$emit('click-button', index)"></card-dial-button>
        </v-button>
      </div>
      <!-- 详情页 头像 结束 -->
      <!-- 详情内容 循环 开始 -->
      <d-skeleton v-if="!$slots['contact-invisiable']">
        <div v-for="(item, index) in lists" :key="index">
          <!-- 分割线 -->
          <div class="v-divder" v-if="index!==0" v-show="!item.hideItem"></div>
          <!-- 内容插槽 -->
          <slot v-if="$scopedSlots.default" :item="item" :index="index"></slot>
          <!-- 内容主体 -->
          <card-content v-else :item="item" @send="$emit('send')" @icon-click="$emit('icon-click', item)" @check="args=>$emit('check',args)" @update="args=>$emit('update',args)"></card-content>
        </div>
        <card-lists-skeleton slot="skeleton"></card-lists-skeleton>
      </d-skeleton>
      <!-- 详情内容 循环 结束 -->
      <!-- 隐藏详情内容 开始-->
      <slot name="contact-invisiable"></slot>
      <!-- 隐藏详情内容 结束 -->
    </div>
  </div>
</template>
<script>
import CardImg from './CardImg.vue';
import { mapGetters } from 'vuex';
import CardContent from './CardContent.vue';
import CardCorner from './CardCorner.vue';
import CardDialButton from './CardDialButton.vue';
import CardListsSkeleton from './CardListsSkeleton.vue';
export default {
  props: {
    /**
     * lists数据声明：
     * 1.必传：disabled（是否允许操作），hasChecked（是否允许选中），title/content任一（主标题、次标题）
     * 2.选传：icon（card两边的图标）
     * 3.备注：content传入数据结构和lists一致（或者是字符串）
     */
    lists: Array,
    img: String,
    name: String,
    gender: Number,
    /**
     * dialList数据声明：
     * 1.必传：icon（悬浮图标）、tooltip（悬浮图标功能提示）、id（唯一标识：用来定义class）
     * 2.选传：color（悬浮图标背景）、isHidden（默认false，即不隐藏图标）
     * 3.备注：默认id不能改：msg（发送消息）、delete（删除）、edit（编辑）、add（添加）
     */
    dialList: Array,
    qrcode: Object,
    title: String,
  },
  data() {
    return {
      isDialListShow: false,         // 控制显示隐藏
      isDialListShowState:false,     // 控制显示隐藏预状态
      isShowMenu: false,
      isQrcode: false,
      // img: 'https://cdn.vuetifyjs.com/images/lists/ali.png'
      // name: 'zhyang',
      // img1: 'https://cdn.vuetifyjs.com/images/parallax/material.jpg',
      // img: 'C:/workspace/vue/newLinkdood/Linkdood/vrv-static/resources/images/contact/manDefault.png',
      // lists: [
      //   { title:'Mobile',content:lists, icon: {left:'&#xe693;', right:'&#xe672;'}},
      //   { title:'Phone', content:'18592071009', icon: {left:'&#xe608;', right:'&#xe672;'}},
      //   { title:'Email', content:'zhangyang@vrv.mai.com', icon: {left:'&#xe817;'}},
      //   { title:'Address', content:'高新区锦业路', icon: {left:'&#xe622;'}}
      // ]
    }
  },
  components: {
    CardImg,
    CardContent,
    CardCorner,
    CardDialButton,
    CardListsSkeleton
  },
  methods: {
    closeDialList(){
      this.isDialListShowState = false;
      // 防抖处理
      setTimeout(() => {
        this.isDialListShow = this.isDialListShowState;
      }, 250);
    },
    openDialList(){
      this.isDialListShowState = true;
      // 防抖处理
      setTimeout(() => {
         this.isDialListShow = this.isDialListShowState;
      }, 150);
    }
  },
}
</script>
<style lang="scss">
@import './_cardLists.scss';
.v-lists {
  width: 48%;
  display: block;
  background-color: #fff;
  border-color: #fff;
  color: rgba(0,0,0,0.87);
  border-radius: $--border-radius-base;
  min-width: 0;
  max-width: 420px;
  //max-height: 100%;
  position: relative;
  text-decoration: none;
  transition: 0.3s cubic-bezier(0.25, 0.8, 0.5, 1);
  //overflow: hidden;
  .v-lists-content {
    height: 270px;
    overflow-y: hidden;
    list-style-type: none;
    padding: 8px 0 8px;
    transition: 0.3s cubic-bezier(0.25, 0.8, 0.5, 1);
    &:hover {
      overflow-y: overlay;
    }
    .card-feature {
      display: flex;
      align-items: center;
      position: absolute;
      bottom: 245px;
      right: 10px;
      .is-button {
        background: #fff;
        border-radius: $--border-radius-circle;
        padding: 0;
        height: 100%;
        width: 100%;
        @include z-index(btn);
        &:hover {
          .avatar {
            opacity: 0.88;
          }
        }
        .avatar {
          width: 60px;
          height: 60px;
          background: #fff;
        }
      }
    }
    .v-divder {
      margin-left: 48px;
      max-width: calc(100% - 72px);
      display: block;
      flex: 1 1 0px;
      max-width: 100%;
      height: 0px;
      max-height: 0px;
      border: solid;
      border-width: thin 0 0 0;
      transition: inherit;
      border-color: rgba(0,0,0,0.12);
    }
    .media-right {
      align-items: center;
    }
  }
  .media{
    max-width: auto;
    .subtitle{
      justify-content: flex-start;
      .content{
        flex-grow: 1;
        width: auto;
      }
    }
    .media-right{
      margin-left: 0px;
    }
  }
}  
</style>

