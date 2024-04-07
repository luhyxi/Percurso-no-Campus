//
//Created by luana on 4/6/24.
//
//Standard path for reading => "./CSVData/locais.csv"
//

#include "locaisReader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 200
#define MAX_LOCAIS 200


Local *lr_readAndCreateLocais(const char *filename)
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
	Local *locais = NULL;
	while (fgets(linha, MAX_LINE, file) != NULL) records_read++;
	
	//>Memory allocation
	rewind(file);
	
	locais = (Local *) malloc(sizeof(Local) * records_read);
	if (locais == NULL)
	{
		printf("Error allocating memory for locais\n");
		fclose(file);
		return NULL;
	}
	
	//>Internal logic
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
	
	//>Return
	return locais;
}

void lr_freeLocais(Local *locais) { if (locais != NULL) free(locais); }

int lr_CountLocais(Local *locais)
{
	int count = 0;
	for (int i = 0; i < MAX_LOCAIS; ++i)
	{
		if (locais[i].nome[0] == '\0') { return count; }
		count++;
	}
	return count;
}

void lr_printLocal(Local *l) {
	printf("Nome: %s\n", l->nome);
	printf("Latitude: %lf\n", l->lat);
	printf("Longitude: %lf\n", l->lon);
	printf("Descrição: %s\n", l->desc);
}

/// Return the local by the name chosen
Local lr_GetLocalByName(Local *locais, char name[])
{
	for (int i = 0; i < MAX_LOCAIS; ++i)
	{
		if (strcmp(locais[i].nome, name) == 0) { return locais[i]; }
	}
	Local error = {""}; // Assuming an empty name represents an error
	return error;
}

/// 'lr_dataReaderTests' tests the implementations
void lr_dataReaderTests()
{
	Local *locais;
	locais = lr_readAndCreateLocais("/home/luana/CLionProjects/Percurso-no-Campus/src/CSVData/locais.csv");
	for (int i = 0; i < lr_CountLocais(locais); i++)
	{
		printf("\nLocal %d:\n", i + 1);
		printf("  Nome: %s\n", locais[i].nome);
		printf("  Latitude: %lf\n", locais[i].lat);
		printf("  Longitude: %lf\n", locais[i].lon);
		printf("  Descricao: %s\n", locais[i].desc);
	}
	printf("\nQuantidade de Locais: %d\n", lr_CountLocais(locais));
	
	Local localExistente = lr_GetLocalByName(locais, "memo");
	Local localInexistente = lr_GetLocalByName(locais, "errado");
	
	lr_printLocal(&localExistente);
	lr_printLocal(&localInexistente);
	lr_freeLocais(locais);
}
