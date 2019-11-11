#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char** CriaGrafo(int *tam){
    char **mat_grafos;
    FILE *input = fopen("input.txt","r");
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
    mat_grafos = (char**) malloc((*tam) * sizeof(char*)); // Alocar dinamicamente a matriz[tam][tam], aloca o numero de linhas
    for (i = 0; i < *tam; i++){
        mat_grafos[i] = (char*) malloc((*tam) * sizeof(char)); // Aloca as colunas da matriz
        for (j = 0; j < *tam; j++){
            mat_grafos[i][j] = 'F'; // Inicializa todos os vertices da matriz com F
        }
    }
    while (!feof(input)){ // Ler cada linha do arquivo para criar os caminhos que existem entre as empresas
        fscanf (input, "%i %i", &vert1, &vert2);
        mat_grafos[vert1][vert2] = 'V'; // Atualiza esses vertices para V, ou seja, existe aresta entre aqueles vertices
        mat_grafos[vert2][vert1] = 'V'; // Como e um grafo nao direcionado, e necessario colocar o valor V na linha e coluna dos vertices
    }
    fclose(input); 
    return mat_grafos;
}

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
    vet = (int*) malloc (tam * sizeof(int)); // Vetor que ira guardar todos os vertices que sao adjacentes
    for (i = 0; i < tam; i++){ // For para percorrer toda a matriz (linhas)
        k = 0;
        cont1 = 0;
        cont2 = 0;
        for (j = 0; j < tam; j++){ // For para percorrer toda a matriz (colunas)
            if (mat_grafos[i][j] == 'V'){ // Confere se na linha que esta percorrendo a matriz existe algum vertice adjacente
                vet[k] = j; // Guarda no vetor qual e a posicao desse vertice adjacente
                k++;
                cont1++; // Existe adjacente ao vertice que o programa esta executando
            }
        }
        if (cont1 != 0){ // Se houver adjacentes ao vertice que o programa rodou
            // Iremos verificar qual vertice contem mais vertices adjacentes, se e o que o programa esta agora [i], ou se e um dos vertices adjacentes ao vertice [i]
                for (j = 0; j < k; j++){ // For para percorrer os vertices adjacentes a [i]
                    valor = vet[j]; // Guarda a posicao de um dos vertices adjacentes a [i]
                    cont2 = 0;
                    for (m = 0; m < tam; m++){ // For para percorrer a matriz (colunas)
                        if (mat_grafos[valor][m] == 'V'){ // Se encontrar algum adjacente ao vertice adjacente de [i]
                            cont2++; // Existe adjacentes ao adjacentes de [i]
                        }
                        if (cont2 >= cont1){ // Para poupar verificacao, se o cont2 passar cont1, o vertice adjacente ao [i] que sera excluido, nao sendo necessario mais a busca de mais vertices
                            break;
                        }
                    }
                if (cont2 >= cont1){ // Se o numero de adjacentes ao vertice adjacente a [i] for superior a quantidade de adjacentes a [i]
                    for (m = 0; m < tam; m++){ // Percorre toda a linha da matriz "apagando" o vertice da solucao
                        mat_grafos[valor][m] = 'F'; // A atribuicao F, indica para o programa que ele nao deve mais se preocupar com esse vertice
                        mat_grafos[m][valor] = 'F';
                    }
                }else{ // Se o numero de adjacentes a [i] for superior que o seu adjacente, ele e eliminado da solucao
                    for (m = 0; m < tam; m++){
                        mat_grafos[i][m] = 'F';
                        mat_grafos[m][i] = 'F';
                    }
                    j += k; // Se o vertice [i] for excluido, nao tem motivo o programa tentar excluir qualquer outro vertice
                }
                retira ++; // Uma empresa foi excluida da solucao
            }
        }
    }
    free (vet); // Libera o espaco armazenado pelo vetor que guarda os vertices adjacentes
    return tam - retira;
}


bool vazio(int *vet, int tam){ // Confere se existe algum valor nao nulo no vetor, essa funcao foi usada na Heuristica 2
    bool confere = true; 
    for (int i = 0; i < tam; i++){
        if (vet[i] != 0){ //Se houver algum valor nao nulo no vetor, indica que a Heuristica 2 ainda deve trabalhar
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
        vet[i] = 0; // Zera cada posicao, assegurando que nao pegue lixo de memoria
        for( j = 0; j < tam; j++){ // Percorre todo o vetor
            if (mat_grafos[i][j] == 'V'){ // Se naquele vertice que o programa estiver rodando houver alguma aresta para outro vertice
                vet[i]+=1; // Atualiza a quantidade de adjacentes que existe ao vertice [i]
            }
        }
    }
    while (!(vazio(vet,tam))){ // Essa funcao ira retornar verdadeiro se nao houver mais aresta no grafo, ou retornara falso caso ainda haja aresta no grafo
        max = 0;
        for (i = 0;i < tam; i++){ // Percorre todo o vetor procurando o maior valor
            if (max < vet[i]){ // Se encontrar algum valor maior ao que ja foi encontrado, atualiza o valor maximo
                max = vet[i]; // Guarda o novo valor maximo
                indice = i; // Pega o indice do valor maximo
            }
        }
        vet[indice] = 0; // Como esse vertice sera apagado, seu novo valor sera 0
        for(j = 0; j < tam; j++){ // For para atualizar o vetor e a matriz
            if (mat_grafos[j][indice] == 'V'){  // Quando encontrar os adjacentes ao vertice com maior grau
                mat_grafos[indice][j] = 'F'; // Apaga a aresta que existia entre os vertices, uma vez que esse vertice com maior grau sera apagado da solucao
                mat_grafos[j][indice] = 'F';
                vet[j] -= 1; // Reduz a quantidade de valores adjacentes dos vertices
            }
        }
        retira++; // Uma empresa foi excluida da solucao
    }
    free (vet);
    return tam - retira;
}

bool Verifica_CMVI(int *vert, int k, char **mat_grafos, int tam){
    int vertice1, vertice2, verifica,i,j;
    for (i = 0; i < k; i++){
        vertice1 = vert[i];
        for ( j = 0; j < k; j++){ // Compara-se se os vertices sao adjacentes entre si
            vertice2 = vert[j];
            if ((vertice1 != vertice2) && (mat_grafos[vertice1][vertice2]== 'V')){ // Verifica se existe alguma aresta entre os vertices
                return false;
            } 
        }
    }
    for (j = 0; j < k; j++){
        printf ("%i ",vert[j]);
    }
    printf ("\n");
    for (i = 0; i < tam; i++){ // Iremos comparar agora se todos os vertices são adjacentes ao conjunto
        vertice1 = i; // Trava cada vertice na matriz para comparar se ele e adjacente a alguem do conjunto
        verifica = 0;
        for (j = 0; j < k; j++){
            vertice2 = vert[j]; //Trava cada vertice do possivel conjunto maximo para descobrir se os vertices sao adjacentes a ele
            if (vertice1 == vertice2){
                verifica++;
                break;
            }
            if (mat_grafos[vertice1][vertice2] == 'V'){
                verifica++; // Indica que o vertice da matriz e adjacente a algum do conjunto
                break; // Como o vertice tem que deve adjacente a pelo menos um vertice, entao nao e necessario fazer mais verificacoes
            }
        }
        if (verifica == 0){ 
            return false;
        }
    }
    return true;
}


int ForcaBruta(int i, int tam, int *conju, int cont, int *vert, char **mat_grafos,int tamanho){
    if(i > tam){
        int k = 0;
        for(int j = 1; j <= tam; j++){
            if(conju[j]==1){
                //printf ("%i ", j-1);
                vert[k] = j-1;
                k++;
            }
        }
        if (cont < k){
            if (Verifica_CMVI(vert,k,mat_grafos,tamanho)){
                cont = k;
            }
        }
    }else{
        conju[i] = 1;
        ForcaBruta(i+1,tam,conju,cont,vert,mat_grafos,tamanho);
        conju[i] = 0;
        ForcaBruta(i+1,tam,conju,cont,vert,mat_grafos,tamanho);
    }
    return cont;
}



int main(){
    int *vert, *conju;
    char **mat_grafos;
    int tam = 0, opcao;
    /*
        Variavel mat_grafos = Matriz que ira ser alocada dinamicamente com a quantidade de empresas que estao sendo instaladas
        Variavel tam = Variavel que ira guardar a quantidade de empresas que estao sendo instaladas
        Variavel opcao = Usuario ira decidir qual algoritmo ele ira executar
    */
    mat_grafos = CriaGrafo(&tam);
    printf ("\nO que deseja executar:\n1) Solucao otima\n2) Heuristica 1\n3) Heuristica 2\n");
    printf ("Opcao: ");
    scanf ("%i",&opcao);
    switch (opcao){
        case 1: // Solucao otima
            vert = (int*) malloc (tam * sizeof(int));
            conju = (int*) malloc (tam * sizeof(int));
            printf ("%i \n",ForcaBruta(1,tam,conju,0,vert,mat_grafos,tam));
            break;
        case 2: // Heuristica 1
            printf("%i \n",Heuristica1(mat_grafos,tam));
            break;
        case 3: // Heuristica 2
            printf ("%i \n",Heuristica2(mat_grafos,tam));
            break;
        default: // Se o usuario digitar um valor invalido
            printf ("Comando invalido!\n");
    }
    free(mat_grafos); // Libera espaco alocado pela matriz
}       