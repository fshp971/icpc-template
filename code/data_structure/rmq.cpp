LL rmq[maxn + 5][MaxStep + 2];
void InitRMQ(LL *a, int len) { // arr[]爲原始數據, len为数组长度
    for(int i = 1; i <= len; ++i) {
        rmq[i][0] = a[i];
        for(int k = 1; (1 << k) <= i; ++k)
            // 自行修改比较方式
            rmq[i][k] = min(rmq[i][k-1], rmq[i - (1 << (k-1))][k-1]);
    }
}

LL RMQ(int l, int r) {
    int i;
    for(i = 0; (1 << (i+1)) < (r-l+1); ++i);
    return min(rmq[r][i], rmq[l + (1<<i) - 1][i]); // 根據需要修改比較方式
}
