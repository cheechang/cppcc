const OPERA_TYPE = {
  viewed : 'viewed',
  prev: 'prev',
  next: 'next'
}
function getImgMsg() {
  return new Promise(resolve => {
    service.chat.getImgMsg({
      targetId: targetId.toString()
    }, resp => {
      console.log('getImgInfo::::', resp)
      resolve(resp)
    })
  })
}

function getImgPath(sourcePath) {
  return new Promise((resolve, reject) => {
    let getNameByUrlCb = resp => { // 通过图片名称获取它的url
      console.log('sourcePath:::', sourcePath)
      if (resp.result) {
        let imgLastName = resp.result.lastIndexOf('/') // imgLastName 为图片后缀名称
        let imgLocation = resp.result.substr(0, imgLastName) // 图片所在位置
        let imgUrl = `${user_imgPath}/${imgLocation}/cache${resp.result.substr(imgLastName)}` //图片完整路径 
        resolve({
          mediaUrl: imgUrl,
          imgLocation: `${user_imgPath}/${imgLocation}/cache/`
        })
      }
    }
    service.file.getNameByUrl({
      url: sourcePath
    }, getNameByUrlCb)
  })
}

function getImgInfo(targetId, msgId) {
  return new Promise((resolve, reject) => {
    let param = {
      targetId: targetId.toString(),
      count: 1,
      msgId: msgId.toString(),
      flag: 2
    }
    service.chat.getMessages(param, resp => {
      // let imgCollection = JSON.parse(resp.msgs[0].body).serverUrl;
      resolve(resp)
    })
  })
}

function downloadImgs(targetId, imgUrl) {
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
    var cirtleNode = document.querySelector(".img-process-rate");
    cirtleNode.style.display = 'block';
    var processNode = document.querySelector("#big-process");
    var circleLength = Math.floor(2 * Math.PI * processNode.getAttribute("r"));
    console.log('downloadImageParam', downloadImageParam)
    service.file.downloadImage(downloadImageParam, resp => {
      console.log('imgdownLoad code-------------------------------->', resp.code)
      if (currentMsg.index && index !== currentMsg.index) return
      if (currentMsg.nineIndex && nineIndex !== currentMsg.nineIndex) return
      cirtleNode.style.display = 'none';
      processNode.setAttribute("stroke-dasharray", "" + 0 + ",10000");
      resolve(resp)
    }, process => {
      console.log('circleprocess', circleLength * process.progess / 100)
      if (currentMsg.index && index !== currentMsg.index) return
      if (currentMsg.nineIndex && nineIndex !== currentMsg.nineIndex) return
      processNode.setAttribute("stroke-dasharray", "" + circleLength * process.progess / 100 + ",10000");
    })
  })
}

function decryptImgs(srcpath, encryptKey, destPath) {
  return new Promise((resolve, reject) => {
    let decryptFileParam = {
      encryptkey: encryptKey,
      srcpath: srcpath,
      destpath: destPath
    }
    console.log('decryptFileParam', decryptFileParam)
    let decryptFileCb = decryptFileRes => {
      console.log('解密结果', decryptFileRes.result)
      resolve(decryptFileRes)
    }

    service.file.decryptFile(decryptFileParam, decryptFileCb)
  })
}

function downloadMedialUrl(targetId, user_imgPath, mediaUrl, enc_dec_key, destpath, imgData) {
  console.log('destpath::', destpath)
  return new Promise((resolve, reject) => {
    downloadImgs(targetId, mediaUrl).then(resp => {
      if (resp.code === 0) {
        /** enc_dec_key 为空 图片不需要解密 */
        if (!enc_dec_key) {
          service.log(`medialImg download no_enc_dec_key  ${user_imgPath}${resp.imgName}`)
          // resolve()
          resolve({
            path: `${user_imgPath}${resp.imgName}`
          })
          return
        }

        let srcpath = user_imgPath + '/' + resp.imgName
        console.log('srcpath:::', srcpath)
        decryptImgs(srcpath, enc_dec_key, destpath).then(resp => {
          if (resp.result) {
            resolve({
              path: destpath,
              imgData: imgData
            })
          } else {
            service.log(`medialImg decrypt fail  ${resp.result}`)
          }
        })
      } else {
        if (resp.code === -16777206) {
          let errorTip = document.getElementsByClassName('error-tip')[0]
          errorTip.style.display = 'block';
          // errorTip.innerHTML = '图片已过期或已被清理'
        }
        service.log(`medialImg download fail  ${resp.code}`)
      }
    })
  })
}

function newViewer(imgPath) {
  var image = new Image();
  image.src = imgPath;
  image.onerror = err => {
    console.log('image onerror::::', err)
    image.src = '../../resources/images/message/default_privew.jpg'
  }
  viewer = new Viewer(image, {
    viewed: function() {
      console.log('msg viewed')
      console.log('model', model)
      if (model === 'editImg') {
        handleEditAreaImg('viewed')
        return
      }
      /**
       * isMixMsg 混合消息特殊处理
       * 获取混合消息的消息Id 和targetId
       */
      if (isMixMsg === 'true') {
        let mixTargetId = searchParams.get("mixTargetId")
        let mixMsgId = searchParams.get("mixMsgId")
        service.log(`image isMixMsg  mixTargetId::${mixTargetId}mixMsgId::${mixMsgId}`)
        getImgInfo(mixTargetId, mixMsgId).then(msg => {
          let mix_msg = msg.msgs[0].mVt_msg
          let currentIndexs = mix_msg.findIndex(e => e.msgId == msgId)
          currentMsg = mix_msg[currentIndexs]
          console.log('currentMsg::', currentMsg)
          imgMsg = msg.msgs
          index = 0
          if (model === 'muti') {
            showSwitchBtn()
            nineIndex = parseInt(searchParams.get("index"))
            nineImg = currentMsg.nine[nineIndex]
            showImg(nineImg)  
            console.log('nineImg::', nineImg)
            return
          }
          showImg(currentMsg)
        })
        return
      }
      async function getsAllImage() {
        let imgList = await getImgMsg()
        imgMsg = imgList.msgs
        service.log(`imgMsg length  ${imgMsg.length||0}`)
        index = imgMsg.findIndex((e) => {
          return e.msgId === msgId.toString()
        })
        showSwitchBtn()
        console.log('imgMsg', imgMsg)
        console.log('index', index)
        currentMsg = imgMsg[index]
        if (model === 'muti') {
          console.log(':::muti', model)
          nineIndex = parseInt(searchParams.get("index"))
          nineImg = currentMsg.nine[nineIndex]
          showImg(nineImg)
          return
        }
        console.log('currentMsg', currentMsg)
        showImg(currentMsg, false)
      }
      getsAllImage()
    },
    navbar: false,
    button: false,
    title: false,
    toolbar: {
      rotateRight: true,
      flipHorizontal: true,

      prev: function() {
        console.log('prev:::::::::::')
        if (model === 'editImg') {
          handleEditAreaImg('prev')
          return
        }
        if (model === 'muti' && nineIndex > 0) {
          nineIndex--
          nineImg = currentMsg.nine[nineIndex]
          showImg(nineImg)
          return
        }
        if (index === 0) {
          return
        }
        index--
        currentMsg = imgMsg[index]
        if (currentMsg.msgType === 28) {
          nineIndex = currentMsg.nine.length - 1
          model = 'muti'
          nineImg = currentMsg.nine[nineIndex]
          showImg(nineImg)
          return
        }
        model = 'single'
        showImg(currentMsg)

      },
      next: function() {
        if (model === 'editImg') {
          handleEditAreaImg('next')
          return
        }
        if (model && model === 'muti' && nineIndex < currentMsg.nine.length - 1) {
          nineIndex++
          nineImg = currentMsg.nine[nineIndex]
          showImg(nineImg)
          return
        }
        if (index >= imgMsg.length - 1) {
          return
        }
        index++
        currentMsg = imgMsg[index]
        if (currentMsg.msgType === 28) {
          nineIndex = 0
          model = 'muti'
          nineImg = currentMsg.nine[nineIndex]
          showImg(nineImg)
          return
        }
        model = 'single'
        showImg(currentMsg)
      },
      download: function() {
        console.log('download::', viewer.image.src, viewer.image.alt)
        // downLoadImgToLocal(viewer.image.src, viewer.image.alt)
        saveAs()
        
      }
    },
    hidden: function() {
      return false;
    },
  });
  viewer.show();
  return viewer;
}

/**
 * 初始化节点
 */
function initNode () {
  let errorTip = document.getElementsByClassName('error-tip')[0]
  errorTip.style.display = 'none';
  let cirtleNode = document.querySelector(".img-process-rate");
  cirtleNode.style.display = 'none';
  let processNode = document.querySelector("#big-process");
  processNode.setAttribute("stroke-dasharray", "" + 0 + ",10000");
}

/**
 * 显示向上向下切换按钮
 */
function showSwitchBtn() {
  let nextNode = document.querySelector(".viewer-next"),
  prevNode = document.querySelector(".viewer-prev");
  prevNode.style.display = 'block';
  nextNode.style.display = 'block';
}

function showImg(currentMsg, isNeedDefaultImg = true) {
  console.log('isNeedDefaultImg:::', isNeedDefaultImg)
  initNode()
  currentMsg.index = index
  if (model === 'muti') {
    currentMsg.nineIndex = nineIndex
  }
  getImgPath(currentMsg.mainUrl).then(resp => {
    console.log('getImgPath:::', resp)
    let fileOperateParam = {
      filepath: resp.mediaUrl, //路径
      type: 0 // 操作类型 0：判断文件或文件夹是否存在 1.创建文件夹 2.删除文件 3.重命名文件
    }
    /*
     * 判断大图是否存在
     * 不存在 开启新窗口时附带缩略图路径和大图路径
     * 若存在 直接带大图路径
     */
    service.log(`img mainPath::  ${resp.mediaUrl}`)
    if (service.file.fileOperate(fileOperateParam)) {
      viewer.image.src = resp.mediaUrl
      console.log('viewer::', viewer)
      setTimeout(() => {
        viewer.resize()
      })
    } else {
      if (isNeedDefaultImg) {
        console.log('isNeedDefaultImg:::', isNeedDefaultImg)
        if (currentMsg.thumbPath && service.file.fileOperate({ filepath: currentMsg.thumbPath, type: 0})) {
          viewer.image.src = currentMsg.thumbPath
          console.log('viewer::', viewer)
          setTimeout(() => {
            viewer.resize()
          })
        } else {
          console.log('currentMsg.thumbUrl', currentMsg.thumbUrl)
          getImgPath(currentMsg.thumbUrl).then(resp => {
            let fileOperateParam = {
              filepath: resp.mediaUrl, //路径
              type: 0 // 操作类型 0：判断文件或文件夹是否存在 1.创建文件夹 2.删除文件 3.重命名文件
            }
            /*
             * 判断大图是否存在
             * 不存在 开启新窗口时附带缩略图路径和大图路径
             * 若存在 直接带大图路径
             */
            console.log('thumbUrl', resp.mediaUrl)
            console.log('fileOperate Res:::', service.file.fileOperate(fileOperateParam))
            console.log('resp.mediaUrl', resp.mediaUrl)
            if (service.file.fileOperate(fileOperateParam)) {
              viewer.image.src = resp.mediaUrl
              setTimeout(() => {
                viewer.resize()
              })
            } else {
              viewer.image.src = '../../resources/images/message/default_privew.jpg'
              setTimeout(() => {
                viewer.resize()
              })
            }
          })
        }
      }

      downloadMedialUrl(targetId, user_imgPath, currentMsg.mainUrl, currentMsg.encryptKey, resp.mediaUrl).then(img => {
        console.log('index::', index, currentMsg.index)
        console.log('nineIndex', currentMsg.nineIndex)
        if (currentMsg.index && index !== currentMsg.index) return
        if (currentMsg.nineIndex && nineIndex !== currentMsg.nineIndex) return
          viewer.image.src = img.path
          console.log('downloadMedialUrl::', img.path)
          setTimeout(() => {
            viewer.resize()
          })
      })
    }
  })
}

// function downLoadImgToLocal(savePath) {
//   // const a = document.createElement('a');

//   // a.href = src;
//   // a.download = alt;
//   // document.body.appendChild(a);
//   // a.click();
//   // document.body.removeChild(a);
//   fs.createReadStream(viewer.image.src).pipe(fs.createWriteStream(savePath))
// }


function copy() {
  let currentSrc = viewer.image.src.replace(isMac ?'file://': 'file:///', '')
  let imgs = nativeImage.createFromPath(currentSrc)
  clipboard.writeImage(imgs)
}

async function saveAs() {
  console.log('alt', viewer.image.alt)
  let imgLastName = viewer.image.src.lastIndexOf('/')
  let imgLocation = viewer.image.src.substr(imgLastName)
  let savePath = await showSaveDialog(imgLocation)
  console.log('savePath', savePath)
  console.log('src', viewer.image.src)
  let currentSrc = viewer.image.src.replace(isMac ?'file://': 'file:///', '')
  let createStream, readStream
  readStream = fs.createReadStream(currentSrc).pipe(createStream = fs.createWriteStream(savePath))
  readStream.on('close', function () {
    service.log(`img 另存为 读取完成::`)
  });
  createStream.on('close', function () {
    service.log(`img 另存为 下载完成::`)
  });
}

function foward() {
  console.log('targetId', targetId, msgId)
  let forwardParam = {
    mode:  'sendImg',
    targetId: targetId,
    msgId: msgId,
    imgPath: viewer.image.src
  }
  console.log('forwardParam', forwardParam)
  ipcRenderer.send('imagePreviewForward', forwardParam)
}

function handleEditAreaImg(type) {
  if (type === OPERA_TYPE.viewed) {
    let editImgs = JSON.parse(searchParams.get("imgs").replace(/\\/ig, '/'))
    console.log('editImgs', editImgs)
    if (editImgs.length > 1) {
      showSwitchBtn()
      imgMsg = editImgs
    }
    index =  searchParams.get("currentIndex")
  } else if (type === OPERA_TYPE.prev) {
    if (index === 0) {
      return
    }
    index--
    viewer.image.src = imgMsg[index]
    setTimeout(() => {
      viewer.resize()
    })
  } else {
    if (index >= imgMsg.length-1) {
      return
    }
    index++
    viewer.image.src = imgMsg[index]
    setTimeout(() => {
      viewer.resize()
    })
  }
}
function showSaveDialog(fileName) {
  return new Promise(resolve => {
    /**
     * 文件后缀过滤 
     * 若存在文件后缀 限制保存格式
     * 不存在后缀名称 则支持所有文件类型
     */
    let extensionFilter = [{ name: 'All Files', extensions: ['*'] }]
    if (fileName.lastIndexOf('.') !== -1) {
      let fileExtension = fileName.substr(fileName.lastIndexOf('.') + 1)
      if (fileExtension) {
        extensionFilter.unshift({ name: 'Files', extensions:[fileExtension] })
        console.log('extensionFilter::', extensionFilter)
      }
    }
    remote.dialog.showSaveDialog({ defaultPath: fileName, filters: extensionFilter }, resp => {
      resolve(resp)
    })
  })
}

function identifyQrcode(thumbImg) {
  let currentSrc = thumbImg?thumbImg:viewer.image.src.replace(isMac ?'file://': 'file:///', '')
  let buffer = fs.readFileSync(currentSrc)
  Jimp.read(buffer).then((blockimg)=>{
    console.log('blockimg::::', blockimg)
    let bitmap = blockimg.bitmap
    let code = jsQR(bitmap.data,bitmap.width,bitmap.height);
    if (code) {
      console.log(code.data)
      ipcRenderer.send('imagePreview-identifyQrcode', code.data)
    } else {
      console.log('未识别成功')
    }
  }).catch((err2)=>{
    if(err2){
      console.log(err2);
      cb(null,null);
    }
  });
}

window.newViewer = newViewer;
window.saveAs = saveAs
window.foward = foward
window.identifyQrcode = identifyQrcode
window.copy = copy