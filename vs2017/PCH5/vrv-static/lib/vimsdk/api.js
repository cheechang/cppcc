const vimsdk = require(`./${process.platform}/vimsdk`)
const utils = require('./api/utils/utils')
const fs = require('fs');
const path = require('path')
class Client {
    constructor() {
        this._utils = new utils();
        this._client = new vimsdk.client();
        this._loadService();
    }
    startup(dataPath, crtPath, info) {
        let clientId = this._client.startup(dataPath,crtPath,info);
        return clientId;
    }
    setDataPath(param) {
      this._client.setDataPath(param);
    }
    setLog(param) {
        this._client.setLog(param);
    }
    _loadService() {
        let files = fs.readdirSync(path.resolve(__dirname,'./api/service'))
        files.forEach(file=>{
            let childName = file.split('.')[0];
            this[childName] = () => {
                let child = require(`./api/service/${file}`);
                let childClass = new child(this._client, this._utils);
                return childClass;
            };
        })

    }
}
module.exports = Client;