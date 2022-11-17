#include <stdio.h>
#include <stdbool.h>
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
  bool existe;
} Aresta;

//Estrutura que representa um grafo.
typedef struct Grafo {
  Vertice* vertices;
  Aresta* arestas;
  int n; //qtde_vertices
  int m; //qtde_arestas
  int maxArestas;
} Grafo;

typedef struct ArestaEmp {
  int u;
  int v;
  bool emparelhada;
} ArestaEmp;

//Estrutura que representa um emparelhamento.
typedef struct Emparelhamento {
  ArestaEmp *conjuntoArestas;
  bool *vEmparelhados;
  int tamanho;
  int maxArestas;
} Emparelhamento;

#endif