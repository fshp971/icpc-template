#include<bits/stdc++.h>
using namespace std;


// const LL P = (2615053605667LL << 18) + 1, G = 3;
// const LL P = (190734863287LL << 18) + 1, G = 3;
// const LL P = (15LL << 27) + 1, G = 31;
// const LL P = ((7 * 17) << 23) + 1, G = 3;
// const LL P = ((3 * 3 * 211) << 19) + 1, G = 5;
// const LL P = (25 << 22) + 1, G = 3;
const LL P = (479 << 21) + 1, G = 3;
const int maxn = 1<<18;

// type=1为DFT运算, type=-1为DFT逆运算
void NTT(LL *a, int len, int type) {
    int i, j, k, l;
    for(i=1, j=len>>1; i<len-1; ++i) {
        if(i<j) swap(a[i], a[j]);
        k = len>>1;
        while(j>=k)
            j -= k, k >>= 1;
        j += k;
    }
    LL var, step, u, v;
    for(l=2; l<=len; l<<=1) {
        step = pow_mod(G, (P-1)/l);
        for(k=0; k<len; k+=l) {
            var = 1;
            for(i=k; i<k+l/2; ++i) {
                u = a[i], v = var*a[i+l/2] % P;
                a[i] = (u+v) % P;
                a[i+l/2] = (u-v+P) % P;
                var = var*step % P;
            }
        }
    }
    if(type == -1) {
        for(i=1; i<len/2; ++i) swap(a[i], a[len-i]);
        LL inv = pow_mod(len, P-2);
        for(i=0; i<len; ++i) a[i] = a[i]*inv % P;
    }
}

int main() {
    // n必须是2的幂, 若不足则在后面补0
    // n指的是NTT后算出的结果的多项式长度, 故 n >= len(aa) + len(bb)
    int n = 1<<10;
    // aa[i]表示 x^i 项的系数, bb[i]类似
    Comp aa[n+5], bb[n+5];
    NTT(aa, n, 1);
    NTT(bb, n, 1);
    for(int i=0; i<n; ++i)
        aa[i] = aa[i]*bb[i] % P;
    NTT(aa, n, -1);
    return 0;
}
