# 3月7日上机课

> 由于助教不幸~~疑似~~感染甲流，遂大作业的第一节上机课内容仍然以文档的形式提供（讲道理，应该都更喜欢文档吧）。

## 阶段0回顾

### commit message

`commit message` 应该写改动的内容，比如修复了功能，添加了文件。

和库管理员交流的话应该是放在 `pr` 的评论里。

有几个组用 `commit message` 和我聊天，不太应该。

### 命令行界面 Command-line interface(CLI)

命令行界面是在图形用户界面得到普及之前使用最为广泛的用户界面，输入命令，然后回车，就会执行命令。命令行本质上是和图形界面中点点划划平行的一种操作计算机的逻辑。

使用 Git 并不是只能用 `Git Bash`，
`git` 是安装在电脑上的，而不是在 `Git Bash` 里的，所以任何命令行界面都可以用 `Git`，比如 `Windows PowerShell`，`cmd`，`Linux` 的 `bash` 等等。

如果用过 `dev-c++`，那么 `cmd` 就不陌生了，它就是每次运行的时候弹出来的黑框框。

> 不过不同的命令行，它的显示内容可能不一样，比如 `Git Bash` 里就额外显示了很多 `git` 相关的信息。

![](imgs/Bash_screenshot.png)

## 大作业总览

[overview](../../task/1.1-overview.md) 里已经对大作业整体要求做了很详细的说明，以下是一些强调。

### 工作流

我们要求用 Git 协作，具体工作流任意，比如你们可以每个人全在同一个 branch 上开发，或者每个人开一个 branch 再合并，或者你们也可以用 fork 工作流。

### 面向对象编程

我们要求面向对象编程，尽量用类，如果你不用类来写我们视作没有按规定完成大作业。

具体地，你可以参考下图某个跳棋程序的类的关系，其中虚线表示包含关系，实线表示继承关系，圈箭头表示功能。

![](imgs/class.jpg)

### 代码风格

这个话题以后如果我看到了，就会扯一句。虽然代码风格不显式地打分，但如果问除了 [Google C++ style guide](https://google.github.io/styleguide/cppguide.html)，可以参考什么具体项目，那我大概率会说 [`Google Chromium`](https://source.chromium.org/chromium/chromium/src)。

一般情况下，工业中不写

```cpp
void mergeSet(std::set< std::pair<int,int> > &x, std::set< std::pair<int,int> > &y);
```

这种风格的代码，你可以考虑写成

```cpp
// 气
using Liberty = std::pair<int, int>;

// 连通块周围的气的集合
using LibertySet = std::set<Liberty>;

// 合并两个气集合
void mergeLibertySet(LibertySet &x, LibertySet &y);
```

但这不是必须的，对于比较简单好理解的项目，这么写对于开发人员可能是负担。

但如果你考虑代码的可读性，后人能否方便地维护等等，这么写是有必要的。

例如当你的代码复杂到这样的时候：

```cpp
template <typename T>
using IsNotStdArray = std::negation<IsStdArrayImpl<std::decay_t<T>>>;

template <typename T>
using IsNotCArray = std::negation<std::is_array<std::remove_reference_t<T>>>;

template <typename From, typename To>
using IsLegalDataConversion = std::is_convertible<From (*)[], To (*)[]>;

template <typename Iter, typename T>
using IteratorHasConvertibleReferenceType =
    IsLegalDataConversion<std::remove_reference_t<iter_reference_t<Iter>>, T>;

template <typename Iter, typename T>
using EnableIfCompatibleContiguousIterator = std::enable_if_t<
    std::conjunction<IsContiguousIterator<Iter>,
                     IteratorHasConvertibleReferenceType<Iter, T>>::value>;

template <typename Container, typename T>
using ContainerHasConvertibleData = IsLegalDataConversion<
    std::remove_pointer_t<decltype(std::data(std::declval<Container>()))>,
    T>;

template <typename Container>
using ContainerHasIntegralSize =
    std::is_integral<decltype(std::size(std::declval<Container>()))>;

template <typename From, size_t FromExtent, typename To, size_t ToExtent>
using EnableIfLegalSpanConversion =
    std::enable_if_t<(ToExtent == dynamic_extent || ToExtent == FromExtent) &&
                     IsLegalDataConversion<From, To>::value>;

// SFINAE check if Array can be converted to a span<T>.
template <typename Array, typename T, size_t Extent>
using EnableIfSpanCompatibleArray =
    std::enable_if_t<(Extent == dynamic_extent ||
                      Extent == internal::Extent<Array>::value) &&
                     ContainerHasConvertibleData<Array, T>::value>;
```

> 以上是 chromium 的[源代码节选](https://source.chromium.org/chromium/chromium/src/+/main:base/containers/span.h)，chromium 就是 Google Chrome 的开源版本。如今的 Edge, 360 极速浏览器等等都是基于 chromium 开发的。其开发语言是 C++，这个项目的源代码有3.2G，4000w行。
>
> 可以看到，它的命名都非常长，工业中一般都是这样。

### 抄袭说明

顺便再强调一次 [抄袭说明](../../task/1.1-overview.md#抄袭说明)，请仔细阅读，我们会严谨地对待抄袭。

### 分工提示

第三阶段的 AI 可能比较简单，而且几乎都是面向过程，所以写AI的人最好适度参与到前面中。

## 阶段1指南

详情见 [task1](../../task/2.2-stage1.md)，和最初相比做了微小的删减，将一小部分移到了下一阶段。

简单说，这一阶段的任务就是用 Qt 写一个基本规则完善的不围棋。不用考虑网络，AI，非规则内的温馨功能，或者说，能玩就行。

其中要实现计时功能你们可以利用 `QTimer`。

另外，虽然第一阶段的截止日期是4月4日，但因为第二阶段可能会撞上期中考，所以你可以考虑提前做一点第二阶段。理想状态下是学一周 Qt，两周把第一阶段写完，然后最后一周开始写第二阶段。

一旦完成了第一阶段，就可以在上机课上找潘俊达助教（男的助教）检查。
