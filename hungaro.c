#include "estruturas.h"
#include "emparelhamento.h"
#include "grafos.h"
#include "aps.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

TuplaHungaro* alocaMemoriaHungaro(Grafo* G, Emparelhamento* M) {
  TuplaHungaro* tupla;
  tupla = malloc(sizeof(TuplaHungaro));
  tupla->tau = malloc(G->n * sizeof(ArvoreAPS*));
  tupla->R = malloc(G->n * sizeof(bool));
  tupla->B = malloc(G->n * sizeof(bool));
  tupla->Mestrela = alocaEmparelhamento(G);
  tupla->U = malloc(G->n * sizeof(bool));
  tupla->F = G;

  int i;
  for (i = 0; i < G->n; i++) {
    tupla->R[i] = false;
    tupla->B[i] = false;
    tupla->U[i] = false;
  }
  return tupla;
}

int procuraDesemparelhado(Emparelhamento* M) {
  int i = 0;
  while (i < M->nVertices && M->vEmparelhados[i]!=-1) {
    i++;
  }
  return i;
}

void uniao (bool* A, bool* B, int tamanho) {
  for (int i = 0; i<tamanho; i++) {
    if (B[i]) {
      A[i] = true;
    }
  }
}

void uniaoEmparelhamento (Emparelhamento* Mestrela, Emparelhamento* M) {
  for (int i = 0; i < Mestrela->tamanho; i++) {
    if (M->vEmparelhados[i] != -1) {
      Mestrela->vEmparelhados[i] = M->vEmparelhados[i];
    }
  }
  Mestrela->tamanho += M->tamanho;

}

void uniaoEmparelhamentoArray (Emparelhamento* Mestrela, int* M) {
  int count = 0;
  for (int i = 0; i < Mestrela->tamanho; i++) {
    if (M[i] != -1) {
      Mestrela->vEmparelhados[i] = M[i];
      count++;
    }
  }
  Mestrela->tamanho += (count/2);
}

void subtraiEmparelhamento (Emparelhamento* M, ArvoreAPS* T) {
  int count = 0;
  for(int i = 0; i < M->nVertices; i++) {
    if (M->vEmparelhados[i] && T->visitado[i]) {
      M->vEmparelhados[i] = false;
      count++;
    }
  }
  M->tamanho-=(count/2);
}

void subtraiGrafo (Grafo* F, ArvoreAPS* T) {
  for(int i = 0; i < T->nVertices; i++) {
    if (T->visitado[i]) {
      removeVertice(i, F);
    }
  }
}

TuplaHungaro* hungaro (Grafo* G, Emparelhamento* M) {
  int u;
  TuplaAPS* aps;
  TuplaHungaro* tupla = alocaMemoriaHungaro(G, M);
  int desemparelhado = procuraDesemparelhado(M);
  int i = 0;
  while(desemparelhado!= M->nVertices) {
    u = desemparelhado;
    printf("u = %d\n", u);
    aps = APS(G, M, u);
    imprimeEmparelhamento(M);
    if(!aps->achouEmparelhamento) {
      printf("Não achou mais emparelhamento");
      tupla->tau[i] = aps->T;
      i++;
      uniao(tupla->R,aps->Rt,G->n);
      uniao(tupla->B,aps->Bt,G->n);
      tupla->U[u] = true;
      printf("R B U\n");
      for (int j = 0; j < G->n; j++) {
        printf("%d %d %d\n", tupla->R[j], tupla->B[j], tupla->U[j]);
      }
      uniaoEmparelhamentoArray(tupla->Mestrela, aps->Mt);
      subtraiEmparelhamento(M, aps->T);
      subtraiGrafo(tupla->F,aps->T);
    }
    desemparelhado = procuraDesemparelhado(M);
  }
  printf("R B U\n");
  for (int j = 0; j < G->n; j++) {
    printf("%d %d %d\n", tupla->R[j], tupla->B[j], tupla->U[j]);
  }
  uniaoEmparelhamento(tupla->Mestrela, M);
  return tupla;
}