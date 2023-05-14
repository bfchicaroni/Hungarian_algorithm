#include "estruturas.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef APS_H_
#define APS_H_

ArvoreAPS *alocaArvore(Grafo *G);

void diferencaSimetrica(ArvoreAPS *T, Emparelhamento *M, int y);

TuplaAPS *APS(Grafo *G, Emparelhamento *M, int u);
#endif