#include <stdio.h>
#include <stdbool.h>
#ifndef ESTRUTURAS_H_
#define ESTRUTURAS_H_

//Estrutura que representa os vértices do grafo.
typedef struct Vertice {
  int rotulo;
  struct Vertice *next;
} Vertice;


//Estrutura que representa um grafo.
typedef struct Grafo {
  Vertice* vertices;
  int n; //qtde_vertices
  int m; //qtde_arestas
  int maxArestas;
} Grafo;

//Estrutura que representa um emparelhamento.
typedef struct Emparelhamento {
  int *vEmparelhados;
  int nVertices;
  int tamanho;
  int maxArestas;
} Emparelhamento;

//Estrutura que representa a árvore APS
typedef struct ArvoreAPS {
  int *pai;
  bool *visitado;
  int nVertices;
} ArvoreAPS;

typedef struct TuplaAPS {
  bool achouEmparelhamento;
  ArvoreAPS* T;
  int u;
  bool* Rt;
  bool* Bt;
  int* Mt;
} TuplaAPS;

#endif