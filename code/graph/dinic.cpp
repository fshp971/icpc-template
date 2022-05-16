//Power By Metowolf
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

const int MAXN = 100 + 10;
const int INF = 1e9;
struct Edge {
	int from, to, cap, flow;
};
struct Dinic {
	int n, m, s, t;
	vector<Edge> edges; //边表，edges[e]和edges[e^1]互为反向弧
	vector<int> G[MAXN]; //邻接表，G[i][j]表示结点i的第j条边在e数组中的序号
	bool vis[MAXN]; //BFS使用
	int d[MAXN]; //从起点到i的距离
	void AddEdge(int from, int to, int cap) {
		edges.push_back((Edge) {
			from, to, cap, 0
		});
		edges.push_back((Edge) {
			to, from, 0, 0
		});
		m = edges.size();
		G[from].push_back(m - 2);
		G[to].push_back(m - 1);
	}
	bool BFS() { //使用BFS计算出每一个点在残量网络中到t的最短距离d
		memset(vis, 0, sizeof(vis));
		queue<int> Q;
		Q.push(s);
		vis[s] = 1;
		d[s] = 0;
		while(!Q.empty()) {
			int x = Q.front();
			Q.pop();
			for(int i = 0; i < G[x].size(); ++i) {
				Edge &e = edges[G[x][i]];
				if(!vis[e.to] && e.cap > e.flow) {
					vis[e.to] = 1;
					d[e.to] = d[x] + 1;
					Q.push(e.to);
				}
			}
		}
		return vis[t];
	}
	int DFS(int x, int a) { //使用DFS从S出发，沿着d值严格递减的顺序进行多路增广
		if(x == t || a == 0) return a;
		int flow = 0, f;
		for(int i = 0; i < G[x].size(); ++i) {
			Edge &e = edges[G[x][i]];
			if(d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0) {
				e.flow += f;
				edges[G[x][i] ^ 1].flow -= f;
				flow += f;
				a -= f;
				if(a == 0) break;
			}
		}
		return flow;
	}
	int Maxflow(int s, int t) {
		this->s = s;
		this->t = t;
		int flow = 0;
		while(BFS())
			flow += DFS(s, INF);
		return flow;
	}
};
Dinic g;
