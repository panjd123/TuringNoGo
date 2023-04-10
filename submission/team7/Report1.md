## 第一阶段实验报告

- 李懿哲、王熹负责棋盘绘制
- 张晋恺负责规则判断及实验报告撰写

#### 棋盘绘制

采用了最普通的棋盘画法，使用程序绘图，没什么UI设计

![img](http://a1.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5p5zdXBwlK1gLwqqYUWXuIVhdXdZ31RqjHdgUWM2AfcD2ueC3ujdWyu5X9s5o6KBPPwvrrC3XbXFbauJg5qG8Zk!/c&ek=1&kp=1&pt=0&bo=kgU4BAAAAAADF5k!&tl=1&vuin=1353156306&tm=1680534000&dis_t=1680536894&dis_k=09fdee4b78ec15da101882869280c79e&sce=60-2-2&rf=0-0)

使用灰色的背景区分棋盘部分与其他部分，

![img](http://a1.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5h8xT*7yXYfRPtGEr7EGiwwrbEwMcHBXVqRfgOHQe4MCQMI.keCWcxPWrVNlHlvymci*v.Rs9juXyd*vAhfnzpk!/c&ek=1&kp=1&pt=0&bo=YAU4BAAAAAADJ1s!&tl=1&vuin=1353156306&tm=1680534000&dis_t=1680537427&dis_k=74cf07ca50ae5f4daed669f6699e0dde&sce=60-2-2&rf=viewer_4)



棋子选用经典的黑白配色，并且棋子可以跟随鼠标进行移动。

以下是使用到的函数

![](http://a1.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5oHaSeVvWt7q7EF2TaTJEFw5fVewdiSO9FRRtLQ79Kgdht9nbtxm.zEO8.RD4kQFBSU4E55I3VyglsJctVUg338!/c&ek=1&kp=1&pt=0&bo=zgRqAwAAAAADJ6E!&tl=1&vuin=1353156306&tm=1680537600&dis_t=1680537652&dis_k=587ab2fa0d4d51752362dfda0a42041f&sce=60-2-2&rf=viewer_4)

在绘制棋子的函数中加入了判定鼠标位置防止其在棋盘外的区域绘制棋子，使用QVector来存储棋子

#### 规则判断

采用dfs搜索棋子块以及其是否有气，棋子块是否有气的判定采用了在搜索到每颗棋子时都进行对其四周的检查，有几个空格就加几个气，因为该游戏只需要判定棋子块是否有气即可，因此对棋子块的气的重复计算不会对结果的判定产生影响（但是可能会对后续的AI部分的估值函数产生影响，后续再改一下）

十分抱歉的是，在编写完函数运行后发现下几颗棋子就会导致程序崩溃（死循环了），因此这部分还没有完成，十分抱歉十分抱歉（哭😭）

过两天会改好的（大哭😭

## 致谢 

感谢孙亚辉老师和潘俊达及王卓冉两位助教的教导

感谢浙江大学Xishanqiming学长对我学业上的关照
