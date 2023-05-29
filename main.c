#include "hungarian.h"
#include <string.h>

Graph *readInput(FILE *fptr) {
  int vertices, a, b;
  char mat[2][50];
  char buf[100];
  fgets(buf, 100, fptr);
  char *ptr;
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
  return G;
}

int main(int argc, char *argv[]) {
  FILE *fptr;

  char *filename = argv[2];
  char filepath[] = "input/";

  strcat(filepath, filename);

  printf("Procurando o arquivo no caminho: %s\n", filepath);

  fptr = fopen(filepath, "r");

  if (fptr != NULL) {

    Graph *G = readInput(fptr);

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
