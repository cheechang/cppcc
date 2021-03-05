/**
 * @name VueJS vChatScroll (vue-chat-scroll)
 * @description Monitors an element and scrolls to the bottom if a new child is added
 * @author Theodore Messinezis <theo@theomessin.com>
 * @file v-chat-scroll  directive definition
 */

// const scrollToBottom = el => {
//   setTimeout(() => el.scrollTop = el.scrollHeight)
// };

const vChatScroll = {
  bind: (el, binding, vnode, oldVnode) => {

    new MutationObserver(e => {
      if (e[e.length - 1].addedNodes.length != 1) return
      console.log('vnode.context.isPauseScroll', vnode.context.isPauseScroll)
      if (vnode.context.isPauseScroll) return
      if (!vnode.context.isOpen && !vnode.context.isNeedToScroll) {
        vnode.context.isNeedToScroll = true
        return
      }
      console.log('el.scrollHeight', el.scrollHeight, el.scrollTop)
      if (el.scrollTop !== vnode.context.lastScrollPosition &&
        el.scrollHeight - el.scrollTop > 600 &&
        vnode.context.messageObject[Object.keys(vnode.context.messageObject)[Object.keys(vnode.context.messageObject).length - 1]]
        .messageObject.fromId !== vnode.context.user_account.userId
      ) {
        vnode.context.isShowMsgNotify = true
        vnode.context.unreadCountMsg++
        return
      }
      /** 滚动至底部 */
      el.scrollTop = el.scrollHeight
      console.log('el.scrollTop', el.scrollTop, el.scrollHeight, el.offsetHeight)
      vnode.context.lastScrollPosition = el.scrollTop
    }).observe(el, {
      childList: true,
      subtree: false
    })
  }
  //  inserted: scrollToBottom
};

export default vChatScroll;
