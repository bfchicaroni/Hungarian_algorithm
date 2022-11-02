#include <stdio.h>
#ifndef ESTRUTURAS_H_
#define ESTRUTURAS_H_

//Estrutura que representa os vértices do grafo.
typedef struct Vertice {
  int rotulo;
  struct Vertice *next;
} Vertice;

//Estrutura que representa uma aresta.
typedef struct Aresta {
  int u;
  int v;
  int existe;
} Aresta;

typedef struct Grafo {
  Vertice* vertices;
  Aresta* arestas;
  int n; //qtde_vertices
  int m; //qtde_arestas
  int maxArestas;
} Grafo;

#endif