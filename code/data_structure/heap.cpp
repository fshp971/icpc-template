// 可持久化可并堆, 注意要srand(time(NULL))
struct Node {
    int l, r, v; // l(r)保存左(右)结点的编号, 为0表示不存在左(右)孩子; v保存权值
} heap[maxn + 5];
int tot = 0; // 结点从1开始编号, 0表示不存在

// 将根结点编号为x, y的两个堆合并, 返回合并后的堆的根结点编号
int Merge(int x, int y) {
    if(!x || !y) return x|y;
    if(heap[x].v < heap[y].v) swap(x,y); // 此为最大堆
    int t = ++tot;
    heap[t] = heap[x];
    (rand()&1) ? (heap[t].l = Merge(heap[t].l,y)) : (heap[t].r = Merge(heap[t].r,y));
    return t;
}
