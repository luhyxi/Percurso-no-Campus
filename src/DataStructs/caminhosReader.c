//
// Created by luana on 4/6/24.
// Maybe it would be better to make it more abstract? I.e. not dependent on locaisReader
//

#include "caminhosReader.h"
#include "locaisReader.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_LINE 100
#define MAX_CAMINHOS 100


Caminho *cr_readAndCreateCaminhos(const char *filename, Local *locais)
{
	//>Reading file
	FILE *file;
	char linha[MAX_LINE];
	
	file = fopen(filename, "r");
	
	if (file == NULL)
	{
		printf("Erro ao abrir arquivo\n");
		return NULL;
	}
	
	int records_read = 0;
	Caminho *caminhos = NULL;
	while (fgets(linha, MAX_LINE, file) != NULL) records_read++;
	
	//>Memory allocation
	rewind(file);
	
	caminhos = (Caminho *) malloc(sizeof(Caminho) * records_read);
	if (caminhos == NULL)
	{
		printf("Error allocating memory for caminhos\n");
		fclose(file);
		return NULL;
	}
	
	//>Internal logic
	records_read = 0;
	while (fgets(linha, MAX_LINE, file) != NULL)
	{
		Caminho caminho;
		char charLocalStart[5];
		char charLocalEnd[5];
		sscanf(linha, "%[^,],%[^,]]", charLocalStart, charLocalEnd);
		
		Local localStart = lr_GetLocalByName(locais, charLocalStart);
		Local localEnd = lr_GetLocalByName(locais, charLocalStart);
		
		caminho.localStart = &localStart;
		caminho.localEnd = &localEnd;
		caminhos[records_read++] = caminho;
	}
	fclose(file);
	
	return caminhos;
}

void cr_freeCaminhos(Caminho *caminhos) { if (caminhos != NULL) free(caminhos); }

int cr_CountCaminhos(Caminho *caminhos)
{
	int count = 0;
	for (int i = 0; i < MAX_CAMINHOS; ++i)
	{
		if (caminhos[i].localStart == NULL) { return count; }
		count++;
	}
	return count;
}

/// 'cr_caminhosReaderTests' tests the implementations
void cr_caminhosReaderTests()
{
	Local *locais;
	locais = lr_readAndCreateLocais("/home/luana/CLionProjects/Percurso-no-Campus/src/CSVData/locais.csv");
	Caminho *caminhos;
	caminhos = cr_readAndCreateCaminhos("/home/luana/CLionProjects/Percurso-no-Campus/src/CSVData/caminhos.csv", locais);
	
	
	cr_freeCaminhos(caminhos);
}
