#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "../estruturas/grafo_lista.h"

GrafoLista* criarGrafoLista(int n,Jogador* jogadores)
{
    GrafoLista* g = malloc(sizeof(GrafoLista));
    g->numVertices = n;
    g->jogadores = jogadores;
    g->lista = malloc(n * sizeof(ListaAdj));
    for(int i=0;i<n;i++)
    {
        g->lista[i].cabeca = NULL;
    }
    return g;
}

void adicionarArestaLista(GrafoLista* g,int u,int v,float peso)
{
    //Grafo não orientado
    //add aresta de u para v
    No* new_no = malloc(sizeof(No));
    new_no->destino = v;
    new_no->peso = peso;
    new_no->prox = g->lista[u].cabeca;
    g->lista[u].cabeca = new_no;
    
    //add aresta de v para u
    new_no = malloc(sizeof(No));
    new_no->destino = u;
    new_no->peso = peso;
    new_no->prox = g->lista[v].cabeca;
    g->lista[v].cabeca = new_no;
}

void liberarGrafoLista(GrafoLista* g)
{
    for(int i=0;i<g->numVertices;i++)
    {
        No* atual = g->lista[i].cabeca;
        //Vai percorrendo a lista e liberando os nó
        while(atual)
        {
            No* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->lista);
    free(g);
}
//começa a DFS a partir do vértice da origem
void dfsLista(GrafoLista* g, int inicio)
{
    printf("\nDFS (Lista) iniciando em %s\n", g->jogadores[inicio].nome);

    int* visitado = calloc(g->numVertices, sizeof(int));
    dfsRecursivoLista(g, inicio, visitado, 0);

    printf("FIM\n");
    free(visitado);
}

void dfsRecursivoLista(GrafoLista* g, int v, int* visitado, int nivel) // utilizamos o nivel para deixar mais legivel
{
    visitado[v] = 1;

    // indentação visual
    for (int i = 0; i < nivel; i++)
        printf("   ");

    printf("|-> %s (%s)\n", g->jogadores[v].nome, g->jogadores[v].posicao);

    No* adj = g->lista[v].cabeca;

    while (adj)
    {
        if (!visitado[adj->destino])
        {
            dfsRecursivoLista(g, adj->destino, visitado, nivel + 1);
        }
        adj = adj->prox;
    }
}

//Percorre o grafo e imprime a BFS
// Função recursiva para imprimir a árvore BFS
void imprimirRecursivoLista(GrafoLista* g, int* pai, int vertice_atual, int nivel)
{
    // imprime espaços para representar o nível da árvore
    for(int i = 0; i < nivel; i++)
        printf(" ");

    // imprime o jogador
    printf("|-> %s (%s)\n", g->jogadores[vertice_atual].nome,
                           g->jogadores[vertice_atual].posicao);

    // percorre todos os vértices e imprime quem tem o pai igual ao vértice atual
    for(int i = 0; i < g->numVertices; i++)
    {
        if(pai[i] == vertice_atual)
            imprimirRecursivoLista(g, pai, i, nivel + 2);
    }
}

void bfsLista(GrafoLista* g, int s)
{
    printf("\nBFS (Lista) iniciando em %s\n", g->jogadores[s].nome);

    //inicializa as estruturas
    int* visitado = calloc(g->numVertices, sizeof(int));
    int* fila = malloc(g->numVertices * sizeof(int));
    int* pai = malloc(g->numVertices * sizeof(int));   // <-- novo: vetor de pais
    int frente = 0, tras = 0;

    // inicializa pais com -1
    for(int i = 0; i < g->numVertices; i++)
        pai[i] = -1;

    visitado[s] = 1;
    fila[tras++] = s;

    //Enquanto a fila não estiver vazia ele continua
    while(frente < tras)
    {
        //Tira da fila
        int v = fila[frente++];

        No* adj = g->lista[v].cabeca;
        while(adj)
        {
            //Se ele ainda não foi visitado, marca como visitado e coloca na fila
            if(!visitado[adj->destino])
            {
                visitado[adj->destino] = 1;
                pai[adj->destino] = v;        // <-- registra pai para a árvore BFS
                fila[tras++] = adj->destino;
            }
            adj = adj->prox;
        }
    }

    // Agora imprimimos a árvore BFS recursivamente
    imprimirRecursivoLista(g, pai, s, 0);

    printf("FIM\n");

    free(visitado);
    free(fila);
    free(pai);
}



//Funções do heap para usa nos algoritmos dijktra e Prim
MinHeapLista* criarHeapLista(int capacidade)
{
    MinHeapLista* h = malloc(sizeof(MinHeapLista));
    //array que guarda os nós do heap
    h->array = malloc(capacidade * sizeof(HeapNoLista));
    h->tamanho = 0; //marca o número de elementos contidos no heap
    h->capacidade = capacidade;
    return h;
}

void trocarLista(HeapNoLista* a,HeapNoLista* b)
{
    HeapNoLista temp = *a;
    *a = *b;
    *b = temp;
}
//Função que mantém a propriedade do heap ao inserir um novo nó
void heapifyUpLista(MinHeapLista* h,int id)
{
    while (id > 0)
    {
        int pai = (id-1)/2;
        //Comapra o elemento com seu pai se o filho tem menor distância troca
        if(h->array[id].dist<h->array[pai].dist)
        {
            trocarLista(&h->array[id], &h->array[pai]);
            id = pai;
        } 
        else
        {
            break;
        }
    }
}
//Função que mantém o heap depois de extrair o nó com menor distância
void heapifyDownLista(MinHeapLista* h, int id)
{
    int menor = id;
    int esq = 2*id+1;
    int dir = 2*id+2;
    //Cmp com os filhos e troca com o menor
    if(esq<h->tamanho && h->array[esq].dist<h->array[menor].dist)
    {
        menor = esq;
    }
    if(dir<h->tamanho && h->array[dir].dist<h->array[menor].dist)
    {
        menor = dir;
    }
    if(menor!=id)
    {
        //Faz a troca e continua o processo de forma recusiva
        trocarLista(&h->array[id],&h->array[menor]);
        heapifyDownLista(h, menor);
    }
}
//Insere um novo vértice no heap
void inserirHeapLista(MinHeapLista* h,int v,float d)
{
    h->array[h->tamanho].vertice = v;
    h->array[h->tamanho].dist = d;
    heapifyUpLista(h, h->tamanho);
    h->tamanho++;
}
//Extrai o nó com menor distância no heap
HeapNoLista extrairMinLista(MinHeapLista* h)
{
    HeapNoLista min = h->array[0];
    h->array[0] = h->array[h->tamanho - 1];
    h->tamanho--;
    //Passa a raiz para "baixo" no heap para mantê-lo
    heapifyDownLista(h,0);
    return min;
}

// Impressao recursiva da árvore do Dijkstra
void imprimirRecursivoDijkstraLista(GrafoLista* g, int* pai, int vertice_atual, int nivel)
{
    // identação por nível
    for(int i = 0; i < nivel; i++)
        printf(" ");

    printf("|-> %s (%s)\n",
        g->jogadores[vertice_atual].nome,
        g->jogadores[vertice_atual].posicao);

    // percorre todos os vértices procurando filhos
    for(int i = 0; i < g->numVertices; i++)
    {
        if(pai[i] == vertice_atual)
            imprimirRecursivoDijkstraLista(g, pai, i, nivel + 2);
    }
}


// Djikstra com estruturas estaticas (para simplificar)
void dijkstraLista(GrafoLista* g,int inicio,int fim)
{
    printf("\nDijkstra (Lista) de %s ate %s\n",
        g->jogadores[inicio].nome,
        g->jogadores[fim].nome);

    float* dist = malloc(g->numVertices * sizeof(float));
    int* pai = malloc(g->numVertices * sizeof(int));
    int* visitado = calloc(g->numVertices, sizeof(int));

    //Inicializa as distâncias e o vetor pai
    for(int i = 0; i < g->numVertices; i++)
    {
        dist[i] = FLT_MAX;
        pai[i] = -1;
    }

    //Distância do nó inicial para ele msm é 0
    dist[inicio] = 0.0;

    MinHeapLista* h = criarHeapLista(g->numVertices * 10);
    inserirHeapLista(h, inicio, 0.0);

    while(h->tamanho > 0)
    {
        //Pega o nó com menor distância
        HeapNoLista atual = extrairMinLista(h);
        int u = atual.vertice;

        //Se já foi visitado ele pula para o proximo da fila
        if(visitado[u]) 
            continue;

        visitado[u] = 1;

        No* adj = g->lista[u].cabeca;

        // relaxamento
        while(adj)
        {
            //cmp a dist (do menor peso) + o peso do atual com a prioridade atual do destino
            if(!visitado[adj->destino] && dist[u] + adj->peso < dist[adj->destino])
            {
                //Se for menor att a prioridade do heap e define o pai
                dist[adj->destino] = dist[u] + adj->peso;
                pai[adj->destino] = u;
                inserirHeapLista(h, adj->destino, dist[adj->destino]);
            }
            adj = adj->prox;
        }
    }

    // se não há caminho
    if(dist[fim] == FLT_MAX)
    {
        printf("Nao ha caminho!\n");
        return;
    }

    // Impressão total da ÁRVORE de Dijkstra
    imprimirRecursivoDijkstraLista(g, pai, inicio, 0);

    free(dist);
    free(pai);
    free(visitado);
    free(h->array);
    free(h);
}

//Algoritmo de Prim para árvore geradora mínima (MST) em estrutura estatica (para simplificar)
void primLista(GrafoLista* g)
{
    printf("\nArvore Geradora Minima - Prim (Lista)\n");
    //Inicialização
    int* incluidoMST = calloc(g->numVertices, sizeof(int));
    float* chave = malloc(g->numVertices * sizeof(float));
    int* pai = malloc(g->numVertices * sizeof(int));
    //inicializa o vetor pai e inicializa as distancias dos vértices como MAX
    for(int i = 0; i < g->numVertices; i++)
    {
        chave[i] = FLT_MAX;
        pai[i] = -1;
    }
    chave[0] = 0.0;
    
    MinHeapLista* h = criarHeapLista(g->numVertices*10);
    inserirHeapLista(h,0,0.0);
    
    float pesoTotal = 0.0;
    
    while(h->tamanho>0)
    {
        //tira da fila o v com menor peso
        HeapNoLista atual = extrairMinLista(h);
        int u = atual.vertice;
        
        if(incluidoMST[u])
        {
            continue;
        }
        incluidoMST[u] = 1;
        
        if(pai[u]!=-1)
        {
            printf("%-25s -- %.2f -- %25s\n", g->jogadores[pai[u]].nome, chave[u], g->jogadores[u].nome);
            pesoTotal += chave[u];
        }
        
        No* adj = g->lista[u].cabeca;
        while(adj)
        {
            int v = adj->destino;
            float peso = adj->peso;
            
            if(!incluidoMST[v] && peso<chave[v])
            {
                chave[v] = peso;
                pai[v] = u;
                inserirHeapLista(h,v,chave[v]);
            }
            adj = adj->prox;
        }
    }
    
    printf("Peso total da MST: %.2f\n",pesoTotal);
    
    free(incluidoMST);
    free(chave);
    free(pai);
    free(h->array);
    free(h);
}
//Acha e imprime os componentes conexos do grafo
void componentesConexosLista(GrafoLista* g)
{
    printf("\nComponentes Conexos (Lista)\n");
    
    int* visitado = calloc(g->numVertices, sizeof(int));
    int numComponentes=0;
    //Percorre todos os vértices do grafo
    for (int i=0;i<g->numVertices;i++)
    {
        //Se não foi visitado começa busca a partir dele
        if(!visitado[i])
        {
            numComponentes++;
            printf("Componente %d: ",numComponentes);
            //Cria fila para usar na busca
            int* fila = malloc(g->numVertices * sizeof(int));
            int frente = 0, tras = 0;
            
            visitado[i] = 1;
            fila[tras++] = i;
            //Enquanto a fila não estiver vazia ele a percorre
            while(frente < tras)
            {
                int v = fila[frente++];
                printf("%s - ", g->jogadores[v].nome);
                
                No* adj = g->lista[v].cabeca;
                while(adj)
                {
                    //Se o vizinho não foi visitado marca e coloca na fila
                    if(!visitado[adj->destino])
                    {
                        visitado[adj->destino] = 1;
                        fila[tras++] = adj->destino;
                    }
                    adj = adj->prox;
                }
            }
            printf("\n");
            free(fila);
        }
    }
    //Imprime o número de componentes conexos
    printf("Total de componentes: %d\n", numComponentes);
    free(visitado);
}

//Verifica se existe caminho entre dois vértices
int existeCaminhoLista(GrafoLista* g, int inicio, int fim)
{
    //Se os dois vértices são iguais já existe caminho
    if (inicio == fim)
    {
        return 1;
    }
    //Inicializa
    int* visitado = calloc(g->numVertices, sizeof(int));
    int* fila = malloc(g->numVertices * sizeof(int));
    int frente=0, tras=0;
    
    visitado[inicio] = 1;
    fila[tras++] = inicio;
    
    while(frente < tras)
    {
        //Tira da fila para visitar seus vizinhos
        int v=fila[frente++];
        
        No* adj=g->lista[v].cabeca;
        while(adj)
        {
            //Se encontrar o vértice fim retorna 1
            if(adj->destino==fim)
            {
                free(visitado);
                free(fila);
                return 1;
            }
            //Se não foi visitado marca e coloca na fila
            if(!visitado[adj->destino])
            {
                visitado[adj->destino]=1;
                fila[tras++]=adj->destino;
            }
            adj=adj->prox;
        }
    }
    free(visitado);
    free(fila);
    return 0;
}
//Recomenda o melhor passe para um jogador baseado no menor peso (maior entrosamento)
void recomendarPasseLista(GrafoLista* g, int jogador)
{
    printf("\nRecomendacao de Passe (Lista) para %s (%s)\n",g->jogadores[jogador].nome, g->jogadores[jogador].posicao);
    
    float melhorPeso=FLT_MAX;
    int melhor = -1;
    
    No* adj=g->lista[jogador].cabeca;
    while(adj)
    {   
        //Procura o jogador vizinho com menor peso (maior entrosamento)
        if(adj->peso < melhorPeso)
        {
            melhorPeso = adj->peso;
            melhor = adj->destino;
        }
        adj = adj->prox;
    }
    //Imprime o melhor passe encontrado
    if (melhor != -1)
    {
        printf("Melhor passe: %s (%s) (entrosamento: %.2f)\n",g->jogadores[melhor].nome, g->jogadores[jogador].posicao, 1.0 / melhorPeso);
    }
    //Se não houver vizinhos
    else
    {
        printf("Nenhum vizinho disponivel!\n");
    }
}

void imprimirGrafoLista(GrafoLista* g)
{
    for(int i=0;i<g->numVertices;i++)
    {
        printf("%02d:", g->jogadores[i].id);
        No* adj = g->lista[i].cabeca;
        while(adj)
        {
            printf(" -> (%d, %.2f)", g->jogadores[adj->destino].id, adj->peso);
            adj = adj->prox;
        }
        printf("\n");
    }
}