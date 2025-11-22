#include <stdio.h>
#include <stdlib.h>
#include "PilhasFilas/GrMatriz.c"


// estrutura do grafo
typedef struct
{
    int n;
    int **adj;

} grafo;

// alocando grafo
grafo *criarGrafo(int n)
{
    grafo *novoG = malloc(sizeof(grafo));

    novoG->n = n;
    novoG->adj = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        novoG->adj[i] = malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            novoG->adj[i][j] = 0;
        }
    }

    return novoG;
}

// desalocando grafo
void destruirGrafo(grafo *g)
{
    for (int i = 0; i < g->n; i++)
    {
        free(g->adj[i]);
    }

    free(g->adj);

    free(g);
}

// inserindo no grafo
void insereAresta(grafo *g, int u, int v)
{
    g->adj[u][v] = 1;
}

// removendo do grafo
void removeAresta(grafo *g, int u, int v)
{
    g->adj[u][v] = 0;
}

// verificando aresta
int temAresta(grafo *g, int u, int v)
{
    return g->adj[u][v];
}

// criando grafo
grafo *ler_grafo()
{
    int n, m;
    printf("\nInforme o numero de elementos: ");
    scanf("%d", &n);

    printf("\nInforme o numero de arestas: ");
    scanf("%d", &m);

    grafo *g = criarGrafo(n);

    for (int i = 0; i < m; i++)
    {
        int u, v;

        printf("\nInforme u e v:\n");
        scanf("%d %d", &u, &v);

        insereAresta(g, u, v);
    }

    return g;
}

// imprimindo arestas que ha conexao
void imprimindoAresta(grafo *g)
{
    printf("\n---IMPRIMINDO ARESTAS COM CONEXOES---\n");

    for (int i = 0; i < g->n; i++)
    {
        for (int j = i + 1; j < g->n; j++)
        {
            if (g->adj[i][j] == 1)
            {
                printf("\n(%d, %d)", i, j);
            }
        }
    }

    printf("\n\n");
}

// quantas conexoes u tem
int grau(grafo *g, int u)
{
    int grau = 0;

    for (int v = 0; v < g->n; v++)
    {
        if (g->adj[u][v] == 1)
        {
            grau++;
        }
    }

    return grau;
}

// quem tem mais conexoes
int maisPopular(grafo *g)
{
    int maiorGrau = grau(g, 0);
    int maiorU = 0;

    for (int u = 1; u < g->n; u++)
    {
        int grau_u = grau(g, u);

        if (grau_u > maiorGrau)
        {
            maiorGrau = grau_u;
            maiorU = u;
        }
    }

    printf("\nMais popular: %d", maiorU);
    printf("\nGrau do mais popular: %d", maiorGrau);

    return maiorU;
}

// imprimindo recomendacoes de conexao para u
void imprimirRecomendacoes(grafo *g, int u)
{
    printf("\nImprimindo recomendacoes para %d\n", u);
    for (int v = 0; v < g->n; v++)
    {
        if (g->adj[u][v] == 1)
        {
            for (int i = 0; i < g->n; i++)
            {
                if (g->adj[v][i] == 1 && i != u && g->adj[u][i] == 0)
                {
                    printf("\n(%d)", i);
                }
            }
        }
    }
}

// auxiliar de existe_caminho
int busca_rec(grafo *g, int *visitado, int v, int t)
{

    if (v == t)
    {
        return 1;
    }

    visitado[v] = 1;

    for (int w = 0; w < g->n; w++)
    {
        if (g->adj[v][w] == 1 && visitado[w] == 0)
        {
            if (busca_rec(g, visitado, w, t) == 1)
            {
                return 1;
            }
        }
    }

    return 0;
}

// verifica se ha caminho entre s e t
int existe_caminho(grafo *g, int s, int t)
{
    int encontrou, *visitado = malloc(g->n * sizeof(int));

    for (int i = 0; i < g->n; i++)
    {
        visitado[i] = 0;
    }

    encontrou = busca_rec(g, visitado, s, t);

    free(visitado);

    return encontrou;
}

// busca em profundidade para o algoiritmo encontra_caminhos()
void busca_em_profundidade(grafo *g, int *pais, int pai, int atual)
{
    pais[atual] = pai;

    for (int i = 0; i < g->n; i++)
    {
        if (g->adj[atual][i] == 1 && pais[i] == -1)
        {
            busca_em_profundidade(g, pais, atual, i);
        }
    }
}

// guarda os pais de cada elemento
int *encontra_caminhos(grafo *g, int s)
{
    int *pai = malloc(g->n * sizeof(int));

    for (int i = 0; i < g->n; i++)
    {
        pai[i] = -1;
    }

    busca_em_profundidade(g, pai, s, s);

    return pai;
}

// imprime o caminho ao contrário (destino retornando para raiz)
void imprimir_caminho_reverso(int destino, int *pai)
{
    printf("%d", destino);

    if (pai[destino] != destino)
    {
        imprimir_caminho_reverso(pai[destino], pai);
    }
}

// imprime o caminho direto (raiz até destino)
void imprimir_caminho(int destino, int *pai)
{
    if (pai[destino] != destino)
    {
        imprimir_caminho(pai[destino], pai);
    }

    printf("%d", destino);
}

// busca em profundidade com pilha
int *busca_em_profundidadePilha(grafo *g, int s)
{

    int *pai = malloc(g->n * sizeof(int));

    int *visitado = malloc(g->n * sizeof(int));

    pilhaMatriz *p = criarPilha();

    for (int v = 0; v < g->n; v++)
    {
        pai[v] = -1;
        visitado[v] = 0;
    }

    empilhar(p, s);

    pai[s] = s;

    while (pilha_vazia(p) == false)
    {
        int v = desempilhar(p);

        visitado[v] = 1;

        for (int w = 0; w < g->n; w++)
        {
            if (g->adj[v][w] && !visitado[w])
            {
                pai[w] = v;
                empilhar(p, w);
            }
        }

        printar_Pilha(p);
    }

    destroi_pilha(p);

    free(visitado);

    return pai;
}

// busca em largura com fila
int *busca_em_larguraFila(grafo *g, int s)
{

    int *pai = malloc(g->n * sizeof(int));

    int *visitado = malloc(g->n * sizeof(int));

    filaMatriz *f = criarFila();

    for (int v = 0; v < g->n; v++)
    {
        pai[v] = -1;
        visitado[v] = 0;
    }

    enfileirar(f, s);

    pai[s] = s;

    visitado[s] = 1;

    while (fila_vazia(f) == false)
    {
        int v = desenfileirar(f);

        for (int w = 0; w < g->n; w++)
        {
            if (g->adj[v][w] && !visitado[w])
            {
                visitado[v] = 1;
                pai[w] = v;
                enfileirar(f, w);
            }
        }

        printar_Fila(f);
    }

    destroi_fila(f);

    free(visitado);

    return pai;
}

// auxiliar de ordenacao_topologica
void visita_rec(grafo *g, int *visitado, int v)
{   
    visitado[v] = 1;

    for (int i = 0; i < g->n; i++)
    {
        if (g->adj[v][i] == 1 && !visitado[i])
        {
            visita_rec(g, visitado, i);
        }
    }
        
    printf("%d ", v);
}

// verifica quais vertices não tem conexão e printa de ordem reversa (semelhante ao pos_ordem em arvores binarias)
void ordenacao_topologica(grafo *g)
{
    printf ("\nOrdenacao topologica: ");

    int s, *visitado = malloc(g->n * sizeof(int));
    for (s = 0; s < g->n; s++)
    {
        visitado[s] = 0;
    }
        
    for (s = 0; s < g->n; s++)
    {
        if (!visitado[s])
        {
            visita_rec(g, visitado, s);
        }
    }
        
    free(visitado);
    printf("\n");
}

// encontra o menor caminho possível entre dois pontos

// Esse algoritmo não foi implementado, pois é necessário alterar a estrutura da matriz (colocar os pesos)
// a implementação desse algoritmo foi feita em 'digrafo_lista.c'

/* int* dijkstra(grafo *g, int inicio)
{
    int *pai = malloc(g->n * sizeof(int));

    FP *heap = criar_FP(g->n);

    for (int i = 0; i < g->n; i++)
    {
        pai[i] = -1;
        insere_FP(heap, i, INT_MAX);
    }

    pai[inicio] = inicio;

    diminuiprioridade_FP(heap, inicio, 0);

    while (!vazia_FP(heap))
    {
        int atual = extrai_minimo_FP(heap);

        if (prioridade_FP(atual, heap) != INT_MAX)
        {
            for (noGrafo *aux = g->adj[atual]; aux != NULL; aux = aux->prox)
            {
                if (prioridade_FP(heap, atual) + aux->peso < prioridade_FP (heap, aux->m))
                {
                    pai[aux->m] = atual;
                    
                    diminuiprioridade_FP(heap, aux->m, prioridade_FP(heap, atual) + aux->peso);
                }
            }
        }
    }

    return pai;
} */




void imprimirMatriz(grafo *g)
{

    printf("/ ");

    for (int i = 0; i < g->n; i++)
    {
        printf("%d  ", i);
    }

    printf("\n");
    for (int i = 0; i < g->n; i++)
    {
        printf("%d ", i);
        for (int j = 0; j < g->n; j++)
        {
            printf("%d  ", g->adj[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    grafo *g = criarGrafo(4);

    insereAresta(g, 0, 2);
    insereAresta(g, 0, 3);
    insereAresta(g, 3, 1);

    ordenacao_topologica(g);

    imprimirMatriz(g);

    int *resultado = busca_em_larguraFila(g, 0);

    for (int i = 0; i < 4; i++)
    {
        printf("\n%d", resultado[i]);
    }

    destruirGrafo(g);

    return 0;
}