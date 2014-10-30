#include <cstdio>
#include <cstring>
#define MAX_NODE 1000000
#define MAX_EDGE 2000000

int n, u, d;
struct Edge{
	int to, next;
} edge[MAX_EDGE];
int idx, pre[MAX_NODE];

inline void addEdge(int x, int y)
{
	edge[idx].to = y;
	edge[idx].next = pre[x];
	pre[x] = idx++;
}
void dfs(int x, int fa, int dis)
{
	int i, y;
	for(i = pre[x]; i; i = edge[i].next){
		y = edge[i].to;
		if(y == fa) continue;
		dfs(y, x, dis + 1);
	}
	if(dis > d){
		d = dis;
		u = x;
	}
}

int main()
{
	int i, l, r;
	while(scanf("%d", &n) == 1){
		//initialize
		idx = 1;
		memset(pre, 0, n << 2);
		//input
		for(i = 1; i < n; ++i){
			scanf("%d%d", &l, &r);
			addEdge(l, r);
			addEdge(r, l);
		}
		//dfs to find a node on the diameter
		u = d = 0;
		dfs(0, -1, 0);
		dfs(u, -1, 0);
		printf("%d\n", (d+1)>>1);
	}
}
