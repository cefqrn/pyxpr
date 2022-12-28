#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

struct list_node {
    void *value;
    struct list_node *next;
    struct list_node *prev;
};

struct list {
    struct list_node *first;
    struct list_node *last;
    size_t length;
};

struct list *list_create();
void list_free(struct list *l);

void list_append(struct list *l, void *value);
void *list_pop(struct list *l);

#endif
