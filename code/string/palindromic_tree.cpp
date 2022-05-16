#include<bits/stdc++.h>
using namespace std;

// 在回文树(Palindromic Tree)中, 其每个结点代表一个本质不同的回文串
// 其中0号结点表示偶数串的空串, 1号结点表示奇数串的空串
// 0号结点的fail指针指向1号结点(fail[0] = 1)
// 故实际存在的不同回文串个数为tree.tot-2
const int maxn = 1e5, c_size = 26;
struct PTree {
    int tot, last, S_len;
    int len[maxn+5], fail[maxn+5], S[maxn+5];
    // nex[i][w]表示字符串i在前后加上字符w时指向的字符串
    int nex[maxn+5][c_size];

    int newnode(int l) {
        len[tot] = l, fail[tot] = 0;
        // 此处将所有nex赋值为0, 是为了先判断aa形式的回文串, 再判断a形式的回文串
        // 而a形式的回文串是必定存在的
        memset(nex[tot], 0, sizeof(nex[tot]));
        return tot++;
    }

    void init() {
        tot = 0;
        newnode(0), newnode(-1);
        fail[0] = 1, last = 0;
        // 此处为字符串的边界标记
        // 在支持两端添加字符的回文树中, 可以在每次get_fail前重新标记一下两端的边界
        S[S_len = 0] = -1;
    }

    int get_fail(int x) {
        while(S[S_len-len[x]-1] != S[S_len])
            x = fail[x];
        return x;
    }

    void add(int w) {
        S[++S_len] = w;
        last = get_fail(last);
        if(nex[last][w] == 0) {
            int u = newnode(len[last]+2);
            fail[u] = nex[get_fail(fail[last])][w];
            // num[u] = num[fail[u]]+1; 一种十分有用的计数方法
            // 这里的num[u]表示使用了S[S_len]位置的回文串的个数
            nex[last][w] = u;
        }
        last = nex[last][w];
        // return num[last];
    }
};
