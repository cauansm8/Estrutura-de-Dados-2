#include <stdio.h>
#include <stdbool.h>

/* 
estrutura pilha e fila para grafo de lista de adjacência
*/

// estrutura do nó
typedef struct noGrafo
{

    int peso;
    int m;
    struct noGrafo *prox;

} noGrafo;

// estrutura do grafo
typedef struct grafo
{
    int n;
    noGrafo **adj;

} grafo;


// estrutura no de fila e pilha
typedef struct noLista{

    int vertice;
    struct noLista *prox;

}noLista;

typedef struct {

    struct noLista *topo;
    
}pilhaLista;

pilhaLista* criarPilha()
{
    pilhaLista *p = malloc(sizeof(pilhaLista));

    p->topo = NULL;

    return p;
}

void empilhar(pilhaLista *p, int vertice)
{
    noLista *novoNumero = malloc(sizeof(noLista));

    novoNumero->vertice = vertice;
    novoNumero->prox = p->topo;

    p->topo = novoNumero;
}

int desempilhar(pilhaLista *p)
{
    noLista *aux = p->topo;

    p->topo = p->topo->prox;

    int vertice = aux->vertice;

    free(aux);

    return vertice;
}

bool pilha_vazia (pilhaLista *p)
{
    if (p->topo == NULL){
        return true;
    }

    return false;
}

void destroi_pilha (pilhaLista *p)
{
    noLista *aux = p->topo;

    while (aux != NULL)
    {
        noLista *remover = aux;

        aux = aux->prox;

        free(remover);

    }

    free (p);
}

void printar_Pilha (pilhaLista *p)
{
    noLista *aux = p->topo;

    while (aux != NULL)
    {
        printf ("%d  ", aux->vertice);

        aux = aux->prox;
    }

    printf ("\n");
}


///////////////////////////////////////////////////////////

typedef struct filaLista{

    struct noLista *inicio;
    
}filaLista;

filaLista* criarFila()
{
    filaLista *f = malloc(sizeof(filaLista));

    f->inicio = NULL;

    return f;
}

void enfileirar (filaLista *f, int vertice)
{
    noLista *novoNumero = malloc(sizeof(noLista));

    novoNumero->vertice = vertice;
    novoNumero->prox = NULL;

    if (f->inicio == NULL){
        f->inicio = novoNumero;
    }

    else{
        noLista *aux = f->inicio;

        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }

        aux->prox = novoNumero;
    }
}

int desenfileirar (filaLista *f)
{
    noLista *aux = f->inicio;

    f->inicio = f->inicio->prox;

    int vertice = aux->vertice;

    free(aux);

    return vertice;
}


bool fila_vazia (filaLista *f)
{
    if (f->inicio == NULL){
        return true;
    }

    return false;
}

void destroi_fila (filaLista *f)
{
    noLista *aux = f->inicio;

    while (aux != NULL)
    {
        noLista *remover = aux;

        aux = aux->prox;

        free(remover);
    }
    free (f);
}

void printar_Fila (filaLista *f)
{
    noLista *aux = f->inicio;

    while (aux != NULL)
    {
        printf ("%d  ", aux->vertice);

        aux = aux->prox;
    }

    printf ("\n");
}
