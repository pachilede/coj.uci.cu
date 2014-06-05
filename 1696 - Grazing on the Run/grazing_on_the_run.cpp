#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define INF 1152921504606846976
using namespace std;
int N, L;
vector<int> clump;
long long memo[1024][1024];
long long dp(int pos, int next, long long remaining){
	if(remaining == 0 && pos <= N-1 && pos >= 0)
		return 0;

	if(pos < 0 || pos > N-1)
		return INF;
	if(memo[pos][next] != -1)
		return memo[pos][next];

	long long a , b;
	if(pos < next){
		a = dp(pos-1, next, remaining-1) + remaining * (clump[pos] - clump[pos-1]);
		b = dp(next, pos-1, remaining-1) + remaining * (clump[next] - clump[pos]); 	
	} else {
		a = dp(pos+1, next, remaining-1) + remaining * (clump[pos+1] - clump[pos]);
		b = dp(next, pos+1, remaining-1) + remaining * (clump[pos] - clump[next]); 
		
	}
	//printf("entra pos:%d next:%d resultado: %d\n", pos, next, min(a,b));
	return memo[pos][next] = min(a,b);
}
int main(){
	memset(memo,-1,sizeof(memo));
	scanf("%d %d", &N, &L);
	for(int i = 0; i < N; i++){
		int aux;
		scanf("%d", &aux);
		clump.push_back(aux);
	}
	sort(clump.begin(), clump.end());
	int start = lower_bound(clump.begin(), clump.end(), L) - clump.begin();
	//printf("start: %d\n", start);
	long long a,b;
	if(start == N)
		a = b = dp(N-1, N-2, N-1) + N * (L - clump[N-1]);
	else if(start == 0)
		a = b = dp(0, 1, N-1) + N * (clump[0] - L);
	else if(clump[start] == L){
		a = dp(start, start+1, N-1);
		b = dp(start, start-1, N-1);
	} else {
		a = dp(start, start-1, N-1) + N * (clump[start] - L);
		b = dp(start-1, start, N-1) + N * (L - clump[start-1]);
	}
	long long r = min(a,b);
	printf("%lld\n", r);
	return 0;
}
