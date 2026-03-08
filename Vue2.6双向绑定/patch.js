function initPatch() {
  function createElement() {}
  return function patch(oldVnode, vnode) {
    if (isDef(oldVnode)) {
      // 顶层实例为真正dom的时候把他转换成vnoide
      if (vnode.nodeType) {
        oldVnode = new vnode(oldVnode.tagName, {}, [], undefined, oldVnode);
      }
      const oldElm = oldVnode.elm;
      const parentElm = oldElm.parentNode;
    } else {
      createElement(vnode);
    }
  };
}
