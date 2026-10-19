
#include "pebble_index.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    HashTable *table = index_create(2);

    if (table == NULL) {
        printf("Table creation failed\n");
        return 1;
    }

    // Insert three keys into a table with only two buckets
    if (!index_put(table, "color1", 6, "blue", 4) ||
        !index_put(table, "color2", 6, "blu", 3) ||
        !index_put(table, "color3", 6, "bl", 2)) {
        printf("Insert failed\n");
        index_destroy(table);
        return 1;
    }

    // Retrieve and print all three values
    size_t value_len;
    const void *value;

    value = index_get(table, "color1", strlen("color1"), &value_len);
    if (value != NULL) {
        printf("color1 = %.*s\n", (int)value_len, (const char *)value);
    }

    value = index_get(table, "color2", strlen("color2"), &value_len);
    if (value != NULL) {
        printf("color2 = %.*s\n", (int)value_len, (const char *)value);
    }

    value = index_get(table, "color3", strlen("color3"), &value_len);
    if (value != NULL) {
        printf("color3 = %.*s\n", (int)value_len, (const char *)value);
    }

    printf("Size before deletion: %zu\n", table->size);

    // Delete color2
    if (index_delete(table, "color2", strlen("color2"))) {
        printf("color2 deleted\n");
    } else {
        printf("Delete failed\n");
    }

    // Confirm color2 is gone
    value = index_get(table, "color2", strlen("color2"), &value_len);
    if (value == NULL) {
        printf("color2 not found\n");
    }

    // Confirm the other keys still exist
    value = index_get(table, "color1", strlen("color1"), &value_len);
    if (value != NULL) {
        printf("color1 still exists: %.*s\n",
               (int)value_len, (const char *)value);
    }

    value = index_get(table, "color3", strlen("color3"), &value_len);
    if (value != NULL) {
        printf("color3 still exists: %.*s\n",
               (int)value_len, (const char *)value);
    }

    printf("Size after deletion: %zu\n", table->size);

    index_destroy(table);
    return 0;
}
