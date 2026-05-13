#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int PIDcont = 100;
enum tipo {KERNEL, USER};

typedef struct typeProcesso{
	int tipo;
	int pid;
	int status;
	int inst;
	int contador;
	struct typeProcesso* prox;
	struct typeProcesso* ant;
}typeProcesso;

typedef typeProcesso* Process;

typedef struct typeList{
	Process head;
	Process tail;
	Process tail_kernel;
	int size;
}typeList;

typedef typeList* List;

Process new_Process(char tipo){
	Process novo = (Process)malloc(sizeof(typeProcesso));
	if(tipo == 'K' || tipo == 'k') novo->tipo = KERNEL;
	if(tipo == 'u' || tipo == 'U') novo->tipo = USER;
	novo->pid = PIDcont++;
	novo->inst = rand()%12 + 1;
	novo->contador = 0;
	novo->status = 1;
	novo->prox = NULL;
	novo->ant = NULL;
	return novo;
	}

List new_List(){
	List novo = (List)malloc(sizeof(typeList));
	novo->head = novo->tail = novo->tail_kernel = NULL;
	novo->size = 0;
	return novo;
	}

void inserirProcesso(List lst, char tipo){
	if(!lst) {
		printf("Não foi criado a lista"); 
		return;}
	Process novo = new_Process(tipo);
	if(!lst->head){
		lst->head = lst->tail = novo;
		}
		else{
			novo->ant = lst->tail;
			lst->tail->prox = novo;
			lst->tail = novo;
			}
	if(novo->tipo == USER)
		lst->tail_kernel = novo;
		
	lst->size++;
}

char marcardorStatus(Process p){
	if(p->status)
		return '*';
	return ' ';
}

void printProcess(Process p){
	char status = marcardorStatus(p);
	printf("%c\tType:%s\tPID:%d\tInstrução:%d\t Contador:%d\n", status, (p->tipo? "User" : "Kernel"), p->pid, p->inst, p->contador);
	}

void printList(List lst){
	if(!lst || !lst->head){
		return;
	}
	printf("\tType\tPID\tInstrução\tContador\n");
	Process p = lst->head;
	while(p){
		if(p->tipo == KERNEL){
			printProcess(p);}
		p = p->prox;
	}
	p = lst->head;
	while(p){
		if(p->tipo == USER){
			printProcess(p);}
		p = p->prox;
	}
}
void deletarAtivo(List lst) {
    if (!lst || !lst->head) return;

    Process p = lst->head;
    
    while (p != NULL) {
        if (p->status == 1) {
            if (p == lst->head) {
                lst->head = p->prox;
                if (lst->head) lst->head->ant = NULL;
                else lst->tail = NULL; // Lista ficou vazia
            } 
            else if (p == lst->tail) {
                lst->tail = p->ant;
                if (lst->tail) lst->tail->prox = NULL;
            } 
            else {
                p->ant->prox = p->prox;
                p->prox->ant = p->ant;
            }
            if (p == lst->tail_kernel) {
                lst->tail_kernel = p->ant; 
            }

            free(p);
            lst->size--;
            return; // Sai após deletar o primeiro ativo encontrado
        }
        p = p->prox;
    }
}

void encerraProcesso(List lst) {
    if (!lst || !lst->head) return;

    Process p = lst->head;
    while (p) {
        Process proximo = p->prox;
        if (p->contador >= p->inst) {
            if (p == lst->head) {
                lst->head = p->prox;
                if (lst->head) lst->head->ant = NULL;
                else lst->tail = NULL;
            } 
            else if (p == lst->tail) {
                lst->tail = p->ant;
                if (lst->tail) lst->tail->prox = NULL;
            } 
            else {
                p->ant->prox = p->prox;
                p->prox->ant = p->ant;
            }
            if (p == lst->tail_kernel) {
                lst->tail_kernel = p->ant;
            }

            free(p);
            lst->size--;
        }
        p = proximo;
    }
}

void atualizarCiclo(List lst) {
    Process p = lst->head;
    while (p) {
        if (p->status == 1) {
            p->contador++;
        }
        p = p->prox;
    }
}

void gerenciarAtivo(List lst) {
    if (!lst || !lst->head) return;

    Process p = lst->head;
    int algumAtivo = 0;

    // Verifica se já existe alguém ativo
    while (p) {
        if (p->status == 1) {
            algumAtivo = 1;
            break;
        }
        p = p->prox;
    }
    if (!algumAtivo) {
        lst->head->status = 1;
    }
}

void rotacionarStatus(List lst) {
    if (!lst || !lst->head || lst->size < 2) return;

    Process p = lst->head;
    while (p) {
        if (p->status == 1) {
            p->status = 0;
            if (p->prox) {
                p->prox->status = 1; 
            } else {
                lst->head->status = 1;
            }
            break; 
        }
        p = p->prox;
    }
}

void validarCiclo(List lst){
		gerenciarAtivo(lst);
		encerraProcesso(lst);
		rotacionarStatus(lst);
		atualizarCiclo(lst);

	}
