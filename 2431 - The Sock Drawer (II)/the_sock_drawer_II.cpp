#include <cstdio>
#include <cstring>
using namespace std;
int K;
int c[16];
int s[1<<16];
long long f[16];
int M;

int _suma(int mask){

	if(mask == 0)
		return 0;
	if(s[mask] != -1)
		return s[mask];

	s[mask] = _suma(1<<__builtin_ctz(mask)) + _suma(mask ^ (1<<__builtin_ctz(mask)) );

	return s[mask];
}

double _p(int colores, int s, int mask){
	int x = colores - __builtin_popcount(mask);
	if(x == 0)
		return (double) ((_suma(mask) - colores) * f[colores]) / (M - colores) ;
	else if(s == K)
		return 0;

	double r =  _p(colores, s + 1, mask);
	if( !(mask & (1<<s)) )
		r += _p(colores, s + 1, (mask | (1<<s) )) * ( (double) _suma(1<<s)/(M - colores + x) );

	return r;
}

int main(){
	int t;

	f[0] = 1L;
	for(long long i = 1; i < 16; i++)
		f[i] = f[i-1] * i;

	scanf("%d", &t);
	int caso = 1;
	while(t--){
		scanf("%d", &K);
		memset(s, -1, sizeof(s));

		M = 0;
		for(int i = 0; i < K; i++){
			scanf("%d", &(c[i]));
			s[1 << i] = c[i];
			M += c[i];
		}
		double p = 0;
		for(int c = 1; c <= K; c++)
			p += _p(c, 0, 0)  * (c + 1);
		printf("Case %d: %.3f\n",caso++ ,p);
	}
	return 0;
}
