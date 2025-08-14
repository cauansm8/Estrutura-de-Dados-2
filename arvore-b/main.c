#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define b 3

int t = (b + 1) / 2;



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

    //escrita (novoNo);

    return novoNo;
}


/* void leitura (arvB *r) // desenvolver
{

}

void escrita (arvB *r) // desenvolver
{
    
} */

arvB* buscarArv (arvB *r, int k)
{
    int i = 0;

    // anda (pelo vetor de números) até encontrar um número maior ou igual 
    while (i < r->n && k > r->chave[i])
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
        //leitura (r->filho[i]);
        return buscarArv (r->filho[i], k);
    }
}



// **********************************************
//  TESTAR OS LOOPS PARA ENTENDER MELHOR OS VALORES
// **********************************************
void splitChildArvoreB (arvB *x, int i) // função de split -> recebe o nó pai e o índice do filho que será dividido
{
    // novo nó
    arvB *z = malloc(sizeof(arvB)); 

    // ponteiro ao filho que sofrerá split
    arvB *y = x->filho[i];

    // como as chaves e os filhos serão divididos entre os dois nós, eles são "iguais" no quesito folha ou árvore
    // logo recebem o mesmo "estado"
    z->folha = y->folha;

    // o novo nó terá metade das chaves de y, pois eles serão divididos 
    z->n = t - 1;

    // passando os ultimos t-1 chaves ao novo nó (z)
    for (int j = 0; j < t - 1; j++)
    {
        z->chave[j] = y->chave[t + j]; // ********************************* DÚVIDA -> a mediana está sendo passada ao pai? ***********************
    }

    // se o nó cheio tem filhos, é necessário passar esses filhos ao novo nó (z)
    if (y->folha == false)
    {
        // como tem b+1 filhos, passam-se os ultimos t filhos 
        for (int j = 0; j < t; j++)
        {
            z->filho[j] = y->filho[t + j];
        }
    }

    // ajusta a quantidade de chaves no nó que anteriormente estava cheio para t-1 (metade) 
    y->n = t-1;

    // passa os filhos a direita de i para a direta
    for (int j = x->n + 1; j >= i + 1; j--)
    {
        x->filho[j+1] = x->filho[j];
    }

    // insere o novo filho na posição a direita de i, ou seja, i + 1
    x->filho[i+1] = z;

    // abrindo espaço para a mediana do y (quando estava cheio!)
    for (int j = x->n; j >= i; j--)
    {
        x->chave[j+1] = x->chave[j];    
    }
    
    // inserindo a mediana e atualizando o valor de n
    x->chave[i] = y->chave[t];
    x->n ++;

    //escrever(x);
    //escrever(y);
    //escrever(z);

}

void insereNaoCheioArvoreB(arvB *x, int k)
{
    // contador
    int i = x->n;
    
    // se o nó for folha -> pode inserir direto
    if (x->folha == true)
    {
        // loop para que os valores maiores que o k "pulem" para direita no vetor -> ordenação
        while (i >= 0 && k < x->chave[i])
        {
            x->chave[i+1] = x->chave[i];
            i--;
        }

        // inserção
        x->chave[i+1] = k;

        // indicando que há mais um número
        x->n++;

        // escrevendo no disco
        //escrever(x);


    }
    
    // se o nó não é folha -> busca o filho
    else {
        
        // encontrando a posição que o número deveria ser inserido se fosse folha 
        // ou seja, estamos procurando o filho que receberá k
        while (i >= 0 && k < x->chave[i])
        {
            i--;
        }

        // ajuste
        i++;

        // le o nó que está no disco
        //leitura (x->filho[i]);

        // verifica se o nó filho está cheio
        if (x->filho[i]->n == b)
        {
            // se estiver, faz o split na posição i
            splitChildArvoreB(x, i);

            // verifica se o número k é maior que o número que "subiu" com o split
            // se k for maior, faz o reajuste (i++) 
            if (k > x->chave[i])
            {
                i++;
            }
        }

        // chama a função de inserção no nó filho
        // lembrando que: só pode inserir em nó folha!
        insereNaoCheioArvoreB(x->filho[i], k);

    }
}


void insereArvoreB(arvB *r, int k)  // função de inserir
{
    // se o nó estiver cheio, cria-se um novo nó (não folha, 0 chaves, primeiro filho como o nó anterior(que estava cheio) e insere o k no novo nó)
    if (r->n == b)          
    {
        arvB *s = malloc(sizeof(arvB));
        s->folha = false;
        s->n = 0;
        s->filho[0] = r;
        splitChildArvoreB(s, 0);
        insereNaoCheioArvoreB(s, k);
    }
    // se não estiver cheio, insere normalmente
    else {
        insereNaoCheioArvoreB(r, k);
    }
}




void imprimir_arvore(arvB *arv)
{
    if (arv != NULL)
    {
        printf ("\n|   ");
        for (int i = 0; i < arv->n; i++)
        {
            printf ("%d   ", arv->chave[i]);
        }

        printf ("|\n");

        if (arv->folha == false)
        {
            for (int i = 0; i < arv->n + 1; i++)
            {
                imprimir_arvore(arv->filho[i]);
            }
        }
    }


}


int main ()
{
    arvB *raiz = criarNoRaizInicial();

    insereArvoreB(raiz, 1);

    insereArvoreB(raiz, 5);

    insereArvoreB(raiz, 10);
    
    imprimir_arvore(raiz);


    return 0;
}