#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef GRAFOS_H_
#define GRAFOS_H_

Grafo* constroiGrafo (int qtde_vertices);

//Dados dois vértices verifica se existe uma aresta entre eles
bool ehVizinho (int indiceVerticePrincipal, int rotuloVerticeVizinho, Grafo *G);

//Insere um vértice no grafo
void insereVertice(int rotulo, Grafo *G);

// Remove um vértice da lista de vizinhos de um vértice
void removerVizinho(int rotuloVizinho, int rotuloVertice, Grafo *G);

//Função de apoio à função removeAresta
void removeArestaDoVetor(Grafo* G, int i);

//Remove uma aresta de um grafo
void removeAresta(int rotuloVerticeA, int rotuloVerticeB, Grafo* G);

//Remove um vértice do grafo e suas arestas
void removeVertice(int rotuloRemover, Grafo *G);

//Adiciona um novo nó à vizinhança de um vértice na lista de adjacências
void adicionarVizinho(int rotuloNovoVizinho, int rotuloVertice, Grafo* G);

//Cria uma aresta em um grafo
void criaAresta(int rotuloVerticeA, int rotuloVerticeB, Grafo* G);

//Imprime na tela a lista de arestas do grafo
void imprimeArestas(Grafo *G);

//Imprime na tela a estrutura que representa o grafo
void imprimeGrafo(Grafo* G);

#endif