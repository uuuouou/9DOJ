#include <cstdio>
#define MAX	100005

int n, a[MAX], f[MAX][17];

inline int min(int a, int b){ return a < b ? a : b; }
void init()
{
	int i, k, len;
	for(i = 1; i <= n; ++i) f[i][0] = a[i];
	for(i = 1; (len = 1 << i) <= n; ++i){
		for(k = 1; k + len <= n+1; ++k){
			f[k][i] = min(f[k][i-1], f[k+(len>>1)][i-1]);
		}
	}
}
int query(int l, int r)
{
	int len = r - l + 1, i = 0;
	for(; (1 << i+1) < len; ++i) ;
	return min(f[l][i], f[r-(1<<i)+1][i]);
}

int main()
{
	int i, l, r, t;
	while(scanf("%d", &n) == 1){
		for(i = 1; i <= n; ++i) scanf("%d", a + i);
		init();
		for(scanf("%d", &t); t--; ){
			scanf("%d%d", &l, &r);
			printf("%d\n", query(l, r));
		}
	}
	return 0;
}
