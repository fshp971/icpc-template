//Tarjan求强连通分量
#include<bits/stdc++.h>
using namespace std;

const int maxn = 10000, maxm = 1000000;

//n为结点个数，m为边数，使用链式前向星存储边
int n, m;
int h[maxn+5], e[maxm+5], nex[maxm+5];

/*
 * scc为强连通块个数，sta[top]为栈顶元素，Index为当前递归时间
 * DFN为时间戳，Low为当前点最早追溯到的时间，Belong为所属分块
 */
int scc, top, Index;
int sta[maxn+5], DFN[maxn+5], Low[maxn+5], Belong[maxn+5];
char Insta[maxn+5];

void init() {
	memset(h, 0, sizeof(h));
	int u, v, tot = 0;
	for(int i=1; i<=m; ++i)
		e[++tot] = v, nex[tot] = h[u], h[u] = tot;
}

void Tarjan(int u) {
	DFN[u] = Low[u] = ++Index;
	sta[++top] = u, Insta[u] = 1;
	for(int i=h[u]; i; i=nex[i]) {
		if(!DFN[e[i]]) {
			Tarjan(e[i]);
			Low[u] = min(Low[u], Low[e[i]]);
		}
		else if(Insta[e[i]])
			Low[u] = min(Low[u], Low[e[i]]);
	}
	int t;
	if(DFN[u] == Low[u]) {
		++scc;
		do {
			//此处可以根据题目要求各种扩展
			t = sta[top--];
			Insta[t] = 0;
			Belong[t] = scc;
		} while(t != u);
	}
}

int main() {
	init();
	scc = top = Index = 0;
	memset(DFN, 0, sizeof(DFN));
	memset(Insta, 0, sizeof(Insta));
	for(int i=1; i<=n; ++i)
		if(!DFN[i])
			Tarjan(i);
	return 0;
}
