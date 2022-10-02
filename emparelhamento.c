#include "estruturas.h"
#include "grafos.h"
#include "emparelhamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool ehEmparelhamento (Grafo *G, Aresta* conjuntoArestas) {
  bool *emparelhados = malloc((G->n)*sizeof(bool));
  int i, u, v;
  for(i = 0; i < G->n ; i++) {
    emparelhados[i] = false;
  }
  int tamanhoEmparelhamento = 2;
  printf("Tamanho = %d\n", tamanhoEmparelhamento);
  for(i=0; i < tamanhoEmparelhamento; i++) {
    u = conjuntoArestas[i].u;
    v = conjuntoArestas[i].v;
    printf("%d %d\n", u, v);
    if (emparelhados[u] == true || emparelhados[v] == true) {
      return false;
    }
    else {
      emparelhados[u] = true;
      emparelhados[v] = true;
    }
  }
  return true;
}