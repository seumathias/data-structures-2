#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definindo uma interface padrão para funções construtoras
#define new(TYPE, ...) new_##TYPE(__VA_ARGS__)

typedef struct __Object
{
	void *item;
	struct __Object *left;
	struct __Object *right;
} __Object;
typedef __Object *Object;

typedef struct
{
	char nome[100];
	int power;
} __Item;
typedef __Item *Item;

typedef struct
{
	char nome[100];
	int hp;
} __Player;
typedef __Player *Player;

Object new_Object()
{
	Object obj = malloc(sizeof(__Object));
	return obj;
}

Object new_Player(char *nome, int hp)
{
	Object obj = new(Object);
	Player n = malloc(sizeof(__Player));
	obj->item = n;
	strcpy(n->nome, nome);
	n->hp = hp;
	return obj;
}

Object new_Item(char *nome, int power)
{
	Object obj = malloc(sizeof(__Object));
	Item n = malloc(sizeof(__Item));
	obj->item = n;
	strcpy(n->nome, nome);
	n->power = power;
	return obj;
}

void inItem(Object lst, char* nome, int p){
    Object n = new(Item, nome, p);
    if(!lst->left){
        lst->left = lst->right = n;
    }
    else{
        lst->left->right = n;
        lst->right = NULL;
    }
}

void inPlayer(Object lst, char* nome, int h){
    Object n = new(Player, nome, h);
    if(!lst->left){
        lst->left = lst->right = n;
    }
    else{
        lst->right->left = n;
        lst->right = n;
        lst->right->right = NULL;
    }
}

void printPlayer(Player p){
     printf("PLAYER----\nNome: %s\nHP: %d\n", p->nome, p->hp);
}

void printItem(Item o){
    printf("ITEM----\nNome: %s\nPoder: %d\n", o->nome, o->power);
    }

void printListItem(Object lst){
    Object o = lst->left;
    while(o){
        if(o->item == Item)
            printItem(o->item);
        }
        o = o->right;
    }

void printListPlayer(Object lst){
    Object o = lst->left;
    while(o){
        if(o->item == Player)
            printPlayer(o->item);
        }
        o = o->right;
    }

void AdicionarItem(Object lst){
    char nome[100];
    int p;
    printf("Digite o nome do Item:\n");
    scanf(" %[^\n]s", nome);
    printf("E qual o poder?\n");
    scanf(" %d", &p);
    return inItem(lst, nome, p);
}

void AdicionarPlayer(Object lst){
    char nome[100];
    int p;
    printf("Digite o nome do jogador:\n");
    scanf(" %[^\n]s", nome);
    printf("E quantos HP?\n");
    scanf(" %d", &p);
    return inPlayer(lst, nome, p);
}

int menu(){
    int opt;
    printf("1-Adicionar item\n");
    printf("2-Adicionar Player\n");
    printf("3-Listar Items\n");
    printf("4-Listar Players\n");
}

int main()
{
	Object lst = new(Object);
    
    switch(menu()){
        case 1: AdicionarItem(lst);
        break;
        case 2: AdicionarPlayer(lst);
        break;
        case 3: printListItem(lst);
        break;
        case 4: printListPlayer(lst);
        break;
    }

}
