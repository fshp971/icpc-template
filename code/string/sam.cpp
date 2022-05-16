#include<bits/stdc++.h>
using namespace std;

// 后缀自动机(SAM)
// 只有parent树才是树形结构, 且存在严格包含关系
// 而对于正向情况, 同一个State可能被多个不同的其他State找到
// 对于一个State, 其唯一对应于一系列子串, 这些子串的长度构成一个连续闭区间
// 设其上界为Max(s), 下界为Min(s), 则有如下公式:
// Max(s) = s->val, Min(s) = Max(par(s))+1;
// 这在各种计数问题中会用到
// SAM的状态数至少为原串长度的2倍
const int maxn = 1e5, c_size = 26;

struct State {
    int val;
    State *par, *go[c_size];
    void init() { val = 0, par = NULL, memset(go,0,sizeof(go)); }
}que[maxn*2+5], *root, *last;
int tot;

void Extend(int w) {
    State *p = last, *np = que + (tot++);
    np->init();
    np->val = p->val+1;
    while(p!=NULL && p->go[w]==NULL)
        p->go[w] = np, p = p->par;
    if(p == NULL) np->par = root;
    else {
        State *q = p->go[w];
        if(p->val+1 == q->val) np->par = q;
        else {
            State *nq = que + (tot++);
            *nq = *q; // 要小心这里可能存在的数据覆盖问题
            nq->val = p->val+1;
            np->par = q->par = nq;
            while(p!=NULL && p->go[w]==q)
                p->go[w] = nq, p = p->par;
        }
    }
    last = np;
}

void init() {
    root = last = que;
    tot = 1, que[0].init();
}

// SAM计算LCS的计算过程, match是可选的, 需要自己加上
// 最后根据题目要求可以加上基数排序更新最终的match直并计算一些信息
char arr[maxn+5];
int cont[maxn+5], S[maxn*2+5];
void LCS {
    State *p = root;
    int now = 0, len = strlen(arr);
    for(i=0; i<len; ++i) {
        int w = arr[i]-'a';
        if(p->go[w] != NULL) {
            p = p->go[w];
            p->match = max(p->match, ++now);
        }
        else {
            while(p!=NULL && p->go[w]==NULL)
                p = p->par; // 往回找到的串会缩短
            if(p == NULL) p = root, now = 0;
            else {
                now = p->val+1; // 此处要特别注意
                p = p->go[w];
                p->match = max(p->match, now);
            }
        }
    }
    // 基数排序, 设S_len为SAM中字符串的长度
    for(int i=0; i<=S_len; ++i) cont[i] = 0;
    for(int i=0; i<tot; ++i) ++cont[que[i].val];
    for(int i=1; i<=S_len; ++i) cont[i] += cont[i-1];
    for(int i=tot-1; i>=1; --i) S[--cont[que[i].val]] = i;
    // 排序完毕后, 排序后的结果便存在S[0]~S[tot-1]
    // 即在parent树中, 一个结点的孩子必定排在它后面

    // SAM统计第k小字串(第k大类似)
    // 首先确保SAM的状态中存有当前后缀的出现次数cnt
    // 要区分是否统计相同子串的情况(对应的cnt会不同)
    // 然后增设一个sum值, 表示以当前串为前缀的串有多少个
    for(int i = tot - 1; i >= 0; --i) {
        que[S[i]].sum = que[S[i]].cnt; // 特别注意要按照拓扑序遍历
        for(int k = 0; k < c_size; ++k) {
            if(que[S[i]].go[k] != NULL)
                que[S[i]].sum += que[S[i]].go[k]->sum;
        }
    }
    // 最后只要在正向一边dfs一边输出就可以了
}
