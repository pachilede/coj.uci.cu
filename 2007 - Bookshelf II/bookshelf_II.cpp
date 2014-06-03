#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define INF 11529215046068411
#define MAXN 100100
using namespace std;
int N, L, end;
int height[MAXN], width[MAXN];
long long memo[MAXN];
long long _dp(int start){
	if(memo[start] != -1)
		return memo[start];
	if(start > end)
		return memo[start] = 0;
	if(start == end)
		return memo[start] = height[start];

	int remaining = L - width[start];
	int h = height[start];
	long long result = INF;
	for(int i = start + 1; (i <= end +1) && (remaining >= 0); i++){
		if(height[i] <= h && remaining >= width[i]){
			remaining -= width[i];
			continue;
		}
		result = min(result, _dp(i) + h);
		h = max(h, height[i]);
		remaining -= width[i];
	}
	return memo[start] = result;
}

int main(){
	
	scanf("%d %d", &N, &L);
	
	for(int i = 0; i < N; i++){
		scanf("%d %d", &height[i],&width[i]);
		memo[i] = -1;
	}
	memo[N] = -1;
	end = N-1;
	//for(int i = N; i >= 0; i--)
	//	_dp(i);
	printf("%lld\n", _dp(0));
	return 0;
}
