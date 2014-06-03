#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
int N, K;
vector<vector<int> > cow;
typedef vector<int>::iterator vit;
int field[100100];
int memo[24][100100];

int main(){
	scanf("%d %d", &N, &K);
	for(int i = 0; i < N; i++){
		vector<int> aux;
		cow.push_back(aux);
	}
	for(int i = 0; i < N-1; i++){
		int a,b;
		scanf("%d %d", &a, &b);
		cow[--a].push_back(--b);
		cow[b].push_back(a);
	}
	
	for(int i = 0; i < N; i++)
		scanf("%d", &memo[0][i]);

	for(int a = 1; a <= K; a++)
		for(int b = 0; b < N; b++){
			memo[a][b] = memo[0][b];
			if(a>=2) memo[a][b] += memo[a-2][b];
			for(vit i = cow[b].begin(); i != cow[b].end(); i++){
				memo[a][b] += memo[a-1][*i];
				if(a >= 2)
					memo[a][b] = memo[a][b] - (memo[a-2][b]);
			}
		}
	
	for(int i = 0; i < N; i++)
		if(K >= 2)
			printf("%d\n", memo[K][i] - memo[K-2][i]);
		else
			printf("%d\n", memo[K][i]);
	return 0;
}
