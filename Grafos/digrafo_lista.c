#include <stdio.h>
#include <stdlib.h>
#include "PilhasFilas/GrLista.c"
#include "Heap/heap.c"



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

// imprime amigos de amigos
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

// busca em profundidade com pilha
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

// auxiliar de ordenacao_topologica
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

// verifica quais vertices não tem conexão e printa de ordem reversa (semelhante ao pos_ordem em arvores binarias)
void ordenacao_topologica(grafo *g)
{
    printf("\nOrdenacao topologica: ");

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

// encontra o menor caminho possível entre dois pontos -> retorna os predecessores do pontos
int *dijkstra(grafo *g, int inicio)
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
        int dist_v = heap->v[0].prioridade;

        int atual = extrai_minimo_FP(heap);

        if (dist_v != INT_MAX)
        {
            for (noGrafo *aux = g->adj[atual]; aux != NULL; aux = aux->prox)
            {
                if (dist_v + aux->peso < prioridade_FP(heap, aux->m))
                {
                    pai[aux->m] = atual;

                    diminuiprioridade_FP(heap, aux->m, dist_v + aux->peso);
                }
            }
        }
    }

    return pai;
}

// resulta na arvore geradora minima - conecta todos os vertices com o menor custo total
int *prim(grafo *g, int s)
{
    int *pai = malloc(g->n * sizeof(int));

    FP *h = criar_FP(g->n);

    for (int v = 0; v < g->n; v++)
    {
        pai[v] = -1;
        insere_FP(h, v, INT_MAX);
    }

    pai[s] = s;

    diminuiprioridade_FP(h, s, 0);

    while (!vazia_FP(h))
    {
        int atual = extrai_minimo_FP(h);

        for (noGrafo *aux = g->adj[atual]; aux != NULL; aux = aux->prox)
        {
            if (aux->peso < prioridade_FP(h, aux->m))
            {
                diminuiprioridade_FP(h, aux->m, aux->peso);

                pai[aux->m] = atual;
            }
        }
    }
    return pai;
}


int main()
{
    grafo *g = criarGrafo(4);

    insere_aresta(g, 0, 1, 8);
    insere_aresta(g, 0, 2, 5);
    insere_aresta(g, 2, 3, 5);
    insere_aresta(g, 3, 1, 1);

    int *resultado = prim(g, 0);

    destroi_grafo(g);

    return 0;
}