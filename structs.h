#include <stdbool.h>
#include <stdio.h>
#ifndef ESTRUTURAS_H_
#define ESTRUTURAS_H_

// Estrutura que representa os vértices do grafo.
typedef struct Vertice {
  int rotulo;
  struct Vertice *next;
} Vertice;

// Estrutura que representa um grafo.
typedef struct Graph {
  Vertice *vertices;
  bool *existe;
  int n; // qtde_vertices
  int nExistentes;
  int m; // qtde_arestas
  int maxArestas;
} Graph;

// Estrutura que representa um emparelhamento.
typedef struct Matching {
  int *vEmparelhados;
  int nVertices;
  int tamanho;
  int maxArestas;
} Matching;

// Estrutura que representa a árvore APS
typedef struct ArvoreAPS {
  int *pai;
  bool *visitado;
  int nVertices;
} ArvoreAPS;

typedef struct TuplaAPS {
  bool achouEmparelhamento;
  ArvoreAPS *T;
  int u;
  bool *Rt;
  bool *Bt;
  int *Mt;
} TuplaAPS;

typedef struct TuplaHungaro {
  ArvoreAPS **tau;
  bool *R;
  bool *B;
  Matching *Mestrela;
  bool *U;
  Graph *F;
} TuplaHungaro;

#endif