#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[ ]){

    char str [10];
FILE *arq = fopen("input.txt","w");
if(argc != 4){
  printf("Parametros incorretos. Use os parametros: "
	 "<numero de grafos> <total de vertices> <total de arestas> \n");
  return -1;
}
/*usage: m arestas, n vertices, ng grafos */
/* i,j,k,aux1 e aux2 sao variaveis auxiliares */
/* max Ã© o tamanho max do vetor */

int m,n,ng,i,j,max,k,aux1,aux2;

ng=atoi(argv[1]);
n=atoi(argv[2]);
m=atoi(argv[3]);
//scanf("%d %d %d",&ng,&n,&m);
fputs(argv[2] ,arq);
fputc('\n',arq);
max=n*(n-1)/2;
if (m>max) {
  m = max;
  fprintf(stderr,
	  "Numero de arestas superior ao maximo permitido, atribuido %d.\n",
	  max);
}
printf("%d %d %d\n",ng,n,m);

int vetor_i[max+1];
int vetor_j[max+1];
int escreve_arquivo[2];

k=0;
for(i=0;i<n-1;i++){

	for(j=i+1;j<n && j!=i;j++){ // A aresta (i,j) Ã© guardada na posicao vetor_i[k] e vetor_j[k]
		vetor_i[k]=i;
		vetor_j[k]=j;
		k++;
	}
}



for(k=0;k<ng;k++){ // fornece ng grafos
    j=0;

    for (i=0;i<max;i++) {
	    j=rand()%max;       // j deve receber um inteiro aleatÃ³rio do conjunto de i a w-1.

	    aux1=vetor_i[i];          //Permutacao dos elementos
	    vetor_i[i]=vetor_i[j];
	    vetor_i[j]=aux1;

	    aux2=vetor_j[i];
	    vetor_j[i]=vetor_j[j];
	    vetor_j[j]=aux2;
    }

    for(i=0;i<m;i++){
	    printf("%d %d\t",vetor_i[i],vetor_j[i]);
        escreve_arquivo[0] = vetor_i[i];
        sprintf (str, "%d", escreve_arquivo[0]);
        fputs (str,arq);
        fputc (32,arq);
        escreve_arquivo[1] = vetor_j[i];
        sprintf (str, "%d", escreve_arquivo[1]);
        fputs(str,arq);
        fputc('\n',arq);
    }
    printf("\n");
}
fclose(arq);

return 0;
}
