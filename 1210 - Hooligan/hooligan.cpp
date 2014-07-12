#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <cstring>	
#define mp(a,b) make_pair(a,b)
#define forn(i,n) for(int i = 0; i < n; i++)
#define forall(it, vec) for(typeof(vec.begin()) it = vec.begin(); it != vec.end(); it++)
#define MAXN 50
#define INF 9999999
using namespace std;
struct nodo{
	int prev, best;
	vector<int> c;
};
nodo n[50];
int A[MAXN][MAXN];
int edmond_karp(int SOURCE, int SINK){
	int s[MAXN], S,E,F[MAXN][MAXN],FLOW,tmp,it;
	bool v[MAXN];
	memset(F,0,sizeof(F));
	FLOW = 0;
	while(1){
		memset(v,false,sizeof(v));
		n[SOURCE].best = INF;
		n[SOURCE].prev = -1;
		s[0] = SOURCE; S = 0; E = 1; v[SOURCE] = true;
		while(S != E && s[S] != SINK){
			for(it = 0; it < n[s[S]].c.size(); it++){
				tmp = n[s[S]].c[it];
				if(v[tmp] == false && A[s[S]][tmp]-F[s[S]][tmp] > 0){
					v[tmp] = true;
					n[tmp].prev = s[S];
					n[tmp].best = min(n[s[S]].best, A[s[S]][tmp] - F[s[S]][tmp]);
					s[E] = tmp;
					E++;
				}
			}
			S++;
		}
		if(S==E) return FLOW;
		FLOW += n[SINK].best;
		tmp = SINK;
		while(n[tmp].prev != -1){
			F[n[tmp].prev][tmp] += n[SINK].best;
			F[tmp][n[tmp].prev] = -F[n[tmp].prev][tmp];
			tmp = n[tmp].prev;
		}
	}
}
int match[MAXN][MAXN], p[MAXN];
int main(){
	int N,M,G;
	scanf("%d%d%d", &N, &M, &G);
	while(N){
		memset(match,0,sizeof(match));
		memset(A,0,sizeof(A));
		int ini = (N-1) * M;
		forn(i,N){
			p[i] = ini;
			n[i].c.clear();
		}
		n[N].c.clear();
		forn(i,G){
			int a, b; char r;
			scanf("%d %c %d", &a, &r, &b);
			match[a][b] = ++match[b][a];
			switch(r){
				case '<': p[a]--; p[b]++; break;
				case '>': p[a]++;p[b]--; break;
			}
		}
		for(int i = 1; i < N; i++){
			p[0] += M - match[0][i];
			p[i] -= M - match[0][i];
			match[0][i] = M;	
		}
		int src = 0;
		int t = N+1;
		int in = 0;
		for(int i = 1; i < N; i++){
			if(p[i] >= p[0]){
				A[src][i] = p[i] - p[0] + 1;
				n[src].c.push_back(i);
				in += A[src][i];
			 }else{ 
				A[i][t] = p[0] - p[i] - 1;
				n[i].c.push_back(t);
			}
			for(int j = 1; j < N; j++){
				if(i == j) continue;
				A[i][j] = M - match[i][j];
				n[i].c.push_back(j);
			}
		}

		int flow = edmond_karp(src, t); 	
		printf("%s\n", (flow==in)?"Y":"N");
		scanf("%d%d%d", &N, &M, &G);
	}
	return 0;
}
