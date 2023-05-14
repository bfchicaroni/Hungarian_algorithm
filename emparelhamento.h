#include "estruturas.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef EMPARELHAMENTO_H_
#define EMPARELHAMENTO_H_

bool ehEmparelhamento(Grafo *G, Emparelhamento *M);

Emparelhamento *alocaEmparelhamento(Grafo *G);

Emparelhamento *geraEmparelhamentoGuloso(Grafo *G);

void imprimeEmparelhamento(Emparelhamento *M, FILE *foutptr);

bool ehCoberto(int vertice, Emparelhamento *M);

#endif