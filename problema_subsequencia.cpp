/* 
CENTRO UNIVERSTÁRIO NORTE DO ESPÍRITO SANTO - CEUNES/ UFES
ATIVIDADE COMPLEMENTAR DE ESTRUTURA DE DADOS II
CURSO: CIÊNCIA DA COMPUTAÇÃO

OBJETIVO: Programação dinâmica : Problema da subsequencia mais longa

CRIADO EM: 
PROFESSOR: Luciana Lee
--------------------------------------------------------------------------------*/

#include <bits/stdc++.h>

using namespace std;


enum Seta
{
	ESQUERDA, DIAGONAL, CIMA
};

// Calcula e retorna a lcs com o maior comprimento possível comum a duas sequências
// X, Y : Strings com as sequências a serem analisadas
vector<vector<Seta>> comprimento_lcs( string X, string Y )
{
	int m = X.size(), n = Y.size(), i, j;
	vector<vector<int>> C( m+1, vector<int>( n+1, 0 ) );
	vector<vector<Seta>> B( m+1, vector<Seta>( n+1) );

	// Para cada elemento de X
	for ( i = 1; i <= m; i++ )
	{
		// Para cada elemento de Y
		for ( j = 1; j <= n; j++ )
		{
			// Desconto pelo fato da string começar em 0
			if ( X[i-1] == Y[j-1] )
			{
				C[i][j] = C[i-1][j-1] + 1;
				B[i][j] = DIAGONAL;
			} else
			{
				if ( C[i-1][j] >= C[i][j-1] )
				{
					C[i][j] = C[i-1][j];
					B[i][j] = CIMA;
				} else
				{
					C[i][j] = C[i][j-1];
					B[i][j] = ESQUERDA;
				}
			}

		}
	}

	return B;
}

// Exibe na tela a maior subsequẽncia comum possível dentre duas sequẽncias
// B : Matriz com a solução calculada
// X : Sequência original
// i, j : Índices do elemento analisado 
void imprimir_lcs( vector<vector<Seta>> B, string X, int i, int j )
{
	// Se i e j são ambos não nulos
	if ( i * j )
	{
		// Se pertence à subsequência comum, então exiba-o
		if ( B[i][j] == DIAGONAL )
		{
			imprimir_lcs( B, X, i-1, j-1 );
			cout<<X[i-1];
		} else
		{
			// Caso contrário, analise o elemento cuja matriz de solução indica
			if ( B[i][j] == CIMA )
				imprimir_lcs( B, X, i-1, j );
			else
				imprimir_lcs( B, X, i, j-1 );
		}
	}
}

int main()
{
	string X, Y;
	vector<vector<Seta>> B;
	
	cin>>X>>Y;
	B = comprimento_lcs( X, Y );
	imprimir_lcs( B, X, X.size(), Y.size() );
	return 0;
}