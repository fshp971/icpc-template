#include<bits/stdc++.h>
using namespace std;
const int maxnode = 1e7, c_size = 127; // 結點個數與字符集大小

struct Tire {
    int top;
    int nex[maxnode+5][c_size+5], val[maxnode+5];
    int fail[maxnode+5], last[maxnode+5];

    void clear() {
        top = val[0] = 0;
        memset(nex[0], 0, sizeof(nex[0]));
    }

    inline int c_id(char c){ return c; } // 自行設定返回值

    void insert(char *a, int vv) {
        int len = strlen(a), u = 0, t;
        for(int i=0; i<len; ++i) {
            t = c_id(a[i]);
            if(!nex[u][t]) {
                nex[u][t] = (++top), val[top] = 0;
                memset(nex[top], 0, sizeof(nex[top]));
            }
            u = nex[u][t];
        }
        val[u] = vv; // 需根據情況設定如何保存關鍵值
    }

    void get_fail() {
        fail[0] = last[0] = 0;
        queue<int> q;
        for(int i=0; i<c_size; ++i) if(int &t = nex[0][i]) {
            fail[t] = last[t] = 0;
            q.push(t);
        }
        while(!q.empty()) {
            int x = q.front(); q.pop();
            for(int i=0; i<c_size; ++i) {
                int u = nex[x][i];
                if(!u) { nex[x][i] = nex[fail[x]][i]; continue; }
                q.push(u);
                int v = fail[x];
                // while(v && !nex[v][i]) v = fail[v];
                fail[u] = nex[v][i];
                // last函數, val在此處的含義爲: 結點是否爲一個串的結尾
                last[u] = val[fail[u]] ? fail[u] : last[fail[u]];
                // 另一種題目的常用寫法
                // match[u] |= match[fail[u]];
            }
        }
    }

    void find(int x) // 查詢所有以該串結尾的字符串
    {
        if(x) {
            // 查詢內容
            // ...;
            find(last[x]);
        }
    }

    // 匹配函數略, 可参考kmp的思路
    // void query(char *a) {
    //     ...;
    // }
};
