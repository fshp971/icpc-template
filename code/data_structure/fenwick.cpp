// 树状数组
const int max_range = 10000;

// 单点修改, 单点查询的树状数组模板
struct SeqArray {
    int top;
    LL node[max_range+5];
    void add(int x, LL v) { for(; x<=top; x+=x&(-x)) node[x]+=v; }
    LL sum(int x) { LL r=0; for(; x; x-=x&(-x)) r+=node[x]; return r; }
};

// 区间修改, 单点查询
SeqArray T1;

void update(int l, int r, LL del) {
    T1.add(l, del), T1.add(r+1, -del);
}

LL query(int x){ return T1.sum(x); }

// 区间修改, 区间查询(要注意指定树状数组的大小)
SeqArray T1, T2;

void update(int l, int r, LL del) {
    T1.add(l, del), T1.add(r+1, -del, T0);
    T2.add(l, del*l), T2.add(r+1, -del*(r+1));
}

LL sum(int x) {
    return T1.sum(x)*(x+1) - T2.sum(x);
}

LL query(int l, int r) {
    return sum(r) - sum(l-1);
}

// 二维树状数组, 单点修改, 单点查询(有效下标均从1开始)
void Add(int i, int j, int del) {
    for(; i <= MaxRow; i += i&(-i)) {
        int jj = j;
        for(; jj <= MaxCol; jj += jj&(-jj))
            cnt[i][jj] += del;
    }
}

int Sum(int i, int j) {
    int res = 0;
    for(; i > 0; i -= i&(-i)) {
        int jj = j;
        for(; jj > 0; jj -= jj&(-jj))
            res += cnt[i][jj];
    }
    return res;
}

// 二维树状数组, 区间修改, 区间查询(要注意指定树状数组的大小)
struct Tree {
    SeqArray T1, T2, T3, T4;

    void _update(int x, int y, int del) {
        T1.add(x, y, del);
        T2.add(x, y, del*x);
        T3.add(x, y, del*y);
        T4.add(x, y, del*x*y);
    }
    void update(int x1, int y1, int x2, int y2, LL del) {
        _update(x1, y1, del);
        _update(x1, y2+1, -del);
        _update(x2+1, y1, -del);
        _update(x2+1, y2+1, del);
    }
    LL _query(int x, int y) {
        return T1.sum(x,y)*x*y - T2.sum(x,y)*(y+1) - T3.sum(x,y)*(x+1) + T4.sum(x,y);
    }
    LL query(int x1, int y1, int x2, int y2) {
        return _query(x2,y2) - _query(x1-1,y2) - _query(x2,y1-1) + _query(x1-1,y1-1);
    }
};
