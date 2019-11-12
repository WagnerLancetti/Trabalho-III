#include "Arquivos.h"


/* ********************************************************** ARQUIVOS ********************************************************** */


char** CriaGrafo(int *tam, FILE *input){
    char **mat_grafos;
    int i,j,vert1=0, vert2=0;

    /*
        Variavel mat_grafos = Matriz que sera alocada dinamicamente, seu tipo e 'char' para poupar espaco na memoria, visto que o grafo e nao ponderado
        Variavel input = Arquivo de entrada. Contem a quantidade de empresas que estao sendo instaladas, bem como as ligacoes que existem entre elas
        Variavel str = String que ira ler cada linha do arquivo
        Variavel mult = Variavel que ira converter os valores lidos no arquivo (str) por valores inteiros, usando a decomposicao do numero, em unidades, dezenas, centenas, etc...
        Variavel i, j = Indices para a string, bem como para a matriz
        Variavel vert1 = Variavel que ira guardar o indice de 1 vertice lido no arquivo de entrada
        Variavel vert2 = Varaivel que ira guardar o outro indice do vertice lido no arquivo de entrada
    */
    fscanf (input, "%i", tam);
    mat_grafos = (char**) malloc((*tam) * sizeof(char*)); /* Alocar dinamicamente a matriz[tam][tam], aloca o numero de linhas*/
    for (i = 0; i < *tam; i++){
        mat_grafos[i] = (char*) malloc((*tam) * sizeof(char)); /* Aloca as colunas da matriz*/
        for (j = 0; j < *tam; j++){
            mat_grafos[i][j] = 'F'; /* Inicializa todos os vertices da matriz com F*/
        }
    }
    while (!feof(input)){ /* Ler cada linha do arquivo para criar os caminhos que existem entre as empresas*/
        fscanf (input, "%i %i", &vert1, &vert2);
        mat_grafos[vert1][vert2] = 'V'; /* Atualiza esses vertices para V, ou seja, existe aresta entre aqueles vertices*/
        mat_grafos[vert2][vert1] = 'V'; /* Como e um grafo nao direcionado, e necessario colocar o valor V na linha e coluna dos vertices*/
    }
    fclose(input);
    return mat_grafos;
}
