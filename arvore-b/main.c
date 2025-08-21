#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define b 3

int t = (b + 1) / 2;

typedef struct no{

    int n;
    bool folha;

    // essa alocação dinâmica das chaves serve para que o lixo criado no vetor tenha um valor alto
    // logo, no while insereNaoCheioArvoreB não tem problema -> evita o erro
    // quando o vetor era alocação fixa (int chave[b]) o primeiro era zero, ou seja, 
    // o primeiro elemento do vetor era sempre zero (se k fosse maior que zero)
    // com alocação dinâmica, o primeiro elemento do vetor é algo tipo: 12981648
    // logo todos valores são maiores que esse número/lixo
    int *chave; 
    struct no **filho;

} arvB;

arvB* criarNoRaizInicial()
{
    arvB *novoNo = malloc(sizeof(arvB));

    novoNo->chave = malloc(b * sizeof(int));
    novoNo->filho = malloc((b+1) * sizeof(arvB));

    novoNo->n = 0;
    novoNo->folha = true;

    for (int i = 0; i < b+1; i++)
    {
        novoNo->filho[i] = NULL;
    }


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
    arvB *z = criarNoRaizInicial();

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
    x->chave[i] = y->chave[t-1];
    x->n++;

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


arvB* insereArvoreB(arvB *r, int k)  // função de inserir
{
    // se o nó estiver cheio, cria-se um novo nó (não folha, 0 chaves, primeiro filho como o nó anterior(que estava cheio) e insere o k no novo nó)
    if (r->n == b)          
    {
        arvB *s = criarNoRaizInicial();
        s->folha = false;
        s->filho[0] = r;
        splitChildArvoreB(s, 0);
        insereNaoCheioArvoreB(s, k);

        return s;   // manter a raiz atualizada
    }
    // se não estiver cheio, insere normalmente
    else {
        insereNaoCheioArvoreB(r, k);

        return r;   // manter a raiz atualizada
    }
}




void imprimir_arvore(arvB *arv, int nivel)
{
    if (arv != NULL)
    {
        printf ("\n|   ");
        for (int i = 0; i < arv->n; i++)
        {
            printf ("%d   ", arv->chave[i]);
        }

        printf ("| nivel - %d\n", nivel);

        if (arv->folha == false)
        {
            for (int i = 0; i < arv->n + 1; i++)
            {
                imprimir_arvore(arv->filho[i], nivel + 1);
            }
        }
    }

}


void mergeChildArvoreB (arvB *x, int i) // função merge
{
    // ponteiros aos filhos
    arvB *y = x->filho[i];
    arvB *z = x->filho[i+1];

    // desce a mediana (entre os filhos) do pai
    y->chave[t-1] = x->chave[i];

    y->n++;

    // passando as chaves
    for (int j = 0; j < z->n; j++)
    {
        y->chave[j+t] = z->chave[j];
    }

    // se y não é folha (z tbm não é) -> passa os filhos
    if (y->folha == false)
    {
        for (int j = 0; j < z->n+1; j++)
        {
            y->filho[j+t] = z->filho[j];
        }
    }

    y->n += z->n;
    
    free (z);
    
    // y se juntou ao z 

    // falta ajustar o nó pai em relação ao número que desceu!

    x->n--;

    // removendo a mediana(número entre os filhos que sofreram merge) do pai (já que ela desceu)
    for (int j = i; j < x->n; j++)
    {
        x->chave[j] = x->chave[j+1];
    }

    // ajustando os filhos
    for (int j = i + 1; j < x->n + 1; j++)
    {
        x->filho[j] = x->filho[j+1];
    }

    // escrever (x);
    // escrever (y);
}

// implementando a remoção de um número K
// caso 1: k no nó folha -> remoção direta -> mais simples -> reajuste e x->n-- 

// caso 2: t-1 -> mínimo de chaves no nó -> logo, para se retirar precisa ter no minimo t para substituição
// a - encontrar um predecessor na posição i de k -> k'
//      coloca o k' no lugar do k
//      remove o k' (original)

// b - encontrar um sucessor na posição i+1 de k -> k'
//      coloca k' no lugar do k
//      remove o k' (original)

// c - os dois nós estão com o mínimo (t - 1)
//      merge nos filhos (i, i+1)
//      remove o k

// caso 3: esse caso não remove apenas garante que os filhos tenham pelo menos t chaves 
// a - filho i tem t-1 chaves
//      passa a chave ao filho que tem só t-1 chaves
//      passa ao pai (x) um elemento do filho que tem pelo menos t chaves
//              -> se o filho for da direita: pega o menor
//              -> se o filho for da esquerda: pega o maior

// b - os dois filhos tem apenas t-1 chaves
//      merge nos filhos
//      insere o elemento do pai no nó filho tbm


void remover (arvB *x, int k) // a remoção usará os casos acima + função merge
{
    int i = 0;

    while (i < x->n && k < x->chave[i])
    {
        i++;
    }

    // caso 1 - nó folha
    if (x->folha == true)
    {
        if (x->chave[i] == k)
        {
            for (int j = i; j < x->n - 1; j++)
            {
                x->chave[j] = x->chave[j+1];
            }

            x->n--;

            // escrever(x);

            printf ("\n\nELEMENTO REMOVIDO!!");
        }
        
        else 
        {
            printf ("\n\nELEMENTO NÃO ENCONTRADO!!");
        }

    }

    // caso 2 - nó interno

    else if (i < x->n && x->chave[i] == k)
    {
        // ponteiros
        arvB *y = x->filho[i];      // esquerda

        arvB *z = x->filho[i+1];    // direita

        // a - predecessor
        if (y->n > t - 1)                           // filho a esquerda tem mais que o minimo de chaves
        {
            int posicao = y->n - 1;                 // o maior valor menor que k -> ou seja, pega o maior valor de y (sempre vai ser menor do que k)

            int predecessor = y->chave [posicao];   // arquivando o valor

            x->chave[i] = predecessor;              // copiando o valor para o nó pai

            remover(y, predecessor);                // removendo o número original
        }

        // b - sucessor
        else if (z->n > t - 1)                      // o filho a direita tem mais que o minimo de chaves
        {
            int posicao = 0;                        // o menor valor maior que k -> ou seja, pega o menor valor de z (sempre vai ser maior que k)

            int sucessor = z->chave[posicao];

            x->chave[i] = sucessor;

            remover (z, sucessor);
        }


        // c - merge
        else                                        // os dois estão com o mínimo de chaves (não é possível substituir)
        {
            mergeChildArvoreB(x, i);                // merge - junta os filhos

            remover(y, k);                          // o k (desceu ao filho_merge) precisa ser removido
        }

        // escrever(x);
    }



}





int main ()
{
    arvB *raiz = criarNoRaizInicial();

    raiz = insereArvoreB(raiz, 1);

    raiz = insereArvoreB(raiz, 5);

    raiz = insereArvoreB(raiz, 10);

    raiz = insereArvoreB(raiz, 3);

    raiz = insereArvoreB(raiz, 7);

    raiz = insereArvoreB(raiz, 16);

    raiz = insereArvoreB(raiz, 6);

    raiz = insereArvoreB(raiz, 8);

    raiz = insereArvoreB(raiz, 9);
    
    raiz = insereArvoreB(raiz, 12);
    
    imprimir_arvore(raiz, 0);


    return 0;
}