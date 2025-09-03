#include <stdio.h>
#include <stdlib.h>

/* 
A árvore trie somente tem conteúdo válido em nós folhas!
*/

#define bits_na_chave 4

typedef struct no{

    
    unsigned chave;
    struct no *esq, *dir;

}no;

no* criarNo (unsigned chave)
{
    no *novoNo = malloc (sizeof(no));

    novoNo->chave = chave;
    novoNo->dir = NULL;
    novoNo->esq = NULL;

    return novoNo;
}

unsigned bit (unsigned chave, int nivel)
{
    return chave >> (bits_na_chave - nivel - 1) & 1;
}

no* insere_rec (no *raiz, unsigned chave, int nivel)
{
    // gerando nó -> apenas insere
    if (raiz == NULL)
    {
        no *novoNo = criarNo(chave);

        return novoNo;
    }

    // ajuste - filho à esquerda
    if (raiz->esq != NULL && raiz->dir == NULL)
    {
        unsigned media = (raiz->chave + raiz->esq->chave) / 2;

        no *novoNo = criarNo(media);

        novoNo->esq = raiz->esq;

        novoNo->dir = raiz;

        raiz->esq = NULL;

        return novoNo;
    }

    // ajuste - filho à direita
    if (raiz->esq == NULL && raiz->dir != NULL)
    {
        unsigned media = (raiz->chave + raiz->esq->chave) / 2;

        no *novoNo = criarNo(media);

        novoNo->esq = raiz;
        
        novoNo->dir = raiz->dir;

        raiz->dir = NULL;

        return novoNo;
    }


    // continuando a busca -> se os 
    if (raiz->esq != NULL && raiz->dir != NULL)
    {
        if (bit(chave, nivel) == 0)
        {
            raiz->esq = insere_rec(raiz->esq, chave, nivel + 1);
        }
        else
        {
            raiz->dir = insere_rec(raiz->dir, chave, nivel + 1);
        }
    }

    return raiz;
}

void imprimir_rec (no *raiz)
{
    if (raiz != NULL)
    {
        imprimir_rec(raiz->esq);

        if (raiz->esq == NULL && raiz->dir == NULL)
        {
            printf ("\n%u", raiz->chave);
        }

        imprimir_rec(raiz->dir);
    }
}


no* inserir (no *raiz, unsigned chave)
{
    raiz = insere_rec(raiz, chave, 0);

    return raiz;
}



int main ()
{
    no *raiz = NULL;

    raiz = inserir(raiz, 5);

    raiz = inserir(raiz, 10);

    imprimir_rec(raiz);

    return 0;
}