#include "estruturas.h"
#include "grafos.h"
#include "emparelhamento.h"
#include "hungaro.h"
#include "aps.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void testeFuncoesEmparelhamento(Grafo* G) {
  Emparelhamento* M = geraEmparelhamentoGuloso(G);

  FILE *foutptr = fopen("result.txt", "w");

  imprimeEmparelhamento(M, foutptr);

  fclose(foutptr); 


  for(int i = 0; i < 5; i++) {
    if(ehCoberto (i, M) == true){
      printf("%d eh coberto por M\n", i);
    } else {
      printf("%d NAO eh coberto por M\n", i);
    }
  }

}

void testeFuncoesBasicasGrafo(Grafo* G){
  FILE *foutptr = fopen("result.txt", "w");
  removeVertice(1, G);
  imprimeGrafo(G, foutptr);

  printf(ehVizinho(1, 2, G)? "true\n":"false\n");
  printf(ehVizinho(2, 1, G)? "true\n":"false\n");
  printf(ehVizinho(2, 3, G)? "true\n":"false\n");
  printf(ehVizinho(3, 2, G)? "true\n":"false\n");

  removeAresta(1, 2, G);
  criaAresta(4, 3, G);
  imprimeGrafo(G, foutptr);


  criaAresta(1, 2, G);
  criaAresta(2, 4, G);
  imprimeGrafo(G, foutptr);
  fclose(foutptr); 
}

Grafo* criaGrafoTeste(int qtde_vertices) {
  FILE *foutptr = fopen("result.txt", "w");
  Grafo* G = constroiGrafo(qtde_vertices);
  imprimeGrafo(G, foutptr);

  // criaAresta(3, 2, G);
  // criaAresta(1, 4, G);
  // criaAresta(0, 2, G);
  // criaAresta(3, 0, G);
  // criaAresta(2, 1, G);
  // imprimeGrafo(G, foutptr);

  fclose(foutptr);
  return G;
}

void testeAPS1 () {
  FILE *foutptr = fopen("result.txt", "w");
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

  imprimeGrafo(G, foutptr);

  Emparelhamento* M = alocaEmparelhamento(G);

  M->vEmparelhados[1] = 7;
  M->vEmparelhados[7] = 1;
  M->vEmparelhados[2] = 8;
  M->vEmparelhados[8] = 2;
  M->tamanho = 2;
  imprimeEmparelhamento(M, foutptr);

  //TuplaAPS* aps = APS(G, M, 4);

  imprimeEmparelhamento(M, foutptr);
  fclose(foutptr);
}

void testeAPS2 () {
  FILE *foutptr = fopen("result.txt", "w");
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

  imprimeGrafo(G, foutptr);

  Emparelhamento* M = alocaEmparelhamento(G);

  M->vEmparelhados[0] = 8;
  M->vEmparelhados[8] = 0;
  M->tamanho = 1;
  imprimeEmparelhamento(M, foutptr);

  //TuplaAPS* aps = APS(G, M, 6);

  imprimeEmparelhamento(M, foutptr);
  fclose(foutptr);
}

int main(void) {

  // testeFuncoesBasicasGrafo(G);

  // testeFuncoesEmparelhamento(G);

  // testeAPS1();

  // testeAPS2();

  int vertices, a, b;
  FILE *fptr;  
  char mat [2][50];
  char *ptr;

  printf("Digite o nome do arquivo de entrada: ");
  char filename[100];
  scanf("%s", filename);
  char filepath[] = "instances/";

  strcat(filepath,filename);

  printf("Procurando o arquivo no caminho:\n%s\n", filepath);

  fptr = fopen(filepath, "r");

  if (fptr != NULL) {
    char buf[100];
    fgets(buf, 100, fptr);
    ptr = strtok(buf, "-\n");
    vertices = atoi(ptr);

    Grafo *G = constroiGrafo(vertices);

    while (fgets(buf, 100, fptr)) {
      ptr = strtok(buf, "-\n");
      int i = 0;
      while (ptr != NULL) {
        strcpy(mat[i], ptr);
        ptr = strtok(NULL, "-\n");
        i++;
      }
      a = atoi(mat[0]);
      b = atoi(mat[1]);
      criaAresta(a, b, G);
    }

    FILE *foutptr;

    foutptr = fopen("result.txt", "w");

    fprintf(foutptr, "Grafo inicial\n");
    imprimeGrafo(G, foutptr);

    fprintf(foutptr, "Emparelhamento inicial\n");
    Emparelhamento *M = geraEmparelhamentoGuloso(G);
    imprimeEmparelhamento(M, foutptr);

    TuplaHungaro *hungarian = hungaro(G, M);

    fprintf(foutptr, "Emparelhamento otimo\n");
    imprimeEmparelhamento(hungarian->Mestrela, foutptr);

    fclose(foutptr); 

    printf("Os resultados estao no arquivo result.txt\n");

  } else {
    printf("Not able to open the file.\n");
  }

  fclose(fptr);

  return 0;
}
