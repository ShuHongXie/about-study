function add() {
  return 123;
}

exports.add = add;
module.exports = add;

console.log(module.exports, exports);
