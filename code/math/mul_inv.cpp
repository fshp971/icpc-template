// 若 a*b ≡ 1(mod p), 则称 b 为 a mod p 时的乘法逆元, 记作a^(-1)
// 乘法逆元存在当且仅当 a 与 p 互质

// 用扩展欧几里得求乘法逆元
// 若逆元不存在, 返回 -1
LL inv(LL a, LL p) {
    LL g,x,y;
    ex_gcd(a,p,g,x,y);
    return g==1 ? (x+p)%p : -1;
}

// 用费马小定理求乘法逆元
// 费马小定理: (1). 若p是一个质数, 则有 a^p ≡ a(mod p)
//             (2). 当a不是p的倍数时有: a^(p-1) ≡ 1(mod p)
// 故当a不是p的倍数时, a^(p-2) 即为a的逆元
LL inv2(LL a, LL p) {
    return pow_mod(a, p-2, p);
}

// 线性求逆元
// 原理: (P/i)*i + (P%i) = 0(mod P) -> i^(-1) = -(P/i) * (P%i)^(-1) (mod P)
LL inv[maxn + 5], P;
LL GetInv(int n) {
    inv[1] = 1;
    for(int i = 1; i <= n; ++i)
        inv[i] = (P-(P/i)) * inv[P%i] % P;
}
