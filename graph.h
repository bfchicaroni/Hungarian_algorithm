#include "structs.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef GRAPHS_H_
#define GRAPHS_H_

Graph *buildGraph(int numberOfVertices);

// Dados dois vértices verifica se existe uma aresta entre eles
bool ehVizinho(int mainVertexIndex, int rotuloVerticeVizinho, Graph *G);

// Remove um vértice da lista de vizinhos de um vértice
void removerVizinho(int rotuloVizinho, int vertexLabel, Graph *G);

// Remove um vértice de um grafo
void removeVertex(int removedVertexLabel, Graph *G);

// Remove uma aresta de um grafo
void removeEdge(int vertexALabel, int vertexBLabel, Graph *G);

// Adiciona um novo nó à vizinhança de um vértice na lista de adjacências
void adicionarVizinho(int rotuloNovoVizinho, int vertexLabel, Graph *G);

// Cria uma aresta em um grafo
void addEdge(int vertexALabel, int vertexBLabel, Graph *G);

// Imprime na tela a lista de arestas do grafo
void printEdges(Graph *G, FILE *foutptr);

// Imprime na tela a estrutura que representa o grafo
void printGraph(Graph *G, FILE *foutptr);

#endif