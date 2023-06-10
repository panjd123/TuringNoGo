## 第二阶段实验报告

##### 小组分工

- 李懿哲负责网络部分的编写
- 王熹与张晋恺负责实验报告的撰写与代码检查

### 通信协议

使用了给出的基于QTcpServer和QTcpSocket二次封装的NetworkServer类和NetworkSocket类实现

数据类型如下

![](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5lG7hFK7vE3ilKuNi2NIsm.xXWPRQHeM22xb9r4eJVekvP8Bmh1zfD3sgnCECJv5vy8dfgoSUtda8m3iYa5N.ug!/b&bo=rgFwAQAAAAADB*w!&rf=viewer_4)

具体使用的函数如下

![](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5lG7hFK7vE3ilKuNi2NIsm8frgJhJE8AuagBwNWD3s4jqrvJWAKEK.pxfYhWdoR5c7.NrWdTt8NpslwNUbhfADI!/b&bo=aAOsAAAAAAADF*U!&rf=viewer_4)

在联机游戏中，主要逻辑为：服务端监听----客户端链接----服务端接受联机----一方申请对局----另一方确认对局----进行游戏----结束并断开连接

过程如下

![](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5swYgW6BhUFuUpokRZjalvhrVKsUSZrmjrbMdu0qaZRY7UHtTk1Xg6XqRKj4LohV2Tt0aJKYoA6la1LzmvibHvY!/b&bo=wAF2AQAAAAADB5Q!&rf=viewer_4)

![](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5swYgW6BhUFuUpokRZjalvinn.pJsQB5NeI9mxl3CHhALfNNwpnZunfFC4dil8O.najZu7Q*Zq54JUtC46cRsFU!/b&bo=1gHeAAAAAAADBys!&rf=viewer_4)

![](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5vynp1W3sgHf97kKNWl9BEoailvWaiPZ5lcJ5FcHvD9BQm0jU35bTshjO22LK.Gb0eWj8LcDLLM8ftzUp0*4URc!/b&bo=KgJyAQAAAAADB3k!&rf=viewer_4)

![](http://m.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5vynp1W3sgHf97kKNWl9BErw*Cnp5bSzOVDp9Pz9fdBD9EXVnn6WEHqDkLJuAQwj9c6Mf..wUT5k8ffCGAqeLz0!/b&bo=MAOGAQAAAAADB5Y!&rf=viewer_4)

当一方发送对局申请时，发送一方向对方发出READY_OP，对方窗口同时弹出是否接受对局，接受则发送READY_OP并进入对局，拒绝则发送REJECT_OP并取消对局链接

由于有自杀判定，因此对局的结束只能通过认输或超时来决定

当一方认输时，会向另一方发送GIVEUP_OP并在对方游戏中弹出窗口进行确认，具体函数如下

![](http://a1.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5qyjqXVOw4H0pm2qkETSIf.yAToDjuKItWLT0GPzTZN00wZwCFIrg6fS5BS40oY006MrXEEIQzUzJqUewZvQDdk!/c&ek=1&kp=1&pt=0&bo=hgXAAgAAAAADJ0M!&tl=1&vuin=1353156306&tm=1685880000&dis_t=1685883097&dis_k=5c681ba9f0eb9331d248589bd11e9932&sce=60-2-2&rf=viewer_4)

当一方超时，超时一方会向另一方发送TIMEOUT_END_OP并对方游戏中弹出窗口进行确认，具体函数如下

![](http://a1.qpic.cn/psc?/V14BODuP0JJm1D/ruAMsa53pVQWN7FLK88i5qyjqXVOw4H0pm2qkETSIf*3yeDdFSg8EU23B5XeOWcJVv02cV0B.ja.KbBhzJrKy0ARJF4wRaZqqbBd16n9nF0!/c&ek=1&kp=1&pt=0&bo=pAVmAgAAAAADJ8c!&tl=1&vuin=1353156306&tm=1685880000&dis_t=1685883097&dis_k=62e3e4c1d5de65f1c99c2e83033aaa2d&sce=60-2-2&rf=viewer_4)

联机对战结束后，双方断开连接

