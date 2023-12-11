#include "../inc/set.h"

// Data Struct chosen: AVL Tree

struct node_ {
    ITEM *item;
    NODE *left;
    NODE *right;
    int height;
};
struct set_ {
    NODE *root;
    int depth;
};

// --------------------------------------------------------------------------------------------------------------------------
//                                              auxiliar functions
// --------------------------------------------------------------------------------------------------------------------------

void destroyAux(NODE *root) {
    if (root) {
        destroyAux(root->left);
        destroyAux(root->right);
        delete_item(&(root->item));
        free(root);
    }
}

int height(NODE *root) {
    if (!root) return -1;
    return root->height;
}

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

NODE *rightRotation(NODE *a) {
    NODE *b = a->left;
    a->left = b->right;
    b->right = a;

    a->height = max(height(a->left), height(a->right)) + 1;
    b->height = max(height(b->right), a->height) + 1;

    return b;
}

NODE *leftRotation(NODE *a) {
    NODE *b = a->right;
    a->right = b->left;
    b->left = a;

    a->height = max(height(a->left), height(a->right)) + 1;
    b->height = max(height(b->right), a->height) + 1;

    return b;
}

NODE *leftRightRotation(NODE *a) {
    a->left = leftRotation(a->left);
    return rightRotation(a);
}

NODE *rightLeftRotation(NODE *a) {
    a->right = rightRotation(a->right);
    return leftRotation(a);
}

NODE *insertNode(NODE *root, NODE *node) {
    if (!root)
        root = node;
    else if (getKey_item(node->item) < getKey_item(root->item))
        root->left = insertNode(root->left, node);
    else if (getKey_item(node->item) > getKey_item(root->item))
        root->right = insertNode(root->right, node);

    root->height = max(height(root->left), height(root->right)) + 1;

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

NODE *removeElementAux(NODE **root, int key) {
    NODE *p;

    if (!root)
        return NULL;
    else if (key == getKey_item((*root)->item)) {
        // Case 1 and 2: Child exists or not
        if (!(*root)->left || !(*root)->right) {
            p = *root;
            if (!(*root)->left)
                *root = (*root)->right;
            else
                *root = (*root)->left;

            free(p);
            p = NULL;
        }

        // Case 3: Both children exist
        else {
            p = (*root)->left;
            while (p->right) p = p->right;

            (*root)->item = p->item;
            (*root)->left =
                removeElementAux(&((*root)->left), getKey_item(p->item));
        }
    }

    else if (key < getKey_item((*root)->item))
        (*root)->left = removeElementAux(&((*root)->left), key);
    else
        (*root)->right = removeElementAux(&((*root)->right), key);

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

void *aux_union(SET *uni, NODE *root) {
    addElement_set(uni, root->item);
    if (root->left != NULL) {
        aux_union(uni, root->left);
    }
    if (root->right != NULL) {
        aux_union(uni, root->right);
    }
}

// --------------------------------------------------------------------------------------------------------------------------
//                                                   basic operations
// --------------------------------------------------------------------------------------------------------------------------

SET *create_set() {
    SET *sp = (SET *)malloc(sizeof(SET));
    if (sp) {
        sp->root = NULL;
        sp->depth = -1;
    }
    return sp;
}

bool destroy_set(SET **sp) {
    destroyAux((*sp)->root);
    free(*sp);
    *sp = NULL;
    return true;
}

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

bool removeElement_set(SET *sp, ITEM *ele) {
    if (!sp) return false;
    return removeElementAux(&(sp->root), getKey_item(ele));
}

// forward declaration for recursive helper function
void printSubtree(NODE *node);

//  print a single node and its children
void printNode(NODE *node) {
    if (node == NULL) {
        return;
    }

    int key = getKey_item(node->item);
    printf("%d: ", key);
    printSubtree(node);

}

// recursive helper function to print the children of a node
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

// wrapper function to print the entire tree
void print_set(SET *set) { printNode(set->root); }


int search(SET *sp, int key) {
    NODE *temp = sp->root;
    while (temp != NULL) {
        if (key != getKey_item(temp->item)) {
            return 1;
        } else if (key > getKey_item(temp->item)) {
            temp = temp->right;
        } else {
            temp = temp->left;
        }
    }
    return 0;
}

// --------------------------------------------------------------------------------------------------------------------------
//                                               specific operations
// --------------------------------------------------------------------------------------------------------------------------

SET *union_set(SET *sp1, SET *sp2) {
    SET *uni = create_set();
    aux_union(uni, sp1->root);
    aux_union(uni, sp2->root);
    return uni;
}

