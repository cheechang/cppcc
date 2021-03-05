<script>
import {
  closest,
  getOffset,
  getPrecedingRange,
  getRange,
  applyRange,
  scrollIntoView,
  getAtAndIndex,
  placeCaretAtEnd,
  insertNode
} from "./at";
import AtTemplate from "./AtTemplate.vue";

export default {
  name: "At",
  mixins: [AtTemplate],
  props: {
    chatType: Number,
    at: {
      type: String,
      default: null
    },
    ats: {
      type: Array,
      default: () => ["@"]
    },
    suffix: {
      type: String,
      default: " "
    },
    loop: {
      type: Boolean,
      default: true
    },
    allowSpaces: {
      type: Boolean,
      default: true
    },
    avoidEmail: {
      type: Boolean,
      default: true
    },
    hoverSelect: {
      type: Boolean,
      default: true
    },
    members: {
      type: Array,
      default: () => []
    },
    nameKey: {
      type: String,
      default: ""
    },
    isShowList: {
      type: Boolean,
      default: false
    },

    msgAtList: {
      type: Object | Array
    },
    filterMatch: {
      type: Function,
      default: (name, pingyin, chunk, at) => {
        // match at lower-case
        return (
          name.toLowerCase().indexOf(chunk.toLowerCase()) > -1 ||
          pingyin.toLowerCase().indexOf(chunk.toLowerCase()) > -1
        );
      }
    },
    deleteMatch: {
      type: Function,
      default: (name, chunk, suffix) => {
        return chunk === name;
      }
    },
    scrollRef: {
      type: String,
      default: ""
    }
  },

  data() {
    return {
      hasComposition: false,
      atwho: null,
      allMember: [],
      groupdefault: require("vrv-static/resources/images/contact/groupdefault_1.png"),
      manDefault: require("vrv-static/resources/images/contact/manDefault.png"),
      num: 0
    };
  },
  mounted() {
    this.$nextTick(() => {
      this.$emit("mounteds");
    });
  },
  computed: {
    atItems() {
      return this.at ? [this.at] : this.ats;
    },

    // style() {
    //   if (this.atwho) {
    //     const { list, cur, x, y } = this.atwho
    //     const { wrap } = this.$refs
    //     if (wrap) {
    //       const offset = getOffset(wrap)
    //       let crisis = wrap.clientWidth  // 临界点 超过此临界点  就显示在此处
    //       const scrollLeft = this.scrollRef
    //         ? document.querySelector(this.scrollRef).scrollLeft
    //         : 0
    //       const scrollTop = this.scrollRef
    //         ? document.querySelector(this.scrollRef).scrollTop
    //         : 0
    //       let left =
    //         x + scrollLeft + window.pageXOffset - offset.left > crisis
    //           ? `${crisis}px`
    //           : x + scrollLeft + window.pageXOffset - offset.left + 'px'
    //       let top = y + scrollTop + window.pageYOffset - offset.top + 'px'
    //       return { left, top }
    //     }
    //   }
    //   return null
    // },
    list() {
      if (this.atwho.list) {
        return this.atwho.list.slice(0, 40);
      }
    }
  },
  watch: {
    "atwho.cur"(index) {
      if (index != null) {
        // cur index exists
        this.$nextTick(() => {
          this.scrollToCur();
        });
      }
    },
    members() {
      if (this.members.length) {
        this.$nextTick(() => {
          this.handleInput(true);
          this.allMember = this.members;
        });
      }
    },


    isShowList() {
      if (!this.isShowList) {
        this.atwho = {};
        this.$emit("hasAt", false);
      }
    }
  },

  methods: {
    itemName(v) {
      const { nameKey } = this;
      return nameKey ? v[nameKey] : v;
    },
    itemId(v, name, chunk) {
      if (name.trim() === chunk.trim()) {
        let id = v["id"];
        this.$emit("change-relatedUsers", { oprea: 0, id: id });
      }
    },
    isCur(index) {
      return index === this.atwho.cur;
    },

    handleItemHover(e) {
      if (this.hoverSelect) {
        this.selectByMouse(e);
      }
    },
    handleItemClick(e) {
      this.selectByMouse(e);
      this.insertItem();
    },
    handleDelete(e) {
      let sel = window.getSelection();
      let range = sel.getRangeAt(0);

      const r = range.cloneRange();
      r.collapse(true);
      r.setStart(r.endContainer, 0);
      const text = r.toString();
      console.log("text", text);
      if (text === "") return;
      const { at, index } = getAtAndIndex(text, ["@"]);

      console.log("at", index);
      if (index < 0) return;
      const chunk = text.slice(index + at.length);
      console.log("text::", text);
      console.log("chunk", chunk);
      const {
        atItems,
        allMember,
        suffix,
        deleteMatch,
        itemName,
        itemId
      } = this;
      if (text[text.length - 1] !== "@") {
        const has = allMember.some(v => {
          const name = itemName(v);
          const id = itemId(v, name, chunk);
          return deleteMatch(name, chunk, suffix);
        });
        console.log("has", has);
        if (!has) return;
        e.preventDefault();
        e.stopPropagation();
        let sels = window.getSelection();
        const rs = sels.getRangeAt(0);
        if (rs) {
          rs.setStart(rs.endContainer, index);
          rs.deleteContents();
          rs.collapse(false); // 参数在IE下必传
          sels.removeAllRanges();
          sels.addRange(rs);
        }
      }
    },
    // handleDelete(e) {
    //   const range = getPrecedingRange()
    //   console.log('range', range)
    //  if (range.endContainer.lastElementChild && range.endContainer.lastElementChild.localName === 'br') return
    //  console.log('delete::::::::')
    //   if (range) {
    //     const {
    //       atItems,
    //       allMember,
    //       suffix,
    //       deleteMatch,
    //       itemName,
    //       itemId
    //     } = this
    //     const text = range.toString()
    //     if (!text) return
    //     console.log('text', text)
    //     const { at, index } = getAtAndIndex(text, atItems)
    //     console.log('at', at, index)
    //     if (index > -1) {
    //       const chunk = text.slice(index + at.length)
    //       console.log('text::', text)
    //       if(text[text.length-1] !== '@'){
    //       const has = allMember.some(v => {
    //         const name = itemName(v)
    //         const id = itemId(v, name, chunk)
    //         return deleteMatch(name, chunk, suffix)
    //       })
    //       if (has) {
    //         if(!this.isShowList)  this.$emit('hasAt', true)
    //         e.preventDefault()
    //         e.stopPropagation()
    //         const r = getRange()
    //         if (r) {
    //           r.setStart(r.endContainer, index)
    //           r.deleteContents()
    //           applyRange(r)
    //           this.handleInput()

    //           // if(r.endContainer.nodeType ===  Node.TEXT_NODE) {
    //           //   console.log('r:::', r)
    //           //   if (r.endContainer.data === '') {
    //           //     console.log('empty', r)
    //           //     console.log('r.endContainer is empty', r.endContainer.data ,r.endContainer.wholeText)

    //           //     if (r.endContainer.parentElement.lastElementChild && r.endContainer.parentElement.lastElementChild.localName === 'img') {
    //           //     //  console.log('endContainer')
    //           //      r.endContainer.parentElement.removeChild(r.endContainer.parentElement.lastChild)
    //           //     } else {
    //           //       r.endContainer.parentElement.innerText = r.endContainer.parentElement.innerText.slice(0, index)
    //           //       placeCaretAtEnd(r.endContainer.parentElement)
    //           //     }
    //           //     return
    //           //     // this.$el.children['edit-box'].innerHTML = r.endContainer.wholeText.slice(0, index)
    //           //     // return placeCaretAtEnd(this.$el.children['edit-box'])
    //           //   }
    //           //   console.log('has range', r.endContainer, index)
    //           //   r.setStart(r.endContainer, index)
    //           //   r.deleteContents()
    //           //   applyRange(r)
    //           //   this.handleInput()
    //           // } else {
    //           //   console.log('nnnnnnnn', r)
    //           //   if (r.endContainer.lastElementChild && r.endContainer.lastElementChild.localName === 'img') {
    //           //     r.endContainer.removeChild(r.endContainer.lastChild)
    //           //   } else {
    //           //     r.endContainer.innerText = r.endContainer.innerText.slice(0, index)
    //           //     placeCaretAtEnd(r.endContainer)
    //           //   }
    //           // }
    //         }
    //       }
    //       }
    //     }
    //   }
    // },
    handleKeyUp(e) {
      if (e.keyCode !==8) return
      // if (e.keyCode === 8 && this.chatType === 2) {
      //   this.handleDelete(e);
      // }
    },
    handleKeyDown(e) {
      // if (!this.isShowList) return
      const { atwho } = this;
      if (atwho) {
        if (e.keyCode === 38 || e.keyCode === 40) {
          // ↑/↓
          if (!this.isShowList) return
          if (!(e.metaKey || e.ctrlKey)) {
            e.preventDefault();
            e.stopPropagation();
            this.selectByKeyboard(e);
          }
          return;
        }
        if (e.keyCode === 13 && this.isShowList) {
          // this.$log.debug("enter in at::");
          // enter
          this.insertItem();
          e.preventDefault();
          e.stopPropagation();
          return;
        }
        if (e.keyCode === 27 && this.isShowList) {
          // esc
          this.closePanel();
          return;
        }
      }

      // 为了兼容ie ie9~11 editable无input事件 只能靠keydown触发 textarea正常
      // 另 ie9 textarea的delete不触发input
      // const isValid = (e.keyCode >= 48 && e.keyCode <= 90) || e.keyCode === 8;
      // if (isValid) {
      //   console.log('isValid:::', isValid)
      //   setTimeout(() => {
      //     this.handleInput();
      //   }, 50);
      // }

      // if (e.keyCode === 8 && this.chatType === 2) {
      //   let selectText = window.getSelection().toString();
      //   if (selectText) {
      //     this.$emit('handleDeleteAll', selectText)
      //   }
      // }    	
    },

    // compositionStart -> input -> compositionEnd
    handleCompositionStart() {
      this.hasComposition = true;
    },
    handleCompositionEnd() {
      this.hasComposition = false;
      this.handleInput();
    },
    handleInput(keep) {
      if (this.hasComposition) return;
      if (!this.isShowList) return;
      console.log("step1===>");
      setTimeout(() => {
        const range = getPrecedingRange();
        if (range) {
          const { atItems, avoidEmail, allowSpaces } = this;
          let show = true;
          const text = range.toString();
          console.log("text:::", text);
          const { at, index } = getAtAndIndex(text, atItems);
          if (index < 0) show = false;
          const prev = text[index - 1];

          const chunk = text.slice(index + at.length, text.length);
          if (avoidEmail) {
            // 上一个字符不能为字母数字 避免与邮箱冲突
            // 微信则是避免 所有字母数字及半角符号
            if (/^[a-z0-9]$/i.test(prev)) show = false;
          }

          if (!allowSpaces && /\s/.test(chunk)) {
            show = false;
          }

          // chunk以空白字符开头不匹配 避免`@ `也匹配
          if (/^\s/.test(chunk)) show = false;

          if (!show) {
            this.closePanel();
          } else {
            const { filterMatch, itemName } = this;

            if (!keep && chunk.length > 0) {
              this.$emit("at", chunk);
            }
            const members = this.members.length ? this.members : this.allMember;
            if (text[text.length - 1] === "@") {
              this.openPanel(members, range, index, at);
              show = false;
            } else {
              const matched = members.filter(v => {
                const name = itemName(v);
                return filterMatch(name, v.pingyin, chunk, at);
              });
              if (matched.length) {
                this.openPanel(matched, range, index, at);
                show = false;
              } else {
                this.closePanel();
              }
            }
          }
        }
      });
    },

    closePanel() {
      if (this.isShowList) this.$emit("hasAt", false);
      if (this.atwho) this.atwho = null;
    },
    openPanel(list, range, offset, at) {
      const fn = () => {
        const r = range.cloneRange();
        r.setStart(r.endContainer, offset + at.length); // 从@后第一位开始
        // todo: 根据窗口空间 判断向上或是向下展开
        const rect = r.getClientRects()[0];
        this.atwho = {
          range,
          offset,
          list,
          x: rect.left,
          y: rect.top - 4,
          cur: 0 // todo: 尽可能记录
        };
      };
      if (this.atwho) {
        fn();
      } else {
        // 焦点超出了显示区域 需要提供延时以移动指针 再计算位置
        setTimeout(fn, 10);
      }
    },

    scrollToCur() {
      if (this.isShowList) {
        const curEl = this.$refs.cur[0];
        const scrollParent = curEl.parentElement.parentElement; // .atwho-view
        scrollIntoView(curEl, scrollParent);
      }
    },
    selectByMouse(e) {
      const el = closest(e.target, d => {
        return d.getAttribute("data-index");
      });
      const cur = +el.getAttribute("data-index");
      this.atwho = {
        ...this.atwho,
        cur
      };
    },
    selectByKeyboard(e) {
      const offset = e.keyCode === 38 ? -1 : 1;
      const { cur, list } = this.atwho;
      const nextCur = this.loop
        ? (cur + offset + list.length) % list.length
        : Math.max(0, Math.min(cur + offset, list.length - 1));
      this.atwho = {
        ...this.atwho,
        cur: nextCur
      };
    },

    // todo: 抽离成库并测试
    insertText(text, r) {
      r.deleteContents();
      const node = r.endContainer;
      if (node.nodeType === Node.TEXT_NODE) {
        const cut = r.endOffset;
        node.data = node.data.slice(0, cut) + text + node.data.slice(cut);
        r.setEnd(node, cut + text.length);
      } else {
        console.log("text", text);
        const t = document.createTextNode(text);
        r.insertNode(t);
        r.setEndAfter(t);
      }
      r.collapse(false); // 参数在IE下必传
      applyRange(r);
    },
    insertItem() {
      // const { list, cur } = this.atwho;
      // this.$emit('insertAt', {id: list[cur].id})
      // var source = '<span class="at-image"></span>'
      // insertNode(this.$refs.editArea, source)
      // let node = 
      const { range, offset, list, cur } = this.atwho;
      const { suffix, atItems, itemName } = this;
      const r = range.cloneRange();
      const text = range.toString();
      const { at, index } = getAtAndIndex(text, atItems);
      console.log('index', index)
      const start = index + at.length; // 从@后第一位开始
      console.log('start', start)
      r.setStart(r.endContainer, start - 1);
      // hack: 连续两次 可以确保click后 focus回来 range真正生效
      applyRange(r);
      applyRange(r);
      r.deleteContents();
      this.$emit('insertAt', {id: list[cur].id})
      // var source = '<span class="at-image"></span>'
      // insertNode(this.$refs.editArea, source)
      // // hack: 连续两次 可以确保click后 focus回来 range真正生效
      // applyRange(r);
      // applyRange(r);
      // const t = itemName(list[cur]) + suffix;
      // const id = list[cur].id;
      // this.$emit("change-relatedUsers", { oprea: 1, id: id });
      // this.$Service.log(`insert atId   ${id}`)
      // this.insertText(t, r);
      // this.handleInput();
    }
  }
};
</script>
