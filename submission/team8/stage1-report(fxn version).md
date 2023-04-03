# 第一阶段报告

## 摘要

1. 设计题目

    不围棋联机对战游戏（第一部分：初步实现游戏界面和简单逻辑）

2. 阶段设计内容

    利用C++设计一款可以轮流落子和具有简单判断逻辑~~并且有很多bug笨重至极~~的不围棋游戏。

3. 开发工具

    Qt6

4. 小组分工

    房向南(此版本)

尽管是一个小组大作业，我们小组(team8)却有着两份不同的版本，此版本为小组中房向南完成。

因这些因素给助教带来检查的不便我深表歉意。

## 详细设计

### 代码框架

![代码框架](http://m.qpic.cn/psc?/V13tRFxc0Vxo8W/ruAMsa53pVQWN7FLK88i5nWye3jR9EHevwHUQv7wFomC6eacn0NnMXpMGIPLqDQcH39iXP1ag5o7KsFO58wB2xUNI4SGvx*cgwr*BC304yE!/b&bo=aQLaBAAAAAADF4c!&rf=viewer_4)

如图，start是开始界面，mainwindow是下棋界面，setting是设置界面。

item是棋子的类，block是棋子块的类。

计时器及逻辑判断等闲杂内容在mainwindow中实现。

本框架参考了网上一些五子棋的框架，如item的类，但是仅止于此。[参考网址](https://blog.csdn.net/muLanlh/article/details/108936757#t2)

### 代码简介

![代码简介](http://m.qpic.cn/psc?/V13tRFxc0Vxo8W/ruAMsa53pVQWN7FLK88i5txrh9EJlEmJ7Ou*pCi1fPqDT6iyONhxLeufBc8CtqBKFWA0DxjYLvltEZ24SPiwf69mqHecfr2diG0fd7jAWHo!/b&bo=XgQ4BAAAAAADN3Q!&rf=viewer_4)

+ 逻辑判断部分

    本作业逻辑判断部分比较抽象，利用其他模式想要简化搜索算法的编写难度(~~本人大概是写不明白~~)。

    但最后的结果与预想背道而驰。在测试发现bug然后修复这样两次之后我已经对这个东西的正确率抱有极大的怀疑。
    不过肯定会花功夫想办法改进。

    基本思路：一个棋子落下，判断它是哪个块,如果边上没有块(相同颜色的棋子)，那就新建立一个块。这样的块叫小块。

    判断胜负的时候，除了判断最新下落的棋子所属的小块是否有气，还要判断本身所在的同色大块以及周围的不同异色大块是否有气。(递归实现)

+ 游戏结果部分

    本作业采取QMessageBox中的information和question来实现结果展示。

    在判断胜负之后利用statistic函数和jiesuan函数来生成结算信息字符串(QString类型)。然后利用QMessagebox展示并保存在d盘的txt文档里(只保存最新对局)。

    ![结算信息](http://m.qpic.cn/psc?/V13tRFxc0Vxo8W/ruAMsa53pVQWN7FLK88i5onB0iOhKAqWsICw*j1y3YOPGuJSyXM7FKgs9QNNtqMJQZ.BNouqDXVBUGnnnv0KMpAwziqJp2CSt700EK84lTQ!/b&bo=GAQOAwAAAAADBzM!&rf=viewer_4)

    由于不是所有电脑都有d盘而又没有c盘权限，这里的游戏日志保存方法值得商榷。

    结算展示后，会询问是否开启新的一局。若是，则新建一个mainwindow；若否，则新建一个start窗口。然后关掉原来的mainwindow。

    ![结算信息](http://m.qpic.cn/psc?/V13tRFxc0Vxo8W/ruAMsa53pVQWN7FLK88i5mktKFftinw5rFZeObyKhpYGi0RKcf.5hq.dTUuyyl2dfllAVGGoxkxzL67xIAYjdmX.JNK3BguTYDYjcaEj7jw!/b&bo=0gFJAgAAAAADF6o!&rf=viewer_4)

    图片是利用认输做的示例。

+ 其他部分

  + 认输方面，我采取了和正常输赢一样的结算方法。
  + 再来一局设计的很鸡肋，类似于点击是否开启新的一局的Yes。
  + 返回就是返回start界面。想去setting界面得这样走。

### ui设计

![开始界面](http://m.qpic.cn/psc?/V13tRFxc0Vxo8W/ruAMsa53pVQWN7FLK88i5mktKFftinw5rFZeObyKhpYJ2EFtY4DGt9uefx8oS9vQ18qkOr0m8cF7lu*nPbzfBkWUOjk21I7qvKbDTnYqSqo!/b&bo=NAUnBAAAAAADFyA!&rf=viewer_4)

>界面设计采取绿色为主基调，背景是知乎“十大最高级渐变颜色”这一专栏介绍的渐变色的其中一种(不仔细看哪有渐变)。

>开始界面有着“开始”和“设置”两个按钮，分别对应mainwindow窗口和setting窗口。开始界面中间的部分为了美观采取白色圆角设计

![游戏界面](http://m.qpic.cn/psc?/V13tRFxc0Vxo8W/ruAMsa53pVQWN7FLK88i5nWye3jR9EHevwHUQv7wFokAdjWrYi7DMK*MqARc9Y412Prpm9Yopc64isXnFg1PpQ9oiqeiUDEU8f2XtykS3Vc!/b&bo=AwU8AwAAAAADFws!&rf=viewer_4)

>游戏界面以简洁为主，其实可以采取贴图的方式规避QPainter画的图被背景挡住的问题，此问题待阶段二解决。

>右边的认输和再来一局及返回在前文都有介绍，这里不再赘述。四个lineedit分别为总计时和读秒。

![轮流落子](http://a1.qpic.cn/psc?/V13tRFxc0Vxo8W/ruAMsa53pVQWN7FLK88i5uMULMdkhn4oQeXr6BNnFJoURTwwO0a7nTmPH8D1cRrjXm76O3Mkh0gTDOud72TgVL5rn4e7CLpfNbyiDc8CVE4!/c&ek=1&kp=1&pt=0&bo=9wQ4AwAAAAADF*o!&tl=1&vuin=3328675434&tm=1680519600&dis_t=1680519865&dis_k=4a94558817d78f84b36265a87cdeaa53&sce=60-2-2&rf=viewer_4)

>这是轮流落子展示，我利用深蓝色或者浅黄色标记最近一颗的落子。这里的“高亮”不够显眼，好在只涉及颜色挑选的问题。

![设置界面](http://m.qpic.cn/psc?/V13tRFxc0Vxo8W/ruAMsa53pVQWN7FLK88i5nWye3jR9EHevwHUQv7wFok4dDE0iOyZS176uVoERTGQo3h0EqZ8dof046aG2HSJvxjFCpPVSUf.Jd7AuoSJ0kY!/b&bo=NAUnBAAAAAADFyA!&rf=viewer_4)

>设置中可以调整棋盘行数，读秒时长，读秒次数。

>下方空余区域为以后可能存在的设置留下位置。

  ui设计是利用一篇CSDN文章学习的，也引用了小部分内容
  
## 遇到的困难

1. 在C++没学多少的情况下写此作业十分考验临场学习水平。
2. 因为一些事耽误了完成进程导致写的有些仓促。
3. 因水平所限，ui设计和逻辑判断不尽如人意。

## 展望

1. 测试出可能存在的bug，并用更简洁的办法写出逻辑判断
2. 添加联机功能以及尝试ai功能
3. 进一步美化界面设计

## 鸣谢

+ 网络资源的大力支持
+ 中国人民大学提供的平台
+ 两位助教和老师的细心讲解
+ 理学院侯同学的双人对战测试和财政金融学院龚同学的界面设计建议
+ 同小组徐耀文和王鲲翔两位同学的对我的启发和帮助
+ ~~B站给予的精神支持~~
