#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* 
A árvore trie somente tem conteúdo válido em nós folhas!
*/

#define bits_na_chave 4

typedef struct no{

    bool folha; // importante para a inserção
    unsigned chave;
    struct no *esq, *dir;

}no;


// função para criar o nó
no* criarNo (unsigned chave)
{
    no *novoNo = malloc (sizeof(no));

    novoNo->folha = true;
    novoNo->chave = chave;
    novoNo->dir = NULL;
    novoNo->esq = NULL;

    return novoNo;
}

// função que retorna o bit de uma chave considerando o nivel na árvore
unsigned bit (unsigned chave, int nivel)
{
    return chave >> (bits_na_chave - nivel - 1) & 1;
}


// função de inserção
no* insere_rec (no *raiz, unsigned chave, int nivel)
{
    // gerando nó -> apenas insere
    if (raiz == NULL)
    {
        no *novoNo = criarNo(chave);

        return novoNo;
    }


    // se o nó é folha -> tem conteúdo importante + é necessário criar um nó interno/mediador para os dois nós (já existente e o novo)
    if (raiz->folha == true)
    {
        // se o elemento ja existe, nn tem pq inserir na árvore
        if (raiz->chave == chave)
        {
            printf ("\nElemento ja existe");
            return raiz;
        }

        // chave com conteudo não importante, somente serve para preencher o campo, mas não é utilizado
        unsigned chave_intermediaria = (raiz->chave + chave) / 2;

        no *intermediador = criarNo(chave_intermediaria);
        intermediador->folha = false;

        // criamos o intermediador
        // e a partir dele inserimos na árvore
        // entao, verificamos se a chave (da raiz atual) iria para a esquerda ou direita do nivel 
        if (bit(raiz->chave, nivel) == 0)
        {
                intermediador->esq = insere_rec (intermediador->esq, raiz->chave, nivel + 1);
        }
        else
        {
                intermediador->dir = insere_rec (intermediador->dir, raiz->chave, nivel + 1);
        }


        // fazemos o mesmo com a nova chave
        if (bit(chave, nivel) == 0)
        {
                intermediador->esq = insere_rec (intermediador->esq, chave, nivel + 1);
        }
        else
        {
                intermediador->dir = insere_rec (intermediador->dir, chave, nivel + 1);
        }

        // apagamos a raiz 
        free (raiz);

        return intermediador;

    }
    

    // percorre até chegar numa folha
    if (bit(chave, nivel) == 0)
    {
        raiz->esq = insere_rec(raiz->esq, chave, nivel + 1);
    }
    else
    {
        raiz->dir = insere_rec(raiz->dir, chave, nivel + 1);
    }
    

    return raiz;
}

// função que chama a inserção
no* inserir (no *raiz, unsigned chave)
{
    raiz = insere_rec(raiz, chave, 0);

    return raiz;
}


// função para imprimir
void imprimir_rec (no *raiz, int nivel)
{
    if (raiz != NULL)
    {
        imprimir_rec(raiz->esq, nivel + 1);

        if (raiz->esq == NULL && raiz->dir == NULL)
        {
            printf ("\n%d - %u", nivel, raiz->chave);
        }

        imprimir_rec(raiz->dir, nivel + 1);
    }
}

void imprimir (no *raiz)
{
    printf ("\nNIVEL - CHAVE\n-------------");
    imprimir_rec(raiz, 0);
    printf ("\n-------------");
}


int main ()
{
    no *raiz = NULL;

    raiz = inserir(raiz, 3);

    raiz = inserir(raiz, 12);

    raiz = inserir(raiz, 1);

    raiz = inserir(raiz, 5);

    raiz = inserir(raiz, 9);

    imprimir(raiz);

    return 0;
}