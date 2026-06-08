#ifndef LIST_H
#define LIST_H
#include <stdio.h>

typedef struct __List{
    int size;
    Object head;
    Object tail;
    void (*print)(struct __List* self);
    void (*enqueue)(struct __List* self, Object obj);
    void (*push)(struct __List* self, Object obj);
    Object (*get)(struct __List* self, int id);
    void (*del)(struct __List* self, int id);
    void (*clear)(struct __List* self);
    void (*pop)(struct __List* self);
}__List;
typedef __List* List;

static void print_List(List self){
    if(!self) return;
    Object obj = self->head;
    while(obj){
        obj->print(obj);
        obj = obj->right;
    }
}

static void add(List self, Object obj){
    if(!self || !obj) return;
    if(!self->head){
        self->head = obj;
        self->tail = obj;
    } else {
        self->tail->right = obj;
        obj->left = self->tail;
        self->tail = obj;
    }
    self->size++;
}

static void push(List self, Object obj){
    if(!self || !obj) return;
    if(self->head){
        obj->right = self->head;
        self->head->left = obj;
        self->head = obj;
    } else {
        self->head = obj;
        self->tail = obj;
    }
    self->size++;
}

static Object get_List(List self, int id){
    if(!self) return NULL;
    Object obj = self->head;
    while(obj){
        if(obj->id == id)
            return obj;
        obj = obj->right;
    }
    printf("Não localizado\n");
    return NULL;
}
    
static void deletar(List self, int id){
    if(!self) return;
    Object alvo = get_List(self, id);
    if(!alvo) return;
    
    if(alvo == self->head){
        self->head = alvo->right;
        if(self->head) self->head->left = NULL;
        else self->tail = NULL;
    } else if(alvo == self->tail){
        self->tail = alvo->left;
        if(self->tail) self->tail->right = NULL;
    } else {
        alvo->left->right = alvo->right;
        alvo->right->left = alvo->left;
    }
    alvo->destroy(alvo);
    self->size--;
}

static void clear(List self){
    if(!self) return;
    Object obj = self->head;
    while(obj){
        Object temp = obj->right;
        obj->destroy(obj);
        obj = temp;
    }
    self->head = NULL;
    self->tail = NULL;
    self->size = 0;
}

static void pop(List self){
    if(!self || !self->head) return;
    Object obj = self->head;
    self->head = obj->right;
    if(self->head) self->head->left = NULL;
    else self->tail = NULL;
    obj->destroy(obj);
    self->size--;
}

List new_List(){
    List lst = malloc(sizeof(__List));
    if(!lst) return NULL;
    lst->size = 0;
    lst->head = NULL;
    lst->tail = NULL;
    lst->get = get_List;
    lst->clear = clear;
    lst->del = deletar;
    lst->push = push;
    lst->enqueue = add;
    lst->print = print_List;
    lst->pop = pop;
    return lst;
}

#endif
