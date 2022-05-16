// O(n)构建笛卡尔树
// A[]存储1~n的一个排列, sta[]是一个栈, 存储当前构造出的树的右链
// 每个结点意义为: 当前结点是其所在区间的最大值, 同时改把区间分成不相交的两部分
// 此模板构造的笛卡尔树存在最大堆性质, 可自行修改比较方式
int n, A[maxn + 5], sta[maxn + 5];
int Build() {
    int top = 0;
    for(int i = 1; i <= n; ++i) {
        L[ A[i] ] = R[ A[i] ] = 0;
        int p = top;
        while(p && sta[p] < A[i]) --p; // 可修改比较方式
        if(p>0) R[ sta[p] ] = A[i];
        if(p<top) L[ A[i] ] = sta[p+1];
        sta[++p] = A[i]; top = p;
    }
    return sta[1];
}
