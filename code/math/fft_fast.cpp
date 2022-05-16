//计算卷积a(x)*b(x), 结果存在c(x)当中
//a(x)*b(x)结果的最大非零项次数不超过(len-1)
Comp A[maxn + 5], B[maxn + 5];
void Conv(LL *a, LL *b, LL *c, int len) {
    for(int i = 0; i < len; ++i) A[i] = Comp(a[i], b[i]);
    FFT(A, len, 1);
    for(int i = 0; i < len; ++i) {
        int j = (len-i) & (len-1);
        B[i] = (A[i]*A[i] - (A[j]*A[j]).conj()) * Comp(0,-0.25);
    }
    FFT(B, len, -1);
    for(int i = 0; i < len; ++i) c[i] = LL(B[i].re+0.5);
}
