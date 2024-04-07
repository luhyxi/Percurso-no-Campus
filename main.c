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

#include "src/DataStructs/locaisReader.h"
#include "src/DataStructs/caminhosReader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc)
{
	Local *locais;
	locais = lr_readAndCreateLocais("/home/luana/CLionProjects/Percurso-no-Campus/src/CSVData/locais.csv");
	Caminho *caminhos;
	caminhos = cr_readAndCreateCaminhos("/home/luana/CLionProjects/Percurso-no-Campus/src/CSVData/caminhos.csv", locais);
	
	lr_dataReaderTests();
	cr_caminhosReaderTests();
}
