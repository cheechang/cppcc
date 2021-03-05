<template>
  <div
    class="theme-container"
    :style="{height: openSkin?boxHeight+'px':'0'}"
  >
    <div class="for-get-height">
      <div class="theme-lists-container">
        <!-- 模块title -->
        <div class="chat-mode-title">
          <i class="icon theme-titlt-icon"></i>
          <span class="chat-mode">{{$t('user.selectTheme')}}:</span>
          <i class="icon close-theme" @click="$emit('close-theme')">&#xe603;</i>
        </div>
        <div class="theme-lists">
          <!-- 上一页按钮 -->
          <div @click="beforImg" class="scrol-skin scrol-skin-left">
            <span>
              <i class="icon">&#xe60e;</i>
            </span>
          </div>
          <!-- 列表区域 -->
          <div class="content-list" ref="contentW">
            <div :style="{width: skinBoxWidth, left: changeBoxPos + 'px'}" class="list-box" ref="skinBoxW">
              <div class="skin-box" v-for="(item,index) in themeThumbImg" :key="index" @click="changeTheme(item.key)">
                <div class="skin-item">
                  <img :src="item.src">
                  <div v-if="0 == index">{{$t('user.restoreDefault')}}</div>
                </div>
              </div>
            </div>
          </div>
          <!-- 下一页按钮 -->
          <div @click="nextImg" class="scrol-skin scrol-skin-right">
            <span>
              <i class="icon">&#xe60e;</i>
            </span>
          </div>
        </div>
      </div>
      <div
        class="other-option"
        v-if="modes.length>1"
      >
        <div class="chat-mode-title">
          <i class="icon mo-bang"></i>
          <span class="chat-mode">{{$t('user.selectEditMode')}}:</span>
        </div>
        <div class="mode-list">
          <div
            class="mode-item"
            v-for="(item, index) in modes"
            :key="index"
            @click="selectMode(item)"
          >
            <img :src="nodeModulesPath+item.imgPath" alt="">
            <span class="lable">{{getModeNameByKey(item.key)}}</span>
            <div class="selsct-tip theme-bgc_font" v-show="user_localConfig.editBox_mode === item.key">{{$t('user.currentSelect')}}</div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>
<script>
import { resolve } from 'path';
import { mapGetters } from 'vuex';
import {setConfig} from '../../../comm/util'
import AccountMixin from './../Account/AccountMixin.js';
// import config from 'vrv-static/data/config.json';
import config from './../../../comm/config.js';
export default {
  mixins: [AccountMixin],
  data() {
    return {
      color: '',
      showSkinListTemp: true,
      skinHeight: 0,
      changeBoxPos: 0,
      themeKeyList:[],
      themeThumbImg: [
        {src: require('vrv-static/resources/images/theme/backgroundImg0.jpg'), key: 'theme-default'},
        {src: require('vrv-static/resources/images/theme/backgroundImgSpecial.jpg'), key: 'theme-special'},
        {src: require('vrv-static/resources/images/theme/backgroundImg1.jpg'), key: 'theme-orange'},
        {src: require('vrv-static/resources/images/theme/backgroundImg2.jpg'), key: 'theme-blue'},
        {src: require('vrv-static/resources/images/theme/backgroundImg3.jpg'), key: 'theme-grey'},
        {src: require('vrv-static/resources/images/theme/backgroundImg4.jpg'), key: 'theme-purple'},
        {src: require('vrv-static/resources/images/theme/backgroundImg5.jpg'), key: 'theme-green'}
      ],
      modes: config.chat.edit.mode,
      boxHeight: 0
    }
  },
  created(){
    this.themeKeyList = this.$ConfigIni.getConfig({key:'themeList'});
    if(!this.clientConfig_system.openSpecialTheme){
      // 关闭了特殊主题
      this.themeThumbImg.splice(1,1)
    }
  },
  computed: {
    ...mapGetters(['user_localConfig','clientConfig_system']),
    // 计算主题列表的宽度
    skinBoxWidth () {
      return (143*this.themeThumbImg.length)+'px'
    },
    nodeModulesPath() {
      return this.$is.isDev
        ?
        (this.$is.isOSX ? `${this.$osxDirPath}/`+'node_modules/' : resolve(__dirname, '../../../../node_modules/', '') )
        :
        __dirname+'/node_modules/';
    },
    listAnimation() {
      this.changeBoxPos = 0;
      return this.openSkin ? 'slideOutX ' : 'slideInX '
    },
  },
  props: {
    openSkin:false
  },
  watch: {
    openSkin(val) {
      if (val) {
        this.changeBoxPos = 0;
        this.boxHeight = Number(document.getElementsByClassName('for-get-height')[0].clientHeight);
      }
    }
  },
  methods: {
    getModeNameByKey(key){
      switch (key) {
        case 'editBox_classic':
        {
          return this.$t('user.classic');    
        }
        case 'editBox_standard':
        {
          return this.$t('user.standard');    
        }
        default:
          return ''
      }
    },
    // 选择会话编辑框模式
    selectMode(item) {
      this.setUserConfigForDatabase(
        this.user_localConfig.isEditBoxMode,
        'editBox_mode',
        item.key,
        'isEditBoxMode'
      )
    },
    // 更改主题
    changeTheme(key) {
      console.log('boxHeight:::', this.user_localConfig);
      this.setDoodTheme(key);
      this.$Service.log(`更改主题入参:::${key}`);
      let tempList = [...this.themeKeyList];
      tempList.some((element,index)=>{
        if(element === key){
          tempList.splice(index,1);
          return;
        }
      })
      tempList.unshift(key);
      this.$ConfigIni.setConfig({key:'themeList', value: tempList});
      this.$signalMonitor.$emit('change-theme', key)
    },

    // 切换到下一组
    nextImg() {
      if(this.$refs.contentW.offsetWidth >= this.$refs.skinBoxW.offsetWidth){
        return;
      } else {
        if(this.changeBoxPos <= -(this.$refs.skinBoxW.offsetWidth-(this.$refs.contentW.offsetWidth))){
          return;
        } else {
          this.changeBoxPos-= this.$refs.contentW.offsetWidth;
        }
      }
    },

    // 切换到上一组
    beforImg() {
      if(this.$refs.contentW.offsetWidth >= this.$refs.skinBoxW.offsetWidth){
        return;
      } else {
        if(this.changeBoxPos > -this.$refs.contentW.offsetWidth){
          return;
        } else {
          this.changeBoxPos+= this.$refs.contentW.offsetWidth;
        }
      }
    }
  }
};
</script>
<style lang="scss" scoped>
.theme-container{
  background: rgba(0, 0, 0, 0.91);
  overflow: hidden;
  transition: height 0.3s;
  width: 100%;
  position: absolute;
  top: 55px;
  left:0; //fit xp
  -webkit-app-region: no-drag;
  box-shadow: $--box-shadow-navbar;
  @include z-index(box);
  .for-get-height{
    width: 100%;
    height: auto;
    position: absolute;
    top: 0;
    .theme-lists-container{
      margin: 15px 0;
      .theme-lists{
        display: flex;
        justify-content: center;
        position: relative;
        height: 70px;
        .scrol-skin{
          width: 75px;
          height: 100%;
          position: absolute;
          @include z-index(navigation);
          
          top:0;
          background: rgba(0, 0, 0, 0);
          display: flex;
          justify-content: center;  
          align-items: center;
          cursor: pointer;
          &:hover{
            background: linear-gradient(-90deg,rgba(255, 255, 255, 0),rgba(0, 0, 0, 0.788));
            span{
              i{
                color:rgba(173, 171, 171, 0.589)
              }
            }
          }
          span{
            i{
              color: rgba(181, 181, 181, 0.44);
              font-size: 40px;
              transition: color 0.3s;
            }
          }
        }
        .scrol-skin-left{
          left:0;
        }
        .scrol-skin-right{
          right:0;
          transform: rotateY(180deg);
        }
        .close-skin{
          width: 30px;
          height:30px;
          padding:2px 3px;
          position: absolute;
          right:10px;
          top: 10px;
          border-radius: $--border-radius-circle;
          background: rgba(247, 247, 247, 0.51);
          i{
            &:hover{
              color:$--color-white;
            }
          }
        }
        .reset-skin{
          position:absolute;
          bottom: 10px;
          left:10px;
          color: get-grey-color(darken-1);
          cursor:pointer;
          font-size: $--font-size-small;
        }
        .content-list{
          display: flex;
          width: 85%;
          height: 100%;
          justify-content: space-between;
          position: relative;
          height: auto;
          overflow: hidden;
          .list-box{
            display: flex;
            justify-content: flex-start;
            position: absolute;
            transition: left 0.5s;
            height: 100%;
          }
          .skin-box{
            margin: 0 10px;
            .skin-item{
              width: 143px;
              position:relative;
              cursor: pointer;
              img{
                width: 143px;
                height: 70px;
                display: block
              }
              div{
                text-align: center;
                padding-top:20px;
                background: rgba(0,0,0,0.5);
                position: absolute;
                height: 100%;
                width: 100%;
                top: 0
              }
            }
          }
        }
      }
    }
    .other-option{
      color: #fff;
      font-size: 14px;
      margin-bottom: 15px; 
      .mode-list{
        display: flex;
        justify-content: space-between;
        width: 85%;
        height: auto;
        margin: 0 auto;
        .mode-item{
          width: 47%;
          height: auto;
          // margin: 0 10px;
          // background: red;
          position: relative;
          background-repeat: no-repeat;
          background-size: cover;
          overflow: hidden;
          cursor: pointer;
          .selsct-tip{
            width: 100px;
            background: red;
            position: absolute;
            text-align: center;
            padding: 0px 0;
            top: 18px;
            right: -22px;
            transform: rotate(45deg);
          }
          img{
            width: 100%;
            height: 100%;
          }
          .lable{
            color: #fff;
            font-size: 14px;
            height: 21px;
            position: absolute;
            top: 5px;
            left: 0;
            padding: 0 5px 0 10px;
            background: #4caf50;
            &::before{
              content: "";
              display: inline-block;
              position: absolute;
              border: 9px solid transparent;
              border-right-width: 6px;
              border-left-width: 2px;
              right: -8px;
              top: 0;
              border-top-color: #4caf50;
              border-left-color: #4caf50;
            }
            &::after{
              content: "";
              display: inline-block;
              position: absolute;
              border: 9px solid transparent;
              border-right-width: 6px;
              border-left-width: 2px;
              right: -8px;
              top: 3px;
              border-bottom-color: #4caf50;
              border-left-color: #4caf50;
            }
          }
        }
      }
      .mode{
        cursor: pointer;
        margin-left: 10px;
      }
    }
  }
  .chat-mode-title{
    color: #fff;
    font-size: 14px;
    margin: 0 26px 10px 26px;
    position: relative;
    .icon{
      width: 20px;
      height: 20px;
      background-repeat: no-repeat;
      background-size: cover;
      background-position: 50%;
    }
    .mo-bang{
      background: url('~vrv-static/resources/images/auth/mobang.png');
      width: 20px;
      height: 20px;
      background-repeat: no-repeat;
      background-size: cover;
      background-position: 50%;
    }
    .theme-titlt-icon{
      background: url('~vrv-static/resources/images/auth/shuazi.png');
      background-repeat: no-repeat;
      background-size: cover;
      background-position: 50%;
    }
    .close-theme{
      position: absolute;
      top: 0;
      right: 0px;
      font-size: 24px;
      &:hover{
        background: $--color-danger
      }
    }
    .chat-mode{
      margin-left: 7px
    }
  }
}
</style>
