//POTÊNCIA
#include <stdio.h>

int pot(int x, int y){
    if(y == 0) return 1;
    return x * pot(x,y-1);
}

int main(){
    int x = 2;
    int y = 3;
    int z = pot(x, y);
    printf("A potência %d^%d é == %d",x,y,z);
    return 0;
}


//SOMANDO VALORES DE UM ARRAY
#include <stdio.h>

int sumArray(int lista[], int n){
    if(n == 0) return 0;
    return lista[n-1] + sumArray(lista, n-1);
}

int main(){
    int lista [] = {2,3,4,5};
    int x = sizeof(lista) / sizeof(lista[0]);
    int z = sumArray(lista, x);
    printf("A soma é == %d", z);
    return 0;
}


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
//BUSCA SEQUENCIAL
#include <stdio.h>

int buscarArray(int lista[], int n, int i){
    if(n == 1) return 0;
    int alvo = buscarArray(lista, n-1, i);
    if(lista[n-1] == i)
        return n-1;
    else
        return alvo;
}

int main(){
    int lista [] = {2,3,4,5,23,7,64,9,10};
    int x = sizeof(lista) / sizeof(lista[0]);
    int alvo = 3;
    int z = buscarArray(lista, x, alvo);
    printf("O número %d está na posicão [%d]",alvo, z);
    return 0;
}

//BUSCA BINÁRIA
#include <stdio.h>

int buscarArray(int lista[], int a, int n, int i){
    int inc = a;
    int fim = n;
    int meio = inc + (fim - inc) / 2;
	
	if(lista[meio] == i)
		return meio;
	if(i < lista[meio])
		return buscarArray(lista,inc, meio - 1, i);
		else
			return buscarArray(lista, meio + 1, fim, i);    
}
int main(){
    int lista[] = {1,2,3,4,5,6,7,8,9,10,11};
    int fim = sizeof(lista);
    int alvo = 3;
    int z = buscarArray(lista, 0, fim, alvo);
    printf("O número %d está na posicão [%d]",alvo, z);
    return 0;
}

