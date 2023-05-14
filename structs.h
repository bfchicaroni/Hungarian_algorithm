#include <stdbool.h>
#include <stdio.h>
#ifndef ESTRUTURAS_H_
#define ESTRUTURAS_H_

// Estrutura que representa os vértices do grafo.
typedef struct Vertex {
  int label;
  struct Vertex *next;
} Vertex;

// Estrutura que representa um grafo.
typedef struct Graph {
  Vertex *vertices;
  bool *exists;
  int n; // numberOfVertices
  int nExistentes;
  int m; // numberOfEdges
  int maxEdges;
} Graph;

// Estrutura que representa um emparelhamento.
typedef struct Matching {
  int *vEmparelhados;
  int nVertices;
  int size;
  int maxEdges;
} Matching;

// Estrutura que representa a árvore APS
typedef struct APSTree {
  int *pai;
  bool *visitado;
  int nVertices;
} APSTree;

typedef struct TuplaAPS {
  bool foundMatching;
  APSTree *T;
  int u;
  bool *Rt;
  bool *Bt;
  int *Mt;
} TuplaAPS;

typedef struct TuplaHungaro {
  APSTree **tau;
  bool *R;
  bool *B;
  Matching *Mestrela;
  bool *U;
  Graph *F;
} TuplaHungaro;

#endif