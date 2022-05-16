// hdoj-6190 ICPC2017广西邀请赛 shift-and模版题
#include<bits/stdc++.h>
using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = int(1e3), maxm = 1e6, md = 1e9 + 7, c_size = 26;

struct Node {
    int fa, cc;
    // dp[i] = true 表示存在一个长度为i且以当前结点为末尾的串;
    // res[i]=true 表示长度为i的字串在当前结点对应的串中出现过;
    bitset<maxn + 1> dp, res;
} tree[maxm + 5];

struct Que {
    int l, r, u, n;
    Que(): l(0), r(0), u(0), n(0) {}
    Que(int _l, int _r, int _u, int _n) {
        l = _l, r = _r, u = _u, n = _n;
    }
};

vector<Que> arr;
// f[c][i]为真表示模式串第i个位置可以放字母c;
bitset<maxn + 1> f[c_size];

int main() {
    int T, n, u, v, l, r, tot;
    char str[10], ord[10];
    LL ans;
    tree[0].dp.reset(), tree[0].dp[0] = 1;
    tree[0].res.reset();
    while(~scanf("%d", &T)) {
        n = tot = 0;
        arr.clear();
        for(int i = 0; i < c_size; ++i) f[i].reset();
        while(T--) {
            scanf("%s", ord);
            if(ord[1] == 'D') {
                scanf("%d%d%s", &u, &v, str);
                tree[v].fa = u, tree[v].cc = str[0] - 'a';
                tot = v;
            } else if(ord[1] == 'S') {
                scanf("%d%d%d", &l, &r, &u);
                arr.push_back(Que(l, r, u, n));
            } else {
                scanf("%s", str), l = str[0] - 'a';
                scanf("%s", str), r = str[0] - 'a';
                ++n;
                for(int i = l; i <= r; ++i)
                    f[i][n] = 1; // f的构建
            }
        }
        for(int i = 1; i <= tot; ++i) {
            Node &x = tree[i];
            x.dp = (tree[x.fa].dp << 1) & f[x.cc]; // shift-and关键步骤
            x.dp[0] = 1; // 注意这里的赋值
            x.res = tree[x.fa].res | x.dp;
        }
        ans = 0;
        for(auto it: arr) {
            int cnt = (tree[it.u].res>>it.l).count() - (tree[it.u].res>>(it.r+1)).count();
            ans = (ans * 233 + (cnt ? 1 : 2)) % md;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
