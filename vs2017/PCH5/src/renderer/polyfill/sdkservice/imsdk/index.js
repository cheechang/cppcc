import auth from './service/auth';
import user from './service/user';
import cloud from './service/cloud';
import contact from './service/contact';
import file from './service/file';
import enterprise from './service/enterprise';
import config from './service/config';


export let service = {
  auth: new auth(),
  user: new user(),
  cloud: new cloud(),
  contact: new contact(),
  file : new file(),
  enterprise: new enterprise(),
  config: new config(),
  log: console.log
};
