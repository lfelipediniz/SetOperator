#include "set.h"

#define MAX_SETS 10

SET *sets[MAX_SETS];
int num_sets = 0;

SET *find_set(char *name) {
    for (int i = 0; i < num_sets; i++) {
        char *setName = getName_set(sets[i]);
        if (setName != NULL && strcmp(setName, name) == 0) return sets[i];
    }
    return NULL;
}

void list_sets() {
    if (num_sets == 0) {
        printf("Nenhum conjunto foi criado ainda.\n");
        return;
    }

    printf("Conjuntos criados:\n");
    for (int i = 0; i < num_sets; i++) {
        char *setName = getName_set(sets[i]);
        if (setName != NULL) {
            printf(" - %s\n", setName);
        }
    }
}

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

bool nameAvail(char *name) { return find_set(name) == NULL; }

void exitProgram() {
    int i;
    for (i = 0; i < num_sets; i++) {
        destroy_set(&sets[i]);
    }

    exit(0);
}

int main() {
    char command[100];
    char setName[50];
    int itemKey;

    while (true) {
        printf("\n");
        scanf("%s", command);

        if (strcmp(command, "create-set") == 0) {
            if (num_sets >= MAX_SETS) {
                printf("Limite de conjuntos atingido.\n");
                continue;
            }

            scanf("%s", setName);
            if (!nameAvail(setName)) {
                printf("O nome '%s' já está em uso.\n", setName);
                continue;
            }

            sets[num_sets++] = create_set(setName);
        } else if (strcmp(command, "delete-set") == 0) {
            scanf("%s", setName);
            if (!delete_set(setName)) {
                printf("Conjunto não encontrado.\n");
            }
        } else if (strcmp(command, "print-set") == 0) {
            scanf("%s", setName);
            SET *set = find_set(setName);
            if (set != NULL) {
                print_set(set);
            } else {
                printf("Conjunto não encontrado.\n");
            }
        } else if (strcmp(command, "removeItem-set") == 0) {
            scanf("%s %d", setName, &itemKey);
            SET *set = find_set(setName);
            if (set != NULL) {
                if (!removeElement_set(set, create_item(itemKey))) {
                    printf("Falha ao remover o item ou item não encontrado.\n");
                }
            } else {
                printf("Conjunto não encontrado.\n");
            }
        }

        else if (strcmp(command, "addItem-set") == 0) {
            scanf("%s %d", setName, &itemKey);
            SET *set = find_set(setName);
            if (set != NULL) {
                addElement_set(set, create_item(itemKey));
            } else {
                printf("Conjunto não encontrado.\n");
            }
        } else if (strcmp(command, "list") == 0) {
            list_sets();
        } else if (strcmp(command, "exit") == 0) {
            exitProgram();
        } else if (strcmp(command, "union-set") == 0 ||
                   strcmp(command, "intersection-set") == 0) {
            char setNameA[50], setNameB[50], newName[50];
            scanf("%s %s %s", setNameA, setNameB, newName);

            if (!nameAvail(newName)) {
                printf("O nome '%s' já está em uso.\n", newName);
                continue;
            }

            SET *setA = find_set(setNameA);
            SET *setB = find_set(setNameB);

            if (setA == NULL || setB == NULL) {
                printf("Um ou ambos os conjuntos não foram encontrados.\n");
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
                printf(
                    "Falha ao criar o conjunto ou limite de conjuntos "
                    "atingido.\n");
                if (newSet != NULL) {
                    destroy_set(&newSet);
                }
            }
        } else {
            printf("Comando não reconhecido.\n");
        }
    }

    return 0;
}
