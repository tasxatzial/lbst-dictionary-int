/* Test file for the dictionary library */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lbst.h"
#include "lbst_private.h"

int main() {
    int i, key, data, found;
    lbst_T root;

    /* create dictionary */
    root = lbst_create();
    srand(time(NULL));

    /* insert 10 random (key, data) */
    printf("----------Insert-----------------------------------\n");
    for (i = 0; i < 10; i++) {
        key = rand() % 15;
        data = rand() % 10;
        printf("(%d,%d):\t", key, data);
        lbst_insert(root, key, data);

        /* print dictionary after each insertion */
        lbst_print(root);
    }

    /* print full tree */
    printf("----------Print tree (preorder traversal)----------\n");
    lbst_print_tree(root);

    /* lookup random (key, data) */
    printf("----------Lookup-----------------------------------\n");
    for (i = 0; i < 5; i++) {
        key = rand() % 15;
        printf("%d -> ", key);
        found = lbst_lookup(root, key, &data);
        if (found) {
            printf("%d\n", data);
        }
        else {
            printf("Not found\n");
        }
    }
    
    /* lookup keys in [a, b] */
    printf("----------Range Query [5,8]------------------------\n");
    lbst_range_query(root, 5, 8);

    /* delete random keys */
    printf("----------Delete-----------------------------------\n");
    for (i = 0; i < 20; i++) {
        key = rand() % 15;
        printf("%d:\t", key);
        lbst_delete(root, key);
        lbst_print(root);
    }

    /* clear dictionary */
    printf("---------------------------------------------------\n");
    printf("Clear dictionary\n");
    lbst_clear(root);

    /* check if empty */
    printf("Check if dictionary is empty (should print 1): %d\n", lbst_is_empty(root));

    /* should print nothing */
    printf("Print dictionary: ");
    lbst_print(root);

    /* re-use dictionary: insert */
    printf("Re-use dictionary. Insert [1,1]\n");
    lbst_insert(root, 1, 1);

    printf("Print dictionary: ");
    lbst_print(root);
    
    /* clear dictionary */
    printf("Clear dictionary\n");
    lbst_clear(root);

    printf("Print dictionary: ");
    lbst_print(root);

    /* check if empty */
    printf("Check if dictionary is empty (should print 1): %d\n", lbst_is_empty(root));

    /* destroy dictionary.
    We cannot call any other functions after this */
    printf("Destroy dictionary\n");
    lbst_destroy(root);

    return 0;
}