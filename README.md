# lbst - A dictionary data structure

Library for creating dictionaries, that is, sorted collections by key of (key, value) pairs.

This version supports (key, value) pairs that have type (int, int). Pairs are sorted by key (ascending).

The following functions are provided:

* lbst_create(): Create an empty dictionary.
* lbst_is_empty(d): Check whether the dictionary is empty.
* lbst_insert(d, key, value): Insert (key, value). If key exists, update its value.
* lbst_delete(d, key): Delete key.
* lbst_lookup(d, key, *value): Get the value associated with key.
* lbst_print(d): Print the dictionary.
* lbst_clear(d): Clear the dictionary.
* lbst_destroy(d): Clear the dictionary. No other functions should be used after this one.
* lbst_range_query(d, first, last): Print all (key, value) with key between first and last (inclusive).

## Implementation

The library exposes the dictionary as an [opaque data type](https://en.wikipedia.org/wiki/Opaque_data_type).

Internally the dictionary is stored as a leaf-oriented binary search tree structure. Time complexity of operations 'insert', 'delete', 'lookup' is O(tree_height) whereas 'range_query' has a complexity of O(tree_height + last - first). More details can be found in [lbst.md](docs/lbst.md) (english) and [lbst.pdf](docs/lbst.pdf) (greek).

For a more advanced version of the library that supports (char*, void*) pairs, see [lbst-dictionary](https://github.com/tasxatzial/lbst-dictionary).

## Compile

Build the library (functions declared in lbst.h):

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
