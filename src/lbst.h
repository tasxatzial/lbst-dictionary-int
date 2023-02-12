#ifndef _LBST_H_
#define _LBST_H_

#include <stdio.h>

typedef void* lbst_T;


/* Inserts a new (key, data) into the dictionary. If key is already in the
dictionary, its data is updated.

Returns:
* 1 If key was added/updated.
* -1 On error.

Time complexity: O(h) */
int lbst_insert(lbst_T root, int key, int data);


/* Deletes a key from the dictionary.

Returns:
* 1 If the key is found and deleted.
* 0 If the key is not found.

Time complexity: O(h) */
int lbst_delete(lbst_T root, int key);


/* Searches for a key in the dictionary.

If key is found, its data is *data. Return value is 1.
If key is not found, return value is 0. The specified data pointer should
be ignored.

Time complexity: O(h) */
int lbst_lookup(lbst_T root, int key, int *data);


/* Returns 1 if dictionary has no keys, 0 otherwise */
int lbst_is_empty(lbst_T root);


/* Creates and returns an empty dictionary. Its (key, data) pairs have
type (int, int).

Returns NULL on fail.*/
lbst_T lbst_create();


/* Clears the dictionary. The function lbst_is_empty() returns 1 after
calling this one. */
void lbst_clear(lbst_T root);


/* Clears the dictionary. No other functions should be called after
calling this one. */
void lbst_destroy(lbst_T root);


/* Prints (key, data) that satisfy first <= key <= last.

Time complexity: O(h + last - first) */
void lbst_range_query(lbst_T root, int first, int last);


/* Prints the dictionary. (key, data) pairs are sorted by key (ascending).

Time complexity: O(h + #keys) */
void lbst_print(lbst_T root);

#endif