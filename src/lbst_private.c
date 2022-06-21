#include <stdio.h>
#include <assert.h>
#include "lbst_private.h"


/* Prints the full tree structure of the dictionary (preorder traversal) */
void lbst_print_tree(struct lbst *root) {
    assert(root);

    lbst_print_subtree(root->head);
}


/* Prints the full tree structure of the subtree  (preorder traversal) */
void lbst_print_subtree(struct lbst_node *node) {
    if (node == NULL) {
        return;
    }
    printf("[%d,%d]", node->key, node->data);
    if (node->next != NULL) {
        printf(" --> [%d,%d]\n", node->next->key, node->next->data);
    }
    else {
        printf("\n");
    }
    lbst_print_subtree(node->lc);
    lbst_print_subtree(node->rc);
}
