#include "hungarian.h"

HungarianTuple *allocatesMemoryHungarian(Graph *G, Matching *M) {
  HungarianTuple *tuple;
  tuple = malloc(sizeof(HungarianTuple));
  tuple->tau = malloc(G->n * sizeof(APSTree *));
  tuple->R = malloc(G->n * sizeof(bool));
  tuple->B = malloc(G->n * sizeof(bool));
  tuple->Mstar = allocatesMatching(G);
  tuple->U = malloc(G->n * sizeof(bool));
  tuple->F = G;

  int i;
  for (i = 0; i < G->n; i++) {
    tuple->R[i] = false;
    tuple->B[i] = false;
    tuple->U[i] = false;
  }
  return tuple;
}

int searchUnmatched(Graph *G, Matching *M) {
  int i = 0;
  while (i < M->nVertices && (M->coveredVertices[i] != -1 || !G->exists[i])) {
    i++;
  }
  return i;
}

void unionOp(bool *A, bool *B, int size) {
  for (int i = 0; i < size; i++) {
    if (B[i]) {
      A[i] = true;
    }
  }
}

void matchingUnion(Matching *Mstar, Matching *M) {
  for (int i = 0; i < Mstar->nVertices; i++) {
    if (M->coveredVertices[i] != -1) {
      Mstar->coveredVertices[i] = M->coveredVertices[i];
    }
  }
  Mstar->size += M->size;
}

void matchingUnionArray(Matching *Mstar, int *M) {
  int count = 0;
  // printf("Tamanho Mestrela: %d\n", Mstar->nVertices);
  // for (int j = 0; j < Mstar->nVertices; j++) {
  //   printf("%d ", M[j]);
  // }
  // printf("\n");
  for (int i = 0; i < Mstar->nVertices; i++) {
    if (M[i] != -1) {
      Mstar->coveredVertices[i] = M[i];
      count++;
    }
  }
  Mstar->size += (count / 2);
  // printf("Mestrela:\n");
  // printMatching(Mstar);
}

void removeMatching(Matching *M, APSTree *T) {
  int count = 0;
  for (int i = 0; i < M->nVertices; i++) {
    if (M->coveredVertices[i] != -1 && T->visited[i]) {
      M->coveredVertices[i] = -1;
      count++;
    }
  }
  M->size -= (count / 2);
}

void removeSubgraph(Graph *F, APSTree *T) {
  for (int i = 0; i < T->nVertices; i++) {
    if (T->visited[i]) {
      removeVertex(i, F);
    }
  }
}

HungarianTuple *hungarian(Graph *G, Matching *M) {
  int u;
  APSTuple *aps;
  HungarianTuple *tuple = allocatesMemoryHungarian(G, M);
  int unmatched = searchUnmatched(G, M);
  // printf("Primeiro desemparelhado: %d\n", unmatched);
  int i = 0;
  while (unmatched != M->nVertices) {
    u = unmatched;
    // printf("u = %d\n", u);
    aps = APS(G, M, u);
    // printMatching(M);
    if (!aps->foundMatching) {
      // printf("Nao achou mais emparelhamento\n");
      tuple->tau[i] = aps->T;
      i++;
      unionOp(tuple->R, aps->Rt, G->n);
      unionOp(tuple->B, aps->Bt, G->n);
      tuple->U[u] = true;
      // printf("R B U\n");
      // for (int j = 0; j < G->n; j++) {
      //   printf("%d %d %d\n", tuple->R[j], tuple->B[j], tuple->U[j]);
      // }
      matchingUnionArray(tuple->Mstar, aps->Mt);
      removeMatching(M, aps->T);
      // printf("M - E(T):\n");
      // printMatching(M);
      removeSubgraph(tuple->F, aps->T);
    }
    unmatched = searchUnmatched(G, M);
    // printf("Desemparelhado = %d\n", unmatched);
  }
  // printf("R B U\n");
  // for (int j = 0; j < G->n; j++) {
  //   printf("%d %d %d\n", tuple->R[j], tuple->B[j], tuple->U[j]);
  // }
  matchingUnion(tuple->Mstar, M);
  return tuple;
}