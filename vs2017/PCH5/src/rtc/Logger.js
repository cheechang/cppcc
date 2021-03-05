const APP_NAME = 'RTCFILE';
const {
	remote
  } = require('electron');
const Service = remote.getGlobal('service')

export default class Logger {

	constructor(prefix) {
		this.prefix = `${APP_NAME}::${prefix}`;
	}
	warn(tag, ...msg) {
		console.warn(`${this.prefix}:: ${tag}`, ...msg);
	}

	info(tag, ...msg) {
		console.info(`${this.prefix}:: ${tag}`, ...msg);
	}

	debug(tag, ...msg) {
		console.debug(`${this.prefix}:: ${tag}`, ...msg);
	}

	error(tag, ...msg) {
		console.error(`${this.prefix}:: ${tag}`, ...msg);
	}

	file(tag, ...msg){
		console.debug(`sdkLog::${this.prefix}:: ${tag}`, ...msg);
		Service.log(`${this.prefix}:: ${tag} ${msg}`);
	}

	fileError(tag, ...msg){
		console.error(`sdkLog::${this.prefix}:: ${tag}`, ...msg);
		Service.log(`${this.prefix}:: ${tag} ${msg}`);
	}
}