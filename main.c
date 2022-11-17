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
  criaAresta(0, 2, G);
  criaAresta(3, 0, G);
  criaAresta(2, 1, G);
  imprimeGrafo(G);

  removeAresta(1, 2, G);
  criaAresta(4, 3, G);
  imprimeGrafo(G);

  // Emparelhamento* M = pegaEmparelhamento(G);
  // printf("Criou o emparelhamento\n");
  Emparelhamento* M = alocaEmparelhamento(G);

  // imprimeEmparelhamento(M);

  // M->conjuntoArestas[4].emparelhada = true;
  // M->conjuntoArestas[9].emparelhada = true;
  // //M->conjuntoArestas[7].emparelhada = true;
  // M->tamanho = 2;

  // imprimeEmparelhamento(M);
  
  // if (ehEmparelhamento(G, M) == true) {
  //   printf("Eh emparelhamento\n");
  // }
  // else {
  //   printf("Nao eh emparelhamento\n");
  // }

  printf("Acabou\n");
 
  return 0;
}
