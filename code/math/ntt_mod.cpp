// 三模数NTT使用的CRT模板
// 具体使用时就是通过三次NTT分别计算出卷积在模m1, m2, m3下的结果
// 然后再把三个结果提供给CRT进行合并, CRT合并时会同时进行(%mod)操作
//
// 额外需要的模板: MulMod(), PowMod()
typedef long long LL;
const int maxn = 5e5 + 10 , G = 3; // 所用到的三个模数原根均为3
const int M[] = {998244353, 1004535809, 469762049};
const LL _M = (LL)M[0] * M[1]; // 这玩意儿不要漏啊(
const int mod = 1e9 + 7; // 实际要用于取模的数
const int m1 = M[0], m2 = M[1], m3 = M[2];
const int inv1 = PowMod(m1 % m2, m2-2, m2);
const int inv2 = PowMod(m2 % m1, m1-2, m1);
const int inv12 = PowMod(_M % m3, m3-2, m3);

LL CRT(LL a1, LL a2, LL a3){
    LL ret = MulMod(a1 * m2 % _M, inv2, _M);
    (ret += MulMod(a2 * m1 % _M, inv1, _M)) %= _M;
    LL ans = ((a3 - ret) % m3 + m3) % m3 * inv12 % m3;
    ans = (ans % mod * (_M % mod) % mod + ret % mod) % mod;
    return ans;
}
