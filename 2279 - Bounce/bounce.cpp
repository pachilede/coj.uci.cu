#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
typedef vector<char> vi;
int ox[] = {-1,1,-1,1,-2,2};
int oy[] = {-1,-1,1,1,0,0};
char map[8][15], str[3];
bool visitado[8][15];
char solutions[50][50]; 
int R,C,N, mns;
void dfs(int x, int y, vi &s, int c, bool f){
	
	if(c >= mns) return;
	
	if(visitado[y][x]) return;
	if(x < 0 || x >= (C + C) + 2 * (y%2)) return;
	if(y < 0 || y >= R) return;
	visitado[y][x] = true;
	if(y == R-1) f = true;
	s.push_back(map[y][x]);
	if(c < N){
		for(int i = 0; i < 6; i++)
			dfs(x+ox[i], y+oy[i], s, c+1, f);
	} else if(map[y][x] == s[c%N]) {
		
		if(c > 0 && f && y == 0 && c % N == N-1){
			mns = c;
			for(int i = 0; i <= c; i++)
				solutions[c][i] = s[i%N];
			solutions[c][c+1] = 0;
		} else {
			for(int i = 0; i < 6; i++)
				dfs(x+ox[i], y+oy[i], s, c+1, f);
		}
	}
	s.pop_back();
	visitado[y][x] = false;
}
int main(){
	memset(visitado, 0, sizeof(visitado));
	while(scanf("%d %d %d", &R, &C, &N) == 3 && N != 0){
		mns = 10000000;
		for(int i = 0; i < R; i++)
			for(int j = (i+1) % 2; j < (C + C) + 2 * (i%2); j += 2){
				scanf("%s", str);
				map[i][j] = str[0];
			}
		vi vec;
		for(int i = 1; i < C + C; i += 2)
			dfs(i, 0, vec, 0, false);
		if(mns != 10000000)
			printf("%s\n", solutions[mns]);
		else
			printf("no solution\n");
	}
	return 0;
}
