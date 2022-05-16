// 計算mobius函數
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int max_len = 1e8; // 差不多是極限長度了

LL N = max_len;
bool vis[max_len+5];
int prime[max_len+5];
int mu[max_len+5]; // mobius函數值

void mobius() {
    memset(vis, 0, sizeof(vis));
    int tot = 0;
    mu[1] = 1;
    for(int i=2; i<=N; ++i) {
        if(!vis[i])
            prime[++tot] = i, mu[i] = -1;
        for(int k=1; k<=tot; ++k) {
            if((LL)prime[k] * i > N) break;
            vis[prime[k] * i] = true;
            if(i % prime[k]) mu[i * prime[k]] = -mu[i];
            else {
                mu[i * prime[k]] = 0;
                break;
            }
        }
    }
}
