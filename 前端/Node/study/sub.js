process.on("message", function (m) {
  console.log("子进程获取到了信息:", m);
});
process.send({ foo: "bar" });
