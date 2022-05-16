// 完全k短路, 求有向图中起点ss到终点tt的第k短路
// 支持自环, 重边, 非负边, 不连通图
// 可并堆是通过随机化实现的, 如果被卡的话就换成左偏树(红书有板)
// 这里的所有路径, 是包括单点的, 即若ss==tt时单点也算路径, 可能需要根据题目具体修改
// 同时, 这里的路径上每个点是可以重复走的(不过不重复走好像也做不了)
//
// 若是无向图, 照着稍微修改一下也能做, 但要注意同一条边的编号不要维护错
// (大概需要单独再开一个数组存编号, 然后就不需要再分正向/反向边了)
//
// 如果要求k长路的话, 首先要保证起点到终点的路径不会成环(不会出现无穷长路)
// 这样才能保证终点tt到其他点有最长路
// 然后要把可并堆改成最大堆, 同时优先队列中传入的权值也不能传相反数
// 以及用INF判连通性的部分, 也要改(本来用INF就是个偷懒的写法)
//
// 代码有很多细节(各种正负号什么的, 变量名还长), 小心别敲错
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<algorithm>
#include<queue>

using namespace std;

#define MP make_pair
#define fi first
#define se second
typedef long long LL;

const LL INF = 1LL<<60; // 无穷大还是有点用的...
const int maxn = 1000; // 点数上界
const int maxE = 100000; // (有向边) 边数上界
const int maxnode = 500000 * 10; // 可并堆结点个数上界, 在不影响性能的前提下尽量开大

struct Node {
    int l, r;
    LL val; // 最短路增加值 (用心体会)
    int to; // 接下来会到达的点
    Node() {}
    Node(LL _val, int _to) : l(0), r(0), val(_val), to(_to) {}
} heap[maxnode + 5];
int tot = 0, rt[maxn+5];

int Merge(int x, int y) {
    if(!x || !y) return x|y;
    if(heap[x].val > heap[y].val) swap(x,y); // 由于是求最短路, 所以是最小堆
    int t = ++tot;
    heap[t] = heap[x];
    (rand()&1) ? (heap[t].l = Merge(heap[t].l,y)) : (heap[t].r = Merge(heap[t].r,y));
    return t;
}

int n, m; // n个结点, m条有向边
LL dist[maxn+5];
priority_queue< pair<LL,int> > q1;
queue<int> q2;

int top = 0;
int h1[maxE+5], e1[maxE+5], w1[maxE+5], nx1[maxE+5]; // 正向边
int h2[maxE+5], e2[maxE+5], w2[maxE+5], nx2[maxE+5]; // 反向边
bool flag[maxE+5]; // 用于标记对应编号的边是否属于最短路树边

// 同时添加有向图中正向和反向边
inline void AddEdge(int u, int v, int d) {
    ++top, flag[top] = 0; // flag[]必须要清空
    e1[top] = v, w1[top] = d, nx1[top] = h1[u], h1[u] = top;
    e2[top] = u, w2[top] = d, nx2[top] = h2[v], h2[v] = top;
}

// 根据反向边计算x到其他所有点的最短路
void Dij(int x) {
    while(!q1.empty()) q1.pop(); // 清空q1
    for(int i = 1; i <= n; ++i)  dist[i] = INF;
    dist[x] = 0, q1.push( MP(-0LL,x) );
    while(!q1.empty()) {
        LL d = -q1.top().fi;
        int x = q1.top().se;
        q1.pop();
        if(dist[x] != d) continue;
        for(int i = h2[x]; i; i = nx2[i]) {
            if(w2[i]+dist[x] < dist[e2[i]]) {
                dist[e2[i]] = w2[i] + dist[x];
                 // 因要求最短路, 所以要用相反数作为优先队列权值
                q1.push( MP( -dist[e2[i]], e2[i] ) );
            }
        }
    }
}

// 求ss到tt的第kk短路, kk >= 1
// 无解返回-1
LL KthPath(int ss, int tt, int kk) {
    // 清除树边标记, 若要做多次k短路则每次都需要清标记
    // REP(i,1,m) flag[i] = 0;

    Dij(tt); // 根据反向边计算tt到其他所有点的最短路

    // 构建最短路树
    for(int x = 1; x <= n; ++x) {
        if(x==tt || dist[x]==INF) continue;
        // 注意此时应使用正向边判断
        for(int i = h1[x]; i; i = nx1[i])
            if(e1[i]!=x && dist[e1[i]]!=INF && dist[e1[i]]+w1[i]==dist[x]) {
                flag[i] = 1; break;
            }
    }

    // 根据最短路树构建可并堆
    for(int i = 1; i <= n; ++i) rt[i] = 0; // 清堆
    tot = 0, q2.push(tt);
    while(!q2.empty()) {
        int x = q2.front(); q2.pop();
        if(dist[x] != INF) { // 只从非树边扩展
            for(int i = h1[x]; i; i = nx1[i]) if(flag[i]==0 && dist[e1[i]]!=INF) {
                heap[++tot] = Node( dist[e1[i]]+w1[i] - dist[x], e1[i] );
                rt[x] = Merge(rt[x], tot);
            }
        }
        for(int i = h2[x]; i; i = nx2[i]) if(flag[i]) {
            rt[e2[i]] = rt[x], q2.push(e2[i]);
        }
    }

    // 以下开始求kk短路, 无解返回-1
    if(dist[ss] == INF) return -1LL;
    //if(ss == tt) ++kk;
    if(kk == 1) return dist[ss]; // 最短路也是一条路径
    --kk;
    while(!q1.empty()) q1.pop();
    if(rt[ss])
        q1.push( MP( -(dist[ss]+heap[rt[ss]].val), rt[ss]) );
    while(!q1.empty() && (kk--)) {
        LL d = -q1.top().fi;
        int x = q1.top().se;
        q1.pop();
        if(kk == 0) return d;
        if(rt[heap[x].to])
            q1.push( MP( -(d+heap[rt[heap[x].to]].val), rt[heap[x].to] ) );
        d -= heap[x].val;
        if(heap[x].l)
            q1.push( MP( -(d+heap[heap[x].l].val), heap[x].l ) );
        if(heap[x].r)
            q1.push( MP( -(d+heap[heap[x].r].val), heap[x].r ) );
    }
    return -1LL;
}

int main() {
    srand(time(NULL)); // 一定要初始化随机数, 不然可并堆复杂度就炸了
    //srand(19260817);
    while(~scanf("%d%d", &n, &m)) {
        // 以下为初始化部分
        tot = top = 0; // 注意区分 tot 和 top
        for(int i = 1; i <= n; ++i) h1[i] = h2[i] = 0;

        // 读入图, AddEdge()中有清除flag[]标记
        for(int i = 1, u,v,d; i <= m; ++i) {
            scanf("%d%d%d", &u, &v, &d);
            AddEdge(u,v,d);
        }
        int ss, tt, kk; // 起点ss; 终点tt; 第kk短路;
        scanf("%d%d%d", &ss, &tt, &kk);

        printf("%lld\n", KthPath(ss,tt,kk));
    }
    return 0;
}
