#include "estruturas.h"
#include "grafos.h"
#include "emparelhamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

Emparelhamento* alocaEmparelhamento (Grafo* G) {
  Emparelhamento *M;
  M = malloc(sizeof(Emparelhamento));
  M->vEmparelhados = malloc(G->n*sizeof(int));
  M->nVertices = G->n;
  M->maxArestas = G->maxArestas; 
  M->tamanho = 0;
  int i;
  for (i = 0; i < G->n; i++) {
    M->vEmparelhados[i] = -1;
  }
  return M;
}

Emparelhamento* geraEmparelhamentoGuloso(Grafo* G) {
  Emparelhamento* M = alocaEmparelhamento(G);

    /* 
  pega o 0 e o primeiro vizinho e começa a percorrer as listas a partir do vertice 1
  
  */

  // Vertice* vizinhoDoVerticeZero = G->vertices[0].next;

  // if (vizinhoDoVerticeZero != NULL) {
  //   M->vEmparelhados[0] = vizinhoDoVerticeZero->rotulo;
  //   M->vEmparelhados[vizinhoDoVerticeZero->rotulo] = 0;
  // }

  int i;
  Vertice* vizinho;

  for (i = 0; i < G->n; i++) {
    if (M->vEmparelhados[i] == -1) {
      vizinho = G->vertices[i].next;
      while( vizinho != NULL) {
        if (M->vEmparelhados[vizinho->rotulo] == -1) {
          M->vEmparelhados[i] = vizinho->rotulo;
          M->vEmparelhados[vizinho->rotulo] = i;
          M->tamanho ++;
          vizinho = NULL; //essa linha serve para parar o while
        }
        else {
          vizinho = vizinho->next;
        }
      }
    }
  }
  return M;
}

void imprimeEmparelhamento(Emparelhamento* M) {
  printf("================================================\n");
  printf("Imprimindo emparelhamento de tamanho %d\n", M->tamanho);
  int i;
  for(i=0; i < M->nVertices; i++) {
    if(M->vEmparelhados[i] != -1) {
      if (i < M->vEmparelhados[i]) {
        printf("|%d|---|%d|\n", i, M->vEmparelhados[i]);
      }
    }
  }
}

bool ehCoberto(int vertice, Emparelhamento* M) {
  return (M->vEmparelhados[vertice] != -1);
}
