#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "grafo.h"

struct _grafo{
    int numnodos;
    bool **arestas;
    float **pesos;
    bool orientado;
};


Grafo g_cria(int n, bool orientado) {
    Grafo self = malloc(sizeof(*self));
    if (self == NULL) {
        return NULL;
    }

    self->numnodos = n;
    self->orientado = orientado;
    self->arestas = malloc(sizeof(bool*) * self->numnodos);
    self->pesos = malloc(sizeof(float*) * self->numnodos);
    if (self->arestas == NULL || self->pesos == NULL) {
        free(self->arestas);
        free(self->pesos);
        free(self);
        return NULL;
    }

    for (int i = 0; i < self->numnodos; i++){
        self->arestas[i] = calloc(sizeof(bool), self->numnodos);
        self->pesos[i] = calloc(sizeof(float), self->numnodos);
        if (self->arestas[i]  == NULL || self->pesos[i] == NULL) {
            g_destroi(self);
            return NULL;
        }
    }

    return self;
}


void g_destroi(Grafo self) {
    if (self == NULL) {
        return;
    }

    for (int i = 0; i < self->numnodos; i++) {
        free(self->arestas[i]);
        free(self->pesos[i]);
    }

    free(self->arestas);
    free(self->pesos);
    free(self);
}


int g_nvertices(Grafo self) {
    assert(self != NULL);
    return self->numnodos;
}

void g_ins_aresta(Grafo self, int origem, int destino, float peso) {
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


void g_rem_aresta(Grafo self, int origem, int destino){
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


void g_print(Grafo self)
{
    printf("grafo{\n");
    for (int from = 0; from < self->numnodos; from++){
        for (int to = 0; to < self->numnodos; to++){
            if (self->arestas[from][to]){
            printf("%d -> %d \n", from, to);}
        }
    }
    printf("}\n");
}

void g_arestas_que_partem(Grafo self, int origem) {
    assert(self != NULL);

    int aresta_origem = origem;
    int destino = 0;
    float peso = 0.0;

    // Percorre as arestas que saem de origem
    g_proxima_aresta(self, &aresta_origem, &destino, &peso);
    while (aresta_origem == origem) {
        printf("Aresta: %d -> %d (%.2f)\n", aresta_origem, destino, peso);

        if (!g_proxima_aresta(self, &aresta_origem, &destino, &peso)) {
            break;
        }
    }
}


void g_arestas(Grafo self) {
    assert(self != NULL);
    int origem = 0;
    int destino = 0;
    float peso = 0.0;

    // Percorre todas as arestas do grafo
    while (g_proxima_aresta(self, &origem, &destino, &peso)) {
        printf("Aresta: %d -> %d (%.2f)\n", origem, destino, peso);
    }
}


bool g_proxima_aresta(Grafo self, int *origem, int *destino, float *peso) {
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


int main()
{
    // Cria um gafo
    Grafo graph = g_cria(5, true);

    // Popula o grafo
    g_ins_aresta(graph, 0, 1, 1);
    g_ins_aresta(graph, 1, 2, 2);
    g_ins_aresta(graph, 1, 3, 3);
    g_ins_aresta(graph, 3, 1, 3);

    printf("Número de vértices: %d \n", g_nvertices(graph));
    printf("\n");
    g_print(graph);
    printf("\n");
    g_arestas(graph);
    printf("\n");
    g_arestas_que_partem(graph, 1);

    g_rem_aresta(graph, 1, 2);
    printf("\n");
    g_arestas_que_partem(graph, 1);

    g_destroi(graph);

    return 0;
}
