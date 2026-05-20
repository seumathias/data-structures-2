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

void printList(Object lst, int opt){
    Object o = lst->left;
    switch(opt){
        case 1: printPlayer(o);
        break;
        case 2: printItem(o);
        break;
    }
}

void printPlayer(Object o){
     printf("PLAYER----\nNome: %s\nHP: %d\n", o->Player->nome, o->Player->hp);
}

void printItem(Object o){
    printf("ITEM----\nNome: %s\nPoder: %d\n", o->Item->nome, o->Item->power);
    }
}

int main()
{
	List lst = new(Object);

	Object arma = new(Item, "arma", 50);

}
