 #include<bits/stdc++.h>
using namespace std;

const int maxn = 1e5;
const int maxnode = maxn * 20 * 2, c_sz = 10;

struct State {
    int val;
    State *par, *go[c_sz];
    void init() { val = 0, par = NULL, memset(go, 0, sizeof(go)); }
} que[maxnode + 5], *root;
int tot;

// 在线构造算法, ⻓得跟线性SAM几乎一摸一样
State* Extend(int w, State *last) {
    // 注意这一步与线性SAM不不同
    if(last->go[w] != NULL && last->val + 1 == last->go[w]->val)
        return last->go[w];
    State *p = last, *np = que + (tot++);
    np->init();
    np->val = p->val + 1;
    while(p != NULL && p->go[w] == NULL)
        p->go[w] = np, p = p->par;
    if(p == NULL) np->par = root;
    else {
        State *q = p->go[w];
        if(p->val + 1 == q->val) np->par = q;
        else {
            State *nq = que + (tot++);
            *nq = *q;
            nq->val = p->val + 1;
            np->par = q->par = nq;
            while(p != NULL && p->go[w] == q)
                p->go[w] = nq, p = p->par;
        }
    }
    return np;
}

int n, col[maxn + 5];
vector<int> G[maxn + 5];

// 树形构造的关键部分
void dfs(int x, int pre, State *last) {
    last = Extend(col[x], last);
    for(int i = 0; i < G[x].size(); ++i)
        if(G[x][i] != pre)
            dfs(G[x][i], x, last);
}

int main() {
    int u, v;
    scanf("%d%d", &n, &u);
    for(int i = 1; i <= n; ++i) scanf("%d", col + i);
    for(int i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    root = que;
    tot = 1, que[0].init();
    for(int i = 1; i <= n; ++i) {
        if(G[i].size() == 1)
            dfs(i, 0, root);
    }
    long long ans = 0;
    // 统计答案时候和普通的SAM一样
    for(int i = 1; i < tot; ++i)
        ans += que[i].val - que[i].par->val;
    printf("%lld\n", ans);
    return 0;
}
