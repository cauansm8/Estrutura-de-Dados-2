#include <stdio.h>
#include <stdlib.h>

#define bits_na_chave 8

typedef struct no{
    unsigned chave;
    int bit;
    struct no *esq;
    struct no *dir;
}no;


// função para criar o dummy
no* criarDummy()
{
    no *dummy = malloc(sizeof(no));
    dummy->bit = -1;
    dummy->chave = 99999;
    dummy->esq = dummy;
    dummy->dir = dummy;

    return dummy;
}


// função para pegar o bit de alguma posição específica (igual a função da árvore digital de busca)
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

// função que faz a 2° busca + inserção da chave
no* insere_rec (no *raiz, unsigned chave, int i, no *pai)
{
    // verificação para ver se subiu ou foi para o mesmo nó
    // raiz->bit >= i ===== significa que a diferença está antes - imagina assim:
    //      i = 3
    //      raiz->bit (nó atual) = 4      
    //      ou seja, a diferença na chave do nó atual é "mais profunda"
    //      logo a nova chave deve ser inserida
    //      não achei nos slides algum exemplo de i < raiz->bit


    // raiz->bit <= pai->bit ===== ou subiu (<) ou foi para o mesmo (=)
    if (raiz->bit >= i || raiz->bit <= pai->bit)
    {
       no *novoNo = malloc(sizeof(no));

        novoNo->chave = chave;

        novoNo->bit = i;

        // para lembrar -> o ponteiro para si mesmo depende do bit na posicao i
        // bit(chave, i) = 1 -> direita = novoNo
        // bit(chave, i) = 0 -> esquerda = novoNo
        if (bit(chave, i) == 1)
        {
            novoNo->esq = raiz;
            novoNo->dir = novoNo;
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

// função que faz a primeira busca: nó mais parecido
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
    // -> 1 - somente a posição zero é igual (lembrando que a contagem de bit() é da esquerda pra direita)
    // a posição 1 é diferente
    for (i = 0; bit(chave, i) == bit(retorno_da_busca->chave, i); i++);

    // novamente, o raiz->esq é para sair do dummy
    raiz->esq = insere_rec(raiz->esq, chave, i, raiz);

}

// função para caminhar pelos nós
void imprimir_rec(no* atual, no *anterior)
{

    // essa condição serve para verificar se:
    // subiu 
    // apontou para o mesmo nó
    // ou seja, o caminho para imprimir é: sempre deve aumentar o atual->bit, se não: subiu (diminuiu o bit) ou continuou igual
    if (atual->bit > anterior->bit)
    {
        printf ("\nBit: %d", atual->bit);
        printf ("\nChave: %u", atual->chave);
        printf ("\n");

        imprimir_rec(atual->esq, atual);
        
        imprimir_rec(atual->dir, atual);
        
    }
}

// função para imprimir a árvore
// sempre passa a esquerda (o dummy a esquerda tem nó)
//  a direita aponta para si mesmo
void imprimir (no *raiz)
{
    imprimir_rec(raiz->esq, raiz);
}

int main ()
{
    no *dummy = criarDummy();

    insere(dummy, 41);
    insere(dummy, 19);
    insere(dummy, 28);
    insere(dummy, 16);
    insere(dummy, 49);
    insere(dummy, 36);
    insere(dummy, 62);
    insere(dummy, 57);
    insere(dummy, 58);
    insere(dummy, 0);

    imprimir(dummy);


    return 0;
}