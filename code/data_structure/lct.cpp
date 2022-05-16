// uoj-274 【清华集训2016】温暖会指引我们前行
// lct动态维护最大生成树
// lct核心思想是将树剖成一些链, 通过lct按深度维护这些链
#include<bits/stdc++.h>
using namespace std;
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define PER(i,a,b) for(int i=a; i>=b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 4e5;

int ch[maxn+5][2], fa[maxn+5];
int val[maxn+5], mi[maxn+5], len[maxn+5], sum[maxn+5];
bool rev[maxn+5]; // 区间翻转, 主要用于实现快速换根(MakeRoot)

// 判断当前结点是否是一个树链的根
inline bool IsRoot(int x) { return (ch[fa[x]][0]!=x && ch[fa[x]][1]!=x); }
inline void PushUp(int x) {
    sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + len[x];
    mi[x] = min(val[x], min(mi[ch[x][0]], mi[ch[x][1]]));
}
inline void PushDown(int x) {
    if(rev[x]) {
        rev[x] = 0;
        swap(ch[x][0], ch[x][1]);
        if(ch[x][0]) rev[ch[x][0]] ^= 1;
        if(ch[x][1]) rev[ch[x][1]] ^= 1;
    }
}

// 快速旋转
void Rotate(int x) {
    int y = fa[x], d = ch[y][1]==x;
    ch[y][d] = ch[x][d^1];
    if(ch[x][d^1]) fa[ch[x][d^1]] = y;
    if(fa[y]) {
        int z = fa[y];
        if(ch[z][0] == y) ch[z][0] = x;
        if(ch[z][1] == y) ch[z][1] = x;
    }
    fa[x] = fa[y], fa[y] = x, ch[x][d^1] = y;
    PushUp(y);
}

// 一般lct中的splay只需要将结点旋转到伸展树的根即可
// 因此target是不必要的, 可以删掉
int top, sta[maxn+5];
void Splay(int x, int target = 0) {
    sta[top = 1] = x;
    for(int i = x; !IsRoot(i) && fa[x]!=target; i = fa[i]) sta[++top] = fa[i];
    while(top>0) PushDown(sta[top--]);
    while(!IsRoot(x) && fa[x]!=target) {
        int y = fa[x];
        if(!IsRoot(y) && fa[y]!=target)
            Rotate( ((ch[fa[y]][0]==y)^(ch[y][0]==x)) ? x : y );
        Rotate(x);
    }
    PushUp(x);
}

// lct的核心操作是Access(x), 即为将x和它当前的根单独剖成一条链, 这时x是当前链最深的结点
// Split(x,y)是提出x到y的路径作为单独的一条链, 这时x是根, 而y是这条链最深的结点且被Splay()到伸展树的根
// 其他操作简单明了, 在此不做赘述
void Access(int x) { for(int y = 0; x; y = x, x = fa[x]) Splay(x), ch[x][1] = y, PushUp(x); }
void MakeRoot(int x) { Access(x); Splay(x); rev[x]^=1; }
int FindRoot(int x) { Access(x); Splay(x); while(ch[x][0]) { x = ch[x][0], PushDown(x); } return x; }
void Split(int x, int y) { MakeRoot(x); Access(y); Splay(y); }
void Cut(int x, int y) { Split(x,y); if(ch[y][0] == x) ch[y][0] = 0, PushUp(y), fa[x] = 0; }
void Link(int x, int y) { Split(x,y); if(ch[y][0] != x) fa[x] = y; }

int fp[maxn+5]; // 使用并查集判连通性(FindRoot()太慢了)
int find(int x) { return fp[x]==x ? x : fp[x]=find(fp[x]); }

int main() {
    val[0] = mi[0] = 1e9+10; // 为了实现方便而设置的边界条件
    int n, m; scanf("%d%d", &n, &m);
    REP(i,1,n) val[i] = mi[i] = 1e9 + 10, fp[i] = i;
    char ord[10];
    while(m--) {
        scanf("%s", ord);
        if(ord[0] == 'f') {
            int id, u, v, t, l;
            scanf("%d%d%d%d%d", &id, &u, &v, &t, &l);
            id += n+1, ++u, ++v;
            val[id] = mi[id] = t, len[id] = sum[id] = l;
            if(find(u) != find(v)) {
                fp[find(u)] = find(v);
                // 以下操作将边id视为一个结点, 并把其对应的两个端点连到自身
                MakeRoot(u);
                MakeRoot(v);
                fa[v] = id, fa[u] = id;
            }
            else {
                Split(u,v);
                if(mi[v] >= t) continue; // Split(u,v)后v在平衡树根, 因此可以进行这样的操作
                int key = mi[v];
                int x = v;
                while(1) {
                    if(val[x] == key) break;
                    if(ch[x][0] && mi[ch[x][0]] == key) x = ch[x][0];
                    else x = ch[x][1];
                }
                Splay(x); // 重要, x必须要是伸展树根才能进行如下查找
                int y = ch[x][0], z = ch[x][1];
                while(PushDown(y), ch[y][1]) y = ch[y][1];
                while(PushDown(z), ch[z][0]) z = ch[z][0];
                // 以下操作将边x和它对应的两个端点y,z之间的边断掉(即断掉了<x,y>, <x,z>)
                MakeRoot(x);
                Access(y), Splay(y), fa[x] = 0, ch[y][0] = 0, PushUp(y);
                Access(z), Splay(z), fa[x] = 0, ch[z][0] = 0, PushUp(z);
                // 以下操作将u,v连到id
                MakeRoot(u), MakeRoot(v);
                fa[u] = id, fa[v] = id;
            }
        }
        else if(ord[0] == 'm') {
            int u, v;
            scanf("%d%d", &u, &v);
            ++u, ++v;
            if(find(u) != find(v)) puts("-1");
            else {
                Split(u,v);
                printf("%d\n", sum[v]);
            }
        }
        else {
            int id, l;
            scanf("%d%d", &id, &l);
            id += n+1;
            // 以下操作用于修改边id的距离
            Splay(id);
            len[id] = l; PushUp(id);
        }
    }
    return 0;
}
