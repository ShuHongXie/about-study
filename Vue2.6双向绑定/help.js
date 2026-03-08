function installHelp(target) {
  target._v = createTextVNode;
  target._s = function toString(val) {
    console.log(this);
    return val ? String(val) : "";
  };
}
