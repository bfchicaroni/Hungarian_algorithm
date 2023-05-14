#include "structs.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef EMPARELHAMENTO_H_
#define EMPARELHAMENTO_H_

bool ehEmparelhamento(Graph *G, Matching *M);

Matching *alocaEmparelhamento(Graph *G);

Matching *geraEmparelhamentoGuloso(Graph *G);

void imprimeEmparelhamento(Matching *M, FILE *foutptr);

bool ehCoberto(int vertice, Matching *M);

#endif