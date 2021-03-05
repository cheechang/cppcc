<template>
    <div class="image-text">
      <section
        class="main-content"
        v-if='mainContentInfo.length'
        @click="openNew(mainContentInfo[0].url, mainContentInfo[0].title)"
      >
        <img class="main-item-img" v-if="mainContentInfo[0].imgPath" :src="mainContentInfo[0].imgPath">
        <div class="main-title">
          <h4
            :title="mainContentInfo[0].title"
            class="main-title-content"
          >{{mainContentInfo[0].title}}</h4>
        </div>
      </section>
      <div class="sub-content">
        <div
          class="sub-item"
          v-for="(item, index) in subContentInfos"
          @click="openNew(item.url, item.title)"
          :key="index"
        >
          <p class="sub-item-title" :title="item.title">{{item.title}}</p>
          <img class="sub-item-img" v-if="item.imgPath" :src="item.imgPath">
        </div>
      </div>
    </div>
</template>

<script>
import { mapGetters } from "vuex";
import ImgMixins from "../Mixins/ImgMixins";
export default {
  computed: {
    subContentInfos() {
      if (!this.mainContentInfo.length) return;
      return this.mainContentInfo.filter((e, i) => i !== 0);
    },
    ...mapGetters(["user_imgPath", 'http_head'])
  },
  mixins: [ImgMixins],
  props: {
    message: Object
  },
  data() {
    return {
      imgUrl: "",
      mainContentInfo: [],
    };
  },
  mounted() {
    this.$nextTick(() => {
      console.log('http_head', this.http_head)
      this.mainContentInfo = this.message.messageObject.vtPtBean;
      this.mainContentInfo.forEach(e => {
        this.getImgPaths(e.picUrl).then(imgUrl => {
          if (this.$Service.file.fileOperate({ filepath: imgUrl, type: 0 })) {
            // 此时图片存在
              this.$set(e, "imgPath", imgUrl);
          } else {
            // 此时图片不存在 需要下载
            this.downloadImgs(
              this.message.messageObject.targetId,
              e.picUrl
            ).then(downloadRes => {
              if (downloadRes.code === 0) {
                this.$set( e, "imgPath", `file://${this.user_imgPath}${downloadRes.imgName}`);
              }
            });
          }
        });
      });
    });
  },
  methods: {
    openNew(url, title) {
      let itemurl = url.substr(0, 4).toLowerCase() === "http" ? url :`${this.http_head.preLoginAddress}${url}`;
      this.$Service.log(`msgImgTextUrl:::    ${itemurl||''}`)
      this.$ipc.send("new-window", {
        winUrl: itemurl,
        winType: "templateMsg",
        winTitle: title,
        winFrame: true,
        shapeType: "normal"
      });
    },

    getImgPaths(sourcePath) {
      return new Promise((resolve, reject) => {
        let getNameByUrlCb = resp => {
          // 通过图片名称获取它的url
          console.log("getNameByUrlCb", resp);
          if (resp.result) {
            let imgLastName = resp.result.lastIndexOf("/"); // imgLastName 为图片后缀名称
            let imgLocation = resp.result.substr(0, imgLastName); // 图片所在位置
            let imgUrls = `${
              this.user_imgPath
            }${imgLocation}${resp.result.substr(imgLastName)}`; //图片完整路径
            resolve(imgUrls);
          }
        };
        this.$Service.file.getNameByUrl({ url: sourcePath }, getNameByUrlCb);
      });
    }
  }
};
</script>

<style lang="scss" scoped>
.image-text {
  width: 320px;
  display: flex;
  flex-direction: column;
  padding: 4px;
  overflow: hidden;
  border-radius: 18px;
  min-height: 200px;
  .main-content {
    flex:1;
    width: 100%;
    position: relative;
    border-radius: 18px 18px 0px 0px;
    overflow: hidden;
    .main-title {
      background: rgba(0, 0, 0, 0.3);
      position: absolute;
      bottom: 5px;
      z-index: 100;
      color: #fff;
      width: 100%;
      height: 40px;
      display: flex;
      /* justify-content: center; */
      align-items: center;
      padding-left: 14px;
      .main-title-content {
        @include ellipsis;
      }
    }
    .main-item-img {
      width: 100%;
    }
  }
  .sub-content {
    width: 100%;
    position: relative;
    border-radius: 0 0 18px 18px;
    overflow: hidden;
    .sub-item {
      display: flex;
      height: 60px;
      padding: 0px 15px;
      align-items: center;
      background: #fff;
      border-bottom: solid 1px #ccc;
      justify-content: space-between;
    }
    .sub-item-title {
      @include ellipsis;
    }
    .sub-item-img {
      width: 46px;
    }
  }
}

header {
  height: 35px;
  line-height: 35px;
  font-size: 1rem;
  font-weight: bold;
  margin: 0 4px;
  @include ellipsis;
  border-bottom: 1px solid $--border-color-grey-lighten;
}

.img {
  height: 180px;
  overflow: hidden;
  margin: 5px 10px;
}

.img img {
  width: 360px;
  height: 180px;
}

.url {
  height: 30px;
  line-height: 30px;
  border-top: 1px solid $--border-color-grey-lighten;
  padding: 0 10px;
  text-align: right;
}
</style>
