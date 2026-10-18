#include "pebble_index.h"
#include <stdio.h>

int main(void) {
    HashTable *table = index_create(16);

    if (table == NULL) {
        printf("Failed to create hash table\n");
        return 1;
    }

    printf("Capacity: %zu\n", table->capacity);
    printf("Size: %zu\n", table->size);
    index_destroy(table);
    table = NULL;

    return 0;
}