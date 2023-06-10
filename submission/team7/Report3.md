## Stage 3

#### 小组分工

- 三人各自编写了一个AI，但由于个人能力有限，MCTS算法的搜索次数过低（甚至远远不如随机下棋），所以最终选择了李懿哲的算法
- 张晋恺、王熹负责代码检查
- 实验报告由张晋恺编写

### AI逻辑

首先检测四个角是否可以下棋，如果可以则优先下在角落。思路是尽可能减少对方能够落子的位置。

然后采用构造活眼的方式，并且优先在棋盘的边缘下棋，如下图所示

![](http://a1.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5vynp1W3sgHf97kKNWl9BEoe7kgiSIEklolyHFy9nIp*BrmmkUKXrTNmZXFbtXn94PuCdSUpWdR6POZcQ5gFVHI!/c&ek=1&kp=1&pt=0&bo=1gK.AgAAAAADJ2o!&tl=1&vuin=1353156306&tm=1686384000&dis_t=1686386220&dis_k=0483af4f669f3813493203026fe45a82&sce=60-2-2&rf=viewer_4)

白棋与黑棋都构造了几个活眼从而导致对方不能下在眼处

对位置的生成使用随机数生成，并先进行是否有构造活眼的可能以及是否会导致自杀的判断，如果有则落子，如果不能构造活眼便生成一个不会导致自己死亡的点落子，在生成随机数时会进行时间检测防止超时，若生成时间超过4秒，则直接随机生成一个棋盘上没有棋子的位置进行落子。

代码如下

![](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5swYgW6BhUFuUpokRZjalvhKdH8PY4qSEmAVUXTo4XdnYTh4um8JC3Ua2oUHBS6vAhaw36VBRC*SjL5WVy6IT*Q!/b&bo=EATKBAAAAAADJ9g!&rf=viewer_4)

![](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5swYgW6BhUFuUpokRZjalvj1LsH7ugdtLlGZ.4Xl.zenY9RpKpt3RvXjc6d.u6jHfMqj4jnMILCxgMMt6psBYY0!/b&bo=lQQ4BAAAAAADN78!&rf=viewer_4)

![](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5swYgW6BhUFuUpokRZjalviquVLWnHG6hJxD.XsZ1fjIqOnVEcYsk*PLn5g2*xjuOZPhrpqmI6Y8c6lhu3thOhc!/b&bo=WQQ4BAAAAAADJ2M!&rf=viewer_4)

经测试，打败随机应该是没什么问题

### 复盘

在单人下棋界面中，加入了“复现”按钮，点击复现按钮会弹出选择文件的窗口，选取合适的文件后会在棋盘上生成文件所表示的对局，如图

![](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5hAQR9LhoxrRP13.Y9s8aBcPrmdaXdq*5m7JGePnuYVayHLXwyurUovny9dPT5nVBsu3DvrkBm7kY2.IpGbtOCI!/b&bo=ZQU4BAAAAAADJ14!&rf=viewer_4)

![](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5qyjqXVOw4H0pm2qkETSIf*UNy3HkweVOxfGi4D4FMa3t1QmCxUa0ghDPWylXyvPVze6tBB8VQRHlrTGa367*k4!/b&bo=ZgaWAwAAAAADN.c!&rf=viewer_4)

![](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5qyjqXVOw4H0pm2qkETSIf*6Un2gWF8J9N8y9OYXZP85nxcgOEjUaVAr579juQPoPEuWwPUe2Y4isnAi2q5KL.U!/b&bo=dAU4BAAAAAADJ08!&rf=viewer_4)

### 对前两阶段的补充

加入了多路棋盘的选择，默认是九路

![](http://a1.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5hOadZ14CLCa.4hJH5YE0vhGEIWgmDHzFxPLkwl0I3mfsS2855LlgbdePgA2ReZeYqGiJDLKTFau4Bq*f6*325s!/c&ek=1&kp=1&pt=0&bo=TwU4BAAAAAADF0Q!&tl=1&vuin=1353156306&tm=1686405600&dis_t=1686407509&dis_k=f174e84c06d95ceb6d80293e625ce983&sce=60-2-2&rf=viewer_4)

![](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5hOadZ14CLCa.4hJH5YE0vjNRbXgHZLSwk*GMXnISzq*7nLltKSoZiaq1WBJS2Kboa*.LcGfwaEFboCFm0OXvCk!/b&bo=SwU4BAAAAAADF0A!&rf=viewer_4)





### 致谢

- 感谢与李懿哲、王熹组成的小组
- 感谢图灵班提供的平台
- 感谢老师与助教的教导
- 感谢房向南同学与我们小组多次进行联机测试

- 感谢李知非同学，沈海涛同学，房向南同学的悉心教导

GitHub : https://github.com/Shirakitera/Team7.git
