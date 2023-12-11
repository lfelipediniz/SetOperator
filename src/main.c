#include "set.h"
#include <string.h>

#define MAX_SETS 10

SET *sets[MAX_SETS];
int num_sets = 0;

SET *find_set(char *name) {
    for (int i = 0; i < num_sets; i++) {
        char *setName = getName_set(sets[i]);
        if (setName != NULL && strcmp(setName, name) == 0)
            return sets[i];
    }
    return NULL;
}


int main() {
    char command[100];
    char setName[50];
    int itemKey;

    while (true) {
        printf("Digite o comando:\n");
        scanf("%s", command);

        if (strcmp(command, "create-set") == 0) {
            if (num_sets >= MAX_SETS) {
                printf("Limite de conjuntos atingido.\n");
                continue;
            }

            scanf("%s", setName);
            sets[num_sets++] = create_set(setName);
        } else if (strcmp(command, "addItem-set") == 0) {
            scanf("%s %d", setName, &itemKey);
            SET *set = find_set(setName);
            if (set != NULL) {
                addElement_set(set, create_item(itemKey));
            } else {
                printf("Conjunto não encontrado.\n");
            }
        }
        // Adicione aqui mais comandos conforme necessário.
    }

    // Não esqueça de liberar a memória e destruir os conjuntos no final.
    for (int i = 0; i < num_sets; i++) {
        destroy_set(&sets[i]);
    }

    return 0;
}
