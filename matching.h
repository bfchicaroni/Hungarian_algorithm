#include "structs.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef MATCHING_H_
#define MATCHING_H_

bool isMatching(Graph *G, Matching *M);

Matching *allocatesMatching(Graph *G);

Matching *makeGreedyMatching(Graph *G);

void printMatching(Matching *M, FILE *foutptr);

bool ehCoberto(int vertice, Matching *M);

#endif