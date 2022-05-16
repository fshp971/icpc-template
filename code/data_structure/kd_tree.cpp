// hdu-5992 KD-Tree模板题(其实是因为数据太弱)
// 对于每个询问, 找出价格不超过给定值的欧氏距离最近结点的编号
//
// 只有建树和查找部分
// KD-Tree查找方法的本质就是搜索剪枝+启发式乱搞
// 插入直接类似建树瞎模拟一遍即可
// 插入可能需要通过替罪羊树实现高度平衡
// 简单来说就是插入后找到最浅层的不平衡度超过阈值的点(即sz1>sz2*a, a一般取0.7)
// 然后dfs出该结点对应子树的所有结点编号并存在num[]中, 然后使用Build()重建子树
// 然而替罪羊树在实际应用中相当慢, 所以不到万不得已时尽量别使用
//
// 此模板仅用于比赛时回忆KD-Tree的实现细节, 应尽量做到能裸敲KD-Tree
#include<bits/stdc++.h>
using namespace std;

#define REP(i,a,b) for(int i=a; i<=b; ++i)
typedef long long LL;
const int maxn = 2e5;

struct Node {
    int x[2], mi[2], mx[2], mic, c, id, l, r;
} tr[maxn+5];
int D, num[maxn+5]; // num[]保存将要用于建树的结点编号

// 对num[]进行比较, 注意这里的大写D别打错
bool cmp(const int &a, const int &b) { return tr[a].x[D] < tr[b].x[D]; }

int Build(int l, int r, int d) {
    int mid = (l+r) >> 1;
    D = d; // 用于cmp()排序
    nth_element(num+l, num+mid, num+r+1, cmp);
    int x = num[mid]; // 注意num[mid]才是实际上的结点编号
    tr[x].mi[0] = tr[x].mx[0] = tr[x].x[0];
    tr[x].mi[1] = tr[x].mx[1] = tr[x].x[1];
    tr[x].mic = tr[x].c;
    tr[x].l = tr[x].r = 0;
    if(l<mid) {
        tr[x].l = Build(l, mid-1, d^1); // 使用(d^1)维对下一层建树
        REP(i,0,1) {
            tr[x].mi[i] = min(tr[x].mi[i], tr[tr[x].l].mi[i]);
            tr[x].mx[i] = max(tr[x].mx[i], tr[tr[x].l].mx[i]);
        }
        tr[x].mic = min(tr[x].mic, tr[tr[x].l].mic);
    }
    if(mid<r) {
        tr[x].r = Build(mid+1, r, d^1);
        REP(i,0,1) {
            tr[x].mi[i] = min(tr[x].mi[i], tr[tr[x].r].mi[i]);
            tr[x].mx[i] = max(tr[x].mx[i], tr[tr[x].r].mx[i]);
        }
        tr[x].mic = min(tr[x].mic, tr[tr[x].r].mic);
    }
    return x;
}

LL dist;
int pid;
inline LL sqr(LL x) { return x*x; }
void Query(int x, Node &pt) {
    if(tr[x].c <= pt.c) {
        LL tmp = 0;
        REP(i,0,1) tmp += sqr(tr[x].x[i]-pt.x[i]);
        if(tmp < dist) dist = tmp, pid = tr[x].id;
        else if(tmp == dist && tr[x].id < pid) pid = tr[x].id;
    }
    LL lc = 0, rc = 0;
    int l = tr[x].l, r = tr[x].r;

    // 搜索剪枝+启发式乱搞
    // 因为此题求的是欧式距离, 所以启发式的函数长下面这样
    if(l) REP(i,0,1) lc += sqr( max(0, tr[l].mi[i]-pt.x[i]) + max(0, pt.x[i]-tr[l].mx[i]) );
    if(r) REP(i,0,1) rc += sqr( max(0, tr[r].mi[i]-pt.x[i]) + max(0, pt.x[i]-tr[r].mx[i]) );
    if(lc < rc) {
        // 在剪枝时一定要仔细思考, 不要把可能的正确答案也剪掉
        if(l && tr[l].mic<=pt.c && lc<=dist) Query(l, pt);
        if(r && tr[r].mic<=pt.c && rc<=dist) Query(r, pt);
    }
    else {
        if(r && tr[r].mic<=pt.c && rc<=dist) Query(r, pt);
        if(l && tr[l].mic<=pt.c && lc<=dist) Query(l, pt);
    }
}

int n, m, xx[maxn+5], yy[maxn+5], cc[maxn+5];
int main() {
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d%d", &n, &m);
        REP(i,1,n) {
            scanf("%d%d%d", xx+i, yy+i, cc+i);
            tr[i].x[0] = xx[i], tr[i].x[1] = yy[i];
            tr[i].c = cc[i], tr[i].id = i;
            num[i] = i; // 一定要把用于建树的结点编号存入num[]中
        }
        int root = Build(1,n,0);
        while(m--) {
            int x, y, c; scanf("%d%d%d", &x, &y, &c);
            Node nd;
            nd.x[0] = x, nd.x[1] = y, nd.c = c;
            dist = 1LL << 60, pid = 0;
            Query(root, nd);
            printf("%d %d %d\n", xx[pid], yy[pid], cc[pid]);
        }
    }
    return 0;
}
