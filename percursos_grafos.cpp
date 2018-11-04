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
	int u, w, qtd_adj, raio_G = 0;
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
				raio_G = max( raio_G, dist[w] );
				pred[w] = u;
				Q.push(w);
			}
		}

		cor[u] = PRETO;
	}
	cout<<"Raio de G:"<<raio_G<<endl;
	return pred;
}

// Procedimento de visita em profundidade
// G : Grafo no qual será realizado o percurso
// u : Vértice raíz do percurso
// idCC : Número da componente conexa atual
// time : Contador do tempo de descoberta e exploração
// cor : Vetor com as cores de cada vértice
// pred : Vetor de predecessores no percurso 
// CC : Vetor que associa cada vértice a uma componente conexa
// V : Ordem do grafo
void DFS_visitar( Grafo G, int u, int idCC, int *time, vector<Cor> &cor, vector<int> &pred, vector<int> &CC )
{
	int v;
	*time++;
	// Armazena o u.d
	cor[u] = CINZA;
	int tamAdj = G[u].size();
	for ( int k = 0; k < tamAdj; ++k )
	{
		v = G[u][k];
		if ( cor[v] == BRANCO )
		{	
			cor[v] = BRANCO;
			CC[v] = idCC;
			pred[v] = u;
			DFS_visitar( G, v, idCC, time, cor, pred, CC );
 		}
 		cor[u] = PRETO;
 		*time++;
 		//Armazena  o u.f
	}
}

// Procedimento de percurso em profundidade
// G : Grafo no qual será realizado o percurso
// V : Ordem do grafo
vector<int> DFS( Grafo G, int V )
{
	int u, v, idCC, time;
	vector<int> CC = vector<int>(V,-1), pred = vector<int>(V,-1);
	vector<Cor> cor = vector<Cor>(V,BRANCO);
	idCC = 1;
	time = 0;

	for ( u = 0; u < V; u++ )
		DFS_visitar( G, u, idCC++, &time, cor, pred, CC );

	return pred;
}	


// Procedimento de impressão de caminho no percurso
// pred : vetor de predecessores gerado por um percurso
// s : Vértice origem do percurso
// t : Vértice destino do percurso
void imprimir_percurso( vector<int> pred, int s, int t )
{
	if ( s == t )
	{
		printf( "%d", s );
	} else
	{
		if ( pred[t] < 0 )
			printf("Não há caminho possível");
		else
		{
			imprimir_percurso( pred, s, pred[t] );
			printf(" %d", t );
		}
	}
}


int main()
{
	int V, E;
	cin>>V>>E;
	Grafo G = criar_grafo( V, E );
	vector<int> pred_BFS = BFS( G, 0, V ), pred_DFS = DFS( G, V );
	imprimir_grafo( G, V );

	for ( int k = 0; k < V; k++ )
	{
		imprimir_percurso( pred_BFS, 0, k);
		cout<<endl;
	}
	
	for ( int k = 0; k < V; k++ )
	{	
		imprimir_percurso( pred_DFS, 0, k);
		cout<<endl;
	}

	return 0;
}