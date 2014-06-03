#include <cstdio>
#include <cstring>
#define MOD 1000000007
int memo[1024][1024];
int _dp(int n, int k){
	if(n == 0) return 1;
	if(memo[n][k] != -1)
		return memo[n][k];
	memo[n][k]  = _dp(n,k-1);
	if(n >= k)
		memo[n][k] = (memo[n][k] + _dp(n-k,k) ) % MOD;
	return memo[n][k];
}

using namespace std;
int N;
int main(){
	scanf("%d", &N);
	memset(memo,-1,sizeof(memo));
	for(int i = 0; i <= N; i++) memo[i][1] = 1;
	
	memo[0][0] = 1;
	int res = 0;
	for(int i = 1 + (N % 2); i <= N; i+=2)
		res = (res + _dp(N-i,i));
	
	printf("%d\n",res);
	return 0;
}
