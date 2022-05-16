// bzoj-3223: Tyvj 1729 文艺平衡树
// splay模板题, 主要操作为区间翻转
//
// Splay的核心思想就是要把最近访问过的结点移到根结点上
// 所以无论什么样的扩展操作, 只要涉及到查询某个结点x
// 操作到最后都要执行Splay(x,0)
#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;

const int maxn = 1e5 + 10;

// 结点不存在时对应编号为0
// 需保证ch[0][0], ch[0][1], fa[0]这三个变量恒为0
int root = 0, tot = 0; // root保存根结点编号
int val[maxn+5], sz[maxn+5]; // 需要维护的结点信息(例子), val为结点值, sz为子树大小
int ch[maxn+5][2], fa[maxn+5];
bool rev[maxn+5]; // 用于支持区间翻转

// 根据左右孩子更新结点x保存的值, 可自行扩展
void PushUp(int x) {
    sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1;
}

// 下放lazy标记
void PushDown(int x) {
    if(rev[x]) {
        swap(ch[x][0], ch[x][1]), rev[x] = 0;
        if(ch[x][0]) rev[ch[x][0]] ^= 1;
        if(ch[x][1]) rev[ch[x][1]] ^= 1;
    }
}

// 旋转操作, 可以自己判断执行左旋还是右旋
void Rotate(int x) {
    int y = fa[x], d = ch[y][1]==x;
    ch[y][d] = ch[x][d^1];
    if(ch[x][d^1]) fa[ch[x][d^1]] = y;
    if(fa[y]) { // 防止进行非法修改
        int z = fa[y];
        if(ch[z][0] == y) ch[z][0] = x;
        if(ch[z][1] == y) ch[z][1] = x;
    }
    fa[x] = fa[y], fa[y] = x, ch[x][d^1] = y;
    PushUp(y); // 减少PushUp()操作次数
}

// Splay操作, 作用是把结点x旋转到target的孩子上
int top, sta[maxn+5];
void Splay(int x, int target) {
    // 下放lazy标记
    sta[top = 1] = x;
    for(int i = x; i != target; i = fa[i]) sta[++top] = fa[i];
    while(top>0) PushDown(sta[top--]);
    // fa[p] != target: 很关键啊, 不然就会执行非法旋转了
    while(fa[x] != target) {
        int y = fa[x];
        if(fa[y] != target) {
            if((ch[fa[y]][0]==y)^(ch[y][0]==x)) Rotate(x);
            else Rotate(y);
        }
        Rotate(x);
    }
    PushUp(x); // 用于减少PushUp()执行次数, 所以最后一次PushUp()必须执执行
    // 如果target = 0, 意味着要把x旋转变成root结点, 因此这里要更新root
    if(fa[x] == 0) root = x;
}

// 找排序在kth的结点, 并返回对应结点的编号(相当于指针)
int Kth(int k) {
    int x = root;
    while(x) {
        PushDown(x);
        if(k == sz[ch[x][0]]+1) return x;
        if(k <= sz[ch[x][0]]) x = ch[x][0];
        else k -= sz[ch[x][0]]+1, x = ch[x][1];
    }
    assert(false); // 用于调试
    return 0;
}

int n, m, ans[maxn+5];

// 翻转区间[l,r], 原理简单易懂
void Reverse(int l, int r) {
    // 为了实现方便, 所以插入了 0th 和 (n+1)th
    // 因此 (l-1)th 和 (r+1)th 实际对应的是(l-1+1), (r+1+1)
    int x = Kth(l-1+1), y = Kth(r+1+1);
    Splay(x,0), Splay(y,root);
    rev[ch[ch[x][1]][0]] ^= 1;
}

// 建立初始树, 尽可能平衡
int Build(int p, int l, int r) {
    int x = ++tot, mid = (l+r)>>1;
    fa[x] = p, sz[x] = r-l+1, val[x] = mid;
    if(l<=mid-1) ch[x][0] = Build(x, l, mid-1);
    if(mid+1<=r) ch[x][1] = Build(x, mid+1, r);
    return x;
}

// 计算答案
void dfs(int x, int d) {
    PushDown(x);
    ans[ sz[ch[x][0]]+1+d-1 ] = val[x];
    if(ch[x][0]) dfs(ch[x][0], d);
    if(ch[x][1]) dfs(ch[x][1], d+sz[ch[x][0]]+1);
}

int main() {
    // root = 0, tot = 0; // 重置伸展树
    scanf("%d%d", &n, &m);
    root = Build(0, 0, n+1);
    while(m--) {
        int l, r; scanf("%d%d", &l, &r);
        Reverse(l,r);
    }
    dfs(root, 0);
    for(int i = 1; i <= n; ++i)
        printf("%d%c", ans[i], (i==n)?'\n':' ');
    return 0;
}
