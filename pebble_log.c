
#include "pebble_log.h"
#include <stdint.h>

FILE *log_open(const char *filename)
{
    if (filename == NULL) {
        return NULL;
    }

    return fopen(filename, "a+b");
}

void log_close(FILE *log)
{
    if (log != NULL) {
        fclose(log);
    }
}
#include <stdint.h>

static int write_u32_le(FILE *log, uint32_t number)
{
    unsigned char bytes[4];

    bytes[0] = number & 0xFF;
    bytes[1] = (number >> 8) & 0xFF;
    bytes[2] = (number >> 16) & 0xFF;
    bytes[3] = (number >> 24) & 0xFF;

    return fwrite(bytes, 1, 4, log) == 4;
}
int log_append_put(
    FILE *log,
    const void *key,
    size_t key_len,
    const void *value,
    size_t value_len
) {
    if (log == NULL || key == NULL || key_len == 0) {
        return 0;
    }

    if (value == NULL && value_len > 0) {
        return 0;
    }

    if (key_len > 1024 || value_len > 1024 * 1024) {
        return 0;
    }

    unsigned char type = RECORD_PUT;

    if (fwrite(&type, 1, 1, log) != 1) {
        return 0;
    }

    if (!write_u32_le(log, (uint32_t)key_len)) {
        return 0;
    }

    if (!write_u32_le(log, (uint32_t)value_len)) {
        return 0;
    }

    if (fwrite(key, 1, key_len, log) != key_len) {
        return 0;
    }

    if (value_len > 0 &&
        fwrite(value, 1, value_len, log) != value_len) {
        return 0;
    }

    return fflush(log) == 0;
}