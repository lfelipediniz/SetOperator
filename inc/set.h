#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct set_ SET;

// basic operations
SET *create_set();
bool destroy_set(SET *sp);
bool addElement_set(SET *sp, int ele);
bool removeElement_set(SET *sp, int ele);
void print_set(SET *sp);

// specific operations
bool isMember_set(SET *sp, int ele);
SET *union_set(SET *sp1, SET *sp2);
SET *intersection_set(SET *sp1, SET *sp2);


#endif
