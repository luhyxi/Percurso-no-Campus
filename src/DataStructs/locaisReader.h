//
// Created by luana on 4/6/24.
//

#ifndef PERCURSO_NO_CAMPUS_LOCAISREADER_H
#define PERCURSO_NO_CAMPUS_LOCAISREADER_H

typedef struct local Local;

Local *lr_readAndCreateLocais(const char *filename);

void lr_freeLocais(Local *locais);
int lr_CountLocais(Local *locais);
void lr_printLocal(Local *l);
Local lr_GetLocalByName(Local *locais, char name[]);


#endif //PERCURSO_NO_CAMPUS_LOCAISREADER_H
