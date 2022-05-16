// 通过dfs序来建立虚树
// 这种维护关键点dfs序的思想还有很多其他的应用
int DFN[maxn + 5]; // 存储dfs序号
int dep[maxn + 5]; // 存储结点深度, 需保证虚树根结点编号最小
vector<int> seg; // seg存储需要包含的点
int sta[maxn + 5], top = 0;
const bool cmp(const int &a, const int &b) { return DFN[a] < DFN[b]; }
void Build() {
    sort(seg.begin(), seg.end(), cmp); // 按照dfs序排序
    sta[top = 1] = 0; // 选取一个不在原树中的点作为虚树根结点, 保证该结点深度最小
    for(int i = 0; i < seg.size(); ++i) {
        int lca = LCA(sta[top], seg[i]); // 注意此处LCA的点可能不在原树中, 要特判
        while(top >= 2 && dep[sta[top-1]] >= dep[lca])
            AddEdge(sta[top-1], sta[top]), --top; // AddEdge时记得清空原虚树图
        if(sta[top] != lca)
            AddEdge(lca, sta[top]), sta[top] = lca;
        sta[++top] = seg[i];
    }
    while(top >= 2)
        Addedge(sta[top-1], sta[top]), --top;
}
