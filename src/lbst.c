/* A library for creating and using dictionaries of integer (key, data) pairs */

#include <stdio.h>
#include <stdlib.h>
#include "lbst.h"
#include "lbst_public.h"

static void lbst_delete_root(struct lbst *root);
static void lbst_delete_nodes(struct lbst_node *node);


/* Inserts a new (key, data) into the dictionary. If key is already in the
dictionary, its data is updated.

Time complexity: O(h) */
void lbst_insert(lbst_T root, int key, int data) {
    struct lbst *root_private = root;
    struct lbst_node *ptr, *n1, *n2, *parent, *grparent;

    /* special case: root has not been initialized using lbst_create() */
    if (root_private == NULL) {
        printf("Error inserting: NULL root\n");
        return;
    }

    /* special case: 0 (key, data) nodes */
    if (root_private->head == NULL) {
        ptr = malloc(sizeof(struct lbst_node));
        if (ptr == NULL) {
            printf("Error inserting: Mem alloc NULL\n");
            return;
        }
        ptr->key = key;
        ptr->data = data;
        ptr->next = NULL;
        ptr->lc = NULL;
        ptr->rc = NULL;
        root_private->head = ptr;
        return;
    }

    /* traverse the tree and find a leaf that should be
    used as parent node of the new nodes */
    ptr = root_private->head;
    parent = NULL;
    grparent = NULL; /* parent node of parent */
    while(ptr != NULL) {
        grparent = parent;
        parent = ptr;
        if (key <= ptr->key) {
            ptr = ptr->lc;
        }
        else {
            ptr = ptr->rc;
        }
    }

    /* update the parent data if the same key was provided */
    if (parent->key == key) {
        parent->data = data;
        return;
    }

    /* create two new nodes n1, n2 */
    n1 = malloc(sizeof(struct lbst_node));
    if (n1 == NULL) {
        printf("Error inserting: Mem alloc NULL\n");
        return;
    }
    n1->rc = NULL;
    n1->lc = NULL;
    n1->next = NULL;

    n2 = malloc(sizeof(struct lbst_node));
    if (n2 == NULL) {
        free(n1);
        printf("Error inserting: Mem alloc NULL\n");
        return;
    }
    n2->rc = NULL;
    n2->lc = NULL;
    n2->next = NULL;

    /* initialize pointers */
    n1->next = parent->next;
    parent->next = n1;
    n2->lc = parent;
    n2->rc = n1;

    /* now arrange (key, data) of grparent, parent, n1, n2 based on
    the new key */
    if (key <= parent->key) {
        n1->key = parent->key;
        n1->data = parent->data;
        parent->key = key;
        parent->data = data;
        n2->key = key;
        n2->data = data;
    }
    else {
        n2->key = parent->key;
        n2->data = parent->data;
        n1->key = key;
        n1->data = data;
    }
    if (grparent != NULL) {
        if (parent == grparent->lc)
            grparent->lc = n2;
        else
            grparent->rc = n2;
    }
    else {
        root_private->head = n2;
    }

    return;
}


/* Deletes a key from the dictionary.

Time complexity: O(h) */
void lbst_delete(lbst_T root, int key) {
    struct lbst *root_private;
    struct lbst_node *ptr, *ptr2, *child, *parent, *grparent, *last_right_child;

    root_private = root;
    if (root_private == NULL) {
        return;
    }

    /* traverse the tree based on the key and find the leaf node that
    has the key */
    ptr = root_private->head;
    last_right_child = NULL; /* last right child while traversing tree */
    child = NULL; /* this node should have the key */
    parent = NULL; /* parent node of child */
    grparent = NULL; /* parent node of parent node */
    while(ptr != NULL) {
        grparent = parent;
        parent = child;
        child = ptr;
        if (parent != NULL && parent->rc == child) {
            last_right_child = parent;
        }
        if (key <= ptr->key) {
            ptr = ptr->lc;
        }
        else {
            ptr = ptr->rc;
        }
    }

    /* nothing to do: key does not exist in the dictionary */
    if (child == NULL || child->key != key) {
        return;
    }

    /* key was found in a leaf but parent is NULL: root node has the key */
    if (parent == NULL) {
        child->next = NULL;
        child->lc = NULL;
        child->rc = NULL;
        root_private->head = NULL;
        free(child);
        return;
    }

    /* start from from the left child of last_right_node and go to
    rightmost node: Connect it to the next node of child since child
    will be deleted */
    if (last_right_child != NULL) {
        ptr = NULL;
        ptr2 = last_right_child->lc;
        while (ptr2 != NULL) {
            ptr = ptr2;
            ptr2 = ptr2->rc;
        }
        ptr->next = child->next;
    }
    
    /* if grparent of child is NULL, the parent node of child is
    the root node of the tree. But both parent and child will be deleted
    therefore root node needs to change */
    if (grparent == NULL) {
        if (parent->rc == child) {
            root_private->head = parent->lc;
        }
        else {
            root_private->head = parent->rc;
        }
    }

    /* else connect the grparent node of child to the other child
    of its parent node */
    else {
        if (parent->rc == child) {
            ptr = parent->lc;
        }
        else {
            ptr = parent->rc;
        }
        if (grparent->lc == parent) {
            grparent->lc = ptr;
        }
        else {
            grparent->rc = ptr;
        }
    }

    /* free memory occupied by child and parent */
    child->next = NULL;
    child->lc = NULL;
    child->rc = NULL;
    free(child);
    child = NULL;

    parent->next = NULL;
    parent->lc = NULL;
    parent->rc = NULL;
    free(parent);
    parent = NULL;
}


/* Finds a key in the dictionary.

If key is found, return value is 1 and the specified data pointer provides
access to key data.
If key is not found, return value is 0 and the specified data pointer should
be ignored.

Time complexity: O(h) */
int lbst_lookup(lbst_T root, int key, int *data) {
    struct lbst *root_private;
    struct lbst_node *ptr, *prev;

    root_private = root;
    if (root_private == NULL) {
        return 0;
    }

    ptr = root_private->head;
    prev = NULL;
    while(ptr != NULL) {
        prev = ptr;
        if (key <= ptr->key) {
            ptr = ptr->lc;
        }
        else {
            ptr = ptr->rc;
        }
    }
    if (prev != NULL && prev->key == key) {
        *data = prev->data;
        return 1;
    }

    return 0;
}


/* Returns 1 if dictionary has no (key, data) pairs, 0 otherwise */
int lbst_is_empty(lbst_T root) {
    struct lbst *root_private;

    root_private = root;
    if (root_private == NULL) {
        return 1;
    }
    if (root_private->head == NULL) {
        return 1;
    }
    return 0;
}


/* Creates and returns an empty dictionary. Its (key, data) pairs have
type (int, int). Key should be unique. */
lbst_T lbst_create() {
    struct lbst *root_private;

    root_private = malloc(sizeof(struct lbst));
    root_private->head = NULL;

    return (lbst_T) root_private;
}


/* Deletes the dictionary and frees allocated memory */
void lbst_delete_dict(lbst_T root) {
    struct lbst *root_private;

    root_private = root;
    if (root_private == NULL) {
        return;
    }
    lbst_delete_nodes(root_private->head);
    lbst_delete_root(root_private);
}


/* Frees memory allocated for the root node of the dictionary */
static void lbst_delete_root(struct lbst *root) {
    if (root == NULL) {
        return;
    }
    free(root);
}


/* Frees memory allocated for all (key, data) nodes of the dictionary */
static void lbst_delete_nodes(struct lbst_node *node) {
    if (node == NULL) {
        return;
    }
    lbst_delete_nodes(node->lc);
    lbst_delete_nodes(node->rc);
    free(node);
}


/* Prints (key, data) that satisfy first <= key <= last.

Time complexity: O(h + last - first) */
void lbst_range_query(lbst_T root, int first, int last) {
    struct lbst *root_private;
    struct lbst_node *ptr, *prev;

    root_private = root;
    if (root_private == NULL) {
        return;
    }

    ptr = root_private->head;
    prev = NULL;
    while(ptr != NULL) {
        prev = ptr;
        if (ptr->key >= first) {
            ptr = ptr->lc;
        }
        else {
            ptr = ptr->rc;
        }
    }
    if (prev != NULL && prev->key >= first && prev->key <= last) {
        printf("<%d,%d> ", prev->key, prev->data);
    }
    prev = prev->next;
    while (prev != NULL && prev->key <= last) {
        printf("<%d,%d> ", prev->key, prev->data);
        prev = prev->next;
    }
    printf("\n");
}


/* Prints the dictionary. (key, data) pairs are sorted by key value.

Time complexity: O(h + #keys) */
void lbst_print(lbst_T root) {
    struct lbst *root_private;
    struct lbst_node *ptr, *prev;

    root_private = root;
    if (root_private == NULL) {
        return;
    }

    /* Go to leftmost leaf node */
    ptr = root_private->head;
    prev = NULL;
    while(ptr != NULL) {
        prev = ptr;
        ptr = ptr->lc;
    }

    /* Use the next pointers to traverse the nodes
    that start from the leftmost leaf to the rightmost leaf */
    while(prev != NULL) {
        printf("<%d,%d> ", prev->key, prev->data);
        prev = prev->next;
    }

    printf("\n");
}