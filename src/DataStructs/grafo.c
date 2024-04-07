#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "grafo.h"

struct _grafo {
	int numnodos;
	bool **arestas;
	float **pesos;
	bool orientado;
};

struct _vertice {
	int valor;
	
};


Grafo Cria(int n, bool orientado)
{
	Grafo self = malloc(sizeof(*self));
	if (self == NULL)
	{
		return NULL;
	}
	
	self->numnodos = n;
	self->orientado = orientado;
	self->arestas = malloc(sizeof(bool *) * self->numnodos);
	self->pesos = malloc(sizeof(float *) * self->numnodos);
	if (self->arestas == NULL || self->pesos == NULL)
	{
		free(self->arestas);
		free(self->pesos);
		free(self);
		return NULL;
	}
	
	for (int i = 0; i < self->numnodos; i++)
	{
		self->arestas[i] = calloc(sizeof(bool), self->numnodos);
		self->pesos[i] = calloc(sizeof(float), self->numnodos);
		if (self->arestas[i] == NULL || self->pesos[i] == NULL)
		{
			Destroi(self);
			return NULL;
		}
	}
	
	return self;
}


void Destroi(Grafo self)
{
	if (self == NULL)
	{
		return;
	}
	
	for (int i = 0; i < self->numnodos; i++)
	{
		free(self->arestas[i]);
		free(self->pesos[i]);
	}
	
	free(self->arestas);
	free(self->pesos);
	free(self);
}


int NumeroVertices(Grafo self)
{
	assert(self != NULL);
	return self->numnodos;
}

void InsereAresta(Grafo self, int origem, int destino, float peso)
{
	assert(self != NULL);
	assert(origem < self->numnodos && origem >= 0);
	assert(destino < self->numnodos && origem >= 0);
	
	self->arestas[origem][destino] = true;
	self->pesos[origem][destino] = peso;
	
	if (!self->orientado)
	{
		self->arestas[destino][origem] = true;
		self->pesos[destino][origem] = peso;
	}
	
	return;
}


void RemoveAresta(Grafo self, int origem, int destino)
{
	assert(self != NULL);
	assert(origem < self->numnodos && origem >= 0);
	assert(destino < self->numnodos && origem >= 0);
	
	self->arestas[origem][destino] = false;
	self->pesos[origem][destino] = 0.0;
	
	if (!self->orientado)
	{
		self->arestas[destino][origem] = false;
		self->pesos[destino][origem] = 0.0;
	}
	
	return;
}


void Print(Grafo self)
{
	printf("grafo{\n");
	for (int from = 0; from < self->numnodos; from++)
	{
		for (int to = 0; to < self->numnodos; to++)
		{
			if (self->arestas[from][to])
			{
				printf("%d -> %d \n", from, to);
			}
		}
	}
	printf("}\n");
}

void ArestasQuePartem(Grafo self, int origem)
{
	assert(self != NULL);
	
	int aresta_origem = origem;
	int destino = 0;
	float peso = 0.0;
	
	// Percorre as arestas que saem de origem
	ProximaAresta(self, &aresta_origem, &destino, &peso);
	while (aresta_origem == origem)
	{
		printf("Aresta: %d -> %d (%.2f)\n", aresta_origem, destino, peso);
		
		if (!ProximaAresta(self, &aresta_origem, &destino, &peso))
		{
			break;
		}
	}
}


void PercoreTodasArestas(Grafo self)
{
	assert(self != NULL);
	int origem = 0;
	int destino = 0;
	float peso = 0.0;
	
	// Percorre todas as arestas do grafo
	while (ProximaAresta(self, &origem, &destino, &peso))
	{
		printf("Aresta: %d -> %d (%.2f)\n", origem, destino, peso);
	}
}

bool ProximaAresta(Grafo self, int *origem, int *destino, float *peso) {
	assert(self != NULL);
	static int indice_orig = -1;
	static int indice_dest = -1;
	
	if (origem != NULL) indice_orig = *origem;
	
	for (int i = indice_orig; i < self->numnodos; i++) {
		int j;
		if (i == indice_orig) j = indice_dest; // Continuar a busca por arestas na mesma linha, começando da coluna onde paramos anteriormente
		else j = 0; // Iniciar a busca por arestas na nova linha a partir da coluna 0
		for (; j < self->numnodos; j++) {
			if (self->arestas[i][j]) {
				*origem = i;
				*destino = j;
				*peso = self->pesos[i][j];
				
				indice_orig = i;
				indice_dest = j + 1;
				
				// Verifica se o índice de destino ultrapassou o número de vértices
				// Se sim, avança para o próximo vértice de origem
				if (indice_dest >= self->numnodos) {
					indice_orig++;
					indice_dest = 0;
				}
				
				return true;
			}
		}
	}
	
	indice_orig = -1;
	indice_dest = -1;
	
	return false;
}


void GrafoTest()
{
	// Cria um gafo
	Grafo graph = Cria(5, true);
	
	// Popula o grafo
	InsereAresta(graph, 0, 1, 1);
	InsereAresta(graph, 1, 2, 2);
	InsereAresta(graph, 1, 3, 3);
	InsereAresta(graph, 3, 1, 3);
	
	printf("Número de vértices: %d \n", NumeroVertices(graph));
	printf("\n");
	Print(graph);
	printf("\n");
	PercoreTodasArestas(graph);
	printf("\n");
	ArestasQuePartem(graph, 1);
	
	RemoveAresta(graph, 1, 2);
	printf("\n");
	ArestasQuePartem(graph, 1);
	
	Destroi(graph);
	
}