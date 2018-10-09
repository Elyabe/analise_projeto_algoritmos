/* 
CENTRO UNIVERSTÁRIO NORTE DO ESPÍRITO SANTO - CEUNES/ UFES
ATIVIDADE COMPLEMENTAR DE ANÁLISE E PROJETO DE ALGORITMOS
CURSO: CIÊNCIA DA COMPUTAÇÃO

OBJETIVO: Programação dinâmica : Problema da mochila 0/1

CRIADO EM: 
PROFESSOR: Luciana Lee
--------------------------------------------------------------------------------*/

#include <bits/stdc++.h>

using namespace std;

int carregar_mochila( vector<int> V, vector<int> P, int n, int C )
{
	vector<vector<int>> K( n+1, vector<int>( C+1, 0 ) );
	int i, w;

	// Para cada elemento disponível
	for ( i = 1; i <= n; i++ )
	{
		for ( w = 1; w <= C; w++ )
		{
			if ( P[i] <= w && V[i] + K[i-1][ w - P[i] ] > K[i-1][w] )
				K[i][w] = V[i] + K[i-1][ w - P[i] ];
			else
				K[i][w] = K[i-1][w];
		}
	}
	
	return K[n][C];
}


int main()
{
	int N, W;
	cin>>N;
	vector<int> w(N+1,0), V(N+1,0);

	for ( int k = 1; k <= N; k++ )
		cin>>V[k]>>w[k];

	cin>>W;

	cout<<carregar_mochila( V, w, N, W );
	return 0;
}