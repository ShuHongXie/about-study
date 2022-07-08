## Why did i write?

每次面试都会被面试官问到 diff 算法，每次都看别人文章，过了就忘。最近抽空自己看看源码，自己在不
借助其他人文章思路的情况下，自己死磕源码，总结出自己的一些心得，ps：下次再也不用一直找别人文章看

## 从问题说起？

1. diff 算法是怎么对比的？
2. 遇到了 v-for 绑定的 key 值为 index 导致删除列表的某一项，删除的却是始终是最后一项的情况。
3. 没绑定 index，删除后也会出现始终删除最后一项的问题。
4. 官网说的默认使用旧地复用在哪里体现？

具体看下图代码

```html
<div class="content-body">
  <ul>
    <li v-for="(item,index) in selectionConditionList" :key="index">
      <v-selection-condition-list></v-selection-condition-list>
      <button @click="deleteSelectionCondition(index)">删除</button>
    </li>
  </ul>
  <button @click="addNewSelectionTask">新建任务</button>
</div>

<script>
  const vSelectionConditionList = {
    data() {
      return {
        inputName: Math.random(),
      };
    },
    template: `<input type="text" :value="inputName">`,
  };
  var app = new Vue({
    el: ".content-body",
    data() {
      return {
        selectionConditionList: [],
      };
    },
    methods: {
      // 添加
      addNewSelectionTask() {
        this.selectionConditionList.push({});
      },
      // 删除
      deleteSelectionCondition(index) {
        console.log("delete.." + index);
        this.selectionConditionList.splice(index, 1);
      },
    },
    components: {
      vSelectionConditionList,
    },
  });
</script>
```

## 解决问题先看看源码

下面代码会去掉一些非核心的代码

/more

```js
// src/core/vdom/patch.js
function updateChildren(
  parentElm,
  oldCh,
  newCh,
  insertedVnodeQueue,
  removeOnly
) {
  let oldStartIdx = 0; // 旧起始标记 默认0
  let newStartIdx = 0; // 新起始标记 默认0
  let oldEndIdx = oldCh.length - 1; // 旧的最后一个的索引
  let oldStartVnode = oldCh[0]; // 旧的第一个节点
  let oldEndVnode = oldCh[oldEndIdx]; // 旧的最后一个节点
  let newEndIdx = newCh.length - 1; // 新的最后一个的索引
  let newStartVnode = newCh[0]; // 新的第一个节点
  let newEndVnode = newCh[newEndIdx]; // 新的最后一个节点
  let oldKeyToIdx, idxInOld, vnodeToMove, refElm;

  // removeOnly是一个特殊标志，仅由<transition group>使用，以确保在离开转换期间被删除的元素保持在正确的相对位置
  const canMove = !removeOnly;
  // 判断新节点是否存在重复的key
  if (process.env.NODE_ENV !== "production") {
    checkDuplicateKeys(newCh);
  }
  // 起始对比
  // 当旧起始index小于等于旧的旧的结束index 并且 新起始小于等于新结束index
  while (oldStartIdx <= oldEndIdx && newStartIdx <= newEndIdx) {
    // 如果旧起始节点未定义
    if (isUndef(oldStartVnode)) {
      // 旧起始节点下标进1位 +1
      oldStartVnode = oldCh[++oldStartIdx]; // Vnode has been moved left
    } else if (isUndef(oldEndVnode)) {
      // 如果旧的结束节点未定义 那么下标就退一位 -1
      oldEndVnode = oldCh[--oldEndIdx];
    } else if (sameVnode(oldStartVnode, newStartVnode)) {
      // 如果新旧起始节点是同个节点 那么就进行下一层的对比 并且两者下标都进一位 +1
      patchVnode(
        oldStartVnode,
        newStartVnode,
        insertedVnodeQueue,
        newCh,
        newStartIdx
      );
      oldStartVnode = oldCh[++oldStartIdx];
      newStartVnode = newCh[++newStartIdx];
    } else if (sameVnode(oldEndVnode, newEndVnode)) {
      // 如果新旧结束节点是同个节点 那么就进行下一层的对比 并且两者下标都退一位 1
      patchVnode(
        oldEndVnode,
        newEndVnode,
        insertedVnodeQueue,
        newCh,
        newEndIdx
      );
      oldEndVnode = oldCh[--oldEndIdx];
      newEndVnode = newCh[--newEndIdx];
    } else if (sameVnode(oldStartVnode, newEndVnode)) {
      // 如果旧起始节点和新结束是同个节点，那么进行下一层对比 旧起始进一位+1 新起始节点退一位-1
      // 并且把 那么就把旧起始节点插入到旧结束节点的前面
      // Vnode moved right
      patchVnode(
        oldStartVnode,
        newEndVnode,
        insertedVnodeQueue,
        newCh,
        newEndIdx
      );
      canMove &&
        nodeOps.insertBefore(
          parentElm,
          oldStartVnode.elm,
          nodeOps.nextSibling(oldEndVnode.elm)
        );
      oldStartVnode = oldCh[++oldStartIdx];
      newEndVnode = newCh[--newEndIdx];
    } else if (sameVnode(oldEndVnode, newStartVnode)) {
      // 如果旧结束和新起始是同个节点，那么进行下一层对比 旧结束退一位-1 新起始节点进一位+1
      // 并且把 那么就把旧起始节点插入到旧结束节点的位置
      // Vnode moved left
      patchVnode(
        oldEndVnode,
        newStartVnode,
        insertedVnodeQueue,
        newCh,
        newStartIdx
      );
      canMove &&
        nodeOps.insertBefore(parentElm, oldEndVnode.elm, oldStartVnode.elm);
      oldEndVnode = oldCh[--oldEndIdx];
      newStartVnode = newCh[++newStartIdx];
    } else {
      // 如果旧数据没有绑定key值
      if (isUndef(oldKeyToIdx))
        // oldKeyToIdx存储当前旧数据区间的key值为key当前的索引
        oldKeyToIdx = createKeyToOldIdx(oldCh, oldStartIdx, oldEndIdx);
      // 如果当前新数据有key的话  idxInOld就等于oldKeyToIdx的key项的索引
      // findIdxInOld拿当前新开始节点，通过判断旧起始-结束节点之中有没有其位置，找出当前新开始在旧中的位置

      // 无key情况下
      //    如果新节点不存在于旧节点中，那么就作为新增节点加入插入到oldStartNode前面
      // 有key情况下 直接获取当前节点在旧的之前的位置
      idxInOld = isDef(newStartVnode.key)
        ? oldKeyToIdx[newStartVnode.key]
        : findIdxInOld(newStartVnode, oldCh, oldStartIdx, oldEndIdx);
      // 如果如果没有index 那么就直接创建元素
      if (isUndef(idxInOld)) {
        // 如果没有找到 那么就在当前索引前面插入新元素
        createElm(
          newStartVnode,
          insertedVnodeQueue,
          parentElm,
          oldStartVnode.elm,
          false,
          newCh,
          newStartIdx
        );
      } else {
        // 有index就直接复用元素
        vnodeToMove = oldCh[idxInOld];
        // 同元素情况下
        if (sameVnode(vnodeToMove, newStartVnode)) {
          patchVnode(
            vnodeToMove,
            newStartVnode,
            insertedVnodeQueue,
            newCh,
            newStartIdx
          );
          oldCh[idxInOld] = undefined;
          // 在前面插入
          canMove &&
            nodeOps.insertBefore(parentElm, vnodeToMove.elm, oldStartVnode.elm);
        } else {
          // same key but different element. treat as new element
          createElm(
            newStartVnode,
            insertedVnodeQueue,
            parentElm,
            oldStartVnode.elm,
            false,
            newCh,
            newStartIdx
          );
        }
      }
      newStartVnode = newCh[++newStartIdx];
    }
  }
  // 如果对比完成
  // 如果旧起始大于旧结束 说明新的里面的东西都是新增的 就加入
  if (oldStartIdx > oldEndIdx) {
    refElm = isUndef(newCh[newEndIdx + 1]) ? null : newCh[newEndIdx + 1].elm;
    addVnodes(
      parentElm,
      refElm,
      newCh,
      newStartIdx,
      newEndIdx,
      insertedVnodeQueue
    );
  } else if (newStartIdx > newEndIdx) {
    // 如果新开始大于新结束，那说明旧的里面的dom是被删除 就移除调
    removeVnodes(oldCh, oldStartIdx, oldEndIdx);
  }
}
```

## diff 算法是怎么 diff？

下面用一个例子来做一层模拟 更直观地展示，**上方为 oldVnode，下方为 newVnode，key 为内容数字，且唯一**

![](http://www.xiesmallxie.cn/20211026171121.png)

Step1: 新头旧头，新尾旧尾，新头旧尾，新尾旧头对比后，发现并不一致，进入源码中的最后一个 else 内部，进入之后
oldKeyToIdx 为 undefined，初始化 oldKeyToIdx 的值。因为 newStartVnode 有值，idxInOld = oldKeyToIdx[newStartVnode.key]等于 1，调用 createElement 在 oldStartVnode 前面插入 newStartVnode，newStartIndex++。此时 oldStartIndex：0,oldEndIndex：2，newStartIndex：1，newEndIndex：3

![](http://www.xiesmallxie.cn/20211026171120.png)

Step2: 新头旧头对比后发现都为 1，一致 newStartIndex,oldStartIndex 都+1，当前层不进行复用/排列操作，保存本位。此时 oldStartIndex：1,oldEndIndex：2，newStartIndex：2，newEndIndex：3

![](http://www.xiesmallxie.cn/20211026171120.png)

Step3: 旧尾新头对比后发现都为 3，newStartIndex+1，oldEndIndex-1，此时 oldStartIndex：1,oldEndIndex：1，newStartIndex：3，newEndIndex：3

![](http://www.xiesmallxie.cn/20211026171120.png)

Step3: 头尾相比发现都不一致，进入 else 内部，oldKeyToIdx 数组内部没有第 4 个的值 所以在 newStartIndex 前面插入 4，newStartIdx+1，此时 newStartIndex > newOldIndex,就移除旧数组的 oldStartIdx 到 oldEndIdx 的 vnode，也就是 2，最后返回 2134
![](http://www.xiesmallxie.cn/20211026171119.png)
![](http://www.xiesmallxie.cn/20211026171118.png)

从上图源码来看，可以得出，**diff 算法会依照固定的判断同层级 Vnode 的顺序进行头头，尾尾，头尾，尾头的比较不断收缩 4 个定义的下标的位置
来进行 dom 的重排和复用操作**

## 解决第 2，3 个问题,探究下本质

为什么会出现 key 绑定为 index，或者不绑定情况下删除会删除最后一项问题呢，
这其实涉及到了 vnode 的渲染原理

- 假如按照上面代码通过调用编译后的 render 函数调用 \_l 方法也就是 renderList 调用 createElement 方法初始化了多个 vnode
  ，在绑定 key 为 index 的情况下 增加 3 个删除第一个，打印 vnode 大概是这样的，

```js
/*
旧vnode
children: Array(3)
0: VNode {tag: "li", data: {…}, children: Array(3), text: undefined, key: 0, …}
1: VNode {tag: "li", data: {…}, children: Array(3), text: undefined, key: 1, …}
2: VNode {tag: "li", data: {…}, children: Array(3), text: undefined, key: 2, …}
*

/*
新vnode
children: Array(2)
0: VNode {tag: "li", data: {…}, children: Array(3), text: undefined, key: 0, …}
1: VNode {tag: "li", data: {…}, children: Array(3), text: undefined, key: 1, …}

*/
```

由上可知，key 是不变的，但是实际上 dom 内容已经变了。这就会导致在头头对比之中因为双方 key 一致，从而判断为同个 vnode，会使 newStartIdx 和 oldStartIndex 一致向右进 1, 最后 newStarteIndex > newEndIndex, 导致 oldStartIndex 到 oldEndIndex 之间的 vnode 被删除，所以这才会出现删除的总是最后一项的情况。没有绑定 key 时情况也是如此。具体如下图所示

![](http://www.xiesmallxie.cn/20211026153950.png)

## 解决第 4 个问题，就地复用在哪里得到体现？

源码中，如果新的节点在旧的节点列表上有出现的 ，那么就会存储当前 Vnode，直接插入到 dom 前面，复用旧 Vnode，不创建新的 dom。如下源码：

```js
function updateChildren() {
  // 拿到旧代码 直接存储
  vnodeToMove = oldCh[idxInOld];
  if (sameVnode(vnodeToMove, newStartVnode)) {
    patchVnode(
      vnodeToMove,
      newStartVnode,
      insertedVnodeQueue,
      newCh,
      newStartIdx
    );
    oldCh[idxInOld] = undefined;
    // 在前面插入
    canMove &&
      nodeOps.insertBefore(parentElm, vnodeToMove.elm, oldStartVnode.elm);
  }
}
```

> 以上就是我看源码得出的结论，有疑问的小伙伴可以在下方留言。thanks！！！
