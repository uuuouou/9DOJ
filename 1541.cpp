#include <cstdio>
#include <cstring>
#define MAX	1005

int n, left[MAX], right[MAX], parent[MAX], count[MAX], root;

void dfs(int i)
{
	count[i] = 1;
	if(left[i] != -1){
		dfs(left[i]);
		count[i] += count[left[i]];
	}
	if(right[i] != -1){
		dfs(right[i]);
		count[i] += count[right[i]];
	}
}
inline int getNodesCount(int x)
{
	return x != -1 ? count[x] : 0;
}
void rotate(int x)
{
	if(x < 1 || x > n || x == root) return;

	int p = parent[x], pp = parent[p];

	count[x] = count[p];
	if(left[p] == x){//x is left child, so rotate to right
		left[p] = right[x];
		if(right[x] != -1) parent[right[x]] = p;
		count[p] -= getNodesCount(left[x]) + 1;
		right[x] = p;
	}
	else{//x is right child, so rotate to left
		right[p] = left[x];
		if(left[x] != -1) parent[left[x]] = p;
		count[p] -= getNodesCount(right[x]) + 1;
		left[x] = p;
	}

	if(pp == -1) root = x;
	else{
		if(left[pp] == p) left[pp] = x;
		else right[pp] = x;
	}
	parent[p] = x;
	parent[x] = pp;
}

int main()
{
	int i, t;
	char s[8];
	while(scanf("%d", &n) == 1){
		//initialize
		memset(parent+1, -1, n << 2);
		//input
		for(i = 1; i <= n; ++i){
			scanf("%d%d", left + i, right + i);
			if(left[i] != -1) parent[left[i]] = i;
			if(right[i] != -1) parent[right[i]] = i;
		}
		for(i = 1; i <= n; ++i){
			if(parent[i] == -1){
				root = i;
				break;
			}
		}
		//dfs and count nodes
		dfs(root);
		//rotate
		scanf("%d", &t);
		while(t--){
			scanf("%s %d", s, &i);
			if(s[0] == 's') printf("%d\n", count[i]);
			else if(s[0] =='p') printf("%d\n", parent[i]);
			else rotate(i);
		}
	}
	return 0;
}
