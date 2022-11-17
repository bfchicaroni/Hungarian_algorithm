#include "estruturas.h"
#include "grafos.h"
#include "emparelhamento.h"
#include "aps.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
  printf("Iniciando...\n");
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


  criaAresta(1, 2, G);
  imprimeGrafo(G);
  // Emparelhamento* M = alocaEmparelhamento(G);
  // printf("Criou o emparelhamento\n");
  Emparelhamento* M = geraEmparelhamentoGuloso(G);

  imprimeEmparelhamento(M);

  for(int i = 0; i < 5; i++) {
    if(ehCoberto (i, M) == true){
      printf("%d eh coberto por M\n", i);
    } else {
      printf("%d NAO eh coberto por M\n", i);
    }
  }

  ArvoreAPS* T = alocaArvore(G);

  T->predecessor[0] = 2;
  T->predecessor[1] = 1;
  T->predecessor[2] = 1;
  T->predecessor[3] = 0;

  for(int i = 0; i < M->nVertices; i++) {
    M->vEmparelhados[i] = -1;
  }
  M->tamanho = 0;

  imprimeEmparelhamento(M);

  M->vEmparelhados[0] = 2;
  M->vEmparelhados[2] = 0;
  M->tamanho = 1;

  imprimeEmparelhamento(M);
  
  M = diferencaSimetrica(T, M, 3, 1);

  imprimeEmparelhamento(M);


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
