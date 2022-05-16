// 计算 a*b%c
// 方法1: 自然溢出法, 时间复杂度O(1)
typedef long long LL;
const long double eps = 1e-8;

LL multi_mod(LL a,LL b,LL c) {
    a%=c, b%=c;
    LL ans=a*b-(LL)((long double)a*b/c+eps)*c;
    if(ans<0) ans+=c;
    return ans;
}

// 方法2: 瞎搞, 类似快速幂, 时间复杂度O(logn)
LL MulMod(LL a, LL b, LL c) {
    //a %= c, b %= c;
    LL ret = 0;
    while(b) {
        if(b&1) ret = (ret+a)%c;
        a = (a+a)%c, b >>= 1;
    }
    return ret;
}
