#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "untitled.c"

void colocarDoc(List lst, int id){
	char nome[1000];
	printf("Digite o nome do arquivo: ");
	scanf(" %[^\n]s", nome);
	inserirDoc(lst, nome, id);
	return;

	}

int menu(){
	int opt;
	printf("======MENU==5=====\n");
	printf("1-Criar documento\n");
	printf("2-Imprimir primeiro da lista\n");
	printf("3-Priorizar documento\n");
	printf("4-Deletar documento\n");
	printf("5-Ver documentos listados\n");
	printf("6-Encerrar impressora\n\nDigite sua opção: ");
	scanf(" %d", &opt);
	return opt;
	}

int main(){
	List lst = new_List();
	int id = 1;

	while(1){
		switch(menu()){
			case 1: colocarDoc(lst, id);
				id++;
				system("clear");
			break;
			case 2:
				imprimirPrimeiro(lst);
				system("clear");
			break;
			case 3:
				int p;
				printList(lst);
				printf("\nQual ID priorizar?");
				scanf(" %d", &p);
				priorizar(lst, p);	
				system("clear");
			break;
			case 4: 
				int c;
				printList(lst);
				printf("\nQual ID deletar??");
				scanf(" %d", &c);
				deletar(lst, c);
				system("clear");
			break;
			case 5:
				printList(lst);
				printf("\n\nDigite qualquer coisa para continuar...\n");
				while(getchar() != '\n');
				getchar();
				system("clear");
			break;
			case 6:
			return 0;
			default:
			printf("Inválido, tente uma opção. \n\n");
			break;
			
			}
		}
		printf("\n\n===Impressora encerrada!");
}
