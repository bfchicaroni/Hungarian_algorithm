#include "structs.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef APS_H_
#define APS_H_

ArvoreAPS *alocaArvore(Graph *G);

void diferencaSimetrica(ArvoreAPS *T, Matching *M, int y);

TuplaAPS *APS(Graph *G, Matching *M, int u);
#endif