<template>
	<div class="various-item cutting-line-after">
		<div class="">{{$t('setting.chooseLanguage')}}：</div>
    <div class="settings-content">
      <div class="curr-lang">
        <div class="lang">
          {{currentLang}}
          <i class="icon" @click.self.stop="isShow=!isShow">&#xe77a;</i>
        </div>
        <transition name="zoom-in-top">
          <div
            v-if="isShow"
            class="lang-list"
             v-click-outside="onClickOutside"
          >
            <div
              class="lang-item"
              v-for="(item, index) in langsList"
              :key="index"
              @click="selectItem(item)"
            >{{item.val}}</div>
          </div>
        </transition>
      </div>
    </div>
	</div>
</template>
<script>
const fs = require('fs');
import { mapGetters } from "vuex";
import {getConfig,setConfig} from '../../../../../comm/util'
import mixin from './../../AccountMixin.js';
import List from './../../../Auth/common/list.vue';
import vClickOutside from './../../../Chat/v-click-outside/index';
export default {
  mixins: [mixin],
  components: {List},
  directives: {
    clickOutside: vClickOutside.directive
  },
  data() {
    return {
      isShow: false,
      currentLang: this.$t('setting.followSystem'),
      langsList: [
        {val: this.$t('setting.followSystem'), type: ''},
        {val: '中文', type: 'zh-CN'},
        {val: 'English', type: 'en-US'}
      ]
    };
  },
  created() {
    this.currentLang = this.langsList.filter(e => e.type === getConfig({key:'language'}))[0].val;
    console.log('this.currentLang:::',this.currentLang); 
  },
  methods: {
    selectItem(item) {
      // 关闭列表
      this.isShow = false;
      this.currentLang = item.val;
      this.$ConfigIni.setConfig({key:'language',value:item.type});
      this.errPromptBox(this.$t('setting.chooseLanguageTip'), 'is-success');
    },
    // 点击外部区域关闭列表
    onClickOutside(){
      this.isShow = false;
    }
  }
};
</script>
<style lang="scss" scoped>
.settings-content{
  border-bottom: none!important;
  .curr-lang{
    position: relative;
    width: 140px;
    .lang{
      padding: 5px 0;
      i{margin-left: 10px;}
    }
    .lang-list{
      position: absolute;
      background: #fff;
      top: 35px;
      left: 0;
      @include z-index(none);
      border-radius: $--border-radius-base;
      box-shadow: 0 0 1px #3b3939;
      overflow: hidden;
      .lang-item{
        padding: 5px 15px;
        &:hover {
          background: rgb(45, 117, 250);
          color: $--color-white;
        }
      }
    }
  }
}
</style>
