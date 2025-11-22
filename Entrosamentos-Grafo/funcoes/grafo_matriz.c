#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "../estruturas/grafo_matriz.h"


// gera um grafo com matriz de adjacencia
GrafoMatriz* criarGrafoMatriz(int n, Jogador* jogs)
{
    GrafoMatriz* g = (GrafoMatriz*) malloc(sizeof(GrafoMatriz));
    
    g->numVertices = n;
    
    g->jogadores = jogs;
    
    g->matriz = (float**)malloc(n * sizeof(float*));

    
    // inicializa a matriz com valores 0
    for (int i = 0; i < n; i++)
    {
        g->matriz[i] = (float*) malloc(n * sizeof(float));
        for (int j = 0; j < n; j++)
        {
            g->matriz[i][j] = 0.0;
        }
    }

    return g;
}

// insercao no grafo
void adicionarArestaMatriz(GrafoMatriz* g, int src, int dest, float peso)
{   
    g->matriz[src][dest] = peso;
    g->matriz[dest][src] = peso;
}

// free no grafo
void liberarGrafoMatriz(GrafoMatriz* g)
{
    // free nas linhas
    for (int i = 0; i < g->numVertices; i++)
    {
        free(g->matriz[i]);
    }
    
    // free na matriz
    free(g->matriz);

    // free no grafo
    free(g);
}

// dfs recursivo 
// função recursiva da DFS (matriz)
void dfsRecursivoMatriz(GrafoMatriz* g, int v, int* visitado, int nivel)
{
    // marca o vértice como visitado
    visitado[v] = 1;
    
    // imprime com indentação de árvore
    for(int i = 0; i < nivel; i++)
        printf("   ");

    printf("|-> %s (%s)\n", g->jogadores[v].nome, g->jogadores[v].posicao);

    // percorre todos os vértices para achar vizinhos
    for (int i = 0; i < g->numVertices; i++)
    {
        // percorre pelos vizinhos nao visitados
        if (g->matriz[v][i] > 0 && !visitado[i])
        {
            // chamada recursiva para o vizinho
            dfsRecursivoMatriz(g, i, visitado, nivel + 1);
        }
    }
}

// dfs - busca em profundidade
void dfsMatriz(GrafoMatriz* g, int inicio)
{
    printf("\nDFS (Matriz) iniciando em %s\n", g->jogadores[inicio].nome);
    
    // criando o vetor auxiliar 'visitado'
    int* visitado = (int*)calloc(g->numVertices, sizeof(int));
    
    // realizando busca dfs (nível inicial = 0)
    dfsRecursivoMatriz(g, inicio, visitado, 0);
    
    printf("FIM\n");
    
    // free no vetor visitado
    free(visitado);
}

void imprimeArvoreRecursiva(GrafoMatriz* g, int v, int* pai, int nivel)
{
    for(int k = 0; k < nivel; k++)
        printf("   ");

    printf("|-> %s (%s)\n", g->jogadores[v].nome, g->jogadores[v].posicao);

    for(int i = 0; i < g->numVertices; i++)
    {
        if(pai[i] == v)
            imprimeArvoreRecursiva(g, i, pai, nivel + 1);
    }
}

// bfs - busca em largura
void bfsMatriz(GrafoMatriz* g, int inicio)
{
    printf("\nBFS (Matriz) iniciando em %s\n", g->jogadores[inicio].nome);
    
    // criiando o vetor auxiliar 'visitado'
    int* visitado = (int*)calloc(g->numVertices, sizeof(int));

    // criando a fila estática
    int* fila = (int*)malloc(g->numVertices * sizeof(int));
    
    int frente = 0, tras = 0;

    int* pai = malloc(g->numVertices * sizeof(int));
    for(int i = 0; i < g->numVertices; i++)
        pai[i] = -1;

    // marcando o primeiro como visitado
    visitado[inicio] = 1;
    
    fila[tras++] = inicio;

    // realizando a busca bfs
    while(frente < tras)
    {
        // pegando o primeiro da fila
        int v = fila[frente++];

        // percorrendo os vizinhos
        for(int i = 0; i < g->numVertices; i++)
        {
            // se o vizinho nao estiver sido visitado -> visita ele e adiciona na fila
            if (g->matriz[v][i] > 0 && !visitado[i])
            {
                visitado[i] = 1;
                pai[i] = v;
                fila[tras++] = i;
            }
        }
    }
    
    printf("%s (%s)\n", g->jogadores[inicio].nome, g->jogadores[inicio].posicao);

    for(int i = 0; i < g->numVertices; i++)
    {
        if(pai[i] == inicio)
            imprimeArvoreRecursiva(g, i, pai, 0);
    }

    // liberando os vetores visitado e fila
    free(visitado);
    
    free(fila);
    free(pai);
}


// estrutura de dados para o min-heap (Dijkstra e Prim)
typedef struct
{
    int vertice;
    float dist;
}HeapNoMatriz;

// estrutura do min-heap
typedef struct
{
    HeapNoMatriz* array;
    int tamanho;
    int capacidade;
}MinHeapMatriz;


// criar heap
MinHeapMatriz* criarHeapMatriz(int cap)
{
    MinHeapMatriz* h = (MinHeapMatriz*)malloc(sizeof(MinHeapMatriz));
    
    h->array = (HeapNoMatriz*)malloc(cap * sizeof(HeapNoMatriz));
    
    h->tamanho = 0;
    
    h->capacidade = cap;
    
    return h;
}

// trocar dois nós do heap
void trocarMatriz(HeapNoMatriz* a, HeapNoMatriz* b)
{
    HeapNoMatriz temp = *a;
    
    *a = *b;
    
    *b = temp;
}

// ajustar para cima
void heapifyUpMatriz(MinHeapMatriz* h, int idx)
{
    // enquanto nao chegar na raiz
    while (idx > 0)
    {
        int pai = (idx - 1) / 2;
        
        // se o no atual for menor que o pai -> troca
        if (h->array[idx].dist < h->array[pai].dist)
        {
            trocarMatriz(&h->array[idx], &h->array[pai]);
            idx = pai;
        } 

        else
        {
            break;
        }
    }
}

// ajustar para baixo
void heapifyDownMatriz(MinHeapMatriz* h, int idx)
{
    int menor = idx;
    
    int esq = 2 * idx + 1;
    
    int dir = 2 * idx + 2;

    // verifica se o filho esquerdo é menor
    if (esq < h->tamanho && h->array[esq].dist < h->array[menor].dist)
    {
        menor = esq;
    }
        
    // verifica se o filho direito é menor
    if (dir < h->tamanho && h->array[dir].dist < h->array[menor].dist)
    {
        menor = dir;
    }

    // se o menor nao for o idx atual, troca e continua ajustando para baixo (chama novamente a função para descer o no trocado)
    if (menor != idx) 
    {
        trocarMatriz(&h->array[idx], &h->array[menor]);
        
        heapifyDownMatriz(h, menor);
    }
}

// inserir no heap
void inserirHeapMatriz(MinHeapMatriz* h, int v, float d)
{
    h->array[h->tamanho].vertice = v;
    
    h->array[h->tamanho].dist = d;
    
    heapifyUpMatriz(h, h->tamanho);
    
    h->tamanho++;
}

// extrair o minimo do heap -> remove o no com menor distancia
HeapNoMatriz extrairMinMatriz(MinHeapMatriz* h)
{
    HeapNoMatriz min = h->array[0];
    
    h->array[0] = h->array[h->tamanho - 1];
    
    h->tamanho--;
    
    heapifyDownMatriz(h, 0);
    
    return min;
}

void imprimirRecursivoDijkstraMatriz(GrafoMatriz* g, int* ant, int atual, int nivel)
{
    for(int i = 0; i < nivel; i++)
        printf(" ");

    printf("|-> %s (%s)\n", g->jogadores[atual].nome, g->jogadores[atual].posicao);

    for(int i = 0; i < g->numVertices; i++)
        if(ant[i] == atual)
            imprimirRecursivoDijkstraMatriz(g, ant, i, nivel + 2);
}


// dijkstra -> caminho minimo entre dois vertices(jogadores)
void dijkstraMatriz(GrafoMatriz* g, int inicio, int fim)
{
    printf("\nDijkstra (Matriz) de %s ate %s\n", g->jogadores[inicio].nome, g->jogadores[fim].nome);

    // criando o vetor distancia
    float* dist = (float*)malloc(g->numVertices * sizeof(float));
    
    // criando o vetor anterior
    int* ant = (int*)malloc(g->numVertices * sizeof(int));
    
    // criando o vetor visitado
    int* visitado = (int*)calloc(g->numVertices, sizeof(int));

    // inicializando
    for(int i = 0; i < g->numVertices; i++)
    {
        dist[i] = FLT_MAX;
        ant[i] = -1;
    }

    dist[inicio] = 0.0;

    MinHeapMatriz* h = criarHeapMatriz(g->numVertices * 10);
    
    inserirHeapMatriz(h, inicio, 0.0);

    // loop principal do dijkstra (dps de extrair o minimo, percorre os vizinhos e atualiza as distancias)
    while(h->tamanho > 0)
    {
        HeapNoMatriz atual = extrairMinMatriz(h);
        
        int u = atual.vertice;

        if (visitado[u])
        {
            continue;
        }
        
        visitado[u] = 1;

        // percorrendo os vizinhos
        for (int v = 0; v < g->numVertices; v++)
        {
            float peso = g->matriz[u][v];

            // se o peso for maior que 0 (tem aresta) e nao foi visitado e a nova distancia for menor -> atualiza a distancia
            if (peso > 0 && !visitado[v] && dist[u] + peso < dist[v])
            {
                dist[v] = dist[u] + peso;
                
                ant[v] = u;
                
                inserirHeapMatriz(h, v, dist[v]);
            }
        }
    }

    imprimirRecursivoDijkstraMatriz(g, ant, inicio, 0);

    // free nos vetores e estruturas 

    free(dist);

    free(ant);
    
    free(visitado);
    
    free(h->array);
    
    free(h);
}


// prim -> gera a arvore geradora minima
void primMatriz(GrafoMatriz* g)
{
    printf("\nArvore Geradora Minima - Prim (Matriz)\n");

    // criando o vetor inMST (se o vertice ja esta na MST)
    int* inMST = (int*)calloc(g->numVertices, sizeof(int));
    
    // criando o vetor chave (menor peso para adicionar na MST)
    float* chave = (float*)malloc(g->numVertices * sizeof(float));
    
    // criando o vetor pai 
    int* pai = (int*)malloc(g->numVertices * sizeof(int));


    for(int i = 0; i < g->numVertices; i++)
    {
        chave[i] = FLT_MAX;
        pai[i] = -1;
    }

    chave[0] = 0.0;

    MinHeapMatriz* h = criarHeapMatriz(g->numVertices * 10);
    
    inserirHeapMatriz(h, 0, 0.0);

    float pesoTotal = 0.0;

    // iniciando prim -> enquanto o heap nao estiver vazio, extrai o minimo (nó) e percorre os vizinhos
    while (h->tamanho > 0)
    {
        HeapNoMatriz atual = extrairMinMatriz(h);
        
        int u = atual.vertice;

        if (inMST[u])
        {
            continue;
        }
        
        inMST[u] = 1;

        if (pai[u] != -1)
        {
            printf("%-25s -- %.2f -- %25s\n", g->jogadores[pai[u]].nome, chave[u], g->jogadores[u].nome);
            
            pesoTotal += chave[u];
        }

        // passando pelos vizinhos
        for(int v = 0; v < g->numVertices; v++)
        {
            float peso = g->matriz[u][v];
            
            // se o peso for maior que 0 (tem aresta) e nao esta na MST e o peso for menor que a chave -> atualiza a chave (IGUAL AO DJIKSTRA)
            if (peso > 0 && !inMST[v] && peso < chave[v])
            {
                chave[v] = peso;
                
                pai[v] = u;
                
                inserirHeapMatriz(h, v, chave[v]);
            }
        }
    }

    printf("Peso total da MST: %.2f\n", pesoTotal);

    // free nos betores e estruturas

    free(inMST);

    free(chave);
    
    free(pai);
    
    free(h->array);
    
    free(h);
}

// componentes conexas - indica as componentes ("grupos") conexas do grafo 
void componentesConexosMatriz(GrafoMatriz* g)
{
    printf("\nComponentes Conexos (Matriz)\n");

    int* visitado = (int*)calloc(g->numVertices, sizeof(int));
    
    int numComponentes = 0;

    for (int i = 0; i < g->numVertices; i++)
    {
        if (!visitado[i])
        {
            numComponentes++;
            
            printf("Componente %d: ", numComponentes);

            int* fila = (int*)malloc(g->numVertices * sizeof(int));
            
            int frente = 0, tras = 0;

            visitado[i] = 1;
            
            fila[tras++] = i;

            while(frente < tras)
            {
                int v = fila[frente++];
                
                printf("%s - ", g->jogadores[v].nome);

                for (int j = 0; j < g->numVertices; j++)
                {
                    if (g->matriz[v][j] > 0 && !visitado[j])
                    {
                        visitado[j] = 1;
                        fila[tras++] = j;
                    }
                }
            }
            printf("\n");
            
            free(fila);
        }
    }

    printf("Total de componentes: %d\n", numComponentes);
    
    free(visitado);
}

// verifica se existe caminho entre dois vertices (dois jogadores)
int existeCaminhoMatriz(GrafoMatriz* g, int inicio, int fim)
{
    if (inicio == fim)
    {
        return 1;
    }

    // criando o vetor visitado
    int* visitado = (int*)calloc(g->numVertices, sizeof(int));
    
    // criando fila
    int* fila = (int*)malloc(g->numVertices * sizeof(int));
    
    int frente = 0, tras = 0;

    visitado[inicio] = 1;
    
    fila[tras++] = inicio;

    // enquanto a fila nao estiver vazia
    while(frente < tras)
    {
        int v = fila[frente++];

        // percorrendo os vizinhos
        for (int i = 0; i < g->numVertices; i++)
        {
            // se tem conexao
            if (g->matriz[v][i] > 0)
            {
                // chegou no destino (fim)
                if (i == fim)
                {
                    free(visitado);
                    
                    free(fila);
                    
                    return 1;
                }

                // se nao foi visitado -> marca como visitado e bota na fila (final)
                if (!visitado[i])
                {
                    visitado[i] = 1;
                    
                    fila[tras++] = i;
                }
            }
        }
    }

    // free no vetor e na estrutura
    free(visitado);

    free(fila);
    
    return 0;
}

// recomendacao de passe -> sugere o melhor passe baseado no menor peso (maior entrosamento)
void recomendarPasseMatriz(GrafoMatriz* g, int jogador)
{
    printf("\nRecomendacao de Passe (Matriz) para %s (%s)\n", g->jogadores[jogador].nome, g->jogadores[jogador].posicao);

    float melhorPeso = FLT_MAX;

    int melhor = -1;

    // percorrendo os vizinhos para achar o de menor peso (maior entrosamento)
    for (int i = 0; i < g->numVertices; i++)
    {
        // se tem conexao e o entrosamento for melhor (peso menor)
        if (g->matriz[jogador][i] > 0 && g->matriz[jogador][i] < melhorPeso)
        {
            melhorPeso = g->matriz[jogador][i];
            melhor = i;
        }
    }

    if (melhor != -1)
    {
        printf("Melhor passe: %s (%s)(entrosamento: %.2f)\n", g->jogadores[melhor].nome, g->jogadores[jogador].posicao, 1.0 / melhorPeso);
    } 
    
    else
    {
        printf("Nenhum vizinho disponivel!\n");
    }
}

void imprimirGrafoMatriz(GrafoMatriz* g)
{
    printf("\n    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21\n");
    for(int i = 0; i < g->numVertices; i++)
    {
        printf("%02d ", i);
        for(int j = 0; j < g->numVertices; j++)
        {
            if(g->matriz[i][j] > 0)
            {
                printf("%.1f ", g->matriz[i][j]);
            }
            else
            {
                printf("--- ");
            }
        }
        printf("\n");
    }
}
