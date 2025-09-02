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
no* busca_rec(no *atual, unsigned chave_buscada, int bit_anterior)
{
    // se o bit do nó atual for menor que w (bit do nó anterior) - significa que subiu
    if (atual->bit <= bit_anterior)
    {
        return atual;
    }

    // verifica o bit da posicao raiz->bit na chave_buscada
    // se for zero - esquerda
    // se for um   - direita
    if (bit(chave_buscada, atual->bit) == 0)
    {
        return busca_rec (atual->esq, chave_buscada, atual->bit);
    }
    else
    {
        return busca_rec (atual->dir, chave_buscada, atual->bit);
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

/* 
    A inserção tem duas etapas de busca
        - 1° busca: encontra o nó com maior semelhança
        - 2° busca + inserção: encontra o nó semelhante e insere com base no bit de diferença
                                                            bit(chave, i)

*/


void insere (no *raiz, unsigned chave)
{
    int i;

    // passa o raiz->esq pq a cabeça é dummy 
    no *retorno_da_busca = busca_rec (raiz->esq, chave, -1);

    if (chave == retorno_da_busca->chave)
    {
        printf ("\nElemento ja esta na arvore!");
        return;
    }

    // LOOP IMPORTANTE
    // verificando onde se diferenciam
    // ex: 001 e 010
    // -> 2 - somente a primeira posição é igual (lembrando que a contagem de bit() é da esquerda pra direita)
    // a posição 2 é diferente
    for (i = 0; bit(chave, i) == bit(retorno_da_busca, i); i++);

    // novamente, o raiz->esq é para sair do dummy
    raiz->esq = insere_rec(raiz->esq, chave, i, raiz);

}

no* insere_rec (no *raiz, unsigned chave, int i, no *pai)
{
    no *novoNo;

    // verificação para ver se subiu ou foi para o mesmo nó
    if (raiz->bit <= i || raiz->bit < pai->bit)
    {
        novoNo = malloc(sizeof(no));

        novoNo->chave = chave;

        novoNo->bit = i;

        // para lembrar -> o ponteiro para si mesmo depende do bit na posicao i
        // bit(chave, i) = 1 -> direita = novoNo
        // bit(chave, i) = 0 -> esquerda = novoNo
        if (bit(chave, i) == 1)
        {
            novoNo->dir = novoNo;
            novoNo->esq = raiz;
        }
        else
        {
            novoNo->esq = novoNo;
            novoNo->dir = raiz;
        }

        return novoNo;
    }


    // se não subiu ou foi para um nó igual ao anterior -> continua a busca
    if (bit(chave, raiz->bit) == 0)
    {
        raiz->esq = insere_rec(raiz->esq, chave, i, raiz);
    }
    else
    {
        raiz->dir = insere_rec(raiz->dir, chave, i, raiz);
    }

    return raiz;

}


int main ()
{






    return 0;
}