/* PRECISA:
    I-
        a) IMPLEMENTAR FLOATS MAIORES PARA ACOMODAR A LAT E LON
        b) LER DATA 
        c) ENCONTRAR UMA FORMA DE DAR STORE NO LOCAL EM QUESTÃO
           SALVAR NA STRUCT OU COISA DO TIPO, DEPOIS APLICAR AS
           FORMULAS DO GRAFO 
    
    II - 
        a) TRANSFORMAR TUDO NO CALCULO DO LOCAL I.E PESO (???)
        b) APLICAR FOMULAS DO GRAFO, MONTAR VERTICES E DEPOIS MONTAR
        ARESTAS LENDO OS CAMINHOS,

    III -
        a) APLICAR DISJSKRA APARTIR DOS VALORES DA VISITA
        b) RETORNAR O CAMINHO NO FORMATO QUE O BENHUR QUER*/

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100

typedef struct{
    char nome [5];
    float lat;
    float lon;
    char desc [50];
} Local;

int main() {
    FILE *file;
    char linha[MAX_LINE];

    file = fopen("locais2.csv", "r");

    if (file == NULL) {
        printf("Erro ao abrir arquivo");
        return 1;
    }

    Local locais [41];
    int ler = 0;
    int records = 0;


    do {
    ler = fscanf(file,
    "%4[^,],%f, %f,%49[^,]\n",
    locais[records].nome, 
    &locais[records].lat, 
    &locais[records].lon, 
    locais[records].desc); records++;
    } while (fgets(linha, sizeof(linha), file)); // Leitura e bla bla bla, tá lendo tudo tirando um problema na desc, vou ter que usar desc

    fclose(file);

    printf("Locais e Latitudes Encontradas:\n \n"); // Print Temporario
    for (int i = 0; i < records; i++)
        printf("%s %f %f\n", 
           locais[i].nome, 
           locais[i].lat,
           locais[i].lon);
    
    printf("\n");

    return 0;
}
