#include <limits.h>

typedef struct
{
    int prioridade;
    int vertice;
}Item;

typedef struct
{
    Item *v; 
    int *indice; 
    int n; 
    int tamanho; 
}FP;

void troca(Item *a,Item *b)
{
    Item temp = *a;
    *a = *b;
    *b = temp;
}

FP* criar_FP(int n)
{
    FP *h = malloc(sizeof(FP));

    h->v = malloc(n*sizeof(Item));

    h->indice = malloc(n*sizeof(int));

    h->n = n;

    h->tamanho=0;
    
    for(int i = 0; i < n; i++)
    {
        h->indice[i] = -1;
    }
    return h;
}

int vazia_FP(FP *h)
{
    if (h->tamanho == 0)
    {
        return 1;
    }

    return 0;
}

int prioridade_FP(FP *h,int v)
{
    int i = h->indice[v]; 
    
    if (i == -1)
    {
        return INT_MAX; 
    }
    
    return h->v[i].prioridade; 
}
void sobe_heap(FP *h,int i)
{
    while (i > 0)
    {
        int pai = (i - 1) / 2;

        if(h->v[pai].prioridade <= h->v[i].prioridade)
        {
            break;
        }
        
        h->indice[h->v[pai].vertice] = i;
        
        h->indice[h->v[i].vertice] = pai;
        
        troca(&h->v[pai],&h->v[i]);

        i = pai;
    }
}

void desce_heap(FP *h,int i)
{
    int menor = i;

    int esq = 2 * i + 1;
    
    int dir = 2 * i + 2;
    
    if (esq < h->tamanho && h->v[esq].prioridade < h->v[menor].prioridade)
    {
        menor = esq;
    }
    
    if (dir < h-> tamanho && h->v[dir].prioridade < h->v[menor].prioridade)
    {
        menor = dir;
    }
    
    if (menor != i)
    {
        h->indice[h->v[i].vertice] = menor;

        h->indice[h->v[menor].vertice] = i;
        
        troca(&h->v[i],&h->v[menor]);
        
        desce_heap(h, menor);
    }
}

void insere_FP(FP *h, int v, int prioridade)
{
    if (h->tamanho == h->n)
    {
        printf("\nHeap esta cheio!\n");
        return;
    }

    int i = h->tamanho++;
    
    h->v[i].vertice = v;
    
    h->v[i].prioridade = prioridade;
    
    h->indice[v] = i;
    
    sobe_heap(h, i);
}

int extrai_minimo_FP(FP *h)
{
    if (vazia_FP(h))
    {
        printf("Heap vazio!\n");

        return 0;
    }

    int vertice_min = h->v[0].vertice;

    h->indice[vertice_min] = -1;
    
    h->tamanho--;

    if (h->tamanho > 0)
    {
        h->v[0] = h->v[h->tamanho];
        h->indice[h->v[0].vertice] = 0;
        desce_heap(h, 0);
    }
    
    return vertice_min;
}

void diminuiprioridade_FP(FP *h,int v,int nova_prioridade)
{
    int i= h-> indice[v];
    
    if (i == -1)
    {
        return;
    }
    
    if (nova_prioridade >= h->v[i].prioridade)
    {
        return; 
    }
    
    h->v[i].prioridade = nova_prioridade;
    
    sobe_heap(h, i);
}
