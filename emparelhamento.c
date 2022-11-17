#include "estruturas.h"
#include "grafos.h"
#include "emparelhamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool ehEmparelhamento (Grafo *G, Emparelhamento* M) {
  bool *emparelhados = malloc((G->n)*sizeof(bool));
  int i, u, v;
  for(i = 0; i < G->n ; i++) {
    emparelhados[i] = false;
  }
  printf("Tamanho = %d\n", M->tamanho);
  for(i=0; i < M->tamanho; i++) {
    u = M->conjuntoArestas[i].u;
    v = M->conjuntoArestas[i].v;
    printf("%d %d\n", u, v);
    if (emparelhados[u] || emparelhados[v]) {
      return false;
    }
    else {
      emparelhados[u] = true;
      emparelhados[v] = true;
    }
  }
  printf("EH EMP\n");
  return true;
}

Emparelhamento* alocaEmparelhamento (Grafo* G) {
  Emparelhamento *M;
  M = malloc(sizeof(Emparelhamento));
  M->conjuntoArestas = malloc(G->maxArestas*sizeof(bool));
  M->vEmparelhados = malloc(G->n*sizeof(bool));
  M->maxArestas = G->maxArestas; 
  M->tamanho = 0;
  int i;
  for (i = 0; i < G->n; i++) {
    M->vEmparelhados[i] = false;
  }
  for (i = 0; i < G->maxArestas; i++) {
    M->conjuntoArestas[i].u = G->arestas[i].u;
    M->conjuntoArestas[i].v = G->arestas[i].v;
    M->conjuntoArestas[i].emparelhada = true;
  }
  return M;
}

Emparelhamento* geraEmparelhamentoGuloso(Grafo* G) {
  Emparelhamento *M = alocaEmparelhamento(G);

  /* 
  pega o 0 e o primeiro vizinho e começa a percorrer as listas a partir do vertice 1
  
  */
  int i, extremidadeU, extremidadeV;
  printf("Vai entrar no for\n");

  for (i = 0; i < G->maxArestas; i++) {
    printf("%d %d\n", M->conjuntoArestas[i].u,  M->conjuntoArestas[i].v);
    if(G->arestas[i].existe) {
      printf("i = %d: ", i);
      extremidadeU = M->conjuntoArestas[i].u;
      extremidadeV = M->conjuntoArestas[i].v;
      printf("%d %d\n", M->conjuntoArestas[i].u, M->conjuntoArestas[i].v);
      if( M->vEmparelhados[extremidadeU] == false && M->vEmparelhados[extremidadeV] == false ) {
        M->vEmparelhados[extremidadeU] = true;
        M->vEmparelhados[extremidadeV] = true;
        M->conjuntoArestas[i].emparelhada = true;
        M->tamanho ++;
      }
    }
  }
  printf("Saiu do for\n");
  return M;
}

void imprimeEmparelhamento(Emparelhamento* M) {
  printf("================================================\n");
  printf("Imprimindo emparelhamento de tamanho %d\n", M->tamanho);
  int i;
  ArestaEmp* emp = M->conjuntoArestas;
  for(i=0; i < M->maxArestas; i++) {
    if(emp[i].emparelhada == true) {
      printf("|%d|---|%d|\n", emp[i].u, emp[i].v);
    }
  }
}