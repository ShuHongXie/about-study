function debounce(fn, time) {
  let timer;
  return function () {
    const args = arguments;
    console.log(args);

    if (timer) {
      clearTimeout(timer);
    }

    timer = setTimeout(() => {
      fn.apply(this, args);
    }, time);
  };
}

setTimeout((_) => console.log(4));

new Promise((resolve) => {
  resolve();
  console.log(1);
}).then((_) => {
  console.log(3);
  Promise.resolve()
    .then((_) => {
      console.log("before timeout");
    })
    .then((_) => {
      Promise.resolve().then((_) => {
        console.log("also before timeout");
      });
    });
});

console.log(2);
