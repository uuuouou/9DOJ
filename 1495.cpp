#include <cstdio>
#include <cstring>
#include <set>
#include <queue>
using namespace std;
#define MAX_NODE	10005
#define MAX_EDGE	200005
#define INF			0x66666666

int n, m, s, t;
set<int> neighbour[MAX_NODE];
queue<int> q;
bool inq[MAX_NODE];
int dis[MAX_NODE];
int in[MAX_NODE], out[MAX_NODE];

void build()
{
	for(int i = 1; i <= n; ++i) neighbour[i].clear();

	int x, y;
	for(int i = 0; i < m; ++i){
		scanf("%d%d", &x, &y);
		neighbour[x].insert(y);
		neighbour[y].insert(x);
	}
}
void spfa()
{
	memset(inq+1, 0, n);
	memset(dis+1, 0x66, n << 2);

	dis[s] = 0;
	q.push(s);
	inq[s] = true;

	set<int>::iterator iter, eter;
	while(!q.empty()){
		int x = q.front(); q.pop(); inq[x] = false;
		iter = neighbour[x].begin();
		eter = neighbour[x].end();
		for(; iter != eter; ++iter){
			int y = *iter;
			if(dis[y] > dis[x] + 1){
				dis[y] = dis[x] + 1;
				if(!inq[y]){
					q.push(y);
					inq[y] = true;
				}
			}
		}
	}
}
int findCrucial()
{
	memset(inq+1, 0, n);
	memset(in+1, 0, n << 2);
	memset(out+1, 0, n << 2);

	q.push(t);
	inq[t] = true;

	set<int>::iterator iter, eter;
	while(!q.empty()){
		int levelCount = q.size();
		while(levelCount--){
			int x = q.front(); q.pop(); inq[x] = false;
			iter = neighbour[x].begin();
			eter = neighbour[x].end();
			for(; iter != eter; ++iter){
				int y = *iter;
				if(dis[x] == dis[y] + 1){
					++out[x];
					++in[y];
					if(!inq[y]){
						q.push(y);
						inq[y] = true;
					}
				}
			}
		}
	}

	int total = 0;
	for(int i = 1; i <= n; ++i){
		if(in[i] > 1 || out[i] > 1){
			//printf("in[%d] = %d, out[%d] = %d\n", i, in[i], i, out[i]);
			++total;
		}
	}
	return total - (in[s] > 1) - (out[t] > 1);
}

int main()
{
	while(scanf("%d%d%d%d", &n, &m, &s, &t) == 4){
		build();
		spfa();
		if(dis[t] == INF) puts("0");
		else printf("%d\n", findCrucial());
	}
	return 0;
}
