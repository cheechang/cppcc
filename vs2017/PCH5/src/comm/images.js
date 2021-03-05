
const nativeImage = require('electron').nativeImage;
import { isWinXp } from '../comm/is'
/** ****************************************图 片 压 缩 裁 剪 ******************************************* */
export const thumbImage = (srcImg, isResize) => {
  let image = isResize ? nativeImage.createFromPath(srcImg) : nativeImage.createFromDataURL(srcImg);
  if (isResize && !isWinXp) {
    if (image.getSize().height > 200) {
      image =image.resize({
        height: 200
      });
    }
    if (image.getSize().width > 300) {
      image = image.resize({
        width: 300
      });
    }
  }
  console.log("Image",image);
  let originBuffer = isWinXp?image.toJpeg(100):image.toJPEG(100);
  let thumBbinary;
  for(let i=100;i>1;i=i/1.5){
    thumBbinary = isWinXp?image.toJpeg(Math.round(i)).toString("base64"):image.toJPEG(Math.round(i)).toString("base64")
    if(thumBbinary.length<2500){
      break;
    }
  }
  let images = {
    thumBbinary:thumBbinary.length>2500?'':thumBbinary,  //避免某些图片压缩失败
    originBuffer: originBuffer,
    width: image.getSize().width,
    height: image.getSize().height
  };
  return images;
};

export function toFileImg(el, fileIcon, fileName, fileSize) {
  return new Promise ((resolve) => {
    let canvas = el.getContext('2d');

    canvas.fillStyle = '#fff';    //   填充颜色
    canvas.lineWidth = 1;//设置边框大写
    canvas.strokeStyle = "#ccc";//填充边框颜色
    canvas.strokeRect(0, 0, 220, 50);//对边框的设置
    canvas.fillRect(1, 1, 218, 48);
  
    let img = new Image;
    img.src = fileIcon;
    console.log('img',img);
  
    img.onload = function () {
      canvas.drawImage(img, 6, 10);
      resolve(el.toDataURL("image/jpeg"))
    }
  
    canvas.fillStyle = '#000';   // 文字填充颜色
    canvas.font = '12px Microsoft YaHei';
    canvas.fillText(fileName,40, 22);
    
    canvas.fillStyle = '#000';   // 文字填充颜色
    canvas.font = '10px Microsoft YaHei';
    canvas.fillText(fileSize,40, 38);
  
    canvas.stroke();
  })
}

