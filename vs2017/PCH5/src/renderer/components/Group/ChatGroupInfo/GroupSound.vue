<template>
  <div class="sound">
    <p class="sound-text" :title="$t('groups.groupBeepTone')">{{ $t('groups.groupBeepTone') }}</p>
    <div class="sound-title" @click.self.stop="isShow=!isShow" v-click-outside="onClickOutside">
      <span @click.self.stop="isShow=!isShow" :title="currentTone">{{ currentTone }}</span>
      <i class="icon" @click.self.stop="isShow=!isShow" :title="currentTone">&#xe77a;</i>
      <transition name="zoom-in-top">
        <div v-if="isShow" class="sound-list">
          <div
            class="sound-item"
            v-for="(item, index) in toneInfoList"
            :key="index"
            @click="selectItem(item)"
            :title="item.val"
          >{{item.val}}</div>
        </div>
      </transition>
    </div>
    <load-animal
      :style="{visibility:toneTopLoadStart?'visible':'hidden',width:'4px'}"
      :loadFinished="toneLoadFinished"
    ></load-animal>
  </div>
</template>
<script>
import { mapGetters } from "vuex";
import vClickOutside from "./../../Chat/v-click-outside/index";
import LoadAnimal from "./LoadAnimal";
export default {
  directives: {
    clickOutside: vClickOutside.directive
  },
  props: {
    isGroupLeader: Number | String,
    id: String,
    toneInfo: {
      type: String,
      default: "push6"
    },
    toneTopLoadStart: Boolean,
    toneLoadFinished: Boolean
  },
  components: {
    LoadAnimal
  },
  data() {
    return {
      toneInfoList: [
        { val: this.$t("groups.push1"), tone: "push1" },
        { val: this.$t("groups.push2"), tone: "push2" },
        { val: this.$t("groups.push3"), tone: "push3" },
        { val: this.$t("groups.push4"), tone: "push4" },
        { val: this.$t("groups.push5"), tone: "push5" },
        { val: this.$t("groups.push6"), tone: "push6" },
      ],
      isShow: false,
      audioGroupToneNode: null
    };
  },
  computed: {
    ...mapGetters(["contact_groupList", "user_account"]),
    currentTone() {
      return this.$t(`groups.${this.toneInfo}`);
    }
  },
  mounted() {
    this.$nextTick(() => {
      this.audioGroupToneNode = document.getElementById("audioGroupTone");
    })
  },
  methods: {
    // 点击外部区域关闭列表
    onClickOutside() {
      this.isShow = false;
    },
    // 设置群提示音
    selectItem(item) {
      // 关闭列表
      this.isShow = false;
      this.audioGroupToneNode.src = require(`vrv-static/resources/audio/${
        item.tone
      }.mp3`);
      this.$nextTick(() => {
        this.audioGroupToneNode.play();
      });
      if (item.tone !== this.toneInfo) {
        this.$emit("setSound", item.tone);
      }
    }
  }
};
</script>
<style lang="scss">
.sound {
  position: relative;
  width: 100%;
  display: flex;
  align-items: center;
  .sound-text {
    flex-basis: 43%;
  }
  .sound-title {
    display: flex;
    align-items: center;
    position: relative;
    flex: 1;
    text-align: center;
    &:hover {
      cursor: pointer;
    }
    span {
      flex: 1;
      font-weight: 800;
    }
    i {
      width: 12px;
      height: 12px;
      line-height: normal;
    }
    .sound-list {
      width: 104%;
      font-size: 12px;
      position: absolute;
      background: #fff;
      top: 30px;
      left: 0;
      z-index: 1;
      border-radius: $--border-radius-base;
      box-shadow: 0 0 1px #3b3939;
      overflow: hidden;
      .sound-item {
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
