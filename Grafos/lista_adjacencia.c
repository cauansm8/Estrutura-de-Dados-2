#include <stdio.h>
#include <stdlib.h>
#include "PilhasFilas/GrLista.c"

/*

funções não testadas e que não estão nos slides:
    int grau
    int mais popular
    void imprimirRecomendacoes

    busca em profundidade (com pilha e fila)
*/

// cria nó
noGrafo *insere_na_lista(int m, noGrafo *lista, int peso)
{
    noGrafo *novoNo = malloc(sizeof(noGrafo));

    novoNo->peso = peso;
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
void insere_aresta(grafo *g, int u, int v, int peso)
{
    g->adj[v] = insere_na_lista(u, g->adj[v], peso);
    g->adj[u] = insere_na_lista(v, g->adj[u], peso);
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

        if (grau_u > maiorGrau)
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

// busca em profundidade para o algoritmo encontra_componentes()
void visita_recursiva_conexas(grafo *g, int *componentes, int comp, int v)
{
    componentes[v] = comp;

    for (noGrafo *t = g->adj[v]; t != NULL; t = t->prox)
    {
        if (componentes[t->m] == -1)
        {
            visita_recursiva_conexas(g, componentes, comp, t->m);
        }
    }
}

// separa cada componente conexa em grupos diferentes
int *encontra_componentes(grafo *g)
{
    int c = 0, *componentes = malloc(g->n * sizeof(int));

    for (int s = 0; s < g->n; s++)
    {
        componentes[s] = -1;
    }

    for (int s = 0; s < g->n; s++)
    {
        if (componentes[s] == -1)
        {
            visita_recursiva_conexas(g, componentes, c, s);
            c++;
        }
    }

    return componentes;
}



// busca em profundidade para o algoiritmo encontra_caminhos()
void busca_em_profundidade(grafo *g, int *pais, int pai, int atual)
{
    pais[atual] = pai;

    for (noGrafo *t = g->adj[atual]; t != NULL; t = t->prox)
    {
        if (pais[t->m] == -1)
        {
            busca_em_profundidade(g, pais, atual, t->m);
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

int *busca_em_profundidadePilha(grafo *g, int s)
{

    int *pai = malloc(g->n * sizeof(int));

    int *visitado = malloc(g->n * sizeof(int));

    pilhaLista *p = criarPilha();

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
            if (tem_aresta(g, v, w) == 1 && visitado[w] == 0)
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

int *busca_em_larguraFila(grafo *g, int s)
{

    int *pai = malloc(g->n * sizeof(int));

    int *visitado = malloc(g->n * sizeof(int));

    filaLista *f = criarFila();

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
            if (tem_aresta(g, v, w) && !visitado[w])
            {
                visitado[w] = 1;
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

void visita_recursiva_topologica(grafo *g, int *visitado, int v)
{
    visitado[v] = 1;
    for (noGrafo *t = g->adj[v]; t != NULL; t = t->prox)
    {
        if (visitado[t->m] == 0)
        {
            visita_recursiva_topologica(g, visitado, t->m);
        }
            
    }
        
    printf("%d ", v);
}

void ordenacao_topologica(grafo *g)
{
    int *visitado = malloc(g->n * sizeof(int));
    for (int s = 0; s < g->n; s++)
    {
        visitado[s] = 0;
    }
        
    for (int s = 0; s < g->n; s++)
    {
        if (visitado[s] == 0)
        {
            visita_recursiva_topologica(g, visitado, s);
        }
            
    }
        
    free(visitado);
    printf("\n");
}



int main()
{
    grafo *g = criarGrafo(4);

    insere_aresta(g, 0, 2, 3);
    insere_aresta(g, 0, 3, 1);
    insere_aresta(g, 3, 1, 4);

    int *retorno = busca_em_larguraFila(g, 0);

    printf ("\n\n\n");

    for (int i = 0; i < 4; i++)
    {
        printf ("%d   ", retorno[i]);
    }

    return 0;
}