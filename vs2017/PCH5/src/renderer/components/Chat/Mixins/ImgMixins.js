import { mapGetters } from 'vuex';
import { resolve } from 'dns';
import { join } from 'path';
const ImgMixins = {
  data() {
    return {
      encryptFileSavePath: '' // 加密文件存放位置
    }
  },
  computed: {
    ...mapGetters(['user_account', 'user_imgPath'])
  },
  methods: {
    getImgPath(sourcePath) {
      return new Promise((resolve, reject) => {
        let getNameByUrlCb = resp => { // 通过图片名称获取它的url
          console.log('getNameByUrlCb', resp)
          if (resp.result) {
            let imgLastName = resp.result.lastIndexOf('/') // imgLastName 为图片后缀名称
            let imgLocation = resp.result.substr(0, imgLastName) // 图片所在位置
            let imgUrls = `${this.user_imgPath}${imgLocation}/cache${resp.result.substr(imgLastName)}` //图片完整路径 
            resolve(imgUrls)
          }
        }
        this.$Service.file.getNameByUrl({ url: sourcePath }, getNameByUrlCb)
      })
    },
    downloadImgs(targetId, imgUrl) {
      return new Promise((resolve, reject) => {
       /*
        *下载图片
        *@param[in] targetId
        *@param[in] 图片url
        *@param[in] cb
        */
        let downloadImageParam = {
            targetId: targetId,
            url: imgUrl
        }
        // console.log('downloadImageParam', JSON.stringify(downloadImageParam))
        this.$Service.file.downloadImage(downloadImageParam, resp => {
            this.$Service.log(`imgdownLoad code------- ${resp.code}`)
            resolve(resp)
        })
    })
  },
  decryptImgs(imgName, encryptKey, destPath, srcpath) {
    return new Promise((resolve, reject) => {
    let decryptFileParam = {
        encryptkey: encryptKey,
        srcpath: srcpath? srcpath:this.user_imgPath + imgName,
        destpath: destPath
    }

    console.log('decryptFileParam', JSON.stringify(decryptFileParam))
    let decryptFileCb = decryptFileRes => {
      this.$Service.log(`解密结果 ${decryptFileRes.result}`)
      resolve({result: decryptFileRes.result, destPath: destPath})
    }

    this.$Service.file.decryptFile (decryptFileParam, decryptFileCb)
  })
  }
}
};
export default ImgMixins;
