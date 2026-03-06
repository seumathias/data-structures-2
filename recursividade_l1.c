


//COMO SELECIONAR O MAIOR ITEM DE UM ARRAY
#include <stdio.h>

int sumArray(int lista[], int n){
    if(n == 1) return lista[0];
    int maior = sumArray(lista, n-1);
    if(lista[n-1] > maior)
        return lista[n-1];
    else
        return maior;
}

int main(){
    int lista [] = {2,3,4,5,23,7,64,9,10};
    int x = sizeof(lista) / sizeof(lista[0]);
    int z = sumArray(lista, x);
    printf("o maior número é de == %d", z);
    return 0;
}
