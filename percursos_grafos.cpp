/* 
CENTRO UNIVERSTÁRIO NORTE DO ESPÍRITO SANTO - CEUNES/ UFES
ATIVIDADE COMPLEMENTAR DE ANÁLISE E PROJETO DE ALGORITMOS
CURSO: CIÊNCIA DA COMPUTAÇÃO

OBJETIVO: Percurso em grafos 

CRIADO EM: 
PROFESSOR: Luciana Lee
--------------------------------------------------------------------------------*/

#include <bits/stdc++.h>

using namespace std;

#define INF 9999999


typedef vector<vector<int>> Grafo;

typedef enum { BRANCO, CINZA, PRETO } Cor;

// Cria e retorna um grafo orientado
// V : Ordem do grafo
// E : Quantidade de arestas
Grafo criar_grafo( int V, int E )
{
	Grafo G = Grafo( V, vector<int>() );
	int u, v, p;
	for ( int k = 0; k < E; k++ )
	{
		cin>>u>>v;
		G[u].push_back(v);
	}
	return G;
}

// Exibe na tela o grafo no formato de lista de adjacẽncias
// G : Grafo a ser exibido
// V : Quantidade de vértices
void imprimir_grafo( Grafo G, int V)
{
	int qtd_adj, u, k ;
	for ( u = 0; u < V; u++ )
	{
		cout<<u<<": ";
		qtd_adj = G[u].size();
		for ( k = 0; k < qtd_adj; k++ )
		{	
			cout<<G[u][k]<<" ";
		}
		cout<<endl;
	}
}

// Procedimento de percurso em largura
// G : Grafo no qual será realizado o percurso
// s : Vértice raíz do percurso
// V : Ordem do grafo
vector<int> BFS( Grafo G, int s, int V )
{
	int u, w, qtd_adj;
	vector<int> pred = vector<int>(V,-1), dist = vector<int>(V,INF);
	vector<Cor> cor = vector<Cor>(V,BRANCO);
	queue<int> Q;

	// Inicio do percurso
	cor[s] = CINZA;
	dist[s] = 0;
	pred[s] = -1;
	Q.push(s);

	while (!Q.empty())
	{
		u = Q.front();
		Q.pop();
		qtd_adj = G[u].size();
		
		for ( int v = 0; v < qtd_adj; v++ )
		{
			w = G[u][v];
			if ( cor[w] == BRANCO )
			{
				cor[w] = CINZA;
				dist[w] = dist[u] + 1;
				pred[w] = u;
				Q.push(w);
			}
		}

		cor[u] = PRETO;
	}

	return pred;
}

int main()
{
	int V, E;
	cin>>V>>E;
	Grafo G = criar_grafo( V, E );
	vector<int> pred_BFS = BFS( G, 0, V );
	imprimir_grafo( G, V );

	return 0;
}