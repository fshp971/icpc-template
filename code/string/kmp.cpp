#include<bits/stdc++.h>
using namespace std;

const int max_len = 1e7;

void KMP(char *A, char *B) { // A爲匹配串，B爲模式串
    // 計算失配函數
    int nA = strlen(A), nB = strlen(B);
    int f[max_len + 5], now = 0;
    f[1] = 0;
    for(int i=1; i<nB; ++i) {
        while(now && B[now] != B[i]) now = f[now];
        f[i+1] = B[now] == B[i] ? (++now) : 0;
    }

    // 模式匹配
    now = 0;
    for(int i=0; i<nA; ++i) {
        while(now && B[now] != A[i]) now = f[now];
        if(A[i] == B[now]) ++now;
        if(now == nA) {
            printf("Well Done\n");
            break;
        }
    }
}
