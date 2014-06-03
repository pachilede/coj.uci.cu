#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define INF 1073741824
using namespace std;

int mapa[256][256], dp[220][220][512];
int N, M, K;
int valor(int f, int c, int i){
	if(c<0 || c>=M || dp[f][c][i] == -1)
		return INF;
	return dp[f][c][i];
}
void _dp(int f, int c){
	if(dp[f][c][0] != -1)
		return;
	if(c<0 || c>=M)
		return;
	if(f == N-1){
		dp[f][c][0] = mapa[f][c];
		dp[f][c][1] = INF;
		return;
	}
	_dp(f+1, c-1);
	_dp(f+1, c);
	_dp(f+1, c+1);
	int mn = -2, x = 0, y = 0, z = 0;
	int i;
	for(i = 0; (i <= K) && (mn != INF); i++){
		//printf("k: %d i:%d\n", K, i);
		mn = min(valor(f+1,c-1,x), min(valor(f+1,c,y), valor(f+1,c+1,z)));
		dp[f][c][i] = mn;
		if(mn != INF)
			dp[f][c][i] += mapa[f][c];
		if(mn == valor(f+1,c-1,x)) x++;
		else if(mn == valor(f+1,c,y)) y++;
		else if(mn == valor(f+1,c+1,z)) z++;
	}
	dp[f][c][i] = INF;
}

int paths[210*512];
int main(){
	memset(dp,-1,sizeof(dp));
	scanf("%d %d %d", &N, &M, &K);
	
	for(int i = 0; i < N; i++)
		for(int j = 0; j < M; j++)
			scanf("%d", &mapa[i][j]);
	for(int i = 0; i < M; i++)
		_dp(0, i);
	
	
	int c = 0;
	for(int i = 0; i < M; i++){
		int j = 0;
		while(dp[0][i][j] != INF){
			paths[c] = dp[0][i][j];
			j++;
			c++;
		}
	}
	
	sort(paths, paths + c);
	printf("%d", paths[0]);
	for(int i = 1; i < K; i++) 
		printf(" %d", paths[i]);
	printf("\n");
	return 0;
}
