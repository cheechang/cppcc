const crypto = require('crypto');
const dgram = require("dgram");
const secretKey = Buffer.from('BeiLjing2VRIV0SoftwaNre1CorpKoraDtioon9LimiDted', 'utf8');
let miniPort = 41234;
let maxPort = 41243;
let socket_server;
let socket_client;
let myPort;
/****************************************注册服务消息通知********************************************* */
export function regServersMsg(cb){
  createServer(resp=>{
    //解密消息并进行返回
    let result = JSON.parse(decryStr(resp));
    global.service.log(`收到其他服务器消息:${JSON.stringify(result)}`);
    cb(result);
  })
}
/****************************************给其他服务发送消息********************************************* */
// msg：object
export function sendMsg(msg){
    // 加密后将消息进行广播
    global.service.log(`服务器进行消息广播:${JSON.stringify(msg)}`);
    let bufferMsg = Buffer.from(encryStr(JSON.stringify(msg)));
    broadcastMsgs(bufferMsg);
}

/****************************************加密字符串********************************************* */
// 采用crypto aes加密
export function encryStr(str) { //str 为utf-8格式
  const cipher = crypto.createCipher('aes-128-ecb', secretKey);
  let enc = cipher.update(str, 'utf8', 'hex'); //编码方式从utf-8转为hex;
  enc += cipher.final('hex'); //编码方式从转为hex;
  return enc
}

/****************************************解密字符串********************************************* */
export function decryStr(str) { //str 为hex格式
  const decipher = crypto.createDecipher('aes-128-ecb', secretKey);
  let dec = decipher.update(str, 'hex', 'utf8'); //编码方式从hex转为utf-8;
  dec += decipher.final('utf8'); //编码方式从utf-8;
  return dec;
}
/****************************************创建服务监听广播消息********************************************* */
function createServer(cb){
    socket_server = dgram.createSocket("udp4")
    socket_server.on("error", function (err) {
    console.log("server error:\n" + err.stack);
    socket_server.close();
    if(miniPort < maxPort){
        miniPort++;
        createServer(cb);
    }
    else{
        //cb('createServerError')
    }
  });
  
  socket_server.on("message", (msg, rinfo)=> {
    console.log("server got: " + msg + " from " +
      rinfo.address + ":" + rinfo.port);
      cb(msg.toString());
  });
  
  socket_server.on("listening", function () {
    let address = socket_server.address();
    console.log("server listening " +
        address.address + ":" + address.port);
    myPort = miniPort;
  });
  
  socket_server.bind(miniPort);
}
/****************************************广播消息********************************************* */
function broadcastMsgs(message){
   global.service.log(`服务器进行消息广播broadcastMsgs加密消息:${message}`);
    if(!socket_client){
        socket_client = dgram.createSocket("udp4");
        socket_client.bind(function () {
            socket_client.setBroadcast(true);
       });
    }
   for(let port = 41234;port<41244;port++){
       if(port !== myPort){
        socket_client.send(message, 0, message.length, port, '127.0.0.1', function(err, bytes) {
            //socket.close();
          });
       }
   }
}