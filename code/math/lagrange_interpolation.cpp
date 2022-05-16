// 51nod-1258 计算\sigma_{i=1}^{n}{i^k} % P, n<=1e18, k<=50000
// 线性插值模板
// 1. 必须要预处理逆元
// 2. 调用Larange()插值前要先求出f(1), f(2), ..., f(n)并保存在f[]中
// 3. 通过n个点插出来的是(n-1)次多项式
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

const int P = 1e9+7;
const int maxn = 50000+10;

LL PowMod(LL a,LL b) {LL r=1; while(b){if(b&1)r=r*a%P; a=a*a%P,b>>=1;} return r;}

// f[i]保存f(i)的值
LL f[maxn+5], inv[maxn+5];
LL pfx[maxn+5], sfx[maxn+5];

// 拉格朗日插值, 通过f(x)在x=1~n共计n个点插出一个n-1次多项式
// 并计算这个n-1次多项式在x处的值
LL Lagrange(LL n, LL x) {
    x %= P;
    LL div = 1;
    for(int i = 1; i <= n-1; ++i)  div = div * LL(-i+P) % P;
    div = PowMod(div, P-2);
    pfx[0] = sfx[n+1] = 1;
    for(int i = 1; i <= n; ++i)  pfx[i] = ((x-i+P)%P) * pfx[i-1] % P;
    for(int i = n; i >= 1; --i) sfx[i] = ((x-i+P)%P) * sfx[i+1] % P;
    LL ret = 0;
    for(int i = 1; i <= n; ++i) {
        ret = (ret + pfx[i-1] * sfx[i+1] % P * div % P * f[i]) % P;
        div = div * inv[i] % P * (P-(n-i)) % P;
    }
    return ret;
}

int main() {
    // 线性预处理逆元 (预处理部分必不可少)
    inv[1] = 1;
    for(int i = 2; i <= maxn; ++i) inv[i] = LL(P-P/i) * inv[P%i] % P;

    // 题目相关处理
    int _; scanf("%d", &_);
    while(_--) {
        LL n;
        int kk;
        scanf("%lld%d", &n, &kk);
        // 因S_k(n)是一个关于n的(k+1)次多项式, 故需要计算1~(kk+2)的点的值
        for(int i = 1; i <= kk+2; ++i) f[i] = (PowMod(i,kk) + f[i-1]) % P;
        printf("%lld\n", Lagrange(kk+2,n));
    }
    return 0;
}
