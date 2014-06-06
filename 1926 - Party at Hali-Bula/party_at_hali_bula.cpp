#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>

#define forn(i,n) for(int i = 0; i < n; i++)
#define forn1(i,n) for(int i = 1; i <= n; i++)
#define forall(it, vec) for(typeof(vec.begin()) it = vec.begin(); it != vec.end(); it++)
#define MAXN 256
using namespace std;
int memo[2][MAXN];
vector<int> g[MAXN];
bool uniq[2][MAXN];
int _dp(int n, bool inc){
	if(memo[inc][n] != -1) return memo[inc][n];
	int a,b,res=inc?1:0;
	uniq[inc][n] = true;
	forall(it,g[n]){
		a = _dp(*it,0); b = -1;
		if(!inc){
			b = _dp(*it,1);
			if(a==b) uniq[inc][n] = false;
			else if(a > b)
				uniq[inc][n] &= uniq[0][*it];
			else uniq[inc][n] &= uniq[1][*it];
		} else
			uniq[inc][n] &= uniq[0][*it];
		res += max(a,b);
	}
	return memo[inc][n] = res;
}
map<string,int> mp;
int main(){
	int N,a,b, id;
	cin >> N;
	string str;
	while(N){
		//uniq = true;
		memset(memo,-1,sizeof(memo));
		/*forn(i,N+1){
			uniq[0][i] = true;
			uniq[1][i] = true;
		}*/
		mp.clear();
		forn(i,N+1) g[i].clear();
		id = 0;
		cin >> str;
		mp[str] = id++;
		forn(i,N-1){
			cin >> str;
			if(mp.find(str) == mp.end())
				mp[str] = id++;
			a = mp[str];
			cin >> str;
			if(mp.find(str) == mp.end())
				mp[str] = id++;
			b = mp[str];
			g[b].push_back(a);
			
		}
		a = _dp(0,1); b = _dp(0,0);
		if(a < b)
			cout << b << (uniq[0][0]?" Yes":" No") << endl;
		else if(a > b)
			cout << a << (uniq[1][0]?" Yes":" No") << endl;
		else
			cout << a << " No" << endl;
		cin >> N;
	}
	return 0;
}
