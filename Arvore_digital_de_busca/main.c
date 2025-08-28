#include <stdio.h>
#include <stdlib.h>

#define bits_na_chave 4


// estrutura do nó
typedef struct no{
    unsigned chave;
    struct no *esq, *dir;
} no;


// função para criar o nó
no* criarNo(unsigned chave)
{
    no *novoNo = malloc(sizeof(no));
    novoNo->chave = chave;
    novoNo->esq = NULL;
    novoNo->dir = NULL;

    return novoNo;
}

// função para extrair um bit da chave com base no nivel
// ex: 12 = 1100 e nivel = 2
//   retorno = 0 (3 número)
// lembrando que o valor de bits_na_chave é importante para entender qual será o bit de retorno
unsigned bit(unsigned chave, int nivel)
{
    return chave >> (bits_na_chave - 1 - nivel) & 1;
}


// função de busca
// usa a função bit se não encontrar a chave
no* busca_rec(no *raiz, unsigned chave, int nivel)
{
    // se a raiz é nula -> a chave não está na árvore
    if (raiz == NULL)
    {
        printf ("\nNão encontrado! - retornando null");
        return NULL;
    }

    // chave encontrada -> retornando o nó
    if (chave == raiz->chave)
    {
        printf ("\nNumero encontrado!");
        return raiz;
    }

    // buscando (pela esquerda ou direita) a chave
    if (bit(chave, nivel) == 0)
    {
        return busca_rec (raiz->esq, chave, nivel+1);
    }
    else
    {
        return busca_rec (raiz->dir, chave, nivel+1);
    }
}


// função que chama a busca
no* busca (no *raiz, unsigned chave)
{
    return busca_rec(raiz, chave, 0);
}



// função para inserir uma chave na árvore digital de busca
// usa a função bit para escolher o lado da inserção
no* inserir_rec (no *raiz, unsigned chave, int nivel)
{
    
    // se for nulo -> cria-se um novo nó
    if (raiz == NULL)
    {
        no *novoNo = criarNo(chave);

        return novoNo;
    }

    // se a chave ja estiver no nó, apenas retorna
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


// função que chama a inserção
no* inserir(no *raiz, unsigned chave)
{
    return inserir_rec(raiz, chave, 0);
}

// função para imprimir a árvore (mesma impressão em_ordem da árvore ABB)
// obviamente não vai imprimir em ordem crescente, pois a inserção não usa este critério
void imprimir_em_ordem(no *raiz)
{
    if (raiz != NULL)
    {
        imprimir_em_ordem(raiz->esq);
        printf ("\n%d", raiz->chave);
        imprimir_em_ordem(raiz->dir);
    }
}

// função para chamar a impressão
void imprimir(no *raiz)
{
    printf ("\nIMPRIMINDO ARVORE!!\n");
    imprimir_em_ordem(raiz);
    printf ("\n\n");
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
