#include <stdio.h>
#include <stdlib.h>

#define bits_na_chave 4

typedef struct no{
    unsigned chave;
    int bit;
    struct no *esq;
    struct no *dir;
}no;

unsigned bit (unsigned chave, int nivel)
{
    return chave >> (bits_na_chave - 1 - nivel) & 1;
}

// função de busca do nó
no* busca_rec(no *raiz, unsigned chave_buscada, int w)
{
    // se o bit do nó atual for menor que w (bit do nó anterior) - significa que subiu
    if (raiz->bit <= w)
    {
        return raiz;
    }

    // verifica o bit da posicao raiz->bit na chave_buscada
    // se for zero - esquerda
    // se for um   - direita
    if (bit(chave_buscada, raiz->bit) == 0)
    {
        return busca_rec (raiz->esq, chave_buscada, raiz->bit);
    }
    else
    {
        return busca_rec (raiz->dir, chave_buscada, raiz->bit);
    }

}

// função que chama a busca
no* busca(no *raiz, unsigned x)
{
    no *retorno = busca_rec(raiz, x, -1);

    if (retorno->chave == x)
    {
        printf ("\nENCONTRADO!");
        return retorno;
    }

    printf ("\nNAO ENCONTRADO! - retornando null");
    return NULL;
}


int main ()
{






    return 0;
}