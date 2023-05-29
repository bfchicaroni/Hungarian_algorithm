#include "graph.h"

// Constroi um grafo sem arestas com a qtde de vertices passada como parâmetro
Graph *buildGraph(int numberOfVertices) {
  Graph *G;
  G = malloc(sizeof(Graph));
  G->vertices = malloc(numberOfVertices * sizeof(Vertex));
  G->exists = malloc(numberOfVertices * sizeof(bool));
  int numberOfEdges = (numberOfVertices * (numberOfVertices - 1)) / 2;
  G->maxEdges = numberOfEdges;
  G->n = numberOfVertices;
  G->nExistentes = numberOfVertices;
  G->m = 0;
  int i;
  Vertex newVertex;
  for (i = 0; i < numberOfVertices; i++) {
    newVertex.label = i;
    newVertex.next = NULL;
    G->vertices[i] = newVertex;
    G->exists[i] = true;
  }
  return G;
}

// Dados dois vértices verifica se exists uma aresta entre eles
bool isNeighbor(int mainVertexIndex, int neighborLabel, Graph *G) {

  if (!G->exists[mainVertexIndex]) {
    return false;
  }

  Vertex *vg = G->vertices;
  Vertex *atual = vg[mainVertexIndex].next;

  while (atual != NULL) {
    if (atual->label == neighborLabel) {
      return true;
    }
    atual = atual->next;
  }
  return false;
}

// Remove um vértice da lista de vizinhos de um vértice
void removeNeighbor(int neighborLabel, int vertexLabel, Graph *G) {

  if (!G->exists[vertexLabel]) {
    printf("Nao e possivel remover %d dos vizinhos de %d pois %d nao existe\n",
           neighborLabel, vertexLabel, vertexLabel);
    return;
  }

  Vertex *vg = G->vertices;
  Vertex *atual = vg[vertexLabel].next;

  Vertex *anterior;
  while (atual != NULL) {
    if (atual->label == neighborLabel) {
      if (atual == vg[vertexLabel].next) {
        vg[vertexLabel].next = atual->next;
      } else {
        anterior->next = atual->next;
      }
    }
    anterior = atual;
    atual = atual->next;
  }
}

void removeVertex(int removedVertexLabel, Graph *G) {
  Vertex *neighbor;
  if (G->exists[removedVertexLabel]) {
    if (G->vertices[removedVertexLabel].next != NULL) {
      neighbor = G->vertices[removedVertexLabel].next;
      while (neighbor != NULL) {
        if (G->exists[neighbor->label]) {
          removeNeighbor(removedVertexLabel, neighbor->label, G);
          G->m--;
        }
        neighbor = neighbor->next;
      }
    }
  } else {
    printf("Nao e possivel remover o vertice %d pois ele nao existe\n",
           removedVertexLabel);
  }

  G->exists[removedVertexLabel] = false;
  G->nExistentes--;
}

// Remove uma aresta de um grafo
void removeEdge(int vertexALabel, int vertexBLabel, Graph *G) {
  if (G->exists[vertexALabel] && G->exists[vertexBLabel]) {
    removeNeighbor(vertexALabel, vertexBLabel, G);
    removeNeighbor(vertexBLabel, vertexALabel, G);
    G->m--;
  }
}

// Adiciona um novo nó à vizinhança de um vértice na lista de adjacências
void addNeighbor(int newNeighborLabel, int vertexLabel, Graph *G) {

  if (!G->exists[vertexLabel]) {
    printf("Nao e possivel adicionar um novo vizinho a %d pois %d nao existe\n",
           vertexLabel, vertexLabel);
    return;
  } else if (!G->exists[newNeighborLabel]) {
    printf("Nao e possivel adicionar %d como vizinho de um vertice pois o "
           "vertice %d nao existe\n",
           newNeighborLabel, newNeighborLabel);
    return;
  }

  // Cria a estrutura do novo vizinho
  Vertex *newNeighbor = (Vertex *)malloc(sizeof(Vertex));
  (*newNeighbor).label = newNeighborLabel;

  // Encontra o endereço do vértice que vai receber o novo vizinho
  Vertex *vg = G->vertices;
  Vertex *primeiro = &vg[vertexLabel];

  // Insere o novo vizinho no início da lista de vizinhos do vértice
  (*newNeighbor).next = primeiro->next;
  primeiro->next = newNeighbor;
}

// Cria uma aresta em um grafo
void addEdge(int vertexALabel, int vertexBLabel, Graph *G) {
  if (G->exists[vertexALabel] && G->exists[vertexBLabel]) {
    addNeighbor(vertexALabel, vertexBLabel, G);
    addNeighbor(vertexBLabel, vertexALabel, G);
    G->m++;
  }
}

// Imprime na tela a lista de arestas do grafo
void printEdges(Graph *G, FILE *foutptr) {
  int i;
  Vertex *neighbor;
  for (i = 0; i < G->n; i++) {
    if (G->exists[i]) {
      if (G->vertices[i].next != NULL) {
        neighbor = G->vertices[i].next;
        while (neighbor != NULL) {
          if (G->exists[neighbor->label] && i < neighbor->label) {
            fprintf(foutptr, "|%d|---|%d|\n", i, neighbor->label);
          }
          neighbor = neighbor->next;
        }
      }
    }
  }
}

// Imprime na tela a estrutura que representa o grafo
void printGraph(Graph *G, FILE *foutptr) {
  int i;
  Vertex *vg = G->vertices;
  bool *vertexExists = G->exists;
  Vertex *atual;
  fprintf(foutptr, "%d %d\n", G->nExistentes, G->m);
  for (i = 0; i < G->n; i++) {
    if (vertexExists[i]) {
      fprintf(foutptr, "|%d|", vg[i].label);
      atual = vg[i].next;
      while (atual != NULL) {
        fprintf(foutptr, " -> %d ", atual->label);
        atual = atual->next;
      }
      fprintf(foutptr, "\n");
    }
  }
  printEdges(G, foutptr);
  fprintf(foutptr, "================================================\n");
}