#include "estruturas.h"
#include "grafos.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Constroi um grafo sem arestas com a qtde de vertices passada como parâmetro
Grafo* constroiGrafo (int qtde_vertices) {
  Grafo *G;
  G = malloc(sizeof(Grafo));
  G->vertices = malloc(qtde_vertices*sizeof(Vertice));
  int qtde_arestas = (qtde_vertices * (qtde_vertices - 1)) / 2;
  G->maxArestas = qtde_arestas;
  G->arestas = malloc(qtde_arestas*sizeof(Aresta));
  G->n = qtde_vertices;
  G->m = 0;
  int i, j, k;
  Vertice novoVertice;
  for (i=0; i<qtde_vertices; i++) {
    novoVertice.rotulo = i;
    novoVertice.next = NULL;
    G->vertices[i] = novoVertice;
  }
  Aresta novaAresta;
  k = 0;
  for (i = 0; i < qtde_vertices; i++) {
    for(j = i + 1; j < qtde_vertices; j++) {
      novaAresta.u = i;
      novaAresta.v = j;
      novaAresta.existe = false;
      G->arestas[k] = novaAresta;
      k++;
    }
  }
  return G;
}

//Dados dois vértices verifica se existe uma aresta entre eles
bool ehVizinho (int indiceVerticePrincipal, int rotuloVerticeVizinho, Grafo *G) {
  Vertice *vg = G->vertices;
  Vertice *atual = vg[indiceVerticePrincipal].next;

  while( atual != NULL) {
    if(atual->rotulo == rotuloVerticeVizinho) {
      return true;
    }
    atual = atual->next;
  }
  return false;
}

// Remove um vértice da lista de vizinhos de um vértice
void removerVizinho(int rotuloVizinho, int rotuloVertice, Grafo *G) {

  //encontra o vértice no vetor que representa o grafo
  Vertice *vg = G->vertices;
  Vertice *atual = vg[rotuloVertice].next;


  Vertice *anterior;
  while ( atual != NULL) {
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

//Remove uma aresta de um grafo
void removeAresta(int rotuloVerticeA, int rotuloVerticeB, Grafo* G) {
  removerVizinho(rotuloVerticeA, rotuloVerticeB, G);
  removerVizinho(rotuloVerticeB, rotuloVerticeA, G);

  Aresta *ag = G->arestas;

  int i = 0;
  int qtd_arestas = G->maxArestas;
  while (i < qtd_arestas) {
    if (ag[i].u == rotuloVerticeA) {
      if (ag[i].v == rotuloVerticeB) {
        ag[i].existe = false;
        break;
      }
    }
    else if (ag[i].u == rotuloVerticeB) {
      if (ag[i].v == rotuloVerticeA) {
        ag[i].existe = false;
        break;
      }
    }
    i++;
  }
  G->m --;
}

//Adiciona um novo nó à vizinhança de um vértice na lista de adjacências
void adicionarVizinho(int rotuloNovoVizinho, int rotuloVertice, Grafo* G) {
  //Cria a estrutura do novo vizinho
  Vertice *novoVizinho = (Vertice*) malloc (sizeof(Vertice));
  (*novoVizinho).rotulo = rotuloNovoVizinho;

  //Encontra o endereço do vértice que vai receber o novo vizinho
  Vertice *vg = G->vertices;
  Vertice *primeiro = &vg[rotuloVertice];

  //Insere o novo vizinho no início da lista de vizinhos do vértice
  (*novoVizinho).next = primeiro->next;
  primeiro->next = novoVizinho;

} 

//Cria uma aresta em um grafo
void criaAresta(int rotuloVerticeA, int rotuloVerticeB, Grafo* G) {
  adicionarVizinho(rotuloVerticeA, rotuloVerticeB, G);
  adicionarVizinho(rotuloVerticeB, rotuloVerticeA, G);
  Aresta *ag = G->arestas;

  int i = 0;
  int qtd_arestas = G->maxArestas;
  while (i < qtd_arestas) {
    if (ag[i].u == rotuloVerticeA) {
      if (ag[i].v == rotuloVerticeB) {
        ag[i].existe = true;
        break;
      }
    }
    else if (ag[i].u == rotuloVerticeB) {
      if (ag[i].v == rotuloVerticeA) {
        ag[i].existe = true;
        break;
      }
    }
    i++;
  }
  G->m ++;
}

//Imprime na tela a lista de arestas do grafo
void imprimeArestas(Grafo *G) {
  int i;
  Aresta *ag = G->arestas;
  for (i = 0; i < G->maxArestas; i++) {
    if(ag[i].existe == true) {
      printf("|%d|---|%d|\n", ag[i].u, ag[i].v);
    }
  }
}

//Imprime na tela a estrutura que representa o grafo
void imprimeGrafo(Grafo* G){
  printf("================================================\n");
  int i;
  Vertice *vg = G->vertices;
  Vertice *atual;
  for(i=0; i < G->n; i++) {
    printf ("|%d|", vg[i].rotulo);
    atual = vg[i].next;
    while (atual!=NULL){
      printf(" -> %d ", atual ->rotulo);
      atual = atual->next;
    }
    printf("\n");
  }
  printf("Quantidade de vertices: %d\n", G->n);
  printf("Quantidade de arestas: %d\n", G->m);
  imprimeArestas(G);
}