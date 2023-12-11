#include "../inc/set.h"

int main() {
    SET *mySet = create_set();

    addElement_set(mySet, create_item(10));
    addElement_set(mySet, create_item(20));
    addElement_set(mySet, create_item(50));
    addElement_set(mySet, create_item(2));
    addElement_set(mySet, create_item(7));
    addElement_set(mySet, create_item(51));

    // print the tree of set indexes
    print_set(mySet);

    SET *mySet2 = create_set();

    addElement_set(mySet2, create_item(10));
    addElement_set(mySet2, create_item(233));
    addElement_set(mySet2, create_item(32));


    print_set(mySet2);

    SET * mySet3 = union_set(mySet, mySet2);

    print_set(mySet3);

    printf("\n");

    if(isMember_set(mySet3, create_item(11))) {
        printf("is a member of the set\n");
    } else {
        printf("is not a member of the set\n");
    }

    SET * mySet4 = intersection_set(mySet, mySet3);

    print_set(mySet4);


    // Clean up

    destroy_set(&mySet);
    destroy_set(&mySet2);
    destroy_set(&mySet3);
    destroy_set(&mySet4);
    printf("\n");
    return 0;
}
