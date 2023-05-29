#include "hungarian.h"
#include <string.h>

void testeFuncoesEmparelhamento(Graph *G) {
  Matching *M = makeGreedyMatching(G);

  FILE *foutptr = fopen("result.txt", "w");

  printMatching(M, foutptr);

  fclose(foutptr);

  for (int i = 0; i < 5; i++) {
    if (isCovered(i, M) == true) {
      printf("%d eh coberto por M\n", i);
    } else {
      printf("%d NAO eh coberto por M\n", i);
    }
  }
}

void testeFuncoesBasicasGrafo(Graph *G) {
  FILE *foutptr = fopen("result.txt", "w");
  removeVertex(1, G);
  printGraph(G, foutptr);

  printf(isNeighbor(1, 2, G) ? "true\n" : "false\n");
  printf(isNeighbor(2, 1, G) ? "true\n" : "false\n");
  printf(isNeighbor(2, 3, G) ? "true\n" : "false\n");
  printf(isNeighbor(3, 2, G) ? "true\n" : "false\n");

  removeEdge(1, 2, G);
  addEdge(4, 3, G);
  printGraph(G, foutptr);

  addEdge(1, 2, G);
  addEdge(2, 4, G);
  printGraph(G, foutptr);
  fclose(foutptr);
}

Graph *criaGrafoTeste(int numberOfVertices) {
  FILE *foutptr = fopen("result.txt", "w");
  Graph *G = buildGraph(numberOfVertices);
  printGraph(G, foutptr);

  // addEdge(3, 2, G);
  // addEdge(1, 4, G);
  // addEdge(0, 2, G);
  // addEdge(3, 0, G);
  // addEdge(2, 1, G);
  // printGraph(G, foutptr);

  fclose(foutptr);
  return G;
}

void testeAPS1() {
  FILE *foutptr = fopen("result.txt", "w");
  Graph *G = buildGraph(10);

  addEdge(0, 6, G);
  addEdge(0, 8, G);
  addEdge(1, 5, G);
  addEdge(1, 7, G);
  addEdge(2, 6, G);
  addEdge(2, 8, G);
  addEdge(3, 7, G);
  addEdge(3, 9, G);
  addEdge(4, 6, G);
  addEdge(4, 8, G);

  printGraph(G, foutptr);

  Matching *M = allocatesMatching(G);

  M->coveredVertices[1] = 7;
  M->coveredVertices[7] = 1;
  M->coveredVertices[2] = 8;
  M->coveredVertices[8] = 2;
  M->size = 2;
  printMatching(M, foutptr);

  // APSTuple* aps = APS(G, M, 4);

  printMatching(M, foutptr);
  fclose(foutptr);
}

void testeAPS2() {
  FILE *foutptr = fopen("result.txt", "w");
  Graph *G = buildGraph(10);

  addEdge(0, 6, G);
  addEdge(0, 8, G);
  addEdge(1, 5, G);
  addEdge(1, 7, G);
  // addEdge(2, 6, G);
  addEdge(2, 8, G);
  addEdge(3, 7, G);
  addEdge(3, 9, G);
  // addEdge(4, 6, G);
  addEdge(4, 8, G);

  printGraph(G, foutptr);

  Matching *M = allocatesMatching(G);

  M->coveredVertices[0] = 8;
  M->coveredVertices[8] = 0;
  M->size = 1;
  printMatching(M, foutptr);

  // APSTuple* aps = APS(G, M, 6);

  printMatching(M, foutptr);
  fclose(foutptr);
}

int main(int argc, char *argv[]) {

  int vertices, a, b;
  FILE *fptr;
  char mat[2][50];
  char *ptr;

  char *filename = argv[2];
  char filepath[] = "input/";

  strcat(filepath, filename);

  printf("Procurando o arquivo no caminho: %s\n", filepath);

  fptr = fopen(filepath, "r");

  if (fptr != NULL) {
    char buf[100];
    fgets(buf, 100, fptr);
    ptr = strtok(buf, "-\n");
    vertices = atoi(ptr);

    Graph *G = buildGraph(vertices);

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
      addEdge(a, b, G);
    }

    FILE *foutptr;

    char *outputFile = argv[3];
    char outputpath[] = "output/";

    strcat(outputpath, outputFile);

    foutptr = fopen(outputpath, "w");

    bool printInputGraph;
    bool printFirstMatching;
    if (argc <= 4) {
      printInputGraph = false;
      printFirstMatching = false;
    } else if (argc == 5) {
      printInputGraph = !strcmp("true", argv[4]);
      printFirstMatching = false;
    } else {
      printInputGraph = !strcmp("true", argv[4]);
      printFirstMatching = !strcmp("true", argv[5]);
    }

    if (printInputGraph) {
      fprintf(foutptr, "Initial graph\n");
      printGraph(G, foutptr);
    }

    Matching *M = makeGreedyMatching(G);

    if (printFirstMatching) {
      fprintf(foutptr, "Initial matching\n");
      printMatching(M, foutptr);
      fprintf(foutptr, "================================================\n");
    }

    HungarianTuple *hungarianOut = hungarian(G, M);

    if (printInputGraph || printFirstMatching) {
      fprintf(foutptr, "Optimal matching\n");
    }
    printMatching(hungarianOut->Mstar, foutptr);

    printf("The results are on the file %s\n", outputFile);

    fclose(foutptr);
    fclose(fptr);
  } else {
    printf("Not able to open the file.\n");
  }

  return 0;
}
