#include <stdio.h>
#include <stdlib.h>


/* 

funções não testadas e que não estão nos slides:
    int grau
    int mais popular
    void imprimirRecomendacoes


*/


// estrutura do nó
typedef struct noGrafo
{

    int m;
    noGrafo *prox;

} noGrafo;

// estrutura do grafo
typedef struct grafo
{

    int n;
    noGrafo **adj;

} grafo;

// cria nó
noGrafo *insere_na_lista(int m, noGrafo *lista)
{
    noGrafo *novoNo = malloc(sizeof(noGrafo));

    novoNo->m = m;
    novoNo->prox = lista;

    return novoNo;
}

// cria grafo
grafo *criarGrafo(int n)
{
    grafo *novoGrafo = malloc(sizeof(grafo));

    novoGrafo->n = n;

    novoGrafo->adj = malloc(n * sizeof(noGrafo));

    for (int i = 0; i < n; i++)
    {
        novoGrafo->adj[i] = NULL;
    }

    return novoGrafo;
}

// desaloca nós
void liberar_lista(noGrafo *no)
{
    if (no != NULL)
    {
        liberar_lista(no->prox);
        free(no);
    }
}

// desaloca grafo
void destroi_grafo(grafo *g)
{
    for (int i = 0; i < g->n; i++)
    {
        liberar_lista(g->adj[i]);
    }

    free(g->adj);

    free(g);
}

// inserindo no grafo
void insere_aresta(grafo *g, int u, int v)
{
    g->adj[v] = criarNo(u, g->adj[v]);
    g->adj[u] = criarNo(v, g->adj[u]);
}

// removendo da lista
noGrafo *remove_da_lista(noGrafo *lista, int u)
{
    noGrafo *prox;

    if (lista == NULL)
    {
        return NULL;
    }

    // se for o primeiro, da free e retorna o prox
    else if (lista->m == u)
    {
        prox = lista->prox;

        free(lista);
        return prox;
    }

    else
    {
        lista->prox = remove_da_lista(lista->prox, u);

        return lista;
    }
}

// removendo do grafo
void remove_aresta(grafo *g, int u, int v)
{
    g->adj[u] = remove_da_lista(g->adj[u], v);
    g->adj[v] = remove_da_lista(g->adj[v], u);
}

// verificando se ha aresta
int tem_aresta(grafo *g, int u, int v)
{
    noGrafo *aux = g->adj[u];

    while (aux != NULL)
    {
        if (aux->m == v)
        {
            return 1;
        }

        aux = aux->prox;
    }

    return 0;
}

// imprimindo arestas
void imprime_arestas(grafo *g)
{
    printf("\n---IMPRIMINDO ARESTAS COM CONEXOES---\n");

    for (int i = 0; i < g->n; i++)
    {
        noGrafo *aux = g->adj[i];

        while (aux != NULL)
        {
            printf("\n{%d, %d}", i, aux->m);

            aux = aux->prox;
        }
    }
}

// quantas conexoes u tem
int grau(noGrafo *lista)
{
    int i = 0;

    noGrafo *aux = lista;

    while (aux != NULL)
    {
        i++;

        aux = aux->prox;
    }

    return i;
}

// quem tem mais conexoes
int maisPopular(grafo *g)
{
    int maiorGrau = grau(g->adj[0]);
    int maiorU = 0;

    for (int u = 1; u < g->n; u++)
    {
        int grau_u = grau(g->adj[u]);

        if (grau_u > grau)
        {
            maiorU = u;
            maiorGrau = grau_u;
        }
    }

    printf("\nMais popular: %d", maiorU);
    printf("\nGrau do mais popular: %d", maiorGrau);

    return maiorU;
}

void imprimirRecomendacoes(grafo *g, int u)
{
    printf("\nImprimindo recomendacoes para %d\n", u);

    noGrafo *aux = g->adj[u];

    while (aux != NULL)
    {
        noGrafo *amigo = g->adj[aux->m];
        
        while (amigo != NULL)
        {
            if (tem_aresta(g, u, amigo->m) == 0 && amigo->m != u)
            {
                printf("\n(%d)", amigo->m);
            }


            amigo = amigo->prox;
        }

        aux = aux->prox;
    }
}

/* 
**************
entender melhor esse dois algoritmos abaixo



*/


int* encontra_componentes(grafo *g)
{
    int s, c = 0, *componentes = malloc(g->n * sizeof(int));
    
    for (s = 0; s < g->n; s++)
    {
        componentes[s] = -1;
    }
        
    for (s = 0; s < g->n; s++)
    {
        if (componentes[s] == -1)
        {
            visita_rec(g, componentes, c, s);
            c++;
        }
    }
        
    return componentes;
}

void visita_rec(grafo *g, int *componentes, int comp, int v)
{
    componentes[v] = comp;

    for (noGrafo *t = g->adj[v]; t != NULL; t = t->prox)
    {
        if (componentes[t->m] == -1)
        {
            visita_rec(g, componentes, comp, t->m);
        }
    }
        
}

int main()
{

    return 0;
}