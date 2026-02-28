const buf = new Buffer("test", "utf-8");
console.log(buf);

const fs = require("fs");
var rs = fs.createReadStream("./test.md", {
  highWaterMark: 11,
  encoding: "utf8",
});
rs.setEncoding("utf8");
let data = "";
rs.on("data", function (chunk) {
  data += chunk;
});
rs.on("end", function () {
  console.log(data);
});
