## **Turing NoGo stage3 报告**

### 大体分工

陈宇轩：完成附加任务1；完善估值打分ai；测试运行情况。

沈海涛：完成附加任务9；完善蒙特卡洛ai移植；打包整个文件。

付弋洋：完善蒙特卡洛ai；负责大作业汇报和实验报告的书写。

### 内容概述

在阶段三中完成：

#### 附加任务一：

​	在重现对局中实现 `播放`,`暂停`,`上一步`,`下一步`,`到第_步` 等功能。

​	代码框架如下：

```c++
bool MainWindow::save() //存储程序
bool MainWindow::read_in() {//复盘程序
    reproduced=true;
    showall();
    this->lb->hide();
    this->ui->report->hide();
    QFile file("item.txt");
    ...
    while(!in.atEnd()) 
    {
        in>>str;
        bool ok;int x,y;x=str.mid(0,str.length()-1).toInt(&ok);//横轴
        if(!ok) 
           break;
      	else 
            y=str.right(1).at(0).unicode()-'A'+1;//纵
        if(num%2==1)
          m_items[x][y]=1;
        else 
        {m_items[x][y]=2;
        m_steps[x][y]=num;saving.push_back(node{m_items[x][y],x,y,num});//这里使用了动态数组来存储、后续再优化前面的
    ...}
      ...
}
```



#### 附加任务九

​	帮助第五组同学完成网络相关的问题

#### AI算法的实现如下

```c++
				// 优先选择与已有棋子相邻的空格子
       	...
        for (int x = 1; x <= boardWidth; x++)
        {
        for (int y = 1; y <= boardHeight; y++)
        {
            if(t->candown[x][y]==1)
            {
                flag=1;
                if(t->scores[x][y]>max) max=t->scores[x][y];
            }
        }
        }
        if(flag==0) return QPoint(-1, -1);
        for (int x = 1; x <= boardWidth; x++)
        {
        for (int y = 1; y <= boardHeight; y++)
        {
            if(t->candown[x][y]==1&&t->scores[x][y]==max) Positions.append(QPoint(x,y));
        }
        }
        if (!Positions.isEmpty())
        {
        srand(QTime::currentTime().msec());
        int randomIndex = rand() % Positions.size();
        return Positions[randomIndex];
        }
        return QPoint(-1, -1);
}
```

接下来展示一下被抛弃的MTCS的框架（虽然没用上，但写都写了，遂放上来

```c++
void Ai::UnionSet::init() //该函数用于初始化坐标与索引之间的映射。
{
    srand(time(0));//用当前的时间来随机
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++) {
            int id = i * sz + j;//二维转一维
            pos_to_id[i][j] = id;
            id_to_pos[id] = poss(i, j);//用一个pair来对应id
        }
}
bool Ai::UnionSet::check1(int i,int j)//检查给定的坐标(i, j)是否在合法的范围内
// using union set to save our state
Ai::UnionSet::UnionSet(){
  {...
    }//初始化并查集
    ... //初始化所有位置为-1
}
int Ai::UnionSet::getfa(int a)//用于查找元素 x 的根节点（代表元素）
{
    return fa[col][x] == x ? x : fa[col][x] = getfa(fa[col][x]);
}
void Ai::UnionSet::merge(int x,int y) //它将元素 x 和元素 y 所在的集合进行合并。
{
    fa[col][getfa(y)] = getfa(x);
}
int UnionSet::insert(int i, int j) {//插入
...
}
...
// our Monte-Carlo Tree
Ai::Node::Node(Node *par, int n_child, poss p, int play) //构造函数
int Ai::Node::bestChild() //选择最佳的子节点
{
     int bstId = 0;//最好的位置
     double maxVal = 0;//记录最大的评估值
     for (int i = 0; i < nExpand; i++) {
        // UCB formula
        //UCB算法公式
        //如果当前子节点的评估值（eval）大于当前最大评估值（maxVal），则更新 maxVal 为 eval，同时更新 bstId 为当前子节点的索引（i）。
        double eval = 1.0 * child[i]->cntWin / child[i]->cntAll + 0.9 * sqrt(log(cntAll) / child[i]->cntAll);
        //计算公式 获胜次数/游玩次数+0.9*√（ln(目前的游玩次数)/子节点游玩次数）
        //前半部分表示期望回报，后半部分是一种探索（非贪心），从而表示总体的期望回报的不确定程度
        if (eval > maxVal) {
            maxVal = eval;
            bstId = i;
        }
     }
     return bstId;
}
void Ai::treePolicy(Ai::Node *&now, Ai::UnionSet *state) //执行蒙特卡洛树搜索的策略,可以在蒙特卡洛树搜索过程中进行策略的执行，根据当前的游戏状态和已有的树结构，选择合适的子节点进行探索和游戏状态更新。
{
     if (state->end != -1)//如果已经存在胜利的情况（end 不等于 -1），则直接返回，不再执行后续的策略。
        return;
     while (now->nExpand == now->nChild) //当前节点已经扩展了所有可能的子节点，需要选择一个最佳的子节点进行探索
     {
        int bst = now->bestChild();
        //返回最优子节点位置,在这里进行了预测
        poss p = now->child[bst]->index;
        //找到对应坐标
        int x = p.px, y = p.py;
        //存储最优子节点信息
        now = now->child[bst];
        //更新
        int t = state->insert(x, y);//将选择的子节点的位置信息传递给游戏状态 state 进行更新
        if (t != -1)
            return;
     }
}
void Ai::expandChild(Ai::Node *&now, Ai::UnionSet *state) //扩展当前节点的子节点
int Ai::defaultPolicy(Ai::Node *&now, Ai::UnionSet *state) //在当前游戏状态下进行随机操作直到游戏结束
void Ai::backPropagate(Ai::Node *&now, int st) //反向传播更新节点的统计信息，以便更新节点的胜利次数和访问次数
poss Ai::mctsSearch(Ai::Node *rt, Ai::UnionSet *state) //蒙特卡洛树搜索
{
    int st = clock();//time.h中的函数，用来计时
     while (1.0 * (clock() - st) / CLOCKS_PER_SEC < TIME_LIMIT) //超过时间限制后，根据已经收集到的统计信息选择最优的子节点
     //卡时，不过可以修改一下，时间要求没有那么高
     //CLOCKS_PER_SEC将单位转成秒
     {
        Ai::Node* now = rt;
        //新建并查集
        Ai::UnionSet* st = new Ai::UnionSet();
        *st = *state;
        //现在状态
        treePolicy(now, st);//开始搜索,这里存储了最优的子节点
        expandChild(now, st);//扩展子节点
        int t = defaultPolicy(now, st);//随机落子的条件下,返回落子方
        backPropagate(now, t);//从相应的子节点返回
     }
     int bstId = 0;
     double maxVal = 0;
     for (int i = 0; i < rt->nExpand; i++)
     {
        // UCB formula
        double eval = 1.0 * rt->child[i]->cntWin / rt->child[i]->cntAll;
        //估值函数:胜利次数/游玩次数,这是一个期望的计算，没有处理预测
        if (eval > maxVal) {
            maxVal = eval;
            bstId = i;
        }
     }
     return rt->child[bstId]->index;
}
```



### 遇到的问题

	+ 在该阶段我们实际上一直有两个ai，一个是较为简单粗暴的上述估值ai，一个是加入UCB的蒙特卡洛。但是由于参数和算法逻辑等问题，最后测试中我们发现看起来高级一些的MTCS的胜率甚至不如这个简单粗暴的估值ai😓😭😠。再修改无果之后，我们决定就采用这个简单粗暴的。
	+ 由于并行两个ai，所以经常出现权衡取舍和bug传染。。。给本就艰难的stage3平添困难
	+ 一如既往的Mac与windows的系统差异问题，windows跑不了的程序，Mac能跑；Mac跑不了的，Windows能跑。导致测试和debug过程较多
	+ 快到期末了，别的科目也学不走了😭，于是大作业拖拖拖，直到看到立德凌晨三点的夜景

### 特别鸣谢

+ 























