#include "grafos.h"
#include "estruturas.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Constroi um grafo sem arestas com a qtde de vertices passada como parâmetro
Grafo *constroiGrafo(int qtde_vertices) {
  Grafo *G;
  G = malloc(sizeof(Grafo));
  G->vertices = malloc(qtde_vertices * sizeof(Vertice));
  G->existe = malloc(qtde_vertices * sizeof(bool));
  int qtde_arestas = (qtde_vertices * (qtde_vertices - 1)) / 2;
  G->maxArestas = qtde_arestas;
  G->n = qtde_vertices;
  G->nExistentes = qtde_vertices;
  G->m = 0;
  int i;
  Vertice novoVertice;
  for (i = 0; i < qtde_vertices; i++) {
    novoVertice.rotulo = i;
    novoVertice.next = NULL;
    G->vertices[i] = novoVertice;
    G->existe[i] = true;
  }
  return G;
}

// Dados dois vértices verifica se existe uma aresta entre eles
bool ehVizinho(int indiceVerticePrincipal, int rotuloVerticeVizinho, Grafo *G) {

  if (!G->existe[indiceVerticePrincipal]) {
    return false;
  }

  Vertice *vg = G->vertices;
  Vertice *atual = vg[indiceVerticePrincipal].next;

  while (atual != NULL) {
    if (atual->rotulo == rotuloVerticeVizinho) {
      return true;
    }
    atual = atual->next;
  }
  return false;
}

// Remove um vértice da lista de vizinhos de um vértice
void removerVizinho(int rotuloVizinho, int rotuloVertice, Grafo *G) {

  if (!G->existe[rotuloVertice]) {
    printf("Nao e possivel remover %d dos vizinhos de %d pois %d nao existe\n",
           rotuloVizinho, rotuloVertice, rotuloVertice);
    return;
  }

  Vertice *vg = G->vertices;
  Vertice *atual = vg[rotuloVertice].next;

  Vertice *anterior;
  while (atual != NULL) {
    if (atual->rotulo == rotuloVizinho) {
      if (atual == vg[rotuloVertice].next) {
        vg[rotuloVertice].next = atual->next;
      } else {
        anterior->next = atual->next;
      }
    }
    anterior = atual;
    atual = atual->next;
  }
}

void removeVertice(int rotuloDoVerticeRemovido, Grafo *G) {
  Vertice *vizinho;
  if (G->existe[rotuloDoVerticeRemovido]) {
    if (G->vertices[rotuloDoVerticeRemovido].next != NULL) {
      vizinho = G->vertices[rotuloDoVerticeRemovido].next;
      while (vizinho != NULL) {
        if (G->existe[vizinho->rotulo]) {
          removerVizinho(rotuloDoVerticeRemovido, vizinho->rotulo, G);
          G->m--;
        }
        vizinho = vizinho->next;
      }
    }
  } else {
    printf("Nao e possivel remover o vertice %d pois ele nao existe\n",
           rotuloDoVerticeRemovido);
  }

  G->existe[rotuloDoVerticeRemovido] = false;
  G->nExistentes--;
}

// Remove uma aresta de um grafo
void removeAresta(int rotuloVerticeA, int rotuloVerticeB, Grafo *G) {
  if (G->existe[rotuloVerticeA] && G->existe[rotuloVerticeB]) {
    removerVizinho(rotuloVerticeA, rotuloVerticeB, G);
    removerVizinho(rotuloVerticeB, rotuloVerticeA, G);
    G->m--;
  }
}

// Adiciona um novo nó à vizinhança de um vértice na lista de adjacências
void adicionarVizinho(int rotuloNovoVizinho, int rotuloVertice, Grafo *G) {

  if (!G->existe[rotuloVertice]) {
    printf("Nao e possivel adicionar um novo vizinho a %d pois %d nao existe\n",
           rotuloVertice, rotuloVertice);
    return;
  } else if (!G->existe[rotuloNovoVizinho]) {
    printf("Nao e possivel adicionar %d como vizinho de um vertice pois o "
           "vertice %d nao existe\n",
           rotuloNovoVizinho, rotuloNovoVizinho);
    return;
  }

  // Cria a estrutura do novo vizinho
  Vertice *novoVizinho = (Vertice *)malloc(sizeof(Vertice));
  (*novoVizinho).rotulo = rotuloNovoVizinho;

  // Encontra o endereço do vértice que vai receber o novo vizinho
  Vertice *vg = G->vertices;
  Vertice *primeiro = &vg[rotuloVertice];

  // Insere o novo vizinho no início da lista de vizinhos do vértice
  (*novoVizinho).next = primeiro->next;
  primeiro->next = novoVizinho;
}

// Cria uma aresta em um grafo
void criaAresta(int rotuloVerticeA, int rotuloVerticeB, Grafo *G) {
  if (G->existe[rotuloVerticeA] && G->existe[rotuloVerticeB]) {
    adicionarVizinho(rotuloVerticeA, rotuloVerticeB, G);
    adicionarVizinho(rotuloVerticeB, rotuloVerticeA, G);
    G->m++;
  }
}

// Imprime na tela a lista de arestas do grafo
void imprimeArestas(Grafo *G, FILE *foutptr) {
  int i;
  Vertice *vizinho;
  for (i = 0; i < G->n; i++) {
    if (G->existe[i]) {
      if (G->vertices[i].next != NULL) {
        vizinho = G->vertices[i].next;
        while (vizinho != NULL) {
          if (G->existe[vizinho->rotulo] && i < vizinho->rotulo) {
            fprintf(foutptr, "|%d|---|%d|\n", i, vizinho->rotulo);
          }
          vizinho = vizinho->next;
        }
      }
    }
  }
}

// Imprime na tela a estrutura que representa o grafo
void imprimeGrafo(Grafo *G, FILE *foutptr) {
  int i;
  Vertice *vg = G->vertices;
  bool *existeVertice = G->existe;
  Vertice *atual;
  fprintf(foutptr, "%d %d\n", G->nExistentes, G->m);
  for (i = 0; i < G->n; i++) {
    if (existeVertice[i]) {
      fprintf(foutptr, "|%d|", vg[i].rotulo);
      atual = vg[i].next;
      while (atual != NULL) {
        fprintf(foutptr, " -> %d ", atual->rotulo);
        atual = atual->next;
      }
      fprintf(foutptr, "\n");
    }
  }
  imprimeArestas(G, foutptr);
  fprintf(foutptr, "================================================\n");
}