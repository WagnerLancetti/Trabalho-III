#include "Solucao_Otima.h"


/* ********************************************************** SOLUCAO OTIMA ********************************************************** */


bool Verifica_CMVI(int *vert, int k, char **mat_grafos, int tam){
    int vertice1, vertice2, verifica,i,j;
    for (i = 0; i < k; i++){
        vertice1 = vert[i];
        for ( j = 0; j < k; j++){ /* Compara-se se os vertices sao adjacentes entre si*/
            vertice2 = vert[j];
            if ((vertice1 != vertice2) && (mat_grafos[vertice1][vertice2]== 'V')){ /* Verifica se existe alguma aresta entre os vertices*/
                return false;
            }
        }
    }
    for (i = 0; i < tam; i++){ /* Iremos comparar agora se todos os vertices são adjacentes ao conjunto*/
        vertice1 = i; /* Trava cada vertice na matriz para comparar se ele e adjacente a alguem do conjunto*/
        verifica = 0;
        for (j = 0; j < k; j++){
            vertice2 = vert[j]; /*Trava cada vertice do possivel conjunto maximo para descobrir se os vertices sao adjacentes a ele*/
            if (vertice1 == vertice2){ /* Quando passar por um vertice que faz parte do conjunto solucao*/
                verifica++;
                break;
            }
            if (mat_grafos[vertice1][vertice2] == 'V'){
                verifica++; /* Indica que o vertice da matriz e adjacente a algum do conjunto*/
                break; /* Como o vertice tem que deve adjacente a pelo menos um vertice, entao nao e necessario fazer mais verificacoes*/
            }
        }
        if (verifica == 0){ /* Se algum vertice da matriz nao for adjacente a pelo menos um vertice do conjunto, entao esse conjunto nao e um CVI, menos ainda um CMVI*/
            return false;
        }
    }
    return true;
}


void ForcaBruta(int i, int tam, int *conju, int *cont, int *vert, char **mat_grafos){
    /*
        Variavel i = Comporta-se como indice do vetor de conju
        Variavel tam = Tamanho total da combinacao, ou da quantidade de linhas da matriz
        Variavel conju = Vetor que ira gerar as combinacoes, indicando qual vertice sera verificado ou ignorado para compor a combinacao
        Variavel cont = Variavel que recebera o tamanho do Conjunto Maximo Independente de Vertices (CMIV)
        Variavel vert = Vetor que ira guardar todas as combinacoes geradas para verificar se a combinacao e, ou nao, um CMVI
        Variavel mat_grafos = Matriz de adjacencia que contem as ligacoes que existe entre as empresas
    */
    if(i > tam){
        int k = 0;
        for(int j = 1; j <= tam; j++){
            if(conju[j]==1){ /* Caso o valor seja valido para entrar no conjunto solucao*/
                vert[k] = j-1;
                k++;
            }
        }
        if (*cont < k){
            if (Verifica_CMVI(vert,k,mat_grafos,tam)){
                *cont = k;
            }
        }
    }else{
        /* Cria uma sequencia de valores para ser comparada, por exemplo, se conju tiver so valores 1,
        entao quer dizer que todos aqueles valores fazem parte da combinacao de valores. Caso tenha
        algum valor 0, significa que aquele indice nao deve entrar na combinacao
        */
        conju[i] = 1;
        ForcaBruta(i+1,tam,conju,cont,vert,mat_grafos);
        conju[i] = 0; /* Reseta a sequencia para gerar novas sequencias*/
        ForcaBruta(i+1,tam,conju,cont,vert,mat_grafos);
    }
}
