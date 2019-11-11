#include <stdio.h>
#include <stdlib.h>

int conj[32];
int cont;

void subconjunto(int i, int n){
 int j;
 if(i>n){
  printf("%d subconjunto: ",++cont);
  for(j=1;j<=n;j++)
   if(conj[j]==1)
    printf("%d ",j-1);
  printf("\n");
}else{
  conj[i] = 1;
  subconjunto(i+1,n);
  conj[i] = 0;
  subconjunto(i+1,n);
 }
}

int main(){
    int n = 7;
    cont = 0;
    subconjunto(1,n);
    return 0;
}
