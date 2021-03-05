const ERROR_JSON_PARSE = -110;
class Utils {
  constructor() {

  }
  makeCallBack(resp, cb, resolve, reject) {
    if(typeof(resp) === 'object'){
      resp = JSON.stringify(resp);
    }
    let obj = null;
    let parseError = false;
    try {
        obj = JSON.parse(resp);
    } catch (error) {
        obj = {
            code: ERROR_JSON_PARSE,
            msg: 'json parse error!'
        };
        parseError = true;
    }
    if(resolve){
      setTimeout(()=>{
          if (parseError) {
              console.log('parseError:',resp);
              reject(obj);
          }
          else {
              resolve(obj);                
          }
      }, 0)
    }
    if (!cb) {
      return;
    }
    cb(obj);
  }
}
module.exports = Utils;