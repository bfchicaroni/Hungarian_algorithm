#include "structs.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef HUNGARO_H_
#define HUNGARO_H_

TuplaHungaro *alocaMemoriaHungaro(Graph *G, Matching *M);

int procuraDesemparelhado(Graph *G, Matching *M);

void uniao(bool *A, bool *B, int size);

void matchingUnion(Matching *Mestrela, Matching *M);

void matchingUnionArray(Matching *Mestrela, int *M);

void matchingSubtraction(Matching *M, APSTree *T);

void subtraiGrafo(Graph *F, APSTree *T);

TuplaHungaro *hungaro(Graph *G, Matching *M);

#endif