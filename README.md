# Leaf-oriented binary search trees

A data structure that can be used for storing dictionaries, which are sorted collections of (key, value) pairs, sorted by key.

This version supports (key, value) pairs that have type (int, int).

The following functions are provided:

* lbst_create(): Create an empty dictionary.
* lbst_is_empty(d): Check whether the dictionary is empty.
* lbst_insert(d, key, value): Insert (key, value). If key exists, update its value.
* lbst_delete(d, key): Delete key.
* lbst_lookup(d, key, *value): Get the value associated with key.
* lbst_print(d): Print the dictionary.
* lbst_clear(d): Clear the dictionary.
* lbst_destroy(d): Clear the dictionary. No other functions should be used after this one.
* lbst_range_query(d, first, last): Print all pairs with key between first and last (inclusive).

## Implementation

The dictionary is defined as an [opaque data type](https://en.wikipedia.org/wiki/Opaque_data_type). The public interface is defined in [lbst.h](src/lbst.h).

Time complexity is O(tree_height) for 'insert', 'delete', 'lookup' and O(tree_height + number of keys) for 'range_query'. Details can be found in [lbst.md](lbst.md).

For a more advanced version of the library that supports (char*, void*) pairs, see [leaf-search-tree.c](https://github.com/tasxatzial/leaf-search-tree.c).

## Compile

Build the library (functions declared in [lbst.h](src/lbst.h)):

```bash
make lbst.o
```

## Demo

Using the library is demonstrated in [main.c](src/main.c).

Build:

```bash
make lbst_demo
```

Run:

```bash
./lbst_demo
```

## Profiling

'lbst_demo' has been tested for memory leaks with [valgrind](https://valgrind.org/) and [AddressSanitizer](https://github.com/google/sanitizers/wiki/AddressSanitizer).
