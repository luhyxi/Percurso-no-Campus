/* PRECISA:
    I-
        a) [X]~~ IMPLEMENTAR FLOATS MAIORES PARA ACOMODAR A LAT E LON ~~ [X]
        b) [X] ~~ LER DATA ~~ [X] (PROVAVEL ERRO, REVISITAR)
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

typedef struct {
    char nome[5];
    double lat;
    double lon;
    char desc[50];
} Local;

int main() {
    FILE* file;
    char linha[MAX_LINE];

    file = fopen("locais2.csv", "r");

    if (file == NULL) {
        printf("Erro ao abrir arquivo");
        return 1;
    }

    Local locais[41];
    int ler = 0;
    int records = 0;

    do {
        ler = fscanf(file,
            "%4[^,],%lf,%lf,%49[^]\n",
            locais[records].nome,
            &locais[records].lat,
            &locais[records].lon,
            locais[records].desc);

        if (ler == 3) {
            // Set desc to an empty string
            strcpy(locais[records].desc, "");
        }

        records++;
    } while (fgets(linha, sizeof(linha), file));

    fclose(file);

    printf("Locais e Latitudes Encontradas:\n\n");
    for (int i = 0; i < records; i++) {
        if (strlen(locais[i].desc) > 0) {
            printf("%s %.15lf %.15lf, %s\n",
                locais[i].nome,
                locais[i].lat,
                locais[i].lon,
                locais[i].desc);
        } else {
            printf("%s %.15lf %.15lf\n",
                locais[i].nome,
                locais[i].lat,
                locais[i].lon);
        }
    }

    return 0;
}
