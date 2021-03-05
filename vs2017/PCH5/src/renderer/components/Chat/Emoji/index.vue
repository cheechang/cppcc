<template>
  <div class="emoji-container">
    <div class="emoji-bar">
      <div class="emoji-dashboard">
        <span v-for="(item, index) in computedEmojiType" :key="index" @click="cutoverType(index)" :style="{background: typeIndex === index?'#fff':''}">
          <img :src="item.img" :title="item.name">
        </span>
      </div>
    </div>
    <ul class="emoji-list"  @mouseleave="emptyEmoji" >
      <li  v-for="(emoji, index) in emojiData"   :key="index">
        <a  href="javascript:;" 
            :key="index" @click="selectItem(emoji)"
            @mouseenter.self.stop="hoverEmoji(emoji)"
            :style="{height: isGif ? '50px':''}"
        >
           <span v-if="!isDynamic" class="emoji-item" :class="'sprite-' + getPureName(emoji)"></span>
           <img class="emoji-dynamic-item" v-if="isGif" :src="emoji.img" alt="">
        </a>
      </li>
    </ul>
    <div v-if="hoverIndex!==''" class="show-emoji-info" :style="{paddingTop: isGif?'6px':''}">
      <i class="emoji-name" v-if="isShowEmojiName">{{hoverIndex}}</i>
      <span v-if="!isGif" :class="'sprite-' + imgs" class="sprite-hover"></span>
    </div>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import { MsgDynamicExp } from '../Msg'
import { encryptionPassword } from '../../../../comm/util'
import config from '../../../../comm/config.js';
// import MsgMxin from '../msgMixin';
import data  from './index.js'
export default {
  name: 'emoji',
  data () {
    return {
      emojiData: data[0],
      hoverIndex: '',
      emojiImgs: '',
      typeIndex: 0,
      emojiType: [
        {
          name: this.$t('chat.default'),
          img: require('vrv-static/resources/images/emoji/default.png')
        },
        {
          name: this.$t('chat.doodEmoji'),
          img: require('vrv-static/resources/images/emoji/dood.png')
        },
        {
          name: this.$t('chat.Sticker'),
          img: require('vrv-static/resources/images/emoji/dynamic.gif'),
          isHidden: this.isHideDynamic
        },
        {
          name: this.$t('chat.Sticker'),
          img: require('vrv-static/resources/images/emoji/dynamic_pig.gif'),
          isHidden: !config.chat.emoji_pig
        }
      ],
      isShowEmojiName: true,
      isGif: false
    }
  },
  props: {
    targetId: String,
    isEncryptMsg: Boolean,
    isHideDynamic: false
  },
  // mixins: [MsgMxin],
  mounted() {
    /** 特殊处理 英文环境下先不显示表情名称 */
     let language = this.$Service.config.getLanguage()
     console.log('language', language)
     if (language === 'en-US') {
      this.isShowEmojiName = false
     }
  },
  methods: {
    getPureName (a) {
      return a.class.replace(/:/g, '')
    },
    selectItem (emoji) {
      console.log(emoji, '查看选择的动态图');
      if (this.isGif) {
        this.$emit('select');
        let msgbase = {
            fromId: this.user_account.userId,
            targetId: this.targetId,
            body: `${emoji.code}`,
            msgType: 19,
            isPrivateMsg: this.isEncryptMsg ? 1 : 0,
            msgId: encryptionPassword()
        };
        let msg = new MsgDynamicExp(msgbase, 1);
        console.log('MsgDynamicExp::::', msg)
        this.$store.dispatch('SET_CHATCONTENT', msg);
      } else {
        this.$emit('select', {src: emoji.code, alt :this.typeIndex === 0 ? emoji.code : emoji.name});
      }
    },
    hoverEmoji(emoji) {
      this.hoverIndex = emoji.name
      if (!this.isGif) {
        this.imgs = this.getPureName(emoji)
      }
    },
    emptyEmoji() {
       this.hoverIndex = '';
       this.imgs = '';
    },
    cutoverType(index) {
      this.typeIndex = index;
      this.emojiData = data[index];
      console.log('data', data)
      console.log('this.emojiData', this.emojiData)
    }
  },
  computed: {
    ...mapGetters(['user_account']),
    emojis () {
       return this.emojiData.TEXT_EMOJI;
    },
    computedEmojiType() {
      return _.filter(this.emojiType, e => !e.isHidden)
    },
    isDynamic() {
      return this.isGif =  this.typeIndex === 2 || this.typeIndex === 3
    }
  }
}
</script>

<style lang="scss" scoped>
 @import './spring.css';

.emoji-container {
  width: 336px;
  height: 228px;
  background: #fff;
  overflow: hidden;
  @include z-index(box);
  
  .emoji-list {
    height: 160px;
    overflow-y: hidden;
    overflow-x: hidden;
    position: relative;
    padding: 7px;
    // border-top: solid 1px #dbdbdb;
    border-bottom: solid 1px $--border-color-grey;
    &:hover{
      overflow-y: auto;
    }
    li {
      padding: 0px;
      a {
        float: left;
        overflow: hidden;
        height: 35px;
        transition: all ease-out .2s;
        border-radius: $--border-radius-base;
        margin: 1px;
        &:hover {
          background-color: map-get($--color-grey, lighten-2);
          border-color: $--border-color-grey;
        }
        span {
          width: 23px;
          height: 23px;
          display: inline-block;
          border: 1px solid transparent;
          cursor: pointer;
        }
        .emoji-dynamic-item{
          width: 50px;
          height: auto;
        }
      }
    }
  }
  .emoji-bar{
    height: 35px;
    display: flex;
    justify-content: space-between;
    background: #eeeeee;
    padding-left: 10px;
    .emoji-dashboard{
      display: flex;
      align-items: center;
      justify-content: flex-start;
      span{
        width: 50px;
        height: 100%;
        cursor: pointer;
        padding: 0 5px;
        position: relative;
        img{
          position: absolute;
          top: 5px;
          right: 14px;
          height: 70%;
        }
        &:hover{
          background: rgb(219, 219, 219);
        }
      }
    }
  }
  .show-emoji-info{
      display: flex;
      align-items: center;
      justify-content: flex-end;
      span{
        width: 21px;
        height: 21px;
      }
      .emoji-name{
        font-style: normal;
        font-size:$--font-size-mid;;
        margin-right: 6px;
      }
  }
}
  
</style>
