#include <iostream>
#include <utility>
#include <stack>
using namespace std;

const int LEFT  = 1;
const int RIGHT = 2;
typedef pair<int,int> PII;
typedef unsigned __int64 ULL;

stack<PII> path;
ULL findPos(ULL x, ULL y)
{
	while(x != 1 && y != 1){
		if(x > y){
			path.push(make_pair(RIGHT, int(x / y)));
			x %= y;
		}
		else{
			path.push(make_pair(LEFT, int(y / x)));
			y %= x;
		}
	}
	if(x != 1) path.push(make_pair(RIGHT, int(x - 1)));
	if(y != 1) path.push(make_pair(LEFT, int(y - 1)));

	ULL n = 1;
	PII t;
	while(!path.empty()){
		t = path.top();
		path.pop();
		if(t.first == LEFT){
			for(; t.second; --t.second) n <<= 1;
		}
		else{
			for(; t.second; --t.second) n = n << 1 | 1;
		}
	}
	return n;
}

stack<int> move;
pair<ULL,ULL> getNode(ULL n)
{
	for(; n != 1; n >>= 1){
		if(n & 1) move.push(RIGHT);
		else move.push(LEFT);
	}

	ULL l = 1, r = 1;
	for(; !move.empty(); move.pop()){
		if(move.top() == LEFT) r += l;
		else l += r;
	}
	return make_pair(l, r);
}


int main()
{
	int n, t;
	ULL i;
	pair<ULL,ULL> node;

	for(cin >> n; n--; ){
		cin >> t;
		if(t == 1){
			cin >> i;
			node = getNode(i);
			cout << node.first << " " << node.second << "\n";
		}
		else{
			cin >> node.first >> node.second;
			cout << findPos(node.first, node.second) << "\n";
		}
	}
	return 0;
}
