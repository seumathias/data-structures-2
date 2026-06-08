#ifndef OBJECT_H
#define OBJECT_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


#define new(TYPE, ...) new_##TYPE(__VA_ARGS__)

typedef struct __Node{
    void* content;
    struct __Node* left;
    struct __Node* right;
    
    void (*destroy)(struct __Node* self);
    void (*print)(struct __Node* self);
    void (*set)(struct __Node* self, ...);
    
    void (*set_especifico)(void* content, va_list args);
    void (*print_especifico)(void*);
    int id;
}__Node;
typedef __Node* Object;

static void destroy(Object self){
    if(self){
        if(self->content){
			free(self->content);}
        free(self);
    }
}

static void print(Object self) {    
    if(self && self->print_especifico) {
        self->print_especifico(self->content);
    }
}

static void set_Object(Object self, ...){
    if(!self || !self->set_especifico) return;
    va_list args;
    va_start(args, self);
    self->set_especifico(self->content, args);
    va_end(args);
}

Object new_Object(int id){
    Object l = malloc(sizeof(__Node));
    if(!l) return NULL;
    l->left = NULL;
    l->right = NULL;
    l->id = id;
    l->content = NULL;
    l->destroy = destroy;
    l->print = print;
    l->set = set_Object;
    l->print_especifico = NULL;
    l->set_especifico = NULL;
    return l;
}

#endif

//Rodrigo Mathias de Queiroz
