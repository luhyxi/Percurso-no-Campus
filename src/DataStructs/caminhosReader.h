//
// Created by luana on 4/6/24.
//

#ifndef PERCURSO_NO_CAMPUS_CAMINHOSREADER_H
#define PERCURSO_NO_CAMPUS_CAMINHOSREADER_H
#include "locaisReader.h"

typedef struct caminho Caminho;
struct caminho {
	Local* localStart;
	Local* localEnd;
};

Caminho *cr_readAndCreateCaminhos(const char *filename, Local *locais);
void cr_freeCaminhos(Caminho *caminhos);
int cr_CountCaminhos(Caminho *caminhos);
void cr_caminhosReaderTests();



#endif //PERCURSO_NO_CAMPUS_CAMINHOSREADER_H
