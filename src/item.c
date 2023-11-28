#include "item.h"

#include <stdio.h>
#include <stdlib.h>

struct item_ {
    int key;
    /* other components */
};

ITEM *create_item(int key) {
    ITEM *item;
    item = (ITEM *)malloc(sizeof(ITEM));

    if (item != NULL) {
        item->key = key;
        return (item);
    }
    return (NULL);
}

bool delete_item(ITEM **item) {
    if (*item != NULL) {
        free(*item);
        *item = NULL; /* Good practice! */
        return (true);
    }
    return (false);
}

int getKey_item(ITEM *item) {
    if (item != NULL) return (item->key);
    exit(1);
}

bool setKey_item(ITEM *item, int key) {
    if (item != NULL) {
        item->key = key;
        return (true);
    }
    return (false);
}

void print_item(ITEM *item) {
    if (item != NULL) printf("\n-->item: %d\n", item->key);
}
