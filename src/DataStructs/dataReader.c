//
//Created by luana on 4/6/24.
//
//Standart path for reading => "./CSVData/locais.csv"
//

#include "dataReader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 200
#define MAX_LOCAIS 200


struct local{
	char nome[5];
	double lat;
	double lon;
	char desc[50];
};

Local *dr_readAndCreateLocais(const char *filename)
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

void dr_freeLocais(Local *locais) { if (locais != NULL) free(locais); }

int dr_CountLocais(Local *locais)
{
	int count = 0;
	for (int i = 0; i < MAX_LOCAIS; ++i)
	{
		if (locais[i].nome[0] == '\0') { return count; }
		count++;
	}
	return count;
}



int dr_dataReaderTest(int argc)
{
	Local *locais;
	locais = dr_readAndCreateLocais("./CSVData/locais.csv");
	for (int i = 0; i < 35; i++)
	{
		printf("\nLocal %d:\n", i + 1);
		printf("  Nome: %s\n", locais[i].nome);
		printf("  Latitude: %lf\n", locais[i].lat);
		printf("  Longitude: %lf\n", locais[i].lon);
		printf("  Descricao: %s\n", locais[i].desc);
	}
	
	
	dr_freeLocais(locais);
}
