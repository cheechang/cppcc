<template>
  <div class="public-notify">
    <div class="notify-content">
      <i class="icon notify-icon">&#xe61e;</i>
      <p class="marquee">
        <span
          class="notify-text"
          :class="{'is-marquee':isMarquee}"
          :title="notifyContent"
          v-html="notifyContent"
        ></span>
      </p>
    </div>
    <i class="icon go-detail" @click="openDetail" title='前往'>&#xe638;</i>
    <!-- <i class="icon">&#xe606;</i> -->
  </div>
</template>
<script>
import ContactMixin from "../Contact/ContactMixin";
import { mapGetters } from "vuex";
export default {
  name: "publicNotice",
  props: {
    notifyContent: String,
    notifyMsg: Object
  },
  mixins: [ContactMixin],
  data() {
    return {
      isMarquee: false
    };
  },
  mounted() {
    this.$nextTick(() => {
      let notify = document.getElementsByClassName("notify-content")[0];
      let text = document.getElementsByClassName("notify-text")[0];
      console.log("notify", notify.scrollWidth);
      console.log('text', text.scrollWidth)
      if (text.scrollWidth > notify.scrollWidth) {
        let seconds = Math.ceil(text.scrollWidth/notify.scrollWidth)*15
        console.log('seconds:::', seconds)
        this.isMarquee = true;
        text.style.animationDuration	 = seconds + 's';
        setTimeout(() => {
          this.$emit("closeNotify");
        }, seconds*1000);
      } else {
        setTimeout(() => {
          this.$emit("closeNotify");
        }, 5000);
      }
     
    });
  },
  methods: {
    openDetail() {
      console.log("this.notifyMsg", this.notifyMsg);
      let notify = this.contact_appList[this.notifyMsg.targetId];
      console.log("notify:::", notify);
      console.log('this.$route.name', this.$route.name)
      this.startChat(notify);
      if (this.$route.name === 'HomePage') {
        setTimeout(() => {
          this.$signalMonitor.$emit('activeListItem')
        }, 15)
      }
      this.$emit("closeNotify");
    }
  },
  computed: {
    ...mapGetters(["contact_appList"])
  }
};
</script>
<style lang="scss" scoped>
@keyframes marquee {
  0% {
    transform: translateX(0);
  }
  100% {
    transform: translateX(-100%);
  }
}
.public-notify {
  display: flex;
  color: #fff;
  background-image: linear-gradient(rgba(0, 0, 0, 0.4), rgba(0, 0, 0, 0.1));
  height: 32px;
  align-items: center;
  .notify-content {
    width: 100%;
    display: flex;
    justify-content: center;
    align-items: center;
    .v-text-emoji {
      width: 16px;
    }
    .notify-icon {
      margin: 0 10px;
    }
    .marquee {
      white-space: nowrap;
      overflow: hidden;
      box-sizing: border-box;
      margin-right: 24px;
      .notify-text {
        // display: inline-block;
        display: inline-flex;
        justify-content: center;
      }
      .is-marquee {
        padding-left: 100%;
        animation-name: marquee;
        animation-iteration-count: infinite;
        animation-timing-function: linear;
        &:hover {
         animation-play-state: paused;
        }
      }
    }
  }
  .go-detail {
    position: absolute;
    right: 0;
    height: 30px;
    color: #fff;
  }
}
</style>
