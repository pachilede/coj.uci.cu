#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#define MAXN 256
#define INFTO 0x7f7f7f7f
#define forn(i,n) for(int i = 0; i < n; i++)
using namespace std;
int n;
int mt[MAXN][MAXN]; //Matriz de costos (X * Y)
int xy[MAXN], yx[MAXN]; //Matching resultante (X->Y, Y->X)

int lx[MAXN], ly[MAXN], slk[MAXN], slkx[MAXN], prv[MAXN];
char S[MAXN], T[MAXN];
void updtree(int x){
	forn(y,n) if(lx[x] + ly[y] - mt[x][y] < slk[y]){
		slk[y] = lx[x] + ly[y] - mt[x][y];
		slkx[y] = x;
} }
int hungar(){
	forn(i,n){
		ly[i] = 0;
		lx[i] = *max_element(mt[i],mt[i]+n);
	}
	memset(xy,-1,sizeof(xy));
	memset(yx,-1,sizeof(yx));
	forn(m,n){
		memset(S,0,sizeof(S));
		memset(T,0,sizeof(T));
		memset(prv,-1,sizeof(prv));
		memset(slk,0x7f,sizeof(slk));
		queue<int> q;
		#define bpone(e,p) {q.push(e); prv[e] = p; S[e] = 1;updtree(e);}
		forn(i,n) if(xy[i] == -1) { bpone(i,-2); break; }
		int x = 0, y = -1;
		while(y == -1){
			while(!q.empty() && y == -1){
				x = q.front(); q. pop();
				forn(j,n) if(mt[x][j] == lx[x] + ly[j] && !T[j]){
					if(yx[j] == -1){ y = j; break;}
					T[j] = 1;
					bpone(yx[j],x);
				}
			}
			if(y!=-1) break;
			int dlt = INFTO;
			forn(j,n) if(!T[j]) dlt = min(dlt, slk[j]);
			forn(k,n){
				if(S[k]) lx[k] -= dlt;
				if(T[k]) ly[k] += dlt;
				if(!T[k]) slk[k] -= dlt;
			}
			forn(j,n) if(!T[j] && !slk[j]){
				if(yx[j] == -1){
					x = slkx[j]; y = j; break;
				} else {
					T[j] = 1;
					if(!S[yx[j]]) bpone(yx[j],slkx[j]);
				}
			}
		}
		if(y!=-1){
			for(int p = x; p != -2; p = prv[p]){
				yx[y] = p;
				int ty = xy[p]; xy[p] = y; y = ty;
			}
		}else break;
	}
	int res = 0;
	forn(i,n) res += mt[i][xy[i]];
	return res;
}
int main() {
	int N;
	scanf("%d",&N);
	n = N;
	forn(i,N)
		forn(j,N)
			scanf("%d",&mt[i][j]);
	printf("%d ",hungar());

	forn(i,N)
		forn(j,N)
			mt[i][j] = 100-mt[i][j];
	hungar();
	int res = 0;
	forn(i,N)
		res -= mt[i][xy[i]]-100;
	printf("%d\n",res);
	
	return 0;
}

