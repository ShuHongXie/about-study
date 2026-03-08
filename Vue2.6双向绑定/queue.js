const queue = [];
const has = {};
let flush = (wait = false);

function nextTick(fn) {
  Promise.resolve().then(fn);
}

function flushQueue() {
  flush = true;
  for (const watcher of queue) {
    watcher.run();
  }
  wait = flush = false;
}

function queueWatcher(watcher) {
  console.log(has, watcher.id);
  if (!has[watcher.id]) {
    has[watcher.id] = watcher;
    // if (!flush) {
    //   flush = true;

    // }
    queue.push(watcher);
  }
  if (!wait) {
    wait = true;
    nextTick(flushQueue);
  }
}
