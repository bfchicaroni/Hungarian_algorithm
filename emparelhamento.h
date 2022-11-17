#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef EMPARELHAMENTO_H_
#define EMPARELHAMENTO_H_

bool ehEmparelhamento (Grafo *G, Emparelhamento* M);

Emparelhamento* alocaEmparelhamento (Grafo* G);

Emparelhamento* pegaEmparelhamento(Grafo* G);

void imprimeEmparelhamento(Emparelhamento* M);

#endif