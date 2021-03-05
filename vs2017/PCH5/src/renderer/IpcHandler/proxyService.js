const NODE_ENV = 'electron';
export function getTargetByProxy (parentTarget, childName) {
  // console.log(parentTarget);
  let handler = {
    get: function(target, name) {
      return childName in parentTarget ? parentTarget[childName] : 10001;
    }
  };
  let p = new Proxy({}, handler);
  if (p.a === 10001) {
    console.log(childName + ':该方法不存在,请检查方法名是否正确！');
  }
  return p.functionName;
};
export function getServiceByProxy(){
   if(NODE_ENV === 'electron'){
    const path = require('path');
    let mypath = __dirname;
    const mainIpcPath = process.env.NODE_ENV === 'development' ? path.resolve(__dirname, '../../main/electronService.js') : path.resolve(mypath, '../static/electronService.js');
    return require('electron').remote.require(mainIpcPath);
   }
};
