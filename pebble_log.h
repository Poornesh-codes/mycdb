#ifndef PEBBLE_LOG_H
#define PEBBLE_LOG_H

#define RECORD_PUT 1
#define RECORD_DELETE 2
#include <stdio.h>
#include <stddef.h>
FILE *log_open(const char *filename);
void log_close(FILE *log);
int log_append_put(
    FILE *log,
    const void *key,
    size_t key_len,
    const void *value,
    size_t value_len
);
#endif