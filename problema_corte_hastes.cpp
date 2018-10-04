#include <bits/stdc++.h>

using namespace std;

#define INF_NEG -999999999


// Calcula e retorna maior lucro obtido pelo corte da haste
// p : Vetor com preços de cada parte da haste preço/polegada
// n : Comprimento da haste
int cortar_haste( vector<int> P, int n )
{
	int i, q = 0;

	if ( n != 0 )
	{
		q = INF_NEG;
		
		for ( int i = 1; i <= n; i++ )
			q = max( q, P[i] + cortar_haste( P, n - i ) );
	}

	return q;
}


int main()
{
	int N, p_i;
	cin>>N;
	vector<int> P( N+1, 0 ); 

	for ( int k = 1; k <= N; k++ )
		cin>>P[k];

	cout<<"Maior lucro possível: "<<cortar_haste( P, N )<<endl;
	
	return 0;
}