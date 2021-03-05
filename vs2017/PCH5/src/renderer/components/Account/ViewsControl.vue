<template>
  <div class="views-control">
    <i 
      v-for="(icon, i) in controlList" 
      class="icon" 
      :class="[`icon-${icon.label}`,{'vc-hover-bgc': isVcHoverBgc && i == 3}]"
      :key="i" 
      v-html="icon.icon" 
      v-if="icon.isShow" 
      @click="controlClick(i, icon.label, icon.isShow)"
      ref="vcBtn"
      @mouseenter="i == 3?isVcHoverBgc = true:''"
    ></i>
  </div>
</template>
<script>
export default {
  name: 'views-control',
  data() {
    return {
      isVcHoverBgc: false,
      controlList: [
        { icon: '&#xe612;', label: 'minimize', isShow: true },
        { icon: '&#xe690;', label: 'maximize', isShow: true },
        { icon: '&#xe602;', label: 'unmaximize', isShow: false },
        { icon: '&#xe676;', label: 'close', isShow: true }
      ]
    }
  },
  created() {
    console.log('created...view-control');
    this.$ipc.on('max-state',this.setMaxState)
    this.$ipc.on('unmax-state', this.setUnMaxState)
    // this.$ipc.send('winChangeMax', resps => {
    //   this.$emit('window-size', true);
    //   console.log('winChangeMax');
    //    this.controlList[1].icon = '&#xe602;'
    //    this.controlList[1].label = 'unmaximize'
    // });
    // this.$ipc.send('winChangeUnMax', resps => {
    //   this.$emit('window-size', false);
    //    this.controlList[1].icon = '&#xe628;'
    //    this.controlList[1].label = 'max'
    // });
  },
  beforeDestroy() {
    console.log('beforeDestroy...view-control');
    this.$ipc.removeListener('max-state', this.setMaxState)
    this.$ipc.removeListener('unmax-state', this.setUnMaxState)
  },
  methods:{
    setMaxState() {
      this.controlList[1].isShow = false;
      this.controlList[2].isShow = true;
    },
    setUnMaxState() {
      this.controlList[1].isShow = true;
      this.controlList[2].isShow = false;
    },
    controlClick(i, label, show) {
      console.log(i);
      this.isVcHoverBgc = false;
      this.$refs.vcBtn[2].classList.remove('vc-hover-bgc');
      console.log(this.$route, '=========');
      if (this.$route.matched[0].name === 'Auth' && label === 'close') {
        console.log('exit-app');
        this.$ipc.send('exit-app')
      } else {
        if (label.endsWith('maximize' )) {// === 'maximize' || label === 'unmaximize') {
          this.controlList[1].isShow = !this.controlList[1].isShow
          this.controlList[2].isShow = !this.controlList[2].isShow
        }
        // this.$log.debug('win-size-control', label)
        console.log('win-size-control', label)
        this.$ipc.send('win-size-control', label);
      }
    }
  }
}
</script>
<style lang="scss" scoped>
.views-control {
  -webkit-app-region: no-drag;
  display: flex;
  align-items: center;
  height: 39px;
  position: absolute;
  right: 10px;
  @include z-index(navigation);
  top: 0;
  .icon-maximize {
    font-size: 17px !important;
  }
  .icon {
    flex: 1;
    display: flex;
    align-items: center;
    color: #333;
    font-size: $--font-size-mid;
    height: 30px;
    width: 30px;
    position: relative;
    &:hover{
      cursor: pointer;
      color:#999;
    }
    &:hover::before {
      background: currentColor;
    }
    &:before {
      color: inherit;
      border-radius: 50%;
      content: '';
      position: absolute;
      left: 0;
      top: 0;
      height: 100%;
      opacity: 0.12;
      transition: 0.3s cubic-bezier(0.25, 0.8, 0.5, 1);
      width: 100%;
    }
  }
  .vc-hover-bgc{
    &:last-child {
      &:hover{
        background: $--color-danger;
        border-radius: $--border-radius-circle; 
      }
    }
  }
}
</style>
