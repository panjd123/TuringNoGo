# 来自工程上的建议

> 这份文档可以视作拓展阅读，花一天扫一眼即可

## 面向对象

一本很知名的书曾提出 [设计模式：面向对象设计的六大原则](https://www.cnblogs.com/yeya/p/10655760.html) 不过这里面的要求可能过于苛刻了。

本次实验，我建议从两个点来考虑怎么面向对象设计。同时不一定要完全遵守，而是根据实际情况和自己的代码水平来选择。

### 解耦

通俗来讲，假如你实现一个**联网**，**带可视化界面**的**棋类AI**，现在有一个需求只要本地运行的AI，你的代码是否能够分离出来对应的类，或几个子类重新组装在一起，分离出来的内容，不包含联网或者可视化。可以就是低耦合度，不可以就是高耦合度。

一种高耦合的情况是：在实现下棋的时候，每个棋子就是一个按钮，导致如果想下棋，就得带着GUI库走。或者是网络库的那些 socket 也绑定在下棋里，要去掉得删代码。

低耦合的情况是：下棋的逻辑被单独包装成一个类，下棋的时候，先问下棋的逻辑这样走是否合法，如果合法，再把这个棋子的位置传给GUI类，让它显示出来。棋子位置的记录等等都保存在下棋的逻辑类里。同时下棋类被派生出带网络交互的类，这个类再和网络库产生联系。

把高耦合变成低耦合就是解耦

> 提示：在基类里预留未实现的接口，有时候可以避免派生类重写方法，同时又保证解耦

### 复用

相同功能的代码封装成一个函数或类，以重复使用。

这样的好处是，如果你的代码有bug，你只需要修改一处，就能够让所有的地方都不会有bug了。

> 提示：这会是大多数你觉得莫名其妙的BUG出现的原因之一，因为你第一眼以为这段代码或这个逻辑的BUG已经检查过了，更难受的是，你第一眼甚至不一定能分出来哪些是改过的对的，哪些是没改过的错的。

如果有一个本地棋盘，一个联机棋盘，他们的逻辑有很多重复的地方，又有一些不同，你就可以考虑在他们之上再抽象一个棋盘出来了，或者用复杂的继承简单的。

## doxygen

doxygen 是一种跨语言的文档管理系统，它可以借由一定格式的注释生成对应的文档。

如果你想要代码的注释规范化的同时，生成API接口的文档，甚至是类之间继承的关系图，使用这个标准是不错的选择。

[简要教程](https://zhuanlan.zhihu.com/p/510925324)

---

在 VSCode 中，借由 doxygen 格式，你可以做到这样：

![](imgs/doxygen.png)

有一些是 VSCode 不支持的，比如 `@todo`，但可以用在 doxygen 文档中。

![](imgs/doxygen-doc.png)

## C++ style

每个人都有自己的代码风格，例如怎么给变量命名，文件命名，怎么注释，甚至是能不能用 `using namespace std`，怎么用。

业界公认的标准是 [Google C++ style guide](https://google.github.io/styleguide/cppguide.html)，中文版本是 [C++ 风格指南](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/contents/)，一个简化版 [一张图总结Google C++编程规范](https://blog.csdn.net/zyy617532750/article/details/81264648)。

如果你们小组需要一个统一的风格，可以参考这个。事实上，我建议所有人都了解这个风格。

## C++ standard

大家可以自行决定要不要自学C++现代标准中的语法和特性

```cpp
// bad style
std::vector< std::vector<int> > table;
for(size_t i = 0; i < table.size(); i++) {
    for(size_t j = 0; j < table[i].size(); j++) {
        int cell = table[i][j];
        std::cout << cell << std::endl;
    }
}

// good style
std::vector< std::vector<int> > table1;
for(auto row : table1) { // range-based for loop
    for(auto cell : row) {
        std::cout << cell << std::endl;
    }
}

//best style
using Row = std::vector<int>;
using Table = std::vector<Row>;

Table table2;
for(Row row : table2) {
    for(int cell : row) {
        std::cout << cell << std::endl;
    }
}
```

你可以参考这一篇文章 [现代C++标准浅览](https://zhuanlan.zhihu.com/p/595888665)，学习其中你觉得有用的，这可能会大幅加快你们的编程速度。

## Effective C++ 系列

曾有人说，C++程序员可以分为两类，读过 Effective C++ 的和没读过的。如果说 Google C++ style guide 是指导代码的外表应该怎样呈现。那么Effective C++ 就是更深刻地指出了我们应该如何使用 C++ 的各种特性。

还有一种说法，Effective C++ 指出了正确使用 C++ 的最低限度。

这里的正确指的是，比如：使用声明一个常量用 `const float Pi=3.14;` 而不是 `#define Pi 3.14`。从语法和最终执行效果上看，二者几乎没有区别，但从更深刻的角度去看，`const` 相比 `#define` 几乎到处是优点。

> `#define` 和 `const` 的不同
> - `const` 的内存占用更小。`const` 定义常量从汇编的角度来看，只是给出了对应的内存地址，而不是象`#define` 一样给出的是立即数，所以，`const` 定义的常量在程序运行过程中只有一份拷贝（因为是全局的只读变量，存在静态区），而 `#define` 定义的常量在内存中有若干个拷贝
> - `const` 的效率更高。 编译器通常不为普通 `const` 常量分配存储空间，而是将它们保存在符号表中，这使得它成为一个编译期间的常量，没有了存储与读内存的操作，使得它的效率也很高
> - `const` 更安全。`const` 常量有数据类型，而宏常量没有数据类型。编译器可以对前者进行类型安全检查。而对后者只进行字符替换，没有类型安全检查，并且在字符替换可能会产生意料不到的错误（边际效应）。
> - `const` 更方便调试。有些集成化的调试工具可以对 `const` 常量进行调试，但是不能对宏常量进行调试。

Effective C++ 系列正是指导什么叫做正确，其大致对应三本书：

- 《Effective C++》
- 《More Effective C++》
- 《Effective Modern C++》

全读完是不太可能的，不过我找到了一个人做的笔记，将三本书的内容全部集中到了一起，相比之下已经是非常简短的了，如果你们有兴趣可以读一读。

https://github.com/Tianji95/effective-cpp-note


> 后记：
> 
> 以上的一些内容其实超过了本课程的要求，然而又几乎不会有一门课去教，但学习这些东西最有价值的时机或许就是在写一个工程的时候，也就是程设2的大作业。所以也许放在这里是最合适的。
>
> 如果以后你的编程涉及C++，尤其是在工业界，那么以上内容将非常有价值。