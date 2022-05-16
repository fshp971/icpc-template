#include<bits/stdc++.h>
using namespace std;
const int maxn = 100000;

int sa[maxn+5], rk[maxn+5], ht[maxn+5];
int ttx[maxn+5], tty[maxn+5], tc[maxn+5];

// len为a的长度, size为字符集大小, 即size值大于最大字符的ascii码;
// 这样计算出的sa数组中, sa[0] = len(即终止字符排最前面),
// 而sa[1] ~ sa[len]中存的即为所要求的原字符串的后缀数组值.
// 以上的len均指a的原始长度
void BuildSA(char *a, int len, int size) {
    a[len++] = '\0'; // 手动添加末尾终止字符
    int *tx = ttx, *ty = tty; // 必须要使用指针, 方便交换数组
    int i, k, p;
    // 以下为直接根据原串首字母进行基数排序
    for(i = 0; i < size; ++i) tc[i] = 0;
    for(i = 0; i < len; ++i) ++tc[tx[i] = a[i]];
    for(i = 1; i < size; ++i) tc[i] += tc[i-1];
    for(i = len - 1; i >= 0; --i) sa[--tc[tx[i]]] = i;

    for(k = 1; k <= len; k <<= 1) {
        // 以下根据第二关键字(即[k,k*2]的字典序)进行排序, 结果存在ty[]中
        // 要仔细分析以下几行的意义
        p = 0;
        for(i = len - k; i < len; ++i) ty[p++] = i;
        for(i = 0; i < len; ++i) if(sa[i] >= k) ty[p++] = sa[i] - k;

        // 以下在保证第二关键字相同的情况下对第一关键字进行基数排序
        for(i = 0; i < size; ++i) tc[i] = 0;
        for(i = 0; i < len; ++i) ++tc[tx[ty[i]]];
        for(i = 1; i < size; ++i) tc[i] += tc[i-1];

        // 重构sa数组及tx
        for(i = len - 1; i >= 0; --i) sa[--tc[tx[ty[i]]]] = ty[i];
        swap(tx, ty);
        p = 1, tx[sa[0]] = 0;
        for(i = 1; i < len; ++i)
            tx[sa[i]] =
                ty[sa[i]] == ty[sa[i-1]]
                && ty[min(sa[i]+k,len-1)] == ty[min(sa[i-1]+k,len-1)]
                ? p-1 : p++;
        if(p >= len) break;
        size = p;
    }
    --len; //回退len
}

// ht[i]表示后缀sa[i]与sa[i-1]的LCP值;
// rk[i]表示后缀i在sa数组中的下标(即后缀i的字典序);
// 则有性质: ht[rk[i]] >= ht[rk[i-1]] - 1;
// 由于所求字符串已添加终止结点, 故rk[len-1]=0, 在计算时要注意不要越界;
// ht的有效值为ht[1] ~ ht[len-1].
void GetHeight(char *a, int len) {
    int i, j, k = 0;
    for(i = 0; i <= len; ++i) rk[sa[i]] = i;
    for(i = 0; i < len; ++i) { // 由于rk[len] = 0, 故无需考虑
        if(k) --k;
        j = sa[rk[i] - 1];
        while(a[i+k] == a[j+k]) ++k;
        ht[rk[i]] = k;
    }
}

int rmq[maxn + 5][MaxStep + 2];
void InitRMQ(int len) {
    for(int i = 1; i <= len; ++i) {
        rmq[i][0] = ht[i]; // 这导致rmq[i][k]存的是sa[i-2^k]~sa[i]之间的串的LCP
        for(int k = 1; (1 << k) <= i; ++k)
            rmq[i][k] = min(rmq[i][k-1], rmq[i - (1<<(k-1))][k-1]);
    }
}

// 进行LCP前应先调用InitRMQ()初始化RMQ数组;
// 要注意这里l != r, 因为后缀数组的RMQ为了构造上的方便,
// 实际上并没有存sa[i]和自身的LCP值;
// 如果一定要求这样的值, 则需要特判.
int LCP(int l, int r) {
    l = rk[l], r = rk[r];
    if(l > r) swap(l, r);
    // 因为rmq[i][k]存的是排名在[i-2^k, i]之间的串的LCP
    // 所以直接在[l,r]区间进行RMQ算出来的值其实是sa[l-1]~sa[r]的LCP值, 因此需要++l
    int i; ++l;
    for(i = 0; (1 << (i+1)) < (r-l+1); ++i);
    return min(rmq[r][i], rmq[l + (1<<i) - 1][i]);
}

int main() {
    int len, c_size;
    char aa[maxn+5];
    scanf("%s", aa);
    len = strlen(aa);
    BuildSA(aa, len, c_size); // c_size应不小于字符串所有字符的ascii码的最大值
    GetHeight(aa, len);
}
