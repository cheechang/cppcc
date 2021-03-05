// bug report: https://github.com/vuejs/awesome-vue/pull/1028
// https://developer.mozilla.org/en-US/docs/Web/API/Element/scrollIntoViewIfNeeded
export function scrollIntoView(el, scrollParent, upOrdown) {
  if (el.scrollIntoViewIfNeeded) {

    //  el.scrollIntoView(upOrdown? upOrdown : false) // alignToCenter=false
    el.scrollIntoViewIfNeeded(upOrdown)
  } else {
    // should not use `el.scrollIntoView(false)` // alignToTop=false
    // bug report: https://stackoverflow.com/questions/11039885/scrollintoview-causing-the-whole-page-to-move
    const diff = el.offsetTop - scrollParent.scrollTop
    if (diff < 0 || diff > scrollParent.offsetHeight - el.offsetHeight) {
      scrollParent = scrollParent || el.parentElement
      scrollParent.scrollTop = el.offsetTop
    }
  }
}

export function applyRange(range) {
  const selection = window.getSelection()
  if (selection) { // 容错
    selection.removeAllRanges()
    selection.addRange(range)
  }
}
export function getRange() {
  const selection = window.getSelection()
  if (selection && selection.rangeCount > 0) {
    return selection.getRangeAt(0)
  }
}

export function getAtAndIndex(text, ats) {
  return ats.map((at) => {
    return {
      at,
      index: text.lastIndexOf(at)
    }
  }).reduce((a, b) => {
    return a.index > b.index ? a : b
  })
}

/* eslint-disable */
// http://stackoverflow.com/questions/26747240/plain-javascript-replication-to-offset-and-position
export function getOffset(element, target) {
  // var element = document.getElementById(element),
  //     target  = target ? document.getElementById(target) : window;
  target = target || window
  var offset = {
      top: element.offsetTop,
      left: element.offsetLeft
    },
    parent = element.offsetParent;
  while (parent != null && parent != target) {
    offset.left += parent.offsetLeft;
    offset.top += parent.offsetTop;
    parent = parent.offsetParent;
  }
  return offset;
}
// http://stackoverflow.com/questions/3972014/get-caret-position-in-contenteditable-div
export function closest(el, predicate) {
  /* eslint-disable */
  do
    if (predicate(el)) return el;
  while (el = el && el.parentNode);
}
// http://stackoverflow.com/questions/15157435/get-last-character-before-caret-position-in-javascript
// 修复 "空格+表情+空格+@" range报错 应设(endContainer, 0)
// stackoverflow上的这段代码有bug
export function getPrecedingRange() {
  const r = getRange()
  if (r) {
    const range = r.cloneRange()
    range.collapse(true)
    // var el = closest(range.endContainer, d => d.contentEditable)
    // range.setStart(el, 0)
    range.setStart(range.endContainer, 0)
    return range
  }
}
/* eslint-enable */
export function placeCaretAtEnd(el) {
  el.focus();
  if (typeof window.getSelection != "undefined" &&
    typeof document.createRange != "undefined") {
    var range = document.createRange();
    range.selectNodeContents(el);
    range.collapse(false);
    var sel = window.getSelection();
    sel.removeAllRanges();
    sel.addRange(range);
  } else if (typeof document.body.createTextRange != "undefined") {
    var textRange = document.body.createTextRange();
    textRange.moveToElementText(el);
    textRange.collapse(false);
    textRange.select();
  }
}
export function insertNode(el, str) {
  // el.focus();
  let selection = window.getSelection ? window.getSelection() : document.selection;
  let range = selection.createRange ? selection.createRange() : selection.getRangeAt(0);
  if (!window.getSelection) {
    el.focus();
    let selection = window.getSelection ? window.getSelection() : document.selection;
    let range = selection.createRange ? selection.createRange() : selection.getRangeAt(0);
    range.pasteHTML(str);
    range.collapse(false);
    range.select();
  } else {
    el.focus();
    range.collapse(false);
    if (range.startContainer.className === 'edit-textarea' || range.commonAncestorContainer.parentElement.className === 'edit-textarea') {
      let hasR = range.createContextualFragment(str);
      let hasRlastChild = hasR.lastChild;
      range.insertNode(hasR);
      if (hasRlastChild) {
        range.setEndAfter(hasRlastChild);
        range.setStartAfter(hasRlastChild)
      }
      selection.removeAllRanges();
      selection.addRange(range)
    }
  }
}

export function insertAtCursor(dom, html) {
  console.log('dom', dom, html)
  var sel = null;
  var range = null;
  if (window.getSelection) {
    dom.focus()
    // IE9 或 非IE浏览器  
    sel = window.getSelection();
    if (sel.getRangeAt && sel.rangeCount) {
      range = sel.getRangeAt(0);
      range.deleteContents();
      // Range.createContextualFragment() would be useful here but is  
      // non-standard and not supported in all browsers (IE9, for one)  
      var el = document.createElement("div");
      el.innerHTML = html;
      var frag = document.createDocumentFragment();
      var node = null;
      var lastNode = null;
      while ((node = el.firstChild)) {
        lastNode = frag.appendChild(node);
      }
      range.insertNode(frag);
      // Preserve the selection  
      if (lastNode) {
        range = range.cloneRange();
        range.setStartAfter(lastNode);
        range.collapse(true);
        sel.removeAllRanges();
        sel.addRange(range);
      }
      console.log('range', range)
    }
  } else if (document.selection && document.selection.type != "Control") {
    // IE < 9  
    document.selection.createRange().pasteHTML(html);
  }
}
export function getTextWidth(fontSize,fontFamily,text){
  var span = document.createElement("span");
  var result = {};
  result.width = span.offsetWidth;
  result.height = span.offsetHeight;
  span.style.visibility = "hidden";
  span.style.fontSize = fontSize;
  span.style.fontFamily = fontFamily;
  span.style.display = "inline-block";
  document.body.appendChild(span);
  if(typeof span.textContent != "undefined"){
    span.textContent = text;
  }else{
    span.innerText = text;
  }
  result.width = parseFloat(window.getComputedStyle(span).width) - result.width;
  result.height = parseFloat(window.getComputedStyle(span).height) - result.height;
  return result;
}

  // Canvas居中写字，参数（context对象，要写的字，字体，颜色，绘制的高度）
 export function canvasText(_paint, _text, _fontSzie, _color, _width, _height) {
    _paint.font = _fontSzie;
    _paint.fillStyle = _color;
    _paint.textAlign = "center";
    _paint.textBaseline = "middle";
    _paint.fillText(_text,  _width , _height);
  }

  export function isInVisibleArea(elem){
    if(!elem || !elem.getBoundingClientRect) return false;

    var rect = elem.getBoundingClientRect();
    
    if(rect.top < window.innerHeight && rect.bottom > 0){
        return true;
    }else{
        return false;
    }
  }