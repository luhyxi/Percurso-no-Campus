//
// Created by luana on 4/6/24.
//

#ifndef PERCURSO_NO_CAMPUS_DATAREADER_H
#define PERCURSO_NO_CAMPUS_DATAREADER_H

typedef struct local Local;

Local *dr_readAndCreateLocais(const char *filename);

void dr_freeLocais(Local *locais);

#endif //PERCURSO_NO_CAMPUS_DATAREADER_H
