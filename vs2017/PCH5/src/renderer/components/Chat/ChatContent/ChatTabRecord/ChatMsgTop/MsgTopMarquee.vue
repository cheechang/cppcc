<template>
<!-- 【消息置顶】跑马灯组件 -->
  <div class="msg-top-marquee">
    <!-- 暂时是点击跑马灯背景展开/收缩，查看更多 -->
    <div class="content-area">
      <i class="icon msg-top-tip">&#xe8a2;</i>
      <div class="marquee-content" v-if="index<=4" :style="{top: 5+32*index+'px'}" v-for="(item, index) in getList" :key="index" @click="expendMaxTopMsg">
        <!-- 动画总时长，通过修改文字内容长度可以测试 -->
        <span ref="marquee" :style="computedAnimalDuration">{{item.remark+item.content}}</span>
      </div>
      <i class="icon msg-top-close" @click="$emit('closeTopMsg')">&#xe606;</i>
    </div>
  </div>
</template>
<script>
import {mapGetters} from 'vuex'
export default {
  props: {
    topMsgList: {
      type: Array,
      default: () => [
        {content: '消息置顶：暂无消息', remark: ''},
      ]
    },
    id: String
  },
  data() {
    return {
      // 初始300即设置动画初始总时长（300/30）10s
      width: [],
      lists: [],
      isExpend: false
    }
  },
  computed: {
    ...mapGetters(['chat_chatContentTop','chat_objectInfo']),
    getList(){
      this.lists = [];
      let topsArray = Object.keys(this.chat_chatContentTop);
      if(topsArray&&topsArray.length > 0){
        console.log('chat_chatContentTop::::::', JSON.stringify(this.chat_chatContentTop)) 
        console.log('topsArray:',topsArray);
        let topMsgId = topsArray.pop();
        let topObj = Object.assign({},this.chat_chatContentTop[topMsgId]);

        let user = JSON.parse(topObj.topContent);
        topObj.content = user.content;
        topObj.remark = user.name+'的发言：';
        // if (this.chat_objectInfo[this.id]&&this.chat_objectInfo[this.id][topObj.fromId]) {
        //   console.log('remark:::::::', this.chat_objectInfo[this.id][topObj.fromId])
        //   topObj.remark = this.chat_objectInfo[this.id][topObj.fromId].remark + ': '
        // }
        this.lists.push(topObj)
      }
      else{
        this.lists = this.topMsgList
        //this.lists.push(this.topMsgList[0])
      }
       return this.lists;
    },
    computedAnimalDuration() {
      return {
        'animation-duration': (this.width[0]&&this.width[0].offsetWidth||300)/30 + 's'
      }
    }
  },
  created() {
    this.lists.push(this.topMsgList[0])
  },
  mounted() {
    // 根据文字内容长度，修正动画播放总时长，即改变动画播放速度
    this.width = this.$refs.marquee
  },
  methods: {
    expendMaxTopMsg() {
      this.$emit('openChatMsgTop', {index: 3, view: 'msgRecord', components:'ChatTabRecord'});
    }
  }
};
</script>
<style lang="scss">
.msg-top-marquee {
  // 动画位置放在会话的右侧顶部
  position: absolute;
  left: 100%;
  z-index: 9;
  // 动画：from数值是背景宽度
  @keyframes marquee {
    from {
      transform: translateX(120px);
    }
    to {
      transform: translateX(-100%);
    }
  }
  .content-area{
    top: 3px;
    display: flex;
    width: 168px;
    position: absolute;
    height: 32px;
    right: 16px;
    border-radius: 3px;
    color:#4CAF50;
    overflow: hidden;
    background: #fff;
    font-size: 12px;
    box-shadow: 0 0 10px 0 rgba(101, 111, 122, 0.5);
    align-items: center;
    .msg-top-tip{
      width: 24px;
      height: 100%;
    }
    .msg-top-close{
      width: 24px;
      border-left: solid 1px #bdbdbd;
      height: 75%;
      top: 10%;
      font-size: 14px;
    }
    .marquee-content {
    //width: 275px;
   // position: absolute;
    height: 32px;
    cursor: pointer;
    width: 120px;
    overflow: hidden;
    // 动画背景
    //background: lightblue;
    span {
      white-space: nowrap;
      //position: absolute;
      // 动画效果
      animation: marquee linear infinite;
      // 动画播放字体颜色
      display: flex;
      align-items: center;
      height: 100%;
    }
  }
  }
}
</style>
