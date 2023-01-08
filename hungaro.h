#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef HUNGARO_H_
#define HUNGARO_H_

TuplaHungaro* alocaMemoriaHungaro(Grafo* G, Emparelhamento* M);

int procuraDesemparelhado(Grafo* G, Emparelhamento* M);

void uniao (bool* A, bool* B, int tamanho);

void uniaoEmparelhamento (Emparelhamento* Mestrela, Emparelhamento* M);

void uniaoEmparelhamentoArray (Emparelhamento* Mestrela, int* M);

void subtraiEmparelhamento (Emparelhamento* M, ArvoreAPS* T);

void subtraiGrafo (Grafo* F, ArvoreAPS* T);

TuplaHungaro* hungaro (Grafo* G, Emparelhamento* M);

#endif