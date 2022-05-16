// 树分治找重心, 结点下标从1开始
vector<int> G[maxn+5];
int que[maxn+5], fa[maxn+5], sz[maxn+5], msz[maxn+5];
bool ban[maxn+5];
int FindRoot(int x) {
    int s = 1, t = 1;
    que[1] = x, fa[x] = 0; // 结点下标从1开始
    while(s <= t) {
        x = que[s++], sz[x] = 1, msz[x] = 0;
        for(auto v : G[x])
            if(!ban[v] && v!=fa[x])
                que[++t] = v, fa[v] = x;
    }
    for(int i = t; i >= 1; --i) {
        x = que[i], msz[x] = max(msz[x], t-sz[x]);
        // 判断重心的写法比较特殊
        // 这导致找出的点不一定是严格定义上的重心, 但能满足分治的要求
        if((msz[x]<<1) <= t) return x;
        sz[fa[x]] += sz[x], msz[fa[x]] = max(msz[fa[x]], sz[x]);
    }
    assert(false); // 错误检测
    return 0;
}
