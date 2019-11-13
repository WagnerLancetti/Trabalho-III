#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <getopt.h>
#include "Arquivos.h"
#include "H1.h"
#include "H2.h"
#include "Solucao_Otima.h"





/* ********************************************************** PROGRAMA PRINCIPAL ********************************************************** */


int main(int argc, char *argv[]){
    system("clear");
    int *vert, *conju;
    char **mat_grafos, *entrada = NULL, *saida = NULL;;
    int tam = 0, opcao,cont = 0, option;
    struct timeval start, end;
    if(argc != 5){
        printf("\nERROR!!! argumentos incorretos na linha do terminal\n");
        printf("Digite: ./(arquivo_executavel) -i (arquivo_de_entrada) -o (arquivo_de_saida)\n\n");
        return -1;
    }
    /*
        Variavel mat_grafos = Matriz que ira ser alocada dinamicamente com a quantidade de empresas que estao sendo instaladas
        Variavel tam = Variavel que ira guardar a quantidade de empresas que estao sendo instaladas
        Variavel opcao = Usuario ira decidir qual algoritmo ele ira executar
    */

    while((option = getopt(argc , argv , "i:o:")) != -1){
        switch (option) {
            case 'i':
            entrada = optarg;
            break;
          case 'o':
            saida = optarg;
            break;
          case '?':
            printf("\nDigite: ./(arquivo_executavel) -i (arquivo_de_entrada) -o (arquivo_de_saida)\n\n");
            return -1;
            break;
          default:
            printf("\nERROR!!! argumentos incorretos na linha do terminal\n");
            break;
            }
    }
    if (entrada !=  NULL && saida != NULL){
        FILE *input = fopen (entrada,"r");
        FILE *output = fopen (saida,"w");
        if(input == NULL)
        {
            printf("\nERROR!!! arquivo de entrada nao encontrado!\n\n");
            return -1;
        }
        printf ("\nO que deseja executar:\n1) Solucao otima\n2) Heuristica 1\n3) Heuristica 2\n");
        printf ("Opcao: ");
        scanf ("%i",&opcao);
        gettimeofday(&start, NULL);
        mat_grafos = CriaGrafo(&tam,input);
        switch (opcao){
            case 1: // Solucao otima
                vert = (int*) malloc (tam * sizeof(int));
                conju = (int*) malloc (tam * sizeof(int));
                ForcaBruta(1,tam,conju,&cont,vert,mat_grafos);
                fprintf (output,"%d",cont);
                break;
            case 2: // Heuristica 1
                cont = Heuristica1(mat_grafos,tam);
                fprintf (output,"%d",cont);
                break;
            case 3: // Heuristica 2
                cont = Heuristica2(mat_grafos,tam);
                fprintf (output,"%d",cont);
                break;
            default: // Se o usuario digitar um valor invalido
                system("clear");
                printf ("Comando invalido!\n");
        }
        free (vert);
        free (conju);
        fclose(input);
        fclose (output);
        free(mat_grafos);
        gettimeofday(&end, NULL);
        printf("\nTempo gasto = %ld microssegundos.\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));
    }
}
