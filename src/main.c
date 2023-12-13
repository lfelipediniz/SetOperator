/*
    Created by:
    Luiz Felipe Diniz Costa - 13782032
    Nicolas Carreiro Rodrigues - 14600801
*/

#include "set.h"

/* maximum number of sets that can exist at a time, it is up to the user to
 * increase or decrease */
#define MAX_SETS 10

// auxiliary array to have control over the created sets
SET *sets[MAX_SETS];

// number of sets counter
int num_sets = 0;

// find a set by name in the sets array
SET *find_set(char *name) {
    for (int i = 0; i < num_sets; i++) {
        char *setName = getName_set(sets[i]);
        if (setName != NULL && strcmp(setName, name) == 0) return sets[i];
    }
    return NULL;
}

// list all sets created
void list_sets() {
    if (num_sets == 0) {
        printf("No sets have been created yet.");
        return;
    }

    printf("Sets created:\n");
    for (int i = 0; i < num_sets; i++) {
        char *setName = getName_set(sets[i]);
        if (setName != NULL) {
            printf(" - %s\n", setName);
        }
    }
}

// as its representative in the auxiliary array, the set is also deleted
bool delete_set(char *name) {
    for (int i = 0; i < num_sets; i++) {
        if (strcmp(getName_set(sets[i]), name) == 0) {
            destroy_set(&sets[i]);
            for (int j = i; j < num_sets - 1; j++) {
                sets[j] = sets[j + 1];
            }
            num_sets--;
            return true;
        }
    }
    return false;
}

// check if a name is available to be used, cannot have a repeated name
bool nameAvail(char *name) { return find_set(name) == NULL; }

// exit the program, destroying all sets
void exitProgram() {
    int i;
    for (i = 0; i < num_sets; i++) {
        destroy_set(&sets[i]);
    }

    exit(0);
}

// adds several items at once to the set, separating them with a comma
void addMultipleItems(SET *set, char *items) {
    char *token = strtok(items, ", ");
    while (token != NULL) {
        int itemKey = atoi(token);
        addElement_set(set, create_item(itemKey));
        token = strtok(NULL, ", ");
    }
}

// equal to add multiple items, but with additional checks in case the user tries to remove an item that does not exist
void removeMultipleItems(SET *set, char *items) {
    char *token = strtok(items, ", "); // divide string in sub-strings
    while (token != NULL) {
        int itemKey = atoi(token);
        ITEM *item = create_item(itemKey);
        if (isMember_set(set, item)) {
            removeElement_set(set, item);
        } else {
            printf("Item %d not found in set.", itemKey);
        }
        token = strtok(NULL, ", ");
    }
}

/*

How it works:

The user has the power to create and remove sets, with these commands:

create-set <set name>
delete-set <set name>

The user can add and remove an item in a specific set, like this:

addItem-set <set name> <item key>
removeItem-set <set name> <key to item>

The program gives you the power to create union and intersecting sets, as
well:

union-set <name of set A> <name of set B> <union name>

intersection-set <name of set A> <name of set B> <intersection name>

if you want to know if an item belongs to the set, do the following command
belong-set <set name> <item key>

The user can also list the sets created with the command: list-set
and exit the program whenever you want with: exit
*/

int main() {
    char command[100];
    char setName[50];
    int itemKey;

    while (true) {
        printf("\n");
        scanf("%s", command);

        if (strcmp(command, "create-set") == 0) {
            if (num_sets >= MAX_SETS) {
                printf("Set limit reached!");
                continue;
            }

            scanf("%s", setName);
            if (!nameAvail(setName)) {
                printf("The name '%s' is already in use.", setName);
                continue;
            }

            sets[num_sets++] = create_set(setName);
        } else if (strcmp(command, "delete-set") == 0) {
            scanf("%s", setName);
            if (!delete_set(setName)) {
                printf("Set not found.\n");
            }
        } else if (strcmp(command, "print-set") == 0) {
            scanf("%s", setName);
            SET *set = find_set(setName);
            if (set != NULL) {
                print_set(set);
            } else {
                printf("Set not found.");
            }
        }

        else if (strcmp(command, "addItem-set") == 0) {
            scanf("%s", setName);
            SET *set = find_set(setName);
            if (set != NULL) {
                char items[100];
                scanf(" %[^\n]",
                      items);  // reads the whole line after the set name
                addMultipleItems(set, items);
            } else {
                printf("Set not found.\n");
            }
        } else if (strcmp(command, "removeItem-set") == 0) {
            scanf("%s", setName);
            SET *set = find_set(setName);
            if (set != NULL) {
                char items[100];
                scanf(" %[^\n]",
                      items);  // reads the whole line after the set name
                removeMultipleItems(set, items);
            } else {
                printf("Set not found.\n");
            }
        }

        else if (strcmp(command, "list-set") == 0) {
            list_sets();
        } else if (strcmp(command, "exit") == 0) {
            exitProgram();
        } else if (strcmp(command, "union-set") == 0 ||
                   strcmp(command, "intersection-set") == 0) {
            char setNameA[50], setNameB[50], newName[50];
            scanf("%s %s %s", setNameA, setNameB, newName);

            if (!nameAvail(newName)) {
                printf("The name '%s' is already in use.\n", newName);
                continue;
            }

            SET *setA = find_set(setNameA);
            SET *setB = find_set(setNameB);

            if (setA == NULL || setB == NULL) {
                printf("One or both sets were not found.");
                continue;
            }

            SET *newSet = NULL;
            if (strcmp(command, "union-set") == 0) {
                newSet = union_set(setA, setB, newName);
            } else if (strcmp(command, "intersection-set") == 0) {
                newSet = intersection_set(setA, setB, newName);
            }

            if (newSet != NULL && num_sets < MAX_SETS) {
                sets[num_sets++] = newSet;
            } else {
                printf("Failed to create set or set limit hit.");
                if (newSet != NULL) {
                    destroy_set(&newSet);
                }
            }
        } else if (strcmp(command, "belong-set") == 0) {
            scanf("%s %d", setName, &itemKey);
            SET *set = find_set(setName);
            if (set != NULL) {
                if (isMember_set(set, create_item(itemKey))) {
                    printf("The item belongs to the set.");
                } else {
                    printf("The item does not belong to the set.");
                }
            } else {
                printf("Set not found.");
            }
        }

        else {
            printf("Command not recognized.");
        }
    }

    return 0;
}
