#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

#include "jogador.h"

// estrutura grafo com matriz de adjacencia
typedef struct {
    int numVertices;
    Jogador* jogadores;
    float** matriz;
} GrafoMatriz;

// funcoes do grafo com matriz de adjacencia
GrafoMatriz* criarGrafoMatriz(int n, Jogador* jogs);
void adicionarArestaMatriz(GrafoMatriz* g, int src, int dest, float peso);
void liberarGrafoMatriz(GrafoMatriz* g);

// algoritmos especificos
void dfsMatriz(GrafoMatriz* g, int inicio);
void dfsRecursivoMatriz(GrafoMatriz* g, int v, int* visitado, int nivel);
void dijkstraMatriz(GrafoMatriz* g, int inicio, int fim);
void primMatriz(GrafoMatriz* g);
void componentesConexosMatriz(GrafoMatriz* g);
int existeCaminhoMatriz(GrafoMatriz* g, int inicio, int fim);
void recomendarPasseMatriz(GrafoMatriz* g, int jogador);

#endif