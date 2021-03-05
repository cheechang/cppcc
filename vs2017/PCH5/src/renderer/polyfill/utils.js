let agent = navigator.userAgent.toLowerCase();

export default {
  isWeb() {
    return agent.indexOf("electron") === -1;
  }
}