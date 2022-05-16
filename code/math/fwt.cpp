#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

const int maxn = (1 << 18) + 100;
const int md = 1e9 + 7; // 要模的数自行修改

// type = 1为FWT运算, type = -1为FWT逆运算
// 以下为OR运算
void FWT(LL *a, int len, int type) {
    for(int l = 1; l < len; l <<= 1) {
        for(int i = 0; i < len; i += (l << 1))
            for(int k = 0; k < l; ++k) {
                LL x = a[i + k], y = a[i + k + l];
                if(type == 1)
                    a[i + k + l] = (x + y) % md;
                else
                    a[i + k + l] = (y - x + md) % md;
            }
    }
}

int main() {
    // n必须是2的幂, 若不足则在后面补0
    // n指的是FWT后算出的结果的多项式长度, 故n >= len(aa) + len(bb)
    LL n = 1 << 10;
    // aa[i]表示x^i项的系数，bb[i]类似
    int aa[n + 5], bb[n + 5];
    FWT(aa, n, 1);
    FWT(bb, n, 1);
    for(int i = 0; i < n; ++i)
        aa[i] = aa[i] * bb[i] % md;
    FWT(aa, n, -1);
    return 0;
}
