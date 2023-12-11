#include "../inc/set.h"

// Data Struct chosen: AVL Tree

struct node_ {
    ITEM *item;
    NODE *left;   // pointer to left child
    NODE *right;  // pointer to right child
    int height;   // height of the node
};
struct set_ {
    NODE *root;  // root node of the AVL tree Set
    int depth;   // depth of the tree
    char *name;  // name of the set
};

// --------------------------------------------------------------------------------------------------------------------------
//                                              auxiliar functions
// --------------------------------------------------------------------------------------------------------------------------

// recursively destroys the AVL tree
void destroyAux(NODE *root) {
    if (root) {
        destroyAux(root->left);
        destroyAux(root->right);
        delete_item(&(root->item));
        free(root);
    }
}

// returns the height of a node or -1 if the node is NULL
int height(NODE *root) {
    if (!root) return -1;
    return root->height;
}

// creates a new node with the provided item
NODE *nodeCreator(ITEM *item) {
    NODE *node = (NODE *)malloc(sizeof(NODE));
    if (node) {
        node->height = 0;
        node->right = NULL;
        node->left = NULL;
        node->item = item;
    }
    return node;
}

// performs a right rotation on node a
NODE *rightRotation(NODE *a) {
    NODE *b = a->left;
    a->left = b->right;
    b->right = a;

    a->height = max(height(a->left), height(a->right)) + 1;
    b->height = max(height(b->right), a->height) + 1;

    return b;
}

// performs a left rotation on node a
NODE *leftRotation(NODE *a) {
    NODE *b = a->right;
    a->right = b->left;
    b->left = a;

    a->height = max(height(a->left), height(a->right)) + 1;
    b->height = max(height(b->right), a->height) + 1;

    return b;
}

// performs a left-right rotation on node a
NODE *leftRightRotation(NODE *a) {
    a->left = leftRotation(a->left);
    return rightRotation(a);
}

// performs a right-left rotation on node a
NODE *rightLeftRotation(NODE *a) {
    a->right = rightRotation(a->right);
    return leftRotation(a);
}

// inserts a node into the AVL tree, maintaining its balance
NODE *insertNode(NODE *root, NODE *node) {
    if (!root)
        root = node;
    else if (getKey_item(node->item) < getKey_item(root->item))
        root->left = insertNode(root->left, node);
    else if (getKey_item(node->item) > getKey_item(root->item))
        root->right = insertNode(root->right, node);

    root->height = max(height(root->left), height(root->right)) + 1;

    // balance the tree after insertion
    if (height(root->left) - height(root->right) == 2) {
        if (getKey_item(node->item) < getKey_item(root->left->item))
            root = rightRotation(root);
        else
            root = leftRightRotation(root);
    } else if (height(root->right) - height(root->left) == 2) {
        if (getKey_item(node->item) > getKey_item(root->right->item))
            root = leftRotation(root);
        else
            root = rightLeftRotation(root);
    }

    return root;
}

// auxiliary function to remove an element from the AVL tree
NODE *removeElementAux(NODE **root, int key) {
    NODE *p;

    if (!root)
        return NULL;
    else if (key == getKey_item((*root)->item)) {
        // handles deletion of a node with one or no children
        // Case 1 and 2
        if (!(*root)->left || !(*root)->right) {
            p = *root;
            if (!(*root)->left)
                *root = (*root)->right;
            else
                *root = (*root)->left;

            free(p);
            p = NULL;
        }
        // handles deletion of a node with two children
        // Case 3
        else {
            p = (*root)->left;
            while (p->right) p = p->right;

            (*root)->item = p->item;
            (*root)->left =
                removeElementAux(&((*root)->left), getKey_item(p->item));
        }
    } else if (key < getKey_item((*root)->item))
        (*root)->left = removeElementAux(&((*root)->left), key);
    else
        (*root)->right = removeElementAux(&((*root)->right), key);

    // balance the tree after deletion
    if ((*root)) {
        (*root)->height =
            max(height((*root)->left), height((*root)->right)) + 1;

        if (height((*root)->left) - height((*root)->right) == -2) {
            if (height((*root)->right->left) - height((*root)->right->right) <=
                0)
                (*root) = leftRotation((*root));
            else
                (*root) = rightLeftRotation((*root));
        }

        if (height((*root)->left) - height((*root)->right) == 2) {
            if (height((*root)->left->left) - height((*root)->left->right) >= 0)
                (*root) = rightRotation((*root));
            else
                (*root) = leftRightRotation((*root));
        }
    }

    return (*root);
}

// forward declaration for recursive helper function
void printSubtree(NODE *node);

// prints a single node and its children
void printNode(NODE *node) {
    if (node == NULL) {
        return;
    }

    int key = getKey_item(node->item);
    printf("%d: ", key);
    printSubtree(node);
}

// recursively prints the children of a node
void printSubtree(NODE *node) {
    if (node == NULL) {
        return;
    }

    if (node->left == NULL && node->right == NULL) {
        printf("{}");
    } else {
        printf("{");
        if (node->left != NULL) {
            printNode(node->left);
            if (node->right != NULL) {
                printf(", ");
            }
        }
        if (node->right != NULL) {
            printNode(node->right);
        }
        printf("}");
    }
}

// adds all elements of a tree to the given set
void aux_union(SET *uni, NODE *root) {
    ITEM *item = create_item(getKey_item(root->item));
    addElement_set(uni, item);
    if (root->left != NULL) {
        aux_union(uni, root->left);
    }
    if (root->right != NULL) {
        aux_union(uni, root->right);
    }
}

// checks if a key is a member of the set represented by the AVL tree
bool isMember_aux(NODE *node, int key) {
    if (node == NULL) {
        return false;  // reached leaf, element not found
    }

    int nodeKey = getKey_item(node->item);

    if (key == nodeKey) {
        return true;  // found element
    } else if (key < nodeKey) {
        return isMember_aux(node->left, key);  // search in the left subtree
    } else {
        return isMember_aux(node->right, key);  // search in the right subtree
    }
}

// helper function to perform the intersection operation by traversing the tree
// in order to avoid repetition
void inOrder_interSectionAux(NODE *node, SET *intersection, SET *other) {
    if (node == NULL) {
        return;
    }

    inOrder_interSectionAux(node->left, intersection, other);

    if (isMember_set(other, node->item)) {
        ITEM *item = create_item(getKey_item(node->item));
        addElement_set(intersection, item);
    }

    inOrder_interSectionAux(node->right, intersection, other);
}


char *strdup_auxNameSetCreator(const char *s) {
    char *d = malloc(strlen(s) + 1); // reserve memory for string
    if (d == NULL) return NULL;      // checks whether the allocation was successful
    strcpy(d, s);                    // copy a string
    return d;
}


// --------------------------------------------------------------------------------------------------------------------------
//                                                   basic operations
// --------------------------------------------------------------------------------------------------------------------------

// creates a new set
SET *create_set(char *name) {
    SET *sp = (SET *)malloc(sizeof(SET));
    if (sp) {
        sp->root = NULL;
        sp->depth = -1;
        sp->name = strdup_auxNameSetCreator(name);
    }
    // if the name is NULL, the set is not created
    if (!sp->name) {
        free(sp);
        return NULL;
    }

    return sp;
}

// destroys a set and frees its memory
bool destroy_set(SET **sp) {
    if (sp != NULL && *sp != NULL) {
        destroyAux((*sp)->root); // detroys the AVL tree inside the set

        free((*sp)->name); // free the memory allocated for the name
        (*sp)->name = NULL; // evite dangling pointer

        free(*sp); // free the memory allocated for the set
        *sp = NULL; // evite dangling pointer
        return true;
    }
    return false;
}

// adds an element to the set
bool addElement_set(SET *sp, ITEM *ele) {
    NODE *new;
    if (!sp) return false;
    new = nodeCreator(ele);
    if (new) {
        sp->root = insertNode(sp->root, new);
        return true;
    }
    return false;
}

// removes an element from the set
bool removeElement_set(SET *sp, ITEM *ele) {
    if (!sp) return false;
    removeElementAux(&(sp->root), getKey_item(ele));
    return true;
}

// wrapper function to print the entire tree
void print_set(SET *set) {
    printf("\n");
    printNode(set->root);
}

// returns the name of the set
char *getName_set(SET *set) {
    if (set != NULL) return set->name;

    return NULL;
}

// --------------------------------------------------------------------------------------------------------------------------
//                                               specific operations
// --------------------------------------------------------------------------------------------------------------------------

// checks if an element is a member of the set
bool isMember_set(SET *sp, ITEM *ele) {
    return isMember_aux(sp->root, getKey_item(ele));
}

// creates a new set that is the union of two sets
SET *union_set(SET *sp1, SET *sp2, char *name) {
    SET *uni = create_set(name);
    aux_union(uni, sp1->root);
    aux_union(uni, sp2->root);
    return uni;
}

SET *intersection_set(SET *sp1, SET *sp2, char *name) {
    if (!sp1 || !sp2) return NULL;

    SET *smaller = (sp1->depth < sp2->depth) ? sp1 : sp2;
    SET *other = (smaller == sp1) ? sp2 : sp1;
    SET *intersection = create_set(name);

    inOrder_interSectionAux(smaller->root, intersection, other);

    if (intersection->root == NULL) {  // No elements added
        destroy_set(&intersection);
        return NULL;
    }

    return intersection;
}