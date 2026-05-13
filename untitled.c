#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct typeDoc{
	int id;
	int tamanho;
	char* nome;
	struct typeDoc* next;
	struct typeDoc* before;
}typeDoc;

typedef typeDoc* Doc;

typedef struct typeList{
	Doc head;
	Doc tail;
	int size;
}typeList;

typedef typeList* List;

char* string(char* str){
	char* s = malloc(sizeof(strlen(str)+1));
	strcpy(s,str);
	return s;
	}

Doc new_Document(char nome[], int id){
	Doc novo = malloc(sizeof(typeDoc));
	novo->id = id;
	novo->nome = string(nome);
	novo->tamanho = 1+ rand()%1000 + 100;
	novo->next = NULL;
	novo->before = novo;
	return novo;
	}

List new_List(){
	List novo = malloc(sizeof(typeList));
	novo->size = 0;
	novo->head = novo->tail = NULL;
	return novo;
}

void inserirDoc(List lst, char nome[], int id){
	if(!lst) return;
	Doc novo = new_Document(nome, id);
	if(!lst->head){
		lst->head = lst->tail = novo;
		return;
		}
	novo->before = lst->tail;
	lst->tail->next = novo;
	lst->tail = novo;
	lst->size++;
}

void printDoc(Doc d){
	printf("ID:%d\nNome:%s\nTamanho:%d\n", d->id, d->nome, d->tamanho);
	printf("================\n");
	}

void printList(List lst){
	printf("DOCUMENTOS NA FILA\n========\n");
	Doc i = lst->head;
	while(i){
		printDoc(i);
		i = i->next;
		}
	}
	
void imprimirPrimeiro(List lst){
	if(!lst || !lst->head){
		printf("Não há documento ou fila de impressão");
		return;
		}
	Doc target = lst->head;
	printf("Imprimindo documento...\n");
	printDoc(target);
	lst->head = target->next;
	if(!lst->head)
		lst->tail = NULL;
	lst->size--;	
	free(target->nome);
	free(target);
}

void deletar(List lst, int id){
	if(!lst || !lst->head) return;
	if(lst->head->id == id){ //CASO SER HEAD
		Doc target = lst->head;
		lst->head = target->next; //POSICIONA O NEXT PARA O HEAD
		if(!lst->head) lst->tail = NULL; //SE NÃO HOUVER HEAD, ENTÃO O TAIL TEM QUE SER NULL
		lst->size--; //DIMINUIR A LISTA NO DELETE
		
		free(target->nome);
		free(target);
		return;
	}
	Doc current = lst->head->next; //Caso não seja o primeiro a ser deletado
	while(current){
		if(current->id == id){
			current->before->next = current->next; //Faz o anterior dele apontar para o próximo do atual
			if(current->next) current->next->before = current->before; //Caso tenha um próximo
			if(current == lst->tail) current->before->next = NULL; //Caso seja o último
			
			lst->size--;
			free(current->nome);
			free(current);
			return;
			}
		current = current->next;
		}	
	}
	

void priorizar(List lst, int id){
	if(!lst || !lst->head) return;
	if(lst->head->id == id){
		printf("Documento já é o primeiro da fila.\n\n");
		return;
		}
	Doc target = lst->head->next;
	while(target){ //Caso não seja o head
		if(target->id == id){
			target->before->next = target->next;
			
			if(target->next)
				target->next->before = target->before; //Checar se há um next
					else
					lst->tail = target->before; //Checar se era o último
			
			target->next = lst->head; //Armazena o antigo head com o next do target;
			lst->head->before = target; //Armazena o target em um lugar
			
			lst->head = target; //Posiciona o target no head, sem perder a fila.
			target->before = NULL;
			return;
		}
		target = target->next;
	}
}
