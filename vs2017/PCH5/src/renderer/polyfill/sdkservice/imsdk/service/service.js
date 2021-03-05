import { _get } from '../utils/process'
export default class Service {
  constructor(url) {
    this.url = `http://localhost:3333/${url}`;
  }

  _process(functionName, param, cb) {
    console.log("in _process: ", functionName, param);
    _get(this.url, functionName, param?JSON.stringify(param):param, cb);
  }
}