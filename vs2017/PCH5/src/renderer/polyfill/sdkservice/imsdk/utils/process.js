import axios from 'axios';

export function _get(host, name, param, cb) {
  let p = param ? `?param=${param}` : "";
  axios.get(`${host}/${name}${p}`)
    .then(resp => {
      cb(resp.data);
    })
    .catch(error => {
      console.log(error);
    });
}