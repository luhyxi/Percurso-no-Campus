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

#include "DataStructs/grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 200


// TODO: Passar isso tudo para outra struct ou entity
typedef struct {
	char nome[5];
	double lat;
	double lon;
	char desc[50];
} Local;

Local *readLocais()
{
	FILE *file;
	char linha[MAX_LINE];
	
	file = fopen("./CSVData/locais.csv", "r");
	
	if (file == NULL)
	{
		printf("Erro ao abrir arquivo\n");
		return NULL;
	}
	
	int records_read = 0;
	Local *locais = NULL;
	while (fgets(linha, MAX_LINE, file) != NULL) records_read++;
	
	rewind(file);
	locais = (Local *) malloc(sizeof(Local) * records_read);
	if (locais == NULL)
	{
		printf("Error allocating memory for locais\n");
		fclose(file);
		return NULL;
	}
	
	records_read = 0;
	while (fgets(linha, MAX_LINE, file) != NULL)
	{
		Local local;
		int itemsScanned = sscanf(linha, "%[^,],%lf,%lf,%49[^\n]", local.nome, &local.lat, &local.lon, local.desc);
		
		if (itemsScanned >= 3)
		{
			if (itemsScanned == 3)
			{
				local.desc[0] = '\0';
			}
			locais[records_read++] = local;
		} else fprintf(stderr, "Error parsing line: %s\n", linha);
		
	}
	
	fclose(file);
	return locais;
}

void freeLocais(Local *locais)
{
	if (locais != NULL)
	{
		free(locais);
	}
}


int main(int argc)
{
	Local *locais;
	locais = readLocais();
	for (int i = 0; i < 35; i++)
	{
		printf("\nLocal %d:\n", i + 1);
		printf("  Nome: %s\n", locais[i].nome);
		printf("  Latitude: %lf\n", locais[i].lat);
		printf("  Longitude: %lf\n", locais[i].lon);
		printf("  Descricao: %s\n", locais[i].desc);
	}
	
	
	freeLocais(locais);
}
