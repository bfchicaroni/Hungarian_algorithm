#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef APS_H_
#define APS_H_

ArvoreAPS* alocaArvore (Grafo* G);

void diferencaSimetrica(ArvoreAPS* T, Emparelhamento* M, int y);

TuplaAPS* alocaMemoriaAPS (Grafo* G);

TuplaAPS* APS (Grafo* G, Emparelhamento* M, int u);

#endif