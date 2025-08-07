#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define b 5

typedef struct no{

    int n;
    bool folha;
    int chave[b];
    struct no *filho[b+1];

} arvB;

arvB* criarNoRaizInicial()
{
    arvB *novoNo = malloc(sizeof(arvB));

    novoNo->n = 0;
    novoNo->folha = true;

    escrita (novoNo);

    return novoNo;
}


void leitura (arvB *r) // desenvolver
{

}

void escrita (arvB *r) // desenvolver
{
    
}

arvB* buscarArv (arvB *r, int k)
{
    int i = 0;

    // anda (pelo vetor de números) até encontrar um número maior ou igual 
    while (i <= r->n && k > r->chave[i])
    {
        i++;
    }

    // verifica se o número procurado é igual ao que parou no loop
    if (i < r->n && k == r->chave[i])
    {
        // se for o mesmo número, significa que encontramos o nó
        printf ("\nNumero encontrado!!!");
        return r;
    }


    // se não encontrou, verificamos se o nó é folha (não tem filhos)
        // se não tiver filhos, significa que o número não está na árvore
    if (r->folha == true)
    {
        printf ("\nNumero nao encontrado!!! - retornando null");
        return NULL;
    }

    // se não é folha (tem filhos), continua a busca pelo nó filho 
    else
    {
        leitura (r->filho[i]);
        return buscarArv (r->filho[i], k);
    }
}


int main ()
{
    arvB *raiz = criarNoRaizInicial();

    printf ("\n%d", raiz->n);
    printf ("\n%d", raiz->folha);
    


    return 0;
}