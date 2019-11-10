#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>


char** CriaGrafo(int *tam){
    char **mat_grafos;
    FILE *input = fopen("input.txt","r");
    char str[10];
    int mult = 1,i,j,vert1=0, vert2=0;
    fgets (str,10,input);
    for (i = 0; str[i]!= '\n'; i++){
        *tam = *tam + (str[i] - '0') * mult;
        mult *= 10;
    }
    mat_grafos = (char**) malloc((*tam) * sizeof(char*));
    for (i = 0; i < *tam; i++){
        mat_grafos[i] = (char*) malloc((*tam) * sizeof(char));
        for (j = 0; j < *tam; j++){
            mat_grafos[i][j] = 'F';
        }
    }
    while (!feof(input)){
        fgets (str,10,input);
        mult = 1;
        vert1 = 0;
        vert2 = 0;
        for (i = 0; str[i] != '\0'; i++){
            if (str[i+1] == '\n'){
                for (j = i; str[j] != 32; j--){
                    vert2 += (str[j] - 48) * mult;
                    mult*=10;
                }
            }
            if (str[i] == 32){
                for (j = i - 1; j >= 0; j--){
                    vert1 += (str[j] - '0') * mult;
                }
            }
        }
        mat_grafos[vert1][vert2] = 'V';
        mat_grafos[vert2][vert1] = 'V';
    }
    fclose(input);
    return mat_grafos;
}

bool vazio(int *vet, int tam){
    bool confere = true;
    for (int i = 0; i < tam; i++){
        if (vet[i] != 0){
            confere = false;
            break;
        }
    }
    return confere;
}

int Heuristica1 (char **mat_grafos, int tam){
    int retira = 0,i,j,k,m,cont1,cont2,*vet, valor;
    vet = (int*) malloc (tam * sizeof(int));
    for (i = 0; i < tam; i++){
        k = 0;
        cont1 = 0;
        cont2 = 0;
        for (j = 0; j < tam; j++){
            if (mat_grafos[i][j] == 'V'){
                vet[k] = j;
                k++;
                cont1++;
            }
        }
        if (cont1 != 0){
            for (j = 0; j < k; j++){
                valor = vet[j];
                for (m = 0; m < tam; m++){
                    if (mat_grafos[valor][m] == 'V'){
                        cont2++;
                    }
                    if (cont2 > cont1){
                        break;
                    }
                }
                if (cont2 >= cont1){
                    for (m = 0; m < tam; m++){
                        mat_grafos[valor][m] = 'F';
                        mat_grafos[m][valor] = 'F';
                    }
                }else{
                    for (m = 0; m < tam; m++){
                        mat_grafos[i][m] = 'F';
                        mat_grafos[m][i] = 'F';
                    }
                }
                retira ++;
            }
        }
    }
    free (vet);
    return tam - retira;
}

int Heuristica2(char **mat_grafos, int tam){
    int *vet, i, j, max = 0, retira = 0;
    vet = (int*)malloc(tam*sizeof(int));
    for ( i = 0; i < tam; i++){
        vet[i] = 0;
        for( j = 0; j < tam; j++){
            if (mat_grafos[i][j] == 'V'){
                vet[i]+=1;
            }
        }
    }
    while (!(vazio(vet,tam))){
        max = 0;
        for (i = 0;i < tam; i++){
            if (max < vet[i]){
                max = i;
            }
        }
        vet[max] = 0;
        for(j = 0; j < tam; j++){
            if (mat_grafos[j][max] == 'V'){
                mat_grafos[max][j] = 'F';
                mat_grafos[j][max] = 'F';
                vet[j] -= 1;
            }
        }
        retira++;
    }
    return tam - retira;
}

int main(){
    char **mat_grafos;
    int tam = 0, opcao;
    mat_grafos = CriaGrafo(&tam);
    printf ("\nO que deseja executar:\n1) Solucao otima\n2) Heuristica 1\n3) Heuristica 2\n");
    printf ("Opcao: ");
    scanf ("%i",&opcao);

    switch (opcao){
        case 1:
            break;
        case 2:
            printf("%i \n",Heuristica1(mat_grafos,tam));
            break;
        case 3:
            printf ("%i \n",Heuristica2(mat_grafos,tam));
            break;
        default:
            printf ("Comando invalido!\n");
    }
    free(mat_grafos);
}



