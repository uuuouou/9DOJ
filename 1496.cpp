#include <cstdio>
#include <cstring>
#define MAX_N	1000005
#define MAX_M	100005

int n, m, res, l[MAX_M], r[MAX_M];
bool used[MAX_N];
int father[MAX_N];//father[i] is the first index that used[index] = false
int Find(int x)
{
	return father[x] != x ? father[x] = Find(father[x]) : x;
}

void update(int l, int r)
{
	int i = Find(l), j, k;
	while(i <= r){
		//move j
		for(j = i; j <= r && !used[j]; ++j) used[j] = true;
		if(j - i > res) res = j - i;
		//find next
		k = Find(j);
		//move i
		for(; i < j; ++i) father[i] = k;
		//reset i
		i = k;
	}
}

int main()
{
	int i, j;
	while(scanf("%d%d", &n, &m) == 2){
		//input
		for(i = 1; i <= m; ++i) scanf("%d%d", l+i, r+i);
		//init
		memset(used+1, false, n);
		for(i = 1; i <= n; ++i) father[i] = i;
		father[i] = i;
		res	= 0;
		//update
		for(i = m; i; --i) update(l[i], r[i]);
		//output
		printf("%d\n", res);
	}
	return 0;
}
