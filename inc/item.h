#ifndef ITEM_H
#define ITEM_H

#include <stdbool.h>

typedef struct item_ ITEM;

ITEM *create_item(int key);
bool delete_item(ITEM **item);
void print_item(ITEM *item);
int getKey_item(ITEM *item);
bool setKey_item(ITEM *item, int key);

#endif
