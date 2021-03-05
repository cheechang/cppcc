<template>
  <div class="dood-about">
    <div class="about-content">
      <img :src="doodLogo" class="img-style">
      <div class="version-ins" style="color:black">
        <h3 :style="{color: '#323a7b'}">{{$t('window.title')}}</h3>
        <p>{{$t('work.version')}}: &nbsp;&nbsp;V{{$pkg.version}}&nbsp;&nbsp;{{$pkg.checkUpgrade?'beta':''}}
          <!-- 查看版本更新 -->
          <!-- <i class="icon" v-if="showIntro"  :style="{color: '#323a7b'}" :title="$t('work.versionIntro')" @click="openVersionIntro">&#xe692;</i> -->
          <!-- <i class="icon" :style="{color: '#323a7b'}" :title="$t('work.versionIntro')" @click="openVersionIntro">&#xe692;</i> -->
          <!-- <i class="icon" :style="{color: '#323a7b'}" :title="$t('work.versionIntro')" @click="openVersionIntro">&#xe692;</i> -->
        </p>
        <v-button
          :type="`${buttonType}
          is-primary`"
          class="software-update theme-bgc_font"
          @click="update"
          :ripple="false"
        >{{$t('account.checkUpdate')}}</v-button>
      </div>
    </div>
  </div>
</template>
<script>
import { resolve } from 'path';
import {getConfig} from '../../../../../comm/util'
import {isWinXp } from '../../../../../comm/is'

const path = require('path');
export default {
  data() {
    return {
      doodLogo: require('vrv-static/resources/images/common/dou.png'),
      isLoading: false,
      type: isWinXp ?"xplinkdood":"linkWork",
      updateUrl: `http://192.168.139.250/linkdood/${this.type}/`
    };
  },
  created() {
    // this.showIntro= getConfig({key:'language'}) === 'zh-CN';
    this.$signalMonitor.$on('update-finished', this.completeCheck)
    this.$ipc.on('update-not-available', (e,res)=> {
      console.log(res);
      this.completeCheck(res)
    });
  },
  beforeDestroy() {
    this.$signalMonitor.$off('update-finished', this.completeCheck);
  },
  computed:{
    buttonType() {
      return this.isLoading ? "" : "";
    }
  },
  methods: {
    openVersionIntro(){
     this.$ipc.send('new-window', {
        winUrl:'vrv-static/plugins/versionIntro/versionIntro.html', 
        winType:'versionIntro', 
        winTitle:`${this.$t('work.versionIntro')}`,
        shapeType:'normal',
      })
    },
    completeCheck(msg) {
      this.isLoading = false;
      // if (!msg) return;
      this.$toast.open({
        duration: 3000,
        message: msg,
        position: 'is-top',
        type: 'is-success'
      });
    },
    update() {
      this.isLoading = true;
      this.$ipc.send('check-for-update')
      console.log('local updateUrl=>',this.updateUrl)
      // this.$signalMonitor.$emit('check-for-update')
    }
  }
};
</script>
<style lang="scss" scoped>
.dood-about {
  width: 100%;
  height: 100%;
  text-align: center;
  font-size: $--font-size-mid;
  background-color: #fff;
  border-radius: 3px;
  display: flex;
  justify-content: center;
  align-items: center;
  .about-content{
    // height: auto;
    // padding: 85px 0;
    // background: #fff;
    border-radius: $--border-radius-base;
    .img-style{
      width: 200px;
    }
    .version-ins{
      margin-top: 30px;
      h3{
        margin-bottom: 0;
      }
      p{
        padding: 20px 0;
        margin-bottom: 0;
        
      }
    }
    .software-update{
      border-radius: $--border-radius-base;
      cursor: pointer;
      display: inline-block;
      padding: 5px 10px;
      margin: 0 auto;
      @include bg_color($--color-primary, 'normal');
      color: $--color-text-bg;
    }
  }
}

</style>
