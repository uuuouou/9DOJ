#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

const double eps = 1e-8;
inline bool isZero(double x)
{
	return fabs(x) < eps;
}
const int dir[4][2] ={
	{1, 0}, {-1, 0}, {0, 1}, {0, -1}
};

int n, m, total;
char map[15][16];
inline bool outOfBorder(int r, int c)
{
	return r < 0 || r >= n || c < 0 || c >= m;
}
inline bool isReachable(int r, int c)
{
	return !outOfBorder(r, c) && map[r][c] != '#';
}
//bfs
struct Position{
	int r, c;
	Position(){}
	Position(int a, int b) : r(a), c(b){}
} start;
bool vis[15][16];
queue<Position> q;
//gauss
double a[255][255], b[255], x[225];

bool bfs()
{
	while(!q.empty()) q.pop();

	q.push(start);
	vis[start.r][start.c] = true;
	while(!q.empty()){
		int r = q.front().r, c = q.front().c;
		q.pop();
		for(int i = 0; i < 4; ++i){
			int x = r + dir[i][0], y = c + dir[i][1];
			if(!isReachable(x, y) || vis[x][y]) continue;
			if(map[x][y] == 'E') return true;
			vis[x][y] = true;
			q.push(Position(x, y));
		}
	}
	return false;
}
void init()
{
	int i, j, k, x, y, adj[4], cnt;
	double t;
	for(i = 0; i < total; ++i){
		for(j = 0; j < total; ++j) a[i][j] = 0.0;
		b[i] = 0.0;
	}
	for(i = 0; i < n; ++i){
		for(j = 0; j < m; ++j){
			if(map[i][j] == '#'){//can not be here
				x = i * m + j;
				a[x][x] = 0.0;
				b[x] = 0.0;
				continue;
			}
			if(map[i][j] == 'E'){//already destination, need 0 step
				x = i * m + j;
				a[x][x] = 1.0;
				b[x] = 0.0;
				continue;
			}

			cnt = 0;
			for(k = 0; k < 4; ++k){
				x = i + dir[k][0];
				y = j + dir[k][1];
				if(isReachable(x, y)){//dependent on those neighbours
					adj[cnt++] = x * m + y;
				}
			}
			x = i * m + j;
			a[x][x] = 1.0;
			t = -1.0 / cnt;//move variables to left
			for(k = 0; k < cnt; ++k) a[x][adj[k]] = t;//coefficients
			b[x] = 1.0;//leave constants at right
		}
	}
}
void print()
{
	for(int i = 0; i < total; ++i){
		for(int j = 0; j < total; ++j){
			printf("%.2f ", a[i][j]);
		}
		printf("%.2f\n", b[i]);
	}
}
double gauss()
{
//	print();
	int i, j, k;
	double t;
	for(i = 0; i < total; ++i){
		if(isZero(a[i][i])){//swap a row that a[j][i] != 0 with this a[i]
			for(j = i+1; j < total; ++j){
				if(!isZero(a[j][i])) break;
			}
			if(j == total) continue;//this is related to a wall
			for(k = i; k < total; ++k){//as previous coefficients are all zeros
				swap(a[i][k], a[j][k]);
			}
			swap(b[i], b[j]);//this must be swapped too !!!
		}
		//use a[i][i] to erase a[j][i]
		for(j = i+1; j < total; ++j){
			if(isZero(a[j][i])) continue;
			t = a[j][i] / a[i][i];
			a[j][i] = 0.0;
			for(k = i+1; k < total; ++k){
				a[j][k] -= t * a[i][k];
			}
			b[j] -= t * b[i];
		}
	}
	//the matrix has been a upper triangle
	k = start.r * m + start.c;
	for(i = total - 1; i >= k; --i){
		if(isZero(a[i][i])){
			x[i] = 0.0;
			continue;
		}
		t = 0.0;
		for(j = total-1; j > i; --j){
			t += a[i][j] * x[j];
		}
		x[i] = (b[i] - t) / a[i][i];
	}
	return x[k];
}

int main()
{
	int i, j;
	while(scanf("%d%d", &n, &m) == 2){
		//initialize and input
		total = n * m;
		start.r = -1;
		for(i = 0; i < n; ++i){
			memset(vis[i], false, m);
			scanf("%s", map[i]);
			if(start.r != -1) continue;
			for(j = 0; map[i][j]; ++j){
				if(map[i][j] == 'S'){
					start.r = i;
					start.c = j;
					break;
				}
			}
		}
		//check if any destination is reachable
		if(bfs()){
			init();
			printf("%.2f\n", gauss());
		}
		else puts("-1");
	}
}
