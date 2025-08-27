#include <stdio.h>
#include <stdlib.h>

#define bits_na_chave 32

typedef struct no{
    unsigned chave;
    struct no *esq, *dir;
} no;

no* criarNo(unsigned chave)
{
    no *novoNo = malloc(sizeof(no));
    novoNo->chave = chave;
    novoNo->esq = NULL;
    novoNo->dir = NULL;

    return novoNo;
}

unsigned bit(unsigned chave, int nivel)
{
    return chave >> (bits_na_chave - 1 - nivel) & 1;
}

no* busca_rec(no *raiz, unsigned chave, int nivel)
{
    if (raiz == NULL)
    {
        printf ("\nNão encontrado! - retornando null");
        return NULL;
    }

    if (chave == raiz->chave)
    {
        printf ("\nNumero encontrado!");
        return raiz;
    }

    if (bit(chave, nivel) == 0)
    {
        return busca_rec (raiz->esq, chave, nivel+1);
    }
    else
    {
        return busca_rec (raiz->dir, chave, nivel+1);
    }
}

no* busca (no *raiz, unsigned chave)
{
    return busca_rec(raiz, chave, 0);
}


no* inserir_rec (no *raiz, unsigned chave, int nivel)
{
    if (raiz == NULL)
    {
        no *novoNo = criarNo(chave);

        return novoNo;
    }

    if (chave == raiz->chave)
    {
        return raiz;
    }

    if (bit(chave, nivel) == 0)
    {
        raiz->esq = inserir_rec(raiz->esq, chave, nivel+1);
    }
    else if (bit(chave, nivel) == 1)
    {
        raiz->dir = inserir_rec(raiz->dir, chave, nivel+1);
    }

    return raiz;
}


no* inserir(no *raiz, unsigned chave)
{
    return inserir_rec(raiz, chave, 0);
}

void imprimir (no *raiz)
{
    if (raiz != NULL)
    {
        imprimir(raiz->esq);
        printf ("\n%d", raiz->chave);
        imprimir(raiz->dir);
    }
}


int main ()
{
    no *raiz = NULL;

    raiz = inserir(raiz, 1);

    raiz = inserir(raiz, 8);

    raiz = inserir(raiz, 2);

    raiz = inserir(raiz, 4);

    raiz = inserir(raiz, 9);

    raiz = inserir(raiz, 12);

    imprimir(raiz);

    return 0;
}
