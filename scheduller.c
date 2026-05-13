#include <stdio.h>
#include <stdlib.h>
#include "gconio.h"
#include "document.h"
#include <time.h>

void menu(){
	printf("New Process: (k)ernel process / (u)ser process\n");
	printf("Actions: (d)elete current process / (e)xit application\n\n");
	}

int main(){
	srand(time(NULL));
	List list = new_List();
	char opcao;
	int totalK = 0;
	int totalU = 0;
	//loop principal da aplicação
	do{
		while(!kbhit(&opcao)){
		menu();
		validarCiclo(list);
		printf("Estado atual da fila...\n");
		printList(list);
			//fazer algo eterno!
			switch(opcao){
				case 'k': inserirProcesso(list, 'k');
				totalK++;
				break;
				case 'u': inserirProcesso(list, 'u');
				totalU++;
				break;
				case 'd': deletarAtivo(list);
				break;
				case 'e':
				printf("\n\nForam executados %d processos, sendo %d Kernel e %d User!\n", totalK+totalU, totalK, totalU);
				return 0;
				default: break;
				}
			opcao = ' ';
			system("sleep 1");
			system("clear");
		}
	}while(1);
	
	return 0;
}

