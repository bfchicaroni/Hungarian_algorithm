#include "estruturas.h"
#include "grafos.h"
#include "emparelhamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
  int qtde_vertices = 5;
  Grafo *G = constroiGrafo(qtde_vertices);
  imprimeGrafo(G);

  criaAresta(3, 2, G);
  criaAresta(1, 4, G);
  imprimeGrafo(G);

  removeAresta(1, 4, G);
  imprimeGrafo(G);

  Aresta* emparelhamento = malloc(2*sizeof(Aresta));
  emparelhamento[0].u = 1;
  emparelhamento[0].v = 2;
  emparelhamento[1].u = 3;
  emparelhamento[1].v = 4;
  // emparelhamento[2].u = 2;
  // emparelhamento[2].v = 3;
  if (ehEmparelhamento(G, emparelhamento)) {
    printf("Eh emparelhamento\n");
  }
  else {
    printf("Nao eh emparelhamento\n");
  }

  return 0;
}
