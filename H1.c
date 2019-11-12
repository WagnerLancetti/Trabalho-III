#include "H1.h"

/* ********************************************************** HEURISTICA 1 ********************************************************** */


int Heuristica1 (char **mat_grafos, int tam){
    int retira = 0,i,j,k,m,cont1,cont2,*vet, valor;
    /*
        Variavel Retira = Ira informar quantos vertices foram retirados da solucao
        Variavel i, j, k, m = Sao indices para a matriz e o vetor
        Variavel cont1 = Variavel que ira contabilizar quantos vertices sao adjacentes ao vertice que o programa esta rodando no momento
        Variavel cont2 = Variavel que ira contabilizar quantos vertices sao adjacentes ao vertice adjacente que o programa encontrou
        Variavel *vet = Vetor que ira guardar todos os vertices adjacentes que forem encontrados
        Variavel valor = Variavel que ira guardar a posicao do vetor de vertices adjacentes (o vertice que esta sendo procurado)
    */
    vet = (int*) malloc (tam * sizeof(int)); /* Vetor que ira guardar todos os vertices que sao adjacentes*/
    for (i = 0; i < tam; i++){ /* For para percorrer toda a matriz (linhas)*/
        k = 0;
        cont1 = 0;
        cont2 = 0;
        for (j = 0; j < tam; j++){ /* For para percorrer toda a matriz (colunas)*/
            if (mat_grafos[i][j] == 'V'){ /* Confere se na linha que esta percorrendo a matriz existe algum vertice adjacente*/
                vet[k] = j; /* Guarda no vetor qual e a posicao desse vertice adjacente*/
                k++;
                cont1++; /* Existe adjacente ao vertice que o programa esta executando*/
            }
        }
        if (cont1 != 0){ /* Se houver adjacentes ao vertice que o programa rodou*/
            /* Iremos verificar qual vertice contem mais vertices adjacentes, se e o que o programa esta agora [i], ou se e um dos vertices adjacentes ao vertice [i]*/
                for (j = 0; j < k; j++){ /* For para percorrer os vertices adjacentes a [i]*/
                    valor = vet[j]; /* Guarda a posicao de um dos vertices adjacentes a [i]*/
                    cont2 = 0;
                    for (m = 0; m < tam; m++){ /* For para percorrer a matriz (colunas)*/
                        if (mat_grafos[valor][m] == 'V'){ /* Se encontrar algum adjacente ao vertice adjacente de [i]*/
                            cont2++; /* Existe adjacentes ao adjacentes de [i]*/
                        }
                        if (cont2 >= cont1){ /* Para poupar verificacao, se o cont2 passar cont1, o vertice adjacente ao [i] que sera excluido, nao sendo necessario mais a busca de mais vertices*/
                            break;
                        }
                    }
                if (cont2 >= cont1){ /* Se o numero de adjacentes ao vertice adjacente a [i] for superior a quantidade de adjacentes a [i]*/
                    for (m = 0; m < tam; m++){ /* Percorre toda a linha da matriz "apagando" o vertice da solucao*/
                        mat_grafos[valor][m] = 'F'; /* A atribuicao F, indica para o programa que ele nao deve mais se preocupar com esse vertice*/
                        mat_grafos[m][valor] = 'F';
                    }
                }else{ /* Se o numero de adjacentes a [i] for superior que o seu adjacente, ele e eliminado da solucao*/
                    for (m = 0; m < tam; m++){
                        mat_grafos[i][m] = 'F';
                        mat_grafos[m][i] = 'F';
                    }
                    j += k; /* Se o vertice [i] for excluido, nao tem motivo o programa tentar excluir qualquer outro vertice*/
                }
                retira ++; /* Uma empresa foi excluida da solucao*/
            }
        }
    }
    free (vet); /* Libera o espaco armazenado pelo vetor que guarda os vertices adjacentes*/
    return tam - retira;
}
