#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "../inc/item.h"

// for AVL Tree
#define max(a, b) ((a > b) ? a : b)

typedef struct set_ SET;
typedef struct node_ NODE;

// basic operations
SET *create_set();
bool destroy_set(SET **sp);
bool addElement_set(SET *sp, ITEM * ele);
bool removeElement_set(SET *sp, ITEM * ele);
void print_set(SET *sp);
int search(SET *sp, int key);

// specific operations
bool isMember_set(SET *sp, int ele);
SET *union_set(SET *sp1, SET *sp2);
SET *intersection_set(SET *sp1, SET *sp2);

// debug
void printAVLTree(SET *set);

#endif
