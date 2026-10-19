
#ifndef PEBBLE_INDEX_H
#define PEBBLE_INDEX_H

#include <stddef.h>
#include <stdint.h>
#include<stdlib.h>


typedef struct Entry {
    char *key;
    size_t key_len;
    char *value;
    size_t value_len;
    struct Entry *next;

} Entry;

typedef struct HashTable {
    Entry **buckets;
    size_t capacity;
    size_t size;
} HashTable;

HashTable *index_create(size_t capacity);
void index_destroy(HashTable *table);
int index_put(
    HashTable *table,
    const void *key,
    size_t key_len,
    const void *value,
    size_t value_len
);
const void *index_get(
    const HashTable *table,
    const void *key,
    size_t key_len,
    size_t *value_len_out
);
int index_delete(
    HashTable *table,
    const void *key,
    size_t key_len
);
int index_exists(
    const HashTable *table,
    const void *key,
    size_t key_len
);
#endif
