const path = require('path');
let mypath = __dirname;
const mainIpcPath = process.env.NODE_ENV === 'development' ? path.resolve(__dirname, '../main/IpcMainHandler.js') : mypath + '/static/IpcMainHandler.js';
console.log('__dirname=' + mainIpcPath);
const ipcMain = require('electron').remote.require(mainIpcPath);
module.exports = {
    callService(functionName) {
        let handler = {
            get: function (target, name) {
                return functionName in ipcMain ? ipcMain[functionName] : 10001;
            }
        };
        let p = new Proxy({}, handler);
        if (p.a === 10001) {
            console.log(functionName + ':该方法不存在,请检查方法名是否正确！');
        }
        return p.functionName;
    }
};