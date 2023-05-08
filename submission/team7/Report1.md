## 第一阶段实验报告

- 李懿哲、王熹负责棋盘绘制
- 张晋恺负责规则判断及实验报告撰写

#### 棋盘绘制

棋盘绘制采用了程序画图，棋子也采用了程序绘制，直径为绘制棋盘格的边长，以下是绘图事件函数

![img](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5oHaSeVvWt7q7EF2TaTJEFzu*AKc4rVyZZi8yPXPPKhtHBM0kLjO3dj6sgH.dUK7Cb5cD4vbqzFAFCbJ*aJIrKE!/b&bo=mgImAAAAAAADB5w!&rf=viewer_4)

棋子颜色的选择采用了RGB设置，即（0，0，0）和（255，255，255）

![img2](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5m1XNljK7ld.5M4t.TowIiDE4A4PMKr0DssOZRVSrqCQ1rrWKbY0s1HepkrHYgOdfx8Lp7KnqOKn.Pwvc7*cjN0!/b&bo=XgRYAgAAAAADFzI!&rf=viewer_4)

在绘制棋子存储棋子位置时，为了方便判断棋子气数以及方便搜索，将棋子所在屏幕的实际像素位置除以了棋盘宽度，这样方便建立棋盘格与棋子坐标的映射，实现如下

![img3](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5m1XNljK7ld.5M4t.TowIiCwWIOL*hVcOmplDG.6FodMclj.clIWiLv0rGj.DtdHLG9GSlKPwM5gEOI2u6K7PcY!/b&bo=CAJCAAAAAAADF3o!&rf=viewer_4)

设置的计时器为每人思考15秒时长，超时停止计时器计时并直接判对方胜，当一方下完棋时需要点击屏幕右侧的“我下完了”按钮重置计时器计时，如不点击会提示用户未到下棋时间，黑子第一手不计时

![img4](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5v0eH3zjWOYbLudyMSNcAueSMF3IzYUOTrduNcUzcb365FFGmQZeHEZmS1erZZSAUa2jdiTG6pB8*AtwQkqmA4U!/b&bo=AwU4BAAAAAADFwg!&rf=viewer_4)

![](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5sXxbb4qsJwdwngjyWfwk.iXvCUdM.5Yso.xsPemxsd1U.G.*i6GfvBEXvOg.2j0MR21JUMT968JO5Px0A1MD5w!/b&bo=IgU4BAAAAAADJxk!&rf=viewer_4)

![img6](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5sXxbb4qsJwdwngjyWfwk.huBgClXV*Dn35W814lBVnIKFcbhc*vf7tpfVXV1fQjKbtpNAYFm1SftxOl5Uhh*Zk!/b&bo=MAU4BAAAAAADFzs!&rf=viewer_4)



#### 规则判断

判断棋子气数采用了深度优先搜索，每下一次棋会搜索棋子周围是否为边界或标记过的同色子，有无异色子，若有，则进入下次循环，若没有，则判断周围是否有空子，若有空子则说明该棋子有气，退出搜索，若没有空子则检查周围是否有未标记的同色子，若有则搜索该同色子，若没有则说明该棋子块没有气，对方败，以下为判断函数

![img7](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5v0eH3zjWOYbLudyMSNcAucJzJB5fAH6EiY1dnRHFYOsGWbxzUeqOaxDthf3DOIS12.7kKV.PIKGIhBtilr6YRA!/b&bo=ngFKAAAAAAADF.c!&rf=viewer_4)

![img8](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5v0eH3zjWOYbLudyMSNcAudQdUNeHe*fcCL0k.XenUOjMHwxFmAk28JqgbfWU66VyQ*jOMq9FXSrIhEwqfhUKqg!/b&bo=*gSkAgAAAAADF24!&rf=viewer_4)

![img9](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5v0eH3zjWOYbLudyMSNcAueU8tbfusq2APOP51v5Ga1MEWLZ*DIlkjYTuS*9MWjDwYGRL3R*ghXxouFF5ga9XB8!/b&bo=0gVaAgAAAAADF70!&rf=viewer_4)



以下是MainWindow.h

![img12](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5kAJxPmaCHarmKYW48E2BBY37qRwUvWZ4mG5AW*yC3in.kb2.TEH2fV.JBygBwFopS.H9x1q5.woDVVMZgYseUI!/b&bo=oAMkBAAAAAADJ4E!&rf=viewer_4)

![img11](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5kAJxPmaCHarmKYW48E2BBblAdiu3Z9Z2XEMAALNmJjOS6O1RD*p8aA*QWR*HpwfzLxys3QKs4YiklB0goRjhWA!/b&bo=mAIQBAAAAAADF7w!&rf=viewer_4)

![img10](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5kAJxPmaCHarmKYW48E2BBaB9VtGd1AGl3h5DoovM4Br0hMoW0PgIB.SYSoUk1*r06n2xz4M6YH6RDQBeRdwrSo!/b&bo=tgR0AgAAAAADB.Y!&rf=viewer_4)



## 致谢

感谢孙亚辉老师和潘俊达及王卓冉两位助教的教导
