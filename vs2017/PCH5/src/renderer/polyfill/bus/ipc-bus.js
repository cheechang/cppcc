export default class IpcBus {
  constructor() {
    this.ipc = window.require('electron').ipcRenderer;
  }

  send(event, param) {
    this.ipc.send(event, param);
  }

  on(event, eventHandler) {
    console.log('ipc on: ', event);
    this.ipc.on(event, eventHandler);
  }

  once(event, eventHandler) {
    this.ipc.once(event, eventHandler);
  }

  removeListener(event, eventHandler) {
    this.ipc.removeListener(event, eventHandler);
  }

  removeAllListeners(events) {
    this.ipc.removeAllListeners(events);
  }
}