#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "estruturas/jogador.h"
#include "funcoes/grafo_lista.c"
#include "funcoes/grafo_matriz.c"

#define MAX_JOGADORES 311 //Numero de jogadores nos arquivos

int lerArquivo(const char* nome, char dados[][100], int maxLinhas)
{
    int i; // contador de linhas lidas
    FILE* arquivo = fopen(nome, "r");
    // Verifica se o arquivo foi aberto corretamente
    if (!arquivo)
    {
        printf("Erro ao abrir %s\n", nome);
        return 0;
    }

    for(i = 0; i < maxLinhas && fgets(dados[i], 100, arquivo); i++)
    {
        dados[i][strcspn(dados[i], "\n")] = 0; // remove o /n dos dados 
    }

    fclose(arquivo);
    return i;
}

// calcula o peso da aresta baseado no entrosamento
float calcularPeso(Jogador* j1, Jogador* j2)
{
    int entrosamento = 1; // o valor comeca com 1 para evitar dividir por 0

    // o entrosamento aumenta a cada atribuito igual entre os jogadores
    if(strcmp(j1->time, j2->time) == 0)
    {
        entrosamento++;
    }
    if(strcmp(j1->nacionalidade, j2->nacionalidade) == 0)
    {
        entrosamento++;
    }

    // Como o peso eh inversamente proporcional ao entrosamento,
    // dividdimos 1 pelo valor do entrosamento
    return 1.0 / entrosamento;
}

void conectarPosicoes(GrafoLista* grafoLista, GrafoMatriz* grafoMatriz, Jogador* jogadores)
{

    /*
        0 - gol     11 - gol2
        1 - le      12 - le2
        2 - ze      13 - ze2
        3 - zd      14 - zd2
        4 - ld      15 - ld2
        5 - me      16 - me2
        6 - mc      17 - mc2
        7 - md      18 - md2
        8 - pe      19 - pe2
        9 - ca      20 - ca2
        10 - pd     21 - pd2
    */
    float peso;
    //gol
    peso = calcularPeso(&jogadores[0], &jogadores[2]);
    adicionarArestaLista(grafoLista, 0, 2, peso);
    adicionarArestaMatriz(grafoMatriz, 0, 2, peso);

    peso = calcularPeso(&jogadores[0], &jogadores[3]);
    adicionarArestaLista(grafoLista, 0, 3, peso);
    adicionarArestaMatriz(grafoMatriz, 0, 3, peso);

    //le
    peso = calcularPeso(&jogadores[1], &jogadores[2]);
    adicionarArestaLista(grafoLista, 1, 2, peso);
    adicionarArestaMatriz(grafoMatriz, 1, 2, peso);

    peso = calcularPeso(&jogadores[1], &jogadores[5]);
    adicionarArestaLista(grafoLista, 1, 5, peso);
    adicionarArestaMatriz(grafoMatriz, 1, 5, peso);

    //ze
    peso = calcularPeso(&jogadores[2], &jogadores[3]);
    adicionarArestaLista(grafoLista, 2, 3, peso);
    adicionarArestaMatriz(grafoMatriz, 2, 3, peso);

    peso = calcularPeso(&jogadores[2], &jogadores[5]);
    adicionarArestaLista(grafoLista, 2, 5, peso);
    adicionarArestaMatriz(grafoMatriz, 2, 5, peso);

    //zd
    peso = calcularPeso(&jogadores[3], &jogadores[4]);
    adicionarArestaLista(grafoLista, 3, 4, peso);
    adicionarArestaMatriz(grafoMatriz, 3, 4, peso);

    peso = calcularPeso(&jogadores[3], &jogadores[7]);
    adicionarArestaLista(grafoLista, 3, 7, peso);
    adicionarArestaMatriz(grafoMatriz, 3, 7, peso);

    //ld
    peso = calcularPeso(&jogadores[4], &jogadores[7]);
    adicionarArestaLista(grafoLista, 4, 7, peso);
    adicionarArestaMatriz(grafoMatriz, 4, 7, peso);

    //me
    peso = calcularPeso(&jogadores[5], &jogadores[6]);
    adicionarArestaLista(grafoLista, 5, 6, peso);
    adicionarArestaMatriz(grafoMatriz, 5, 6, peso);

    peso = calcularPeso(&jogadores[5], &jogadores[8]);
    adicionarArestaLista(grafoLista, 5, 8, peso);
    adicionarArestaMatriz(grafoMatriz, 5, 8, peso);

    //mc
    peso = calcularPeso(&jogadores[6], &jogadores[7]);
    adicionarArestaLista(grafoLista, 6, 7, peso);
    adicionarArestaMatriz(grafoMatriz, 6, 7, peso);

    peso = calcularPeso(&jogadores[6], &jogadores[9]);
    adicionarArestaLista(grafoLista, 6, 9, peso);
    adicionarArestaMatriz(grafoMatriz, 6, 9, peso);

    //md
    peso = calcularPeso(&jogadores[7], &jogadores[10]);
    adicionarArestaLista(grafoLista, 7, 10, peso);
    adicionarArestaMatriz(grafoMatriz, 7, 10, peso);

    //pe
    peso = calcularPeso(&jogadores[8], &jogadores[9]);
    adicionarArestaLista(grafoLista, 8, 9, peso);
    adicionarArestaMatriz(grafoMatriz, 8, 9, peso);

    //ca

    //pd
    peso = calcularPeso(&jogadores[10], &jogadores[9]);
    adicionarArestaLista(grafoLista, 10, 9, peso);
    adicionarArestaMatriz(grafoMatriz, 10, 9, peso);

    // gol2 (11)
    peso = calcularPeso(&jogadores[11], &jogadores[13]);
    adicionarArestaLista(grafoLista, 11, 13, peso);
    adicionarArestaMatriz(grafoMatriz, 11, 13, peso);

    peso = calcularPeso(&jogadores[11], &jogadores[14]);
    adicionarArestaLista(grafoLista, 11, 14, peso);
    adicionarArestaMatriz(grafoMatriz, 11, 14, peso);

    // le2 (12)
    peso = calcularPeso(&jogadores[12], &jogadores[13]);
    adicionarArestaLista(grafoLista, 12, 13, peso);
    adicionarArestaMatriz(grafoMatriz, 12, 13, peso);

    peso = calcularPeso(&jogadores[12], &jogadores[16]);
    adicionarArestaLista(grafoLista, 12, 16, peso);
    adicionarArestaMatriz(grafoMatriz, 12, 16, peso);

    // ze2 (13)
    peso = calcularPeso(&jogadores[13], &jogadores[14]);
    adicionarArestaLista(grafoLista, 13, 14, peso);
    adicionarArestaMatriz(grafoMatriz, 13, 14, peso);

    peso = calcularPeso(&jogadores[13], &jogadores[16]);
    adicionarArestaLista(grafoLista, 13, 16, peso);
    adicionarArestaMatriz(grafoMatriz, 13, 16, peso);

    // zd2 (14)
    peso = calcularPeso(&jogadores[14], &jogadores[15]);
    adicionarArestaLista(grafoLista, 14, 15, peso);
    adicionarArestaMatriz(grafoMatriz, 14, 15, peso);

    peso = calcularPeso(&jogadores[14], &jogadores[18]);
    adicionarArestaLista(grafoLista, 14, 18, peso);
    adicionarArestaMatriz(grafoMatriz, 14, 18, peso);

    // ld2 (15)
    peso = calcularPeso(&jogadores[15], &jogadores[18]);
    adicionarArestaLista(grafoLista, 15, 18, peso);
    adicionarArestaMatriz(grafoMatriz, 15, 18, peso);

    // me2 (16)
    peso = calcularPeso(&jogadores[16], &jogadores[17]);
    adicionarArestaLista(grafoLista, 16, 17, peso);
    adicionarArestaMatriz(grafoMatriz, 16, 17, peso);

    peso = calcularPeso(&jogadores[16], &jogadores[19]);
    adicionarArestaLista(grafoLista, 16, 19, peso);
    adicionarArestaMatriz(grafoMatriz, 16, 19, peso);

    // mc2 (17)
    peso = calcularPeso(&jogadores[17], &jogadores[18]);
    adicionarArestaLista(grafoLista, 17, 18, peso);
    adicionarArestaMatriz(grafoMatriz, 17, 18, peso);

    peso = calcularPeso(&jogadores[17], &jogadores[20]);
    adicionarArestaLista(grafoLista, 17, 20, peso);
    adicionarArestaMatriz(grafoMatriz, 17, 20, peso);

    // md2 (18)
    peso = calcularPeso(&jogadores[18], &jogadores[21]);
    adicionarArestaLista(grafoLista, 18, 21, peso);
    adicionarArestaMatriz(grafoMatriz, 18, 21, peso);

    // pe2 (19)
    peso = calcularPeso(&jogadores[19], &jogadores[20]);
    adicionarArestaLista(grafoLista, 19, 20, peso);
    adicionarArestaMatriz(grafoMatriz, 19, 20, peso);

    // ca2 (20)
    // (não tem ligação além da com PD2)

    // pd2 (21)
    peso = calcularPeso(&jogadores[21], &jogadores[20]);
    adicionarArestaLista(grafoLista, 21, 20, peso);
    adicionarArestaMatriz(grafoMatriz, 21, 20, peso);


}

int main()
{
    // seed para aleatorizar os jogadores
    srand(time(NULL));

    printf("+-----------------------------------------------+\n");
    printf("|   SISTEMA DE GRAFOS DE JOGADORES DE FUTEBOL   |\n");
    printf("+-----------------------------------------------+\n");

    char nomes[MAX_JOGADORES][100];
    char posicoes[MAX_JOGADORES][100];
    char times[MAX_JOGADORES][100];
    char nacionalidades[MAX_JOGADORES][100];

    // leitura dos arquivos
    int n1 = lerArquivo("..\\dados/nomes.txt", nomes, MAX_JOGADORES);
    int n2 = lerArquivo("..\\dados/posicoes.txt", posicoes, MAX_JOGADORES);
    int n3 = lerArquivo("..\\dados/times.txt", times, MAX_JOGADORES);
    int n4 = lerArquivo("..\\dados/nacionalidade.txt", nacionalidades, MAX_JOGADORES);

    // verifica se foi possivel abrir os arquivos
    if(n1 == 0 || n2 == 0 || n3 == 0 || n4 == 0)
    {
        printf("Erro ao abrir algum dos arquivos!\n");
        return 1;
    }

    // Sortear 22 jogadores sem repetição
    int indices[MAX_JOGADORES];

    for (int i = 0; i < 22; i++) {
        indices[i] = rand() % MAX_JOGADORES ;  // pode repetir jogador
    }

    Jogador* jogadores = (Jogador*)malloc(22 * sizeof(Jogador));

    printf("+-----------------------------------------------+\n");
    printf("|        ESCALACAO GERADA AUTOMATICAMENTE       |\n");
    printf("+-----------------------------------------------+\n");
    printf("+-----------------------------------------------+\n");
    printf("|                   TITULARES                   |\n");
    printf("+-----------------------------------------------+\n");
    for(int i = 0; i < 11; i++)
    {
        int idx = indices[i];
        jogadores[i].id = i;
        strcpy(jogadores[i].nome, nomes[idx]);
        strcpy(jogadores[i].posicao, posicoes[idx]);
        strcpy(jogadores[i].time, times[idx]);
        strcpy(jogadores[i].nacionalidade, nacionalidades[idx]);
        printf("%02d. %s - %s (%s, %s)\n", i+1, jogadores[i].nome, jogadores[i].posicao, jogadores[i].time, jogadores[i].nacionalidade);
    }

    printf("\n+-----------------------------------------------+\n");
    printf("|                    RESERVAS                   |\n");
    printf("+-----------------------------------------------+\n");
    for (int i = 11; i < 22; i++)
    {
        int idx = indices[i];
        jogadores[i].id = i;
        strcpy(jogadores[i].nome, nomes[idx]);
        strcpy(jogadores[i].posicao, posicoes[idx]);
        strcpy(jogadores[i].time, times[idx]);
        strcpy(jogadores[i].nacionalidade, nacionalidades[idx]);
        printf("%02d. %s - %s (%s, %s)\n", i-10, jogadores[i].nome, jogadores[i].posicao,jogadores[i].time, jogadores[i].nacionalidade);
    }

    printf("\n+-----------------------------------------------+\n");
    printf("|                CRIANDO OS GRAFOS              |\n");
    printf("+-----------------------------------------------+\n");

    GrafoLista* gLista = criarGrafoLista(22, jogadores);
    GrafoMatriz* gMatriz = criarGrafoMatriz(22, jogadores);

    conectarPosicoes(gLista, gMatriz, jogadores);

    printf("+-----------------------------------------------+\n");
    printf("|                 GRAFO - LISTA                 |\n");
    printf("+-----------------------------------------------+\n");
    
    imprimirGrafoLista(gLista);

    printf("\n+-----------------------------------------------+\n");
    printf("|                GRAFO - MATRIZ                 |\n");
    printf("+-----------------------------------------------+");
    
    imprimirGrafoMatriz(gMatriz);

    printf("\n+-----------------------------------------------+\n");
    printf("|            EXECUTANDO OS ALGORITMOS           |\n");
    printf("+-----------------------------------------------+\n");

    // DFS
    dfsLista(gLista, 0);
    dfsMatriz(gMatriz, 0);

    // BFS
    bfsLista(gLista, 0);
    bfsMatriz(gMatriz, 0);

    // Dijkstra
    dijkstraLista(gLista, 0, 10);
    dijkstraMatriz(gMatriz, 0, 10);

    // Prim
    primLista(gLista);
    primMatriz(gMatriz);

    // Componentes Conexos
    componentesConexosLista(gLista);
    componentesConexosMatriz(gMatriz);

    // Existe Caminho
    printf("\n+-----------------------------------------------+\n");
    printf("|              EXISTE CAMINHO - LISTA           |\n");
    printf("+-----------------------------------------------+\n");
    int existe = existeCaminhoLista(gLista, 0, 21);
    printf("De %s ate %s: %s\n", jogadores[0].nome, jogadores[21].nome, existe ? "SIM" : "NAO");

    printf("\n+-----------------------------------------------+\n");
    printf("|             EXISTE CAMINHO - MATRIZ           |\n");
    printf("+-----------------------------------------------+\n");
    existe = existeCaminhoMatriz(gMatriz, 0, 21);
    printf("De %s ate %s: %s\n", jogadores[0].nome, jogadores[2].nome, existe ? "SIM" : "NAO");

    // Recomendação de Passe
    recomendarPasseLista(gLista, 1);
    recomendarPasseMatriz(gMatriz, 1);

    printf("\n+-----------------------------------------------+\n");
    printf("|              FINALIZANDO SISTEMA              |\n");
    printf("+-----------------------------------------------+\n");

    liberarGrafoLista(gLista);
    liberarGrafoMatriz(gMatriz);
    free(jogadores);

    printf("\n+-----------------------------------------------+\n");
    printf("|                  FINALIZADO!                  |\n");
    printf("+-----------------------------------------------+\n");

    return 0;
}
