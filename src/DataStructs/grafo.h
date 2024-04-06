#ifndef GRAFO_H
#define GRAFO_H

#include <stdbool.h>

typedef struct _grafo *Grafo;

// aloca e inicializa um grafo com n vértices
// o grafo pode ser orientado ou não (afeta o processamento das arestas) 
// retorna um ponteiro para o grafo alocado
Grafo Cria(int n, bool orientado);

// libera a memória usada pelo grafo
void Destroi(Grafo self);

// retorna o número de vértices do grafo
int NumeroVertices(Grafo self);

// insere uma aresta no grafo (ou altera o peso de uma aresta já existente)
void InsereAresta(Grafo self, int origem, int destino, float peso);

// remove uma aresta do grafo
void RemoveAresta(Grafo self, int origem, int destino);

// printa o grafo
void Print(Grafo self);

// inicia uma consulta a arestas do grafo.
// as próximas chamadas a ProximaAresta devem retornar cada aresta do grafo
void PercoreTodasArestas(Grafo self);

// inicia uma consulta a arestas do grafo.
// as próximas chamadas à ProximaAresta devem retornar cada aresta do grafo que parte do vértice origem
void ArestasQuePartem(Grafo self, int origem);

// retorna os dados sobre a próxima aresta de uma consulta
// retorna true se ok ou false se não tem mais arestas ou se não foi iniciada uma consulta
// cada ponteiro pode ser NULL, para o caso de não se estar interessado na informação associada
// não se deve inserir ou remover arestas no grafo com uma consulta em andamento
bool ProximaAresta(Grafo self, int *origem, int *destino, float *peso);

#endif // GRAFO_H
