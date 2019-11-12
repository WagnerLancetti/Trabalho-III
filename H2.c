#include "H2.h"


/* ********************************************************** HEURISTICA 2 ********************************************************** */


bool vazio(int *vet, int tam){ /* Confere se existe algum valor nao nulo no vetor, essa funcao foi usada na Heuristica 2*/
    int i;
    bool confere = true;
    for (i = 0; i < tam; i++){
        if (vet[i] != 0){ /*Se houver algum valor nao nulo no vetor, indica que a Heuristica 2 ainda deve trabalhar*/
            confere = false;
            break;
        }
    }
    return confere;
}


int Heuristica2(char **mat_grafos, int tam){
    int *vet, i, j, max = 0, indice, retira = 0;
    vet = (int*)malloc(tam*sizeof(int));
    /*
        Variavel vet = Vetor que ira guardar os vertices que a matriz possue, ou seja, se a matriz possuir 7 vertices, esse vetor ira guardar os vertices 0 1 2 3 4 5 6
        Variavel i, j = Sao indices para percorrer a matriz e o vetor
        Variavel max = Variavel que ira guardar a quantidade de arestas que existe no vertice com maior grau
        Variavel indice = Variavel que ira guardar o indice do vertice que possui o maior grau dentro da matriz
        Variavel retira = Ira informar quantos vertices foram retirados da solucao
    */
    for ( i = 0; i < tam; i++){
        vet[i] = 0; /* Zera cada posicao, assegurando que nao pegue lixo de memoria*/
        for( j = 0; j < tam; j++){ /* Percorre todo o vetor*/
            if (mat_grafos[i][j] == 'V'){ /* Se naquele vertice que o programa estiver rodando houver alguma aresta para outro vertice*/
                vet[i]+=1; /* Atualiza a quantidade de adjacentes que existe ao vertice [i]*/
            }
        }
    }
    while (!(vazio(vet,tam))){ /* Essa funcao ira retornar verdadeiro se nao houver mais aresta no grafo, ou retornara falso caso ainda haja aresta no grafo*/
        max = 0;
        for (i = 0;i < tam; i++){ /* Percorre todo o vetor procurando o maior valor*/
            if (max < vet[i]){ /* Se encontrar algum valor maior ao que ja foi encontrado, atualiza o valor maximo*/
                max = vet[i]; /* Guarda o novo valor maximo*/
                indice = i; /* Pega o indice do valor maximo*/
            }
        }
        vet[indice] = 0; /* Como esse vertice sera apagado, seu novo valor sera 0*/
        for(j = 0; j < tam; j++){ /* For para atualizar o vetor e a matriz*/
            if (mat_grafos[j][indice] == 'V'){  /* Quando encontrar os adjacentes ao vertice com maior grau*/
                mat_grafos[indice][j] = 'F'; /* Apaga a aresta que existia entre os vertices, uma vez que esse vertice com maior grau sera apagado da solucao*/
                mat_grafos[j][indice] = 'F';
                vet[j] -= 1; /* Reduz a quantidade de valores adjacentes dos vertices*/
            }
        }
        retira++; /* Uma empresa foi excluida da solucao*/
    }
    free (vet);
    return tam - retira;
}
