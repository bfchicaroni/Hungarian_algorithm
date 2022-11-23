#include "estruturas.h"
#include "grafos.h"
#include "emparelhamento.h"
#include "aps.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
  // printf("Iniciando...\n");
  // int qtde_vertices = 5;
  // Grafo *G = constroiGrafo(qtde_vertices);
  // imprimeGrafo(G);

  // criaAresta(3, 2, G);
  // criaAresta(1, 4, G);
  // criaAresta(0, 2, G);
  // criaAresta(3, 0, G);
  // criaAresta(2, 1, G);
  // imprimeGrafo(G);

  // removeAresta(1, 2, G);
  // criaAresta(4, 3, G);
  // imprimeGrafo(G);


  // criaAresta(1, 2, G);
  // imprimeGrafo(G);
  // // Emparelhamento* M = alocaEmparelhamento(G);
  // // printf("Criou o emparelhamento\n");
  // Emparelhamento* M = geraEmparelhamentoGuloso(G);

  // imprimeEmparelhamento(M);

  // for(int i = 0; i < 5; i++) {
  //   if(ehCoberto (i, M) == true){
  //     printf("%d eh coberto por M\n", i);
  //   } else {
  //     printf("%d NAO eh coberto por M\n", i);
  //   }
  // }

  // ArvoreAPS* T = alocaArvore(G);

  // T->pai[0] = 2;
  // T->pai[1] = 1;
  // T->pai[2] = 1;
  // T->pai[4] = 1;

  // for(int i = 0; i < M->nVertices; i++) {
  //   M->vEmparelhados[i] = -1;
  // }
  // M->tamanho = 0;

  // imprimeEmparelhamento(M);

  // M->vEmparelhados[0] = 2;
  // M->vEmparelhados[2] = 0;
  // M->tamanho = 1;

  // imprimeEmparelhamento(M);

  // M = diferencaSimetrica(T, M, 4);

  // imprimeEmparelhamento(M);

  printf("Iniciando...\n");
  int qtde_vertices = 10;
  Grafo *G = constroiGrafo(qtde_vertices);

  criaAresta(0, 6, G);
  criaAresta(0, 8, G);
  criaAresta(1, 5, G);
  criaAresta(1, 7, G);
  criaAresta(2, 6, G);
  criaAresta(2, 8, G);
  criaAresta(3, 7, G);
  criaAresta(3, 9, G);
  criaAresta(4, 6, G);
  criaAresta(4, 8, G);
  imprimeGrafo(G);

  Emparelhamento* M = alocaEmparelhamento(G);
  M->vEmparelhados[1] = 7;
  M->vEmparelhados[7] = 1;
  M->vEmparelhados[2] = 8;
  M->vEmparelhados[8] = 2;
  M->tamanho = 2;
  imprimeEmparelhamento(M);

  TuplaAPS* aps = APS(G, M, 5);

  imprimeEmparelhamento(M);

  printf("Acabou\n");
 
  return 0;
}
