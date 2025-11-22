#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include "jogador.h"

typedef struct No {
    int destino;
    float peso;
    struct No* prox;
} No;

typedef struct {
    No* cabeca;
} ListaAdj;

typedef struct {
    int numVertices;
    Jogador* jogadores;
    ListaAdj* lista;
} GrafoLista;


//Funções para criar, liberar e manipular o grafo
GrafoLista* criarGrafoLista(int n, Jogador* jogs);
void liberarGrafoLista(GrafoLista* g);
void adicionarArestaLista(GrafoLista* g, int src, int dest, float peso);

//Funções de busca em profundidade e largura
void dfsLista(GrafoLista* g, int inicio);
void dfsRecursivoLista(GrafoLista* g, int v, int* visitado, int nivel);
void bfsLista(GrafoLista* g, int inicio);

//Algoritmos de caminho mínimo e árvore geradora mínima
void dijkstraLista(GrafoLista* g, int inicio, int fim);
void primLista(GrafoLista* g);

//Outras funcionalidades
void componentesConexosLista(GrafoLista* g);
int existeCaminhoLista(GrafoLista* g, int inicio, int fim);
void recomendarPasseLista(GrafoLista* g, int jogador);

//Heap - funções
typedef struct {
    int vertice;
    float dist;
} HeapNoLista;

typedef struct {
    HeapNoLista* array;
    int tamanho;
    int capacidade;
} MinHeapLista;
//Funções para criar e manipular o heap
MinHeapLista* criarHeapLista(int cap);
void trocarLista(HeapNoLista* a, HeapNoLista* b);

//Funções para manter a propriedade do heap quando um nó é inserido ou removido
void heapifyUpLista(MinHeapLista* h, int idx);
void heapifyDownLista(MinHeapLista* h, int idx);

//Função para inserir um novo nó no heap
void inserirHeapLista(MinHeapLista* h, int v, float d);

//Função para extrair o nó com menor distância do heap
HeapNoLista extrairMinLista(MinHeapLista* h);

#endif