// 根据platform，安装时拷贝各自平台下的sdk文件到vimsdk中
const path = require('path')
var oauth;
try{
   oauth = require(`./lib/vimsdk/${process.platform}/oauth/oauth.node`);
}catch(error){
   oauth =  null;
}
const vimsdk = require(`./lib/vimsdk/api`);
const robot = require(`./lib/robot/${process.platform}/robot.node`);
module.exports.vimsdk = vimsdk;
module.exports.oauth = oauth;
module.exports.robot = robot;