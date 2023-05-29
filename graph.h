#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef GRAPHS_H_
#define GRAPHS_H_

// Estrutura que representa os vértices do grafo.
typedef struct Vertex {
  int label;
  struct Vertex *next;
} Vertex;

// Estrutura que representa um grafo.
typedef struct Graph {
  Vertex *vertices;
  bool *exists;
  int n; // numberOfVertices
  int nExistentes;
  int m; // numberOfEdges
  int maxEdges;
} Graph;

Graph *buildGraph(int numberOfVertices);

// Dados dois vértices verifica se existe uma aresta entre eles
bool isNeighbor(int mainVertexIndex, int neighborLabel, Graph *G);

// Remove um vértice da lista de vizinhos de um vértice
void removeNeighbor(int neighborLabel, int vertexLabel, Graph *G);

// Remove um vértice de um grafo
void removeVertex(int removedVertexLabel, Graph *G);

// Remove uma aresta de um grafo
void removeEdge(int vertexALabel, int vertexBLabel, Graph *G);

// Adiciona um novo nó à vizinhança de um vértice na lista de adjacências
void addNeighbor(int newNeighborLabel, int vertexLabel, Graph *G);

// Cria uma aresta em um grafo
void addEdge(int vertexALabel, int vertexBLabel, Graph *G);

// Imprime na tela a lista de arestas do grafo
void printEdges(Graph *G, FILE *foutptr);

// Imprime na tela a estrutura que representa o grafo
void printGraph(Graph *G, FILE *foutptr);

#endif