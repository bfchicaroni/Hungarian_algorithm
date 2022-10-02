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
  G->arestas = malloc(qtde_arestas*sizeof(Aresta));
  G->n = qtde_vertices;
  G->m = 0;
  int i;
  Vertice novoVertice;
  for (i=0; i<qtde_vertices; i++) {
    novoVertice.rotulo = i;
    novoVertice.next = NULL;
    G->vertices[i] = novoVertice;
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

//Insere um vértice no grafo
void insereVertice(int rotulo, Grafo *G) {
  //Cria a estrutura do novo vertice
  Vertice novoVertice;
  novoVertice.rotulo = rotulo;
  novoVertice.next = NULL;

  Vertice *vg = G->vertices;
  vg[G->n] = novoVertice;
  G->n++;
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

//Função de apoio à função removeAresta
void removeArestaDoVetor(Grafo* G, int i) {
  int k = i;
  Aresta* ag = G->arestas;
  while(k < G->m - 1) {
    ag[k] = ag[k+1];
    k++;
  }
}

//Remove uma aresta de um grafo
void removeAresta(int rotuloVerticeA, int rotuloVerticeB, Grafo* G) {
  removerVizinho(rotuloVerticeA, rotuloVerticeB, G);
  removerVizinho(rotuloVerticeB, rotuloVerticeA, G);

  Aresta *ag = G->arestas;

  int i = 0;
  int qtd_arestas = G->m;
  while (i < qtd_arestas) {
    if (ag[i].u == rotuloVerticeA) {
      if (ag[i].v == rotuloVerticeB) {
        removeArestaDoVetor(G, i);
        break;
      }
    }
    else if (ag[i].u == rotuloVerticeB) {
      if (ag[i].v == rotuloVerticeA) {
        removeArestaDoVetor(G, i);
        break;
      }
    }
    else {
      i++;
    }
  }
  G->m --;
}

//Remove um vértice do grafo e suas arestas
void removeVertice(int rotuloRemover, Grafo *G) {
  int i = rotuloRemover;
  Vertice *vg = G->vertices;

  for(i = 0; i < G->n; i++) {
    if(ehVizinho(i, rotuloRemover, G)) {
      removeAresta(vg[i].rotulo, rotuloRemover, G);
    }
  }

  int qtd_vertices = G->n;
  // if(i == qtd_vertices) {
  //   return;
  // }
  while(i < qtd_vertices - 1) {
    vg[i] = vg[i+1];
    i++;
  }

  G->n--;
}

//Adiciona um novo nó à vizinhança de um vértice na lista de adjacências
void adicionarVizinho(int rotuloNovoVizinho, int rotuloVertice, Grafo* G) {
  //Cria a estrutura do novo vizinho
  Vertice *novoVizinho = (Vertice*) malloc (sizeof(Vertice));
  (*novoVizinho).rotulo = rotuloNovoVizinho;
  (*novoVizinho).next = NULL;

  Vertice *vg = G->vertices;
  Vertice *primeiro = &vg[rotuloVertice];
  
  //INSERIR VIZINHO NO INICIO DA LISTA
  //caso o vértice não tenha vizinhos, acrescenta como o primeiro
  if (primeiro->next==NULL) {
    primeiro->next = novoVizinho;
    return;
  }
  else {
    //caso o vértice já tenha vizinhos, acrescenta no fim da lista de vizinhos
    Vertice* atual = primeiro->next;
    while (atual->next!=NULL) {
      atual = atual->next;
    }
    atual->next = novoVizinho;
  }

} 

//Cria uma aresta em um grafo
void criaAresta(int rotuloVerticeA, int rotuloVerticeB, Grafo* G) {
  adicionarVizinho(rotuloVerticeA, rotuloVerticeB, G);
  adicionarVizinho(rotuloVerticeB, rotuloVerticeA, G);

  Aresta novaAresta;
  novaAresta.u = rotuloVerticeA;
  novaAresta.v = rotuloVerticeB;

  Aresta *ag = G->arestas;
  ag[G->m] = novaAresta;

  G->m++;
}

//Imprime na tela a lista de arestas do grafo
void imprimeArestas(Grafo *G) {
  int i;
  Aresta *ag = G->arestas;
  for (i = 0; i < G->m; i++) {
    printf("|%d|---|%d|\n", ag[i].u, ag[i].v);
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