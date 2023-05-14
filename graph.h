#include "structs.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef GRAPHS_H_
#define GRAPHS_H_

Graph *buildGraph(int qtde_vertices);

// Dados dois vértices verifica se existe uma aresta entre eles
bool ehVizinho(int indiceVerticePrincipal, int rotuloVerticeVizinho, Graph *G);

// Remove um vértice da lista de vizinhos de um vértice
void removerVizinho(int rotuloVizinho, int rotuloVertice, Graph *G);

// Remove um vértice de um grafo
void removeVertice(int rotuloDoVerticeRemovido, Graph *G);

// Remove uma aresta de um grafo
void removeAresta(int rotuloVerticeA, int rotuloVerticeB, Graph *G);

// Adiciona um novo nó à vizinhança de um vértice na lista de adjacências
void adicionarVizinho(int rotuloNovoVizinho, int rotuloVertice, Graph *G);

// Cria uma aresta em um grafo
void criaAresta(int rotuloVerticeA, int rotuloVerticeB, Graph *G);

// Imprime na tela a lista de arestas do grafo
void imprimeArestas(Graph *G, FILE *foutptr);

// Imprime na tela a estrutura que representa o grafo
void printGraph(Graph *G, FILE *foutptr);

#endif