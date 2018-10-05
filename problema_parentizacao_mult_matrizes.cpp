/* 
CENTRO UNIVERSTÁRIO NORTE DO ESPÍRITO SANTO - CEUNES/ UFES
ATIVIDADE COMPLEMENTAR DE ANÁLISE E PROJETO DE ALGORITMOS
CURSO: CIÊNCIA DA COMPUTAÇÃO

OBJETIVO: Programação dinâmica : Problema da parentização de matrizes ótima

CRIADO EM: 
PROFESSOR: Luciana Lee
--------------------------------------------------------------------------------*/

#include <bits/stdc++.h>

using namespace std;

#define INF 999999999

// Calcula e retorna quantidade de alternativas de parentização de produto matrizes
// N : Quantidade de matrizes a serem multiplicadas
unsigned int qtd_alternativas_parentizacao( unsigned int N )
{
	unsigned int soma = 0;
	if ( N < 2 ) return N;
	else
	{
		for ( int k = 1; k < N; k++ )
			soma += qtd_alternativas_parentizacao( k ) * qtd_alternativas_parentizacao( N-k );
		return soma; 
	}
}

// Calcula e retorna a parentização ótima de matrizes
// P : Vetor com as dimensões das matrizes
// N : Quantidade de matrizes na sequẽncia
vector<vector<int>> parentizacao_matrizes( vector<int> P, int N )
{
	vector<vector<int>> M( N+1, vector<int>(N+1,0) ), S( N+1, vector<int>(N+1,0) );
	int i, j, k, q, l;

	for ( l = 2; l <= N; l++ )
	{
		for ( i = 1; i <= N-l+1; i++ )
		{
			j = i + l - 1;
			M[i][j] = INF;
			for ( k = i; k < j; k++ )
			{
				q = M[i][k] + M[k+1][j] + P[i-1]*P[k]*P[j];
				
				if  ( q < M[i][j] )
				{
					M[i][j] = q;
					S[i][j] = k;
				}
			}
		}
	}	

	return S;
}

// Exibir a parentização ótima da solução calculada
// S : Matriz com a solução do problema
// i, j : Início e fim da sequência de matrizes a ser parentizada i <= j
void exibir_parentizacao_otima( vector<vector<int>> S, int i, int j )
{
	if ( i == j )
		cout<<"A_"<<i<<" ";
	else
	{
		cout<<"(";
		exibir_parentizacao_otima( S, i, S[i][j] );
		exibir_parentizacao_otima( S, S[i][j]+1, j );
		cout<<")";
	}
}

int main()
{
	int N;
	cin>>N;
	vector<int> P(N+1,0);

	for ( int k = 0; k <= N; k++ )
		cin>>P[k];

	vector<vector<int>> S = parentizacao_matrizes( P, N );
	exibir_parentizacao_otima( S, 1, N );
	return 0;
}