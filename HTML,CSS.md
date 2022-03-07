### 什么是 BFC?

BFC 是 CSS 布局的一个概念，是一个环境，里面的元素不会影响外面的元素

### link 和@import 的区别

1. link 属于 XHTML 标签，而@import 完全是 css 提供的一种方式。
2. 加载顺序的差别：当一个页面被夹在的时候（就是被浏览者浏览的时候），link 引用的 CSS 会同时被加载，而@import 引用的 CSS 会等到页面全部被下载完再加载。所以有时候浏览@import 加载 CSS 的页面时会没有样式（就是闪烁），网速慢的时候还挺明显。

### href 和 src 的区别

href 用于建立当前页面与引用资源之间的关系（链接），而 src 则会替换当前标签。遇到 href，页面会并行加载后续内容；而 src 则不同，浏览器需要加载完毕 src 的内容才会继续往下走。

### AMD 和 CMD 的区别

AMD 推崇依赖前置、提前执行，CMD 推崇依赖就近、延迟执行

### ES6 模块与 CommonJS 模块的差异

CommonJS 模块输出的是一个值的浅拷贝，ES6 模块输出的是值的引用。

#### CommonJS 模块是运行时加载，ES6 模块是编译时输出接口。

运行时加载: CommonJS 模块就是对象；即在输入时是先加载整个模块，生成一个对象，然后再从这个对象上面读取方法，这种加载称为“运行时加载”。

编译时加载: ES6 模块不是对象，而是通过 export 命令显式指定输出的代码，import 时采用静态命令的形式。即在 import 时可以指定加载某个输出值，而不是加载整个模块，这种加载称为“编译时加载”