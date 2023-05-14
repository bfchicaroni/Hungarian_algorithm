#include "structs.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef APS_H_
#define APS_H_

APSTree *allocatesTree(Graph *G);

void diferencaSimetrica(APSTree *T, Matching *M, int y);

TuplaAPS *APS(Graph *G, Matching *M, int u);
#endif