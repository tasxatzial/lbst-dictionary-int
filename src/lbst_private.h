#ifndef _LBST_PRIVATE_H_
#define _LBST_PRIVATE_H_

#include <stdio.h>


/* Node for the root node of the dictionary */
struct lbst {
    struct lbst_node *head;
};


/* Tree nodes (non root) that store a (key, data) pair.
Leaf nodes have lc and rc equal to NULL.
Internal nodes have lc and rc not NULL*/
struct lbst_node {
    int key;
    int data;
    struct lbst_node *lc;
    struct lbst_node *rc;
    struct lbst_node *next;
};


/* Prints the full tree structure of the dictionary (preorder traversal) */
void lbst_print_tree(struct lbst *root);


/* Prints the full tree structure of the subtree (preorder traversal) */
void lbst_print_subtree(struct lbst_node *node);


#endif