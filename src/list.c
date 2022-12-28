#include "macros.h"
#include "list.h"

#include <stdlib.h>

struct list *list_create() {
    struct list *l = malloc(sizeof *l);
    CHECK_ALLOC(l, "list");

    return l;
}

void list_free(struct list *l) {
    struct list_node *curr = l->first;

    while (curr != NULL) {
        struct list_node *next = curr->next;
        free(curr);
        curr = next;
    }

    free(l);
}

void list_append(struct list *l, void *value) {
    struct list_node *new = malloc(sizeof *new);
    CHECK_ALLOC(new, "node");

    new->value = value;

    if (l->first == NULL)
        l->first = new;

    if (l->last != NULL)
        l->last->next = new;

    l->last = new;
    ++l->length;
}

void *list_pop(struct list *l) {
    if (l->last == NULL)
        return NULL;

    void *value = l->last->value;

    l->last = l->last->prev;
    free(l->last->next);

    --l->length;
    // if the list is empty
    if (l->length == 0)
        l->first = NULL;

    return value;
}
