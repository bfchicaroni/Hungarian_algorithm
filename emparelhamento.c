#include "estruturas.h"
#include "grafos.h"
#include "emparelhamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool ehEmparelhamento (Grafo *G, Aresta* conjuntoArestas, int tamanhoConjunto) {
  bool *emparelhados = malloc((G->n)*sizeof(bool));
  int i, u, v;
  for(i = 0; i < G->n ; i++) {
    emparelhados[i] = false;
  }
  printf("Tamanho = %d\n", tamanhoConjunto);
  for(i=0; i < tamanhoConjunto; i++) {
    u = conjuntoArestas[i].u;
    v = conjuntoArestas[i].v;
    printf("%d %d\n", u, v);
    if (emparelhados[u] || emparelhados[v]) {
      return false;
    }
    else {
      emparelhados[u] = true;
      emparelhados[v] = true;
    }
  }
  return true;
}

Emparelhamento* alocaEmparelhamento (Grafo* G) {
  Emparelhamento *M;
  M = malloc(sizeof(Emparelhamento));
  M->conjuntoArestas = malloc(G->maxArestas*sizeof(bool));
  M->vEmparelhados = malloc(G->n*sizeof(bool));
  int i;
  for (i = 0; i < G->maxArestas; i++) {
    M->conjuntoArestas[i].u = G->arestas[i].u;
    M->conjuntoArestas[i].v = G->arestas[i].v;
    M->conjuntoArestas[i].emparelhada = false;
  }
  for (i = 0; i < G->n; i++) {
    M->vEmparelhados[i] = false;
  }
  return M;
}

Emparelhamento* pegaEmparelhamento(Grafo* G) {
  Emparelhamento *M = alocaEmparelhamento(G);
  M = malloc(sizeof(Emparelhamento));

  int i, extremidadeU, extremidadeV;

  for (i = 0; i < G->maxArestas; i++) {
    if(G->arestas[i].existe) {
      extremidadeU = M->conjuntoArestas[i].u;
      extremidadeV = M->conjuntoArestas[i].v;
      if( M->vEmparelhados[extremidadeU] == false && M->vEmparelhados[extremidadeV] == false ) {
        M->vEmparelhados[extremidadeU] = true;
        M->vEmparelhados[extremidadeV] = true;
        M->conjuntoArestas[i].emparelhada = true;
      }
    }
  }
  return M;
}