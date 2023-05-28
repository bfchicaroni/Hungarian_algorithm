#include "hungarian.h"

TuplaHungaro *alocaMemoriaHungaro(Graph *G, Matching *M) {
  TuplaHungaro *tupla;
  tupla = malloc(sizeof(TuplaHungaro));
  tupla->tau = malloc(G->n * sizeof(APSTree *));
  tupla->R = malloc(G->n * sizeof(bool));
  tupla->B = malloc(G->n * sizeof(bool));
  tupla->Mestrela = allocatesMatching(G);
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

int procuraDesemparelhado(Graph *G, Matching *M) {
  int i = 0;
  while (i < M->nVertices && (M->vEmparelhados[i] != -1 || !G->exists[i])) {
    i++;
  }
  return i;
}

void uniao(bool *A, bool *B, int size) {
  for (int i = 0; i < size; i++) {
    if (B[i]) {
      A[i] = true;
    }
  }
}

void matchingUnion(Matching *Mestrela, Matching *M) {
  for (int i = 0; i < Mestrela->nVertices; i++) {
    if (M->vEmparelhados[i] != -1) {
      Mestrela->vEmparelhados[i] = M->vEmparelhados[i];
    }
  }
  Mestrela->size += M->size;
}

void matchingUnionArray(Matching *Mestrela, int *M) {
  int count = 0;
  // printf("Tamanho Mestrela: %d\n", Mestrela->nVertices);
  // for (int j = 0; j < Mestrela->nVertices; j++) {
  //   printf("%d ", M[j]);
  // }
  // printf("\n");
  for (int i = 0; i < Mestrela->nVertices; i++) {
    if (M[i] != -1) {
      Mestrela->vEmparelhados[i] = M[i];
      count++;
    }
  }
  Mestrela->size += (count / 2);
  // printf("Mestrela:\n");
  // printMatching(Mestrela);
}

void removeMatching(Matching *M, APSTree *T) {
  int count = 0;
  for (int i = 0; i < M->nVertices; i++) {
    if (M->vEmparelhados[i] != -1 && T->visitado[i]) {
      M->vEmparelhados[i] = -1;
      count++;
    }
  }
  M->size -= (count / 2);
}

void removeSubgraph(Graph *F, APSTree *T) {
  for (int i = 0; i < T->nVertices; i++) {
    if (T->visitado[i]) {
      removeVertex(i, F);
    }
  }
}

TuplaHungaro *hungaro(Graph *G, Matching *M) {
  int u;
  TuplaAPS *aps;
  TuplaHungaro *tupla = alocaMemoriaHungaro(G, M);
  int desemparelhado = procuraDesemparelhado(G, M);
  // printf("Primeiro desemparelhado: %d\n", desemparelhado);
  int i = 0;
  while (desemparelhado != M->nVertices) {
    u = desemparelhado;
    // printf("u = %d\n", u);
    aps = APS(G, M, u);
    // printMatching(M);
    if (!aps->foundMatching) {
      // printf("Nao achou mais emparelhamento\n");
      tupla->tau[i] = aps->T;
      i++;
      uniao(tupla->R, aps->Rt, G->n);
      uniao(tupla->B, aps->Bt, G->n);
      tupla->U[u] = true;
      // printf("R B U\n");
      // for (int j = 0; j < G->n; j++) {
      //   printf("%d %d %d\n", tupla->R[j], tupla->B[j], tupla->U[j]);
      // }
      matchingUnionArray(tupla->Mestrela, aps->Mt);
      removeMatching(M, aps->T);
      // printf("M - E(T):\n");
      // printMatching(M);
      removeSubgraph(tupla->F, aps->T);
    }
    desemparelhado = procuraDesemparelhado(G, M);
    // printf("Desemparelhado = %d\n", desemparelhado);
  }
  // printf("R B U\n");
  // for (int j = 0; j < G->n; j++) {
  //   printf("%d %d %d\n", tupla->R[j], tupla->B[j], tupla->U[j]);
  // }
  matchingUnion(tupla->Mestrela, M);
  return tupla;
}