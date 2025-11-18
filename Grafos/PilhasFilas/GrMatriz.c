#include <stdio.h>
#include <stdbool.h>

/* 
estrutura pilha e fila para grafo de matriza de adjacência
*/


typedef struct noMatriz{

    int numero;
    struct noMatriz *prox;

}noMatriz;

typedef struct {

    noMatriz *topo;
    
}pilhaMatriz;

pilhaMatriz* criarPilha()
{
    pilhaMatriz *p = malloc(sizeof(pilhaMatriz));

    p->topo = NULL;

    return p;
}

void empilhar(pilhaMatriz *p, int numero)
{
    noMatriz *novoNumero = malloc(sizeof(noMatriz));

    novoNumero->numero = numero;
    novoNumero->prox = p->topo;

    p->topo = novoNumero;
}

int desempilhar(pilhaMatriz *p)
{
    noMatriz *aux = p->topo;

    p->topo = p->topo->prox;

    return aux->numero;
}

bool pilha_vazia (pilhaMatriz *p)
{
    if (p->topo == NULL){
        return true;
    }

    return false;
}

void destroi_pilha (pilhaMatriz *p)
{
    noMatriz *aux = p->topo;

    while (aux != NULL && aux->prox != NULL)
    {
        noMatriz *remover = aux;

        aux = aux->prox;

        free(remover);

    }

    free (p);
}

void printar_Pilha (pilhaMatriz *p)
{
    noMatriz *aux = p->topo;

    printf ("\npilha: ");

    while (aux != NULL)
    {
        printf ("%d  ", aux->numero);

        aux = aux->prox;
    }

    printf ("\n");
}


///////////////////////////////////////////////////////////

typedef struct filaMatriz{

    struct noMatriz *inicio;
    
}filaMatriz;

filaMatriz* criarFila()
{
    filaMatriz *f = malloc(sizeof(filaMatriz));

    f->inicio = NULL;

    return f;
}

void enfileirar (filaMatriz *f, int numero)
{
    noMatriz *novoNumero = malloc(sizeof(noMatriz));

    novoNumero->numero = numero;
    novoNumero->prox = NULL;

    if (f->inicio == NULL){
        f->inicio = novoNumero;
    }

    else{
        noMatriz *aux = f->inicio;

        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }

        aux->prox = novoNumero;
    }
}

int desenfileirar (filaMatriz *f)
{
    noMatriz *aux = f->inicio;

    f->inicio = f->inicio->prox;

    return aux->numero;
}


bool fila_vazia (filaMatriz *f)
{
    if (f->inicio == NULL){
        return true;
    }

    return false;
}


void destroi_fila (filaMatriz *f)
{
    noMatriz *aux = f->inicio;

    while (aux != NULL && aux->prox != NULL)
    {
        noMatriz *remover = aux;

        aux = aux->prox;

        free(remover);
    }
    free (f);
}

void printar_Fila (filaMatriz *f)
{
    noMatriz *aux = f->inicio;

    printf ("\nfila: ");

    while (aux != NULL)
    {
        printf ("%d  ", aux->numero);

        aux = aux->prox;
    }

    printf ("\n");
}