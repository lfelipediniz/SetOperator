#include "../inc/set.h"

int main() {
    SET *mySet = create_set();
    // You would add elements to the AVL tree here, like this:
    addElement_set(mySet, create_item(10));
    addElement_set(mySet, create_item(20));
    addElement_set(mySet, create_item(50));
    addElement_set(mySet, create_item(2));
    addElement_set(mySet, create_item(7));

    // print the tree of set indexes
    print_set(mySet);

    // Clean up
    destroy_set(&mySet);

    printf("\n");
    return 0;
}
