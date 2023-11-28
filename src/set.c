#include "../inc/set.h"

// Data Struct choisen: AVL Tree

typedef struct node_ NODE;

typedef struct node_ {
    ITEM *item;
    NODE *left;
    NODE *right;
    int height;
} NODE ;

struct set_ {
    NODE *root;
    int depth;
};

// auxiliar functions
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
        NODE *b = a-> left;
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

    NODE *insertNode(NODE *root, NODE * node){
        if(!root) root = node;
        else if(getKey_item(node->item) < getKey_item(root->item))
            root->left = insertNode(root->left, node);
        else if(getKey_item(node->item) > getKey_item(root->item))
            root->right = insertNode(root->right, node);

        root->height = max(height(root->left), height(root->right)) + 1;

        return root;
    }
// basic operations

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

    bool addElement_set(SET *sp, ITEM * ele) {
        NODE * new;
        if(!sp) return false;
        new = nodeCreator(ele);
        if(new){
            sp->root = insertNode(sp->root, new);
            return true;
        }
        return false;
    }