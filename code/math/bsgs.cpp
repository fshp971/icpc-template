// 解方程 a^x ≡ b(mod p) , 其中 p 为质数.
// 由费马小定理可知, 只需检查 x = 0, 1, 2, ... , p-1 即可.
// 本例使用大步小步算法 (Baby-Step-Giant-Step algorithm) 求解,
// 无解返回-1.
typedef long long LL;
LL log_mod(LL a, LL b, LL p) {
    // 此处使用 int 来存储 m. 事实上若 m 过大，则必定会超时
    int m = sqrt(p)+1;
    // pow_mod() 为快速幂
    LL vv = inv(pow_mod(a, m, p), p);
    LL tmp = 1;
    unordered_map<LL, int> shank;
    for(int i=0;i<m;++i) {
        if(!shank.count(tmp)) shank[tmp] = i;
        tmp = tmp*a % p;
    }
    for(int i=0;i<m;++i) {
        if(shank.count(b)) return (LL)i*m + shank[b];
        b = b*vv % p;
    }
    return -1;
}
