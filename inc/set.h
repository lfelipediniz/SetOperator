#ifndef SET_H
#define SET_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../inc/item.h"

// for AVL Tree
#define max(a, b) ((a > b) ? a : b)

typedef struct set_ SET;
typedef struct node_ NODE;

// basic operations
SET *create_set(char *name);
bool destroy_set(SET **sp);
bool addElement_set(SET *sp, ITEM *ele);
bool removeElement_set(SET *sp, ITEM *ele);
void print_set(SET *sp);
char *getName_set(SET *sp);  // returns the name of the set to give the user the
                             // power to manipulate the sets in any structure he
                             // eventually creates by name

// specific operations
bool isMember_set(SET *sp, ITEM *ele);
SET *union_set(SET *sp1, SET *sp2, char *name);
SET *intersection_set(SET *sp1, SET *sp2, char *name);

#endif
