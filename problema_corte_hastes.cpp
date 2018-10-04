#include <bits/stdc++.h>

using namespace std;

#define INF_NEG -999999999


// Calcula e retorna maior lucro obtido pelo corte da haste
// P : Vetor com preços de cada parte da haste preço/polegada
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

//=====================
// Função auxiliar : Caso memoizado
// Calcula e retorna o maior lucro obtido pelo corte de uma haste
// P : Vetor com preços de cada parte da haste (preço x polegada)
// n : Comprimento da haste
// R : Lucro memorizado para otimização
int corte_haste_memoizado_aux( vector<int> P, int n, vector<int> R )
{
	int q;
	if ( R[n] >= 0 ) 
		return R[n];
	else
	{	
		q = INF_NEG;
		for ( int k = 1; k <= n; k++ )
			q = max( q, P[k] + corte_haste_memoizado_aux( P, n-k, R ) );
	}
	
	R[n] = q;

	return q;
}

// Função geral
// Calcula e retorna o maior lucro possível obtido no corte
// P : Vetor com os preços por polegada
// n : Comprimento da haste
int cortar_haste_memoizado( vector<int> P, int n )
{
	vector<int> R(n+1, INF_NEG );
	
	// Caso haste com comprimento 0
	R[0] = 0;
	return corte_haste_memoizado_aux( P, n, R );
}

//=========================

// Calcula e retorna o maior lucro possível num corte de haste
// P : Vetor com os preços por polegada inteira
// n : Comprimento da haste
int cortar_haste_bottomUp( vector<int> P, int n )
{
	vector<int> R(n+1, 0);
	int q, i, j;
	for ( i = 1; i <= n; i++ )
	{
		q = INF_NEG;
		
		for ( j = 1; j <= i; j++ )
			q = max( q, P[j] + R[i-j] );

		R[i] = q;
	}

	return R[n];
}

// Calcula e retorna o maior lucro possível num corte de haste e vetor com pontos de corte
// P : Vetor com os preços por polegada inteira
// n : Comprimento da haste
// S : Vetor com configuração final de corte
int cortar_haste_bottomUp_estendido( vector<int> P, int n, vector<int> &S )
{
	vector<int> R(n+1, 0);

	int q, i, j;
	for ( i = 1; i <= n; i++ )
	{
		q = INF_NEG;
		
		for ( j = 1; j <= i; j++ )
		{	
			if ( q < P[j] + R[i-j] )
			{
				q = P[j] + R[i-j];
				S[i] = j;
			}
		}

		R[i] = q;
	}

	return R[n];
}

// Exibe pontos de corte resultados da solução do problema
// P : Vetor com os preços por polegada inteira
// n : Comprimento da haste
void imprimir_solucao( vector<int> P, int n )
{
	vector<int> S(n+1,0);
	cout<<"Maior lucro possível (bottomUp_Estendido): "<<cortar_haste_bottomUp_estendido( P, n, S )<<endl;
	cout<<"Configuração de corte:"<<endl;

	while ( n > 0 )
	{
		cout<<S[n]<<" ";
		n -= S[n]; 
	}
}


int main()
{
	int N, p_i;
	cin>>N;
	vector<int> P( N+1, 0 ); 
	
	for ( int k = 1; k <= N; k++ )
		cin>>P[k];

	cout<<"Maior lucro possível: "<<cortar_haste( P, N )<<endl;
	cout<<"Maior lucro possível (Memoizado): "<<cortar_haste_memoizado( P, N )<<endl;
	cout<<"Maior lucro possível (bottomUp): "<<cortar_haste_bottomUp( P, N )<<endl;
	imprimir_solucao( P, N );	
	return 0;
}