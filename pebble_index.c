
#include "pebble_index.h"
#include <stdlib.h>
#include <string.h>

HashTable *index_create(size_t capacity)
{
    // Reject an invalid capacity
    if (capacity == 0) {
        return NULL;
    }

    // Allocate memory for the HashTable structure
    HashTable *table = malloc(sizeof(HashTable));

    if (table == NULL) {
        return NULL;
    }

    // Allocate an array of bucket pointers
    table->buckets = calloc(capacity, sizeof(Entry *));

    if (table->buckets == NULL) {
        free(table);
        return NULL;
    }

    // Initialize the table
    table->size = 0;
    table->capacity = capacity;

    return table;
}
void index_destroy(HashTable *table)
{
    if (table == NULL) {
        return;
    }
    free(table->buckets);
    free(table);
}

static size_t hash_key(const void *key, size_t key_len)
{
    const unsigned char *bytes = key;
    size_t hash = 5381;

    for (size_t i = 0; i < key_len; i++) {
        
        hash = hash*33+bytes[i];
    }

    
    return  hash;
}
int index_put(
    HashTable *table,
    const void *key,
    size_t key_len,
    const void *value,
    size_t value_len)
{
    if (table == NULL || key == NULL || key_len == 0 ||
        (value == NULL && value_len > 0)) {
        return 0;
    }

    size_t bucket = hash_key(key, key_len) % table->capacity;
    Entry *current = table->buckets[bucket];

    while (current != NULL) {
        if (current->key_len == key_len && memcmp(current->key, key, key_len) == 0) {
            char *new_value = malloc(value_len > 0 ? value_len : 1);

            if (new_value == NULL) {
                return 0;
            }

            if (value_len > 0) {
                memcpy(new_value, value, value_len);
            }

            free(current->value);
            current->value = new_value;
            current->value_len = value_len;
            return 1;
            }
        current = current->next;
    }
}