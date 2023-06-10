# 程序设计大作业第三阶段报告&&最终版
撰写人：杜非原

我们的GitHub仓库地址为[Dainokami/big-project (github.com)](https://github.com/Dainokami/big-project)（已公开并上传release）

#### 小组分工

* 杜非原：负责主体AI的设计以及实现，代码debug，测试程序
  
* 梅祎航：负责实现附加功能，修改AI，代码debug，测试程序
  
* 胡宇：代码测试。
  
* #### 代码框架
  * AI部分主体使用minmax算法+αβ剪枝算法优化。
  * AI单独作为一个.h/cpp文件，同时被pan和netpan调用。
  * AI核心函数：
    * ![](/image/stage_3_0.png)
    * 该函数致力于通过多次搜索得到棋盘最佳得分，并在此过程中实时更新globestCol和globestRow作为最终落子点坐标。
    * 主要有两部分：min部分和max部分，首先进入max搜索，然后depth-1进入min搜索，直到depth==0，结束搜索。
    * 值得注意的是：最关键的参数实际是实时更新的globestCol和globestRow，而非最后返回的score。
    * ![](/image/stage_3_1.png)
    * 该函数为接口函数：
    * 接受从棋盘传入的 board1[13][13]（当前棋盘），player（AI执棋颜色），len（棋盘长度）
    * 调用minmax函数计算出最佳行（globestRow）和最佳列（globestCol）
    * 返回整数为100*行+列；
    * 在pan和netpan中调用时，将返回值传入落子函数，点亮相应棋子。
  
    * 估值函数有两种实现方式（选一种就行，鉴定为血泪中的错误）：
    * 1、int getPotential(int x, int y, int player)判断连子潜力和空位潜力。
         int evaluate(int player)按边，角，中心估算棋子价值。
    * 2、直接使用int evaluate(int player)函数，调用getliberty函数计算当前局面值即本方计算气数++，对方计算气数--；最后用气数算出总分
  
    * 其余函数为判断合法函数较为简单，最后的两个函数为pan中使用过函数这里拿来用，不过多赘述。
    
    * 为了防止ai计算使用太多时间，我们在ai计算多层后使用随机数强制返回解。



   * 附加部分
     * 我们实现了一盘结束后呼唤READY_OP再来一局(详情请见netpan.cpp的```receieveDataFromServer(NetworkData data)```和```receieveData(QTcpSocket* client, NetworkData data)```中对READY_OP的处理)
     * 我们实现了复盘的开始暂停，上一步，下一步，跳转等附加功能。（详情请见```load.h/cpp```的各个函数）
     * 虽然我们比较菜，但我们仍热心为一些同学提供了绵薄之力，如马博靖同学小组（突然发现这也是一个可以写的点）


* 遇到的问题
  * 开始AI部分在载入pan和netpan时没有找到合适的方案和逻辑，导致无法运行AI，对debug造成了一定的困扰。
  * 估值函数采取了两种不同的想法，两个想法都有，但是都没彻底实现，导致了写代码效率的低下（后来改好了）
  
*  还有些想汇报的

  * 介于这是最后一次汇报，我们决定将我们的代码框架梳理一遍以帮助师兄更好地看这个屎山

    ![](/image/stage_3_2.png)

    如上图，```pan.h/cpp```中为单机下棋部分， ```netpan.h/cpp```中为联机下棋部分，```ai.h/cpp```顾名思义是ai，```load.h/cpp```负责复盘功能。```widget.h/cpp```是主界面，连接了单机下棋，联机下棋，和复盘。
    
    ```networkdata.h/cpp```和```networkserver.h/cpp```和```networksocket.h/cpp```为网络相关,本组并未对网络进行进一步处理，仍采取服务端与客户端分离的策略。（网络部分详见report_2）



  #### 我们具体的工作：
  （前期commit记录大体可以反映我们的工作量，后期发现github还没有微信传文件好用（雾），于是采用了更高效的方式）
 * 我们的神：梅祎航：完成的所有大作业的主体部分：ui设计，下棋逻辑，以及完成了本该由某废物完成的网络功能等等。
 * 垃圾：杜非原：完成了开始绘画棋盘，局内聊天（后来没用上，被梅神包了）AI实现等功能，但由于代码bug较多，梅神给予了其很大的帮助。
 * 神秘人：胡宇：负责代码测试。

     