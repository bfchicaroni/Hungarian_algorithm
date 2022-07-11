#include <stdio.h>
#include <stdlib.h>

//Estrutura que representa os vértices do grafo.
typedef struct {
  int rotulo;
  struct Vertice *next;
} Vertice;

//Estrutura que representa uma aresta.
typedef struct{
  int u;
  int v;
} Aresta;

typedef struct {
  Vertice* vertices;
  int n; //qtde_vertices
  int m; //qtde_arestas
} Grafo;

Grafo insereVertice(Grafo *G, int rotulo) {
}

//Cria uma aresta em um grafo
void criaAresta(int rotuloVerticeA, int rotuloVerticeB, Grafo* G) {
  adicionarVizinho(rotuloVerticeA, rotuloVerticeB, G);
  adicionarVizinho(rotuloVerticeB, rotuloVerticeA, G);
  G->m ++;
}

//Remove uma aresta de um grafo
void removeAresta(int rotuloVerticeA, int rotuloVerticeB, Grafo* G) {
  removerVizinho(rotuloVerticeA, rotuloVerticeB, G);
  removerVizinho(rotuloVerticeB, rotuloVerticeA, G);
  G->m --;
}

//Adiciona um novo nó à vizinhança de um vértice na lista de adjacências
void adicionarVizinho(int rotuloNovoVizinho, int rotuloVertice, Grafo* G) {
  //Cria a estrutura do novo vizinho
  Vertice *novoVizinho = (Vertice*) malloc (sizeof(Vertice));
  (*novoVizinho).rotulo = rotuloNovoVizinho;
  (*novoVizinho).next = NULL;
  
  //encontra o vértice no vetor que representa o grafo
  Vertice *vg = G->vertices;
  int i = 0;
  while ( i<G->n && vg[i].rotulo != rotuloVertice ){
    i++;
  }

  //o vértice não existe
  if (i == G->n) {
    return;
  }

  //caso o vértice não tenha vizinhos, acrescenta como o primeiro
  Vertice *primeiro = &vg[i];
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

// Remove um vértice da lista de vizinhos de um vértice
void removerVizinho(int rotuloVizinho, int rotuloVertice, Grafo *G) {

  //encontra o vértice no vetor que representa o grafo
  Vertice *vg = G->vertices;
  int i = 0;
  while ( i<G->n && vg[i].rotulo != rotuloVertice ){
    i++;
  }

  //o vértice não existe
  if (i == G->n) {
    return;
  }

  Vertice *atual = vg[i].next;
  Vertice *anterior;
  while ( atual != NULL) {
    if (atual->rotulo == rotuloVizinho) {
      if (atual == vg[i].next) {
        vg[i].next = atual->next;
      } else {
        anterior->next = atual->next;
      }
    } 
    anterior = atual;
    atual = atual->next;
  }
}

//Imprime na tela a estrutura que representa o grafo
void imprimeGrafo(Grafo* G){
  int i;
  Vertice *vg = G->vertices;
  for(i=0; i < G->n; i++) {
    printf ("|%d|", vg[i].rotulo);
    Vertice *atual = vg[i].next;
    while (atual!=NULL){
      printf(" -> %d ", atual ->rotulo);
      atual = atual->next;
    }
    printf("\n");
  }
}

//Constroi um grafo sem arestas com a qtde de vertices passada como parâmetro
Grafo* constroiGrafo (int qtde_vertices) {
  Grafo *G;
  G = malloc(sizeof(Grafo));
  G->vertices = malloc(qtde_vertices*sizeof(Vertice));
  G->n = qtde_vertices;
  G->m = 0;
  int i;
  Vertice novoVertice;
  for (i=0; i<qtde_vertices; i++) {
    novoVertice.rotulo = i + 1;
    novoVertice.next = NULL;
    G->vertices[i] = novoVertice;
  }
  return G;
}

int main(void) {
  int qtde_vertices = 5;
  Grafo *G = constroiGrafo(qtde_vertices);

  criaAresta(3, 2, G);
  criaAresta(1, 5, G);
  adicionarVizinho(4, 2, G);

  imprimeGrafo(G);

  removerVizinho(4, 2, G);
  removeAresta(1, 5, G);
  imprimeGrafo(G);

  return 0;
}
