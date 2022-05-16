// 中国剩余定理 (Chinese Remainder Theorem)
// 考虑同余方程组 x ≡ ai (mod mi)
// 其中, m1, m2, ... mn 两两互质, 设 M = Pai(mi), Mi = M / mi
// 则该方程组在 mod M 的剩余系中有唯一解:
//      x0 = sigma(ai * Mi * (Mi)^-1)
//  其中, (Mi)^-1 为 Mi 在 mod mi 下的乘法逆元
//  而对于一般情况, x = x0 + kM , k为整数
typedef long long LL;

LL CRT(int len, LL *ai, LL *mi) {
    LL M = 1, res = 0, x,y,g;
    for(int i=0;i<len;++i) M *= mi[i];
    for(int i=0;i<len;++i) {
        LL tmp = M / mi[i];
        ex_gcd(tmp, mi[i], g, x, y);
        x = (x+mi[i]) % mi[i];
        //注意此处可能会溢出
        res = (res + ai[i] * tmp * x) % M;
    }
    return res;
}
