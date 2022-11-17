#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef APS_H_
#define APS_H_

ArvoreAPS* alocaArvore (Grafo* G);

Emparelhamento* diferencaSimetrica(ArvoreAPS* T, Emparelhamento* M, int y, int u);

#endif