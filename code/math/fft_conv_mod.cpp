// 计算a(x)*b(x)%md, 结果存在c(x)中
// a(x)*b(x)的最大非零项次数应小于(len-1)
const int md = 1e9 + 7, mmd = sqrt(md) + 1;
Comp A[maxn + 5], B[maxn + 5], C[maxn + 5], D[maxn + 5];
void Conv(LL *a, LL *b, LL *c, int len) {
    for(int i = 0; i < len; ++i) {
        A[i] = Comp(a[i]/mmd, b[i]/mmd);
        B[i] = Comp(a[i]%mmd, b[i]%mmd);
    }
    FFT(A, len, 1); FFT(B, len, 1);
    for(int i = 0; i < len; ++i) {
        int j = (len-i) & (len-1);
        C[i] = (A[i]*A[i] - (A[j]*A[j]).conj()) * Comp(0, -0.25);
        // 下面这步也可以拆开计算, 若拆开的话后面合并时也要进行相应修改
        C[i] += (A[i]*B[i] - (A[j]*B[j]).conj()) * Comp(0.5, 0);
        D[i] = (B[i]*B[i] - (B[j]*B[j]).conj()) * Comp(0, -0.25);
    }
    FFT(C, len, -1); FFT(D, len, -1);
    for(int i = 0; i < len; ++i) {
        c[i] = LL(C[i].re+0.5) % md * mmd * mmd % md;
        c[i] = (c[i] + LL(C[i].im+0.5) % md * mmd % md) % md;
        c[i] = (c[i] + LL(D[i].re+0.5) % md) % md;
    }
}
