/**
 * 平台相关数据
 */
const pkg = require('../../package.json')
 export default class Platform {
   constructor() {
    this.platformInfos = [
      {
        platform: 'win32',
        deviceinfo: pkg.deviceInfo,
        dbPath: `/AppData/Local/${pkg.productName}/`
      },
      {
        platform: 'darwin',
        deviceinfo: 'pc-osx',
        dbPath: `/Library/Containers/com.vrv.Linkdood/Data/${pkg.productName}/`
      },
      {
        platform: 'linux',
        deviceinfo: 'pc-linux',  //  以后可能需要根据具体平台获取
        dbPath: `/.local/share/${pkg.productName}/`
      }
    ];

    this.platformInfos.map(info => {
      console.log('process.platform: ', process.platform);
      if (info.platform === process.platform) {
        this.platformInfo =  {deviceInfo: info.deviceinfo, dbPath: info.dbPath, platform: info.platform};
        return;
      }
    });
   }
   platforminfo() {
    return this.platformInfo;
   }
 }