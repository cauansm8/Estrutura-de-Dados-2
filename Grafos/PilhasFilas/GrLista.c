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
    noGrafo *prox;

} noGrafo;

// estrutura do grafo
typedef struct grafo
{
    int n;
    noGrafo **adj;

} grafo;


// estrutura no de fila e pilha
typedef struct{

    noGrafo *no;
    noLista *prox;

}noLista;

typedef struct {

    noLista *topo;
    
}pilhaLista;

pilhaLista* criarPilha()
{
    pilhaLista *p = malloc(sizeof(pilhaLista));

    p->topo = NULL;

    return 0;
}

void empilhar(pilhaLista *p, noGrafo *no)
{
    noLista *novoNumero = malloc(sizeof(noLista));

    novoNumero->no = no;
    novoNumero->prox = p->topo;

    p->topo = novoNumero;
}

int desempilhar(pilhaLista *p)
{
    noLista *aux = p->topo;

    p->topo = p->topo->prox;

    return aux->no->m;
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

    while (aux->prox != NULL)
    {
        noLista *remover = aux;

        aux = aux->prox;

        free(remover);

    }

    free (p);
}




///////////////////////////////////////////////////////////

typedef struct {

    noLista *inicio;
    
}filaLista;

filaLista* criarFila()
{
    filaLista *f = malloc(sizeof(filaLista));

    f->inicio = NULL;
}

void enfileirar (filaLista *f, noGrafo *no)
{
    noLista *novoNumero = malloc(sizeof(noLista));

    novoNumero->no = no;
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

    return aux->no->m;
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

    while (aux->prox != NULL)
    {
        noLista *remover = aux;

        aux = aux->prox;

        free(remover);
    }
    free (f);
}