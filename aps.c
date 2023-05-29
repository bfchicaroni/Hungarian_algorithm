#include "aps.h"

APSTree *allocatesTree(Graph *G) {
  APSTree *T;
  T = malloc(sizeof(APSTree));
  T->dad = malloc(G->n * sizeof(int));
  T->visited = malloc(G->n * sizeof(bool));
  T->nVertices = G->n;
  int i;
  for (i = 0; i < T->nVertices; i++) {
    T->dad[i] = -1;
    T->visited[i] = 0;
  }
  return T;
}

void diferencaSimetrica(APSTree *T, Matching *M, int y) {
  int currentVertex = y;
  while (T->dad[T->dad[currentVertex]] != T->dad[currentVertex]) {
    M->coveredVertices[currentVertex] = T->dad[currentVertex];
    M->coveredVertices[T->dad[currentVertex]] = currentVertex;
    currentVertex = T->dad[currentVertex];
    // M->coveredVertices[T->dad[currentVertex]] = -1;
    currentVertex = T->dad[currentVertex];
  }
  M->coveredVertices[currentVertex] = T->dad[currentVertex];
  M->coveredVertices[T->dad[currentVertex]] = currentVertex;
  M->size++;
}

APSTuple *allocatesMemoryAPSMemoriaAPS(Graph *G) {
  APSTuple *tuple;
  tuple = malloc(sizeof(APSTuple));
  tuple->T = allocatesTree(G);
  tuple->Rt = malloc(G->n * sizeof(bool));
  tuple->Bt = malloc(G->n * sizeof(bool));
  tuple->Mt = malloc(G->n * sizeof(int));

  int i;
  for (i = 0; i < G->n; i++) {
    tuple->Rt[i] = false;
    tuple->Bt[i] = false;
    tuple->Mt[i] = -1;
  }
  return tuple;
}

APSTuple *APS(Graph *G, Matching *M, int u) {
  APSTuple *tuple = allocatesMemoryAPSMemoriaAPS(G);
  int *line = malloc(G->n * sizeof(int));
  int begin = 0;
  int end = 1;
  int x, y, z;

  line[begin] = u;
  x = line[begin];
  bool edgeXYexists = true;
  bool endOfNeighborhood = false;
  Vertex *vizX = G->vertices[x].next;
  tuple->foundMatching = false;
  tuple->T->visited[x] = true;
  tuple->Rt[x] = true;
  tuple->T->dad[x] = x;

  do {
    do {
      if (vizX == NULL) {
        endOfNeighborhood = true;
        break;
      }
      y = vizX->label;
      vizX = vizX->next;
    } while (tuple->T->visited[y]);
    if (endOfNeighborhood) {
      if (begin != end) {
        x = line[begin];
        begin++;
        vizX = G->vertices[x].next;
        endOfNeighborhood = false;
      } else {
        edgeXYexists = false;
      }
    } else {
      tuple->T->visited[y] = true;
      tuple->Bt[y] = true;
      tuple->T->dad[y] = x;
      z = M->coveredVertices[y];
      if (z != -1) {
        line[end] = z;
        end++;
        tuple->T->visited[z] = true;
        tuple->Rt[z] = true;
        tuple->Mt[z] = y;
        tuple->Mt[y] = z;
        tuple->T->dad[z] = y;
      } else {
        tuple->foundMatching = true;
        diferencaSimetrica(tuple->T, M, y);
        // printf("[APS] Terminou com um novo emparelhamento\n");
        return tuple;
      }
    }
  } while (edgeXYexists);
  // printf("[APS] Nao achou novo emparelhamento\n");
  return tuple;
}