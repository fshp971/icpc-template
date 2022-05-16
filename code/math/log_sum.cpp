// 当遇到大数运算, 且结果可为浮点数时, 可以考虑转化为对数来运算
// 例: UVa-10883
// 题目要求: 计算 sigma( C(n-1, i) * ai / 2^(n-1) ), i from 0 to n-1
// 将每一项转化为对数后有:
//     log((n-1)!) + log(abs(ai)) - log((n-1-i)!) -log(i!) - (n-1)*log(2).
// 一定要注意 log(x) 中的 x 需严格为正, 计算时要针对非正的情况另行判断.
#include<bits/stdc++.h>
using namespace std;

const int maxn = 50000;

int n;
double f[maxn+10], arr[maxn+10];

void run() {
    f[0] = 0;
    for(int i = 1; i <= maxn; ++i)
        f[i] = f[i-1] + log10(i);
}

double init() {
    cin>>n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        scanf("%lf", arr+i);
    double res = 0;
    for(int i = 0; i <= n-1; ++i) {
        if(arr[i] == 0) continue;
        double tmp = f[n-1] + log10(fabs(arr[i])) - f[n-1-i] - f[i] - log10(2) * (n-1);
        if(arr[i] > 0) res += pow(10, tmp);
        else res -= pow(10, tmp);
    }
    return res;
}

int main() {
    run();
    int T;
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t)
        printf("Case #%d: %.3f\n",t,init());
    return 0;
}
