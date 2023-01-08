#include "estruturas.h"
#include "grafos.h"
#include "emparelhamento.h"
#include "hungaro.h"
#include "aps.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void testeFuncoesEmparelhamento(Grafo* G) {
  Emparelhamento* M = geraEmparelhamentoGuloso(G);

  imprimeEmparelhamento(M);

  for(int i = 0; i < 5; i++) {
    if(ehCoberto (i, M) == true){
      printf("%d eh coberto por M\n", i);
    } else {
      printf("%d NAO eh coberto por M\n", i);
    }
  }

}

void testeFuncoesBasicasGrafo(Grafo* G){
  removeVertice(1, G);
  imprimeGrafo(G);

  printf(ehVizinho(1, 2, G)? "true\n":"false\n");
  printf(ehVizinho(2, 1, G)? "true\n":"false\n");
  printf(ehVizinho(2, 3, G)? "true\n":"false\n");
  printf(ehVizinho(3, 2, G)? "true\n":"false\n");

  removeAresta(1, 2, G);
  criaAresta(4, 3, G);
  imprimeGrafo(G);


  criaAresta(1, 2, G);
  criaAresta(2, 4, G);
  imprimeGrafo(G);
}

Grafo* criaGrafoTeste(int qtde_vertices) {
  Grafo* G = constroiGrafo(qtde_vertices);
  imprimeGrafo(G);

  criaAresta(3, 2, G);
  criaAresta(1, 4, G);
  criaAresta(0, 2, G);
  criaAresta(3, 0, G);
  criaAresta(2, 1, G);
  imprimeGrafo(G);

  return G;
}

void testeAPS1 () {
  Grafo* G = constroiGrafo(10);

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

  //TuplaAPS* aps = APS(G, M, 4);

  imprimeEmparelhamento(M);
}

void testeAPS2 () {
  Grafo* G = constroiGrafo(10);

  criaAresta(0, 6, G);
  criaAresta(0, 8, G);
  criaAresta(1, 5, G);
  criaAresta(1, 7, G);
  // criaAresta(2, 6, G);
  criaAresta(2, 8, G);
  criaAresta(3, 7, G);
  criaAresta(3, 9, G);
  // criaAresta(4, 6, G);
  criaAresta(4, 8, G);

  imprimeGrafo(G);

  Emparelhamento* M = alocaEmparelhamento(G);

  M->vEmparelhados[0] = 8;
  M->vEmparelhados[8] = 0;
  M->tamanho = 1;
  imprimeEmparelhamento(M);

  //TuplaAPS* aps = APS(G, M, 6);

  imprimeEmparelhamento(M);
}

void testeHungaro1 () {
  Grafo* G = constroiGrafo(10);

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

  printf("Grafo inicial\n");
  imprimeGrafo(G);

  printf("Emparelhamento inicial\n");
  Emparelhamento* M = geraEmparelhamentoGuloso(G);
  imprimeEmparelhamento(M);

  TuplaHungaro* hungarian = hungaro(G, M);

  printf("Emparelhamento otimo\n");
  imprimeEmparelhamento(hungarian->Mestrela);
}

void testeHungaro2 () {
  Grafo* G = constroiGrafo(10);

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

  printf("Grafo inicial\n");
  imprimeGrafo(G);

  printf("Emparelhamento inicial\n");
  Emparelhamento* M = alocaEmparelhamento(G);

  M->vEmparelhados[0] = 8;
  M->vEmparelhados[8] = 0;
  M->tamanho = 1;
  imprimeEmparelhamento(M);

  TuplaHungaro* hungarian = hungaro(G, M);

  printf("Emparelhamento otimo\n");
  imprimeEmparelhamento(hungarian->Mestrela);
}

void testeHungaro3 () {
  Grafo* G = constroiGrafo(10);

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

  printf("Grafo inicial\n");
  imprimeGrafo(G);

  printf("Emparelhamento inicial\n");
  Emparelhamento* M = alocaEmparelhamento(G);
  imprimeEmparelhamento(M);

  TuplaHungaro* hungarian = hungaro(G, M);

  printf("Emparelhamento otimo\n");
  imprimeEmparelhamento(hungarian->Mestrela);
}

void testeHungaro4 () {
  Grafo* G = constroiGrafo(10);

  printf("Grafo inicial\n");
  imprimeGrafo(G);

  printf("Emparelhamento inicial\n");
  Emparelhamento* M = alocaEmparelhamento(G);
  imprimeEmparelhamento(M);

  TuplaHungaro* hungarian = hungaro(G, M);

  printf("Emparelhamento otimo\n");
  imprimeEmparelhamento(hungarian->Mestrela);
}

int main(void) {
  printf("Iniciando...\n");
  // int qtde_vertices = 5;
  // Grafo *G = criaGrafoTeste(qtde_vertices);
  
  // testeFuncoesBasicasGrafo(G);

  // testeFuncoesEmparelhamento(G);

  // testeAPS1();

  // testeAPS2();

  // testeHungaro1();

  // testeHungaro2();

  // testeHungaro3();

  // testeHungaro4();

  printf("Acabou\n");
 
  return 0;
}
