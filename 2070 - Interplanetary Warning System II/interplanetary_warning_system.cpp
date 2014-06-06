#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#define forn(i,n) for(int i = 0; i < n; i++)
#define forn1(i,n) for(int i = 1; i <= n; i++)
#define forall(it, vec) for(typeof(vec.begin()) it = vec.begin(); it != vec.end(); it++)
#define mp make_pair
#define MAXN 30100
using namespace std;
int path[MAXN], d[MAXN];
typedef pair<int, int> pii;
vector<pii> g[MAXN];

pii farthest(int n, int p, int dst){
	pii res;
	res.first = dst;
	res.second = n;
	d[n] = 0;
	path[n] = -1;
	forall(it,g[n]){
		if((*it).second == p) continue;
		pii aux = farthest((*it).second,n, dst + (*it).first);
		if(aux.first > res.first || (aux.first == res.first && aux.second < res.second)){
			res = aux;
			path[n] = (*it).second;
			d[n] = (*it).first;
		}
	}
	return res;
}
vector<pii> best;
bool diam[MAXN];
void dfs(int n, int p, int dst){
	if(diam[n]) return;
	best.push_back(mp(dst,n));
	forall(it,g[n])
		if((*it).second != p) dfs((*it).second, n,dst+(*it).first);
}

int main(){

	int T,N,K,a,b,c,aux;
	
	pii f;
	cin >> T;
	while(T--){
		cin >> N >> K;
		memset(path,-1,sizeof(path));
		best.clear();
		forn(i,N+1) g[i].clear();
		forn(i,N-1){
			cin >> a >> b >> c;
			g[a].push_back(mp(c,b));
			g[b].push_back(mp(c,a));
		}
		f = farthest(1,-1,0);
		a = f.second;
		f = farthest(a,-1,0);
		b = f.second;
		c = f.first;
		aux = a;
		memset(diam,0,sizeof(diam));
		while(aux != -1){
			diam[aux] = true;
			aux = path[aux];
		}
		
		aux = 0;
		while(a!=-1){
			int x = max(c-aux,aux);
			best.push_back(mp(x,a));
			forall(it,g[a])
				dfs((*it).second,a,x+(*it).first);
			aux += d[a];
			a = path[a];
		}
		sort(best.begin(),best.end());
		
		forn(i,K)
			cout << best[i].second << " " << best[i].first << endl;
		cout << endl;
		
	}
	return 0;
}
