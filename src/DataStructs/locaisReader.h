//
// Created by luana on 4/6/24.
//

#ifndef PERCURSO_NO_CAMPUS_LOCAISREADER_H
#define PERCURSO_NO_CAMPUS_LOCAISREADER_H

typedef struct local Local;

struct local{
	char nome[5];
	double lat;
	double lon;
	char desc[50];
};
Local *lr_readAndCreateLocais(const char *filename);

void lr_freeLocais(Local *locais);
int lr_CountLocais(Local *locais);
void lr_printLocal(Local *l);
Local lr_GetLocalByName(Local *locais, char name[]);
void lr_dataReaderTests();

#endif //PERCURSO_NO_CAMPUS_LOCAISREADER_H
